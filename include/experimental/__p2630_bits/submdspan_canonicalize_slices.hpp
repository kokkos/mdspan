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
#include <complex>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {

#if MDSPAN_HAS_CXX_17

namespace detail {

// ============================================================
// de_ice: extract the value of an integral-constant-like type
// ============================================================

MDSPAN_TEMPLATE_REQUIRES(
  class T,
  /* requires */ (std::is_integral_v<remove_cvref_t<T>>)
)
MDSPAN_INLINE_FUNCTION
constexpr T de_ice(T val) {
  return val;
}

MDSPAN_TEMPLATE_REQUIRES(
  class T,
  /* requires */ (is_integral_constant_like_v<remove_cvref_t<T>>)
)
MDSPAN_INLINE_FUNCTION
constexpr decltype(T::value) de_ice([[maybe_unused]] T) {
  return T::value;
}

// ============================================================
// index_cast: cast to IndexType, preserving integral-constant nature
// ============================================================

MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  class OtherIndexType,
  /* requires */ (
    std::is_signed_v<remove_cvref_t<OtherIndexType>> ||
    std::is_unsigned_v<remove_cvref_t<OtherIndexType>>
  )
)
MDSPAN_INLINE_FUNCTION
constexpr auto index_cast(OtherIndexType&& i) noexcept {
  return i;
}

MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  class OtherIndexType,
  /* requires */ (
    ! std::is_signed_v<remove_cvref_t<OtherIndexType>> &&
    ! std::is_unsigned_v<remove_cvref_t<OtherIndexType>>
  )
)
MDSPAN_INLINE_FUNCTION
constexpr auto index_cast(OtherIndexType&& i) noexcept {
  return static_cast<IndexType>(i);
}

// ============================================================
// canonical_index: canonicalize a value to IndexType,
//   preserving integral-constant nature when possible
// ============================================================

MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  class S,
  /* requires */ (std::is_convertible_v<S, IndexType>)
)
MDSPAN_INLINE_FUNCTION
constexpr auto canonical_index([[maybe_unused]] S s) {
  // TODO: might move to public semi/public only to get error earlier, and
  // don't duplicate check
  static_assert(std::is_signed_v<IndexType> || std::is_unsigned_v<IndexType>);
  if constexpr (is_integral_constant_like_v<S>) {
    return cw<static_cast<IndexType>(index_cast<IndexType>(S::value))>;
  }
  else {
    return static_cast<IndexType>(index_cast<IndexType>(std::move(s)));
  }
}

// ============================================================
// subtract_ice: subtract two values, preserving integral-constant
//   nature when both inputs are integral-constant-like
// ============================================================

template<class IndexType, class X, class Y>
MDSPAN_INLINE_FUNCTION
constexpr auto subtract_ice([[maybe_unused]] X x, [[maybe_unused]] Y y) {
  if constexpr (
    is_integral_constant_like_v<remove_cvref_t<X>> &&
    is_integral_constant_like_v<remove_cvref_t<Y>>)
  {
    return cw<IndexType(canonical_index<IndexType>(Y::value) - canonical_index<IndexType>(X::value))>;
  }
  else {
    return canonical_index<IndexType>(y) - canonical_index<IndexType>(x);
  }
}

// ============================================================
// check_static_bounds_result: result of a compile-time bounds check
// ============================================================

enum class check_static_bounds_result {
  in_bounds,
  out_of_bounds,
  unknown
};

// ============================================================
// is_std_complex: detect std::complex (for pre-tuple-like compilers)
// ============================================================

// Clang 21.0.0 does not define __cpp_lib_tuple_like, so it does not
// support the tuple protocol for std::complex.  Interestingly, it permits
// structured binding, but decomposes it into one element, not two.
// We work around with a special canonicalization case.
#if ! defined(__cpp_lib_tuple_like) || (__cpp_lib_tuple_like < 202311L)
template<class T>
constexpr bool is_std_complex = false;
template<class T>
constexpr bool is_std_complex<std::complex<T>> = true;
#endif

// ============================================================
// check_static_bounds: compile-time bounds check for a slice
//
// Returns whether the k-th slice is statically in bounds,
// out of bounds, or unknown (dynamic bounds or dynamic slice values).
//
// This function is called only in static_assert contexts.
// ============================================================

template<size_t k, class S_k, class IndexType, size_t... Exts>
constexpr check_static_bounds_result check_static_bounds(
  const extents<IndexType, Exts...>&)
{
#if defined(__cpp_pack_indexing)
  constexpr size_t Exts_k = Exts...[k];
#else
  constexpr size_t Exts_k = [] () {
    size_t result = 0;
    size_t i = 0;
    (void) ((i++ == k ? (result = Exts, true) : false) || ...);
    return result;
  } ();
#endif

  if constexpr (std::is_convertible_v<S_k, full_extent_t>) {
    return check_static_bounds_result::in_bounds;
  }
  else if constexpr (std::is_convertible_v<S_k, IndexType>) {
    if constexpr (is_integral_constant_like_v<S_k>) {
      if constexpr (de_ice(S_k{}) < 0) {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (
        Exts_k != dynamic_extent &&
        Exts_k <= static_cast<size_t>(de_ice(S_k{})))
      {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (
        Exts_k != dynamic_extent &&
        static_cast<size_t>(de_ice(S_k{})) < Exts_k)
      {
        return check_static_bounds_result::in_bounds;
      }
      else {
        return check_static_bounds_result::unknown;
      }
    }
    else {
      return check_static_bounds_result::unknown;
    }
  }
  else if constexpr (is_strided_slice<S_k>::value) {
    using offset_type = typename S_k::offset_type;

    if constexpr (is_integral_constant_like_v<offset_type>) {
      if constexpr (de_ice(offset_type{}) < 0) {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (
        Exts_k != dynamic_extent &&
        Exts_k < static_cast<size_t>(de_ice(offset_type{})))
      {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (is_integral_constant_like_v<typename S_k::extent_type>) {
        using extent_type = typename S_k::extent_type;

        if constexpr (de_ice(offset_type{}) + de_ice(extent_type{}) < 0) {
          return check_static_bounds_result::out_of_bounds;
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          Exts_k <
            static_cast<size_t>(de_ice(offset_type{}) + de_ice(extent_type{})))
        {
          return check_static_bounds_result::out_of_bounds;
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          0 <= de_ice(offset_type{}) &&
          de_ice(offset_type{}) <=
            de_ice(offset_type{}) + de_ice(extent_type{}) &&
          static_cast<size_t>(
            de_ice(offset_type{}) + de_ice(extent_type{})) <= Exts_k)
        {
          return check_static_bounds_result::in_bounds;
        }
        else {
          return check_static_bounds_result::unknown;
        }
      }
      else {
        return check_static_bounds_result::unknown;
      }
    }
    else {
      return check_static_bounds_result::unknown;
    }
  }
#if ! defined(__cpp_lib_tuple_like) || (__cpp_lib_tuple_like < 202311L)
  else if constexpr (is_std_complex<S_k>) {
    return check_static_bounds_result::unknown;
  }
#endif
  else {
    // General pair-like case: attempt to get the first and second elements.
    // If S_k cannot be structured-bound into two elements, this is ill-formed,
    // which implements the Mandates clause.
    auto get_first = [] (S_k s_k) {
      auto [s_k0, _x] = s_k;
      return s_k0;
    };
    auto get_second = [] (S_k s_k) {
      auto [_x, s_k1] = s_k;
      return s_k1;
    };
    using S_k0 = decltype(get_first(std::declval<S_k>()));
    using S_k1 = decltype(get_second(std::declval<S_k>()));
    if constexpr (is_integral_constant_like_v<S_k0>) {
      if constexpr (de_ice(S_k0{}) < 0) {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (
        Exts_k != dynamic_extent &&
        Exts_k < static_cast<size_t>(de_ice(S_k0{})))
      {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (is_integral_constant_like_v<S_k1>) {
        if constexpr (de_ice(S_k1{}) < de_ice(S_k0{})) {
          return check_static_bounds_result::out_of_bounds;
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          Exts_k < static_cast<size_t>(de_ice(S_k1{})))
        {
          return check_static_bounds_result::out_of_bounds;
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          0 <= de_ice(S_k0{}) &&
          de_ice(S_k0{}) <= de_ice(S_k1{}) &&
          static_cast<size_t>(de_ice(S_k1{})) <= Exts_k)
        {
          return check_static_bounds_result::in_bounds;
        }
        else {
          return check_static_bounds_result::unknown;
        }
      }
      else {
        return check_static_bounds_result::unknown;
      }
    }
    else {
      return check_static_bounds_result::unknown;
    }
  }
}

// ============================================================
// check_submdspan_slice_mandate: mandate check for the k-th slice
//
// Contains only static_asserts; no actual computation.
// Separated from canonical_slice so that
// mandate checking and canonicalization are distinct concerns.
// ============================================================

template<size_t k, class IndexType, size_t... Extents, class Slice>
MDSPAN_INLINE_FUNCTION
constexpr void check_submdspan_slice_mandate(
  const extents<IndexType, Extents...>&,
  [[maybe_unused]] Slice)
{
  static_assert(
    check_static_bounds<k, Slice>(extents<IndexType, Extents...>{}) !=
    check_static_bounds_result::out_of_bounds);
}

// ============================================================
// check_submdspan_slice_mandates: mandate check for all slices
//
// Calls check_submdspan_slice_mandate for each slice.
// Separated from canonicalization so mandate checking is explicit.
// ============================================================

template<size_t... Inds, class IndexType, size_t... Extents, class... Slices>
MDSPAN_INLINE_FUNCTION
constexpr void check_submdspan_slice_mandates(
  std::index_sequence<Inds...>,
  const extents<IndexType, Extents...>& exts,
  Slices... slices)
{
  (check_submdspan_slice_mandate<Inds>(exts, slices), ...);
}

// ============================================================
// canonical_slice: canonicalize a single slice
//
// This function performs ONLY the conversion to canonical form.
// Mandate checking (static_asserts) is NOT done here; it is
// done separately by check_submdspan_slice_mandates.
//
// Templated only on IndexType (the extents index type) and Slice.
// Neither k nor the extents are needed for the actual conversion.
// ============================================================

template<class IndexType, class Slice>
MDSPAN_INLINE_FUNCTION
constexpr auto canonical_slice([[maybe_unused]] Slice s)
{
  if constexpr (std::is_convertible_v<Slice, full_extent_t>) {
    return full_extent; // canonical full-extent slice
  }
  else if constexpr (std::is_convertible_v<Slice, IndexType>) {
    return canonical_index<IndexType>(std::move(s)); // canonical integer index
  }
  else if constexpr (is_strided_slice<Slice>::value) {
    // Canonicalize each component of the strided_slice
    auto offset = canonical_index<IndexType>(s.offset);
    auto extent = canonical_index<IndexType>(s.extent);
    auto stride = canonical_index<IndexType>(s.stride);
    // TODO: Later introduce canonical-range-slice
    return strided_slice<decltype(offset), decltype(extent), decltype(stride)>{
      /* .offset = */ offset,
      /* .extent = */ extent,
      /* .stride = */ stride
    };
  } else {
    // General pair-like case: structured binding into [first, last)
    auto [s_k0, s_k1] = s;
    using S_k0 = decltype(s_k0);
    using S_k1 = decltype(s_k1);
    static_assert(std::is_convertible_v<S_k0, IndexType>);
    static_assert(std::is_convertible_v<S_k1, IndexType>);

    auto offset = canonical_index<IndexType>(s_k0);
    auto extent = subtract_ice<IndexType>(s_k0, s_k1);
    auto stride = cw<IndexType(1)>;
    // TODO: Later introduce canonical-range-slice
    return strided_slice<decltype(offset), decltype(extent), decltype(stride)>{
      /* .offset = */ offset,
      /* .extent = */ extent,
      /* .stride = */ stride
    };
  }
}

// ============================================================
// canonical_slices_impl: implementation helper
//
// First performs mandate checks (static_asserts), then
// returns a detail::tuple of canonical slices.
// Using detail::tuple instead of std::tuple ensures device
// code compatibility (e.g., CUDA).
// ============================================================

MDSPAN_TEMPLATE_REQUIRES(
  size_t... Inds,
  class IndexType,
  size_t... Extents,
  class... Slices,
  /* requires */ (sizeof...(Slices) == sizeof...(Extents))
)
MDSPAN_INLINE_FUNCTION
constexpr auto canonical_slices_impl(
  std::index_sequence<Inds...>,
  const extents<IndexType, Extents...>& exts,
  Slices... slices)
{
  // Mandate checks (static_asserts only, no computation).
  // Separated from canonicalization for clarity.
  check_submdspan_slice_mandates(
    std::make_index_sequence<sizeof...(Slices)>(), exts, slices...);

  // Actual canonicalization: returns detail::tuple for device compatibility.
  return detail::tuple{
    canonical_slice<IndexType>(slices)...
  };
}

} // namespace detail

// ============================================================
// submdspan_canonicalize_slices: public API
//
// Given an extents object and a pack of slice specifiers,
// returns a detail::tuple of canonical slice specifiers.
// Each canonical slice is one of:
//   - full_extent_t (for full-extent slices)
//   - IndexType (for integer index slices)
//   - strided_slice<...> (for range and strided-range slices)
// ============================================================

MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  size_t... Extents,
  class... Slices,
  /* requires */ (sizeof...(Slices) == sizeof...(Extents))
)
MDSPAN_INLINE_FUNCTION
constexpr auto canonical_slices(
  const extents<IndexType, Extents...>& exts,
  Slices... slices)
{
  return detail::canonical_slices_impl(
    std::make_index_sequence<sizeof...(Slices)>(), exts, slices...);
}

#endif // MDSPAN_HAS_CXX_17

} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
