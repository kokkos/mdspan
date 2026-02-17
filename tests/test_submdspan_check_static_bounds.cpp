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
#include <array>
#include <cstdint>
#include <tuple>
#include <type_traits>
#include <utility>
#include <version>
#include <gtest/gtest.h>

#if defined(__cpp_lib_source_location)
#  include <source_location>
#endif

namespace adl_get_trait_detail {
  template<size_t k, class T>
  constexpr auto get(T) = delete;

  template <class T, class PairLike, class = void>
  struct has_get_like_pair_0 : std::bool_constant<false> {};

  template <class T, class PairLike>
  struct has_get_like_pair_0<T, PairLike, std::void_t<decltype(get<0>(std::declval<T>()))>>
    : std::bool_constant<
      std::is_convertible_v<
        decltype(get<0>(std::declval<T>())),
        typename PairLike::first_type
      >
    >
  {};

  template <class T, class PairLike, class = void>
  struct has_get_like_pair_1 : std::false_type {};

  template <class T, class PairLike>
  struct has_get_like_pair_1<T, PairLike, std::void_t<decltype(get<1>(std::declval<T>()))>>
    : std::bool_constant<
      std::is_convertible_v<
        decltype(get<1>(std::declval<T>())),
        typename PairLike::second_type
      >
    >
  {};
} // namespace adl_get_trait_detail

namespace test {

#if defined(MDSPAN_IMPL_USE_CONCEPTS) && MDSPAN_HAS_CXX_20
template<class T, class PairLike>
concept has_get_like_pair = requires(T t) {
  { get<0>(t) } -> std::convertible_to<typename PairLike::first_type>;
  { get<1>(t) } -> std::convertible_to<typename PairLike::second_type>;
};
#else

template <class T, class PairLike>
constexpr bool has_get_like_pair =
  adl_get_trait_detail::has_get_like_pair_0<T, PairLike>::value &&
  adl_get_trait_detail::has_get_like_pair_1<T, PairLike>::value;

#endif // defined(MDSPAN_IMPL_USE_CONCEPTS) && MDSPAN_HAS_CXX_20

struct foo {};
struct bar {};

static_assert(has_get_like_pair<std::array<foo, 2>, std::pair<foo, foo>>);
static_assert(has_get_like_pair<std::pair<foo, bar>, std::pair<foo, bar>>);
static_assert(has_get_like_pair<std::tuple<foo, bar>, std::pair<foo, bar>>);

// Not an aggregate type, but opts into structured binding
// through the tuple protocol.  Has more than two members,
// so without the tuple protocol, it could never be a valid
// candidate for structured binding into two members.
template<class First, class Second>
class non_aggregate_pair {
public:
  constexpr non_aggregate_pair(First first, Second second)
    : first(first), second(second)
  {}

  template<size_t k>
  friend constexpr auto get(const non_aggregate_pair& p) {
    static_assert(k <= 1, "k must be 0 or 1");
    if constexpr (k == 0) {
      return p.first;
    }
    else {
      return p.second;
    }
  }

  constexpr foo get_foo() const { return foo_; }
  constexpr bar get_bar() const { return bar_; }

private:
  First first;
  foo foo_{};
  Second second;
  bar bar_{};
};

static_assert(! std::is_default_constructible_v<non_aggregate_pair<int, int>>);
static_assert(test::has_get_like_pair<non_aggregate_pair<int, int>, std::pair<int, int>>);
static_assert(! std::is_convertible_v<non_aggregate_pair<test::foo, test::bar>, std::pair<test::foo, test::bar>>);
static_assert(! std::is_convertible_v<non_aggregate_pair<test::foo, test::bar>, std::tuple<test::foo, test::bar>>);

} // namespace test

template<class First, class Second>
struct std::tuple_size<test::non_aggregate_pair<First, Second>> :
  std::integral_constant<size_t, 2> {};

template<class First, class Second>
struct std::tuple_element<0, test::non_aggregate_pair<First, Second>> {
  using type = First;
};

template<class First, class Second>
struct std::tuple_element<1, test::non_aggregate_pair<First, Second>> {
  using type = Second;
};

namespace {

struct convertible_to_full_extent_t {
  constexpr operator Kokkos::full_extent_t() const {
    return Kokkos::full_extent;
  }
};
static_assert(std::is_convertible_v<convertible_to_full_extent_t, Kokkos::full_extent_t>);

// Aggregate type with two members.
// It's not convertible to pair or tuple,
// and neither get<0> nor get<1> work on it.
template<class First, class Second>
struct aggregate_pair {
  First first;
  Second second;
};
static_assert(! std::is_convertible_v<aggregate_pair<test::foo, test::bar>, std::pair<test::foo, test::bar>>);
static_assert(! std::is_convertible_v<aggregate_pair<test::foo, test::bar>, std::tuple<test::foo, test::bar>>);
static_assert(! test::has_get_like_pair<aggregate_pair<test::foo, test::bar>, std::pair<test::foo, test::bar>>);

// Clang 14 is bad at CTAD for aggregates.
template<class First, class Second>
constexpr aggregate_pair<First, Second>
make_aggregate_pair(const First& first, const Second& second) {
  return aggregate_pair<First, Second>{first, second};
}

template<size_t k, class Slice, class IndexType, size_t ... Exts>
void test_check_static_bounds(
  Kokkos::extents<IndexType, Exts...> extents,
  Kokkos::detail::check_static_bounds_result expected_result,
#if defined(__cpp_lib_source_location)
  const std::source_location location = std::source_location::current()
#else
  const int line = __LINE__
#endif
  )
{
  using Kokkos::detail::check_static_bounds;
  using Kokkos::detail::check_static_bounds_result;

  auto result = check_static_bounds<k, Slice>(extents);
  static_assert(std::is_same_v<decltype(result), check_static_bounds_result>);
  EXPECT_EQ(result, expected_result) << "on line " <<
#if defined(__cpp_lib_source_location)
    location.line()
#else
    line
#endif
  ;
}

template<size_t... Indices, class Extents>
void test_full_extent_impl_0(
  std::index_sequence<Indices...>,
  const Extents& extents)
{
  using Kokkos::detail::check_static_bounds_result;
  (test_check_static_bounds<Indices, Kokkos::full_extent_t>(extents, check_static_bounds_result::in_bounds), ...);
}

template<size_t... Indices, class Extents>
void test_full_extent_impl_1(
  std::index_sequence<Indices...>,
  const Extents& extents)
{
  using Kokkos::detail::check_static_bounds_result;
  (test_check_static_bounds<Indices, convertible_to_full_extent_t>(extents, check_static_bounds_result::in_bounds), ...);
}

template<class IndexType, size_t ... Exts>
void test_full_extent(
  Kokkos::extents<IndexType, Exts...> extents)
{
  test_full_extent_impl_0(std::make_index_sequence<sizeof...(Exts)>(), extents);
  test_full_extent_impl_1(std::make_index_sequence<sizeof...(Exts)>(), extents);
}

template<int Value>
using IC = std::integral_constant<int, Value>;

TEST(Submdspan, CheckStaticBounds) {
  using Kokkos::detail::check_static_bounds;
  using Kokkos::detail::check_static_bounds_result;
  using Kokkos::strided_slice;
  constexpr auto OOB = check_static_bounds_result::out_of_bounds;
  constexpr auto INB = check_static_bounds_result::in_bounds;
  constexpr auto UNK = check_static_bounds_result::unknown;

  {
    auto exts = Kokkos::extents<int, 5, 7, 11>{5, 7, 11};
    test_full_extent(exts);

    test_check_static_bounds<0, IC<-1>>(exts, OOB);
    test_check_static_bounds<1, IC<-1>>(exts, OOB);
    test_check_static_bounds<2, IC<-1>>(exts, OOB);

    test_check_static_bounds<0, IC<13>>(exts, OOB);
    test_check_static_bounds<1, IC<13>>(exts, OOB);
    test_check_static_bounds<2, IC<13>>(exts, OOB);

    test_check_static_bounds<0, IC<3>>(exts, INB);
    test_check_static_bounds<1, IC<3>>(exts, INB);
    test_check_static_bounds<2, IC<3>>(exts, INB);

    test_check_static_bounds<0, IC<6>>(exts, OOB);
    test_check_static_bounds<1, IC<6>>(exts, INB);
    test_check_static_bounds<2, IC<6>>(exts, INB);

    test_check_static_bounds<0, int>(exts, UNK);
    test_check_static_bounds<1, int>(exts, UNK);
    test_check_static_bounds<2, int>(exts, UNK);

    test_check_static_bounds<0, unsigned short>(exts, UNK);
    test_check_static_bounds<1, unsigned short>(exts, UNK);
    test_check_static_bounds<2, unsigned short>(exts, UNK);

    // 14.3.1.1
    {
      using offset_type = IC<-1>;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using offset_type = IC<-1>;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.2
    {
      using offset_type = IC<13>;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }  
    {
      using offset_type = IC<13>;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.3
    {
      using offset_type = IC<1>;
      using extent_type = IC<-2>;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }  
    {
      using offset_type = IC<1>;
      using extent_type = IC<-2>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.4
    {
      using offset_type = IC<4>; // in bounds
      using extent_type = IC<8>; // out of bounds
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using offset_type = IC<4>; // in bounds
      using extent_type = IC<8>; // out of bounds
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }  
    // 14.3.1.5
    {
      using offset_type = IC<1>; // in bounds
      using extent_type = IC<2>; // in bounds
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, INB);
      test_check_static_bounds<1, slice_type>(exts, INB);
      test_check_static_bounds<2, slice_type>(exts, INB);
    }
    {
      using offset_type = IC<1>; // in bounds
      using extent_type = IC<2>; // in bounds
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, INB);
      test_check_static_bounds<1, slice_type>(exts, INB);
      test_check_static_bounds<2, slice_type>(exts, INB);
    }
    // 14.3.1.6
    {
      using offset_type = int;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using offset_type = int;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }

    // General 14.4 (just to show well-formedness
    // for a variety of types that smell like pair)
    {
      using slice_type = decltype(test::non_aggregate_pair{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(std::pair{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(std::tuple{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }

    // 14.4.1.1
    {
      using slice_type = decltype(make_aggregate_pair(IC<-1>{}, IC<0>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using slice_type = decltype(make_aggregate_pair(IC<-1>{}, int{0}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.2
    {
      using slice_type = decltype(make_aggregate_pair(IC<13>{}, IC<0>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using slice_type = decltype(make_aggregate_pair(IC<13>{}, int{0}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.3
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, IC<0>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.4
    {
      using slice_type = decltype(make_aggregate_pair(IC<0>{}, IC<13>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.5
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, IC<3>{}));
      test_check_static_bounds<0, slice_type>(exts, INB);
      test_check_static_bounds<1, slice_type>(exts, INB);
      test_check_static_bounds<2, slice_type>(exts, INB);
    }
    // 14.4.1.6
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, int{3}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.4.2
    {
      using slice_type = decltype(make_aggregate_pair(int{1}, IC<3>{}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(make_aggregate_pair(int{1}, int{3}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
  }
  {
    auto exts = Kokkos::dims<3>{5, 7, 11};
    test_full_extent(exts);

    test_check_static_bounds<0, IC<-1>>(exts, OOB);
    test_check_static_bounds<1, IC<-1>>(exts, OOB);
    test_check_static_bounds<2, IC<-1>>(exts, OOB);

    test_check_static_bounds<0, IC<13>>(exts, UNK);
    test_check_static_bounds<1, IC<13>>(exts, UNK);
    test_check_static_bounds<2, IC<13>>(exts, UNK);

    test_check_static_bounds<0, IC<3>>(exts, UNK);
    test_check_static_bounds<1, IC<3>>(exts, UNK);
    test_check_static_bounds<2, IC<3>>(exts, UNK);

    test_check_static_bounds<0, IC<6>>(exts, UNK);
    test_check_static_bounds<1, IC<6>>(exts, UNK);
    test_check_static_bounds<2, IC<6>>(exts, UNK);

    test_check_static_bounds<0, int>(exts, UNK);
    test_check_static_bounds<1, int>(exts, UNK);
    test_check_static_bounds<2, int>(exts, UNK);

    test_check_static_bounds<0, unsigned short>(exts, UNK);
    test_check_static_bounds<1, unsigned short>(exts, UNK);
    test_check_static_bounds<2, unsigned short>(exts, UNK);

    // 14.3.1.1
    {
      using offset_type = IC<-1>;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using offset_type = IC<-1>;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.2
    {
      using offset_type = IC<13>;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }  
    {
      using offset_type = IC<13>;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.3.1.3
    {
      using offset_type = IC<1>;
      using extent_type = IC<-2>;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }  
    {
      using offset_type = IC<1>;
      using extent_type = IC<-2>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.4
    {
      using offset_type = IC<4>; // in bounds
      using extent_type = IC<8>; // out of bounds
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using offset_type = IC<4>; // in bounds
      using extent_type = IC<8>; // out of bounds
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }  
    // 14.3.1.5
    {
      using offset_type = IC<1>; // in bounds
      using extent_type = IC<2>; // in bounds
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using offset_type = IC<1>; // in bounds
      using extent_type = IC<2>; // in bounds
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.3.1.6
    {
      using offset_type = int;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using offset_type = int;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }

    // General 14.4 (just to show well-formedness
    // for a variety of types that smell like pair)
    {
      using slice_type = decltype(test::non_aggregate_pair{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(std::pair{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(std::tuple{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }

    // 14.4.1.1
    {
      using slice_type = decltype(make_aggregate_pair(IC<-1>{}, IC<0>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using slice_type = decltype(make_aggregate_pair(IC<-1>{}, int{0}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.2 (actually 14.4.1.6)
    {
      using slice_type = decltype(make_aggregate_pair(IC<13>{}, IC<14>{}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(make_aggregate_pair(IC<13>{}, int{14}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.4.1.3
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, IC<0>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.4 (actually 14.4.1.6)
    {
      using slice_type = decltype(make_aggregate_pair(IC<0>{}, IC<13>{}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.4.1.5 (actually 14.4.1.6)
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, IC<3>{}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.4.1.6
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, int{3}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.4.2
    {
      using slice_type = decltype(make_aggregate_pair(int{1}, IC<3>{}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(make_aggregate_pair(int{1}, int{3}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
  }
  {
    auto exts = Kokkos::extents<int, 5, Kokkos::dynamic_extent, 11>{5, 7, 11};
    test_full_extent(exts);

    test_check_static_bounds<0, IC<-1>>(exts, OOB);
    test_check_static_bounds<1, IC<-1>>(exts, OOB);
    test_check_static_bounds<2, IC<-1>>(exts, OOB);

    test_check_static_bounds<0, IC<13>>(exts, OOB);
    test_check_static_bounds<1, IC<13>>(exts, UNK);
    test_check_static_bounds<2, IC<13>>(exts, OOB);

    test_check_static_bounds<0, IC<3>>(exts, INB);
    test_check_static_bounds<1, IC<3>>(exts, UNK);
    test_check_static_bounds<2, IC<3>>(exts, INB);

    test_check_static_bounds<0, IC<6>>(exts, OOB);
    test_check_static_bounds<1, IC<6>>(exts, UNK);
    test_check_static_bounds<2, IC<6>>(exts, INB);

    test_check_static_bounds<0, int>(exts, UNK);
    test_check_static_bounds<1, int>(exts, UNK);
    test_check_static_bounds<2, int>(exts, UNK);

    test_check_static_bounds<0, unsigned short>(exts, UNK);
    test_check_static_bounds<1, unsigned short>(exts, UNK);
    test_check_static_bounds<2, unsigned short>(exts, UNK);

    // 14.3.1.1
    {
      using offset_type = IC<-1>;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using offset_type = IC<-1>;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.2
    {
      using offset_type = IC<13>;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }  
    {
      using offset_type = IC<13>;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.3
    {
      using offset_type = IC<1>;
      using extent_type = IC<-2>;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }  
    {
      using offset_type = IC<1>;
      using extent_type = IC<-2>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.3.1.4
    {
      using offset_type = IC<4>; // in bounds
      using extent_type = IC<8>; // out of bounds
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using offset_type = IC<4>; // in bounds
      using extent_type = IC<8>; // out of bounds
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }  
    // 14.3.1.5
    {
      using offset_type = IC<1>; // in bounds
      using extent_type = IC<2>; // in bounds
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, INB);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, INB);
    }
    {
      using offset_type = IC<1>; // in bounds
      using extent_type = IC<2>; // in bounds
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, INB);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, INB);
    }
    // 14.3.1.6
    {
      using offset_type = int;
      using extent_type = int;
      using stride_type = int;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using offset_type = int;
      using extent_type = IC<1>;
      using stride_type = IC<1>;
      using slice_type = strided_slice<offset_type, extent_type, stride_type>;
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }

    // General 14.4 (just to show well-formedness
    // for a variety of types that smell like pair)
    {
      using slice_type = decltype(test::non_aggregate_pair{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(std::pair{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(std::tuple{0, 1});
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }

    // 14.4.1.1
    {
      using slice_type = decltype(make_aggregate_pair(IC<-1>{}, IC<0>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using slice_type = decltype(make_aggregate_pair(IC<-1>{}, int{0}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.2 (and 14.4.1.6)
    {
      using slice_type = decltype(make_aggregate_pair(IC<13>{}, IC<14>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, UNK); // 14.4.1.6
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    {
      using slice_type = decltype(make_aggregate_pair(IC<13>{}, int{14}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, UNK); // 14.4.1.6
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.3
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, IC<0>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, OOB);
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.4 (and 14.4.1.6)
    {
      using slice_type = decltype(make_aggregate_pair(IC<0>{}, IC<13>{}));
      test_check_static_bounds<0, slice_type>(exts, OOB);
      test_check_static_bounds<1, slice_type>(exts, UNK); // 14.4.1.6
      test_check_static_bounds<2, slice_type>(exts, OOB);
    }
    // 14.4.1.5 (and 14.4.1.6)
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, IC<3>{}));
      test_check_static_bounds<0, slice_type>(exts, INB);
      test_check_static_bounds<1, slice_type>(exts, UNK); // 14.4.1.6
      test_check_static_bounds<2, slice_type>(exts, INB);
    }
    // 14.4.1.6
    {
      using slice_type = decltype(make_aggregate_pair(IC<1>{}, int{3}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    // 14.4.2
    {
      using slice_type = decltype(make_aggregate_pair(int{1}, IC<3>{}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
    {
      using slice_type = decltype(make_aggregate_pair(int{1}, int{3}));
      test_check_static_bounds<0, slice_type>(exts, UNK);
      test_check_static_bounds<1, slice_type>(exts, UNK);
      test_check_static_bounds<2, slice_type>(exts, UNK);
    }
  }
}

} // namespace (anonymous)
