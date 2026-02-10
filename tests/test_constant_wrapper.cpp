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
#include <type_traits>
#include <gtest/gtest.h>

#if defined(MDSPAN_ENABLE_P3663)
#  include "../include/experimental/__p2630_bits/constant_wrapper.hpp"
#else
#  error "This test requires that the CMake option MDSPAN_ENABLE_P3663 be ON."
#endif

namespace { // (anonymous)

#if ! defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)

template<class Integral, Integral Value>
using IC = std::integral_constant<Integral, Value>;

template<class Integral, Integral Value>
constexpr void test_integral_constant_wrapper(IC<Integral, Value> ic) {
  constexpr auto c = std::cw<Value>;

  static_assert(std::is_same_v<
    decltype(std::cw<Value>),
    std::constant_wrapper<Value>>);
  static_assert(decltype(c)::value == Value);
  static_assert(std::is_same_v<
    typename decltype(c)::type,
    std::constant_wrapper<Value>>);
  static_assert(std::is_same_v<
    typename decltype(c)::value_type,
    Integral>);

  constexpr auto c2 = std::cw<Value>;
  // Casting the arithmetic result back to Integral undoes
  // any integer promotions (e.g., short + short -> int).
  constexpr auto val_plus_1 = Integral(Value + Integral(1));
  constexpr auto c_assigned = (c2 = IC<Integral, val_plus_1>{});
  static_assert(c_assigned() == val_plus_1);
}

TEST(TestConstantWrapper, Construction) {
  test_integral_constant_wrapper(IC<signed char, -3>{});
  test_integral_constant_wrapper(IC<signed char, 3>{});
  test_integral_constant_wrapper(IC<unsigned char, 3u>{});
  test_integral_constant_wrapper(IC<short, -3>{});
  test_integral_constant_wrapper(IC<short, 3>{});
  test_integral_constant_wrapper(IC<unsigned short, 3u>{});
  test_integral_constant_wrapper(IC<int, -5>{});
  test_integral_constant_wrapper(IC<int, 5>{});
  test_integral_constant_wrapper(IC<unsigned, 5u>{});
  test_integral_constant_wrapper(IC<long, -7>{});
  test_integral_constant_wrapper(IC<long, 7>{});
  test_integral_constant_wrapper(IC<unsigned long, 7u>{});
  test_integral_constant_wrapper(IC<long long, -11>{});
  test_integral_constant_wrapper(IC<long long, 11>{});
  test_integral_constant_wrapper(IC<unsigned long long, 11u>{});
}
#endif

TEST(TestConstantWrapper, IntegerPlus) {
  std::constant_wrapper<size_t(11)> cw_11;
  constexpr size_t value = cw_11;
  constexpr size_t value2 = cw_11();
  static_assert(value == value2);
  constexpr size_t value3 = decltype(cw_11)();
  static_assert(value == value3);

#if ! defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND) && (__cplusplus >= 202002L)
  static_assert(std::is_same_v<
    decltype(cw_11),
    decltype(std::cw<size_t(11)>)>);
#endif

  [[maybe_unused]] auto expected_result = std::cw<size_t(12)>;
  using expected_type = std::constant_wrapper<size_t(12)>;
  static_assert(std::is_same_v<decltype(expected_result), expected_type>);

#if ! defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
  [[maybe_unused]] auto cw_11_plus_one = cw_11 + std::cw<size_t(1)>;
  [[maybe_unused]] auto one_plus_cw_11 = std::cw<size_t(1)> + cw_11;

  static_assert(! std::is_same_v<
    decltype(cw_11 + std::cw<size_t(1)>),
    size_t>);
  static_assert(std::is_same_v<
    decltype(cw_11 + std::cw<size_t(1)>),
    std::constant_wrapper<value + size_t(1)>>);
  static_assert(std::is_same_v<
    decltype(std::cw<size_t(1)> + cw_11),
    std::constant_wrapper<value + size_t(1)>>);
#endif
}

} // namespace (anonymous)
