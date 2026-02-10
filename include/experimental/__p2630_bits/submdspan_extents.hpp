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

// NOTE (mfh 2026/02/06) This inexplicably only works with std::integral_constant.
// That's fine; it's not exposed to users anyway.

template<
  size_t Counter,
  size_t... MapIdxs
>
MDSPAN_INLINE_FUNCTION
constexpr auto inv_map_rank_impl(
  std::integral_constant<size_t, Counter>,
  std::index_sequence<MapIdxs...>)
{
  return std::index_sequence<MapIdxs...>();
}

// specialization reducing rank by one (i.e., integral slice specifier)
template<
  size_t Counter,
  class Slice,
  class... SliceSpecifiers,
  size_t... MapIdxs>
MDSPAN_INLINE_FUNCTION
constexpr auto inv_map_rank_impl(
  std::integral_constant<size_t, Counter>,
  std::index_sequence<MapIdxs...>,
  Slice,
  SliceSpecifiers... slices)
{
  using next_idx_seq_t = std::conditional_t<
      std::is_convertible_v<Slice, size_t>,
      std::index_sequence<MapIdxs...>,
      std::index_sequence<MapIdxs..., Counter>
    >;

  return inv_map_rank_impl(
    std::integral_constant<size_t, Counter + 1>(),
    next_idx_seq_t(),
    slices...);
}

template<
  class... SliceSpecifiers,
  size_t... MapIdxs
>
MDSPAN_INLINE_FUNCTION
constexpr auto inv_map_rank(
  std::index_sequence<MapIdxs...> seq,
  SliceSpecifiers... slices)
{
  return inv_map_rank_impl(
    std::integral_constant<size_t, 0>(),
    seq,
    slices...);
}

// Helper for identifying strided_slice
template <class T> struct is_strided_slice : std::false_type {};

template <class OffsetType, class ExtentType, class StrideType>
struct is_strided_slice<
    strided_slice<OffsetType, ExtentType, StrideType>> : std::true_type {};

// P3663 does not need index_pair_like.  In fact, it's impossible
// to define a concept for the set of types that P3663 accepts
// as a pair of indices.
#if ! defined(MDSPAN_ENABLE_P3663)

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

#endif // ! defined(MDSPAN_ENABLE_P3663)

// first_of(slice): getting begin of slice specifier range

#if defined(MDSPAN_ENABLE_P3663)

MDSPAN_TEMPLATE_REQUIRES(
  class Integral,
  /* requires */(std::is_signed_v<Integral> || std::is_unsigned_v<Integral>)
)
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(Integral i) {
  return i;
}

#else

// NOTE (mfh 2025/06/06) The original "return i;" was not conforming,
// in particular for index types that were not integral-not-bool
// but were convertible to index_type.

MDSPAN_TEMPLATE_REQUIRES(
  class Integral,
  /* requires */(
    ! std::is_signed_v<Integral> &&
    ! std::is_unsigned_v<Integral> &&
    (
      std::is_convertible_v<Integral, size_t> ||
      std::is_convertible_v<Integral, int>
    )
  )
)
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(const Integral &i) {
  // FIXME (mfh 2025/06/06) This is broken, but it's better than it was.
  return size_t(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  class Integral,
  /* requires */(
    std::is_signed_v<Integral> ||
    std::is_unsigned_v<Integral>
  )
)
MDSPAN_INLINE_FUNCTION
constexpr Integral first_of(const Integral &i) {
  return i;
}

#endif // MDSPAN_ENABLE_P3663

#if defined(MDSPAN_ENABLE_P3663)
template<auto Value>
MDSPAN_INLINE_FUNCTION
constexpr std::constant_wrapper<Value>
first_of(std::constant_wrapper<Value>) {
  return {};
}
#else
// NOTE This is technically not conforming.
// Pre-P3663, first_of should work on any integral-constant-like type.
// Replacing the return type "Integral" with auto does not change test results.
template<class Integral, Integral v>
MDSPAN_INLINE_FUNCTION
constexpr Integral
first_of(const std::integral_constant<Integral, v>&) {
  return integral_constant<Integral, v>();
}
#endif



#if defined(MDSPAN_ENABLE_P3663)

MDSPAN_INLINE_FUNCTION
constexpr
auto
first_of(const ::MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t &) {
  return std::cw<size_t(0)>;
}

#else

MDSPAN_INLINE_FUNCTION
constexpr
integral_constant<size_t, 0>
first_of(const ::MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t &) {
  return {};
}

#endif // MDSPAN_ENABLE_P3663


// P3663 doesn't need any of these overloads,
// because its version of first_of will never see pair-like types.
// (The only "contiguous range of indices" slice types it sees are
// full_extent_t and strided_slice with compile-time unit stride.)
#if ! defined(MDSPAN_ENABLE_P3663)

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

#endif

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

// clang++ with C++14 is not fond of the pragma appearing inside the
// macro definition.  In that case, it complains, "error: embedding a
// directive within macro arguments has undefined behavior
// [-Werror,-Wembedded-directive]."  The fix is to duplicate code.

#if defined(MDSPAN_ENABLE_P3663)
MDSPAN_TEMPLATE_REQUIRES(
  auto k,
  class Extents,
  class Integral,
  /* requires */(std::is_convertible_v<Integral, size_t>)
)
#else
MDSPAN_TEMPLATE_REQUIRES(
  size_t k,
  class Extents,
  class Integral,
  /* requires */(std::is_convertible_v<Integral, size_t>)
)
#endif // MDSPAN_ENABLE_P3663
MDSPAN_INLINE_FUNCTION
constexpr Integral last_of(
#if defined(MDSPAN_ENABLE_P3663)
  std::constant_wrapper<k>,
#else
  std::integral_constant<size_t, k>,
#endif
  const Extents &,
  const Integral &i)
{
  return i;
}

#if ! defined(MDSPAN_ENABLE_P3663)

// P3663 does not need these index_pair_like overloads,
// because last_of should never see a pair-like type.
MDSPAN_TEMPLATE_REQUIRES(
  size_t k,
  class Extents, class Slice,
  /* requires */(index_pair_like<Slice, size_t>::value)
)
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(
  std::integral_constant<size_t, k>,
  const Extents &,
  const Slice &i)
{
  using std::get;
  return get<1>(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  size_t k,
  class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::tuple<IdxT1, IdxT2>, size_t>::value)
  )
constexpr auto last_of(
  std::integral_constant<size_t, k>,
  const Extents &,
  const std::tuple<IdxT1, IdxT2>& i)
{
  using std::get;
  return get<1>(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  size_t k,
  class Extents, class IdxT1, class IdxT2,
  /* requires */ (index_pair_like<std::pair<IdxT1, IdxT2>, size_t>::value)
  )
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(
  std::integral_constant<size_t, k>,
  const Extents &,
  const std::pair<IdxT1, IdxT2>& i)
{
  return i.second;
}

template<size_t k, class Extents, class T>
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(
  std::integral_constant<size_t, k>,
  const Extents &,
  const std::complex<T> &i)
{
  return i.imag();
}

#endif // ! defined(MDSPAN_ENABLE_P3663)

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
template <
#if defined(MDSPAN_ENABLE_P3663)
  auto
#else
  size_t
#endif  
  k,
  class Extents>
MDSPAN_INLINE_FUNCTION
constexpr auto last_of(
#if defined(MDSPAN_ENABLE_P3663)
  std::constant_wrapper<k>,
#else
  std::integral_constant<size_t, k>,
#endif
  const Extents &ext,
  ::MDSPAN_IMPL_STANDARD_NAMESPACE::full_extent_t)
{
#if defined(MDSPAN_ENABLE_P3663)
  constexpr size_t k_value = std::constant_wrapper<k>{}();
#else
  constexpr size_t k_value = k;
#endif

  if constexpr (Extents::static_extent(k_value) == dynamic_extent) {
    return ext.extent(k_value);
  }
  else {
#if defined(MDSPAN_ENABLE_P3663)
    return std::cw<Extents::static_extent(k_value)>;
#else
    return integral_constant<size_t, Extents::static_extent(k_value)>();
#endif
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

template <
#if defined(MDSPAN_ENABLE_P3663)
  auto
#else
  size_t
#endif  
  k,
  class Extents,
  class OffsetType,
  class ExtentType,
  class StrideType>
MDSPAN_INLINE_FUNCTION
constexpr OffsetType
last_of(
#if defined(MDSPAN_ENABLE_P3663)
  std::constant_wrapper<k>,
#else
  std::integral_constant<size_t, k>,
#endif
  const Extents &,
  const strided_slice<OffsetType, ExtentType, StrideType> &r)
{
  return r.extent; // FIXME then why does this return OffsetType?
}

// get stride of slices
template <class T>
MDSPAN_INLINE_FUNCTION
constexpr auto stride_of(const T &) {
#if defined(MDSPAN_ENABLE_P3663)
  return std::cw<size_t(1)>;
#else
  return integral_constant<size_t, 1>();
#endif
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
  return std::cw<IndexType(i0() == 0 ? 0 : i0() / i1())>;
}
#else
template <class IndexT, class T0, T0 v0, class T1, T1 v1>
MDSPAN_INLINE_FUNCTION
constexpr auto divide(const std::integral_constant<T0, v0> &,
                      const std::integral_constant<T1, v1> &) {
  // cutting short division by zero
  // this is used for strided_slice with zero extent/stride
  return integral_constant<IndexT, v0 == 0 ? 0 : v0 / v1>();
}
#endif

// multiply which can deal with integral constant preservation
template <class IndexT, class T0, class T1>
MDSPAN_INLINE_FUNCTION
constexpr auto multiply(const T0 &v0, const T1 &v1) {
  return IndexT(v0) * IndexT(v1);
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

  return std::cw<IndexType(i0() * i1())>;
}
#else
template <class IndexT, class T0, T0 v0, class T1, T1 v1>
MDSPAN_INLINE_FUNCTION
constexpr auto multiply(const std::integral_constant<T0, v0> &,
                        const std::integral_constant<T1, v1> &) {
  return integral_constant<IndexT, v0 * v1>();
}
#endif

// compute new static extent from range, preserving static knowledge
template <class A, class B,
  bool both_integral_constant_like =
    is_integral_constant_like_v<A> && is_integral_constant_like_v<B>
>
struct StaticExtentFromRange {
  static constexpr ::std::size_t value = dynamic_extent;
};

template <class A, class B>
struct StaticExtentFromRange<A, B, true> {
  static constexpr ::std::size_t value = B::value - A::value;
};

// compute new static extent from strided_slice, preserving static
// knowledge
template <class Arg0, class Arg1> struct StaticExtentFromStridedRange {
  constexpr static size_t value = dynamic_extent;
};

#if defined(MDSPAN_ENABLE_P3663)
template <auto A, auto B>
struct StaticExtentFromStridedRange<std::constant_wrapper<A>, std::constant_wrapper<B>> {
private:
  static constexpr auto A_value = std::constant_wrapper<A>{}();
  static constexpr auto B_value = std::constant_wrapper<B>{}();
public:
  constexpr static size_t value = A_value > 0 ? 1 + (A_value - 1) / B_value : 0;
};
#else
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
#endif

// creates new extents through recursive calls to next_extent member function
// next_extent has different overloads for different types of stride specifiers
template <size_t K, class Extents, size_t... NewExtents>
struct extents_constructor {

  // This covers both the full_extent_t and index-pair-like cases.
  // P3663 only needs the full_extent_t case.
#if defined(MDSPAN_ENABLE_P3663)
  template<class... SlicesAndExtents>
#else
  MDSPAN_TEMPLATE_REQUIRES(
    class Slice, class... SlicesAndExtents,
    /* requires */(!std::is_convertible_v<Slice, size_t> &&
                   !is_strided_slice<Slice>::value)
  )
#endif
  MDSPAN_INLINE_FUNCTION
  constexpr static auto next_extent(
    const Extents &ext,
#if defined(MDSPAN_ENABLE_P3663)
    full_extent_t sl,
#else
    const Slice &sl,
#endif
    SlicesAndExtents... slices_and_extents)
  {
#if defined(MDSPAN_ENABLE_P3663)
    using Slice = full_extent_t;
#endif

    constexpr size_t new_static_extent = StaticExtentFromRange<
        decltype(first_of(std::declval<Slice>())),
        decltype(last_of(
#if defined(MDSPAN_ENABLE_P3663)
          std::cw<Extents::rank() - K>,
#else
          std::integral_constant<size_t, Extents::rank() - K>(),
#endif
          std::declval<Extents>(),
          std::declval<Slice>()))>::value;

    using next_t =
        extents_constructor<K - 1, Extents, NewExtents..., new_static_extent>;
    using index_t = typename Extents::index_type;
    return next_t::next_extent(
        ext, slices_and_extents...,
        index_t(last_of(
#if defined(MDSPAN_ENABLE_P3663)
          std::cw<Extents::rank() - K>,
#else
          std::integral_constant<size_t, Extents::rank() - K>(),
#endif
          ext,
          sl)) - index_t(first_of(sl)));
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

MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  class OtherIndexType,
  /* requires */ (
    std::is_signed_v<remove_cvref_t<OtherIndexType>> ||
    std::is_unsigned_v<remove_cvref_t<OtherIndexType>>
  )
)
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
constexpr auto index_cast(OtherIndexType&& i) noexcept {
  return static_cast<IndexType>(i);
}

MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  class S,
  /* requires */ (
    std::is_convertible_v<S, IndexType>
  )
)
constexpr auto canonical_ice(S s) {
  static_assert(std::is_signed_v<IndexType> || std::is_unsigned_v<IndexType>);
  // TODO Mandates: If S models integral-constant-like and if
  // decltype(S::value) is a signed or unsigned integer type, then
  // S::value is representable as a value of type IndexType.
  //
  // TODO Preconditions: If S is a signed or unsigned integer type,
  // then s is representable as a value of type IndexType.
  //
  // NOTE Added to P3663R2: Use cw instead of constant_wrapper.
  //
  // NOTE Added to P3663R2: Specify that index-cast result is
  // cast to IndexType before being used as the template argument
  // of `cw`, so we don't get a weird constant_wrapper whose value
  // has a different type than the second template argument.
  if constexpr (is_integral_constant_like_v<S>) {
    return std::cw<static_cast<IndexType>(index_cast<IndexType>(S::value))>;
  }
  else {
    return static_cast<IndexType>(index_cast<IndexType>(s));
  }
}

template<class IndexType, class X, class Y>
constexpr auto subtract_ice(X x, Y y) {
#if defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
  // Key to the work-around is acknowledging that GCC 11.4.0 can't find
  // constant_wrapper's overloaded arithmetic operators.
  if constexpr (is_integral_constant_like_v<remove_cvref_t<X>> &&
    is_integral_constant_like_v<remove_cvref_t<Y>>)
  {
    return std::cw<IndexType(canonical_ice<IndexType>(Y::value) - canonical_ice<IndexType>(X::value))>;
  }
  else {
    return canonical_ice<IndexType>(y) - canonical_ice<IndexType>(x);
  }
#else
  return canonical_ice<IndexType>(y) - canonical_ice<IndexType>(x);
#endif
}

MDSPAN_TEMPLATE_REQUIRES(
  class T,
  /* requires */ (
    std::is_integral_v<remove_cvref_t<T>>
  )
)
constexpr T de_ice(T val) {
  return val;
}

MDSPAN_TEMPLATE_REQUIRES(
  class T,
  /* requires */ (
    is_integral_constant_like_v<remove_cvref_t<T>>
  )
)
constexpr decltype(T::value) de_ice(T) {
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

// NOTE It's impossible to write an "if constexpr" check for
// "structured binding into two elements is well-formed."  Thus, we
// must assume that the input Slices are all valid slice types.
// One way to do that is to invoke this only post-canonicalization.
// Another way is to rely on submdspan_canonicalize_slices to be
// ill-formed if called with an invalid slice type.  We can do the
// latter in submdspan_canonicalize_slices by expressing the four
// possible categories of valid slice types in if constexpr, with
// the final else attempting the structured binding into two elements.

// DONE Added to P3663R2: Rewrite wording to use only $S_k$
// and not $s_k$ in check-static-bounds, since we can't use
// the actual function parameter in a function that we want
// to work in a constant expression.

// DONE Added to P3663R2: Implementation takes k and one slice
// only (S_k) as explicit template parameters, rather than
// passing in the whole parameter pack of slices.  This makes
// sense because the function only tests one slice (the k-th one).
// Also, taking slices parameter(s) makes use of check_static_bounds
// not a constant expression.

// DONE Added to P3663R2: Check wording of check-static-bounds
// so that it only assumes that types are default constructible
// in constant expressions if they are integral-constant-like.

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
      // integral-constant-like types are default constructible
      // in constant expressions, so it's OK to use S_k{} here
      // instead of std::declval.  Also, expressions like
      // de_ice(std::declval<S_k>()) are not constant expressions.
      if constexpr (de_ice(S_k{}) < 0) {
        return check_static_bounds_result::out_of_bounds; // 14.3.1
      }
      else if constexpr (Exts_k != dynamic_extent && Exts_k <= de_ice(S_k{})) {
        return check_static_bounds_result::out_of_bounds;
      }
      else if constexpr (Exts_k != dynamic_extent && de_ice(S_k{}) < Exts_k) {
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
    using offset_type = typename S_k::offset_type;

    if constexpr (is_integral_constant_like_v<offset_type>) {
      if constexpr (de_ice(offset_type{}) < 0) {
        return check_static_bounds_result::out_of_bounds; // 14.3.1
      }
      else if constexpr (
        Exts_k != dynamic_extent && Exts_k < de_ice(offset_type{}))
      {
        return check_static_bounds_result::out_of_bounds; // 14.3.2
      }
      else if constexpr (is_integral_constant_like_v<typename S_k::extent_type>) {
        using extent_type = typename S_k::extent_type;

        if constexpr (de_ice(offset_type{}) + de_ice(extent_type{}) < 0) {
          return check_static_bounds_result::out_of_bounds; // 14.3.3
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          Exts_k < de_ice(offset_type{}) + de_ice(extent_type{}))
        {
          return check_static_bounds_result::out_of_bounds; // 14.3.4
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          0 <= de_ice(offset_type{}) &&
          de_ice(offset_type{}) <= de_ice(offset_type{}) + de_ice(extent_type{}) &&
          de_ice(offset_type{}) + de_ice(extent_type{}) <= Exts_k)
        {
          return check_static_bounds_result::in_bounds; // 14.3.5
        }
        else {
          return check_static_bounds_result::unknown; // 14.3.6
        }
      }
      else {
        return check_static_bounds_result::unknown; // 14.5
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
    // That implements the Mandates clause.
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
    if constexpr (is_integral_constant_like_v<S_k0>) {
      if constexpr (de_ice(S_k0{}) < 0) {
        return check_static_bounds_result::out_of_bounds; // 14.4.1
      }
      else if constexpr (
        Exts_k != dynamic_extent &&
        Exts_k < de_ice(S_k0{}))
      {
        return check_static_bounds_result::out_of_bounds; // 14.4.2
      }
      else if constexpr (is_integral_constant_like_v<S_k1>) {
        if constexpr (
          de_ice(S_k1{}) < de_ice(S_k0{}))
        {
          return check_static_bounds_result::out_of_bounds; // 14.4.3
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          Exts_k < de_ice(S_k1{}))
        {
          return check_static_bounds_result::out_of_bounds; // 14.4.4
        }
        else if constexpr (
          Exts_k != dynamic_extent &&
          0 <= de_ice(S_k0{}) &&
          de_ice(S_k0{}) <= de_ice(S_k1{}) &&
          de_ice(S_k1{}) <= Exts_k)
        {
          return check_static_bounds_result::in_bounds; // 14.4.5
        }
        else {
          return check_static_bounds_result::unknown; // 14.4.6
        }
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

// [mdspan.sub.slices] 1
template<class IndexType, class T>
constexpr bool is_canonical_submdspan_index_type() {
  if constexpr (is_constant_wrapper<T>) {
    using value_type = typename T::value_type;
    return std::is_same_v<value_type, IndexType>;
  }
  else {
    return std::is_same_v<T, IndexType>;
  }
}

// [mdspan.sub.slices] 2
template<class IndexType, class Slice>
MDSPAN_INLINE_FUNCTION
constexpr bool is_canonical_slice_type() {
  if constexpr (std::is_same_v<Slice, full_extent_t>) { // 2.1
    return true;
  }
  else if constexpr (is_canonical_submdspan_index_type<IndexType, Slice>()) { // 2.2
    return true;
  }
  else if constexpr (is_strided_slice<Slice>::value) { // 2.3
    if constexpr ( // 2.3.1
      is_canonical_submdspan_index_type<IndexType, typename Slice::offset_type>() &&
      is_canonical_submdspan_index_type<IndexType, typename Slice::extent_type>() &&
      is_canonical_submdspan_index_type<IndexType, typename Slice::stride_type>())
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
        return true;
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
constexpr void
check_canonical_kth_submdspan_slice_type(
  const extents<IndexType, Extents...>&,
  [[maybe_unused]] Slice slice)
{
  if constexpr (! is_canonical_slice_type<IndexType, Slice>()) {
#if defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
    static_assert(is_canonical_slice_type<IndexType, Slice>());
#else
    static_assert(false);
#endif
  }
  else { // 3.2
    static_assert(check_static_bounds<k, decltype(slice)>(extents<IndexType, Extents...>{}) != check_static_bounds_result::out_of_bounds);
  }
}


#if defined(__cpp_pack_indexing) && (! (defined(__GNUC__) && (__GNUC__ < 16)))
// nothing
#else
template<size_t k, class First, class... Rest>
constexpr decltype(auto) get_kth_in_pack(First&& first, Rest&&... rest) {
  static_assert(k <= sizeof...(Rest));
  if constexpr (k == 0) {
    return std::forward<First>(first);
  }
  else {
    return get_kth_in_pack<k - 1>(std::forward<Rest>(rest)...);
  }
}
#endif

#if (__cplusplus < 202002L)
template<size_t... Inds, class IndexType, size_t... Extents, class ... Slices>
MDSPAN_INLINE_FUNCTION
constexpr void
check_canonical_kth_subdmspan_slice_types_impl(
  std::index_sequence<Inds...>,
  const extents<IndexType, Extents...>& exts,
  Slices... slices)
{
  (check_canonical_kth_submdspan_slice_type<Inds>(
    exts,
    get_kth_in_pack<Inds>(slices...)), ...);
}
#endif // (__cplusplus < 202002L)

template<class IndexType, size_t... Extents, class ... Slices>
MDSPAN_INLINE_FUNCTION
constexpr void
check_canonical_kth_subdmspan_slice_types(
  const extents<IndexType, Extents...>& exts, Slices... slices)
{
#if (__cplusplus < 202002L)
  check_canonical_kth_subdmspan_slice_types_impl(
    std::make_index_sequence<sizeof...(Slices)>(), exts, slices...);
#else
  // We really want to keep the C++20 branch here
  // because it could offer compile time advantages.
  [&] <size_t ... Inds> (std::index_sequence<Inds...>) {
    (check_canonical_kth_submdspan_slice_type<Inds>(
      exts,
#if defined(__cpp_pack_indexing) && (! (defined(__GNUC__) && (__GNUC__ < 16)))
      slices...[Inds]
#else
      get_kth_in_pack<Inds>(slices...)
#endif
    ), ...);
  } (std::make_index_sequence<sizeof...(Slices)>{});
#endif // (__cplusplus < 202002L)
}

// [mdspan.sub.slices] 11
template<size_t k, class Slice, class IndexType, size_t... Extents>
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_one_slice(
  [[maybe_unused]] const extents<IndexType, Extents...>& exts,
  [[maybe_unused]] Slice s)
{
  // Part of [mdspan.sub.slices] 9.
  // This could be combined with the if constexpr branches below.
#if defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
  static_assert(check_static_bounds<k, decltype(s)>(extents<IndexType, Extents...>{}) != check_static_bounds_result::out_of_bounds);
#else
  static_assert(check_static_bounds<k, decltype(s)>(exts) != check_static_bounds_result::out_of_bounds);
#endif

  // TODO Check Precondition that s is a valid k-th submdspan slice for exts.

  if constexpr (std::is_convertible_v<Slice, full_extent_t>) {
    return full_extent; // 11.1
  }
  else if constexpr (std::is_convertible_v<Slice, IndexType>) {
    return canonical_ice<IndexType>(s); // 11.2
  }
  else if constexpr (is_strided_slice<Slice>::value) { // 11.3
#if ! defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
    // GCC 11.4.0 (C++20) accepts this code, but Clang 14 does not.
    return strided_slice{
      .offset = canonical_ice<IndexType>(s.offset),
      .extent = canonical_ice<IndexType>(s.extent),
      .stride = canonical_ice<IndexType>(s.stride)
    };
#else
    auto offset = canonical_ice<IndexType>(s.offset);
    auto extent = canonical_ice<IndexType>(s.extent);
    auto stride = canonical_ice<IndexType>(s.stride);
    return strided_slice<decltype(offset),
                         decltype(extent),
                         decltype(stride)> {
      /* .offset = */ offset,
      /* .extent = */ extent,
      /* .stride = */ stride
    };
#endif
  }
#if ! defined(__cpp_lib_tuple_like) || (__cpp_lib_tuple_like < 202311L)
  else if constexpr (detail::is_std_complex<Slice>) {
#if ! defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
    // GCC 11.4.0 (C++20) accepts this code, but Clang 14 does not.
    return strided_slice{
      .offset = canonical_ice<IndexType>(s.real()),
      .extent = canonical_ice<IndexType>(s.imag() - s.real()),
      .stride = std::cw<IndexType(1)>
    };
#else
    auto offset = canonical_ice<IndexType>(s.real());
    auto extent = canonical_ice<IndexType>(s.imag() - s.real());
    auto stride = std::cw<IndexType(1)>;
    return strided_slice<decltype(offset),
                         decltype(extent),
                         decltype(stride)> {
      /* .offset = */ offset,
      /* .extent = */ extent,
      /* .stride = */ stride
    };
#endif
  }
#endif
  else { // 11.4
    auto [s_k0, s_k1] = s;
    using S_k0 = decltype(s_k0);
    using S_k1 = decltype(s_k1);
    static_assert(std::is_convertible_v<S_k0, IndexType>);
    static_assert(std::is_convertible_v<S_k1, IndexType>);
#if ! defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
    // GCC 11.4.0 (C++20) accepts this code, but Clang 14 does not.
    return strided_slice{
      .offset = canonical_ice<IndexType>(s_k0),
      .extent = subtract_ice<IndexType>(s_k0, s_k1),
      .stride = std::cw<IndexType(1)>
    };
#else
    auto offset = canonical_ice<IndexType>(s_k0);
    auto extent = subtract_ice<IndexType>(s_k0, s_k1);
    auto stride = std::cw<IndexType(1)>;
    return strided_slice<decltype(offset),
                         decltype(extent),
                         decltype(stride)> {
      /* .offset = */ offset,
      /* .extent = */ extent,
      /* .stride = */ stride
    };
#endif
  }
}

} // namespace detail

MDSPAN_TEMPLATE_REQUIRES(
  size_t... Inds,
  class IndexType,
  size_t... Extents,
  class... Slices,
  /* requires */ (
    sizeof...(Slices) == sizeof...(Extents)
  )
)
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_slices_impl(
  std::index_sequence<Inds...>,
  const extents<IndexType, Extents...>& exts,
  Slices... slices)
{
  return std::tuple{
    // This is ill-formed if slices...[Inds] is not a valid slice type.
    // That implements the Mandates clause of [mdspan.sub.slices] 9.
    detail::submdspan_canonicalize_one_slice<Inds>(
      exts,
    // Clang 21 accepts this code.
    // GCC 15.1.0 emits an error: "cannot index an empty pack."
#if defined(__cpp_pack_indexing) && (! (defined(__GNUC__) && (__GNUC__ < 16)))
      slices...[Inds]
#else
      detail::get_kth_in_pack<Inds>(slices...)
#endif
    )...
  };
}

MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  size_t... Extents,
  class... Slices,
  /* requires */ (
    sizeof...(Slices) == sizeof...(Extents)
  )
)
MDSPAN_INLINE_FUNCTION
constexpr auto
submdspan_canonicalize_slices(const extents<IndexType, Extents...>& exts, Slices&&... slices)
{
  return submdspan_canonicalize_slices_impl(std::make_index_sequence<sizeof...(Slices)>(), exts, slices...);
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
