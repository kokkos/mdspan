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

#include "accessor_basic.hpp"
#include "layout_right.hpp"
#include "extents.hpp"
#include "trait_backports.hpp"

#include <utility> // make_index_sequence
#include <tuple> // std::apply

namespace std {
namespace experimental {


template <
  class ElementType,
  class Extents,
  class LayoutPolicy = layout_right,
  class AccessorPolicy = accessor_basic<ElementType>
>
class basic_mdspan;


template <
  class ElementType,
  ptrdiff_t... Exts,
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
  // Workaround for non-deducibility of the index sequence template parameter if it's given at the top level
  template <class=make_index_sequence<sizeof...(Exts)>>
  struct __impl;

  template <size_t... Idxs>
  struct __impl<index_sequence<Idxs...>>
  {
    MDSPAN_FORCE_INLINE_FUNCTION static constexpr
    ptrdiff_t __size(basic_mdspan const& __self) noexcept {
      return _MDSPAN_FOLD_TIMES_RIGHT((__self.map_.extents().template __extent<Idxs>()), /* * ... * */ 1);
    }
    template <class ReferenceType, class IndexType, size_t N>
    MDSPAN_FORCE_INLINE_FUNCTION static constexpr
    ReferenceType __callop(basic_mdspan const& __self, const array<IndexType, N>& indices) noexcept {
      return __self.acc_.access(__self.ptr_, __self.map_(indices[Idxs]...));
    }
  };

public:
  
  //--------------------------------------------------------------------------------
  // Domain and codomain types

  using extents_type = std::experimental::extents<Exts...>;
  using layout_type = LayoutPolicy;
  using accessor_type = AccessorPolicy;
  using mapping_type = typename layout_type::template mapping<extents_type>;
  using element_type = ElementType;
  using value_type = remove_cv_t<element_type>;
  using index_type = ptrdiff_t;
  using difference_type = ptrdiff_t;
  using pointer = typename accessor_type::pointer;
  using reference = typename accessor_type::reference;

  //--------------------------------------------------------------------------------
  // [mdspan.basic.cons], basic_mdspan constructors, assignment, and destructor

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr basic_mdspan() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr basic_mdspan(const basic_mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr basic_mdspan(basic_mdspan&&) noexcept = default;

  // TODO noexcept specification
  MDSPAN_TEMPLATE_REQUIRES(
    class... IndexType,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, IndexType, index_type) /* && ... */) &&
      (sizeof...(IndexType) == extents_type::rank_dynamic()) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr basic_mdspan(pointer p, IndexType... dynamic_extents)
    noexcept
    // TODO @proposal-bug shouldn't I be allowed to do `move(p)` here?
    : ptr_(p),
      map_(extents_type(dynamic_extents...)),
      acc_()
  { }

  // TODO noexcept specification
  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, IndexType, index_type) &&
      (N == extents_type::rank_dynamic()) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr basic_mdspan(pointer p, const array<IndexType, N>& dynamic_extents)
    noexcept
    : ptr_(p),
      map_(extents_type(dynamic_extents)),
      acc_()
  { }

  // TODO noexcept specification
  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    basic_mdspan, (pointer p, const mapping_type& m), noexcept,
    /* requires */ (_MDSPAN_TRAIT(is_default_constructible, accessor_type))
  ) : ptr_(p),
      map_(m),
      acc_()
  { }

  // TODO noexcept specification
  MDSPAN_INLINE_FUNCTION
  constexpr basic_mdspan(pointer p, const mapping_type& m, const accessor_type& a) noexcept
    : ptr_(p),
      map_(m),
      acc_(a)
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
    : ptr_(other.ptr_),
      map_(other.map_),
      acc_(other.acc_)
  { }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~basic_mdspan() noexcept = default;

  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED basic_mdspan& operator=(const basic_mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED basic_mdspan& operator=(basic_mdspan&&) noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, ptrdiff_t... OtherExtents, class OtherLayoutPolicy, class OtherAccessorPolicy,
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
    ptr_ = other.ptr_;
    map_ = other.map_;
    acc_ = other.acc_;
    return *this;
  }

  //--------------------------------------------------------------------------------
  // [mdspan.basic.mapping], basic_mdspan mapping domain multidimensional index to access codomain element

  MDSPAN_TEMPLATE_REQUIRES(
    class Index,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, Index, index_type) &&
      sizeof...(Exts) == 1
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](Index idx) const noexcept
  {
    return acc_.access(ptr_, map_(index_type(idx)));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class... IndexType,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, IndexType, index_type) /* && ... */) &&
      sizeof...(Exts) == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(IndexType... indices) const noexcept
  {
    return acc_.access(ptr_, map_(index_type(indices)...));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, IndexType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(const array<IndexType, N>& indices) const noexcept
  {
    return __impl<>::template __callop<reference>(*this, indices);
  }

  MDSPAN_INLINE_FUNCTION
  accessor_type accessor() const { return acc_; };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.domobs], basic_mdspan observers of the domain multidimensional index space

  MDSPAN_INLINE_FUNCTION static constexpr int rank() noexcept { return extents_type::rank(); }
  MDSPAN_INLINE_FUNCTION static constexpr int rank_dynamic() noexcept { return extents_type::rank_dynamic(); }
  MDSPAN_INLINE_FUNCTION static constexpr index_type static_extent(size_t r) noexcept { return extents_type::static_extent(r); }

  MDSPAN_INLINE_FUNCTION constexpr extents_type extents() const noexcept { return map_.extents(); };
  MDSPAN_INLINE_FUNCTION constexpr index_type extent(size_t r) const noexcept { return map_.extents().extent(r); };
  MDSPAN_INLINE_FUNCTION constexpr index_type size() const noexcept {
    return __impl<>::__size(*this);
  };

  // TODO @proposal-bug for non-unique, non-contiguous mappings this is unimplementable
  MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 index_type unique_size() const noexcept {
    if(map_.is_unique()) {
      return size();
    }
    else if(map_.is_contiguous()) {
      return map_.required_span_size();
    }
    else {
      // ??? guess, for now, until this gets fixed in the proposal ???
      return map_.required_span_size();
    }
  }

  // [mdspan.basic.codomain], basic_mdspan observers of the codomain
  // TODO span (or just `codomain` function, as discussed)
  // constexpr span<element_type> span() const noexcept;

  MDSPAN_INLINE_FUNCTION constexpr pointer data() const noexcept { return ptr_; };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.obs], basic_mdspan observers of the mapping

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return mapping_type::is_always_contiguous(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return mapping_type::is_always_strided(); };

  MDSPAN_INLINE_FUNCTION constexpr mapping_type mapping() const noexcept { return map_; };
  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return map_.is_unique(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return map_.is_contiguous(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return map_.is_strided(); };
  MDSPAN_INLINE_FUNCTION constexpr index_type stride(size_t r) const { return map_.stride(r); };

private:

  pointer ptr_ = nullptr;
  _MDSPAN_NO_UNIQUE_ADDRESS mapping_type map_;
  _MDSPAN_NO_UNIQUE_ADDRESS accessor_type acc_;

  template <class, class, class, class>
  friend class basic_mdspan;

};


template <class T, ptrdiff_t... Exts>
using mdspan = basic_mdspan<T, std::experimental::extents<Exts...>>;

} // end namespace experimental
} // end namespace std
