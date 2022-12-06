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
#include <vector>

#include <gtest/gtest.h>

namespace stdex = std::experimental;
_MDSPAN_INLINE_VARIABLE constexpr auto dyn = stdex::dynamic_extent;

TEST(TestSubmdspanLayoutRightStaticSizedRankReducing3Dto1D, test_submdspan_layout_right_static_sized_rank_reducing_3d_to_1d) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<size_t,2, 3, 4>> m(d.data());
  __MDSPAN_OP(m, 1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, 1, 1, stdex::full_extent);
  static_assert(decltype(sub0)::rank()==1,"unexpected submdspan rank");
  ASSERT_EQ(sub0.rank(),         1);
  ASSERT_EQ(sub0.rank_dynamic(), 0);
  ASSERT_EQ(sub0.extent(0),      4);
  ASSERT_EQ((__MDSPAN_OP(sub0, 1)), 42);
}

TEST(TestSubmdspanLayoutLeftStaticSizedRankReducing3Dto1D, test_submdspan_layout_left_static_sized_rank_reducing_3d_to_1d) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<size_t,2, 3, 4>, stdex::layout_left> m(d.data());
  __MDSPAN_OP(m, 1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, 1, 1, stdex::full_extent);
  ASSERT_EQ(sub0.rank(),         1);
  ASSERT_EQ(sub0.rank_dynamic(), 0);
  ASSERT_EQ(sub0.extent(0),      4);
  ASSERT_EQ((__MDSPAN_OP(sub0, 1)), 42);
}

TEST(TestSubmdspanLayoutRightStaticSizedRankReducingNested3Dto0D, test_submdspan_layout_right_static_sized_rank_reducing_nested_3d_to_0d) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<size_t,2, 3, 4>> m(d.data());
  __MDSPAN_OP(m, 1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, 1, stdex::full_extent, stdex::full_extent);
  ASSERT_EQ(sub0.rank(),         2);
  ASSERT_EQ(sub0.rank_dynamic(), 0);
  ASSERT_EQ(sub0.extent(0),      3);
  ASSERT_EQ(sub0.extent(1),      4);
  ASSERT_EQ((__MDSPAN_OP(sub0, 1, 1)), 42);
  auto sub1 = stdex::submdspan(sub0, 1, stdex::full_extent);
  ASSERT_EQ(sub1.rank(),         1);
  ASSERT_EQ(sub1.rank_dynamic(), 0);
  ASSERT_EQ(sub1.extent(0),      4);
  ASSERT_EQ((__MDSPAN_OP(sub1,1)),42);
  auto sub2 = stdex::submdspan(sub1, 1);
  ASSERT_EQ(sub2.rank(),         0);
  ASSERT_EQ(sub2.rank_dynamic(), 0);
  ASSERT_EQ((__MDSPAN_OP0(sub2)), 42);
}

TEST(TestSubmdspanLayoutRightStaticSizedPairs, test_submdspan_layout_right_static_sized_pairs) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<size_t,2, 3, 4>> m(d.data());
  __MDSPAN_OP(m, 1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, std::pair<int,int>{1, 2}, std::pair<int,int>{1, 3}, std::pair<int,int>{1, 4});
  ASSERT_EQ(sub0.rank(),         3);
  ASSERT_EQ(sub0.rank_dynamic(), 3);
  ASSERT_EQ(sub0.extent(0),      1);
  ASSERT_EQ(sub0.extent(1),      2);
  ASSERT_EQ(sub0.extent(2),      3);
  ASSERT_EQ((__MDSPAN_OP(sub0, 0, 0, 0)), 42);
}

TEST(TestSubmdspanLayoutRightStaticSizedTuples, test_submdspan_layout_right_static_sized_tuples) {
  std::vector<int> d(2 * 3 * 4, 0);
  stdex::mdspan<int, stdex::extents<size_t,2, 3, 4>> m(d.data());
  __MDSPAN_OP(m, 1, 1, 1) = 42;
  auto sub0 = stdex::submdspan(m, std::tuple<int,int>{1, 2}, std::tuple<int,int>{1, 3}, std::tuple<int,int>{1, 4});
  ASSERT_EQ(sub0.rank(),         3);
  ASSERT_EQ(sub0.rank_dynamic(), 3);
  ASSERT_EQ(sub0.extent(0),      1);
  ASSERT_EQ(sub0.extent(1),      2);
  ASSERT_EQ(sub0.extent(2),      3);
  ASSERT_EQ((__MDSPAN_OP(sub0, 0, 0, 0)),       42);
}


//template<class LayoutOrg, class LayoutSub, class ExtentsOrg, class ExtentsSub, class ... SubArgs>


using submdspan_test_types =
  ::testing::Types<
      // LayoutLeft to LayoutLeft
      std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,1>,stdex::dextents<size_t,1>, stdex::full_extent_t>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,1>,stdex::dextents<size_t,1>, std::pair<int,int>>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,1>,stdex::dextents<size_t,0>, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,2>,stdex::dextents<size_t,2>, stdex::full_extent_t, stdex::full_extent_t>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,2>,stdex::dextents<size_t,2>, stdex::full_extent_t, std::pair<int,int>>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,2>,stdex::dextents<size_t,1>, stdex::full_extent_t, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,3>,stdex::dextents<size_t,3>, stdex::full_extent_t, stdex::full_extent_t, std::pair<int,int>>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,3>,stdex::dextents<size_t,2>, stdex::full_extent_t, std::pair<int,int>, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,3>,stdex::dextents<size_t,1>, stdex::full_extent_t, int, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,3>,stdex::dextents<size_t,1>, std::pair<int,int>, int, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,6>,stdex::dextents<size_t,3>, stdex::full_extent_t, stdex::full_extent_t, std::pair<int,int>, int, int, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,6>,stdex::dextents<size_t,2>, stdex::full_extent_t, std::pair<int,int>, int, int, int, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,6>,stdex::dextents<size_t,1>, stdex::full_extent_t, int, int, int ,int, int>
    , std::tuple<stdex::layout_left, stdex::layout_left, stdex::dextents<size_t,6>,stdex::dextents<size_t,1>, std::pair<int,int>, int, int, int, int, int>
    // LayoutRight to LayoutRight
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,1>,stdex::dextents<size_t,1>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,1>,stdex::dextents<size_t,1>, std::pair<int,int>>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,1>,stdex::dextents<size_t,0>, int>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,2>,stdex::dextents<size_t,2>, stdex::full_extent_t, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,2>,stdex::dextents<size_t,2>, std::pair<int,int>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,2>,stdex::dextents<size_t,1>, int, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,3>,stdex::dextents<size_t,3>, std::pair<int,int>, stdex::full_extent_t, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,3>,stdex::dextents<size_t,2>, int, std::pair<int,int>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,3>,stdex::dextents<size_t,1>, int, int, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,6>,stdex::dextents<size_t,3>, int, int, int, std::pair<int,int>, stdex::full_extent_t, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,6>,stdex::dextents<size_t,2>, int, int, int, int, std::pair<int,int>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::dextents<size_t,6>,stdex::dextents<size_t,1>, int, int, int, int, int, stdex::full_extent_t>
    // LayoutRight to LayoutRight Check Extents Preservation
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1>,stdex::extents<size_t,1>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1>,stdex::extents<size_t,dyn>, std::pair<int,int>>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1>,stdex::extents<size_t>, int>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2>,stdex::extents<size_t,1,2>, stdex::full_extent_t, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2>,stdex::extents<size_t,dyn,2>, std::pair<int,int>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2>,stdex::extents<size_t,2>, int, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2,3>,stdex::extents<size_t,dyn,2,3>, std::pair<int,int>, stdex::full_extent_t, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2,3>,stdex::extents<size_t,dyn,3>, int, std::pair<int,int>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2,3>,stdex::extents<size_t,3>, int, int, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2,3,4,5,6>,stdex::extents<size_t,dyn,5,6>, int, int, int, std::pair<int,int>, stdex::full_extent_t, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2,3,4,5,6>,stdex::extents<size_t,dyn,6>, int, int, int, int, std::pair<int,int>, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_right, stdex::extents<size_t,1,2,3,4,5,6>,stdex::extents<size_t,6>, int, int, int, int, int, stdex::full_extent_t>

    , std::tuple<stdex::layout_right, stdex::layout_stride, stdex::extents<size_t,1,2,3,4,5,6>,stdex::extents<size_t,1,dyn,6>, stdex::full_extent_t, int, std::pair<int,int>, int, int, stdex::full_extent_t>
    , std::tuple<stdex::layout_right, stdex::layout_stride, stdex::extents<size_t,1,2,3,4,5,6>,stdex::extents<size_t,2,dyn,5>, int, stdex::full_extent_t, std::pair<int,int>, int, stdex::full_extent_t, int>
    >;

template<class T> struct TestSubMDSpan;

template<class LayoutOrg, class LayoutSub, class ExtentsOrg, class ExtentsSub, class ... SubArgs>
struct TestSubMDSpan<
  std::tuple<LayoutOrg,
             LayoutSub,
             ExtentsOrg,
             ExtentsSub,
             SubArgs...>>
  : public ::testing::Test {

  using mds_org_t = stdex::mdspan<int, ExtentsOrg, LayoutOrg>;
  using mds_sub_t = stdex::mdspan<int, ExtentsSub, LayoutSub>;
  using map_t = typename mds_org_t::mapping_type;

  using mds_sub_deduced_t = decltype(stdex::submdspan(mds_org_t(nullptr, map_t()), SubArgs()...));
  using sub_args_t = std::tuple<SubArgs...>;

};


TYPED_TEST_SUITE(TestSubMDSpan, submdspan_test_types);

TYPED_TEST(TestSubMDSpan, submdspan_return_type) {
  static_assert(std::is_same<typename TestFixture::mds_sub_t,
                             typename TestFixture::mds_sub_deduced_t>::value,
                "SubMDSpan: wrong return type");

}
