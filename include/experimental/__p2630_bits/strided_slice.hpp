
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

#include "integral_constant_like.hpp"
#if defined(MDSPAN_ENABLE_P3663)
#  include "constant_wrapper.hpp"
#endif

#include <type_traits>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {

namespace detail {

#if defined(MDSPAN_ENABLE_P3663)
  template<class T, T Value>
  using mdspan_constant_wrapper = decltype(cw<Value>);

  template<class T>
  constexpr bool is_constant_wrapper = false;
  
  template<auto Value, class Type>
  constexpr bool is_constant_wrapper<constant_wrapper<Value, Type>> = true;  
#else
  template<class T, T Value>
  using mdspan_constant_wrapper = std::integral_constant<T, Value>;
#endif // MDSPAN_ENABLE_P3663

  template<class T>
  constexpr bool __mdspan_is_index_like_v =
    (std::is_integral_v<T> && ! std::is_same_v<bool, T>) ||
    is_integral_constant_like_v<T>;
} // namespace detail

// Slice Specifier allowing for strides and compile time extent
template <class OffsetType, class ExtentType, class StrideType>
struct strided_slice {
  using offset_type = OffsetType;
  using extent_type = ExtentType;
  using stride_type = StrideType;

  MDSPAN_IMPL_NO_UNIQUE_ADDRESS OffsetType offset{};
  MDSPAN_IMPL_NO_UNIQUE_ADDRESS ExtentType extent{};
  MDSPAN_IMPL_NO_UNIQUE_ADDRESS StrideType stride{};

  static_assert(detail::__mdspan_is_index_like_v<OffsetType>);
  static_assert(detail::__mdspan_is_index_like_v<ExtentType>);
  static_assert(detail::__mdspan_is_index_like_v<StrideType>);
};

#if (__cplusplus < 202002L)
template <class OffsetType, class ExtentType, class StrideType>
strided_slice(const OffsetType&, const ExtentType&, const StrideType&) ->
  strided_slice<OffsetType, ExtentType, StrideType>;
#endif
} // MDSPAN_IMPL_STANDARD_NAMESPACE
