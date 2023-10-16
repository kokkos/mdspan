//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER
#pragma once

#include <cassert>
#include "layout_padded_fwd.hpp"
#include "../__p0009_bits/dynamic_extent.hpp"
#include "../__p0009_bits/extents.hpp"
#include "../__p0009_bits/mdspan.hpp"
#include "../__p0009_bits/layout_left.hpp"
#include "../__p0009_bits/layout_right.hpp"
#include "../__p0009_bits/layout_stride.hpp"

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
namespace MDSPAN_IMPL_PROPOSED_NAMESPACE {

namespace detail {
template<class _T>
MDSPAN_INLINE_FUNCTION
constexpr _T
__find_next_multiple(_T __alignment, _T __offset)
{
  if ( __alignment == 0 ) {
    return _T(0);
  } else {
    return ( ( __offset + __alignment - 1 ) / __alignment) * __alignment;
  }
}

template <class _ExtentsType, size_t _PaddingValue, size_t _ExtentToPadIdx>
MDSPAN_INLINE_FUNCTION constexpr size_t __get_actual_static_padding_value() {
  constexpr auto __rank = _ExtentsType::rank();

  if constexpr (__rank <= typename _ExtentsType::rank_type(1)) {
    return 0;
  } else if constexpr (_PaddingValue != dynamic_extent &&
                       _ExtentsType::static_extent(_ExtentToPadIdx) !=
                           dynamic_extent) {
    static_assert(
        (_PaddingValue != 0) ||
            (_ExtentsType::static_extent(_ExtentToPadIdx) == 0),
        "padding stride can be 0 only if "
        "extents_type::static_extent(extent-to-pad) is 0 or dynamic_extent");
    return __find_next_multiple(_PaddingValue,
                                _ExtentsType::static_extent(_ExtentToPadIdx));
  } else {
    return dynamic_extent;
  }
}

template <size_t _PaddingValue, typename _Extents, size_t _ExtentToPadIdx, size_t _Rank, typename Enabled = void>
struct __static_array_type_for_padded_extent
{
  static constexpr size_t __padding_value = _PaddingValue;
  using __index_type = typename _Extents::index_type;
  using __extents_type = _Extents;
  using __type = ::MDSPAN_IMPL_STANDARD_NAMESPACE::detail::maybe_static_array<
      __index_type, size_t, dynamic_extent,
      detail::__get_actual_static_padding_value<__extents_type, __padding_value,
                                                _ExtentToPadIdx>()>;
};

template <size_t _PaddingValue, typename _Extents, size_t _ExtentToPadIdx, size_t Rank>
struct __static_array_type_for_padded_extent<_PaddingValue, _Extents,
                                             _ExtentToPadIdx, Rank, std::enable_if_t<Rank <= 1>> {
  using __index_type = typename _Extents::index_type;
  using __extents_type = _Extents;
  using __type =
      ::MDSPAN_IMPL_STANDARD_NAMESPACE::detail::maybe_static_array<
          __index_type, size_t, dynamic_extent, 0>;
};

template <size_t _PaddingValue, typename _Extents, size_t _ExtentToPadIdx>
struct __padded_extent {
  static constexpr size_t __padding_value = _PaddingValue;
  using __index_type = typename _Extents::index_type;
  using __extents_type = _Extents;
  using __static_array_type = typename __static_array_type_for_padded_extent<
      __padding_value, _Extents, _ExtentToPadIdx, _Extents::rank()>::__type;

  static constexpr auto static_value() { return __static_array_type::static_value(0); }

  MDSPAN_INLINE_FUNCTION
  static constexpr __static_array_type
  init_padding(const _Extents &__extents) {
    if constexpr ((_Extents::rank() > 1) && (__padding_value == dynamic_extent)) {
      return {__extents.extent(_ExtentToPadIdx)};
    } else {
      return init_padding(__extents, __padding_value);
    }
  }

  MDSPAN_INLINE_FUNCTION static constexpr __static_array_type
      init_padding(const _Extents &__extents,
                          __index_type __padding_value) {
    if constexpr (_Extents::rank() > 1) {
      return {__find_next_multiple(__padding_value,
                                   __extents.extent(_ExtentToPadIdx))};
    } else {
      return {};
    }
  }

  template <typename _Mapping, size_t _PaddingStrideIdx>
  MDSPAN_INLINE_FUNCTION static constexpr __static_array_type
  init_padding(const _Mapping &__other_mapping,
                      std::integral_constant<size_t, _PaddingStrideIdx>) {
    if constexpr (_Extents::rank() > 1) {
      return {__other_mapping.stride(_PaddingStrideIdx)};
    } else {
      return {};
    }
  }
};
} // namespace detail

template <size_t PaddingValue>
template <class Extents>
class layout_left_padded<PaddingValue>::mapping {
public:
  static constexpr size_t padding_value = PaddingValue;

  using extents_type = Extents;
  using index_type = typename extents_type::index_type;
  using size_type = typename extents_type::size_type;
  using rank_type = typename extents_type::rank_type;
  using layout_type = layout_left_padded<padding_value>;

#ifndef MDSPAN_INTERNAL_TEST
private:
#endif // MDSPAN_INTERNAL_TEST

  static constexpr rank_type __padded_stride_idx = detail::__layout_padded_constants<layout_type, extents_type>::__padded_stride_idx;
  static constexpr rank_type __extent_to_pad_idx = detail::__layout_padded_constants<layout_type, extents_type>::__extent_to_pad_idx;

  static_assert((padding_value != 0)
                || (extents_type::static_extent(__extent_to_pad_idx) == 0)
                || (extents_type::static_extent(__extent_to_pad_idx) == dynamic_extent),
                "out of bounds access for rank 0");

  using __padded_stride_type = detail::__padded_extent< padding_value, extents_type, __extent_to_pad_idx >;

  static constexpr size_t static_padding_stride = __padded_stride_type::static_value();

  typename __padded_stride_type::__static_array_type __padded_stride = {};
  extents_type __extents = {};

  constexpr index_type __compute_offset(std::index_sequence<>) const {
    return 0;
  }

  template <size_t Rank, class IndexOffset>
  constexpr index_type __compute_offset(std::index_sequence<Rank>,
                                        IndexOffset __index_offset) const {
    return __index_offset;
  }

  template <size_t... Ranks, class... IndexOffsets>
  constexpr index_type __compute_offset(std::index_sequence<Ranks...>,
                                        IndexOffsets... __index_offsets) const {
    index_type __indices[] = {static_cast<index_type>(__index_offsets)...};
    // self-recursive fold trick from
    // https://github.com/llvm/llvm-project/blob/96e1914aa2e6d8966acbfbe2f4d184201f1aa318/libcxx/include/__mdspan/layout_left.h#L144
    index_type res = 0;
    ((res = __indices[extents_type::rank() - 1 - Ranks] +
            ((extents_type::rank() - 1 - Ranks) == __extent_to_pad_idx
                 ? __padded_stride.value(0)
                 : __extents.extent(extents_type::rank() - 1 - Ranks)) *
                res),
     ...);
    return res;
  }

public:
#if !MDSPAN_HAS_CXX_20
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr mapping()
      : mapping(extents_type{})
  {}
#else
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr mapping()
    requires(static_padding_stride != dynamic_extent) = default;

  MDSPAN_INLINE_FUNCTION
  constexpr mapping()
    requires(static_padding_stride == dynamic_extent)
      : mapping(extents_type{})
  {}
#endif

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(const mapping&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED mapping& operator=(const mapping&) noexcept = default;

  /**
   * Initializes the mapping with the given extents.
   *
   * \param ext the given extents
   */
  MDSPAN_INLINE_FUNCTION
  constexpr mapping(const extents_type& __ext)
    : __padded_stride(__padded_stride_type::init_padding(__ext)), __extents(__ext)
  {}

  /**
   * Initializes the mapping with the given extents and the specified padding value.
   *
   * This overload participates in overload resolution only if `is_convertible_v<Size, index_type>`
   * is `true` and `is_nothrow_constructible_v<index_type, Size>` is `true`
   *
   * \param ext the given extents
   * \param padding_value the padding value
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class _Size,
    /* requires */ (
      std::is_convertible_v<_Size, index_type>
      && std::is_nothrow_constructible_v<index_type, _Size>
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mapping(const extents_type &__ext, _Size __dynamic_padding_value)
      : __padded_stride(__padded_stride_type::init_padding(__ext, __dynamic_padding_value)), __extents(__ext)
  {
    assert((padding_value == dynamic_extent) || (static_cast<index_type>(padding_value) == static_cast<index_type>(__dynamic_padding_value)));
  }

  /**
   * Converting constructor from `layout_left::mapping`.
   *
   * This overload participates in overload resolution only if `is_constructible_v<extents_type, OtherExtents>` is true.
   * If `OtherExtents::rank() > 1` then one of `padding_value`, `static_extent(0)`, or `OtherExtents::static_extent(0)` must be `dynamic_extent`;
   * otherwise, `OtherExtents::static_extent(0)` must be equal to the least multiple of `padding_value` greater than or equal to `extents_type::static_extent(0)`
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class _OtherExtents,
    /* requires */ (
      std::is_constructible_v<extents_type, _OtherExtents>
    )
  )
  MDSPAN_CONDITIONAL_EXPLICIT((!std::is_convertible_v<_OtherExtents, extents_type>))
  constexpr mapping(const layout_left::mapping<_OtherExtents> &__other_mapping)
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping, std::integral_constant<size_t, __padded_stride_idx>{})),
        __extents(__other_mapping.extents())
  {
    static_assert((_OtherExtents::rank() > 1) || (static_padding_stride != dynamic_extent) || (_OtherExtents::static_extent(__extent_to_pad_idx) != dynamic_extent)
                  || (static_padding_stride == _OtherExtents::static_extent(__extent_to_pad_idx)));
  }

  /**
   * Converting constructor from `layout_stride::mapping`.
   *
   * This overload participates in overload resolution only if `is_constructible_v<extents_type, OtherExtents>` is true
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class _OtherExtents,
    /* requires */ (
      std::is_constructible_v<extents_type, _OtherExtents>
    )
  )
  MDSPAN_CONDITIONAL_EXPLICIT((extents_type::rank() > 0))
  constexpr mapping(const layout_stride::mapping<_OtherExtents> &__other_mapping)
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping, std::integral_constant<size_t, __padded_stride_idx>{})),
        __extents(__other_mapping.extents())
  {
  }

  /**
   * Converting constructor from `layout_left_padded::mapping`.
   *
   * This overload participates in overload resolution only if `is_constructible_v<extents_type, OtherExtents>` is true.
   * Either `padding_value` or `OtherPaddingStride` must be `std::dynamic_extent`, or `padding_value == OtherPaddingStride`.
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class _Mapping,
    /* requires */ (
      detail::__is_layout_left_padded_mapping<_Mapping>::value
      && std::is_constructible_v<extents_type, typename _Mapping::extents_type>
    )
  )
  MDSPAN_CONDITIONAL_EXPLICIT((extents_type::rank() > 1 && (padding_value == dynamic_extent || _Mapping::padding_value == dynamic_extent)))
  constexpr
  mapping(const _Mapping &__other_mapping)
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping, std::integral_constant<size_t, __padded_stride_idx>{})),
        __extents(__other_mapping.extents())
  {
    static_assert(padding_value == dynamic_extent ||
                  _Mapping::padding_value == dynamic_extent ||
                  padding_value == _Mapping::padding_value);
  }

  /**
   * Converting constructor from `layout_right_padded::mapping`.
   *
   * This overload participates in overload resolution only if `extents_type::rank()` is 0 or 1 and `is_constructible_v<extents_type, OtherExtents>` is `true`.
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class _Mapping,
    /* requires */ (
      detail::__is_layout_right_padded_mapping<_Mapping>::value
      && extents_type::rank() <= 1
      && std::is_constructible_v<extents_type, typename _Mapping::extents_type>
    )
  )
  MDSPAN_CONDITIONAL_EXPLICIT((!std::is_convertible_v<typename _Mapping::extents_type, extents_type>))
  constexpr
  mapping(const _Mapping &__other_mapping) noexcept
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping.extents(), __other_mapping.extents().extent(__extent_to_pad_idx))),
        __extents(__other_mapping.extents())
  {}

  constexpr const extents_type &extents() const noexcept
  {
    return __extents;
  }

  constexpr std::array<index_type, extents_type::rank()>
  strides() const noexcept
  {
    if constexpr ( extents_type::rank() == 0 ) {
      return {};
    } else if constexpr ( extents_type::rank() == 1 ) {
      return {1};
    } else {
      index_type value = 1;
      std::array<index_type, extents_type::rank()> __s{};
      __s[__extent_to_pad_idx] = value;
      value *= __padded_stride.value(0);
      for (rank_type __r = __extent_to_pad_idx + 1; __r < extents_type::rank() - 1; ++__r)
      {
        __s[__r] = value;
        value *= __extents.extent(__r);
      }
      __s[extents_type::rank() - 1] = value;
      return __s;
    }
  }

  constexpr index_type
  required_span_size() const noexcept
  {
    if constexpr ( extents_type::rank() == 0 ) {
      return 1;
    } else if constexpr ( extents_type::rank() == 1 ) {
      return __extents.extent(0);
    } else {
      index_type value = __padded_stride.value(0);
      for (rank_type __r = 1; __r < extents_type::rank(); ++__r) {
        value *= __extents.extent(__r);
      }
      return value;
    }
  }

  /**
   * Return the mapping given the provided indices per rank.
   *
   * This overload participates in overload resolution only if:
   * - `sizeof...(Indices) == extents_type::rank()`,
   * - `(is_convertible_v<Indices, index_type> && ...) is true`, and
   * - (is_nothrow_constructible_v<index_type, Indices> && ...) is true.
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class... _Indices,
    /* requires */ (
      sizeof...(_Indices) == extents_type::rank()
      && (std::is_convertible_v<_Indices, index_type> && ...)
      && (std::is_nothrow_constructible_v<index_type, _Indices> && ...)
    )
  )
  constexpr size_t operator()(_Indices... __idxs) const noexcept
  {
    return __compute_offset(std::index_sequence_for<_Indices...>{}, __idxs...);
  }

  static constexpr bool is_always_unique() noexcept { return true; }
  static constexpr bool is_always_exhaustive() noexcept
  {
    return (extents_type::rank() <= size_t(1))
      || (extents_type::static_extent(__extent_to_pad_idx) != dynamic_extent
          && extents_type::static_extent(__extent_to_pad_idx) == __padded_stride_type::static_value());
  }
  static constexpr bool is_always_strided() noexcept { return true; }

  static constexpr bool is_unique() noexcept { return true; }
  constexpr bool is_exhaustive() const noexcept
  {
    return (extents_type::rank() < 2)
           || (__extents.extent(__extent_to_pad_idx) == __padded_stride.value(0));
  }
  static constexpr bool is_strided() noexcept { return true; }

  constexpr index_type stride(rank_type r) const noexcept
  {
    assert(r < extents_type::rank());
    if(r == 0) return 1;

    index_type value = __padded_stride.value(0);
    for (rank_type k = 1; k < r; k++) value *= __extents.extent(k);

    return value;
  }

  /**
   * Equality operator between `layout_left_padded`s
   *
   * This overload only participates in overload resolution if `OtherExtents::rank() == extents_type::rank()`.
   *
   * \note There is currently a difference from p2642r2, where this function is specified as taking
   * `layout_left_padded< padding_value >::mapping< Extents>`. However, this makes `padding_value` non-deducible.
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class _Mapping,
    /* requires */ (
      detail::__is_layout_left_padded_mapping<_Mapping>::value
      && (_Mapping::extents_type::rank() == extents_type::rank())
    )
  )
  friend constexpr bool operator==(const mapping &__left, const _Mapping &__right) noexcept
  {
    // Workaround for some compilers not short-circuiting properly with compile-time checks
    // i.e. we can't access stride(_padding_stride_idx) of a rank 0 mapping
    bool strides_equal = true;
    if constexpr (extents_type::rank() > size_t(1))
    {
      strides_equal = __left.stride(__padded_stride_idx) == __right.stride(__padded_stride_idx);
    }
    return (__left.extents() == __right.extents()) && strides_equal;
  }

#if !MDSPAN_HAS_CXX_20
  /**
   * Inequality operator between `layout_left_padded`s
   *
   * This overload only participates in overload resolution if `OtherExtents::rank() == extents_type::rank()`.
   */
  MDSPAN_TEMPLATE_REQUIRES(
    class _Mapping,
    /* requires */ (
      detail::__is_layout_left_padded_mapping<_Mapping>::value
      && (_Mapping::extents_type::rank() == extents_type::rank())
    )
  )
  friend constexpr bool operator!=(const mapping &__left, const _Mapping &__right) noexcept
  {
    return !(__left == __right);
  }
#endif
};

template <size_t PaddingValue>
template <class Extents>
class layout_right_padded<PaddingValue>::mapping {
public:
  static constexpr size_t padding_value = PaddingValue;

  using extents_type = Extents;
  using index_type = typename extents_type::index_type;
  using size_type = typename extents_type::size_type;
  using rank_type = typename extents_type::rank_type;
  using layout_type = layout_right_padded<padding_value>;

#ifndef MDSPAN_INTERNAL_TEST
  private:
#endif // MDSPAN_INTERNAL_TEST

  static constexpr rank_type __padded_stride_idx = detail::__layout_padded_constants<layout_type, extents_type>::__padded_stride_idx;
  static constexpr rank_type __extent_to_pad_idx = detail::__layout_padded_constants<layout_type, extents_type>::__extent_to_pad_idx;

  static_assert((padding_value != 0)
                || (extents_type::static_extent(__extent_to_pad_idx) == 0)
                || (extents_type::static_extent(__extent_to_pad_idx) == dynamic_extent),
                "if padding stride is 0, static_extent(extent-to-pad-rank) must also be 0 or dynamic_extent");

  using __padded_stride_type = detail::__padded_extent< padding_value, extents_type, __extent_to_pad_idx >;
  static constexpr size_t static_padding_stride = __padded_stride_type::static_value();

  typename __padded_stride_type::__static_array_type __padded_stride = {};
  extents_type __extents = {};

  constexpr index_type __compute_offset(std::index_sequence<>) const {
    return 0;
  }

  template <size_t Rank, class IndexOffset>
  constexpr index_type __compute_offset(std::index_sequence<Rank>,
                                        IndexOffset __index_offset) const {
    return __index_offset;
  }

  template <size_t... Ranks, class... IndexOffsets>
  constexpr index_type __compute_offset(std::index_sequence<Ranks...>,
                                        IndexOffsets... __index_offsets) const {
    // self-recursive fold trick from
    // https://github.com/llvm/llvm-project/blob/4d9771741d40cc9cfcccb6b033f43689d36b705a/libcxx/include/__mdspan/layout_right.h#L141
    index_type res = 0;
    ((res = static_cast<index_type>(__index_offsets) +
            (Ranks == __extent_to_pad_idx ? __padded_stride.value(0)
                                          : __extents.extent(Ranks)) *
                res),
     ...);
    return res;
  }

public:
#if !MDSPAN_HAS_CXX_20
  MDSPAN_INLINE_FUNCTION_DEFAULTED
      constexpr mapping()
      : mapping(extents_type{})
  {}
#else
  MDSPAN_INLINE_FUNCTION_DEFAULTED
      constexpr mapping()
    requires(static_padding_stride != dynamic_extent) = default;

  MDSPAN_INLINE_FUNCTION
      constexpr mapping()
    requires(static_padding_stride == dynamic_extent)
      : mapping(extents_type{})
  {}
#endif

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(const mapping&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED mapping& operator=(const mapping&) noexcept = default;

  /**
   * Initializes the mapping with the given extents.
   *
   * \param ext the given extents
   */
  MDSPAN_INLINE_FUNCTION
  constexpr mapping(const extents_type &__ext)
      : __padded_stride(__padded_stride_type::init_padding(__ext)), __extents(__ext) {}

  /**
   * Initializes the mapping with the given extents and the specified padding value.
   *
   * This overload participates in overload resolution only if `is_convertible_v<Size, index_type>`
   * is `true` and `is_nothrow_constructible_v<index_type, Size>` is `true`
   *
   * \param ext the given extents
   * \param padding_value the padding value
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class _Size,
      /* requires */ (
          std::is_convertible_v<_Size, index_type>
              && std::is_nothrow_constructible_v<index_type, _Size>
          )
      )
  MDSPAN_INLINE_FUNCTION
  constexpr mapping(const extents_type &__ext, _Size __dynamic_padding_value)
      : __padded_stride(__padded_stride_type::init_padding(__ext, static_cast<index_type>(__dynamic_padding_value))),
        __extents(__ext) {
    assert((padding_value == dynamic_extent) ||
           (static_cast<index_type>(padding_value) == static_cast<index_type>(__dynamic_padding_value)));
  }

  /**
   * Converting constructor from `layout_right::mapping`.
   *
   * This overload participates in overload resolution only if `is_constructible_v<extents_type, OtherExtents>` is true.
   * If `OtherExtents::rank() > 1` then one of `padding_value`, `static_extent(0)`, or `OtherExtents::static_extent(0)` must be `dynamic_extent`;
   * otherwise, `OtherExtents::static_extent(0)` must be equal to the least multiple of `padding_value` greater than or equal to `extents_type::static_extent(0)`
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class _OtherExtents,
      /* requires */ (
          std::is_constructible_v<extents_type, _OtherExtents>
          )
      )
  MDSPAN_CONDITIONAL_EXPLICIT((!std::is_convertible_v<_OtherExtents, extents_type>))
  constexpr mapping(const layout_right::mapping<_OtherExtents> &__other_mapping)
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping, std::integral_constant<size_t, __padded_stride_idx>{})),
        __extents(__other_mapping.extents())
  {
    static_assert((_OtherExtents::rank() > 1) || (__padded_stride_type::static_value() != dynamic_extent) || (_OtherExtents::static_extent(__extent_to_pad_idx) != dynamic_extent)
                  || (__padded_stride_type::static_value() == _OtherExtents::static_extent(__extent_to_pad_idx)));
  }

  /**
   * Converting constructor from `layout_stride::mapping`.
   *
   * This overload participates in overload resolution only if `is_constructible_v<extents_type, OtherExtents>` is true
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class _OtherExtents,
      /* requires */ (
          std::is_constructible_v<extents_type, _OtherExtents>
          )
      )
  MDSPAN_CONDITIONAL_EXPLICIT((extents_type::rank() > 0))
  constexpr mapping(const layout_stride::mapping<_OtherExtents> &__other_mapping)
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping, std::integral_constant<size_t, __padded_stride_idx>{})),
        __extents(__other_mapping.extents())
  {}

  /**
   * Converting constructor from `layout_right_padded::mapping`.
   *
   * This overload participates in overload resolution only if `is_constructible_v<extents_type, OtherExtents>` is true.
   * Either `padding_value` or `OtherPaddingStride` must be `std::dynamic_extent`, or `padding_value == OtherPaddingStride`.
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class _Mapping,
      /* requires */ (
          detail::__is_layout_right_padded_mapping<_Mapping>::value
              && std::is_constructible_v<extents_type, typename _Mapping::extents_type>
          )
      )
  MDSPAN_CONDITIONAL_EXPLICIT((extents_type::rank() > 1 &&
                               (padding_value == dynamic_extent ||
                                _Mapping::padding_value == dynamic_extent)))
  constexpr mapping(const _Mapping &__other_mapping)
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping, std::integral_constant<size_t, __padded_stride_idx>{})),
        __extents(__other_mapping.extents())
  {
    static_assert(padding_value == dynamic_extent ||
                  _Mapping::padding_value == dynamic_extent ||
                  padding_value == _Mapping::padding_value);
  }

  /**
   * Converting constructor from `layout_left_padded::mapping`.
   *
   * This overload participates in overload resolution only if `extents_type::rank()` is 0 or 1 and `is_constructible_v<extents_type, OtherExtents>` is `true`.
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class _Mapping,
      /* requires */ (
          detail::__is_layout_left_padded_mapping<_Mapping>::value
                  && extents_type::rank() <= 1
          && std::is_constructible_v<extents_type, typename _Mapping::extents_type>
          )
      )
  MDSPAN_CONDITIONAL_EXPLICIT((!std::is_convertible_v<typename _Mapping::extents_type, extents_type>))
  constexpr mapping(const _Mapping &__other_mapping) noexcept
      : __padded_stride(__padded_stride_type::init_padding(__other_mapping.extents(), __other_mapping.extents().extent(__extent_to_pad_idx))),
        __extents(__other_mapping.extents())
  {}

  constexpr const extents_type &extents() const noexcept
  {
    return __extents;
  }

  constexpr std::array<index_type, extents_type::rank()>
  strides() const noexcept
  {
    if constexpr ( extents_type::rank() == 0 ) {
      return {};
    } else if constexpr ( extents_type::rank() == 1 ) {
      return {1};
    } else {
      index_type value = 1;
      std::array<index_type, extents_type::rank()> __s{};
      __s[__extent_to_pad_idx] = value;
      value *= __padded_stride.value(0);
      for (rank_type __r = __extent_to_pad_idx - 1; __r > 0; --__r)
      {
        __s[__r] = value;
        value *= __extents.extent(__r);
      }
      __s[0] = value;
      return __s;
    }
  }

  constexpr index_type
  required_span_size() const noexcept
  {
    if constexpr ( extents_type::rank() == 0 ) {
      return 1;
    } else if constexpr ( extents_type::rank() == 1 ) {
      return __extents.extent(0);
    } else {
      index_type value = 1;
      for (rank_type __r = 0; __r < __extent_to_pad_idx; ++__r)
      {
        value *= __extents.extent(__r);
      }
      return value * __padded_stride.value(0);
    }
  }

  /**
   * Return the mapping given the provided indices per rank.
   *
   * This overload participates in overload resolution only if:
   * - `sizeof...(Indices) == extents_type::rank()`,
   * - `(is_convertible_v<Indices, index_type> && ...) is true`, and
   * - (is_nothrow_constructible_v<index_type, Indices> && ...) is true.
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class... _Indices,
      /* requires */ (
          sizeof...(_Indices) == extents_type::rank()
          && (std::is_convertible_v<_Indices, index_type> && ...)
          && (std::is_nothrow_constructible_v<index_type, _Indices> && ...)
          )
      )
  constexpr size_t operator()(_Indices... __idxs) const noexcept
  {
    return __compute_offset(std::index_sequence_for<_Indices...>{}, __idxs...);
  }

  static constexpr bool is_always_unique() noexcept { return true; }
  static constexpr bool is_always_exhaustive() noexcept
  {
    return (extents_type::rank() <= size_t(1))
           || (extents_type::static_extent(__extent_to_pad_idx) != dynamic_extent
               && extents_type::static_extent(__extent_to_pad_idx) == __padded_stride_type::static_value());
  }
  static constexpr bool is_always_strided() noexcept { return true; }

  static constexpr bool is_unique() noexcept { return true; }
  constexpr bool is_exhaustive() const noexcept
  {
    return (extents_type::rank() < 2)
           || (__extents.extent(__extent_to_pad_idx) == __padded_stride.value(0));
  }
  static constexpr bool is_strided() noexcept { return true; }

  constexpr index_type stride(rank_type r) const noexcept
  {
    assert(r < extents_type::rank());
    if(r == extents_type::rank() - 1) return 1;

    index_type value = __padded_stride.value(0);
    for (rank_type k = extents_type::rank() - 2; k > r; k--) value *= __extents.extent(k);

    return value;
  }

  /**
   * Equality operator between `layout_right_padded`s
   *
   * This overload only participates in overload resolution if `OtherExtents::rank() == extents_type::rank()`.
   *
   * \note There is currently a difference from p2642r2, where this function is specified as taking
   * `layout_right_padded< padding_value >::mapping< Extents>`. However, this makes `padding_value` non-deducible.
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class _Mapping,
      /* requires */ (
          detail::__is_layout_right_padded_mapping<_Mapping>::value
          && (_Mapping::extents_type::rank() == extents_type::rank())
          )
      )
  friend constexpr bool operator==(const mapping &__left, const _Mapping &__right) noexcept
  {
    // Workaround for some compilers not short-circuiting properly with compile-time checks
    // i.e. we can't access stride(_padding_stride_idx) of a rank 0 mapping
    bool strides_equal = true;
    if constexpr (extents_type::rank() > size_t(1))
    {
      strides_equal = __left.stride(__padded_stride_idx) == __right.stride(__padded_stride_idx);
    }
    return (__left.extents() == __right.extents()) && strides_equal;
  }

#if !MDSPAN_HAS_CXX_20
  /**
   * Inequality operator between `layout_right_padded`s
   *
   * This overload only participates in overload resolution if `OtherExtents::rank() == extents_type::rank()`.
   */
  MDSPAN_TEMPLATE_REQUIRES(
      class _Mapping,
      /* requires */ (
          detail::__is_layout_right_padded_mapping<_Mapping>::value
          && (_Mapping::extents_type::rank() == extents_type::rank())
          )
      )
  friend constexpr bool operator!=(const mapping &__left, const _Mapping &__right) noexcept
  {
    return !(__left == __right);
  }
#endif
};
}
}
