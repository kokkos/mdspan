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

#ifndef MDSPAN_INCLUDE_EXPERIMENTAL___P0009_BITS_ARRAY_WORKAROUND_HPP_
#define MDSPAN_INCLUDE_EXPERIMENTAL___P0009_BITS_ARRAY_WORKAROUND_HPP_

#include "macros.hpp"
#include "trait_backports.hpp"

#include <type_traits>
#include <array>
#include <utility>

namespace std {
namespace experimental {
// nvcc itself and icc's optimizer both don't play well with std::array :-/
namespace __array_workaround {

// Assumes T is integral, which works for our use case
template <class T, size_t Idx>
struct __array_entry_impl {
  T __value = { };
#if !MDSPAN_HAS_CXX_14
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __array_entry_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __array_entry_impl(__array_entry_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __array_entry_impl(__array_entry_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14 __array_entry_impl& operator=(__array_entry_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14 __array_entry_impl& operator=(__array_entry_impl&&) noexcept = default;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __array_entry_impl(T&& val) noexcept : __value(std::move(val)) { }
#endif
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr T __iget(ptrdiff_t i) const noexcept {
    return (i == Idx) ? __value : T(0);
  }
  MDSPAN_FORCE_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 __mdspan_enable_fold_comma __iset(ptrdiff_t i, T val) noexcept {
    if(i == Idx) __value = val;
    return { };
  }
};

template <class T, size_t N, class>
struct __array_impl;

template <class T, size_t I>
using __repeated = T;

template <class T, size_t N, size_t... Idxs>
struct __array_impl<T, N, integer_sequence<size_t, Idxs...>>
  : __array_entry_impl<T, Idxs>...
{
  static constexpr size_t __size = N;

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __array_impl(__array_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __array_impl(__array_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __array_impl& operator=(__array_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __array_impl& operator=(__array_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__array_impl() noexcept = default;

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_FORCE_INLINE_FUNCTION constexpr),
    __array_impl, (), noexcept,
  /* requires */ N != 0
  ) : __array_entry_impl<T, Idxs>()...
  { }

  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr
  __array_impl(__repeated<T, Idxs>... vals) noexcept
    : __array_entry_impl<T, Idxs>({T{vals}})...
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr),
    __array_impl, (array<T, N> vals), noexcept,
    /* requires */ N != 0
  ) : __array_entry_impl<T, Idxs>({T{vals[Idxs]}})...
  { }

  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr
  __array_impl(array<T, 0> vals) noexcept
  { }

  // TODO remove this, it's unused
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr T
  __get(ptrdiff_t i) const noexcept {
    // For N > 0, this should work:
    // (static_cast<__array_entry_impl<T, 0>>(this) + i)->__value;
    return _MDSPAN_FOLD_PLUS_RIGHT((this->__array_entry_impl<T, Idxs>::__iget(i)), /* + ... + */ 0);
  }
  template <ptrdiff_t I>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr T const&
  __get_n() const noexcept {
    return this->__array_entry_impl<T, I>::__value;
  }

  // TODO remove this, it's unused
  MDSPAN_FORCE_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 void
  __set(ptrdiff_t i, T val) noexcept {
    _MDSPAN_FOLD_COMMA(this->__array_entry_impl<T, Idxs>::__iset(i, val) /*, ... */);
  }
  template <ptrdiff_t I>
  MDSPAN_FORCE_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 void
  __set_n(T val) noexcept {
    this->__array_entry_impl<T, I>::__value = val;
  }
};

template <class T, size_t N>
struct __array : __array_impl<T, N, make_index_sequence<N>>
{
  using base_t = __array_impl<T, N, make_index_sequence<N>>;
  using base_t::base_t;
};

} // end namespace __array_workaround
} // end namespace experimental
} // end namespace std

#endif //MDSPAN_INCLUDE_EXPERIMENTAL___P0009_BITS_ARRAY_WORKAROUND_HPP_
