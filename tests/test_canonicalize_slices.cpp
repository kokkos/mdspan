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
#include <type_traits>

#include <gtest/gtest.h>

#if ! defined(MDSPAN_ENABLE_P3663)
#  error "This file requires MDSPAN_ENABLE_P3663=ON"
#endif

namespace {

constexpr bool slice_equal(Kokkos::full_extent_t, Kokkos::full_extent_t) {
  return true;
}

template<class Right>
constexpr bool slice_equal(Kokkos::full_extent_t, const Right&) {
  return std::is_convertible_v<Right, Kokkos::full_extent_t>;
}

template<class Left>
constexpr bool slice_equal(const Left&, Kokkos::full_extent_t) {
  return std::is_convertible_v<Left, Kokkos::full_extent_t>;  
}

template<class Left, class Right>
constexpr bool slice_equal(const Left&, const Right&) {
  static_assert(false, "slice_equal not implemented for this case");
  return false;
}

template<class ExpectedResult, class InputExtents, class... Slices>
void
test_canonicalize_slices(
  const ExpectedResult& expected_result,
  const InputExtents& input_extents,
  Slices... slices)
{
  auto result = Kokkos::submdspan_canonicalize_slices(input_extents, slices...);
  [&] <size_t... Indices> (std::index_sequence<Indices...>) {
    auto test_one = [&] <size_t Ind> (std::integral_constant<size_t, Ind>) {
      using std::get;     
      auto left = get<Ind>(result);
      auto right = get<Ind>(expected_result);
      const bool result = slice_equal(left, right);
      // Below isn't well-formed for some reason -- a compiler bug?
      //const bool result = slice_equal(get<Ind>(result), get<Ind>(expected_result));
      ASSERT_TRUE(result) << " failed for k=" << Ind;
    };
    (test_one(std::integral_constant<size_t, Indices>{}), ...);
  } (std::make_index_sequence<sizeof...(Slices)>());
}

TEST(CanonicalizeSlices, Rank0) {
  test_canonicalize_slices(std::tuple{}, Kokkos::extents<int>{}); 
  test_canonicalize_slices(std::tuple{}, Kokkos::extents<size_t>{});
}

TEST(CanonicalizeSlices, Rank1_full) {
  constexpr auto full = Kokkos::full_extent;
  constexpr auto expected_result = std::tuple{full};
  test_canonicalize_slices(expected_result, Kokkos::extents<int, 10>{}, full);
  test_canonicalize_slices(expected_result, Kokkos::extents<size_t, Kokkos::dynamic_extent>{}, full);
}

} // namespace (anonymous)
