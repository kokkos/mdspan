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

template <class _Mapping>
inline constexpr bool __is_layout_left_padded_mapping_of = __is_layout_left_padded<typename _Mapping::layout_type>::value;

template <class _Layout>
struct __is_layout_right_padded : false_type {};

template <size_t _PaddingStride>
struct __is_layout_right_padded<layout_right_padded<_PaddingStride>> : true_type {};

template <class _Mapping, class _Enabled = void>
struct __is_layout_right_padded_mapping : false_type {};

template <class _Mapping>
struct __is_layout_right_padded_mapping<_Mapping, enable_if_t<__is_layout_right_padded<typename _Mapping::layout_type>::value>>
    : true_type {};

template <class _Mapping>
inline constexpr bool __is_layout_right_padded_mapping_of = __is_layout_right_padded<typename _Mapping::layout_type>::value;

}
}
}
