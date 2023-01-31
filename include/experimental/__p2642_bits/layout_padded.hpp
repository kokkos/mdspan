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
#include "../__p0009_bits/extents.hpp"

namespace std {
namespace experimental {
namespace detail {

// offset_index_sequence idea comes from "offset_sequence" here:
// https://devblogs.microsoft.com/oldnewthing/20200625-00/?p=103903
//
// offset_index_sequence adds N to each element of the given IndexSequence.
// We can't just template on the parameter pack of indices directly;
// the pack needs to be contained in some type.
// We choose index_sequence because it stores no run-time data.
template <size_t N, class IndexSequence>
struct offset_index_sequence;

template <size_t N, size_t... Indices>
struct offset_index_sequence<N, index_sequence<Indices...>>
{
  using type = index_sequence<(Indices + N)...>;
};

template <size_t N, typename IndexSequence>
using offset_index_sequence_t = typename offset_index_sequence<N, IndexSequence>::type;

// iota_index_sequence defines the half-open sequence
// begin, begin+1, begin+2, ..., end-1.
// If end == begin, then the sequence is empty (we permit this).
//
// Defining the struct first, rather than going straight to the type alias,
// lets us check the template arguments.
template <size_t begin, size_t end>
struct iota_index_sequence
{
  static_assert(end >= begin, "end must be >= begin.");
  using type =
      offset_index_sequence_t<begin, std::make_index_sequence<end - begin>>;
};

template <class Extents, class Enabled = void>
struct p_left;

template <class Extents>
struct p_left<Extents, enable_if_t<(Extents::rank() < 2)>>
{
  using type = std::index_sequence<>;
};

template <class IndexType, size_t... Extents>
struct p_left<extents<IndexType, Extents...>>
{
  using extents_type = extents<IndexType, Extents...>;
  using type = typename iota_index_sequence<1, extents_type::rank()>;
};

template<class Alignment, class Offset>
MDSPAN_INLINE_FUNCTION
constexpr auto
find_aligned_offset(Alignment align, Offset offset)
{
  static_assert(Alignment != 0, "alignment of 0 is not allowed");
  return ( ( offset + align - 1 ) / align ) * align;
}

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
    return find_aligned_offset(padding_stride, ExtentsType::static_extent(0));
  } else {
    return dynamic_extent;
  }
}



template <class Extents, class Enabled = void>
struct inner_extents_impl;

template <class Extents>
struct inner_extents_impl<Extents, enable_if_t<(Extents::rank() < 2)>>
{
  using type = Extents;
};

template <class IndexType, size_t... Extents>
struct inner_extents_impl<extents<IndexType, Extents...>>
{
  using extents_type = extents<IndexType, Extents...>;
  using type = extents<IndexType, extents_type::static_extent(iota_index_sequence<1,)
};

}

template<size_t padding_stride = dynamic_extent>
struct layout_left_padded
{
  template<class Extents>
  class mapping {
public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_left_padded<padding_stride>;

private:

    static_assert(padding_stride != 0, "padding stride cannot be 0");

    static constexpr size_t actual_padding_stride = detail::get_actual_padding_stride<Extents, padding_stide>();

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
