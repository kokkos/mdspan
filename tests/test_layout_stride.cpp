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
#include <experimental/mdspan>

#include <gtest/gtest.h>

namespace stdex = std::experimental;
_MDSPAN_INLINE_VARIABLE constexpr auto dyn = stdex::dynamic_extent;

template <class> struct TestLayoutStride;
template <size_t... Extents, size_t... DynamicSizes, size_t... StaticStrides, size_t... DynamicStrides>
struct TestLayoutStride<std::tuple<
  stdex::extents<size_t,Extents...>,
  std::integer_sequence<size_t, DynamicSizes...>,
  std::integer_sequence<size_t, StaticStrides...>,
  std::integer_sequence<size_t, DynamicStrides...>
>> : public ::testing::Test {
  using extents_type = stdex::extents<size_t,Extents...>;
  using mapping_type = typename stdex::layout_stride::template mapping<extents_type>;
  mapping_type map = { extents_type{ DynamicSizes... }, std::array<size_t, sizeof...(DynamicStrides)>{ DynamicStrides... } };
};

template <size_t... Extents>
using _exts = stdex::extents<size_t,Extents...>;
template <size_t... Vals>
using _ints = std::integer_sequence<size_t, Vals...>;
template <class E, class DSz, class SStr, class DStr>
using layout_stride_case_t =
  std::tuple<E, DSz, SStr, DStr>;

using extents_345_t = stdex::extents<size_t,3, 4, 5>;
using extents_3dyn5_t = stdex::extents<size_t,3, dyn, 5>;
using extents_ddd_t = stdex::extents<size_t,dyn, dyn, dyn>;
using zero_stride_maps =
  ::testing::Types<
    layout_stride_case_t<extents_345_t, _ints<>, _ints<dyn, dyn, dyn>, _ints<0, 0, 0>>,
    layout_stride_case_t<extents_3dyn5_t, _ints<4>, _ints<dyn, dyn, dyn>, _ints<0, 0, 0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<dyn, dyn, dyn>, _ints<0, 0, 0>>
  >;

template <class T>
struct TestLayoutStrideAllZero : TestLayoutStride<T> { };

TYPED_TEST_SUITE(TestLayoutStrideAllZero, zero_stride_maps);

TYPED_TEST(TestLayoutStrideAllZero, test_required_span_size) {
  ASSERT_EQ(this->map.required_span_size(), 1);
}

TYPED_TEST(TestLayoutStrideAllZero, test_mapping) {
  using index_type = decltype(this->map.extents().extent(0));
  for(index_type i = 0; i < this->map.extents().extent(0); ++i) {
    for(index_type j = 0; j < this->map.extents().extent(1); ++j) {
      for (index_type k = 0; k < this->map.extents().extent(2); ++k) {
        ASSERT_EQ(this->map(i, j, k), 0);
      }
    }
  }
}

#ifdef __cpp_lib_span
TEST(TestLayoutStrideSpanConstruction, test_from_span_construction) {
  using map_t = stdex::layout_stride::mapping<stdex::extents<size_t,dyn, dyn>>;
  std::array<int,2> strides{1,128};
  map_t m1(stdex::dextents<size_t,2>{16, 32}, std::span<int,2>{strides.data(),2});
  // The following is actually not supported by layout_stride in the standard?
  //map_t m2(stdex::dextents<size_t,2>{16, 32}, std::span<int,std::dynamic_extent>{strides.data(),2});
  //ASSERT_EQ(m1, m2);
  ASSERT_EQ(m1.extents().rank(), 2);
  ASSERT_EQ(m1.extents().rank_dynamic(), 2);
  ASSERT_EQ(m1.extents().extent(0), 16);
  ASSERT_EQ(m1.extents().extent(1), 32);
  ASSERT_EQ(m1.stride(0), 1);
  ASSERT_EQ(m1.stride(1), 128);
  ASSERT_EQ(m1.strides()[0], 1);
  ASSERT_EQ(m1.strides()[1], 128);
  ASSERT_FALSE(m1.is_exhaustive());
}
#endif

TEST(TestLayoutStrideListInitialization, test_list_initialization) {
  stdex::layout_stride::mapping<stdex::extents<size_t,dyn, dyn>> m{stdex::dextents<size_t,2>{16, 32}, std::array<int,2>{1, 128}};
  ASSERT_EQ(m.extents().rank(), 2);
  ASSERT_EQ(m.extents().rank_dynamic(), 2);
  ASSERT_EQ(m.extents().extent(0), 16);
  ASSERT_EQ(m.extents().extent(1), 32);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(m.stride(1), 128);
  ASSERT_EQ(m.strides()[0], 1);
  ASSERT_EQ(m.strides()[1], 128);
  ASSERT_FALSE(m.is_exhaustive());
}

// This fails on GCC 9.2 and others
#if defined(_MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION)
TEST(TestLayoutStrideCTAD, test_ctad) {
  // This is not possible wiht the array constructor we actually provide
  /*
  stdex::layout_stride::mapping m0{stdex::extents{16, 32}, stdex::extents{1, 128}};
  ASSERT_EQ(m0.extents().rank(), 2);
  ASSERT_EQ(m0.extents().rank_dynamic(), 2);
  ASSERT_EQ(m0.extents().extent(0), 16);
  ASSERT_EQ(m0.extents().extent(1), 32);
  ASSERT_EQ(m0.stride(0), 1);
  ASSERT_EQ(m0.stride(1), 128);
  ASSERT_EQ(m0.strides(), (std::array<std::size_t, 2>{1, 128}));
  ASSERT_FALSE(m0.is_exhaustive());
  */

  stdex::layout_stride::mapping m1{stdex::extents{16, 32}, std::array{1, 128}};
  ASSERT_EQ(m1.extents().rank(), 2);
  ASSERT_EQ(m1.extents().rank_dynamic(), 2);
  ASSERT_EQ(m1.extents().extent(0), 16);
  ASSERT_EQ(m1.extents().extent(1), 32);
  ASSERT_EQ(m1.stride(0), 1);
  ASSERT_EQ(m1.stride(1), 128);
  ASSERT_EQ(m1.strides()[0], 1);
  ASSERT_EQ(m1.strides()[1], 128);
  ASSERT_FALSE(m1.is_exhaustive());

// TODO These won't work with our current implementation, because the array will
// be deduced as the extent type, leading to a `static_assert`. We can probably
// get around this with a clever refactoring, or by using an alias template for
// `mapping` and deduction guides.
/*
  stdex::layout_stride::mapping m2{std::array{16, 32}, stdex::extents{1, 128}};
  ASSERT_EQ(m2.extents().rank(), 2);
  ASSERT_EQ(m2.extents().rank_dynamic(), 2);
  ASSERT_EQ(m2.extents().extent(0), 16);
  ASSERT_EQ(m2.extents().extent(1), 32);
  ASSERT_EQ(m2.stride(0), 1);
  ASSERT_EQ(m2.stride(1), 128);
  ASSERT_FALSE(m2.is_exhaustive());

  stdex::layout_stride::mapping m3{std::array{16, 32}, std::array{1, 128}};
  ASSERT_EQ(m3.extents().rank(), 2);
  ASSERT_EQ(m3.extents().rank_dynamic(), 2);
  ASSERT_EQ(m3.extents().extent(0), 16);
  ASSERT_EQ(m3.extents().extent(1), 32);
  ASSERT_EQ(m3.stride(0), 1);
  ASSERT_EQ(m3.stride(1), 128);
  ASSERT_FALSE(m3.is_exhaustive());
*/
}
#endif

