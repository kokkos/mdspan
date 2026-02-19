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

#pragma once

#include "../__p0009_bits/utility.hpp"
#include <type_traits>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
namespace detail {

#if defined(__cpp_lib_constant_wrapper)

using std::constant_wrapper;
using std::cw;

#else

template<auto Value, class T = decltype(Value)>
using constant_wrapper = integral_constant<T, Value>;

template<auto Value>
  constexpr auto cw = constant_wrapper<Value>{};

#endif // __cpp_lib_constant_wrapper

template<auto Value, class T>
constexpr auto
increment([[maybe_unused]] constant_wrapper<Value, T> x) {
  using value_type = typename decltype(x)::value_type;
  return cw< decltype(x)::value + value_type(1) >;
}

template<class T>
constexpr bool is_constant_wrapper = false;

template<auto Value, class Type>
constexpr bool is_constant_wrapper<constant_wrapper<Value, Type>> = true;

} // namespace detail
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
