
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

template <class> class layout_right_impl;

template <ptrdiff_t... Exts>
class layout_right_impl<std::extents<Exts...>>
  : public fixed_layout_common_impl<std::extents<Exts...>, make_index_sequence<sizeof...(Exts)>, layout_right_idx_conditional>
{
private:

  using idx_seq = make_index_sequence<sizeof...(Exts)>;
  using base_t = fixed_layout_common_impl<std::extents<Exts...>, make_index_sequence<sizeof...(Exts)>, layout_right_idx_conditional>;

  template <class>
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

  // TODO noexcept specification
  MDSPAN_TEMPLATE_REQUIRES(
    class OtherExtents,
    /* requires */ (
      is_convertible_v<OtherExtents, std::extents<Exts...>>
    )
  )
  layout_right_impl(layout_right_impl<OtherExtents> const& other) // NOLINT(google-explicit-constructor)
    : base_t(other.extents())
  { }

  // TODO noexcept specification
  MDSPAN_TEMPLATE_REQUIRES(
    class OtherExtents,
      /* requires */ (
      is_convertible_v<OtherExtents, std::extents<Exts...>>
    )
  )
  layout_right_impl& operator=(layout_right_impl<OtherExtents> const& other)
  {
    this->_extents = other.extents();
    return *this;
  }
  //--------------------------------------------------------------------------------

  using base_t::extents;

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return true; }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return sizeof...(Exts) > 1; }

  // TODO @proposal-bug these (and other analogous operators) should be non-member functions
  template<class OtherExtents>
  MDSPAN_INLINE_FUNCTION
  constexpr bool operator==(layout_right_impl<OtherExtents> const& other) const noexcept {
    return this->base_t::extents() == other.extents();
  }

  template<class OtherExtents>
  MDSPAN_INLINE_FUNCTION
  constexpr bool operator!=(layout_right_impl<OtherExtents> const& other) const noexcept {
    return this->base_t::extents() != other.extents();
  }

};

} // namespace detail

//==============================================================================

struct layout_right {
  template <class Extents>
  using mapping = detail::layout_right_impl<Extents>;
};

} // end namespace std