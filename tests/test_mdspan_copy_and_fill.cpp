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

#include <gtest/gtest.h>

template <class T, class SrcLayout, class DstLayout, class SrcExtents,
          class DstExtents>
void test_mdspan_copy_impl(const SrcExtents &src_exts,
                           const DstExtents &dst_exts) {
  Kokkos::Experimental::mdarray<T, SrcExtents, SrcLayout> src1{src_exts};
  Kokkos::Experimental::mdarray<T, DstExtents, DstLayout> dst1{dst_exts};
  auto &src1c = src1.container();
  for (size_t i = 0; i < src1c.size(); ++i)
    src1c[i] = static_cast<T>(i * i);

  ASSERT_NE(dst1.container(), src1.container());
  Kokkos::Experimental::copy(src1.to_mdspan(), dst1.to_mdspan());
  ASSERT_EQ(dst1.container(), src1.container());
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
}
