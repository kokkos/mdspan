//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

#ifdef _MDSPAN_HAS_SYCL
#if __has_include(<sycl/sycl.hpp>)
#include <sycl/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif
#endif

#ifdef _MDSPAN_HAS_HIP
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#endif

#include<cstdio>

namespace {
bool dispatch_host = true;

#ifdef _MDSPAN_HAS_SYCL
#define __MDSPAN_DEVICE_ASSERT_EQ(LHS, RHS) \
if (!(LHS == RHS)) { \
  sycl::ext::oneapi::experimental::printf("expected equality of %s and %s\n", #LHS, #RHS); \
  errors[0]++; \
}
#else
 #define __MDSPAN_DEVICE_ASSERT_EQ(LHS, RHS) \
 if (!(LHS == RHS)) { \
  printf("expected equality of %s and %s\n", #LHS, #RHS); \
  errors[0]++; \
}
#endif

#if defined(_MDSPAN_HAS_CUDA) || defined(_MDSPAN_HAS_HIP)

#if defined(_MDSPAN_HAS_CUDA)
void deviceSynchronize() { (void) cudaDeviceSynchronize(); }
template<class T>
void mallocManaged(T** ptr, size_t size) { (void) cudaMallocManaged(ptr, size); }
template<class T>
void freeManaged(T* ptr) { (void) cudaFree(ptr); }
#endif

#if defined(_MDSPAN_HAS_HIP)
void deviceSynchronize() { (void) hipDeviceSynchronize(); }
template<class T>
void mallocManaged(T** ptr, size_t size) { (void) hipMallocManaged(ptr, size); }
template<class T>
void freeManaged(T* ptr) { (void) hipFree(ptr); }
#endif

template<class LAMBDA>
__global__ void dispatch_kernel(const LAMBDA f) {
  f();
}

template<class LAMBDA>
void dispatch(LAMBDA&& f) {
  if(dispatch_host) {
    static_cast<LAMBDA&&>(f)();
  } else {
    dispatch_kernel<<<1,1>>>(static_cast<LAMBDA&&>(f));
    deviceSynchronize();
  }
}

template<class T>
T* allocate_array(size_t size) {
  T* ptr = nullptr;
  if(dispatch_host == true)
    ptr = new T[size];
  else
    mallocManaged(&ptr, sizeof(T)*size);
  return ptr;
}

template<class T>
void free_array(T* ptr) {
  if(dispatch_host == true)
    delete [] ptr;
  else
    freeManaged(ptr);
}

#define __MDSPAN_TESTS_RUN_TEST(A) \
 dispatch_host = true; \
 A; \
 dispatch_host = false; \
 A;

#define __MDSPAN_TESTS_DISPATCH_DEFINED
#endif // _MDSPAN_HAS_CUDA

#ifdef _MDSPAN_HAS_SYCL

sycl::queue get_test_queue()
{
  static sycl::queue q;
  return q;
}

template<class LAMBDA>
void dispatch(LAMBDA&& f) {
  if(dispatch_host) {
    static_cast<LAMBDA&&>(f)();
  } else {
    sycl::queue q = get_test_queue();
    q.submit([&](sycl::handler &cgh) {
      cgh.single_task([=]() {
        f();
      });
    });
    q.wait_and_throw();
  }
}

template<class T>
T* allocate_array(size_t size) {
  if(dispatch_host == true)
    return new T[size];
  else
  {
    sycl::queue q = get_test_queue();
    return sycl::malloc_shared<T>(size, q);
  }
}

template<class T>
void free_array(T* ptr) {
  if(dispatch_host == true)
    delete [] ptr;
  else
  {
    sycl::queue q = get_test_queue();
    sycl::free(ptr, q);
  }
}

#define __MDSPAN_TESTS_RUN_TEST(A) \
 dispatch_host = true; \
 A; \
 dispatch_host = false; \
 A;

#define __MDSPAN_TESTS_DISPATCH_DEFINED
#endif // _MDSPAN_HAS_SYCL

#ifndef __MDSPAN_TESTS_DISPATCH_DEFINED
template<class LAMBDA>
void dispatch(LAMBDA&& f) {
  static_cast<LAMBDA&&>(f)();
}
template<class T>
T* allocate_array(size_t size) {
  T* ptr = nullptr;
  ptr = new T[size];
  return ptr;
}

template<class T>
void free_array(T* ptr) {
  delete [] ptr;
}

#define __MDSPAN_TESTS_RUN_TEST(A) \
 dispatch_host = true; \
 A;
#endif
} // namespace
