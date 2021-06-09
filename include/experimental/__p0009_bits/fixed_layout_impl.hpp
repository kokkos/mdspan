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

#include "static_array.hpp"
#include "dynamic_extent.hpp"
#include "extents.hpp"
#include "trait_backports.hpp"

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#  include "no_unique_address.hpp"
#endif

#include <cstddef>
#include <array>

//==============================================================================================================

namespace std {
namespace experimental {
namespace detail {

//==============================================================================================================

template <class, class, class> struct __extents_storage_impl;

template <size_t... Exts, size_t... Idxs, class IdxConditional>
struct __extents_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  : __no_unique_address_emulation<experimental::extents<Exts...>>
#endif
{
protected:

#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS experimental::extents<Exts...> __extents_;
#else
  using __base_t = __no_unique_address_emulation<experimental::extents<Exts...>>;
#endif

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  experimental::extents<Exts...>& __extents() noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __extents_;
#else
    return this->__base_t::__ref();
#endif
  }
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr experimental::extents<Exts...> const& __extents() const noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __extents_;
#else
    return this->__base_t::__ref();
#endif
  }

public:

  using extents_type = experimental::extents<Exts...>;

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __extents_storage_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __extents_storage_impl(__extents_storage_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __extents_storage_impl(__extents_storage_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED __extents_storage_impl& operator=(__extents_storage_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED __extents_storage_impl& operator=(__extents_storage_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~__extents_storage_impl() noexcept = default;

  // The layouts need to be implicitly convertible from extents (as currently specified),
  // which means we need to make this not explicit here
  // TODO @proposal-bug make this explicit?
  MDSPAN_INLINE_FUNCTION
  constexpr /* implicit */ __extents_storage_impl(extents_type const& __exts) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __extents_{
#else
    : __base_t(__base_t{
#endif
        __exts
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      })
#endif
  { }

  // The layouts need to be implicitly convertible from extents (as currently specified),
  // which means we need to make this not explicit here
  // TODO @proposal-bug this one isn't in the proposal?
//  MDSPAN_INLINE_FUNCTION
//  constexpr /* implicit */ __extents_storage_impl(extents_type&& __exts) noexcept
//#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
//    : __extents_{
//#else
//    : __base_t(__base_t{
//#endif
//        std::move(__exts)
//#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
//      }
//#else
//      })
//#endif
//  { }

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr size_t get_stride() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, N) ? __extents().template __extent<Idxs>() : 1),
        /* * ... * */ 1
    );
  }

  MDSPAN_INLINE_FUNCTION
  constexpr size_t get_stride(size_t n) const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, n) ? __extents().template __extent<Idxs>() : 1),
        /* * ... * */ 1
    );
  }

};

//==============================================================================================================

template <class, class, class>
class fixed_layout_common_impl;

// TODO: We can probably make `__extents_storage_impl` a [[no_unique_address]]
// member instead of a base class.
template <size_t... Exts, size_t... Idxs, class IdxConditional>
class fixed_layout_common_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
  : protected __extents_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
{
private:

  using base_t = __extents_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>;

public:

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl(fixed_layout_common_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl(fixed_layout_common_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED fixed_layout_common_impl& operator=(fixed_layout_common_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED fixed_layout_common_impl& operator=(fixed_layout_common_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~fixed_layout_common_impl() noexcept = default;

  using base_t::base_t;

  MDSPAN_INLINE_FUNCTION constexpr typename base_t::extents_type extents() const noexcept {
    return typename base_t::extents_type(this->base_t::__extents());
  };

  template <class... Integral>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr size_t operator()(Integral... idxs) const noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT((idxs * this->base_t::template get_stride<Idxs>()), /* + ... + */ 0);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr size_t required_span_size() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((base_t::__extents().template __extent<Idxs>()), /* * ... * */ 1);
  }

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

  MDSPAN_INLINE_FUNCTION
  constexpr size_t stride(size_t r) const noexcept {
    return this->base_t::get_stride(r);
  }

  //--------------------------------------------------------------------------------

public:  // (but not really)

  template <size_t R>
  MDSPAN_INLINE_FUNCTION
  constexpr size_t __stride() const noexcept {
    return this->base_t::template get_stride<R>();
  }

  template <size_t N>
  struct __static_stride_workaround {
    static constexpr size_t __result = _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, N) ?
        base_t::__stored_type::template __static_extent<Idxs, 0>() : 1
      ), /* * ... * */ 1
    );
    static constexpr size_t value = __result == 0 ? dynamic_extent : __result;
  };

  template <size_t N>
  MDSPAN_INLINE_FUNCTION
  static constexpr size_t __static_stride() noexcept
  {
    return __static_stride_workaround<N>::value;
  }

};

//==============================================================================================================

} // namespace detail

} // end namespace experimental
} // namespace std
