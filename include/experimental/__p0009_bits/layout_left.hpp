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
#include "fixed_layout_impl.hpp"
#include "trait_backports.hpp"

namespace std {
namespace experimental {

//==============================================================================

namespace detail {

struct layout_left_idx_conditional {
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr layout_left_idx_conditional() noexcept = default;
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr bool operator()(size_t Idx, size_t N) const noexcept {
    return Idx < N;
  };
};

} // end namespace detail

struct layout_left {
  template <class Extents>
  class mapping
    : public detail::fixed_layout_common_impl<Extents, make_index_sequence<Extents::rank()>, detail::layout_left_idx_conditional>
  {
  private:

    static_assert(detail::__is_extents_v<Extents>, "std::experimental::layout_left::mapping must be instantiated with a specialization of std::experimental::extents.");

    using base_t = detail::fixed_layout_common_impl<Extents, make_index_sequence<Extents::rank()>, detail::layout_left_idx_conditional>;

    template <class>
    friend class mapping;

  public:

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED ~mapping() noexcept = default;

    using base_t::base_t;

    // TODO @proposal-bug This isn't a requirement of layouts in the proposal,
    // but we need it for `mdspan`'s deduction guides for its mapping
    // constructors.
    using layout = layout_left;

    // TODO @proposal-bug This isn't a requirement in the proposal.
    using typename base_t::extents_type;

    // This has to be here for CTAD; just inheriting the base class constructor
    // isn't sufficient.
    constexpr mapping(Extents const& __exts) noexcept
      : base_t(__exts)
    { }

    // TODO noexcept specification
    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_convertible, OtherExtents, Extents)
      )
    )
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(mapping<OtherExtents> const& other) // NOLINT(google-explicit-constructor)
      : base_t(other.extents())
    { }

    // TODO noexcept specification
    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_convertible, OtherExtents, Extents)
      )
    )
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping& operator=(mapping<OtherExtents> const& other)
    {
      this->base_t::__extents() = other.extents();
      return *this;
    }
    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() == rhs.extents();
    }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() != rhs.extents();
    }

  };
};

} // end namespace experimental
} // end namespace std
