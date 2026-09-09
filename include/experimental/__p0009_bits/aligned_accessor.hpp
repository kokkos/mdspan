/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/


// NOTE: This code is prematurely taken from an example based on
// https://github.com/kokkos/mdspan/pull/176

#pragma once

#include "macros.hpp"
#include "default_accessor.hpp"
#include <cassert>
#include <cstdint>
#include <memory>
#include <type_traits>

// If we don't have bitcast, we should use memcpy
#ifndef __cpp_lib_bit_cast
#include <bit>
#include <cstring>
#endif

// Some compilers other than Clang or GCC like to define __clang__ or __GNUC__.
// Thus, we order the tests from most to least specific.
#if defined(__ICL)
#define MDSPAN_ALIGN(BYTE_ALIGNMENT) __declspec(align_value(BYTE_ALIGNMENT))
#elif defined(__ICC)
#define MDSPAN_ALIGN(BYTE_ALIGNMENT)                                           \
  __attribute__((align_value(BYTE_ALIGNMENT)))
#elif defined(__clang__)
#define MDSPAN_ALIGN(BYTE_ALIGNMENT)                                           \
  __attribute__((align_value(BYTE_ALIGNMENT)))
#else
#define MDSPAN_ALIGN(BYTE_ALIGNMENT)
#endif

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
namespace detail {
constexpr bool
has_single_bit(const std::size_t x)
{
// Just checking __cpp_lib_int_pow2 isn't enough for some GCC versions.
// The <bit> header exists, but std::has_single_bit does not.
#if defined(__cpp_lib_int_pow2) && __cplusplus >= 202002L
  return std::has_single_bit(x);
#else
  return x != 0 && (x & (x - 1)) == 0;
#endif
}
} // namespace detail

#ifdef __cpp_lib_assume_aligned
using std::assume_aligned;
#elif defined(__GNUC__)
template <std::size_t ByteAlignment, class T>
constexpr T *assume_aligned(T *ptr) {
  static_assert(detail::has_single_bit(ByteAlignment),
                "ByteAlignment must be a power of two.");
  return reinterpret_cast<T *>(__builtin_assume_aligned(ptr, ByteAlignment));
}
#else
template <std::size_t ByteAlignment, class T>
constexpr T *assume_aligned(T *ptr) {
  static_assert(detail::has_single_bit(ByteAlignment),
                "ByteAlignment must be a power of two.");
  return ptr;
}
#endif

template<size_t ByteAlignment, class T>
#ifdef __cpp_lib_bit_cast // Only can be constexpr if we have bit_cast
constexpr
#endif
bool is_sufficiently_aligned(T* ptr) {
  static_assert(detail::has_single_bit(ByteAlignment),
		"ByteAlignment must be a power of two.");
#ifdef __cpp_lib_bit_cast
  auto dst = std::bit_cast<std::uintptr_t>(ptr);
#else
  // Will work but non-constexpr
  std::uintptr_t dst;
  std::memcpy(&dst, &ptr, sizeof(std::uintptr_t));
#endif
  return !(dst & (ByteAlignment - 1));
}

template<class ElementType, std::size_t ByteAlignment>
struct aligned_accessor {
  using offset_policy = default_accessor<ElementType>;
  using element_type = ElementType;
  using reference = ElementType&;
  using data_handle_type = ElementType* MDSPAN_ALIGN( ByteAlignment );

  static constexpr size_t byte_alignment = ByteAlignment;
  static_assert(detail::has_single_bit(byte_alignment) && byte_alignment >= alignof(ElementType),
		"byte_alignment must be a power of two no less than "
		"the minimum required alignment of ElementType.");

  constexpr aligned_accessor() noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType,
    std::size_t OtherByteAlignment,
    /* requires */ (std::is_convertible<OtherElementType(*)[], element_type(*)[]>::value && OtherByteAlignment >= byte_alignment)
    )
  constexpr aligned_accessor(aligned_accessor<OtherElementType, OtherByteAlignment>) noexcept {}

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType,
    /* requires */ (std::is_convertible<OtherElementType(*)[], element_type(*)[]>::value)
  )
  constexpr explicit aligned_accessor(default_accessor<OtherElementType>) noexcept {}

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType,
    /* requires */ (std::is_convertible<element_type(*)[], OtherElementType(*)[]>::value)
  )
  constexpr operator default_accessor<OtherElementType>() const noexcept {
    return {};
  }

  constexpr reference access(data_handle_type p, size_t i) const noexcept {
    // This may declare alignment twice, depending on
    // if we have an attribute for marking pointer types.
    return assume_aligned<byte_alignment>(p)[i];
  }

  constexpr typename offset_policy::data_handle_type
  offset(data_handle_type p, size_t i) const noexcept {
    return p + i;
  }
};

}  // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
