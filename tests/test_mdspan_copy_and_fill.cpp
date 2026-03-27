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

#include <mdspan/mdarray.hpp>
#include <mdspan/mdspan.hpp>
#include <array>
#include <gtest/gtest.h>

template <class T, class Layout, class Extents>
constexpr auto make_mdarray(const Extents &exts) {
  Kokkos::Experimental::mdarray<T, Extents, Layout> mds{exts};
  for (size_t i = 0; i < mds.mapping().required_span_size(); ++i)
    mds.data()[i] = static_cast<T>(i);

  return mds;
}

template <class T, class Extents, std::size_t... Indices>
constexpr auto make_constexpr_array_impl(std::index_sequence<Indices...>) {
  constexpr auto sz = (Extents::static_extent(Indices) * ...);
  std::array<T, sz> ret;
  for (size_t i = 0; i < sz; ++i)
    ret[i] = static_cast<T>(i);

  return ret;
}

template <class Extents, std::size_t... Indices>
constexpr auto array_size_impl(std::index_sequence<Indices...>) {
  return (Extents::static_extent(Indices) * ...);
}


template <class Extents>
constexpr size_t array_size() {
  return array_size_impl<Extents>();
}


template <class T, class Extents>
constexpr auto make_constexpr_array() {
  return make_constexpr_array_impl<T, Extents>(std::make_index_sequence<Extents::rank()>{});
}

template <class T, class Extents, class Layout, class SrcExtents,
          class SrcLayout>
constexpr auto make_mdarray_copy(const Kokkos::mdspan<T, SrcExtents, SrcLayout> &src) {
  Kokkos::Experimental::mdarray<T, Extents, Layout> dst{};
  Kokkos::Experimental::copy(src, dst.to_mdspan());

  return dst;
}

template <class T, class SrcLayout, class DstLayout, class SrcExtents,
          class DstExtents>
constexpr bool test_mdspan_copy_check(const SrcExtents &src_exts,
                                      const DstExtents &dst_exts) {
  Kokkos::Experimental::mdarray<T, SrcExtents, SrcLayout> src1 =
      make_mdarray<T, SrcLayout>(src_exts);
  Kokkos::Experimental::mdarray<T, DstExtents, DstLayout> dst1{dst_exts};

  if (dst1.container() == src1.container()) return false;
  Kokkos::Experimental::copy(src1.to_mdspan(), dst1.to_mdspan());
  return dst1.container() == src1.container();
}

template <class T, class SrcLayout, class DstLayout, class SrcExtents,
          class DstExtents>
void test_mdspan_copy_impl(const SrcExtents &src_exts,
                           const DstExtents &dst_exts) {
  ASSERT_TRUE(
      (test_mdspan_copy_check<T, SrcLayout, DstLayout>(src_exts, dst_exts)));
}

template <class T, class SrcExtents, class SrcLayout, class DstExtents, class DstLayout>
constexpr bool test_mdspan_copy_constexpr_impl() {
  auto arr = make_constexpr_array<T, SrcExtents>();
  Kokkos::Experimental::mdarray<T, SrcExtents, SrcLayout, decltype(arr)> src1(SrcExtents{}, arr);
  Kokkos::Experimental::mdarray<T, DstExtents, DstLayout> dst1{};

  Kokkos::Experimental::copy(src1.to_mdspan(), dst1.to_mdspan());

  for ( std::size_t i = 0; i < arr.size(); ++i )
    if (dst1.container()[i] != src1.container()[i])
      return false;

  return true;
}

template <class T, class SrcExtents, class SrcLayout, class DstExtents, class DstLayout>
void test_mdspan_copy_constexpr() {
  static_assert(test_mdspan_copy_constexpr_impl<T, SrcExtents, SrcLayout, DstExtents, DstLayout>());
}

TEST(TestMdspanCopyAndFill, test_mdspan_copy) {
  test_mdspan_copy_impl<int, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::extents<size_t, 5, 3>{}, Kokkos::extents<size_t, 5, 3>{});
  test_mdspan_copy_impl<double, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::extents<size_t, 5, 3>{}, Kokkos::extents<size_t, 5, 3>{});
  test_mdspan_copy_impl<float, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::extents<size_t, 5, 3>{}, Kokkos::extents<size_t, 5, 3>{});

  test_mdspan_copy_impl<int, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::dextents<size_t, 2>{5, 3}, Kokkos::extents<size_t, 5, 3>{});
  test_mdspan_copy_impl<double, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::dextents<size_t, 2>{5, 3}, Kokkos::extents<size_t, 5, 3>{});
  test_mdspan_copy_impl<float, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::dextents<size_t, 2>{5, 3}, Kokkos::extents<size_t, 5, 3>{});

  test_mdspan_copy_impl<int, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::extents<size_t, 5, 3>{}, Kokkos::dextents<size_t, 2>{5, 3});
  test_mdspan_copy_impl<double, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::extents<size_t, 5, 3>{}, Kokkos::dextents<size_t, 2>{5, 3});
  test_mdspan_copy_impl<float, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::extents<size_t, 5, 3>{}, Kokkos::dextents<size_t, 2>{5, 3});

  test_mdspan_copy_impl<int, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::dextents<size_t, 2>{5, 3}, Kokkos::dextents<size_t, 2>{5, 3});
  test_mdspan_copy_impl<double, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::dextents<size_t, 2>{5, 3}, Kokkos::dextents<size_t, 2>{5, 3});
  test_mdspan_copy_impl<float, Kokkos::layout_left, Kokkos::layout_left>(
      Kokkos::dextents<size_t, 2>{5, 3}, Kokkos::dextents<size_t, 2>{5, 3});

  test_mdspan_copy_constexpr<int, Kokkos::extents<size_t, 5, 3>, Kokkos::layout_left,
                                  Kokkos::extents<size_t, 5, 3>, Kokkos::layout_left>();
}
