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
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

#pragma once

#include "submdspan_extents.hpp"
#include "submdspan_mapping.hpp"

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
template <class ElementType, class Extents, class LayoutPolicy,
          class AccessorPolicy, class... SliceSpecifiers>
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan(const mdspan<ElementType, Extents, LayoutPolicy, AccessorPolicy> &src,
          SliceSpecifiers... slices) {

#if defined(MDSPAN_ENABLE_P3663)
  [[maybe_unused]] auto [...canonical_slices] = submdspan_canonicalize_slices(src.extents(), slices...);
  static_assert(sizeof...(canonical_slices) == sizeof...(slices));

#if 0
  // TODO FIX IN PROPOSAL: [canonical_]slices (incorrect formatting).
  auto sub_map_result = submdspan_mapping(src.mapping(), canonical_slices...);
  // TODO FIX IN PROPOSAL: It's src.data_handle(), not src.data().
  // Missing "typename" before AccessorPolicy::offset_policy.
  return mdspan(src.accessor().offset(src.data_handle(), sub_map_result.offset),
                sub_map_result.mapping,
                typename AccessorPolicy::offset_policy(src.accessor()));  
#endif // 0
#endif

//#else
  const auto sub_submdspan_mapping_result = submdspan_mapping(src.mapping(), slices...);
  // NVCC has a problem with the deduction so lets figure out the type
  using sub_mapping_t = std::remove_cv_t<decltype(sub_submdspan_mapping_result.mapping)>;
  using sub_extents_t = typename sub_mapping_t::extents_type;
  using sub_layout_t = typename sub_mapping_t::layout_type;
  using sub_accessor_t = typename AccessorPolicy::offset_policy;
  return mdspan<ElementType, sub_extents_t, sub_layout_t, sub_accessor_t>(
      src.accessor().offset(src.data_handle(), sub_submdspan_mapping_result.offset),
      sub_submdspan_mapping_result.mapping,
      sub_accessor_t(src.accessor()));
//#endif
}
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
