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
#include "mixed_size_storage.hpp"
#include "trait_backports.hpp"

#include <cstddef>

namespace std {
namespace experimental {

namespace detail {

template <ptrdiff_t... Extents, ptrdiff_t... OtherExtents>
static constexpr std::false_type _check_compatible_extents(
  std::false_type, std::integer_sequence<ptrdiff_t, Extents...>, std::integer_sequence<ptrdiff_t, OtherExtents...>
) noexcept { return { }; }
template <ptrdiff_t... Extents, ptrdiff_t... OtherExtents>
static std::integral_constant<
  bool,
  _MDSPAN_FOLD_AND(
    (
      Extents == dynamic_extent
        || OtherExtents == dynamic_extent
        || Extents == OtherExtents
    ) /* && ... */
  )
>
_check_compatible_extents(
  std::true_type, std::integer_sequence<ptrdiff_t, Extents...>, std::integer_sequence<ptrdiff_t, OtherExtents...>
) noexcept { return { }; }

} // end namespace detail

template <ptrdiff_t... Extents>
class extents
{
public:

  using index_type = ptrdiff_t;

private:

  using storage_type = typename detail::_make_mixed_impl<integer_sequence<ptrdiff_t, Extents...>>::type;

  template <size_t... Idxs>
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr
  index_type _static_extent_impl(size_t n, std::integer_sequence<size_t, Idxs...>) noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT(((Idxs == n) ? Extents : 0), /* + ... + */ 0);
  }

  template <ptrdiff_t...>
  friend class extents;


  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(std::experimental::extents<OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return false; }
  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(
    std::experimental::extents<OtherExtents...> other,
    true_type, index_sequence<Idxs...>
  ) const noexcept {
    return _MDSPAN_FOLD_AND((_storage.template get<Idxs>() == other._storage.template get<Idxs>()) /* && ... */);
  }

  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(std::experimental::extents<OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return true; }
  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(
    std::experimental::extents<OtherExtents...> other,
    true_type, index_sequence<Idxs...>
  ) const noexcept {
    return _MDSPAN_FOLD_OR((_storage.template get<Idxs>() != other._storage.template get<Idxs>()) /* || ... */);
  }

public:

  MDSPAN_INLINE_FUNCTION
  static constexpr size_t rank() noexcept { return sizeof...(Extents); }
  MDSPAN_INLINE_FUNCTION
  static constexpr size_t rank_dynamic() noexcept { return _MDSPAN_FOLD_PLUS_RIGHT((int(Extents == dynamic_extent)), /* + ... + */ 0); }

  //--------------------------------------------------------------------------------
  // Constructors, Destructors, and Assignment

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED extents& operator=(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED extents& operator=(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~extents() noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    ptrdiff_t... OtherExtents,
    /* requires */ (
      /* multi-stage check to protect from invalid pack expansion when sizes don't match? */
      decltype(detail::_check_compatible_extents(
        std::integral_constant<bool, sizeof...(Extents) == sizeof...(OtherExtents)>{},
        std::integer_sequence<ptrdiff_t, Extents...>{},
        std::integer_sequence<ptrdiff_t, OtherExtents...>{}
      ))::value
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(const extents<OtherExtents...>& other)
    noexcept
    : _storage(other._storage)
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class... Integral,
    /* requires */ (
      _MDSPAN_FOLD_AND(std::_MDSPAN_TRAIT(is_convertible, Integral, index_type) /* && ... */) && sizeof...(Integral) == rank_dynamic()
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr explicit extents(Integral... dyn) noexcept
    : _storage(detail::construct_mixed_storage_from_sizes_tag, dyn...)
  { }


  // TODO @proposal-bug this constructor should be explicit
  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, IndexType, index_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(std::array<IndexType, storage_type::size_dynamic> const& dyn) noexcept
    : _storage(dyn)
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    ptrdiff_t... OtherExtents,
    /* requires */ (
      /* multi-stage check to protect from invalid pack expansion when sizes don't match? */
      decltype(detail::_check_compatible_extents(
        std::integral_constant<bool, sizeof...(Extents) == sizeof...(OtherExtents)>{},
        std::integer_sequence<ptrdiff_t, Extents...>{},
        std::integer_sequence<ptrdiff_t, OtherExtents...>{}
      ))::value
    )
  )
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 extents& operator=(const extents<OtherExtents...>& other) noexcept
  {
    _storage = other._storage;
    return *this;
  }

  //--------------------------------------------------------------------------------
  
  MDSPAN_INLINE_FUNCTION
  static constexpr
  index_type static_extent(size_t n) noexcept {
    return _static_extent_impl(n, std::make_integer_sequence<size_t, sizeof...(Extents)>{});
  }

  MDSPAN_INLINE_FUNCTION
  constexpr
  index_type extent(size_t n) const noexcept {
    return _storage.get(n);
  }

  //--------------------------------------------------------------------------------

  template<ptrdiff_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator==(extents const& lhs, extents<RHS...> const& rhs) noexcept {
    return lhs._eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(Extents) == sizeof...(RHS))>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }

  template<ptrdiff_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator!=(extents const& lhs, extents<RHS...> const& rhs) noexcept {
    return lhs._not_eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(Extents) == sizeof...(RHS))>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }

public:  // (but not really)

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr
  index_type __extent() const noexcept {
    return _storage.template get<N>();
  }

  template <size_t N, ptrdiff_t Default=dynamic_extent>
  MDSPAN_INLINE_FUNCTION
  static constexpr
  index_type __static_extent() noexcept {
    return storage_type::template get_static<N, Default>();
  }

private:

  _MDSPAN_NO_UNIQUE_ADDRESS storage_type _storage = { };

};

} // end namespace experimental
} // namespace std
