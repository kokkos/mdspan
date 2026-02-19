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

#include "../include/experimental/__p2630_bits/constant_wrapper.hpp"

namespace { // (anonymous)

#if defined(__cpp_lib_constant_wrapper)

template<class Integral, Integral Value>
using IC = std::integral_constant<Integral, Value>;

template<class Integral, Integral Value>
constexpr void test_integral_constant_wrapper(IC<Integral, Value> ic) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::constant_wrapper;

  constexpr auto c = cw<Value>;

  static_assert(std::is_same_v<
    std::remove_const_t<decltype(cw<Value>)>,
    constant_wrapper<Value>>);
  static_assert(decltype(c)::value == Value);
  static_assert(std::is_same_v<
    typename decltype(c)::type,
    constant_wrapper<Value>>);
  static_assert(std::is_same_v<
    typename decltype(c)::value_type,
    Integral>);

  constexpr auto c2 = cw<Value>;
  // Casting the arithmetic result back to Integral undoes
  // any integer promotions (e.g., short + short -> int).
  constexpr auto val_plus_1 = Integral(Value + Integral(1));
  constexpr auto c_assigned = (c2 = IC<Integral, val_plus_1>{});
  static_assert(c_assigned == val_plus_1);
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
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::constant_wrapper;

  constant_wrapper<size_t(11)> cw_11;
  constexpr size_t value = cw_11;
  constexpr size_t value2 = constant_wrapper<size_t(11)>::value;
  static_assert(value == value2);
  constexpr size_t value3 = decltype(cw_11)();
  static_assert(value == value3);

#if defined(__cpp_lib_constant_wrapper)
  static_assert(std::is_same_v<
    decltype(cw_11),
    std::remove_const_t<decltype(cw<size_t(11)>)>>);
#endif

  [[maybe_unused]] auto expected_result = cw<size_t(12)>;
  using expected_type = constant_wrapper<size_t(12)>;
  static_assert(std::is_same_v<decltype(expected_result), expected_type>);

#if defined(__cpp_lib_constant_wrapper)
  [[maybe_unused]] auto cw_11_plus_one = cw_11 + cw<size_t(1)>;
  [[maybe_unused]] auto one_plus_cw_11 = cw<size_t(1)> + cw_11;

  static_assert(! std::is_same_v<
    decltype(cw_11 + cw<size_t(1)>),
    size_t>);
  static_assert(std::is_same_v<
    decltype(cw_11 + cw<size_t(1)>),
    constant_wrapper<value + size_t(1)>>);
  static_assert(std::is_same_v<
    decltype(cw<size_t(1)> + cw_11),
    constant_wrapper<value + size_t(1)>>);
#endif
}

TEST(TestConstantWrapper, Arithmetic) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::cw;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::constant_wrapper;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::increment;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::divide;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::multiply;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::detail::is_constant_wrapper;

  constexpr auto c6 = cw<size_t(6)>;
  constexpr auto c3 = cw<size_t(3)>;
  constexpr auto c0 = cw<size_t(0)>;

  // increment preserves compile-time constant
  constexpr auto c7 = increment(c6);
  static_assert(size_t(c7) == 7u);
  static_assert(is_constant_wrapper<decltype(c7)>);

  // divide preserves compile-time constant
  constexpr auto div_result = divide<size_t>(c6, c3);
  static_assert(size_t(div_result) == 2u);
  static_assert(is_constant_wrapper<decltype(div_result)>);

  // divide by zero returns 0 (special case for strided_slice)
  constexpr auto div_zero = divide<size_t>(c0, c3);
  static_assert(size_t(div_zero) == 0u);
  static_assert(is_constant_wrapper<decltype(div_zero)>);

  // multiply preserves compile-time constant
  constexpr auto mul_result = multiply<size_t>(c6, c3);
  static_assert(size_t(mul_result) == 18u);
  static_assert(is_constant_wrapper<decltype(mul_result)>);
}

} // namespace (anonymous)
