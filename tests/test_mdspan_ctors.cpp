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
#include <mdspan/mdspan.hpp>
#include <vector>

#include <gtest/gtest.h>
#include "offload_utils.hpp"

_MDSPAN_INLINE_VARIABLE constexpr auto dyn = md::dynamic_extent;


void test_mdspan_ctor_default() {
  size_t* errors = allocate_array<size_t>(1);
  errors[0] = 0;

  dispatch([=] _MDSPAN_HOST_DEVICE () {
    md::mdspan<int, md::dextents<size_t,1>> m;
    __MDSPAN_DEVICE_ASSERT_EQ(m.data_handle(), nullptr);
    __MDSPAN_DEVICE_ASSERT_EQ(m.rank(), 1);
    __MDSPAN_DEVICE_ASSERT_EQ(m.rank_dynamic(), 1);
    __MDSPAN_DEVICE_ASSERT_EQ(m.extent(0), 0);
    __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(0), dyn);
    __MDSPAN_DEVICE_ASSERT_EQ(m.stride(0), 1);
    __MDSPAN_DEVICE_ASSERT_EQ(m.is_exhaustive(), true);
    __MDSPAN_DEVICE_ASSERT_EQ(m.size(), 0);
    __MDSPAN_DEVICE_ASSERT_EQ(m.empty(), true);
  });
  ASSERT_EQ(errors[0], 0);
  free_array(errors);
}

TEST(TestMdspanCtorDataCArray, test_mdspan_ctor_default) {
  __MDSPAN_TESTS_RUN_TEST(test_mdspan_ctor_default())
}

void test_mdspan_ctor_data_carray() {
  size_t* errors = allocate_array<size_t>(1);
  errors[0] = 0;

  dispatch([=] _MDSPAN_HOST_DEVICE () {
    int data[1] = {42};
    md::mdspan<int, md::extents<size_t,1>> m(data);
    __MDSPAN_DEVICE_ASSERT_EQ(m.data_handle(), data);
    __MDSPAN_DEVICE_ASSERT_EQ(m.rank(), 1);
    __MDSPAN_DEVICE_ASSERT_EQ(m.rank_dynamic(), 0);
    __MDSPAN_DEVICE_ASSERT_EQ(m.extent(0), 1);
    __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(0), 1);
    __MDSPAN_DEVICE_ASSERT_EQ(m.stride(0), 1);
    auto val = __MDSPAN_OP(m,0);
    __MDSPAN_DEVICE_ASSERT_EQ(val, 42);
    __MDSPAN_DEVICE_ASSERT_EQ(m.is_exhaustive(), true);
    __MDSPAN_DEVICE_ASSERT_EQ(m.size(), 1);
    __MDSPAN_DEVICE_ASSERT_EQ(m.empty(), false);
  });
  ASSERT_EQ(errors[0], 0);
  free_array(errors);
}

TEST(TestMdspanCtorDataCArray, test_mdspan_ctor_data_carray) {
  __MDSPAN_TESTS_RUN_TEST(test_mdspan_ctor_data_carray())
}

TEST(TestMdspanCtorDataStdArray, test_mdspan_ctor_data_carray) {
  std::array<int, 1> d = {42};
  md::mdspan<int, md::extents<size_t,1>> m(d.data());
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 1);
  ASSERT_EQ(m.rank_dynamic(), 0);
  ASSERT_EQ(m.extent(0), 1);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(__MDSPAN_OP(m, 0), 42);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCtorDataVector, test_mdspan_ctor_data_carray) {
  std::vector<int> d = {42};
  md::mdspan<int, md::extents<size_t,1>> m(d.data());
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 1);
  ASSERT_EQ(m.rank_dynamic(), 0);
  ASSERT_EQ(m.extent(0), 1);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(__MDSPAN_OP(m, 0), 42);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCtorExtentsStdArrayConvertibleToSizeT, test_mdspan_ctor_extents_std_array_convertible_to_size_t) {
  std::array<int, 4> d{42, 17, 71, 24};
  std::array<int, 2> e{2, 2};
  md::mdspan<int, md::dextents<size_t,2>> m(d.data(), e);
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 2);
  ASSERT_EQ(m.extent(1), 2);
  ASSERT_EQ(m.stride(0), 2);
  ASSERT_EQ(m.stride(1), 1);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanListInitializationLayoutLeft, test_mdspan_list_initialization_layout_left) {
  std::array<int, 1> d{42};
  md::mdspan<int, md::extents<size_t,dyn, dyn>, md::layout_left> m{d.data(), 16, 32};
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 16);
  ASSERT_EQ(m.extent(1), 32);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(m.stride(1), 16);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanListInitializationLayoutRight, test_mdspan_list_initialization_layout_right) {
  std::array<int, 1> d{42};
  md::mdspan<int, md::extents<size_t,dyn, dyn>, md::layout_right> m{d.data(), 16, 32};
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 16);
  ASSERT_EQ(m.extent(1), 32);
  ASSERT_EQ(m.stride(0), 32);
  ASSERT_EQ(m.stride(1), 1);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanListInitializationLayoutStride, test_mdspan_list_initialization_layout_stride) {
  std::array<int, 1> d{42};
  md::mdspan<int, md::extents<size_t,dyn, dyn>, md::layout_stride> m{d.data(), {md::dextents<size_t,2>{16, 32}, std::array<std::size_t, 2>{1, 128}}};
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 16);
  ASSERT_EQ(m.extent(1), 32);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(m.stride(1), 128);
  ASSERT_FALSE(m.is_exhaustive());
}

#if defined(_MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION)
TEST(TestMdspanCTAD, extents_pack) {
  std::array<int, 1> d{42};
  md::mdspan m(d.data(), 64, 128);
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 64);
  ASSERT_EQ(m.extent(1), 128);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, ctad_pointer) {
  std::array<int,5> d = {1,2,3,4,5};
  int* ptr = d.data();
  md::mdspan m(ptr);
  static_assert(std::is_same<decltype(m)::element_type,int>::value);
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 0);
  ASSERT_EQ(m.rank_dynamic(), 0);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, ctad_pointer_tmp) {
  std::array<int,5> d = {1,2,3,4,5};
  md::mdspan m(d.data());
  static_assert(std::is_same<decltype(m)::element_type,int>::value);
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 0);
  ASSERT_EQ(m.rank_dynamic(), 0);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, ctad_pointer_move) {
  std::array<int,5> d = {1,2,3,4,5};
  int* ptr = d.data();
  md::mdspan m(std::move(ptr));
  static_assert(std::is_same<decltype(m)::element_type,int>::value);
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 0);
  ASSERT_EQ(m.rank_dynamic(), 0);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, ctad_carray) {
  int data[5] = {1,2,3,4,5};
  md::mdspan m(data);
  static_assert(std::is_same<decltype(m)::element_type,int>::value);
  ASSERT_EQ(m.data_handle(), &data[0]);
  ASSERT_EQ(m.rank(), 1);
  ASSERT_EQ(m.rank_dynamic(), 0);
  ASSERT_EQ(m.static_extent(0), 5);
  ASSERT_EQ(m.extent(0), 5);
  ASSERT_EQ(__MDSPAN_OP(m, 2), 3);
  ASSERT_TRUE(m.is_exhaustive());


  md::mdspan m2(data, 3);
  static_assert(std::is_same<decltype(m2)::element_type,int>::value);
  ASSERT_EQ(m2.data_handle(), &data[0]);
  ASSERT_EQ(m2.rank(), 1);
  ASSERT_EQ(m2.rank_dynamic(), 1);
  ASSERT_EQ(m2.extent(0), 3);
  ASSERT_TRUE(m2.is_exhaustive());
  ASSERT_EQ(__MDSPAN_OP(m2, 2), 3);
}

TEST(TestMdspanCTAD, ctad_const_carray) {
  const int data[5] = {1,2,3,4,5};
  md::mdspan m(data);
  static_assert(std::is_same<typename decltype(m)::element_type,const int>::value);
  ASSERT_EQ(m.data_handle(), &data[0]);
  ASSERT_EQ(m.rank(), 1);
  ASSERT_EQ(m.rank_dynamic(), 0);
  ASSERT_EQ(m.static_extent(0), 5);
  ASSERT_EQ(m.extent(0), 5);
  ASSERT_EQ(__MDSPAN_OP(m, 2), 3);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, extents_object) {
  std::array<int, 1> d{42};
  md::mdspan m{d.data(), md::extents{64, 128}};
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 64);
  ASSERT_EQ(m.extent(1), 128);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, extents_object_move) {
  std::array<int, 1> d{42};
  md::mdspan m{d.data(), std::move(md::extents{64, 128})};
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 64);
  ASSERT_EQ(m.extent(1), 128);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, extents_std_array) {
  std::array<int, 1> d{42};
  md::mdspan m{d.data(), std::array{64, 128}};
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 64);
  ASSERT_EQ(m.extent(1), 128);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, cptr_extents_std_array) {
  std::array<int, 1> d{42};
  const int* const ptr= d.data();
  md::mdspan m{ptr, std::array{64, 128}};
  static_assert(std::is_same<typename decltype(m)::element_type, const int>::value);
  ASSERT_EQ(m.data_handle(), d.data());
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.extent(0), 64);
  ASSERT_EQ(m.extent(1), 128);
  ASSERT_TRUE(m.is_exhaustive());
}

TEST(TestMdspanCTAD, layout_left) {
  std::array<int, 1> d{42};

  md::mdspan m0{d.data(), md::layout_left::mapping{md::extents{16, 32}}};
  ASSERT_EQ(m0.data_handle(), d.data());
  ASSERT_EQ(m0.rank(), 2);
  ASSERT_EQ(m0.rank_dynamic(), 2);
  ASSERT_EQ(m0.extent(0), 16);
  ASSERT_EQ(m0.extent(1), 32);
  ASSERT_EQ(m0.stride(0), 1);
  ASSERT_EQ(m0.stride(1), 16);
  ASSERT_TRUE(m0.is_exhaustive());

// TODO: Perhaps one day I'll get this to work.
/*
  md::mdspan m1{d.data(), md::layout_left::mapping{{16, 32}}};
  ASSERT_EQ(m1.data(), d.data());
  ASSERT_EQ(m1.rank(), 2);
  ASSERT_EQ(m1.rank_dynamic(), 2);
  ASSERT_EQ(m1.extent(0), 16);
  ASSERT_EQ(m1.extent(1), 32);
  ASSERT_EQ(m1.stride(0), 1);
  ASSERT_EQ(m1.stride(1), 16);
  ASSERT_TRUE(m1.is_exhaustive());
*/
}

TEST(TestMdspanCTAD, layout_right) {
  std::array<int, 1> d{42};

  md::mdspan m0{d.data(), md::layout_right::mapping{md::extents{16, 32}}};
  ASSERT_EQ(m0.data_handle(), d.data());
  ASSERT_EQ(m0.rank(), 2);
  ASSERT_EQ(m0.rank_dynamic(), 2);
  ASSERT_EQ(m0.extent(0), 16);
  ASSERT_EQ(m0.extent(1), 32);
  ASSERT_EQ(m0.stride(0), 32);
  ASSERT_EQ(m0.stride(1), 1);
  ASSERT_TRUE(m0.is_exhaustive());

// TODO: Perhaps one day I'll get this to work.
/*
  md::mdspan m1{d.data(), md::layout_right::mapping{{16, 32}}};
  ASSERT_EQ(m1.data(), d.data());
  ASSERT_EQ(m1.rank(), 2);
  ASSERT_EQ(m1.rank_dynamic(), 2);
  ASSERT_EQ(m1.extent(0), 16);
  ASSERT_EQ(m1.extent(1), 32);
  ASSERT_EQ(m1.stride(0), 32);
  ASSERT_EQ(m1.stride(1), 1);
  ASSERT_TRUE(m1.is_exhaustive());
*/
}

TEST(TestMdspanCTAD, layout_stride) {
  std::array<int, 1> d{42};

  md::mdspan m0{d.data(), md::layout_stride::mapping{md::extents{16, 32}, std::array{1, 128}}};
  ASSERT_EQ(m0.data_handle(), d.data());
  ASSERT_EQ(m0.rank(), 2);
  ASSERT_EQ(m0.rank_dynamic(), 2);
  ASSERT_EQ(m0.extent(0), 16);
  ASSERT_EQ(m0.extent(1), 32);
  ASSERT_EQ(m0.stride(0), 1);
  ASSERT_EQ(m0.stride(1), 128);
  ASSERT_FALSE(m0.is_exhaustive());

  /*
  md::mdspan m1{d.data(), md::layout_stride::mapping{md::extents{16, 32}, md::extents{1, 128}}};
  ASSERT_EQ(m1.data(), d.data());
  ASSERT_EQ(m1.rank(), 2);
  ASSERT_EQ(m1.rank_dynamic(), 2);
  ASSERT_EQ(m1.extent(0), 16);
  ASSERT_EQ(m1.extent(1), 32);
  ASSERT_EQ(m1.stride(0), 1);
  ASSERT_EQ(m1.stride(1), 128);
  ASSERT_FALSE(m1.is_exhaustive());
  */

// TODO: Perhaps one day I'll get this to work.
/*
  md::mdspan m2{d.data(), md::layout_stride::mapping{{16, 32}, {1, 128}}};
  ASSERT_EQ(m2.data_handle(), d.data());
  ASSERT_EQ(m2.rank(), 2);
  ASSERT_EQ(m2.rank_dynamic(), 2);
  ASSERT_EQ(m2.extent(0), 16);
  ASSERT_EQ(m2.extent(1), 32);
  ASSERT_EQ(m2.stride(0), 1);
  ASSERT_EQ(m2.stride(1), 128);
  ASSERT_FALSE(m2.is_exhaustive());
*/
}


#endif
