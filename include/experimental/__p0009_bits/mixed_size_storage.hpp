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

#include "dynamic_extent.hpp"
#include "trait_backports.hpp"
#include "array_workaround.hpp"

#include <cstddef> // ptrdiff_t
#include <utility> // integer_sequence
#include <array>

namespace std {
namespace experimental {
namespace detail {

_MDSPAN_INLINE_VARIABLE constexpr struct construct_mixed_storage_from_sizes_tag_t { } construct_mixed_storage_from_sizes_tag = { };

template <class SizesSeq, class, class=make_index_sequence<SizesSeq::size()>>
class mixed_static_and_dynamic_size_storage;

template <
  ptrdiff_t... Sizes,
  ptrdiff_t... DynamicOffsets,
  size_t... Idxs
>
class mixed_static_and_dynamic_size_storage<
  integer_sequence<ptrdiff_t, Sizes...>,
  integer_sequence<ptrdiff_t, DynamicOffsets...>,
  integer_sequence<size_t, Idxs...>
>
{
public:

  static constexpr auto size_dynamic =
    _MDSPAN_FOLD_PLUS_RIGHT(static_cast<int>((Sizes == dynamic_extent)), /* + ... + */ 0);

private:

  _MDSPAN_NO_UNIQUE_ADDRESS __array_workaround::__array<ptrdiff_t, size_dynamic> dynamic_sizes = { };

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t _select(true_type) const noexcept { return dynamic_sizes.template __get_n<DynamicOffset>(); }
  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t _select(false_type) const noexcept { return Size; }

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  MDSPAN_FORCE_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 ptrdiff_t _select_set(true_type, ptrdiff_t value) noexcept { dynamic_sizes.template __set_n<DynamicOffset>(value); return 0; }
  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  MDSPAN_FORCE_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 ptrdiff_t _select_set(false_type, ptrdiff_t) noexcept { return 0; }

public:

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t select() const noexcept {
    return _select<Size, DynamicOffset>(integral_constant<bool, Size == dynamic_extent>{});
  }

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset, size_t Idx, ptrdiff_t N, ptrdiff_t Default=dynamic_extent>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t select_n() const noexcept {
    return Idx == N ? _select<Size, DynamicOffset>(integral_constant<bool, Size == dynamic_extent>{}) : Default;
  }

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset, ptrdiff_t Default=dynamic_extent>
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr ptrdiff_t select_static() noexcept {
    return Size == dynamic_extent ? Default : Size;
  }

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset, size_t Idx, size_t N, ptrdiff_t Default=dynamic_extent, ptrdiff_t DefaultWrongIdx=Default>
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr ptrdiff_t select_static_n() noexcept {
    return (Idx == N) ? ((Size == dynamic_extent) ? Default : Size) : DefaultWrongIdx;
  }


  template <ptrdiff_t Size, ptrdiff_t DynamicOffset, size_t Idx, ptrdiff_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 ptrdiff_t select_set(ptrdiff_t value) noexcept {
    return _select_set<Size, DynamicOffset>(integral_constant<bool, Size == dynamic_extent && Idx == N>{}, value);
  }
 
 
  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t get() const noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT((select_n<Sizes, DynamicOffsets, Idxs, N, 0>()), /* + ... + */ 0);
  }

  template <size_t N, ptrdiff_t Default=dynamic_extent>
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr ptrdiff_t get_static() noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT((select_static_n<Sizes, DynamicOffsets, Idxs, N, Default, 0>()), /* + ... + */ 0);
  }

  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t get(size_t n) const noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT(((Idxs == n) ? select<Sizes, DynamicOffsets>() : 0), /* + ... + */ 0);
  }

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 __mdspan_enable_fold_comma
  set(ptrdiff_t value) noexcept {
    _MDSPAN_FOLD_COMMA(select_set<Sizes, DynamicOffsets, Idxs, N>(value) /* , ... */);
    return { };
  }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr mixed_static_and_dynamic_size_storage() = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr mixed_static_and_dynamic_size_storage(mixed_static_and_dynamic_size_storage const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr mixed_static_and_dynamic_size_storage(mixed_static_and_dynamic_size_storage&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED mixed_static_and_dynamic_size_storage& operator=(mixed_static_and_dynamic_size_storage const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED mixed_static_and_dynamic_size_storage& operator=(mixed_static_and_dynamic_size_storage&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~mixed_static_and_dynamic_size_storage() noexcept = default;

  template <class... Integral>
  MDSPAN_INLINE_FUNCTION
  constexpr mixed_static_and_dynamic_size_storage(construct_mixed_storage_from_sizes_tag_t, Integral... dyn_sizes)
    : dynamic_sizes(ptrdiff_t{dyn_sizes}...)
  { }

  template <ptrdiff_t... USizes, ptrdiff_t... UDynOffs, size_t... UIdxs>
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 mixed_static_and_dynamic_size_storage(
    mixed_static_and_dynamic_size_storage<
      std::integer_sequence<ptrdiff_t, USizes...>,
      std::integer_sequence<ptrdiff_t, UDynOffs...>,
      std::integer_sequence<size_t, UIdxs...>
    > const& other
  ) : dynamic_sizes()
  {
    _MDSPAN_FOLD_COMMA(set<Idxs>(other.template get<Idxs>()) /* , ... */);
  }

  template <class Integral>
  MDSPAN_INLINE_FUNCTION
  constexpr mixed_static_and_dynamic_size_storage(std::array<Integral, size_dynamic> const& dyn)
    : dynamic_sizes(dyn)
  { }

};

//================================================================================

template <size_t N, class, class> struct _make_mixed_impl_helper;
template <size_t N, size_t... Idxs, ptrdiff_t... Sizes>
struct _make_mixed_impl_helper<N, integer_sequence<size_t, Idxs...>, integer_sequence<ptrdiff_t, Sizes...>> {
  static constexpr ptrdiff_t value =
    _MDSPAN_FOLD_PLUS_RIGHT((int(Idxs < size_t(N) && Sizes == dynamic_extent)), /* + ... + */ 0);
};

template <class Sequence, class=void>
struct _make_mixed_impl;
template <class T, T... Sizes>
struct _make_mixed_impl<integer_sequence<T, Sizes...>, void>
  : _make_mixed_impl<integer_sequence<T, Sizes...>, std::make_index_sequence<sizeof...(Sizes)>>
{ };
template <class T, T... Sizes, size_t... Idxs>
struct _make_mixed_impl<integer_sequence<T, Sizes...>, integer_sequence<size_t, Idxs...>> {
  using type = mixed_static_and_dynamic_size_storage<
      integer_sequence<ptrdiff_t, Sizes...>,
      integer_sequence<ptrdiff_t,
        _make_mixed_impl_helper<
          Idxs, std::index_sequence<Idxs...>, std::integer_sequence<ptrdiff_t, Sizes...>
        >::value...
      >
    >;
};

} // namespace detail
} // end namespace experimental
} // namespace std
