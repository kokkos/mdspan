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
#include "../__p0009_bits/mdspan.hpp"
#include "../__p0009_bits/layout_left.hpp"

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

template <class _Extents, class _Enabled = void>
struct __p_left;

template <class _Extents>
struct __p_left<_Extents, enable_if_t<(_Extents::rank() < 2)>>
{
  using __type = std::index_sequence<>;
};

template <class _IndexType, size_t... _Extents>
struct __p_left<extents<_IndexType, _Extents...>>
{
  using __extents_type = extents<_IndexType, _Extents...>;
  using __type = typename iota_index_sequence<1, __extents_type::rank()>::type;
};

template<class _T>
MDSPAN_INLINE_FUNCTION
constexpr auto
__find_aligned_offset(_T __alignment, _T __offset)
{
  if ( __alignment == 0 )
    return _T(0);
  else
    return ( ( __offset + __alignment - 1 ) / __alignment) * __alignment;
}

template<class _ExtentsType, size_t _PaddingStride>
MDSPAN_INLINE_FUNCTION
constexpr size_t
__get_actual_padding_stride()
{
  constexpr auto __rank = _ExtentsType::rank();

  if constexpr (__rank <= size_t(1)) {
    return _PaddingStride;
  } else if constexpr (_PaddingStride != dynamic_extent &&
                       _ExtentsType::static_extent(0) != dynamic_extent) {
    static_assert((_PaddingStride != 0) || (_ExtentsType::static_extent(0) == 0), "padding stride can be 0 only if extents_type::static_extent(0) is 0");
    return __find_aligned_offset(_PaddingStride, _ExtentsType::static_extent(0));
  } else {
    return dynamic_extent;
  }
}

template<size_t _ExtentToSub, class _Extents, size_t _NewExtent, class _Indices>
struct __substitute_extents_impl;

template<size_t _ExtentToSub, class _Extents, size_t _NewExtent, size_t... _Indices>
struct __substitute_extents_impl<_ExtentToSub, _Extents, _NewExtent, index_sequence<_Indices...>>
{
  using __type = extents<typename _Extents::index_type, ((_Indices == _ExtentToSub) ? _NewExtent : _Extents::static_extent(_Indices))...>;

  MDSPAN_INLINE_FUNCTION
  static constexpr auto
  __construct(const _Extents &__extents, const extents<typename _Extents::index_type, _NewExtent> &__new_extents)
  {
    return __type{((_Indices == _ExtentToSub) ? __new_extents.extent(0) : __extents.extent(_Indices))...};
  }

  MDSPAN_INLINE_FUNCTION
  static constexpr auto
  __construct(const _Extents &__extents)
  {
    return __type{__extents.extent(_Indices)...};
  }
};

template<size_t _ExtentToSub, class _Extents, size_t _NewExtent>
using __substitute_extents = __substitute_extents_impl<_ExtentToSub, _Extents, _NewExtent, make_index_sequence<_Extents::rank()>>;

template<class _Extents, size_t _ActualPaddingStride, class _Enabled = void>
struct __inner_extents_left
{
  using __subs_type = __substitute_extents< 0, _Extents, _ActualPaddingStride >;
  using __type = typename __subs_type::__type;

  template<size_t _PaddingStride>
  MDSPAN_INLINE_FUNCTION
  static constexpr auto
  __construct(const _Extents &__extents)
  {
    if constexpr (_PaddingStride == dynamic_extent)
    {
      return __subs_type::__construct(__extents);
    } else {
      // This is a corner case where `_PaddingStride` is not dynamic but `_ActualPaddingStride` is
      // because `_Extents::static_extents(0)` is dynamic. We need to initialize it with a run-time
      // value that is the least multiple of `_PaddingStride` greater than or equal to `_Extents::static_extents(0)`
      if constexpr (_Extents::static_extent(0) == dynamic_extent)
      {
        const auto __s_left = __find_aligned_offset(_PaddingStride, __extents.extent(0));
        return __subs_type::__construct(__extents, extents<typename _Extents::index_type, _ActualPaddingStride>(__s_left));
      } else {
        return __subs_type::__construct(__extents, extents<typename _Extents::index_type, _ActualPaddingStride>{});
      }
    }
  }
};

template<class _Extents, size_t _ActualPaddingStride>
struct __inner_extents_left<_Extents, _ActualPaddingStride, enable_if_t<_Extents::rank() <= size_t(1)>>
{
  using __type = _Extents;

  template<size_t _PaddingStride>
  MDSPAN_INLINE_FUNCTION
  static constexpr const _Extents &
  __construct(const _Extents &__extents)
  {
    return __extents;
  }
};

template <class _Extents, typename _Enabled = void>
struct __unpadded_extent_type_impl
{
  using __type = extents<typename _Extents::index_type, _Extents::static_extent(0)>;

  MDSPAN_INLINE_FUNCTION
  static constexpr auto
  __construct(const _Extents &__extents)
  {
    return __type(__extents.extent(0));
  }
};

template <class _Extents>
struct __unpadded_extent_type_impl<_Extents, enable_if_t<(_Extents::rank() == 0)>>
{
  using __type = extents<typename _Extents::index_type>;

  MDSPAN_INLINE_FUNCTION
  static constexpr auto
  __construct([[maybe_unused]] const _Extents &__extents)
  {
    return __type{};
  }
};
}

template <size_t padding_stride = dynamic_extent>
struct layout_left_padded
{
  template <class Extents>
  class mapping {
public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_left_padded<padding_stride>;

#ifndef MDSPAN_INTERNAL_TEST
private:
#endif // MDSPAN_INTERNAL_TEST

    static_assert((padding_stride != 0) || (extents_type::static_extent(0) == 0), "padding stride can be 0 only if extents_type::static_extent(0) is 0");

    static constexpr size_t __actual_padding_stride = detail::__get_actual_padding_stride<extents_type, padding_stride>();

    using __inner_extents_type = typename detail::__inner_extents_left<extents_type, __actual_padding_stride>::__type;
    using __unpadded_extent_type = typename detail::__unpadded_extent_type_impl<extents_type>::__type;
    using __inner_mapping_type = layout_left::template mapping<__inner_extents_type>;

    __inner_mapping_type __inner_mapping;
    __unpadded_extent_type __unpadded_extent;

public:
#if !MDSPAN_HAS_CXX_20
    MDSPAN_INLINE_FUNCTION_DEFAULTED
    constexpr mapping()
        : mapping(extents_type{})
    {}
#else
    MDSPAN_INLINE_FUNCTION_DEFAULTED
    constexpr mdspan()
      requires(__actual_padding_stride != dynamic_extent) = default;

    MDSPAN_INLINE_FUNCTION
    constexpr mdspan()
      requires(__actual_padding_stride == dynamic_extent)
        : mapping(extents_type{})
    {}
#endif

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(const mapping&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED mapping& operator=(const mapping&) noexcept = default;

    MDSPAN_INLINE_FUNCTION constexpr
    mapping(const extents_type& __ext)
      : __inner_mapping(detail::__inner_extents_left<extents_type, __actual_padding_stride>::template __construct<padding_stride>(__ext)),
        __unpadded_extent(detail::__unpadded_extent_type_impl<extents_type>::__construct(__ext))
    {}

    template<class Size>
    // TODO: constraints
    constexpr mapping(const extents_type& ext, Size padding_value)
    {

    }

#if 0
    template<size_t other_padding_stride, class OtherExtents>
    constexpr explicit( /* see below */ )
        mapping(const layout_left_padded<other_padding_stride>::mapping<OtherExtents>&);

    template<size_t other_padding_stride, class OtherExtents>
    constexpr explicit(not is_convertible_v<OtherExtents, extents_type>)
        mapping(const layout_right_padded<other_padding_stride>::mapping<OtherExtents>&) noexcept;


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
#endif
  };
};
}
}