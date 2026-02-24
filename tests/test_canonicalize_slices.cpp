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
#include <utility>

#include <gtest/gtest.h>

namespace my_test {

// Aggregate pair type (supports structured binding natively as aggregate)
template<class First, class Second>
struct my_aggregate_pair {
  First first;
  Second second;
};

// Non-aggregate pair type (uses the tuple protocol)
template<class First, class Second>
class my_nonaggregate_pair {
public:
  constexpr my_nonaggregate_pair(First first, Second second)
    : first_(first), second_(second)
  {}

  template<std::size_t Index>
  constexpr auto get() -> std::conditional_t<Index == 0, First, Second> {
    if constexpr (Index == 0) {
      return first_;
    }
    else {
      static_assert(Index == 1);
      return second_;
    }
  }

  template<std::size_t Index>
  constexpr auto get() const -> std::conditional_t<Index == 0, First, Second> {
    if constexpr (Index == 0) {
      return first_;
    }
    else {
      static_assert(Index == 1);
      return second_;
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
  static_assert(Index == 0 || Index == 1, "Index out of range");
};

template<class First, class Second>
struct std::tuple_element<0, my_test::my_nonaggregate_pair<First, Second>> {
  using type = First;
};

template<class First, class Second>
struct std::tuple_element<1, my_test::my_nonaggregate_pair<First, Second>> {
  using type = Second;
};

template<std::size_t Index, class First, class Second>
constexpr auto get(my_test::my_nonaggregate_pair<First, Second>& p)
  -> std::conditional_t<Index == 0, First, Second>
{
  return p.template get<Index>();
}

template<std::size_t Index, class First, class Second>
constexpr auto get(const my_test::my_nonaggregate_pair<First, Second>& p)
  -> std::conditional_t<Index == 0, First, Second>
{
  return p.template get<Index>();
}

namespace {

// ============================================================
// Helpers for comparing slices
// ============================================================

// full_extent_t lacks operator==; two full_extent_t values are always equal
constexpr bool slice_equal(
  MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t,
  MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t)
{
  return true;
}

template<class O1, class E1, class S1, class O2, class E2, class S2>
constexpr bool slice_equal(
  const MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<O1, E1, S1>& left,
  const MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<O2, E2, S2>& right)
{
  return left.offset == right.offset &&
         left.extent == right.extent &&
         left.stride == right.stride;
}

// Integer (index) slices: compare by value
template<class T,
  std::enable_if_t<std::is_integral_v<T>, int> = 0>
constexpr bool slice_equal(T left, T right) {
  return left == right;
}

// Integral-constant-like slices: compare their values
template<class T, class U,
  std::enable_if_t<
    MDSPAN_IMPL_STANDARD_NAMESPACE::detail::is_integral_constant_like_v<T> &&
    MDSPAN_IMPL_STANDARD_NAMESPACE::detail::is_integral_constant_like_v<U>,
    int> = 0>
constexpr bool slice_equal(T, U) {
  return T::value == U::value;
}

// ============================================================
// Test helpers: compare the k-th element of result vs expected
// ============================================================

template<size_t Index, class Result, class ExpectedResult>
void test_canonicalize_slices_impl_one(
  std::integral_constant<size_t, Index>,
  const Result& result,
  const ExpectedResult& expected_result)
{
  // Use ADL to find the right get<>() for each tuple type
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::get;
  using std::get;
  auto left = get<Index>(result);
  auto right = get<Index>(expected_result);
  const bool outcome = slice_equal(left, right);
  ASSERT_TRUE(outcome) << " failed for k=" << Index;
}

template<size_t... Indices, class Result, class ExpectedResult>
void test_canonicalize_slices_impl(
  std::index_sequence<Indices...>,
  const Result& result,
  const ExpectedResult& expected_result)
{
  (test_canonicalize_slices_impl_one(
    std::integral_constant<size_t, Indices>{}, result, expected_result), ...);
}

template<class ExpectedResult, class InputExtents, class... Slices>
void test_canonicalize_slices(
  const ExpectedResult& expected_result,
  const InputExtents& input_extents,
  Slices... slices)
{
  auto result = MDSPAN_IMPL_STANDARD_NAMESPACE::submdspan_canonicalize_slices(
    input_extents, slices...);
  test_canonicalize_slices_impl(
    std::make_index_sequence<sizeof...(Slices)>(), result, expected_result);
}

// ============================================================
// Tests
// ============================================================

TEST(CanonicalizeSlices, Rank0) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;
  test_canonicalize_slices(tuple{}, MDSPAN_IMPL_STANDARD_NAMESPACE::extents<int>{});
  test_canonicalize_slices(tuple{}, MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t>{});
}

TEST(CanonicalizeSlices, Rank1_full) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;
  constexpr auto full = MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent;
  const auto expected_result = tuple{full};
  test_canonicalize_slices(expected_result,
    MDSPAN_IMPL_STANDARD_NAMESPACE::extents<int, 10>{}, full);
  test_canonicalize_slices(expected_result,
    MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t,
      MDSPAN_IMPL_STANDARD_NAMESPACE::dynamic_extent>{},
    full);
}

TEST(CanonicalizeSlices, Rank1_integer_dynamic) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;

  constexpr auto slice0 = int(7);
  constexpr auto expected_slices = tuple{size_t(7u)};
  constexpr auto exts = MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t, 10>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_integer_static) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;

  constexpr auto slice0 = std::integral_constant<int, 7>{};
  constexpr auto expected_slices = tuple{cw<size_t(7u)>};
  constexpr auto exts = MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t, 10>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_pair) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;

  // std::pair with static first element, dynamic second
  constexpr auto slice0 = std::pair{std::integral_constant<int, 7>{}, 11};

  constexpr auto offset = cw<size_t(7u)>;
  constexpr auto extent = size_t(4u); // 11 - 7
  constexpr auto stride = cw<size_t(1u)>;

  const auto expected_slices = tuple{
    MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<
      decltype(offset), decltype(extent), decltype(stride)
    >{offset, extent, stride}
  };
  constexpr auto exts = MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t, 13>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_aggregate_pair) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;

  constexpr auto slice0 = my_test::my_aggregate_pair<int, int>{7, 11};

  constexpr auto offset = size_t(7u);
  constexpr auto extent = size_t(4u); // 11 - 7
  constexpr auto stride = cw<size_t(1u)>;

  const auto expected_slices = tuple{
    MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<
      decltype(offset), decltype(extent), decltype(stride)
    >{offset, extent, stride}
  };
  constexpr auto exts = MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t, 13>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_nonaggregate_pair) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;

  auto slice0 = my_test::my_nonaggregate_pair<int, int>(7, 11);

  constexpr auto offset = size_t(7u);
  constexpr auto extent = size_t(4u); // 11 - 7
  constexpr auto stride = cw<size_t(1u)>;

  const auto expected_slices = tuple{
    MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<
      decltype(offset), decltype(extent), decltype(stride)
    >{offset, extent, stride}
  };
  constexpr auto exts = MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t, 13>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank2_full) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;
  constexpr auto full = MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent;
  const auto expected_result = tuple{full, full};
  test_canonicalize_slices(expected_result,
    MDSPAN_IMPL_STANDARD_NAMESPACE::extents<int, 11, 13>{}, full, full);
}

TEST(CanonicalizeSlices, Rank1_strided_slice_dynamic) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;

  // strided_slice with all dynamic values
  const auto slice0 = MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<int, int, int>{
    /* .offset = */ 1,
    /* .extent = */ 4,
    /* .stride = */ 2
  };

  const auto expected_slices = tuple{
    MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<size_t, size_t, size_t>{
      size_t(1), size_t(4), size_t(2)
    }
  };
  const auto exts = MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t, 10>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

TEST(CanonicalizeSlices, Rank1_strided_slice_static) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::tuple;

  using offset_t = std::integral_constant<int, 1>;
  using extent_t = std::integral_constant<int, 4>;
  using stride_t = std::integral_constant<int, 2>;
  const auto slice0 =
    MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<offset_t, extent_t, stride_t>{};

  const auto expected_slices = tuple{
    MDSPAN_IMPL_STANDARD_NAMESPACE::strided_slice<
      decltype(cw<size_t(1)>),
      decltype(cw<size_t(4)>),
      decltype(cw<size_t(2)>)
    >{cw<size_t(1)>, cw<size_t(4)>, cw<size_t(2)>}
  };
  const auto exts = MDSPAN_IMPL_STANDARD_NAMESPACE::extents<size_t, 10>{};
  test_canonicalize_slices(expected_slices, exts, slice0);
}

} // namespace (anonymous)
