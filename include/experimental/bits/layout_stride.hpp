
#pragma once

#include "macros.hpp"
#include "fixed_layout_impl.hpp"
#include "mixed_size_storage.hpp"
#include "extents.hpp"

namespace std {

//==============================================================================

namespace detail {

template <class, ptrdiff_t...> class layout_stride_impl;

template <ptrdiff_t... Exts, ptrdiff_t... Strides>
class layout_stride_impl<
  std::extents<Exts...>, Strides...
>
  : extents_storage<std::extents<Exts...>>
{
private:

  using base_t = extents_storage<std::extents<Exts...>>;
  using idx_seq = make_index_sequence<sizeof...(Exts)>;

  using stride_storage_t = typename _make_mixed_impl<integer_sequence<ptrdiff_t, Strides...>>::type;

  [[no_unique_address]] stride_storage_t _strides;

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
      return ((self.template __stride<Idxs>() == other.template __stride<Idxs>()) && ...);
    }
    template <class OtherExtents, ptrdiff_t... OtherStrides>
    MDSPAN_INLINE_FUNCTION
    static constexpr bool _not_eq_impl(layout_stride_impl const& self, layout_stride_impl<OtherExtents, OtherStrides...> const& other) noexcept {
      return ((self.template __stride<Idxs>() != other.template __stride<Idxs>()) || ...);
    }

    template <class... Integral>
    MDSPAN_FORCE_INLINE_FUNCTION
    static constexpr ptrdiff_t _call_op_impl(layout_stride_impl const& self, Integral... idxs) noexcept {
      return ((idxs * self.template __stride<Idxs>()) + ... + 0);
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

  template <size_t N, ptrdiff_t Default=dynamic_extent>
  MDSPAN_INLINE_FUNCTION
  static constexpr ptrdiff_t __static_stride() noexcept
  {
    return stride_storage_t::template get_static<N, Default>();
  }

public:

  //--------------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl(layout_stride_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr layout_stride_impl(layout_stride_impl&&) noexcept = default;

  // TODO @proposal-bug layout stride needs this constructor
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

  // TODO constraints
  template <class... Integral>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t operator()(Integral... idxs) const noexcept {
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
} // end namespace std