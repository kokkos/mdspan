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
#include <cstdint>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

namespace {

template<size_t k, class Slice, class IndexType, size_t ... Exts>
void test_check_static_bounds(
  Kokkos::extents<IndexType, Exts...> extents,
  Kokkos::detail::check_static_bounds_result expected_result)
{
  using Kokkos::detail::check_static_bounds;
  using Kokkos::detail::check_static_bounds_result;

  auto result = check_static_bounds<k, Slice>(extents);
  static_assert(std::is_same_v<decltype(result), check_static_bounds_result>);
  EXPECT_EQ(result, expected_result);
}

template<class IndexType, size_t ... Exts>
void test_full_extent(
  Kokkos::extents<IndexType, Exts...> extents)
{
  [&] <size_t ... Inds> (std::index_sequence<Inds...>) {
    using Kokkos::detail::check_static_bounds_result;

    (test_check_static_bounds<Inds, Kokkos::full_extent_t>(extents, check_static_bounds_result::in_bounds), ...);
  } (std::make_index_sequence<sizeof...(Exts)>());
}

template<int Value>
using IC = std::integral_constant<int, Value>;

TEST(Submdspan, CheckStaticBounds) {
  using Kokkos::detail::check_static_bounds;
  using Kokkos::detail::check_static_bounds_result;

  {
    auto exts = Kokkos::extents<int, 5, 7, 11>{5, 7, 11};
    test_full_extent(exts);

    test_check_static_bounds<0, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<1, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<2, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);

    test_check_static_bounds<0, IC<13>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<1, IC<13>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<2, IC<13>>(exts, check_static_bounds_result::out_of_bounds);

    test_check_static_bounds<0, IC<3>>(exts, check_static_bounds_result::in_bounds);
    test_check_static_bounds<1, IC<3>>(exts, check_static_bounds_result::in_bounds);
    test_check_static_bounds<2, IC<3>>(exts, check_static_bounds_result::in_bounds);

    test_check_static_bounds<0, IC<6>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<1, IC<6>>(exts, check_static_bounds_result::in_bounds);
    test_check_static_bounds<2, IC<6>>(exts, check_static_bounds_result::in_bounds);

    test_check_static_bounds<0, int>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<1, int>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, int>(exts, check_static_bounds_result::unknown);
  }
  {
    auto exts = Kokkos::dims<3>{5, 7, 11};
    test_full_extent(exts);

    test_check_static_bounds<0, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<1, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<2, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);

    test_check_static_bounds<0, IC<13>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<1, IC<13>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, IC<13>>(exts, check_static_bounds_result::unknown);

    test_check_static_bounds<0, IC<3>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<1, IC<3>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, IC<3>>(exts, check_static_bounds_result::unknown);

    test_check_static_bounds<0, IC<6>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<1, IC<6>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, IC<6>>(exts, check_static_bounds_result::unknown);

    test_check_static_bounds<0, int>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<1, int>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, int>(exts, check_static_bounds_result::unknown);
  }
  {
    auto exts = Kokkos::extents<int, 5, Kokkos::dynamic_extent, 11>{5, 7, 11};
    test_full_extent(exts);

    test_check_static_bounds<0, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<1, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<2, IC<-1>>(exts, check_static_bounds_result::out_of_bounds);

    test_check_static_bounds<0, IC<13>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<1, IC<13>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, IC<13>>(exts, check_static_bounds_result::out_of_bounds);

    test_check_static_bounds<0, IC<3>>(exts, check_static_bounds_result::in_bounds);
    test_check_static_bounds<1, IC<3>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, IC<3>>(exts, check_static_bounds_result::in_bounds);

    test_check_static_bounds<0, IC<6>>(exts, check_static_bounds_result::out_of_bounds);
    test_check_static_bounds<1, IC<6>>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, IC<6>>(exts, check_static_bounds_result::in_bounds);

    test_check_static_bounds<0, int>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<1, int>(exts, check_static_bounds_result::unknown);
    test_check_static_bounds<2, int>(exts, check_static_bounds_result::unknown);
  }
}

} // namespace (anonymous)
