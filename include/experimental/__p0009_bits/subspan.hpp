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
#include "array_workaround.hpp"

#include <tuple> // std::apply
#include <utility> // std::pair

namespace std {
namespace experimental {

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
  bool result=true,
  bool encountered_first_all=false,
  bool encountered_first_pair=false
>
struct preserve_layout_right_analysis : std::integral_constant<bool, result> {
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
struct preserve_layout_left_analysis : std::integral_constant<bool, result> {
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

//--------------------------------------------------------------------------------

template <
  class Extents, class StaticStrides, class PreserveLayoutAnalysis,
  class Offsets = __array_workaround::__array<ptrdiff_t, 0>,
  class ExtentInitializers = __array_workaround::__array<ptrdiff_t, 0>,
  class DynamicStrides = __array_workaround::__array<ptrdiff_t, 0>,
  class=std::make_index_sequence<Offsets::__size>,
  class=std::make_index_sequence<ExtentInitializers::__size>,
  class=std::make_index_sequence<DynamicStrides::__size>
>
struct _assign_op_slice_handler;

template <
  ptrdiff_t... Extents,
  ptrdiff_t... StaticStrides,
  class PreserveLayoutAnalysis,
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
  PreserveLayoutAnalysis,
  __array_workaround::__array<ptrdiff_t, NOffsets>,
  __array_workaround::__array<ptrdiff_t, NDynamicExtents>,
  __array_workaround::__array<ptrdiff_t, NDynamicStrides>,
  integer_sequence<size_t, OffsetIdxs...>,
  integer_sequence<size_t, ExtentInitIdxs...>,
  integer_sequence<size_t, DynamicStrideIdxs...>
>
{
  static_assert(
    _MDSPAN_FOLD_AND((StaticStrides == dynamic_extent || StaticStrides > 0) /* && ... */),
    " "
  );

  __array_workaround::__array<ptrdiff_t, NOffsets> offsets = { };
  __array_workaround::__array<ptrdiff_t, NDynamicExtents> dynamic_extents = { };
  __array_workaround::__array<ptrdiff_t, NDynamicStrides> dynamic_strides = { };

  // Some old compilers don't like aggregate initialization, so we have to do this.  It shouldn't hurt other compilers
#if !MDSPAN_HAS_CXX_14
  MDSPAN_INLINE_FUNCTION
  _assign_op_slice_handler(
    __array_workaround::__array<ptrdiff_t, NOffsets> arg_offsets,
    __array_workaround::__array<ptrdiff_t, NDynamicExtents> arg_dynamic_extents,
    __array_workaround::__array<ptrdiff_t, NDynamicStrides> arg_dynamic_strides
  ) noexcept
    : offsets(std::move(arg_offsets)),
      dynamic_extents(std::move(arg_dynamic_extents)),
      dynamic_strides(std::move(arg_dynamic_strides))
  { }
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr _assign_op_slice_handler() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr _assign_op_slice_handler(_assign_op_slice_handler const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr _assign_op_slice_handler(_assign_op_slice_handler&&) noexcept = default;
#endif

#if !defined(_MDSPAN_USE_RETURN_TYPE_DEDUCTION) || !_MDSPAN_USE_RETURN_TYPE_DEDUCTION
  using extents_type = std::experimental::extents<Extents...>;
#endif

  // TODO defer instantiation of this?
  using layout_type = typename conditional<
    PreserveLayoutAnalysis::value,
    typename PreserveLayoutAnalysis::layout_type_if_preserved,
    layout_stride<StaticStrides...>
  >::type;

  // TODO noexcept specification
  template <class NewLayout>
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      constexpr /* auto */
      _make_layout_mapping_impl(NewLayout) const noexcept
    ),
    (
      /* not layout stride, so don't pass dynamic_strides */
      /* return */ typename NewLayout::template mapping<std::experimental::extents<Extents...>>(
        std::experimental::extents<Extents...>(dynamic_extents.template __get_n<ExtentInitIdxs>()...)
      ) /* ; */
    )
  )

  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      constexpr /* auto */
      _make_layout_mapping_impl(layout_stride<StaticStrides...>) const noexcept
    ),
    (
      /* return */ typename layout_stride<StaticStrides...>::template mapping<std::experimental::extents<Extents...>>(
        std::experimental::extents<Extents...>(dynamic_extents.template __get_n<ExtentInitIdxs>()...),
        std::array<ptrdiff_t, NDynamicStrides>{dynamic_strides.template __get_n<DynamicStrideIdxs>()...}
      ) /* ; */
    )
  )

  template <class OldLayoutMapping> // mostly for deferred instantiation, but maybe we'll use this in the future
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      constexpr /* auto */
      make_layout_mapping(OldLayoutMapping const&) const noexcept
    ),
    (
      /* return */ this->_make_layout_mapping_impl(layout_type{}) /* ; */
    )
  )

  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride, class T>
  MDSPAN_INLINE_FUNCTION
  constexpr auto fwd_extent(_slice_wrap<OldStaticExtent, OldStaticStride, T> const& slice) const noexcept
    -> decltype(dynamic_extents)
  {
    return dynamic_extents;
  }

  template <ptrdiff_t OldStaticStride, class T>
  MDSPAN_INLINE_FUNCTION
  constexpr auto fwd_extent(_slice_wrap<dynamic_extent, OldStaticStride, T> const& slice) const noexcept
    -> __array_workaround::__array<ptrdiff_t, sizeof...(ExtentInitIdxs) + 1>
  {
    return { dynamic_extents.template __get_n<ExtentInitIdxs>()..., slice.old_extent };
  }

  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride, class T>
  MDSPAN_INLINE_FUNCTION
  constexpr auto fwd_stride(_slice_wrap<OldStaticExtent, OldStaticStride, T> const& slice) const noexcept
    -> decltype(dynamic_strides)
  {
    return dynamic_strides;
  }

  template <ptrdiff_t OldStaticExtent, class T>
  MDSPAN_INLINE_FUNCTION
  constexpr auto fwd_stride(_slice_wrap<OldStaticExtent, dynamic_extent, T> const& slice) const noexcept
    -> __array_workaround::__array<ptrdiff_t, sizeof...(DynamicStrideIdxs) + 1>
  {
    return { dynamic_strides.template __get_n<DynamicStrideIdxs>()..., slice.old_stride };
  }

  // For ptrdiff_t slice, skip the extent and stride, but add an offset corresponding to the value
  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(_slice_wrap<OldStaticExtent, OldStaticStride, ptrdiff_t> slice) noexcept
    -> _assign_op_slice_handler<
         integer_sequence<ptrdiff_t, Extents...>,
         integer_sequence<ptrdiff_t, StaticStrides...>,
         typename PreserveLayoutAnalysis::encounter_scalar,
         __array_workaround::__array<ptrdiff_t, NOffsets + 1>,
         __array_workaround::__array<ptrdiff_t, NDynamicExtents>,
         __array_workaround::__array<ptrdiff_t, NDynamicStrides>
       >
  {
    return {
      __array_workaround::__array<ptrdiff_t, NOffsets + 1>( offsets.template __get_n<OffsetIdxs>()..., slice.slice ),
      dynamic_extents,
      dynamic_strides
    };
  }

  // For a std::all, offset 0 and old extent
  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(_slice_wrap<OldStaticExtent, OldStaticStride, all_type> slice) noexcept
    -> _assign_op_slice_handler<
         integer_sequence<ptrdiff_t, Extents..., OldStaticExtent>,
         integer_sequence<ptrdiff_t, StaticStrides..., OldStaticStride>,
         typename PreserveLayoutAnalysis::encounter_all,
         __array_workaround::__array<ptrdiff_t, NOffsets + 1>,
         decltype(this->fwd_extent(slice)),
         decltype(this->fwd_stride(slice))
       >
  {
    return {
      __array_workaround::__array<ptrdiff_t, NOffsets + 1>(offsets.template __get_n<OffsetIdxs>()..., ptrdiff_t(0)),
      this->fwd_extent(slice),
      this->fwd_stride(slice)
    };
  }

  // For a std::pair, add an offset and add a new dynamic extent (strides still preserved)
  template <ptrdiff_t OldStaticExtent, ptrdiff_t OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(_slice_wrap<OldStaticExtent, OldStaticStride, std::pair<ptrdiff_t, ptrdiff_t>> slice) noexcept
    -> _assign_op_slice_handler<
         integer_sequence<ptrdiff_t, Extents..., dynamic_extent>,
         integer_sequence<ptrdiff_t, StaticStrides..., OldStaticStride>,
         typename PreserveLayoutAnalysis::encounter_pair,
         __array_workaround::__array<ptrdiff_t, NOffsets + 1>,
         __array_workaround::__array<ptrdiff_t, NDynamicExtents + 1>,
         decltype(this->fwd_stride(slice))
       >
  {
    return {
      __array_workaround::__array<ptrdiff_t, NOffsets + 1>(offsets.template __get_n<OffsetIdxs>()..., std::get<0>(slice.slice)),
      __array_workaround::__array<ptrdiff_t, NDynamicExtents + 1>(dynamic_extents.template __get_n<ExtentInitIdxs>()..., std::get<1>(slice.slice) - std::get<0>(slice.slice)),
      this->fwd_stride(slice)
    };
  }
};

#if _MDSPAN_USE_RETURN_TYPE_DEDUCTION
// Forking this because the C++11 version will be *completely* unreadable
template <class ET, ptrdiff_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
MDSPAN_INLINE_FUNCTION
constexpr auto _subspan_impl(
  std::integer_sequence<size_t, Idxs...>,
  basic_mdspan<ET, std::experimental::extents<Exts...>, LP, AP> const& src,
  SliceSpecs&&... slices
) noexcept
{
  auto _handled =
    _MDSPAN_FOLD_ASSIGN_LEFT(
      (
        detail::_assign_op_slice_handler<
          integer_sequence<ptrdiff_t>,
          integer_sequence<ptrdiff_t>,
          typename std::conditional<
            std::is_same<LP, layout_right>::value,
            detail::preserve_layout_right_analysis<>,
            typename std::conditional<
              std::is_same<LP, layout_left>::value,
              detail::preserve_layout_left_analysis<>,
              detail::ignore_layout_preservation
            >::type
          >::type
        >{std::array<ptrdiff_t, 0>{}, std::array<ptrdiff_t, 0>{}, std::array<ptrdiff_t, 0>{}}
      ),
        /* = ... = */
      detail::_wrap_slice<
        Exts, decltype(src.mapping())::template __static_stride_workaround<Idxs>::value
      >(
        slices, src.extents().template __extent<Idxs>(), src.mapping().stride(Idxs)
      )
    );

  ptrdiff_t offset_size = src.mapping()(_handled.offsets.template __get_n<Idxs>()...);
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
       ET, typename Handled::extents_type, typename Handled::layout_type, typename AP::offset_policy
     >
{
  return {
    src.accessor().offset(src.data(), src.mapping()(h.offsets.template __get_n<Idxs>()...)),
    h.make_layout_mapping(src.mapping()),
    typename AP::offset_policy(src.accessor())
  };
}

template <class ET, ptrdiff_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
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
          detail::_assign_op_slice_handler<
            integer_sequence<ptrdiff_t>,
            integer_sequence<ptrdiff_t>,
            typename std::conditional<
              std::is_same<LP, layout_right>::value,
              detail::preserve_layout_right_analysis<>,
              typename std::conditional<
                std::is_same<LP, layout_left>::value,
                detail::preserve_layout_left_analysis<>,
                detail::ignore_layout_preservation
              >::type
            >::type
          >{std::array<ptrdiff_t, 0>{}, std::array<ptrdiff_t, 0>{}, std::array<ptrdiff_t, 0>{}}
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
template <ptrdiff_t... StaticStrides> struct _is_layout_stride<
  layout_stride<StaticStrides...>
> : std::true_type
{ };


} // namespace detail

// TODO @proposal-bug sizeof...(SliceSpecs) == sizeof...(Exts) should be a constraint, not a requirement
MDSPAN_TEMPLATE_REQUIRES(
  class ET, ptrdiff_t... Exts, class LP, class AP, class... SliceSpecs,
  /* requires */ (
    (
      _MDSPAN_TRAIT(is_same, LP, layout_left)
        || _MDSPAN_TRAIT(is_same, LP, layout_right)
        || detail::_is_layout_stride<LP>::value
    ) &&
    _MDSPAN_FOLD_OR((
      _MDSPAN_TRAIT(is_convertible, SliceSpecs, ptrdiff_t)
        || _MDSPAN_TRAIT(is_convertible, SliceSpecs, pair<ptrdiff_t, ptrdiff_t>)
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

} // end namespace experimental
} // namespace std