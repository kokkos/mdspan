
#pragma once

#include "macros.hpp"
#include "fixed_layout_impl.hpp"

namespace std {

//==============================================================================

namespace detail {


struct layout_right_idx_conditional {
  constexpr inline bool operator()(size_t Idx, size_t N) const noexcept {
    return Idx > N;
  };
};

template <class, class> class layout_right_impl;

template <ptrdiff_t... Exts, size_t... Idxs>
class layout_right_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>>
  : public fixed_layout_common_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, layout_right_idx_conditional>
{
private:

  using base_t = fixed_layout_common_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, layout_right_idx_conditional>;
  using idx_seq = integer_sequence<size_t, Idxs...>;

  template <class, class>
  friend class layout_right_impl;

public:

  //--------------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION constexpr layout_right_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_right_impl(layout_right_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_right_impl(layout_right_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_right_impl& operator=(layout_right_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_right_impl& operator=(layout_right_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION ~layout_right_impl() noexcept = default;

  using base_t::base_t;

  // TODO conversion constructors and assignment

  //--------------------------------------------------------------------------------

  using base_t::extents;

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return true; }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return sizeof...(Exts) > 1; }

  // TODO constraints
  template <class OtherExtents, bool OtherStoreStrides>
  constexpr bool operator==(layout_right_impl<OtherExtents, idx_seq> const& other) const noexcept {
    return ((this->base_t::template __stride<Idxs>() == other.template __stride<Idxs>()) && ...); 
  }

  // TODO constraints
  template <class OtherExtents, bool OtherStoreStrides>
  constexpr bool operator!=(layout_right_impl<OtherExtents, idx_seq> const& other) const noexcept {
    return ((this->base_t::template __stride<Idxs>() != other.template __stride<Idxs>()) || ...); 
  }

};

} // namespace detail

//==============================================================================


struct layout_right {
  template <class Extents>
  using mapping = detail::layout_right_impl<
    Extents,
    make_index_sequence<Extents::rank()>
  >;
};
} // end namespace std