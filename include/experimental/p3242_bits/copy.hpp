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

#include "../__p0009_bits/default_accessor.hpp"
#include "../__p0009_bits/extents.hpp"
#include "../__p0009_bits/layout_left.hpp"
#include "../__p0009_bits/layout_right.hpp"
#include "../__p0009_bits/mdspan.hpp"
#include <array>
#include <cstring>
#include <functional>
#include <utility>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
namespace MDSPAN_IMPL_PROPOSED_NAMESPACE {
namespace detail {

template <class Extents, class F, class ArrayType>
constexpr void apply_fun_over_extents(const Extents &ext, F &fun,
                                      ArrayType &indices,
                                      std::index_sequence<>) {
  std::apply(fun, indices);
}

template <class Extents, class F, class ArrayType, size_t R, size_t... Ranks>
constexpr void apply_fun_over_extents(const Extents &ext, F &fun,
                                      ArrayType &indices,
                                      std::index_sequence<R, Ranks...>) {
  using index_type = typename Extents::index_type;
  for (index_type i = 0; i < ext.extent(R); ++i) {
    indices[R] = i;
    apply_fun_over_extents(ext, fun, indices, std::index_sequence<Ranks...>{});
  }
}

template <size_t N, class Indices> struct make_reverse_index_sequence_impl;

template <size_t N, size_t... Indices>
struct make_reverse_index_sequence_impl<N, std::index_sequence<Indices...>> {
  using type = std::index_sequence<(N - 1 - Indices)...>;
};

template <size_t N>
using make_reverse_index_sequence = typename make_reverse_index_sequence_impl<
    N, std::make_index_sequence<N>>::type;

template <class SrcMDSpanType, class DstMDSpanType, typename Enabled = void>
struct mdspan_copy_impl {
  using extents_type = typename DstMDSpanType::extents_type;

  static constexpr void copy_over_extents(const extents_type &ext,
                                          const SrcMDSpanType &src,
                                          const DstMDSpanType &dst) {
    // Generic copy algorithm; this assumes a roughly layout-right traversal
    // but this may not be cache efficient if we can't determine anything about
    // the layout memory ordering
    constexpr auto rank = extents_type::rank();
    auto indices = std::array<typename extents_type::index_type, rank>{};
    apply_fun_over_extents(
        ext, [&src, &dst](auto... idxs) { dst(idxs...) = src(idxs...); },
        indices, make_reverse_index_sequence<rank>{});
  }
};

template <class ElementType, class SrcExtents, class DstExtents>
struct mdspan_copy_impl<
    mdspan<ElementType, SrcExtents, layout_left, default_accessor<ElementType>>,
    mdspan<ElementType, DstExtents, layout_left, default_accessor<ElementType>>,
    void> {
  using extents_type = DstExtents;
  using src_mdspan_type = mdspan<ElementType, SrcExtents, layout_left,
                                 default_accessor<ElementType>>;
  using dst_mdspan_type = mdspan<ElementType, DstExtents, layout_left,
                                 default_accessor<ElementType>>;

  static constexpr void copy_over_extents(const extents_type &ext,
                                          const src_mdspan_type &src,
                                          const dst_mdspan_type &dst) {
    std::memcpy(dst.data_handle(), src.data_handle(), dst.mapping().required_span_size() * sizeof(ElementType));
  }
};

template <class ElementType, class SrcExtents, class DstExtents>
struct mdspan_copy_impl<
    mdspan<ElementType, SrcExtents, layout_right, default_accessor<ElementType>>,
    mdspan<ElementType, DstExtents, layout_right, default_accessor<ElementType>>,
    void> {
  using extents_type = DstExtents;
  using src_mdspan_type = mdspan<ElementType, SrcExtents, layout_left,
                                 default_accessor<ElementType>>;
  using dst_mdspan_type = mdspan<ElementType, DstExtents, layout_left,
                                 default_accessor<ElementType>>;

  static constexpr void copy_over_extents(const extents_type &ext,
                                          const src_mdspan_type &src,
                                          const dst_mdspan_type &dst) {
    std::memcpy(dst.data_handle(), src.data_handle(), dst.mapping().required_span_size() * sizeof(ElementType));
  }
};
} // namespace detail

template <class SrcElementType, class SrcExtents, class SrcLayoutPolicy,
          class SrcAccessorPolicy, class DstElementType, class DstExtents,
          class DstLayoutPolicy, class DstAccessorPolicy>
void copy(
    mdspan<SrcElementType, SrcExtents, SrcLayoutPolicy, SrcAccessorPolicy> src,
    mdspan<DstElementType, DstExtents, DstLayoutPolicy, DstAccessorPolicy>
        dst) {
  using src_type =
      mdspan<SrcElementType, SrcExtents, SrcLayoutPolicy, SrcAccessorPolicy>;
  using dst_type =
      mdspan<DstElementType, DstExtents, DstLayoutPolicy, DstAccessorPolicy>;
  detail::mdspan_copy_impl<src_type, dst_type>::copy_over_extents(src.extents(),
                                                                  src, dst);
}
} // namespace MDSPAN_IMPL_PROPOSED_NAMESPACE
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
