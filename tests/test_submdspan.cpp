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
#include <vector>

#include <gtest/gtest.h>

namespace stdex = std::experimental;
_MDSPAN_INLINE_VARIABLE constexpr auto dyn = stdex::dynamic_extent;

TEST(TestSubmdspanLayoutRightStaticSizedRankReducing3Dto1D, test_submdspan_layout_right_static_sized_rank_reducing_3d_to_1d) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<2, 3, 4>> m(d.data());
  m(1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, 1, 1, stdex::full_extent);
  ASSERT_EQ(sub0.rank(),         1);
  ASSERT_EQ(sub0.rank_dynamic(), 0);
  ASSERT_EQ(sub0.extent(0),      4);
  ASSERT_EQ(sub0(1),             42);
}

TEST(TestSubmdspanLayoutLeftStaticSizedRankReducing3Dto1D, test_submdspan_layout_left_static_sized_rank_reducing_3d_to_1d) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<2, 3, 4>, stdex::layout_left> m(d.data());
  m(1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, 1, 1, stdex::full_extent);
  ASSERT_EQ(sub0.rank(),         1);
  ASSERT_EQ(sub0.rank_dynamic(), 0);
  ASSERT_EQ(sub0.extent(0),      4);
  ASSERT_EQ(sub0(1),             42);
}

TEST(TestSubmdspanLayoutRightStaticSizedRankReducingNested3Dto0D, test_submdspan_layout_right_static_sized_rank_reducing_nested_3d_to_0d) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<2, 3, 4>> m(d.data());
  m(1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, 1, stdex::full_extent, stdex::full_extent);
  ASSERT_EQ(sub0.rank(),         2);
  ASSERT_EQ(sub0.rank_dynamic(), 0);
  ASSERT_EQ(sub0.extent(0),      3);
  ASSERT_EQ(sub0.extent(1),      4);
  ASSERT_EQ(sub0(1, 1),          42);
  auto sub1 = stdex::submdspan(sub0, 1, stdex::full_extent);
  ASSERT_EQ(sub1.rank(),         1);
  ASSERT_EQ(sub1.rank_dynamic(), 0);
  ASSERT_EQ(sub1.extent(0),      4);
  ASSERT_EQ(sub1(1),             42);
  auto sub2 = stdex::submdspan(sub1, 1);
  ASSERT_EQ(sub2.rank(),         0);
  ASSERT_EQ(sub2.rank_dynamic(), 0);
  ASSERT_EQ(sub2(),              42);
}

TEST(TestSubmdspanLayoutRightStaticSizedPairs, test_submdspan_layout_right_static_sized_pairs) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<2, 3, 4>> m(d.data());
  m(1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, std::pair<int,int>{1, 2}, std::pair<int,int>{1, 3}, std::pair<int,int>{1, 4});
  ASSERT_EQ(sub0.rank(),         3);
  ASSERT_EQ(sub0.rank_dynamic(), 3);
  ASSERT_EQ(sub0.extent(0),      1);
  ASSERT_EQ(sub0.extent(1),      2);
  ASSERT_EQ(sub0.extent(2),      3);
  ASSERT_EQ(sub0(0, 0, 0),       42);
}

// TODO @proposal-bug We currently don't allow this, but we should.
/*
TEST(TestSubmdspanLayoutRightStaticSizedTuples, test_submdspan_layout_right_static_sized_tuples) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<double, stdex::extents<2, 3, 4>> m(d.data());
  m(1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, std::tuple{1, 2}, std::tuple{1, 3}, std::tuple{1, 4});
  ASSERT_EQ(sub0.rank(),         3);
  ASSERT_EQ(sub0.rank_dynamic(), 3);
  ASSERT_EQ(sub0.extent(0),      1);
  ASSERT_EQ(sub0.extent(0),      2);
  ASSERT_EQ(sub0.extent(1),      3);
  ASSERT_EQ(sub0(0, 0, 0),       42);
}
*/

