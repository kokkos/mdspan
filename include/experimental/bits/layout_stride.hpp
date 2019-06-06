
#pragma once

#include "macros.hpp"
#include "fixed_layout_impl.hpp"
#include "mixed_size_storage.hpp"
#include "extents.hpp"

namespace std {

//==============================================================================

namespace detail {

template <class, class, class> class layout_stride_impl;

template <ptrdiff_t... Exts, ptrdiff_t... Strides, size_t... Idxs>
class layout_stride_impl<
  std::extents<Exts...>,
  integer_sequence<ptrdiff_t, Strides...>,
  integer_sequence<size_t, Idxs...>
>
  : extents_storage<std::extents<Exts...>>
{
private:

  using base_t = extents_storage<std::extents<Exts...>>;
  using idx_seq = integer_sequence<size_t, Idxs...>;

  using stride_storage_t = typename _make_mixed_impl<integer_sequence<ptrdiff_t, Strides...>>::type;

  [[no_unique_address]] stride_storage_t _strides;

  template <class, class, class>
  friend class layout_stride_impl;

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t __stride() const noexcept {
    return _strides.template get<N>();
  }

public:

  //--------------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl(layout_stride_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl(layout_stride_impl&&) noexcept = default;
  
  MDSPAN_INLINE_FUNCTION
  constexpr
  layout_stride_impl(
    std::extents<Exts...> const& e,
    array<ptrdiff_t, stride_storage_t::size_dynamic> const& strides
  ) noexcept
    : base_t(e),
      _strides(strides)
  { }      

  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl& operator=(layout_stride_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl& operator=(layout_stride_impl&&) noexcept = default;

  MDSPAN_INLINE_FUNCTION ~layout_stride_impl() noexcept = default;

  using base_t::base_t;

  // TODO conversion constructors and assignment

  //--------------------------------------------------------------------------------

  using base_t::extents;

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return false; }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return sizeof...(Exts) > 1; /* ??? */ }

  template <class... Integral>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t operator()(Integral... idxs) const noexcept {
    return ((idxs * __stride<Idxs>()) + ...);
  }

  template <class OtherExtents, class OtherStaticStrides>
  MDSPAN_INLINE_FUNCTION
  constexpr bool operator==(layout_stride_impl<OtherExtents, OtherStaticStrides, idx_seq> const& other) const noexcept {
    return (true && ... && (__stride<Idxs>() == other.template __stride<Idxs>())); 
  }

  template <class OtherExtents, class OtherStaticStrides>
  constexpr bool operator!=(layout_stride_impl<OtherExtents, OtherStaticStrides, idx_seq> const& other) const noexcept {
    return (false || ... || (__stride<Idxs>() != other.template __stride<Idxs>())); 
  }

};

} // namespace detail

//==============================================================================


template <ptrdiff_t... StaticStrides>
struct layout_stride {
  template <class Extents>
  using mapping = detail::layout_stride_impl<
    Extents,
    integer_sequence<ptrdiff_t, StaticStrides...>,
    make_index_sequence<Extents::rank()>
  >;
};
} // end namespace std