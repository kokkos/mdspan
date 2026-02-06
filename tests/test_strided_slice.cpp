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

namespace {

template<class OffsetType, class ExtentType, class StrideType>
void test_strided_slice(OffsetType offset, ExtentType extent, StrideType stride)
{
  // Clang 14 is bad at CTAD for aggregates.
#if defined(__clang__) && (__clang_major__ < 15)
  Kokkos::strided_slice<OffsetType, ExtentType, StrideType> s{offset, extent, stride};
#else
  Kokkos::strided_slice s{offset, extent, stride};
#endif
  static_assert(std::is_same_v<decltype(s), Kokkos::strided_slice<OffsetType, ExtentType, StrideType>>);
  auto offset2 = s.offset;
  static_assert(std::is_same_v<OffsetType, decltype(offset2)>);
  auto extent2 = s.extent;
  static_assert(std::is_same_v<ExtentType, decltype(extent2)>);
  auto stride2 = s.stride;
  static_assert(std::is_same_v<StrideType, decltype(stride2)>);

  ASSERT_EQ(offset2, offset);
  ASSERT_EQ(extent2, extent);
  ASSERT_EQ(stride2, stride);
}

template<class T, T Value>
constexpr auto IC = std::integral_constant<T, Value>{};

#if defined(MDSPAN_ENABLE_P3663)
template<std::integral T, T Value>
  requires(! std::is_same_v<T, bool>)
struct my_integral_constant {
  static constexpr T value = Value;
  constexpr operator T () const { return value; }
#if defined(__cpp_static_call_operator)
  static constexpr T operator() () { return value; }
#endif
};

template<class T, T Value>
constexpr auto IC2 = my_integral_constant<T, Value>{};

static_assert(
  std::convertible_to<
    my_integral_constant<int, 1>,
    decltype(my_integral_constant<int, 1>::value)>);

static_assert(
  std::equality_comparable_with<
    my_integral_constant<int, 1>,
    decltype(my_integral_constant<int, 1>::value)>);

static_assert(
  Kokkos::detail::is_integral_constant_like_v<
    my_integral_constant<int, 1>
  >);
#endif // MDSPAN_ENABLE_P3663

TEST(StridedSlice, WellFormed) {
  test_strided_slice(int(1), unsigned(10), long(3));
  test_strided_slice((signed char)(1), (unsigned short)(10), (unsigned long long)(3));

  test_strided_slice(IC<int, 1>, unsigned(10), long(3));
  test_strided_slice(int(1), IC<unsigned, 10>, long(3));
  test_strided_slice(int(1), unsigned(10), IC<long, 3>);

#if defined(MDSPAN_ENABLE_P3663)
  test_strided_slice(std::cw<1>, unsigned(10), long(3));
  test_strided_slice(int(1), std::cw<unsigned(10)>, long(3));
  test_strided_slice(int(1), unsigned(10), std::cw<long(3)>);

  test_strided_slice(IC2<int, 1>, unsigned(10), long(3));
  test_strided_slice(int(1), IC2<unsigned, 10>, long(3));
  test_strided_slice(int(1), unsigned(10), IC2<long, 3>);
#endif
}

} // namespace (anonymous)
