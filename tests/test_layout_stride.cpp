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

#include <experimental/mdspan>

#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>

namespace stdex = std::experimental;
_MDSPAN_INLINE_VARIABLE constexpr auto dyn = stdex::dynamic_extent;

template <class> struct TestLayoutStride;
template <ptrdiff_t... Extents, ptrdiff_t... DynamicSizes, ptrdiff_t... StaticStrides, ptrdiff_t... DynamicStrides>
struct TestLayoutStride<std::tuple<
  stdex::extents<Extents...>,
  std::integer_sequence<ptrdiff_t, DynamicSizes...>,
  std::integer_sequence<ptrdiff_t, StaticStrides...>,
  std::integer_sequence<ptrdiff_t, DynamicStrides...>
>> : public ::testing::Test {
  using extents_type = stdex::extents<Extents...>;
  using mapping_type = typename stdex::layout_stride<StaticStrides...>::template mapping<extents_type>;
  mapping_type map = { extents_type{ DynamicSizes... }, std::array<ptrdiff_t, sizeof...(DynamicStrides)>{ DynamicStrides... } };
};

template <ptrdiff_t... Extents>
using _exts = stdex::extents<Extents...>;
template <ptrdiff_t... Vals>
using _ints = std::integer_sequence<ptrdiff_t, Vals...>;
template <class E, class DSz, class SStr, class DStr>
using layout_stride_case_t =
  std::tuple<E, DSz, SStr, DStr>;

using extents_345_t = stdex::extents<3, 4, 5>;
using extents_ddd_t = stdex::extents<dyn, dyn, dyn>;
using zero_stride_maps =
  ::testing::Types<
    layout_stride_case_t<extents_345_t, _ints<>, _ints<dyn, dyn, dyn>, _ints<0, 0, 0>>,
    layout_stride_case_t<extents_345_t, _ints<>, _ints<dyn, dyn, 0>, _ints<0, 0>>,
    layout_stride_case_t<extents_345_t, _ints<>, _ints<dyn, 0, dyn>, _ints<0, 0>>,
    layout_stride_case_t<extents_345_t, _ints<>, _ints<0, dyn, dyn>, _ints<0, 0>>,
    layout_stride_case_t<extents_345_t, _ints<>, _ints<dyn, 0, 0>, _ints<0>>,
    layout_stride_case_t<extents_345_t, _ints<>, _ints<0, dyn, 0>, _ints<0>>,
    layout_stride_case_t<extents_345_t, _ints<>, _ints<0, 0, dyn>, _ints<0>>,
    layout_stride_case_t<extents_345_t, _ints<>, _ints<0, 0, 0>, _ints<>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<dyn, dyn, dyn>, _ints<0, 0, 0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<dyn, dyn, 0>, _ints<0, 0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<dyn, 0, dyn>, _ints<0, 0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<0, dyn, dyn>, _ints<0, 0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<dyn, 0, 0>, _ints<0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<0, dyn, 0>, _ints<0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<0, 0, dyn>, _ints<0>>,
    layout_stride_case_t<extents_ddd_t, _ints<3, 4, 5>, _ints<0, 0, 0>, _ints<>>
  >;

template <class T>
struct TestLayoutStrideAllZero : TestLayoutStride<T> { };

TYPED_TEST_SUITE(TestLayoutStrideAllZero, zero_stride_maps);

TYPED_TEST(TestLayoutStrideAllZero, test_required_span_size) {
  ASSERT_EQ(this->map.required_span_size(), 1);
}

TYPED_TEST(TestLayoutStrideAllZero, test_mapping) {
  for(int i = 0; i < this->map.extents().extent(0); ++i) {
    for(int j = 0; j < this->map.extents().extent(1); ++j) {
      for (int k = 0; k < this->map.extents().extent(2); ++k) {
        ASSERT_EQ(this->map(i, j, k), 0);
      }
    }
  }
}
