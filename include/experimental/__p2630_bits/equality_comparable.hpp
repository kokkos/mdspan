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

#include "../__p0009_bits/macros.hpp"
#if defined(__cpp_lib_concepts)
#  include <concepts>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
  namespace detail {
    template<class T, class = void>
    struct is_equality_comparable : std::bool_constant<std::equality_comparable<T>> {};

    template<class T, class U, class = void>
    struct is_equality_comparable_with : std::bool_constant<std::equality_comparable_with<T, U>> {};
  } // namespace detail
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE

#else

#include <type_traits>
#include <utility>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
namespace detail {

  template<typename T, typename = void>
  struct is_equality_comparable : std::false_type {};

  template<typename T>
  struct is_equality_comparable<
    T,
    std::void_t<
      decltype(std::declval<const T&>() == std::declval<const T&>()),
      decltype(std::declval<const T&>() != std::declval<const T&>())
    >
  > : std::bool_constant<
    std::is_convertible_v<
      decltype(std::declval<const T&>() == std::declval<const T&>()),
      bool
    > &&
    std::is_convertible_v<
      decltype(std::declval<const T&>() != std::declval<const T&>()),
      bool
    >
  > {};

  template<typename T, typename U, typename = void>
  struct is_equality_comparable_with : std::false_type {};

  template<typename T, typename U>
  struct is_equality_comparable_with<
    T, U,
    std::void_t<
      decltype(std::declval<const T&>() == std::declval<const U&>()),
      decltype(std::declval<const T&>() != std::declval<const U&>()),
      decltype(std::declval<const U&>() == std::declval<const T&>()),
      decltype(std::declval<const U&>() != std::declval<const T&>())
    >
  > : std::bool_constant<
    is_equality_comparable<T>::value &&
    is_equality_comparable<U>::value &&
    std::is_convertible_v<
      decltype(std::declval<const T&>() == std::declval<const U&>()),
      bool
    > &&
    std::is_convertible_v<
      decltype(std::declval<const T&>() != std::declval<const U&>()),
      bool
    > &&
    std::is_convertible_v<
      decltype(std::declval<const U&>() == std::declval<const T&>()),
      bool
    > &&
    std::is_convertible_v<
      decltype(std::declval<const U&>() != std::declval<const T&>()),
      bool
    >
  > {};

} // namespace detail
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE

#endif // defined(__cpp_lib_concepts)
