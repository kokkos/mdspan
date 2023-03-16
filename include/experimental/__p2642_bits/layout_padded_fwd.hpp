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

#include "../__p0009_bits/dynamic_extent.hpp"

namespace std {
namespace experimental {

template <size_t padding_stride = dynamic_extent>
struct layout_left_padded {
  template <class _Extents>
  class mapping;
};

template <size_t padding_stride = dynamic_extent>
struct layout_right_padded {
  template <class _Extents>
  class mapping;
};

namespace detail {

template <class _Layout>
struct __is_layout_left_padded : false_type {};

template <size_t _PaddingStride>
struct __is_layout_left_padded<layout_left_padded<_PaddingStride>> : true_type {};

template <class _Mapping, class _Enabled = void>
struct __is_layout_left_padded_mapping : false_type {};

template <class _Mapping>
struct __is_layout_left_padded_mapping<_Mapping, enable_if_t<__is_layout_left_padded<typename _Mapping::layout_type>::value>>
    : true_type {};

template <class _Layout>
struct __is_layout_right_padded : false_type {};

template <size_t _PaddingStride>
struct __is_layout_right_padded<layout_right_padded<_PaddingStride>> : true_type {};

template <class _Mapping, class _Enabled = void>
struct __is_layout_right_padded_mapping : false_type {};

template <class _Mapping>
struct __is_layout_right_padded_mapping<_Mapping, enable_if_t<__is_layout_right_padded<typename _Mapping::layout_type>::value>>
    : true_type {};

template <class _Layout>
struct __padded_layout_padding_stride;

template <size_t _PaddingStride>
struct __padded_layout_padding_stride<layout_left_padded<_PaddingStride>> : std::integral_constant<size_t, _PaddingStride> {};

template <size_t _PaddingStride>
struct __padded_layout_padding_stride<layout_right_padded<_PaddingStride>> : std::integral_constant<size_t, _PaddingStride> {};

template <class _LayoutExtentsType, class _PaddedLayoutMappingType, class RankType, RankType _CheckExtentToPadIdx>
constexpr void __check_layout_padded_layout_extents_compatibility(integral_constant< RankType, _CheckExtentToPadIdx >)
{
  using __padded_layout_extents_type = typename _PaddedLayoutMappingType::extents_type;
  constexpr auto __padded_layout_padding = __padded_layout_padding_stride<typename _PaddedLayoutMappingType::layout_type>::value;
  constexpr RankType __check_extent_to_pad_idx = _CheckExtentToPadIdx;
  if constexpr ((_LayoutExtentsType::rank() > 1)
                && (_LayoutExtentsType::static_extent(__check_extent_to_pad_idx) != dynamic_extent)
                && (__padded_layout_extents_type::static_extent(__check_extent_to_pad_idx) != dynamic_extent)
                && (__padded_layout_padding != dynamic_extent))
  {
    if constexpr (__padded_layout_padding == 0) {
      static_assert(_LayoutExtentsType::static_extent(__check_extent_to_pad_idx) == 0);
    } else {
      static_assert(_LayoutExtentsType::static_extent(__check_extent_to_pad_idx) % __padded_layout_padding == 0);
    }
  }
}
}
}
}
