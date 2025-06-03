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
#include <tuple>
#include <type_traits>
#include <utility>
#include <gtest/gtest.h>

namespace {

struct convertible_to_full_extent_t {
  constexpr operator Kokkos::full_extent_t() const {
    return Kokkos::full_extent;
  }
};
static_assert(std::is_convertible_v<convertible_to_full_extent_t, Kokkos::full_extent_t>);

struct foo {};
struct bar {};

template<class T, class PairLike>
concept has_get_like_pair = requires(T t) {
  { std::get<0>(t) } -> std::convertible_to<typename PairLike::first_type>;
  { std::get<1>(t) } -> std::convertible_to<typename PairLike::second_type>;
};
static_assert(has_get_like_pair<std::pair<foo, bar>, std::pair<foo, bar>>);
static_assert(has_get_like_pair<std::tuple<foo, bar>, std::pair<foo, bar>>);

// Structured binding with two elements is valid,
// but it's not convertible to pair or tuple,
// and neither get<0> nor get<1> work on it.
template<class First, class Second>
struct my_pair {
  First first;
  Second second;
};
static_assert(! std::is_convertible_v<my_pair<foo, bar>, std::pair<foo, bar>>);
static_assert(! std::is_convertible_v<my_pair<foo, bar>, std::tuple<foo, bar>>);
static_assert(! has_get_like_pair<my_pair<foo, bar>, std::pair<foo, bar>>);

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
  using Kokkos::detail::check_static_bounds_result;

  [&] <size_t ... Inds> (std::index_sequence<Inds...>) {
    (test_check_static_bounds<Inds, Kokkos::full_extent_t>(extents, check_static_bounds_result::in_bounds), ...);
  } (std::make_index_sequence<sizeof...(Exts)>());

  [&] <size_t ... Inds> (std::index_sequence<Inds...>) {
    (test_check_static_bounds<Inds, convertible_to_full_extent_t>(extents, check_static_bounds_result::in_bounds), ...);
  } (std::make_index_sequence<sizeof...(Exts)>());
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
  }
}

} // namespace (anonymous)
