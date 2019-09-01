/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include "fill.hpp"

#include <experimental/mdspan>

#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <iostream>

//================================================================================

static constexpr int global_delta = 1;
static constexpr int global_repeat = 16;

//================================================================================

template <class T, ptrdiff_t... Es>
using lmdspan = stdex::basic_mdspan<T, stdex::extents<Es...>, stdex::layout_left>;
template <class T, ptrdiff_t... Es>
using rmdspan = stdex::basic_mdspan<T, stdex::extents<Es...>, stdex::layout_right>;

void throw_runtime_exception(const std::string &msg) {
  std::ostringstream o;
  o << msg;
  throw std::runtime_error(o.str());
}

void cuda_internal_error_throw(cudaError e, const char* name,
  const char* file = NULL, const int line = 0) {
  std::ostringstream out;
  out << name << " error( " << cudaGetErrorName(e)
      << "): " << cudaGetErrorString(e);
  if (file) {
    out << " " << file << ":" << line;
  }
  throw_runtime_exception(out.str());
}

inline void cuda_internal_safe_call(cudaError e, const char* name,
       const char* file = NULL,
       const int line   = 0) {
  if (cudaSuccess != e) {
    cuda_internal_error_throw(e, name, file, line);
  }
}

#define CUDA_SAFE_CALL(call) \
  cuda_internal_safe_call(call, #call, __FILE__, __LINE__)

//================================================================================

dim3 get_bench_thread_block(ptrdiff_t M) {
  cudaDeviceProp cudaProp;
  int dim_x = 1;
  while(dim_x*8 < M && dim_x<512) dim_x *= 2;
  return dim3(dim_x,1,1);
}

template <class F, class... Args>
__global__
void do_run_kernel(F f, Args... args) {
  f(args...);
}

template <class F, class... Args>
float run_kernel_timed(ptrdiff_t N, ptrdiff_t M, F&& f, Args&&... args) {
  cudaEvent_t start, stop;
  CUDA_SAFE_CALL(cudaEventCreate(&start));
  CUDA_SAFE_CALL(cudaEventCreate(&stop));

  CUDA_SAFE_CALL(cudaEventRecord(start));
  do_run_kernel<<<N, get_bench_thread_block(M)>>>(
    (F&&)f, ((Args&&) args)...
  );
  CUDA_SAFE_CALL(cudaEventRecord(stop));
  CUDA_SAFE_CALL(cudaEventSynchronize(stop));
  float milliseconds = 0;
  CUDA_SAFE_CALL(cudaEventElapsedTime(&milliseconds, start, stop));
  return milliseconds;
}

template <class MDSpan, class... DynSizes>
MDSpan fill_device_mdspan(MDSpan, DynSizes... dyn) {

  using value_type = typename MDSpan::value_type;
  auto buffer_size = MDSpan{nullptr, dyn...}.mapping().required_span_size();
  auto host_buffer = std::make_unique<value_type[]>(
    MDSpan{nullptr, dyn...}.mapping().required_span_size()
  );
  auto host_mdspan = MDSpan{host_buffer.get(), dyn...};
  mdspan_benchmark::fill_random(host_mdspan);
  
  value_type* device_buffer = nullptr;
  CUDA_SAFE_CALL(cudaMalloc(&device_buffer, buffer_size * sizeof(value_type)));
  CUDA_SAFE_CALL(cudaMemcpy(
    device_buffer, host_buffer.get(), buffer_size * sizeof(value_type), cudaMemcpyHostToDevice
  ));
  return MDSpan{device_buffer, dyn...};
}

//================================================================================

template <class MDSpanMatrix, class... DynSizes>
void BM_MDSpan_CUDA_MatVec(benchmark::State& state, MDSpanMatrix, DynSizes... dyn) {

  using value_type = typename MDSpanMatrix::value_type;
  using MDSpanVector = lmdspan<value_type,stdex::dynamic_extent>;

  auto A = fill_device_mdspan(MDSpanMatrix{}, dyn...);
  auto x = fill_device_mdspan(MDSpanVector{}, A.extent(1));
  auto y = fill_device_mdspan(MDSpanVector{}, A.extent(0));
  
  auto lambda =  
      [=] __device__ {
         const ptrdiff_t i = blockIdx.x;
         
         for(ptrdiff_t j = threadIdx.x; j < A.extent(1); j += blockDim.x) {
           y_i += A(i,j) * x(j);
         }
         y(i) = y_i;
      };
  run_kernel_timed(A.extent(0),A.extent(1),lambda);

  for (auto _ : state) {
    auto timed = run_kernel_timed(A.extent(0),A.extent(1),lambda);
    // units of cuda timer is milliseconds, units of iteration timer is seconds
    state.SetIterationTime(timed * 1e-3);
  }
  ptrdiff_t num_elements = 2 * A.extent(0) * A.extent(1) + 2 * A.extent(0);
  state.SetBytesProcessed( R * num_elements * sizeof(value_type) * state.iterations() * global_repeat);
  state.counters["repeats"] = repeats; 
  
  CUDA_SAFE_CALL(cudaDeviceSynchronize());
  CUDA_SAFE_CALL(cudaFree(s.data()));
}

BENCHMARK_CAPTURE(BM_MDSpan_CUDA_MatVec, left, lmdspan<double,stdex::dynamic_extent,stdex::dynamic_extent>(), 100000, 5000);
BENCHMARK_CAPTURE(BM_MDSpan_CUDA_MatVec, right, rmdspan<double,stdex::dynamic_extent,stdex::dynamic_extent>(), 100000, 5000);


template <class MDSpanMatrix, class... DynSizes>
void BM_MDSpan_CUDA_MatVec_Raw_Right(benchmark::State& state, MDSpanMatrix, DynSizes... dyn) {

  using value_type = typename MDSpanMatrix::value_type;
  using MDSpanVector = lmdspan<value_type,stdex::dynamic_extent>;

  auto A = fill_device_mdspan(MDSpanMatrix{}, dyn...);
  auto x = fill_device_mdspan(MDSpanVector{}, A.extent(1));
  auto y = fill_device_mdspan(MDSpanVector{}, A.extent(0));
  
  ptrdiff_t N = A.extent(0);
  ptrdiff_t M = A.extent(1);

  T* p_A = A.data();
  T* p_x = x.data();
  T* p_y = y.data();

  auto lambda =  
      [=] __device__ {
         const ptrdiff_t i = blockIdx.x;
         
         for(ptrdiff_t j = threadIdx.x; j < M; j += blockDim.x) {
           y_i += p_A[i*M+j] * p_x[j];
         }
         p_y[i] = y_i;
      };
  run_kernel_timed(N,M,lambda);

  for (auto _ : state) {
    auto timed = run_kernel_timed(N,M,lambda);
    // units of cuda timer is milliseconds, units of iteration timer is seconds
    state.SetIterationTime(timed * 1e-3);
  }
  ptrdiff_t num_elements = 2 * A.extent(0) * A.extent(1) + 2 * A.extent(0);
  state.SetBytesProcessed( R * num_elements * sizeof(value_type) * state.iterations());
  state.counters["repeats"] = repeats; 
  
  CUDA_SAFE_CALL(cudaDeviceSynchronize());
  CUDA_SAFE_CALL(cudaFree(s.data()));
}

BENCHMARK_CAPTURE(BM_MDSpan_CUDA_MatVec_Raw_Right, right, rmdspan<double,stdex::dynamic_extent,stdex::dynamic_extent>(), 100000, 5000);


template <class MDSpanMatrix, class... DynSizes>
void BM_MDSpan_CUDA_MatVec_Raw_Left(benchmark::State& state, MDSpanMatrix, DynSizes... dyn) {

  using value_type = typename MDSpanMatrix::value_type;
  using MDSpanVector = lmdspan<value_type,stdex::dynamic_extent>;

  auto A = fill_device_mdspan(MDSpanMatrix{}, dyn...);
  auto x = fill_device_mdspan(MDSpanVector{}, A.extent(1));
  auto y = fill_device_mdspan(MDSpanVector{}, A.extent(0));
  
  ptrdiff_t N = A.extent(0);
  ptrdiff_t M = A.extent(1);

  T* p_A = A.data();
  T* p_x = x.data();
  T* p_y = y.data();

  auto lambda =  
      [=] __device__ {
         const ptrdiff_t i = blockIdx.x;
         
         for(ptrdiff_t j = threadIdx.x; j < M; j += blockDim.x) {
           y_i += p_A[i+j*N] * p_x[j];
         }
         p_y[i] = y_i;
      };
  run_kernel_timed(N,M,lambda);

  for (auto _ : state) {
    auto timed = run_kernel_timed(N,M,lambda);
    // units of cuda timer is milliseconds, units of iteration timer is seconds
    state.SetIterationTime(timed * 1e-3);
  }
  ptrdiff_t num_elements = 2 * A.extent(0) * A.extent(1) + 2 * A.extent(0);
  state.SetBytesProcessed( R * num_elements * sizeof(value_type) * state.iterations());
  state.counters["repeats"] = repeats; 
  
  CUDA_SAFE_CALL(cudaDeviceSynchronize());
  CUDA_SAFE_CALL(cudaFree(s.data()));
}

BENCHMARK_CAPTURE(BM_MDSpan_CUDA_MatVec_Raw_Left, left, lmdspan<double,stdex::dynamic_extent,stdex::dynamic_extent>(), 100000, 5000);
BENCHMARK_MAIN();
