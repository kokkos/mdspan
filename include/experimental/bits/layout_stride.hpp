
#pragma once

#include "macros.hpp"
#include "fixed_layout_impl.hpp"
#include "mixed_size_storage.hpp"
#include "extents.hpp"

#include <algorithm>
#include <numeric>
#include <array>

namespace std {

//==============================================================================

namespace detail {

// TODO make this faster; this is pretty ugly right now
template <class T>

template <class, ptrdiff_t>
struct _fold_assign_drop;
template <size_t... Idxs, size_t I>
struct _fold_assign_drop<index_sequence<Idxs...>, I> {
  template <ptrdiff_t J>
  _fold_assign_drop<index_sequence<Idxs..., J>, I> operator=(integral_constant<size_t, J>) noexcept; // NOLINT(misc-unconventional-assign-operator)
  _fold_assign_drop<index_sequence<Idxs...>, I> operator=(integral_constant<size_t, I>) noexcept; // NOLINT(misc-unconventional-assign-operator)
  using type = index_sequence<Idxs...>;
};
template <class T, ptrdiff_t I> struct _drop_index_impl;
template <class T, T... Vals, ptrdiff_t I> struct _drop_index_impl<
  std::integer_sequence<T, Vals...>, I
> {
  using type = typename decltype(
    ((_fold_assign_drop<integer_sequence<T>, I>{}) = ... = std::integral_constant<T, Vals>{})
  )::type;
};

template <class, class, class, bool, ptrdiff_t>
struct _fold_assign_is_always_contig;
template <class ExtentsType, class StridesType, ptrdiff_t... Rem, bool Result, ptrdiff_t PrevStrideTimesExt>
struct _fold_assign_is_always_contig<ExtentsType, StridesType, std::index_sequence<Rem...>, Result, PrevStrideTimesExt> {
  static constexpr auto value = Result;

  // if any of the strides at the remaining indices equal _prev_stride_times_prev_extent, then remove that index from
  // the remaining indices and continue with true

  static constexpr auto NextIdx = (
    (
      (ExtentsType::template __static_extent<Rem>() == PrevStrideTimesExt) ?
      Rem + 1 : 0
    ) + ... + 0
  ) - 1;

  MDSPAN_TEMPLATE_REQUIRES(
    size_t N,
    (NextIdx > 0)
  )
  constexpr
  _fold_assign_is_always_contig<
    ExtentsType,
    StridesType,
    typename _drop_index_impl<std::index_sequence<Rem...>, NextIdx>::type,
    Result,
    (ExtentsType::template __static_extent<NextIdx>() * StridesType::template get<NextIdx>)
  > operator=(std::integral_constant<size_t, N>) noexcept;

  MDSPAN_TEMPLATE_REQUIRES(
    size_t N,
    (NextIdx == 0)
  )
  constexpr
  _fold_assign_is_always_contig<ExtentsType, StridesType, std::index_sequence<>, false, 0>
  operator=(std::integral_constant<size_t, N>) noexcept;
};
template <class ExtentsType, class StridesType, class RemType>
struct _fold_assign_is_always_contig<ExtentsType, StridesType, RemType, false, 0> {
  template <size_t N>
  _fold_assign_is_always_contig operator=(std::integral_constant<size_t, N>) noexcept;
};

template <class, ptrdiff_t...> class layout_stride_impl;

template <ptrdiff_t... Exts, ptrdiff_t... Strides>
class layout_stride_impl<
  std::extents<Exts...>, Strides...
>
  : public extents_storage<std::extents<Exts...>>
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

    MDSPAN_INLINE_FUNCTION
    static constexpr bool _is_always_contiguous_impl() noexcept {
      return (
        _fold_assign_is_always_contig<
          std::extents<Exts...>,
          stride_storage_t,
          std::index_sequence<Idxs...>,

      )
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

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
  // TODO @proposal-bug this wording for this is (at least slightly) broken (should at least be "... stride(p[0]) == 1...")
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept {
    auto rem = std::array<ptrdiff_t, sizeof...(Exts)>{ };
    std::iota(rem.begin(), rem.end(), ptrdiff_t(0));
    auto next_idx_iter = std::find_if(
      rem.begin(), rem.end(),
      [&](auto i) { _strides.get(i) == 1;  }
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
          [&](auto i) {
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
  /* this is the only recursive template instantiation in the implementation, so don't do it unless we need it */
  MDSPAN_INSTANTIATE_ONLY_IF_USED
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept {
    return ;
  }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

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