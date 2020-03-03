/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#pragma once

#include "macros.hpp"
#include "trait_backports.hpp" // enable_if

#include <cstddef>
#include <utility> // integer_sequence

namespace std {
namespace experimental {
namespace detail {

//==============================================================================

_MDSPAN_INLINE_VARIABLE constexpr struct
    __construct_partially_static_array_from_sizes_tag_t {
} __construct_partially_static_array_from_sizes_tag = {};

template <size_t _N> struct __construct_psa_from_dynamic_values_tag_t {};

//==============================================================================

template <size_t _I, class _T> using __repeated_with_idxs = _T;

//==============================================================================

template <class _T, class _ValsSeq, _T __sentinal, class _IdxsSeq,
          class _Enable = void>
class __standard_layout_psa;

template <class _T, _T __value, _T... __values_or_sentinals, _T __sentinal, size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _T, integer_sequence<_T, __value, __values_or_sentinals...>, __sentinal,
    integer_sequence<size_t, _Idx, _Idxs...>> {
  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_T, integer_sequence<_T, __values_or_sentinals...>,
                            __sentinal, integer_sequence<size_t, _Idxs...>>;

  __next_t __next;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa const &) noexcept =
      default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__standard_layout_psa() noexcept = default;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION
  constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t, _T const &__val,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
      : __next(__construct_partially_static_array_from_sizes_tag, __vals...) {}

  // Dynamic idxs only given version, which is probably going to not need to
  // supported by the time mdspan is merged into the standard, but is currently
  // the way this is specified.  Use a repeated tag for the old semantics
  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t,
      __Ts const &... __vals) noexcept
      : __next(__construct_partially_static_array_from_sizes_tag,
               __construct_partially_static_array_from_sizes_tag, __vals...) {}

  template <size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_T, _N> const &__vals) noexcept
      : __next(__vals) {}

  template <size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
      array<_T, _NDynamic> const &__vals) noexcept
      : __next(__tag, __vals) {}

  template <class _U, class _UValsSeq, _U __u_sentinal, class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_U, _UValsSeq, __u_sentinal, _UIdxsSeq> const
          &__rhs) noexcept
      : __next(__rhs.__next) {}

  //--------------------------------------------------------------------------

  template <size_t _I>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __next.__get_n<_I>();
  }
  template <>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n<_Idx>() const noexcept {
    return __value;
  }
  template <size_t _I>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    __next.__set_value(__rhs);
  }
  template <>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n<_Idx>(_T const &__rhs) noexcept {
    // Don't assert here because that would break constexpr. This better
    // not change anything, though
  }
  template <size_t _I, enable_if_t<_I == _Idx, _T> = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __value;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __next_t.__get_static_n<_I, __sentinal>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value * (_T(_Idxs == __n)) + __next.get(__n);
  }

  //--------------------------------------------------------------------------
};

// Dynamic case
template <class _T, _T __sentinal, _T... __values_or_sentinals, size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _T, integer_sequence<_T, __sentinal, __values_or_sentinals...>, __sentinal,
    integer_sequence<size_t, _Idx, _Idxs...>> {
  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_T, integer_sequence<_T, __values_or_sentinals...>,
                            __sentinal, integer_sequence<size_t, _Idxs...>>;

  _T __value;
  __next_t __next;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa const &) noexcept =
      default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__standard_layout_psa() noexcept = default;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION
  constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t, _T const &__val,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
      : __value(__val),
        __next(__construct_partially_static_array_from_sizes_tag, __vals...) {}

  // Dynamic idxs only given version, which is probably going to not need to
  // supported by the time mdspan is merged into the standard, but is currently
  // the way this is specified.  Use a repeated tag for the old semantics
  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t,
      _T const& __val,
      __Ts const &... __vals) noexcept
      : __value(__val),
        __next(__construct_partially_static_array_from_sizes_tag,
               __construct_partially_static_array_from_sizes_tag, __vals...) {}

  template <size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_T, _N> const &__vals) noexcept
      : __value(::std::get<_Idx>(__vals)),
        __next(__vals) {}

  template <size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
      array<_T, _NDynamic> const &__vals) noexcept
      : __value(::std::get)
        __next(__construct_psa_from_dynamic_values_tag_t<_IDynamic + 1>, __vals) {}

  template <class _U, class _UValsSeq, _U __u_sentinal, class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_U, _UValsSeq, __u_sentinal, _UIdxsSeq> const
          &__rhs) noexcept
      : __next(__rhs.__next) {}

  //--------------------------------------------------------------------------

  template <size_t _I>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __next.__get_n<_I>();
  }
  template <>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n<_Idx>() const noexcept {
    return __value;
  }
  template <size_t _I>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    __next.__set_value(__rhs);
  }
  template <>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n<_Idx>(_T const &__rhs) noexcept {
    __value = __rhs;
  }
  template <size_t _I, enable_if_t<_I == _Idx, _T> = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __sentinal;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __next_t.__get_static_n<_I, __sentinal>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value * (_T(_Idxs == __n)) + __next.get(__n);
  }

  //--------------------------------------------------------------------------
};

} // namespace detail
} // end namespace experimental
} // namespace std
