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
#include "mixed_size_storage.hpp"
#include "extents.hpp"

#include <algorithm>
#include <numeric>
#include <array>

namespace std {
namespace experimental {

//==============================================================================

namespace detail {

template <class, ptrdiff_t...> class layout_stride_impl;

template <ptrdiff_t... Exts, ptrdiff_t... Strides>
class layout_stride_impl<
  std::experimental::extents<Exts...>, Strides...
>
  : public extents_storage<std::experimental::extents<Exts...>>
{
private:

  using base_t = extents_storage<std::experimental::extents<Exts...>>;
  using idx_seq = make_index_sequence<sizeof...(Exts)>;

  using stride_storage_t = typename _make_mixed_impl<integer_sequence<ptrdiff_t, Strides...>>::type;

  template <class, ptrdiff_t...>
  friend class layout_stride_impl;

  // Workaround for non-deducibility of the index sequence template parameter if it's given at the top level
  template <class=make_index_sequence<sizeof...(Exts)>>
  struct __impl;

  template <size_t... Idxs>
  struct __impl<index_sequence<Idxs...>>
  {
    template <class OtherExtents, ptrdiff_t... OtherStrides>
    MDSPAN_INLINE_FUNCTION
    static constexpr bool _eq_impl(layout_stride_impl const& self, layout_stride_impl<OtherExtents, OtherStrides...> const& other) noexcept {
      return _MDSPAN_FOLD_AND((self.template __stride<Idxs>() == other.template __stride<Idxs>()) /* && ... */);
    }
    template <class OtherExtents, ptrdiff_t... OtherStrides>
    MDSPAN_INLINE_FUNCTION
    static constexpr bool _not_eq_impl(layout_stride_impl const& self, layout_stride_impl<OtherExtents, OtherStrides...> const& other) noexcept {
      return _MDSPAN_FOLD_OR((self.template __stride<Idxs>() != other.template __stride<Idxs>()) /* || ... */);
    }

    template <class... Integral>
    MDSPAN_FORCE_INLINE_FUNCTION
    static constexpr ptrdiff_t _call_op_impl(layout_stride_impl const& self, Integral... idxs) noexcept {
      return _MDSPAN_FOLD_PLUS_RIGHT((idxs * self.template __stride<Idxs>()), /* + ... + */ 0);
    }

    MDSPAN_INLINE_FUNCTION
    static constexpr size_t _req_span_size_impl(layout_stride_impl const& self) noexcept {
      // assumes no negative strides; not sure if I'm allowed to assume that or not
      return __impl::_call_op_impl(self, (self.extents().template __extent<Idxs>() - 1)...) + 1;
    }
  };

public: // (but not really)

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t __stride() const noexcept {
    return _strides.template get<N>();
  }

  template <size_t N>
  struct __static_stride_workaround {
    static constexpr ptrdiff_t value =  stride_storage_t::template get_static<N, dynamic_extent>();
  };

  template <size_t N>
  MDSPAN_INLINE_FUNCTION
  static constexpr ptrdiff_t __static_stride() noexcept
  {
    return stride_storage_t::template get_static<N>();
  }

public:

  //--------------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr layout_stride_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr layout_stride_impl(layout_stride_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr layout_stride_impl(layout_stride_impl&&) noexcept = default;

  // TODO @proposal-bug layout stride needs this constructor
  MDSPAN_INLINE_FUNCTION
  constexpr
  layout_stride_impl(
    std::experimental::extents<Exts...> const& e,
    array<ptrdiff_t, stride_storage_t::size_dynamic> const& strides
  ) noexcept
    : base_t(e),
      _strides(strides)
  { }      

  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED layout_stride_impl& operator=(layout_stride_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED layout_stride_impl& operator=(layout_stride_impl&&) noexcept = default;

  MDSPAN_INLINE_FUNCTION_DEFAULTED ~layout_stride_impl() noexcept = default;

  using base_t::base_t;

  // TODO conversion constructors and assignment

  //--------------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION constexpr typename base_t::extents_type extents() const noexcept { return this->base_t::__extents; };

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
  // TODO @proposal-bug this wording for this is (at least slightly) broken (should at least be "... stride(p[0]) == 1...")
  MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 bool is_contiguous() const noexcept {
    // TODO @testing test layout_stride is_contiguous()
    auto rem = std::array<ptrdiff_t, sizeof...(Exts)>{ };
    std::iota(rem.begin(), rem.end(), ptrdiff_t(0));
    auto next_idx_iter = std::find_if(
      rem.begin(), rem.end(),
      [&](ptrdiff_t i) { _strides.get(i) == 1;  }
    );
    if(next_idx_iter != rem.end()) {
      ptrdiff_t prev_stride_times_prev_extent =
        this->extents().extent(*next_idx_iter) * _strides.get(*next_idx_iter);
      // "remove" the index
      constexpr ptrdiff_t removed_index_sentinel = -1;
      *next_idx_iter = removed_index_sentinel;
      int found_count = 1;
      while (found_count != sizeof...(Exts)) {
        next_idx_iter = std::find_if(
          rem.begin(), rem.end(),
          [&](ptrdiff_t i) {
            return i != removed_index_sentinel
              && _strides.get(i) * this->extents().extent(i) == prev_stride_times_prev_extent;
          }
        );
        if (next_idx_iter != rem.end()) {
          // "remove" the index
          *next_idx_iter = removed_index_sentinel;
          ++found_count;
          prev_stride_times_prev_extent = _strides.get(*next_idx_iter) * this->extents().extent(*next_idx_iter);
        } else { break; }
      }
      return found_count == sizeof...(Exts);
    }
    return false;
  }
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept {
    // TODO @proposal-bug this will need to be updated with the incorporation of static strides into the layout stride definition
    // TODO this should actually check whether we know statically from the strides if this is always contiguous
    return false;
  }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

  MDSPAN_TEMPLATE_REQUIRES(
    class... Indices,
    /* requires */ (
      sizeof...(Indices) == sizeof...(Exts) &&
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_constructible, Indices, ptrdiff_t) /*&& ...*/)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t operator()(Indices... idxs) const noexcept {
    return __impl<>::_call_op_impl(*this, idxs...);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t stride(size_t r) const noexcept {
    return _strides.get(r);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t required_span_size() const noexcept {
    // assumes no negative strides; not sure if I'm allowed to assume that or not
    return __impl<>::_req_span_size_impl(*this);
  }

  // TODO @proposal-bug these (and other analogous operators) should be non-member functions
  // TODO @proposal-bug these should do more than just compare extents!

  template<class OtherExtents, ptrdiff_t... OtherStaticStrides>
  MDSPAN_INLINE_FUNCTION
  constexpr bool operator==(layout_stride_impl<OtherExtents, OtherStaticStrides...> const& other) const noexcept {
    return __impl<>::_eq_impl(*this, other);
  }

  template<class OtherExtents, ptrdiff_t... OtherStaticStrides>
  MDSPAN_INLINE_FUNCTION
  constexpr bool operator!=(layout_stride_impl<OtherExtents, OtherStaticStrides...> const& other) const noexcept {
    return __impl<>::_not_eq_impl(*this, other);
  }

private:

  _MDSPAN_NO_UNIQUE_ADDRESS stride_storage_t _strides = { };

};

} // namespace detail

//==============================================================================


// TODO @proposal-bug layout_stride needs these non-type template parameters
template <ptrdiff_t... StaticStrides>
struct layout_stride {
  template <class Extents>
  using mapping = detail::layout_stride_impl<
    Extents, StaticStrides...
  >;
};

} // end namespace experimental
} // end namespace std