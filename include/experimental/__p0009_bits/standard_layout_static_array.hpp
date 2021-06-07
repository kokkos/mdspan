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
#include "no_unique_address.hpp"
#include "trait_backports.hpp" // enable_if

#include <array>
#include <utility> // integer_sequence
#include <cstddef>

namespace std {
namespace experimental {
namespace detail {

//==============================================================================

_MDSPAN_INLINE_VARIABLE constexpr struct
    __construct_partially_static_array_from_sizes_tag_t {
} __construct_partially_static_array_from_sizes_tag = {};

template <size_t _N = 0> struct __construct_psa_from_dynamic_values_tag_t {};

//==============================================================================

template <size_t _I, class _T> using __repeated_with_idxs = _T;

//==============================================================================

#if _MDSPAN_PRESERVE_STANDARD_LAYOUT

/**
 *  PSA = "partially static array"
 *
 * @tparam _T
 * @tparam _ValsSeq
 * @tparam __sentinal
 */
template <class _Tag, class _T, class _ValsSeq, _T __sentinal = dynamic_extent,
          class _IdxsSeq = make_index_sequence<_ValsSeq::size()>>
struct __standard_layout_psa;

//==============================================================================
// Static case
template <class _Tag, class _T, _T __value, _T... __values_or_sentinals,
          _T __sentinal, size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _Tag, _T, integer_sequence<_T, __value, __values_or_sentinals...>,
    __sentinal, integer_sequence<size_t, _Idx, _Idxs...>>
    : private __no_unique_address_emulation<__standard_layout_psa<
          _Tag, _T, integer_sequence<_T, __values_or_sentinals...>, __sentinal,
          integer_sequence<size_t, _Idxs...>>> {
  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_Tag, _T,
                            integer_sequence<_T, __values_or_sentinals...>,
                            __sentinal, integer_sequence<size_t, _Idxs...>>;
  using __base_t = __no_unique_address_emulation<__next_t>;

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 __next_t &__next() noexcept {
    return this->__base_t::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __next_t const &__next() const noexcept {
    return this->__base_t::__ref();
  }

  static constexpr auto __size = sizeof...(_Idxs) + 1;
#ifdef _MDSPAN_COMPILER_MSVC
  // MSVC doesn't like the fact that __next_t happens to be a base
  // class that's private, even though __size_synamic is public in
  // it's definition.
  struct __msvc_workaround_tag {};
  using __msvc_workaround_next_t = __standard_layout_psa<
      __msvc_workaround_tag, _T,
      integer_sequence<_T, __values_or_sentinals...>, __sentinal,
      integer_sequence<size_t, _Idxs...>>;
  static constexpr auto __size_dynamic =
      __msvc_workaround_next_t::__size_dynamic;
#else
  static constexpr auto __size_dynamic = __next_t::__size_dynamic;
#endif

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() noexcept = default;
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
      __construct_partially_static_array_from_sizes_tag_t, _T const & /*__val*/,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
      : __base_t(__base_t{__next_t(
            __construct_partially_static_array_from_sizes_tag, __vals...)}) {}

  // Dynamic idxs only given version, which is probably going to not need to
  // supported by the time mdspan is merged into the standard, but is currently
  // the way this is specified.  Use a repeated tag for the old semantics
  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t,
      _Ts const &... __vals) noexcept
      : __base_t(__base_t{__next_t(
            __construct_partially_static_array_from_sizes_tag,
            __construct_partially_static_array_from_sizes_tag, __vals...)}) {}

  template <size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_T, _N> const &__vals) noexcept
      : __base_t(__base_t{__next_t(__vals)}) {}

  template <size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
      array<_T, _NDynamic> const &__vals) noexcept
      : __base_t(__base_t{__next_t(__tag, __vals)}) {}

  template <class _UTag, class _U, class _UValsSeq, _U __u_sentinal,
            class _IdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _UValsSeq, __u_sentinal, _IdxsSeq> const
          &__rhs) noexcept
      : __base_t(__base_t{__next_t(__rhs.__next())}) {}

  //--------------------------------------------------------------------------

  // See https://godbolt.org/z/_KSDNX for a summary-by-example of why this is
  // necessary.  The we're using inheritance here instead of an alias template
  // is because we have to deduce __values_or_sentinals in several places, and
  // alias templates doen't permit that in this context.
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __standard_layout_psa const &__enable_psa_conversion() const
      noexcept {
    return *this;
  }

  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return this->__base_t::__ref().template __get_n<_I>();
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __value;
  }
  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    this->__base_t::__ref().__set_value(__rhs);
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    // Don't assert here because that would break constexpr. This better
    // not change anything, though
  }
  template <size_t _I, enable_if_t<_I == _Idx, _T> = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __value;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __next_t::template __get_static_n<_I, __default>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value * (_T(_Idx == __n)) + this->__base_t::__ref().__get(__n);
  }

  //--------------------------------------------------------------------------
};

//==============================================================================

// Dynamic case, __next_t may or may not be empty
template <class _Tag, class _T, _T __sentinal, _T... __values_or_sentinals,
          size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _Tag, _T, integer_sequence<_T, __sentinal, __values_or_sentinals...>,
    __sentinal, integer_sequence<size_t, _Idx, _Idxs...>> {
  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_Tag, _T,
                            integer_sequence<_T, __values_or_sentinals...>,
                            __sentinal, integer_sequence<size_t, _Idxs...>>;

  using __value_pair_t = __compressed_pair<_T, __next_t>;
  __value_pair_t __value_pair;
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 __next_t &__next() noexcept {
    return __value_pair.__second();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __next_t const &__next() const noexcept {
    return __value_pair.__second();
  }

  static constexpr auto __size = sizeof...(_Idxs) + 1;
  static constexpr auto __size_dynamic = 1 + __next_t::__size_dynamic;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() noexcept = default;
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
      : __value_pair(__val,
                     __next_t(__construct_partially_static_array_from_sizes_tag,
                              __vals...)) {}

  // Dynamic idxs only given version, which is probably going to not need to
  // supported by the time mdspan is merged into the standard, but is currently
  // the way this is specified.  Use a repeated tag for the old semantics
  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t, _T const &__val,
      _Ts const &... __vals) noexcept
      : __value_pair(__val,
                     __next_t(__construct_partially_static_array_from_sizes_tag,
                              __construct_partially_static_array_from_sizes_tag,
                              __vals...)) {}

  template <size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_T, _N> const &__vals) noexcept
      : __value_pair(::std::get<_Idx>(__vals), __vals) {}

  template <size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
      array<_T, _NDynamic> const &__vals) noexcept
      : __value_pair(
            ::std::get<_IDynamic>(__vals),
            __next_t(__construct_psa_from_dynamic_values_tag_t<_IDynamic + 1>{},
                     __vals)) {}

  template <class _UTag, class _U, class _UValsSeq, _U __u_sentinal,
            class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _UValsSeq, __u_sentinal, _UIdxsSeq> const
          &__rhs) noexcept
      : __value_pair(__rhs.template __get_n<_Idx>(), __rhs.__next()) {}

  //--------------------------------------------------------------------------

  // See comment in the previous partial specialization for why this is
  // necessary.  Or just trust me that it's messy.
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __standard_layout_psa const &__enable_psa_conversion() const
      noexcept {
    return *this;
  }

  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __next().template __get_n<_I>();
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __value_pair.__first();
  }
  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    __next().__set_value(__rhs);
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    __value_pair.__first() = __rhs;
  }
  template <size_t _I, enable_if_t<_I == _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __default;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __next_t::template __get_static_n<_I, __default>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value_pair.__first() * (_T(_Idx == __n)) + __next().__get(__n);
  }

  //--------------------------------------------------------------------------
};

// empty/terminal case
template <class _Tag, class _T, _T __sentinal>
struct __standard_layout_psa<_Tag, _T, integer_sequence<_T>, __sentinal,
                             integer_sequence<size_t>> {
  //--------------------------------------------------------------------------

  static constexpr auto __size = 0;
  static constexpr auto __size_dynamic = 0;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() noexcept
#if defined(__clang__) || defined(_MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND)
  // As far as I can tell, there appears to be a bug in clang that's causing
  // this to be non-constexpr when it's defaulted.
  { }
#else
   = default;
#endif
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

  MDSPAN_INLINE_FUNCTION
  constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t) noexcept {}

  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t) noexcept {}

  template <size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_T, _N> const &) noexcept {}

  template <size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
      array<_T, _NDynamic> const &) noexcept {}

  template <class _UTag, class _U, class _UValsSeq, _U __u_sentinal,
            class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _UValsSeq, __u_sentinal, _UIdxsSeq> const&) noexcept {}

  // See comment in the previous partial specialization for why this is
  // necessary.  Or just trust me that it's messy.
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __standard_layout_psa const &__enable_psa_conversion() const
      noexcept {
    return *this;
  }

  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t /*n*/) const noexcept {
    return 0;
  }
};

// Same thing, but with a disambiguator so that same-base issues doesn't cause
// a loss of standard-layout-ness.
template <class _Tag, size_t... __values_or_sentinals>
struct __partially_static_sizes_tagged
    : __standard_layout_psa<
          _Tag, size_t,
          integer_sequence<size_t, __values_or_sentinals...>> {
  using __tag_t = _Tag;
  using __psa_impl_t = __standard_layout_psa<
      _Tag, size_t, integer_sequence<size_t, __values_or_sentinals...>>;
  using __psa_impl_t::__psa_impl_t;
  MDSPAN_INLINE_FUNCTION
  constexpr __partially_static_sizes_tagged() noexcept
#ifdef _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND
    : __psa_impl_t() { }
#else
    = default;
#endif
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __partially_static_sizes_tagged(
      __partially_static_sizes_tagged const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __partially_static_sizes_tagged(
      __partially_static_sizes_tagged &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __partially_static_sizes_tagged &
  operator=(__partially_static_sizes_tagged const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __partially_static_sizes_tagged &
  operator=(__partially_static_sizes_tagged &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__partially_static_sizes_tagged() noexcept = default;

  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr explicit __partially_static_sizes_tagged(
    __partially_static_sizes_tagged<_UTag, __values_or_sentinals...> const& __vals
  ) noexcept : __psa_impl_t(__vals.__enable_psa_conversion()) { }
};

struct __no_tag {};
template <size_t... __values_or_sentinals>
struct __partially_static_sizes
    : __partially_static_sizes_tagged<__no_tag, __values_or_sentinals...> {
private:
  using __base_t =
      __partially_static_sizes_tagged<__no_tag, __values_or_sentinals...>;
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes(
    __partially_static_sizes_tagged<_UTag, __values_or_sentinals...>&& __vals
  ) noexcept : __base_t(::std::move(__vals)) { }
public:
  using __base_t::__base_t;

#ifdef _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND
  MDSPAN_INLINE_FUNCTION
  constexpr __partially_static_sizes() noexcept : __base_t() { }
#endif
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes_tagged<
      _UTag, __values_or_sentinals...>
  __with_tag() const noexcept {
    return __partially_static_sizes_tagged<_UTag, __values_or_sentinals...>(*this);
  }
};

#endif // _MDSPAN_PRESERVE_STATIC_LAYOUT

} // namespace detail
} // end namespace experimental
} // namespace std
