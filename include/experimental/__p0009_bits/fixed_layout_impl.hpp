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

#include "mixed_size_storage.hpp"
#include "dynamic_extent.hpp"
#include "extents.hpp"
#include "macros.hpp"

#include <type_traits>
#include <utility>
#include <cstddef>
#include <array>

//==============================================================================================================

namespace std {
namespace experimental {

namespace detail {

//==============================================================================================================

template <class Extents>
struct extents_storage
{
public:
  using extents_type = Extents;
protected:
  _MDSPAN_NO_UNIQUE_ADDRESS extents_type __extents = {};
public:
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents_storage() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents_storage(extents_storage const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents_storage(extents_storage&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED extents_storage& operator=(extents_storage const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED extents_storage& operator=(extents_storage&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~extents_storage() noexcept = default;

  MDSPAN_INLINE_FUNCTION
  constexpr extents_storage(extents_type const& exts)
    : __extents(exts)
  { }  

};

//==============================================================================================================

template <class, class, class> struct stride_storage_impl;

template <ptrdiff_t... Exts, size_t... Idxs, class IdxConditional>
struct stride_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
  : extents_storage<std::experimental::extents<Exts...>>
{
protected:
  using base_t = extents_storage<std::experimental::extents<Exts...>>;
public:

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr stride_storage_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr stride_storage_impl(stride_storage_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr stride_storage_impl(stride_storage_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED stride_storage_impl& operator=(stride_storage_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED stride_storage_impl& operator=(stride_storage_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~stride_storage_impl() noexcept = default;

  using base_t::base_t;

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t get_stride() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((IdxConditional{}(Idxs, N) ? base_t::__extents.template __extent<Idxs>() : 1), /* * ... * */ 1);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t get_stride(size_t n) const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((IdxConditional{}(Idxs, n) ? base_t::__extents.template __extent<Idxs>() : 1), /* * ... * */ 1);
  }

};

//==============================================================================================================

template <class, class, class>
class fixed_layout_common_impl;

template <ptrdiff_t... Exts, size_t... Idxs, class IdxConditional>
class fixed_layout_common_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
  : protected stride_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
{
private:

  using base_t = stride_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>;

public:

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl(fixed_layout_common_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl(fixed_layout_common_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED fixed_layout_common_impl& operator=(fixed_layout_common_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED fixed_layout_common_impl& operator=(fixed_layout_common_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~fixed_layout_common_impl() noexcept = default;

  using base_t::base_t;

  MDSPAN_INLINE_FUNCTION constexpr typename base_t::extents_type extents() const noexcept { return this->base_t::base_t::__extents; };

  template <class... Integral>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t operator()(Integral... idxs) const noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT((idxs * this->base_t::template get_stride<Idxs>()), /* + ... + */ 0);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t required_span_size() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((base_t::__extents.template __extent<Idxs>()), /* * ... * */ 1);
  }

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t stride(size_t r) const noexcept {
    return this->base_t::get_stride(r);
  }

  //--------------------------------------------------------------------------------

public:  // (but not really)

  template <size_t R>
  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t __stride() const noexcept {
    return this->base_t::template get_stride<R>();
  }

  template <size_t N>
  struct __static_stride_workaround {
    static constexpr ptrdiff_t __result = _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, N) ? base_t::extents_type::template __static_extent<Idxs, 0>() : 1), /* * ... * */ 1
    );
    static constexpr ptrdiff_t value = __result == 0 ? dynamic_extent : __result;
  };

  template <size_t N>
  MDSPAN_INLINE_FUNCTION
  static constexpr ptrdiff_t __static_stride() noexcept
  {
    return __static_stride_workaround<N>::value;
  }

};

//==============================================================================================================

} // namespace detail

} // end namespace experimental
} // namespace std