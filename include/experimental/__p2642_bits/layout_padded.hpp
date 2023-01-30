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
namespace detail {

template<class ExtentsType, size_t padding_stride>
MDSPAN_INLINE_FUNCTION
constexpr size_t
get_actual_padding_stride()
{
  using index_type = typename ExtentsType::index_type;

  constexpr auto rank = ExtentsType::rank();

  if constexpr (rank == 0 || rank == size_t(1)) {
    return padding_stride;
  } else if constexpr (padding_stride != dynamic_extent &&
                       ExtentsType::static_extent(0) != dynamic_extent) {
    // Least multiple of padding_stride
    // that is >= ExtentsType::static_extent(0).
    if constexpr (padding_stride >= ExtentsType::static_extent(0)) {
      return padding_stride;
    }
    else if constexpr (padding_stride == 0) {
      // FIXME (mfh 2023/01/16) Perhaps the spec needs
      // fixing for this case.  It's not clear what to do.
      return padding_stride;
    }
    else if constexpr (ExtentsType::static_extent(0)) {
      // FIXME (mfh 2023/01/16) Perhaps the spec needs
      // fixing for this case.  It's not clear what to do.
      return padding_stride;
    }
    else {
      return least_multiple_of_x_greater_than_or_equal_to_y(
          padding_stride, ExtentsType::static_extent(0));
    }
  }
  else {
    return dyn;
  }
}
}

template<size_t padding_stride = dynamic_extent>
struct layout_left_padded {
  template<class Extents>
  class mapping {
public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_left_padded<padding_stride>;

private:
    static constexpr size_t actual_padding_stride = /* see-below */; // exposition only

    using <it>inner-extents-type</it> = /* see-below */; // exposition only
    using <it>unpadded-extent-type</it> = /* see-below */; // exposition only
    using <it>inner-mapping-type</it> =
        layout_left::template mapping<<it>inner-extents-type</it>>; // exposition only

    <it>inner-mapping-type</it> <it>inner-mapping_</it>; // exposition only
    <it>unpadded-extent-type</it> <it>unpadded-extent_</it>; // exposition only

public:
    MDSPAN_INLINE_FUNCTION constexpr
    mapping(const extents_type& ext);

    template<class Size>
    constexpr mapping(const extents_type& ext, Size padding_value);

    template<size_t other_padding_stride, class OtherExtents>
    constexpr explicit( /* see below */ )
        mapping(const layout_left_padded<other_padding_stride>::mapping<OtherExtents>&);

    template<size_t other_padding_stride, class OtherExtents>
    constexpr explicit(not is_convertible_v<OtherExtents, extents_type>)
        mapping(const layout_right_padded<other_padding_stride>::mapping<OtherExtents>&) noexcept;

    constexpr mapping(const mapping&) noexcept = default;
    mapping& operator=(const mapping&) noexcept = default;

    constexpr extents_type extents() const noexcept;

    constexpr std::array<index_type, extents_type::rank()>
    strides() const noexcept;

    constexpr index_type required_span_size() const noexcept;

    template<class... Indices>
    constexpr size_t operator()(Indices... idxs) const noexcept;

    static constexpr bool is_always_unique() noexcept { return true; }
    static constexpr bool is_always_exhaustive() noexcept;
    static constexpr bool is_always_strided() noexcept { return true; }

    static constexpr bool is_unique() noexcept { return true; }
    constexpr bool is_exhaustive() const noexcept;
    static constexpr bool is_strided() noexcept { return true; }

    constexpr index_type stride(rank_type r) const noexcept;
  };
};

}
}
