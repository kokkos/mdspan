

#pragma once

#include "basic_mdspan.hpp"
#include "all_type.hpp"
#include "dynamic_extent.hpp"

#include <tuple> // std::apply

namespace std {

namespace detail {

template <ptrdiff_t OldExtent, ptrdiff_t OldStaticStride, class T>
struct _slice_wrap {
  T slice;
  ptrdiff_t old_extent;
  ptrdiff_t old_stride;
};

//--------------------------------------------------------------------------------

template <ptrdiff_t OldExtent, ptrdiff_t OldStaticStride>
MDSPAN_INLINE_FUNCTION
_slice_wrap<OldExtent, OldStaticStride, ptrdiff_t>
_wrap_slice(ptrdiff_t val, ptrdiff_t ext, ptrdiff_t stride) { return { val, ext, stride }; }

template <ptrdiff_t OldExtent, ptrdiff_t OldStaticStride>
MDSPAN_INLINE_FUNCTION
_slice_wrap<OldExtent, OldStaticStride, all_type>
_wrap_slice(all_type val, ptrdiff_t ext, ptrdiff_t stride) { return { val, ext, stride }; }

// TODO generalize this to anything that works with std::get<0> and std::get<1>
template <ptrdiff_t OldExtent, ptrdiff_t OldStaticStride>
MDSPAN_INLINE_FUNCTION
_slice_wrap<OldExtent, OldStaticStride, std::pair<ptrdiff_t, ptrdiff_t>>
_wrap_slice(std::pair<ptrdiff_t, ptrdiff_t> const& val, ptrdiff_t ext, ptrdiff_t stride)
{
  return { val, ext, stride };
}

//--------------------------------------------------------------------------------

template <
  class Extents, class StaticStrides,
  class Offsets, class ExtentInitializers, class DynamicStrides,
  class=std::make_index_sequence<std::tuple_size<Offsets>::value>,
  class=std::make_index_sequence<std::tuple_size<ExtentInitializers>::value>,
  class=std::make_index_sequence<std::tuple_size<DynamicStrides>::value>
>
struct _assign_op_slice_handler;

template <
  ptrdiff_t... Extents,
  ptrdiff_t... StaticStrides,
  size_t NOffsets,
  size_t NDynamicExtents,
  size_t NDynamicStrides,
  size_t... OffsetIdxs,
  size_t... ExtentInitIdxs,
  size_t... DynamicStrideIdxs
>
struct _assign_op_slice_handler<
  integer_sequence<ptrdiff_t, Extents...>,
  integer_sequence<ptrdiff_t, StaticStrides...>,
  array<ptrdiff_t, NOffsets>,
  array<ptrdiff_t, NDynamicExtents>,
  array<ptrdiff_t, NDynamicStrides>,
  index_sequence<OffsetIdxs...>,
  index_sequence<ExtentInitIdxs...>,
  index_sequence<DynamicStrideIdxs...>
>
{
  array<ptrdiff_t, NOffsets> offsets;
  array<ptrdiff_t, NDynamicExtents> dynamic_extents;
  array<ptrdiff_t, NDynamicStrides> dynamic_strides;
  
  //template <class _ignore=void, class=enable_if_t<is_void_v<_ignore>>> // avoid instantiating until necessary
  //MDSPAN_INLINE_FUNCTION
  //constexpr auto make_extents() {
  //  return std::extents<Extents...>(dynamic_extents);
  //}

  using layout_type = layout_stride<StaticStrides...>;

  // TODO return layout_left or layout_right if that info can be preserved
  template <class OldLayoutMapping>
  MDSPAN_INLINE_FUNCTION
  constexpr auto
  make_layout_mapping(OldLayoutMapping const&) {
    return typename layout_stride<StaticStrides...>::template mapping<std::extents<Extents...>>(
      std::extents<Extents...>(dynamic_extents),
      dynamic_strides
    );
  }

  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride, class T>
  auto fwd_extent(_slice_wrap<OldStaticExtent, OldStaticStride, T> const& slice) const {
    return dynamic_extents;
  }

  template <ptrdiff_t OldStaticStride, class T>
  auto fwd_extent(_slice_wrap<dynamic_extent, OldStaticStride, T> const& slice) const {
    return array{ std::get<ExtentInitIdxs>(dynamic_extents)..., slice.old_extent };
  }

  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride, class T>
  auto fwd_stride(_slice_wrap<OldStaticExtent, OldStaticStride, T> const& slice) const {
    return dynamic_strides;
  }

  template <ptrdiff_t OldStaticExtent, class T>
  auto fwd_stride(_slice_wrap<OldStaticExtent, dynamic_extent, T> const& slice) const {
    return array{ std::get<DynamicStrideIdxs>(dynamic_strides)..., slice.old_stride };
  }

  // For ptrdiff_t slice, skip the extent and stride, but add an offset corresponding to the value
  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride>
  auto operator=(_slice_wrap<OldStaticExtent, OldStaticStride, ptrdiff_t> slice)
    -> _assign_op_slice_handler<
         integer_sequence<ptrdiff_t, Extents...>,
         integer_sequence<ptrdiff_t, StaticStrides...>,
         array<ptrdiff_t, NOffsets + 1>,
         array<ptrdiff_t, NDynamicExtents>,
         array<ptrdiff_t, NDynamicStrides>
       >
  {
    return {
      array{std::get<OffsetIdxs>(offsets)..., slice.slice},
      dynamic_extents,
      dynamic_strides
    };
  }

  // For a std::all, offset 0 and old extent
  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride>
  auto operator=(_slice_wrap<OldStaticExtent, OldStaticStride, all_type> slice)
    -> _assign_op_slice_handler<
         integer_sequence<ptrdiff_t, Extents..., OldStaticExtent>,
         integer_sequence<ptrdiff_t, StaticStrides..., OldStaticStride>,
         array<ptrdiff_t, NOffsets + 1>,
         decltype(fwd_extent(slice)),
         decltype(fwd_stride(slice))
       >
  {
    return {
      array{std::get<OffsetIdxs>(offsets)..., ptrdiff_t(0)},
      fwd_extent(slice),
      fwd_stride(slice)
    };
  }

  // For a std::pair, add an offset and add a new dynamic extent (strides still preserved)
  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride>
  auto operator=(_slice_wrap<OldStaticExtent, OldStaticStride, std::pair<ptrdiff_t, ptrdiff_t>> slice) 
    -> _assign_op_slice_handler<
         integer_sequence<ptrdiff_t, Extents..., std::dynamic_extent>,
         integer_sequence<ptrdiff_t, StaticStrides..., OldStaticStride>,
         array<ptrdiff_t, NOffsets + 1>,
         array<ptrdiff_t, NDynamicExtents + 1>,
         decltype(fwd_stride(slice))
       >
  {
    return {
      array{std::get<OffsetIdxs>(offsets)..., std::get<0>(slice.slice)},
      array{std::get<ExtentInitIdxs>(dynamic_extents)..., std::get<1>(slice.slice) - std::get<0>(slice.slice)},
      fwd_stride(slice)
    };
  }
};

  
} // namespace detail

// TODO constraints
template <class ET, ptrdiff_t... Exts, class LP, class AP, class... SliceSpecs>
auto subspan(
  basic_mdspan<ET, std::extents<Exts...>, LP, AP> const& src, SliceSpecs... slices
) noexcept
{
  return [&]<size_t... Idxs>(index_sequence<Idxs...>) {
    auto _handled = (
      detail::_assign_op_slice_handler<
        integer_sequence<ptrdiff_t>,
        integer_sequence<ptrdiff_t>,
        array<ptrdiff_t, 0>,
        array<ptrdiff_t, 0>,
        array<ptrdiff_t, 0>
      >{} = ... = detail::_wrap_slice<
        Exts, decltype(src.mapping())::template __static_stride<Idxs>()
      >(
        slices, src.extents().template __extent<Idxs>(), src.mapping().stride(Idxs)
      )
    );   
    
    ptrdiff_t offset_size = std::apply(src.mapping(), _handled.offsets);
    auto offset_ptr = src.accessor().offset(src.data(), offset_size);
    auto map = _handled.make_layout_mapping(src.mapping());
    auto acc_pol = typename AP::offset_policy(src.accessor());
    return basic_mdspan<
      ET, decltype(map.extents()), typename decltype(_handled)::layout_type, decltype(acc_pol)
    >(
      std::move(offset_ptr), std::move(map), std::move(acc_pol)
    );
  }(index_sequence_for<SliceSpecs...>{});
}
        
} // namespace std