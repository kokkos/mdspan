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

namespace my_test {

template<class First, class Second>
struct my_aggregate_pair {
  First first;
  Second second;
};

// Not an aggregate, to force use of the tuple protocol.
template<class First, class Second>
class my_nonaggregate_pair {
public:
  constexpr my_nonaggregate_pair(First first, Second second)
    : first_(first), second_(second)
  {}

  template<std::size_t Index, class Self>
  constexpr decltype(auto) get(this Self&& self) {
    if constexpr (Index == 0) {
      return self.first_;
    }
    else if constexpr (Index == 1) {
      return self.second_;
    }
    else {
      static_assert(false, "Invalid index");
    }
  }

private:
  First first_;
  Second second_;
};

} // namespace my_test

template<class First, class Second>
struct std::tuple_size<my_test::my_nonaggregate_pair<First, Second>>
  : std::integral_constant<std::size_t, 2> {};

template<std::size_t Index, class First, class Second>
struct std::tuple_element<Index, my_test::my_nonaggregate_pair<First, Second>> {
  static_assert(false, "Invalid index");
};

template<class First, class Second>
struct std::tuple_element<0, my_test::my_nonaggregate_pair<First, Second>> {
  using type = First;
};

template<class First, class Second>
struct std::tuple_element<1, my_test::my_nonaggregate_pair<First, Second>> {
  using type = Second;
};

namespace {

template<class T>
constexpr bool slice_equal(const T& left, const T& right) {
  return left == right;
}

// full_extent_t lacks operator==
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

template<class OffsetType, class ExtentType, class StrideType>
constexpr bool slice_equal(
  const Kokkos::strided_slice<OffsetType, ExtentType, StrideType>& left,
  const Kokkos::strided_slice<OffsetType, ExtentType, StrideType>& right)
{
  return left.offset == right.offset && left.extent == right.extent && left.stride == right.stride;
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

TEST(CanonicalizeSlices, Rank1_integer_dynamic) {
  constexpr auto slice0 = int(7u);
  constexpr auto expected_slices = std::tuple{size_t(7u)};
  constexpr auto exts = Kokkos::extents<size_t, 10>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_integer_static) {
  constexpr auto slice0 = std::integral_constant<int, 7>{};
  constexpr auto expected_slices = std::tuple{std::cw<size_t(7u)>};
  constexpr auto exts = Kokkos::extents<size_t, 10>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_pair) {
  constexpr auto slice0 = std::pair{std::integral_constant<int, 7>{}, 11};
  constexpr auto expected_slices = std::tuple{Kokkos::strided_slice{
    .offset = std::cw<size_t(7u)>,
    .extent = size_t(4u), // 11 - 7
    .stride = std::cw<size_t(1u)>
  }};
  constexpr auto exts = Kokkos::extents<size_t, 13>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_aggregate_pair) {
  constexpr auto slice0 = my_test::my_aggregate_pair<int, int>{7, 11};
  constexpr auto expected_slices = std::tuple{Kokkos::strided_slice{
    .offset = size_t(7u),
    .extent = (size_t(11u) - size_t(7u)),
    .stride = std::cw<size_t(1u)>
  }};
  constexpr auto exts = Kokkos::extents<size_t, 13>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_nonaggregate_pair) {
  constexpr auto slice0 = my_test::my_nonaggregate_pair<int, int>(7, 11);
  constexpr auto expected_slices = std::tuple{Kokkos::strided_slice{
    .offset = size_t(7u),
    .extent = (size_t(11u) - size_t(7u)),
    .stride = std::cw<size_t(1u)>
  }};
  constexpr auto exts = Kokkos::extents<size_t, 13>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

} // namespace (anonymous)
