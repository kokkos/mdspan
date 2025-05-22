
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
#if defined(MDSPAN_ENABLE_P3663)
#  include "constant_wrapper.hpp"
#endif

#include <type_traits>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {

#if defined(MDSPAN_ENABLE_P3663)
template<class T>
concept __mdspan_integral_constant_like =
  std::is_integral_v<std::remove_cvref_t<decltype(T::value)>> &&
  ! std::is_same_v<bool, std::remove_cvref_t<decltype(T::value)>> &&
  std::convertible_to<T, decltype(T::value)> &&
  std::equality_comparable_with<T, decltype(T::value)> &&
  std::bool_constant<T() == T::value>::value &&
  std::bool_constant<static_cast<decltype(T::value)>(T()) == T::value>::value;
#endif // MDSPAN_ENABLE_P3663

namespace { // (anonymous)
  template<class T>
  struct mdspan_is_integral_constant: std::false_type {};

#if defined(MDSPAN_ENABLE_P3663)
  template<__mdspan_integral_constant_like T>
  struct mdspan_is_integral_constant<T> : std::true_type {};
#else
  template<class T, T val>
  struct mdspan_is_integral_constant<std::integral_constant<T,val>>: std::true_type {};
#endif

  template<class T>
  constexpr bool __mdspan_is_index_like_v =
    (std::is_integral_v<T> && ! std::is_same_v<bool, T>) ||
    mdspan_is_integral_constant<T>::value;
    ;
} // namespace (anonymous)

// Slice Specifier allowing for strides and compile time extent
template <class OffsetType, class ExtentType, class StrideType>
struct strided_slice {
  using offset_type = OffsetType;
  using extent_type = ExtentType;
  using stride_type = StrideType;

  MDSPAN_IMPL_NO_UNIQUE_ADDRESS OffsetType offset{};
  MDSPAN_IMPL_NO_UNIQUE_ADDRESS ExtentType extent{};
  MDSPAN_IMPL_NO_UNIQUE_ADDRESS StrideType stride{};

  static_assert(__mdspan_is_index_like_v<OffsetType>);
  static_assert(__mdspan_is_index_like_v<ExtentType>);
  static_assert(__mdspan_is_index_like_v<StrideType>);
};

} // MDSPAN_IMPL_STANDARD_NAMESPACE
