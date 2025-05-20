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

#include <complex>
#include <tuple>

#include "strided_slice.hpp"
#include "../__p0009_bits/utility.hpp"

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
namespace detail {

// Mapping from submapping ranks to srcmapping ranks
// InvMapRank is an index_sequence, which we build recursively
// to contain the mapped indices.
// end of recursion specialization containing the final index_sequence
template <size_t Counter, size_t... MapIdxs>
MDSPAN_INLINE_FUNCTION
constexpr auto inv_map_rank(std::integral_constant<size_t, Counter>, std::index_sequence<MapIdxs...>) {
  return std::index_sequence<MapIdxs...>();
}

// specialization reducing rank by one (i.e., integral slice specifier)
template<size_t Counter, class Slice, class... SliceSpecifiers, size_t... MapIdxs>
MDSPAN_INLINE_FUNCTION
constexpr auto inv_map_rank(std::integral_constant<size_t, Counter>, std::index_sequence<MapIdxs...>, Slice,
                  SliceSpecifiers... slices) {
  using next_idx_seq_t = std::conditional_t<std::is_convertible_v<Slice, size_t>,
                                       std::index_sequence<MapIdxs...>,
                                       std::index_sequence<MapIdxs..., Counter>>;

  return inv_map_rank(std::integral_constant<size_t,Counter + 1>(), next_idx_seq_t(),
                                     slices...);
}

// Helper for identifying strided_slice
template <class T> struct is_strided_slice : std::false_type {};

template <class OffsetType, class ExtentType, class StrideType>
struct is_strided_slice<
    strided_slice<OffsetType, ExtentType, StrideType>> : std::true_type {};

// Helper for identifying valid pair like things
template <class T, class IndexType> struct index_pair_like : std::false_type {};

template <class IdxT1, class IdxT2, class IndexType>
struct index_pair_like<std::pair<IdxT1, IdxT2>, IndexType> {
  static constexpr bool value = std::is_convertible_v<IdxT1, IndexType> &&
                                std::is_convertible_v<IdxT2, IndexType>;
};

template <class IdxT1, class IdxT2, class IndexType>
struct index_pair_like<std::tuple<IdxT1, IdxT2>, IndexType> {
  static constexpr bool value = std::is_convertible_v<IdxT1, IndexType> &&
                                std::is_convertible_v<IdxT2, IndexType>;
};

template <class IdxT1, class IdxT2, class IndexType>
struct index_pair_like<tuple<IdxT1, IdxT2>, IndexType> {
  static constexpr bool value = std::is_convertible_v<IdxT1, IndexType> &&
                                std::is_convertible_v<IdxT2, IndexType>;
};

template <class IdxT, class IndexType>
struct index_pair_like<std::complex<IdxT>, IndexType> {
  static constexpr bool value = std::is_convertible_v<IdxT, IndexType>;
};

template <class IdxT, class IndexType>
struct index_pair_like<std::array<IdxT, 2>, IndexType> {
  static constexpr bool value = std::is_convertible_v<IdxT, IndexType>;
};

// first_of(slice): getting begin of slice specifier range
MDSPAN_TEMPLATE_REQUIRES(
  class Integral,
  /* requires */(std::is_convertible_v<Integral, size_t>)
)
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(const Integral &i) {
  return i;
}

template<class Integral, Integral v>
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(const std::integral_constant<Integral, v>&) {
  return integral_constant<Integral, v>();
}

MDSPAN_INLINE_FUNCTION
constexpr integral_constant<size_t, 0>
first_of(const ::MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t &) {
  return integral_constant<size_t, 0>();
}

MDSPAN_TEMPLATE_REQUIRES(
  class Slice,
  /* requires */(index_pair_like<Slice, size_t>::value)
)
MDSPAN_INLINE_FUNCTION
constexpr auto first_of(const Slice &i) {
  return get<0>(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::tuple<IdxT1, IdxT2>, size_t>::value)
  )
constexpr auto first_of(const std::tuple<IdxT1, IdxT2>& i) {
  return get<0>(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::pair<IdxT1, IdxT2>, size_t>::value)
  )
MDSPAN_INLINE_FUNCTION
constexpr auto first_of(const std::pair<IdxT1, IdxT2>& i) {
  return i.first;
}

template<class T>
MDSPAN_INLINE_FUNCTION
constexpr auto first_of(const std::complex<T> &i) {
  return i.real();
}

template <class OffsetType, class ExtentType, class StrideType>
MDSPAN_INLINE_FUNCTION
constexpr OffsetType
first_of(const strided_slice<OffsetType, ExtentType, StrideType> &r) {
  return r.offset;
}

// last_of(slice): getting end of slice specifier range
// We need however not just the slice but also the extents
// of the original view and which rank from the extents.
// This is needed in the case of slice being full_extent_t.
MDSPAN_TEMPLATE_REQUIRES(
  size_t k, class Extents, class Integral,
  /* requires */(std::is_convertible_v<Integral, size_t>)
)
MDSPAN_INLINE_FUNCTION
constexpr Integral
    last_of(std::integral_constant<size_t, k>, const Extents &, const Integral &i) {
  return i;
}

MDSPAN_TEMPLATE_REQUIRES(
  size_t k, class Extents, class Slice,
  /* requires */(index_pair_like<Slice, size_t>::value)
)
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &,
                       const Slice &i) {
  return get<1>(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  size_t k, class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::tuple<IdxT1, IdxT2>, size_t>::value)
  )
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &, const std::tuple<IdxT1, IdxT2>& i) {
  return get<1>(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  size_t k, class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::pair<IdxT1, IdxT2>, size_t>::value)
  )
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &, const std::pair<IdxT1, IdxT2>& i) {
  return i.second;
}

template<size_t k, class Extents, class T>
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &, const std::complex<T> &i) {
  return i.imag();
}

// Suppress spurious warning with NVCC about no return statement.
// This is a known issue in NVCC and NVC++
// Depending on the CUDA and GCC version we need both the builtin
// and the diagnostic push. I tried really hard to find something shorter
// but no luck ...
#if defined __NVCC__
    #ifdef __NVCC_DIAG_PRAGMA_SUPPORT__
        #pragma nv_diagnostic push
        #pragma nv_diag_suppress = implicit_return_from_non_void_function
    #else
      #ifdef __CUDA_ARCH__
        #pragma diagnostic push
        #pragma diag_suppress implicit_return_from_non_void_function
      #endif
    #endif
#elif defined __NVCOMPILER
    #pragma    diagnostic push
    #pragma    diag_suppress = implicit_return_from_non_void_function
#endif
template <size_t k, class Extents>
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &ext,
                       ::MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t) {
  if constexpr (Extents::static_extent(k) == dynamic_extent) {
    return ext.extent(k);
  } else {
    return integral_constant<size_t, Extents::static_extent(k)>();
  }
#if defined(__NVCC__) && !defined(__CUDA_ARCH__) && defined(__GNUC__)
  // Even with CUDA_ARCH protection this thing warns about calling host function
  __builtin_unreachable();
#endif
}
#if defined __NVCC__
    #ifdef __NVCC_DIAG_PRAGMA_SUPPORT__
        #pragma nv_diagnostic pop
    #else
      #ifdef __CUDA_ARCH__
        #pragma diagnostic pop
      #endif
    #endif
#elif defined __NVCOMPILER
    #pragma    diagnostic pop
#endif

template <size_t k, class Extents, class OffsetType, class ExtentType,
          class StrideType>
MDSPAN_INLINE_FUNCTION
constexpr OffsetType
last_of(std::integral_constant<size_t, k>, const Extents &,
        const strided_slice<OffsetType, ExtentType, StrideType> &r) {
  return r.extent;
}

// get stride of slices
template <class T>
MDSPAN_INLINE_FUNCTION
constexpr auto stride_of(const T &) {
  return integral_constant<size_t, 1>();
}

template <class OffsetType, class ExtentType, class StrideType>
MDSPAN_INLINE_FUNCTION
constexpr auto
stride_of(const strided_slice<OffsetType, ExtentType, StrideType> &r) {
  return r.stride;
}

// divide which can deal with integral constant preservation
template <class IndexT, class T0, class T1>
MDSPAN_INLINE_FUNCTION
constexpr auto divide(const T0 &v0, const T1 &v1) {
  return IndexT(v0) / IndexT(v1);
}

template <class IndexT, class T0, T0 v0, class T1, T1 v1>
MDSPAN_INLINE_FUNCTION
constexpr auto divide(const std::integral_constant<T0, v0> &,
                      const std::integral_constant<T1, v1> &) {
  // cutting short division by zero
  // this is used for strided_slice with zero extent/stride
  return integral_constant<IndexT, v0 == 0 ? 0 : v0 / v1>();
}

// multiply which can deal with integral constant preservation
template <class IndexT, class T0, class T1>
MDSPAN_INLINE_FUNCTION
constexpr auto multiply(const T0 &v0, const T1 &v1) {
  return IndexT(v0) * IndexT(v1);
}

template <class IndexT, class T0, T0 v0, class T1, T1 v1>
MDSPAN_INLINE_FUNCTION
constexpr auto multiply(const std::integral_constant<T0, v0> &,
                        const std::integral_constant<T1, v1> &) {
  return integral_constant<IndexT, v0 * v1>();
}

// compute new static extent from range, preserving static knowledge
template <class Arg0, class Arg1> struct StaticExtentFromRange {
  constexpr static size_t value = dynamic_extent;
};

template <class Integral0, Integral0 val0, class Integral1, Integral1 val1>
struct StaticExtentFromRange<std::integral_constant<Integral0, val0>,
                             std::integral_constant<Integral1, val1>> {
  constexpr static size_t value = val1 - val0;
};

template <class Integral0, Integral0 val0, class Integral1, Integral1 val1>
struct StaticExtentFromRange<integral_constant<Integral0, val0>,
                             integral_constant<Integral1, val1>> {
  constexpr static size_t value = val1 - val0;
};

// compute new static extent from strided_slice, preserving static
// knowledge
template <class Arg0, class Arg1> struct StaticExtentFromStridedRange {
  constexpr static size_t value = dynamic_extent;
};

template <class Integral0, Integral0 val0, class Integral1, Integral1 val1>
struct StaticExtentFromStridedRange<std::integral_constant<Integral0, val0>,
                                    std::integral_constant<Integral1, val1>> {
  constexpr static size_t value = val0 > 0 ? 1 + (val0 - 1) / val1 : 0;
};

template <class Integral0, Integral0 val0, class Integral1, Integral1 val1>
struct StaticExtentFromStridedRange<integral_constant<Integral0, val0>,
                                    integral_constant<Integral1, val1>> {
  constexpr static size_t value = val0 > 0 ? 1 + (val0 - 1) / val1 : 0;
};

// creates new extents through recursive calls to next_extent member function
// next_extent has different overloads for different types of stride specifiers
template <size_t K, class Extents, size_t... NewExtents>
struct extents_constructor {
  MDSPAN_TEMPLATE_REQUIRES(
    class Slice, class... SlicesAndExtents,
    /* requires */(!std::is_convertible_v<Slice, size_t> &&
                   !is_strided_slice<Slice>::value)
  )
  MDSPAN_INLINE_FUNCTION
  constexpr static auto next_extent(const Extents &ext, const Slice &sl,
                                    SlicesAndExtents... slices_and_extents) {
    constexpr size_t new_static_extent = StaticExtentFromRange<
        decltype(first_of(std::declval<Slice>())),
        decltype(last_of(std::integral_constant<size_t, Extents::rank() - K>(),
                         std::declval<Extents>(),
                         std::declval<Slice>()))>::value;

    using next_t =
        extents_constructor<K - 1, Extents, NewExtents..., new_static_extent>;
    using index_t = typename Extents::index_type;
    return next_t::next_extent(
        ext, slices_and_extents...,
        index_t(last_of(std::integral_constant<size_t, Extents::rank() - K>(), ext,
                        sl)) -
            index_t(first_of(sl)));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class Slice, class... SlicesAndExtents,
    /* requires */ (std::is_convertible_v<Slice, size_t>)
  )
  MDSPAN_INLINE_FUNCTION
  constexpr static auto next_extent(const Extents &ext, const Slice &,
                                    SlicesAndExtents... slices_and_extents) {
    using next_t = extents_constructor<K - 1, Extents, NewExtents...>;
    return next_t::next_extent(ext, slices_and_extents...);
  }

  template <class OffsetType, class ExtentType, class StrideType,
            class... SlicesAndExtents>
  MDSPAN_INLINE_FUNCTION
  constexpr static auto
  next_extent(const Extents &ext,
              const strided_slice<OffsetType, ExtentType, StrideType> &r,
              SlicesAndExtents... slices_and_extents) {
    using index_t = typename Extents::index_type;
    using new_static_extent_t =
        StaticExtentFromStridedRange<ExtentType, StrideType>;
    if constexpr (new_static_extent_t::value == dynamic_extent) {
      using next_t =
          extents_constructor<K - 1, Extents, NewExtents..., dynamic_extent>;
      return next_t::next_extent(
          ext, slices_and_extents...,
          r.extent > 0 ? 1 + divide<index_t>(r.extent - 1, r.stride) : 0);
    } else {
      constexpr size_t new_static_extent = new_static_extent_t::value;
      using next_t =
          extents_constructor<K - 1, Extents, NewExtents..., new_static_extent>;
      return next_t::next_extent(
          ext, slices_and_extents..., index_t(divide<index_t>(ExtentType(), StrideType())));
    }
  }
};

template <class Extents, size_t... NewStaticExtents>
struct extents_constructor<0, Extents, NewStaticExtents...> {

  template <class... NewExtents>
  MDSPAN_INLINE_FUNCTION
  constexpr static auto next_extent(const Extents &, NewExtents... new_exts) {
    return extents<typename Extents::index_type, NewStaticExtents...>(
        new_exts...);
  }
};

} // namespace detail

#if defined(MDSPAN_ENABLE_P3663)

namespace impl {

template<class IndexType, class OtherIndexType>
constexpr auto index_cast(OtherIndexType&& i) noexcept {
  using OIT = std::remove_cvref_t<OtherIndexType>;
  if (std::is_signed_v<OIT> || std::is_unsigned_v<OIT>) {
    return i;
  }
  else {
    return static_cast<IndexType>(i);
  }
}

template<class IndexType, class S>
  requires std::convertible_to<S, IndexType>
constexpr auto canonical_ice(S s) {
  static_assert(std::is_signed_v<IndexType> || std::is_unsigned_v<IndexType>);
  // TODO Mandates: If S models integral-constant-like and if
  // decltype(S::value) is a signed or unsigned integer type, then
  // S::value is representable as a value of type IndexType.
  //
  // TODO Preconditions: If S is a signed or unsigned integer type,
  // then s is representable as a value of type IndexType.
  if constexpr (__mdspan_integral_constant_like<S>) {
    return std::constant_wrapper<index_cast<IndexType>(S::value), IndexType>{};
  }
  else {
    return index_cast<IndexType>(s);
  }
}

template<class IndexType, class X, class Y>
constexpr auto subtract_ice(X x, Y y) {
  return canonical_ice<IndexType>(x) - canonical_ice<IndexType>(y);
}

template<class T>
constexpr T de_ice(T val) {
  return val;
}

template<__mdspan_integral_constant_like T>
constexpr auto de_ice(T) {
  return T::value;
}

enum class check_static_bounds_result {
  in_bounds,
  out_of_bounds,
  unknown
};

// TODO It's impossible to write an "if constexpr" check for
// "structured binding into two elements is well-formed."  Thus, we
// write check_static_bounds only for canonical slice types as inputs
// -- that is, we invoke check_static_bounds post-canonicalization.
//
// This may suggest a change in wording, though only if
// we need to call check_static_bounds on pre-canonicalized slices.

template<size_t k, class IndexType, size_t... Exts, class... Slices>
  constexpr check_static_bounds_result check_static_bounds(
    const extents<IndexType, Exts...>&, Slices... slices)
{
  auto s_k = slices...[k];
  using S_k = decltype(s_k);
  if constexpr (std::is_convertible_v<S_k, full_extent_t>) {
    return check_static_bounds_result::in_bounds;
  }
  else if constexpr (std::is_convertible_v<S_k, IndexType>) {
    if constexpr (__mdspan_integral_constant_like<S_k>) {
      if constexpr (de_ice(S_k{}) < 0) {
        return check_static_bounds_result::out_of_bounds; // 14.3.1
      }
      else if constexpr (Exts...[k] != dynamic_extent && Exts...[k] <= de_ice(S_k{})) {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (Exts...[k] != dynamic_extent && de_ice(s_k) < Exts...[k]) {
        return check_static_bounds_result::in_bounds;
      }
      else {
        return check_static_bounds_result::unknown;
      }
    }
    else { // integer, not integral-constant-like (14.5 case)
      return check_static_bounds_result::unknown;
    }
  }
  else if constexpr (detail::is_strided_slice<S_k>::value) {
    if constexpr (__mdspan_integral_constant_like<typename S_k::offset_type>) {
      if constexpr (de_ice(s_k.offset) < 0) {
        return check_static_bounds_result::out_of_bounds; // 14.3.1
      }
      else if constexpr (
        Exts...[k] != dynamic_extent && Exts...[k] < de_ice(s_k.offset))
      {
        return check_static_bounds_result::out_of_bounds; // 14.3.2
      }
      else if constexpr (
        __mdspan_integral_constant_like<typename S_k::extent_type> &&
        de_ice(s_k.offset) + de_ice(s_k.extent) < 0)
      {
        return check_static_bounds_result::out_of_bounds; // 14.3.3
      }
      else if constexpr (
        Exts...[k] != dynamic_extent &&
        __mdspan_integral_constant_like<typename S_k::extent_type> &&
        Exts...[k] < de_ice(s_k.offset) + de_ice(s_k.extent))
      {
        return check_static_bounds_result::out_of_bounds; // 14.3.4
      }
      else if constexpr (
        Exts...[k] != dynamic_extent &&
        __mdspan_integral_constant_like<typename S_k::extent_type> &&
        0 <= de_ice(s_k.offset) &&
        de_ice(s_k.offset) <= de_ice(s_k.offset) + de_ice(s_k.extent) &&
        de_ice(s_k.offset) + de_ice(s_k.extent) <= Exts...[k])
      {
        return check_static_bounds_result::in_bounds; // 14.3.5
      }
      else {
        return check_static_bounds_result::unknown; // 14.3.6
      }
    }
    else { // strided_slice but offset_type isn't integral-constant-like
      return check_static_bounds_result::unknown; // 14.5
    }
  }
  else { // 14.4
    // NOTE: This case means that check_static_bounds cannot be
    // well-formed if it didn't fall into one of the above cases
    // and if it can't be destructured into two elements.
    auto [s_k0, s_k1] = s_k;
    using S_k0 = decltype(s_k0);
    using S_k1 = decltype(s_k1);
    if constexpr (__mdspan_integral_constant_like<S_k0>) {
      if constexpr (de_ice(S_k0{}) < 0) {
        return check_static_bounds_result::out_of_bounds; // 14.4.1
      }
      else if constexpr (
        Exts...[k] != dynamic_extent &&
        Exts...[k] < de_ice(S_k0{}))
      {
        return check_static_bounds_result::out_of_bounds; // 14.4.2
      }
      else if constexpr (
        __mdspan_integral_constant_like<S_k1> &&
        de_ice(S_k1{}) < de_ice(S_k0{}))
      {
        return check_static_bounds_result::out_of_bounds; // 14.4.3
      }
      else if constexpr (
        Exts...[k] != dynamic_extent &&
        __mdspan_integral_constant_like<S_k1> &&
        Exts...[k] < de_ice(S_k1{}))
      {
        return check_static_bounds_result::out_of_bounds; // 14.4.4
      }
      else if constexpr (
        Exts...[k] != dynamic_extent &&
        __mdspan_integral_constant_like<S_k1> &&
        0 <= de_ice(S_k0{}) &&
        de_ice(S_k0{}) <= de_ice(S_k1{}) &&
        de_ice(S_k1{}) <= Exts...[k])
      {
        return check_static_bounds_result::in_bounds; // 14.4.5
      }
      else {
        return check_static_bounds_result::unknown; // 14.4.6
      }
    }
    else { // S_k0 not integral-constant-like
      return check_static_bounds_result::unknown;
    }
  }
}
} // namespace impl

template<class IndexType>
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_slices(const extents<IndexType>&)
{
  return std::tuple{};
}

template<class IndexType, size_t Extent>
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_slices(const extents<IndexType, Extent>&, full_extent_t)
{
  return std::tuple{full_extent};
}

template<class IndexType, size_t... Extents, class... Slices>
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_slices(const extents<IndexType, Extents...>&, Slices... slices)
{
  static_assert(sizeof...(Slices) == 0, "General case not implemented yet");
  return std::tuple{slices...};
}
#endif // MDSPAN_ENABLE_P3663

// submdspan_extents creates new extents given src extents and submdspan slice
// specifiers
template <class IndexType, size_t... Extents, class... SliceSpecifiers>
MDSPAN_INLINE_FUNCTION
constexpr auto submdspan_extents(const extents<IndexType, Extents...> &src_exts,
                                 SliceSpecifiers... slices) {

  using ext_t = extents<IndexType, Extents...>;
  return detail::extents_constructor<ext_t::rank(), ext_t>::next_extent(
      src_exts, slices...);
}
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
