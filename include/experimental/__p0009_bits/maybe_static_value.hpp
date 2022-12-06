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
#include "macros.hpp"

#include "dynamic_extent.hpp"

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#  include "no_unique_address.hpp"
#endif

// This is only needed for the non-standard-layout version of partially
// static array.
// Needs to be after the includes above to work with the single header generator
#if !_MDSPAN_PRESERVE_STANDARD_LAYOUT
namespace std {
namespace experimental {

//==============================================================================

namespace detail {

// static case
template <class _dynamic_t, class static_t, _static_t __v,
          _static_t __is_dynamic_sentinal = dynamic_extent,
          size_t __array_entry_index = 0>
struct __maybe_static_value {
  static constexpr _static_t __static_value = __v;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _dynamic_t __value() const noexcept {
    return static_cast<_dynamic_t>(__v);
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& /*__rhs*/) noexcept {
    // Should we assert that the value matches the static value here?
    return {};
  }

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value(__maybe_static_value const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value(__maybe_static_value&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __maybe_static_value& operator=(__maybe_static_value const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __maybe_static_value& operator=(__maybe_static_value&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__maybe_static_value() noexcept = default;

  MDSPAN_INLINE_FUNCTION
  constexpr explicit __maybe_static_value(_dynamic_t const&) noexcept {
    // Should we assert that the value matches the static value here?
  }

  //--------------------------------------------------------------------------

};

// dynamic case
template <class _dynamic_t, class _static_t, _static_t __is_dynamic_sentinal, size_t __array_entry_index>
struct __maybe_static_value<_dynamic_t, _static_t, __is_dynamic_sentinal, __is_dynamic_sentinal,
                            __array_entry_index>
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __no_unique_address_emulation<_T>
#endif
{
  static constexpr _static_t __static_value = __is_dynamic_sentinal;
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS _dynamic_t __v = {};
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _dynamic_t __value() const noexcept {
    return __v;
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _dynamic_t &__ref() noexcept {
    return __v;
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
    __v = (_U &&)rhs;
    return {};
  }
#else
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _dynamic_t __value() const noexcept {
    return this->__no_unique_address_emulation<_dynamic_t>::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _dynamic_t &__ref() noexcept {
    return this->__no_unique_address_emulation<_dynamic_t>::__ref();
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
    this->__no_unique_address_emulation<_dynamic_t>::__ref() = (_U &&)__rhs;
    return {};
  }
#endif
};

} // namespace detail

//==============================================================================

} // end namespace experimental
} // end namespace std

#endif // !_MDSPAN_PRESERVE_STANDARD_LAYOUT
