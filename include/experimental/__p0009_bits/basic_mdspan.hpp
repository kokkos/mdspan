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

#include "default_accessor.hpp"
#include "layout_right.hpp"
#include "extents.hpp"
#include "trait_backports.hpp"

namespace std {
namespace experimental {


template <
  class ElementType,
  class Extents,
  class LayoutPolicy = layout_right,
  class AccessorPolicy = default_accessor<ElementType>
>
class basic_mdspan;


template <
  class ElementType,
  size_t... Exts,
  class LayoutPolicy,
  class AccessorPolicy
>
class basic_mdspan<
  ElementType,
  std::experimental::extents<Exts...>,
  LayoutPolicy,
  AccessorPolicy
>
{
private:

  using __mapping_base_t = detail::__no_unique_address_emulation<
    typename LayoutPolicy::template mapping<experimental::extents<Exts...>>, 0>;
  using __accessor_base_t = detail::__no_unique_address_emulation<AccessorPolicy, 1>;

  // Workaround for non-deducibility of the index sequence template parameter if it's given at the top level
  template <class>
  struct __impl_impl;

  template <size_t... Idxs>
  struct __impl_impl<index_sequence<Idxs...>>
  {
    MDSPAN_FORCE_INLINE_FUNCTION static constexpr
    size_t __size(basic_mdspan const& __self) noexcept {
      return _MDSPAN_FOLD_TIMES_RIGHT((__self.__mapping_ref().extents().template __extent<Idxs>()), /* * ... * */ 1);
    }
    template <class ReferenceType, class SizeType, size_t N>
    MDSPAN_FORCE_INLINE_FUNCTION static constexpr
    ReferenceType __callop(basic_mdspan const& __self, const array<SizeType, N>& indices) noexcept {
      return __self.__accessor_ref().access(__self.__ptr_ref(), __self.__mapping_ref()(indices[Idxs]...));
    }
  };

  // Can't use defaulted parameter in the __impl_impl template because of a bug in MSVC warning C4348.
  using __impl = __impl_impl<make_index_sequence<sizeof...(Exts)>>;

public:

  //--------------------------------------------------------------------------------
  // Domain and codomain types

  using extents_type = std::experimental::extents<Exts...>;
  using layout_type = LayoutPolicy;
  using accessor_type = AccessorPolicy;
  using mapping_type = typename layout_type::template mapping<extents_type>;
  using element_type = ElementType;
  using value_type = remove_cv_t<element_type>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = typename accessor_type::pointer;
  using reference = typename accessor_type::reference;

private:

  using __map_acc_pair_t = detail::__compressed_pair<mapping_type, accessor_type>;

public:

  //--------------------------------------------------------------------------------
  // [mdspan.basic.cons], basic_mdspan constructors, assignment, and destructor

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr basic_mdspan() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr basic_mdspan(const basic_mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr basic_mdspan(basic_mdspan&&) noexcept = default;

  // TODO noexcept specification
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, size_type) /* && ... */) &&
      (sizeof...(SizeTypes) == extents_type::rank_dynamic()) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr basic_mdspan(pointer p, SizeTypes... dynamic_extents)
    noexcept
    // TODO @proposal-bug shouldn't I be allowed to do `move(p)` here?
    : __members(p, __map_acc_pair_t(mapping_type(extents_type(dynamic_extents...)), accessor_type()))
  { }

  // TODO noexcept specification
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, size_type) &&
      (N == extents_type::rank_dynamic()) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr basic_mdspan(pointer p, const array<SizeType, N>& dynamic_extents)
    noexcept
    : __members(p, __map_acc_pair_t(mapping_type(extents_type(dynamic_extents)), accessor_type()))
  { }

  // TODO noexcept specification
  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    basic_mdspan, (pointer p, const mapping_type& m), noexcept,
    /* requires */ (_MDSPAN_TRAIT(is_default_constructible, accessor_type))
  ) : __members(p, __map_acc_pair_t(m, accessor_type()))
  { }

  // TODO noexcept specification
  MDSPAN_INLINE_FUNCTION
  constexpr basic_mdspan(pointer p, const mapping_type& m, const accessor_type& a) noexcept
    : __members(p, __map_acc_pair_t(m, a))
  { }

  // TODO noexcept specification
  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherAccessor,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, typename OtherLayoutPolicy::template mapping<OtherExtents>, mapping_type) &&
      _MDSPAN_TRAIT(is_convertible, OtherAccessor, accessor_type) &&
      _MDSPAN_TRAIT(is_convertible, typename OtherAccessor::pointer, pointer) &&
      // TODO @proposal-bug there is a redundant constraint in the proposal; the convertibility of the extents is effectively stated twice
      _MDSPAN_TRAIT(is_convertible, OtherExtents, extents_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr basic_mdspan(const basic_mdspan<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>& other)
    : __members(other.__ptr_ref(), __map_acc_pair_t(other.__mapping_ref(), other.__accessor_ref()))
  { }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~basic_mdspan() noexcept = default;

  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED basic_mdspan& operator=(const basic_mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED basic_mdspan& operator=(basic_mdspan&&) noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, size_t... OtherExtents, class OtherLayoutPolicy, class OtherAccessorPolicy,
    /* requires */ (
      _MDSPAN_TRAIT(is_assignable, mapping_type, typename OtherLayoutPolicy::template mapping<std::experimental::extents<OtherExtents...>>) &&
      _MDSPAN_TRAIT(is_assignable, accessor_type, OtherAccessorPolicy) &&
      _MDSPAN_TRAIT(is_assignable, pointer, typename OtherAccessorPolicy::pointer) &&
      sizeof...(OtherExtents) == extents_type::rank() &&
      // "For all r in the range [0, rank()), if other.static_extent(r) != dynamic_extent
      //   && static_extent(r) != dynamic_extent is true, then
      //   other.static_extent(r) == static_extent(r) is true."
      // (this is just the convertiblity constraint on extents...)
      _MDSPAN_TRAIT(is_convertible, std::experimental::extents<Exts...>, std::experimental::extents<OtherExtents...>)
    )
  )
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 basic_mdspan& operator=(
    const basic_mdspan<OtherElementType, std::experimental::extents<OtherExtents...>, OtherLayoutPolicy, OtherAccessorPolicy>& other
  ) noexcept(/* TODO noexcept specification */ true)
  {
    __ptr_ref() = other.__ptr_ref();
    __mapping_ref() = other.__mapping_ref();
    __accessor_ref() = other.__accessor_ref();
    return *this;
  }

  //--------------------------------------------------------------------------------
  // [mdspan.basic.mapping], basic_mdspan mapping domain multidimensional index to access codomain element

  MDSPAN_TEMPLATE_REQUIRES(
    class Index,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, Index, size_type) &&
      sizeof...(Exts) == 1
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](Index idx) const noexcept
  {
    return __accessor_ref().access(__ptr_ref(), __mapping_ref()(size_type(idx)));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, size_type) /* && ... */) &&
      sizeof...(Exts) == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(SizeTypes... indices) const noexcept
  {
    return __accessor_ref().access(__ptr_ref(), __mapping_ref()(size_type(indices)...));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, size_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(const array<SizeType, N>& indices) const noexcept
  {
    return __impl::template __callop<reference>(*this, indices);
  }

  // TODO @proposal-bug The proposal is missing constexpr here
  MDSPAN_INLINE_FUNCTION constexpr
  accessor_type accessor() const { return __accessor_ref(); };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.domobs], basic_mdspan observers of the domain multidimensional index space

  MDSPAN_INLINE_FUNCTION static constexpr int rank() noexcept { return extents_type::rank(); }
  MDSPAN_INLINE_FUNCTION static constexpr int rank_dynamic() noexcept { return extents_type::rank_dynamic(); }
  MDSPAN_INLINE_FUNCTION static constexpr size_type static_extent(size_t r) noexcept { return extents_type::static_extent(r); }

  MDSPAN_INLINE_FUNCTION constexpr extents_type extents() const noexcept { return __mapping_ref().extents(); };
  MDSPAN_INLINE_FUNCTION constexpr size_type extent(size_t r) const noexcept { return __mapping_ref().extents().extent(r); };
  MDSPAN_INLINE_FUNCTION constexpr size_type size() const noexcept {
    return __impl::__size(*this);
  };

  // TODO @proposal-bug for non-unique, non-contiguous mappings this is unimplementable
  MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 size_type unique_size() const noexcept {
    if(__mapping_ref().is_unique()) {
      return size();
    }
    else if(__mapping_ref().is_contiguous()) {
      return __mapping_ref().required_span_size();
    }
    else {
      // ??? guess, for now, until this gets fixed in the proposal ???
      return __mapping_ref().required_span_size();
    }
  }

  // [mdspan.basic.codomain], basic_mdspan observers of the codomain
  // TODO span (or just `codomain` function, as discussed)
  // constexpr span<element_type> span() const noexcept;

  MDSPAN_INLINE_FUNCTION constexpr pointer data() const noexcept { return __ptr_ref(); };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.obs], basic_mdspan observers of the mapping

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return mapping_type::is_always_contiguous(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return mapping_type::is_always_strided(); };

  MDSPAN_INLINE_FUNCTION constexpr mapping_type mapping() const noexcept { return __mapping_ref(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return __mapping_ref().is_unique(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return __mapping_ref().is_contiguous(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return __mapping_ref().is_strided(); };
  MDSPAN_INLINE_FUNCTION constexpr size_type stride(size_t r) const { return __mapping_ref().stride(r); };

private:

  detail::__compressed_pair<pointer, __map_acc_pair_t> __members;

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 pointer& __ptr_ref() noexcept { return __members.__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr pointer const& __ptr_ref() const noexcept { return __members.__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 mapping_type& __mapping_ref() noexcept { return __members.__second().__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr mapping_type const& __mapping_ref() const noexcept { return __members.__second().__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 accessor_type& __accessor_ref() noexcept { return __members.__second().__second(); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr accessor_type const& __accessor_ref() const noexcept { return __members.__second().__second(); }

  template <class, class, class, class>
  friend class basic_mdspan;

};

#if _MDSPAN_USE_DEDUCTION_GUIDES
namespace detail {

template <class>
constexpr auto __make_dynamic_extent() {
  return dynamic_extent;
}

} // end namespace detail

template <class ElementType, class... Integrals>
explicit basic_mdspan(ElementType*, Integrals...)
  -> basic_mdspan<ElementType, extents<detail::__make_dynamic_extent<Integrals>()...>>;
#endif

template <class T, size_t... Exts>
using mdspan = basic_mdspan<T, std::experimental::extents<Exts...>>;

} // end namespace experimental
} // end namespace std
