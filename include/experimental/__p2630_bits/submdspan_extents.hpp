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

// TODO We won't even need index_pair_like when we're done.

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

#if defined(MDSPAN_ENABLE_P3663)

template<class Integral>
  requires (std::is_signed_v<Integral> || std::is_unsigned_v<Integral>)
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(Integral i) {
  return i;
}

#else

MDSPAN_TEMPLATE_REQUIRES(
  class Integral,
  /* requires */(std::is_convertible_v<Integral, size_t>)
)
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(const Integral &i) {
  return i;
}

#endif // MDSPAN_ENABLE_P3663

#if defined(MDSPAN_ENABLE_P3663)
// NOTE (mfh 2025/03/07) Canonicalize integral-constant-like
// to std::integral_constant, just to get things working for now.
// Later, go back and replace all use of std::integral_constant
// in the various mappings' submdspan_mapping_impl functions with
// std::constant_wrapper.
template<__mdspan_integral_constant_like T>
MDSPAN_INLINE_FUNCTION
constexpr auto
first_of(const T&) {
  return std::integral_constant<typename T::value_type, T{}()>{};
}
#else

// NOTE This is technically not conforming.
// Pre-P3663, first_of should work on any integral-constant-like type.
template<class Integral, Integral v>
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(const std::integral_constant<Integral, v>&) {
  return integral_constant<Integral, v>();
}
#endif

MDSPAN_INLINE_FUNCTION
constexpr integral_constant<size_t, 0>
first_of(const ::MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t &) {
  return integral_constant<size_t, 0>();
}

// TODO P3663 won't need this overload,
// because first_of should never see pair-like types.
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

#if defined(MDSPAN_ENABLE_P3663)
// NOTE (mfh 2025/03/07) This should probably replace the above overload.
template<__mdspan_integral_constant_like T, class Extents, class Integral>
  requires(std::is_convertible_v<Integral, size_t>)
MDSPAN_INLINE_FUNCTION
constexpr Integral last_of(T, const Extents&, const Integral& i) {
  return i;
}
#endif // MDSPAN_ENABLE_P3663

MDSPAN_TEMPLATE_REQUIRES(
  size_t k, class Extents, class Slice,
  /* requires */(index_pair_like<Slice, size_t>::value)
)
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &,
                       const Slice &i) {
  return get<1>(i);
}

// NOTE P3663 should not need this overload,
// because last_of should never see a pair-like type.
#if defined(MDSPAN_ENABLE_P3663)
MDSPAN_TEMPLATE_REQUIRES(
  __mdspan_integral_constant_like T, class Extents, class Slice,
  /* requires */(index_pair_like<Slice, size_t>::value)
)
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(T, const Extents &,
                       const Slice &i) {
  using std::get;
  return get<1>(i);
}
#endif

MDSPAN_TEMPLATE_REQUIRES(
  size_t k, class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::tuple<IdxT1, IdxT2>, size_t>::value)
  )
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &, const std::tuple<IdxT1, IdxT2>& i) {
  return get<1>(i);
}

#if defined(MDSPAN_ENABLE_P3663)
MDSPAN_TEMPLATE_REQUIRES(
  __mdspan_integral_constant_like T, class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::tuple<IdxT1, IdxT2>, size_t>::value)
  )
constexpr auto last_of(T, const Extents &, const std::tuple<IdxT1, IdxT2>& i) {
  return get<1>(i);
}
#endif

MDSPAN_TEMPLATE_REQUIRES(
  size_t k, class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::pair<IdxT1, IdxT2>, size_t>::value)
  )
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &, const std::pair<IdxT1, IdxT2>& i) {
  return i.second;
}

#if defined(MDSPAN_ENABLE_P3663)
MDSPAN_TEMPLATE_REQUIRES(
  __mdspan_integral_constant_like T, class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::pair<IdxT1, IdxT2>, size_t>::value)
  )
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(T, const Extents &, const std::pair<IdxT1, IdxT2>& i) {
  return i.second;
}
#endif

template<size_t k, class Extents, class T>
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(std::integral_constant<size_t, k>, const Extents &, const std::complex<T> &i) {
  return i.imag();
}

#if defined(MDSPAN_ENABLE_P3663)
template<__mdspan_integral_constant_like ICL, class Extents, class T>
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(ICL, const Extents &, const std::complex<T> &i) {
  return i.imag();
}
#endif

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

#if defined(MDSPAN_ENABLE_P3663)
template<__mdspan_integral_constant_like T, class Extents>
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(T, const Extents &ext,
                       ::MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t) {
  if constexpr (Extents::static_extent(T::value) == dynamic_extent) {
    return ext.extent(T::value);
  } else {
    return integral_constant<size_t, Extents::static_extent(T::value)>();
  }
}
#endif

template <size_t k, class Extents, class OffsetType, class ExtentType,
          class StrideType>
MDSPAN_INLINE_FUNCTION
constexpr OffsetType
last_of(std::integral_constant<size_t, k>, const Extents &,
        const strided_slice<OffsetType, ExtentType, StrideType> &r) {
  return r.extent;
}

#if defined(MDSPAN_ENABLE_P3663)
template <__mdspan_integral_constant_like ICL, class Extents, class OffsetType, class ExtentType,
          class StrideType>
MDSPAN_INLINE_FUNCTION
constexpr OffsetType
last_of(ICL, const Extents &,
        const strided_slice<OffsetType, ExtentType, StrideType> &r) {
  return r.extent;
}
#endif

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
#if defined(MDSPAN_ENABLE_P3663)
  static_assert(std::is_signed_v<T0> || std::is_unsigned_v<T0>);
  static_assert(std::is_signed_v<T1> || std::is_unsigned_v<T1>);
#endif

  // cutting short division by zero
  // this is used for strided_slice with zero extent/stride
  return integral_constant<IndexT, v0 == 0 ? 0 : v0 / v1>();
}

#if defined(MDSPAN_ENABLE_P3663)
template <class IndexType, auto v0, auto v1>
MDSPAN_INLINE_FUNCTION
constexpr auto divide(std::constant_wrapper<v0> i0,
                      std::constant_wrapper<v1> i1) {
  using I0 = typename std::constant_wrapper<v0>::value_type;
  using I1 = typename std::constant_wrapper<v1>::value_type;
  static_assert(std::is_signed_v<I0> || std::is_unsigned_v<I0>);
  static_assert(std::is_signed_v<I1> || std::is_unsigned_v<I1>);

  // cutting short division by zero
  // this is used for strided_slice with zero extent/stride
  //
  // NOTE For now, use integral_constant internally. 
  return integral_constant<IndexType, i0() == 0 ? 0 : i0() / i1()>();
}
#endif

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

#if defined(MDSPAN_ENABLE_P3663)
template <class IndexType, auto v0, auto v1>
MDSPAN_INLINE_FUNCTION
constexpr auto multiply(std::constant_wrapper<v0> i0,
                        std::constant_wrapper<v1> i1) {
  using I0 = typename std::constant_wrapper<v0>::value_type;
  using I1 = typename std::constant_wrapper<v1>::value_type;
  static_assert(std::is_signed_v<I0> || std::is_unsigned_v<I0>);
  static_assert(std::is_signed_v<I1> || std::is_unsigned_v<I1>);

  return integral_constant<IndexType, i0() * i1()>();
}
#endif

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

#if defined(MDSPAN_ENABLE_P3663)
template <__mdspan_integral_constant_like A, __mdspan_integral_constant_like B>
struct StaticExtentFromRange<A, B> {
  constexpr static size_t value = B::value - A::value;
};
#endif

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

#if defined(MDSPAN_ENABLE_P3663)
template <__mdspan_integral_constant_like A, __mdspan_integral_constant_like B>
struct StaticExtentFromStridedRange<A, B> {
  constexpr static size_t value = A::value > 0 ? 1 + (A::value - 1) / B::value : 0;
};
#endif

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

namespace detail {

template<class IndexType, class OtherIndexType>
  requires(std::is_signed_v<std::remove_cvref_t<OtherIndexType>> ||
    std::is_unsigned_v<std::remove_cvref_t<OtherIndexType>>)
constexpr auto index_cast(OtherIndexType&& i) noexcept {
  return i;
}

template<class IndexType, class OtherIndexType>
  requires(! std::is_signed_v<std::remove_cvref_t<OtherIndexType>> &&
    !std::is_unsigned_v<std::remove_cvref_t<OtherIndexType>>)
constexpr auto index_cast(OtherIndexType&& i) noexcept {
  return static_cast<IndexType>(i);
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
  //
  // TODO NOT IN PROPOSAL: index-cast result needs to be
  // cast again to IndexType, so that we don't get a weird
  // constant_wrapper whose value has a different type
  // than the second template argument.

  // TODO NOT IN PROPOSAL? Make sure constant_wrapper only has one template argument.
  // The first template argument is a value of an exposition-only type, NOT the actual value!
  if constexpr (__mdspan_integral_constant_like<S>) {
    return std::constant_wrapper<static_cast<IndexType>(index_cast<IndexType>(S::value))>{};
  }
  else {
    return static_cast<IndexType>(index_cast<IndexType>(s));
  }
}

template<class IndexType, class X, class Y>
constexpr auto subtract_ice(X x, Y y) {
  return canonical_ice<IndexType>(y) - canonical_ice<IndexType>(x);
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

// TODO It's impossible to write an "if constexpr" check for
// "structured binding into two elements is well-formed."  Thus, we
// must assume that the input Slices are all valid slice types.
// One way to do that is to invoke this only post-canonicalization.
// Another way is to rely on submdspan_canonicalize_slices to be
// ill-formed if called with an invalid slice type.  We can do the
// latter in submdspan_canonicalize_slices by expressing the four
// possible categories of valid slice types in if constexpr, with
// the final else attempting the structured binding into two elements.

// TODO NOT IN PROPOSAL: Consider rewriting to use only $S_k$
// and not $s_k$ in check-static-bounds, since we can't use
// the actual function parameter in a function that we want
// to work in a constant expression.

// TODO NOT IN PROPOSAL: Taking slices parameter(s) makes use
// of check_static_bounds not a constant expression.
// Instead, make Slices... a template parameter pack.

// TODO NOT IN PROPOSAL: It's easier to have a single Slice
// as a template parameter pack.  This makes sense because
// the function only tests one slice (the k-th one) anyway.
template<size_t k, class S_k, class IndexType, size_t... Exts>
  constexpr check_static_bounds_result check_static_bounds(
    const extents<IndexType, Exts...>&)
{
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
      else if constexpr (Exts...[k] != dynamic_extent && de_ice(S_k{}) < Exts...[k]) {
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
  else if constexpr (is_strided_slice<S_k>::value) {
    if constexpr (__mdspan_integral_constant_like<typename S_k::offset_type>) {
      if constexpr (de_ice(S_k{}.offset) < 0) {
        return check_static_bounds_result::out_of_bounds; // 14.3.1
      }
      else if constexpr (
        Exts...[k] != dynamic_extent && Exts...[k] < de_ice(S_k{}.offset))
      {
        return check_static_bounds_result::out_of_bounds; // 14.3.2
      }
      else if constexpr (
        __mdspan_integral_constant_like<typename S_k::extent_type> &&
        de_ice(S_k{}.offset) + de_ice(S_k{}.extent) < 0)
      {
        return check_static_bounds_result::out_of_bounds; // 14.3.3
      }
      else if constexpr (
        Exts...[k] != dynamic_extent &&
        __mdspan_integral_constant_like<typename S_k::extent_type> &&
        Exts...[k] < de_ice(S_k{}.offset) + de_ice(S_k{}.extent))
      {
        return check_static_bounds_result::out_of_bounds; // 14.3.4
      }
      else if constexpr (
        Exts...[k] != dynamic_extent &&
        __mdspan_integral_constant_like<typename S_k::extent_type> &&
        0 <= de_ice(S_k{}.offset) &&
        de_ice(S_k{}.offset) <= de_ice(S_k{}.offset) + de_ice(S_k{}.extent) &&
        de_ice(S_k{}.offset) + de_ice(S_k{}.extent) <= Exts...[k])
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
#if ! defined(__cpp_lib_tuple_like) || (__cpp_lib_tuple_like < 202311L)
  else if constexpr (is_std_complex<S_k>) {
    // std::complex only has run-time slice values, so we can't
    // check at compile time whether they are in bounds.
    return check_static_bounds_result::unknown;
  }
#endif
  else { // 14.4
    // NOTE: This case means that check_static_bounds cannot be
    // well-formed if it didn't fall into one of the above cases
    // and if it can't be destructured into two elements.

    // We can't use s_k on the right-hand side here, because it's not a constant expression.
    // We can't use S_k{} here either, because that presumes that it's default constructible.
    // We can only use std::declval<S_k>() in an unevaluated context.
    auto get_first = [] (S_k s_k) {
      auto [s_k0, _] = s_k;
      return s_k0;
    };
    auto get_second = [] (S_k s_k) {
      auto [_, s_k1] = s_k;
      return s_k1;
    };
    using S_k0 = decltype(get_first(std::declval<S_k>()));
    using S_k1 = decltype(get_second(std::declval<S_k>()));
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

template<class T>
constexpr bool is_constant_wrapper = false;

template<auto Value>
constexpr bool is_constant_wrapper<std::constant_wrapper<Value>> = true;

// [mdspan.sub.slices] 1
template<class IndexType, class T>
constexpr bool is_canonical_submdspan_index_type =
  std::is_same_v<T, IndexType> || (
    is_constant_wrapper<T> &&
    std::is_same_v<typename T::value_type, IndexType>
  );

// [mdspan.sub.slices] 2
template<class IndexType, class Slice>
MDSPAN_INLINE_FUNCTION
constexpr bool is_canonical_slice_type() {
  if constexpr (
    std::is_same_v<Slice, full_extent_t> || // 2.1
    is_canonical_submdspan_index_type<IndexType, Slice>) // 2.2
  {
    return true;
  }
  else if constexpr (is_strided_slice<Slice>::value) { // 2.3
    if constexpr ( // 2.3.1
      is_canonical_submdspan_index_type<IndexType, typename Slice::offset_type> &&
      is_canonical_submdspan_index_type<IndexType, typename Slice::extent_type> &&
      is_canonical_submdspan_index_type<IndexType, typename Slice::stride_type>)
    {
      if constexpr (
        is_constant_wrapper<typename Slice::stride_type> &&
        is_constant_wrapper<typename Slice::extent_type>)
      {
        constexpr auto Stride = de_ice(typename Slice::stride_type{});
        constexpr auto Extent = de_ice(typename Slice::extent_type{});
        return Extent == 0 || Stride > 0; // 2.3.2
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

// [mdspan.sub.slices] 3
template<size_t k, class IndexType, size_t... Extents, class Slice>
MDSPAN_INLINE_FUNCTION
constexpr auto
is_canonical_kth_submdspan_slice_type(const extents<IndexType, Extents...>& exts, Slice slice)
{
  if constexpr (! is_canonical_slice_type<IndexType, Slice>()) {
    return false; // 3.1
  }
  else { // 3.2
    return check_static_bounds<k, decltype(slice)>(exts) != check_static_bounds_result::out_of_bounds;
  }
}

// [mdspan.sub.slices] 11
template<size_t k, class Slice, class IndexType, size_t... Extents>
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_one_slice(const extents<IndexType, Extents...>& exts, Slice s) {
  // Part of [mdspan.sub.slices] 9.
  // This could be combined with the if constexpr branches below.
  //
  // NOTE This is not a constant expression (because it takes exts).
  static_assert(check_static_bounds<k, decltype(s)>(exts) != check_static_bounds_result::out_of_bounds);

  // TODO Check Precondition that s is a valid k-th submdspan slice for exts.

  if constexpr (std::is_convertible_v<Slice, full_extent_t>) {
    return full_extent; // 11.1
  }
  else if constexpr (std::is_convertible_v<Slice, IndexType>) {
    return canonical_ice<IndexType>(s); // 11.2
  }
  else if constexpr (is_strided_slice<Slice>::value) { // 11.3
    return strided_slice{
      .offset = canonical_ice<IndexType>(s.offset),
      .extent = canonical_ice<IndexType>(s.extent),
      .stride = canonical_ice<IndexType>(s.stride)
    };
  }
#if ! defined(__cpp_lib_tuple_like) || (__cpp_lib_tuple_like < 202311L)
  else if constexpr (detail::is_std_complex<Slice>) {
    return strided_slice{
      .offset = canonical_ice<IndexType>(s.real()),
      .extent = canonical_ice<IndexType>(s.imag() - s.real()),
      .stride = std::cw<IndexType(1)>
    };
  }
#endif
  else { // 11.4
    auto [s_k0, s_k1] = s;
    using S_k0 = decltype(s_k0);
    using S_k1 = decltype(s_k1);
    static_assert(std::is_convertible_v<S_k0, IndexType>);
    static_assert(std::is_convertible_v<S_k1, IndexType>);
    return strided_slice{
      .offset = canonical_ice<IndexType>(s_k0),
      .extent = subtract_ice<IndexType>(s_k0, s_k1),
      .stride = std::cw<IndexType(1)>
    };
  }
}

} // namespace detail

template<class IndexType, size_t... Extents, class... Slices>
  requires (sizeof...(Slices) == sizeof...(Extents)) // [mdspan.sub.slices] 8
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_slices(const extents<IndexType, Extents...>& exts, Slices... slices)
{
  return [&]<size_t... Inds>(std::index_sequence<Inds...>) {
    return std::tuple{
      // This is ill-formed if slices...[Inds] is not a valid slice type.
      // That implements the Mandates clause of [mdspan.sub.slices] 9.
      detail::submdspan_canonicalize_one_slice<Inds>(exts, slices...[Inds])...
    };
  } (std::make_index_sequence<sizeof...(Slices)>{});
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
