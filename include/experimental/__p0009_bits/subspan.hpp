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

#include "basic_mdspan.hpp"
#include "all_type.hpp"
#include "dynamic_extent.hpp"
#include "layout_left.hpp"
#include "layout_right.hpp"
#include "layout_stride.hpp"
#include "macros.hpp"
#include "trait_backports.hpp"

#include <tuple> // std::apply
#include <utility> // std::pair

namespace std {
namespace experimental {

namespace detail {

template <size_t OldExtent, size_t OldStaticStride, class T>
struct _slice_wrap {
  T slice;
  size_t old_extent;
  size_t old_stride;
};

//--------------------------------------------------------------------------------

template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
_slice_wrap<OldExtent, OldStaticStride, size_t>
_wrap_slice(size_t val, size_t ext, size_t stride) { return { val, ext, stride }; }

template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
_slice_wrap<OldExtent, OldStaticStride, all_type>
_wrap_slice(all_type val, size_t ext, size_t stride) { return { val, ext, stride }; }

// TODO generalize this to anything that works with std::get<0> and std::get<1>
template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
_slice_wrap<OldExtent, OldStaticStride, std::pair<size_t, size_t>>
_wrap_slice(std::pair<size_t, size_t> const& val, size_t ext, size_t stride)
{
  return { val, ext, stride };
}

//--------------------------------------------------------------------------------


template <
  bool result=true,
  bool encountered_first_all=false,
  bool encountered_first_pair=false
>
struct preserve_layout_right_analysis : integral_constant<bool, result> {
  using layout_type_if_preserved = layout_right;
  using encounter_pair = preserve_layout_right_analysis<
    // If the pair isn't the right-most slice (i.e., if there was a previous pair),
    // we can't preserve any contiguous layout.  Nothing else should matter
    (encountered_first_pair ? false : result),
    // Whether or not we've encountered the first all doesn't change, though it
    // doesn't really matter, since anything to the right of this leads to a false
    // result
    encountered_first_all,
    // This is a pair, so we've encountered at least one
    true
  >;
  using encounter_all = preserve_layout_right_analysis<
    // encountering an all changes nothing unless we've already encountered a pair
    (encountered_first_pair ? false : result),
    // This is an all, so we've encountered at least one
    true,
    // nothing changes about this last one
    encountered_first_pair
  >;
  using encounter_scalar = preserve_layout_right_analysis<
    // if there's a scalar to the right of any non-scalar slice, we can't preserve
    // any contiguous layout:
    (encountered_first_all || encountered_first_pair) ? false : result,
    // nothing else changes (though if they're true, it doesn't matter)
    encountered_first_all,
    encountered_first_pair
  >;
};

template <
  bool result=true,
  bool encountered_first_scalar=false,
  bool encountered_first_all=false,
  bool encountered_first_pair=false
>
struct preserve_layout_left_analysis : integral_constant<bool, result> {
  using layout_type_if_preserved = layout_left;
  using encounter_pair = preserve_layout_left_analysis<
    // Only the left-most slice can be a pair.  If we've encountered anything else,
    // we can't preserve any contiguous layout
    (encountered_first_scalar || encountered_first_all || encountered_first_pair) ? false : result,
    // These change in the expected ways
    encountered_first_scalar,
    encountered_first_all,
    true
  >;
  using encounter_all = preserve_layout_left_analysis<
    // If there's a scalar to the left of us, we can't preserve contiguous
    encountered_first_scalar ? false : result,
    // These change in the expected ways
    encountered_first_scalar,
    true,
    encountered_first_pair
  >;
  using encounter_scalar = preserve_layout_left_analysis<
    // If there's a scalar to the left of us, we can't preserve contiguous
    result,
    // These change in the expected ways
    true,
    encountered_first_all,
    encountered_first_pair
  >;
};

struct ignore_layout_preservation : std::integral_constant<bool, false> {
  using layout_type_if_preserved = void;
  using encounter_pair = ignore_layout_preservation;
  using encounter_all = ignore_layout_preservation;
  using encounter_scalar = ignore_layout_preservation;
};

template <class Layout>
struct preserve_layout_analysis
  : ignore_layout_preservation { };
template <>
struct preserve_layout_analysis<layout_right>
  : preserve_layout_right_analysis<> { };
template <>
struct preserve_layout_analysis<layout_left>
  : preserve_layout_left_analysis<> { };

//--------------------------------------------------------------------------------

template <
  class _PreserveLayoutAnalysis,
  class _OffsetsArray=__partially_static_sizes<>,
  class _ExtsArray=__partially_static_sizes<>,
  class _StridesArray=__partially_static_sizes<>,
  class=make_index_sequence<_OffsetsArray::__size>,
  class=make_index_sequence<_ExtsArray::__size>,
  class=make_index_sequence<_StridesArray::__size>
>
struct __assign_op_slice_handler;

/* clang-format: off */
template <
  class _PreserveLayoutAnalysis,
  size_t... _Offsets,
  size_t... _Exts,
  size_t... _Strides,
  size_t... _OffsetIdxs,
  size_t... _ExtIdxs,
  size_t... _StrideIdxs>
struct __assign_op_slice_handler<
  _PreserveLayoutAnalysis,
  __partially_static_sizes<_Offsets...>,
  __partially_static_sizes<_Exts...>,
  __partially_static_sizes<_Strides...>,
  integer_sequence<size_t, _OffsetIdxs...>,
  integer_sequence<size_t, _ExtIdxs...>,
  integer_sequence<size_t, _StrideIdxs...>>
{
  // TODO remove this for better compiler performance
  static_assert(
    _MDSPAN_FOLD_AND((_Strides == dynamic_extent || _Strides > 0) /* && ... */),
    " "
  );
  static_assert(
    _MDSPAN_FOLD_AND((_Offsets == dynamic_extent || _Offsets >= 0) /* && ... */),
    " "
  );

  using __offsets_storage_t = __partially_static_sizes<_Offsets...>;
  using __extents_storage_t = __partially_static_sizes<_Exts...>;
  using __strides_storage_t = __partially_static_sizes<_Strides...>;
  __offsets_storage_t __offsets;
  __extents_storage_t __exts;
  __strides_storage_t __strides;

#ifdef __INTEL_COMPILER
#if __INTEL_COMPILER <= 1800
  MDSPAN_INLINE_FUNCTION constexpr __assign_op_slice_handler(__assign_op_slice_handler&& __other) noexcept
    : __offsets(::std::move(__other.__offsets)), __exts(::std::move(__other.__exts)), __strides(::std::move(__other.__strides))
  { }
  MDSPAN_INLINE_FUNCTION constexpr __assign_op_slice_handler(
    __offsets_storage_t&& __o,
    __extents_storage_t&& __e,
    __strides_storage_t&& __s
  ) noexcept
    : __offsets(::std::move(__o)), __exts(::std::move(__e)), __strides(::std::move(__s))
  { }
#endif
#endif

// Don't define this unless we need it; they have a cost to compile
#ifndef _MDSPAN_USE_RETURN_TYPE_DEDUCTION
  using __extents_type = ::std::experimental::extents<_Exts...>;
#endif

  // For size_t slice, skip the extent and stride, but add an offset corresponding to the value
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(_slice_wrap<_OldStaticExtent, _OldStaticStride, size_t>&& __slice) noexcept
    -> __assign_op_slice_handler<
         typename _PreserveLayoutAnalysis::encounter_scalar,
         __partially_static_sizes<_Offsets..., dynamic_extent>,
         __partially_static_sizes<_Exts...>,
         __partially_static_sizes<_Strides...>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_Offsets..., dynamic_extent>(
        __construct_partially_static_array_from_sizes_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., __slice.slice),
      ::std::move(__exts),
      ::std::move(__strides)
    };
  }

  // For a std::all, offset 0 and old extent
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(_slice_wrap<_OldStaticExtent, _OldStaticStride, all_type>&& __slice) noexcept
    -> __assign_op_slice_handler<
         typename _PreserveLayoutAnalysis::encounter_all,
         __partially_static_sizes<_Offsets..., 0>,
         __partially_static_sizes<_Exts..., _OldStaticExtent>,
         __partially_static_sizes<_Strides..., _OldStaticStride>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_Offsets..., 0>(
        __construct_partially_static_array_from_sizes_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., size_t(0)),
      __partially_static_sizes<_Exts..., _OldStaticExtent>(
        __construct_partially_static_array_from_sizes_tag,
        __exts.template __get_n<_ExtIdxs>()..., __slice.old_extent),
      __partially_static_sizes<_Strides..., _OldStaticStride>(
        __construct_partially_static_array_from_sizes_tag,
        __strides.template __get_n<_StrideIdxs>()..., __slice.old_stride)
    };
  }

  // For a std::pair, add an offset and add a new dynamic extent (strides still preserved)
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(_slice_wrap<_OldStaticExtent, _OldStaticStride, pair<size_t, size_t>>&& __slice) noexcept
    -> __assign_op_slice_handler<
         typename _PreserveLayoutAnalysis::encounter_pair,
         __partially_static_sizes<_Offsets..., dynamic_extent>,
         __partially_static_sizes<_Exts..., dynamic_extent>,
         __partially_static_sizes<_Strides..., _OldStaticStride>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_Offsets..., dynamic_extent>(
        __construct_partially_static_array_from_sizes_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., ::std::get<0>(__slice.slice)),
      __partially_static_sizes<_Exts..., dynamic_extent>(
        __construct_partially_static_array_from_sizes_tag,
        __exts.template __get_n<_ExtIdxs>()..., ::std::get<1>(__slice.slice) - ::std::get<0>(__slice.slice)),
      __partially_static_sizes<_Strides..., _OldStaticStride>(
        __construct_partially_static_array_from_sizes_tag,
        __strides.template __get_n<_StrideIdxs>()..., __slice.old_stride)
    };
  }

   // TODO defer instantiation of this?
  using layout_type = typename conditional<
    _PreserveLayoutAnalysis::value,
    typename _PreserveLayoutAnalysis::layout_type_if_preserved,
    layout_stride<_Strides...>
  >::type;

  // TODO noexcept specification
  template <class NewLayout>
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      _MDSPAN_CONSTEXPR_14 /* auto */
      _make_layout_mapping_impl(NewLayout) noexcept
    ),
    (
      /* not layout stride, so don't pass dynamic_strides */
      /* return */ typename NewLayout::template mapping<::std::experimental::extents<_Exts...>>(
        experimental::extents<_Exts...>::__make_extents_impl(::std::move(__exts))
      ) /* ; */
    )
  )

  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      _MDSPAN_CONSTEXPR_14 /* auto */
      _make_layout_mapping_impl(layout_stride<_Strides...>) noexcept
    ),
    (
      /* return */ layout_stride<_Strides...>::template mapping<::std::experimental::extents<_Exts...>>
        ::__make_layout_stride_impl(::std::move(__exts), ::std::move(__strides)) /* ; */
    )
  )

  template <class OldLayoutMapping> // mostly for deferred instantiation, but maybe we'll use this in the future
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      _MDSPAN_CONSTEXPR_14 /* auto */
      make_layout_mapping(OldLayoutMapping const&) noexcept
    ),
    (
      /* return */ this->_make_layout_mapping_impl(layout_type{}) /* ; */
    )
  )
};

//==============================================================================

#if _MDSPAN_USE_RETURN_TYPE_DEDUCTION
// Forking this because the C++11 version will be *completely* unreadable
template <class ET, size_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
MDSPAN_INLINE_FUNCTION
constexpr auto _subspan_impl(
  integer_sequence<size_t, Idxs...>,
  basic_mdspan<ET, std::experimental::extents<Exts...>, LP, AP> const& src,
  SliceSpecs&&... slices
) noexcept
{
  auto _handled =
    _MDSPAN_FOLD_ASSIGN_LEFT(
      (
        detail::__assign_op_slice_handler<
          detail::preserve_layout_analysis<LP>
        >{
          __partially_static_sizes<>{},
          __partially_static_sizes<>{},
          __partially_static_sizes<>{}
        }
      ),
        /* = ... = */
      detail::_wrap_slice<
        Exts, decltype(src.mapping())::template __static_stride_workaround<Idxs>::value
      >(
        slices, src.extents().template __extent<Idxs>(),
        src.mapping().template __stride<Idxs>()
      )
    );

  size_t offset_size = src.mapping()(_handled.__offsets.template __get_n<Idxs>()...);
  auto offset_ptr = src.accessor().offset(src.data(), offset_size);
  auto map = _handled.make_layout_mapping(src.mapping());
  auto acc_pol = typename AP::offset_policy(src.accessor());
  return basic_mdspan<
    ET, decltype(map.extents()), typename decltype(_handled)::layout_type, decltype(acc_pol)
  >(
    std::move(offset_ptr), std::move(map), std::move(acc_pol)
  );
}
#else

template <class ET, class AP, class Src, class Handled, size_t... Idxs>
auto _subspan_impl_helper(Src&& src, Handled&& h, std::integer_sequence<size_t, Idxs...>)
  -> basic_mdspan<
       ET, typename Handled::__extents_type, typename Handled::layout_type, typename AP::offset_policy
     >
{
  return {
    src.accessor().offset(src.data(), src.mapping()(h.__offsets.template __get_n<Idxs>()...)),
    h.make_layout_mapping(src.mapping()),
    typename AP::offset_policy(src.accessor())
  };
}

template <class ET, size_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
MDSPAN_INLINE_FUNCTION
_MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
  (
    constexpr /* auto */ _subspan_impl(
      std::integer_sequence<size_t, Idxs...> seq,
      basic_mdspan<ET, std::experimental::extents<Exts...>, LP, AP> const& src,
      SliceSpecs&&... slices
    ) noexcept
  ),
  (
    /* return */ _subspan_impl_helper<ET, AP>(
      src,
      _MDSPAN_FOLD_ASSIGN_LEFT(
        (
          detail::__assign_op_slice_handler<
            detail::preserve_layout_analysis<LP>
          >{
            __partially_static_sizes<>{},
            __partially_static_sizes<>{},
            __partially_static_sizes<>{}
          }
        ),
        /* = ... = */
        detail::_wrap_slice<
          Exts, decltype(src.mapping())::template __static_stride_workaround<Idxs>::value
        >(
          slices, src.extents().template __extent<Idxs>(), src.mapping().stride(Idxs)
        )
      ),
      seq
    ) /* ; */
  )
)

#endif

template <class T> struct _is_layout_stride : std::false_type { };
template <size_t... StaticStrides> struct _is_layout_stride<
  layout_stride<StaticStrides...>
> : std::true_type
{ };

} // namespace detail

//==============================================================================

// TODO @proposal-bug sizeof...(SliceSpecs) == sizeof...(Exts) should be a constraint, not a requirement
MDSPAN_TEMPLATE_REQUIRES(
  class ET, size_t... Exts, class LP, class AP, class... SliceSpecs,
  /* requires */ (
    (
      _MDSPAN_TRAIT(is_same, LP, layout_left)
        || _MDSPAN_TRAIT(is_same, LP, layout_right)
        || detail::_is_layout_stride<LP>::value
    ) &&
    _MDSPAN_FOLD_AND((
      _MDSPAN_TRAIT(is_convertible, SliceSpecs, size_t)
        || _MDSPAN_TRAIT(is_convertible, SliceSpecs, pair<size_t, size_t>)
        || _MDSPAN_TRAIT(is_convertible, SliceSpecs, all_type)
    ) /* && ... */) &&
    sizeof...(SliceSpecs) == sizeof...(Exts)
  )
)
MDSPAN_INLINE_FUNCTION
_MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
  (
    constexpr subspan(
      basic_mdspan<ET, std::experimental::extents<Exts...>, LP, AP> const& src, SliceSpecs... slices
    ) noexcept
  ),
  (
    /* return */
      detail::_subspan_impl(std::make_index_sequence<sizeof...(SliceSpecs)>{}, src, slices...) /*;*/
  )
)
/* clang-format: on */

} // end namespace experimental
} // namespace std
