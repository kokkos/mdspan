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

#include <mdspan/mdspan.hpp>
#include <benchmark/benchmark.h>

#include <algorithm>
#include <bit>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>

namespace submdspan_benchmark {

#if defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)

template<class ElementType, class Extents, class Layout, class Accessor, size_t... Indices>
constexpr typename Kokkos::mdspan<ElementType, Extents, Layout, Accessor>::reference
get_broadcast_element_impl(
  const Kokkos::mdspan<ElementType, Extents, Layout, Accessor>& x,
  typename Extents::index_type broadcast_index,
  std::index_sequence<Indices...>)
{
#if defined(MDSPAN_USE_BRACKET_OPERATOR) && (MDSPAN_USE_BRACKET_OPERATOR != 0)
  return x[((void) Indices, 0)...];
#else
  return x(((void) Indices, 0)...);
#endif
}

template<class ElementType, class Extents, class Layout, class Accessor>
constexpr typename Kokkos::mdspan<ElementType, Extents, Layout, Accessor>::reference
get_broadcast_element(
  const Kokkos::mdspan<ElementType, Extents, Layout, Accessor>& x,
  typename Extents::index_type broadcast_index)
{
  return get_broadcast_element_impl(x, broadcast_index, std::make_index_sequence<Extents::rank()>());
}

#else

template<class ElementType, class IndexType, size_t... Exts, class Layout, class Accessor>
constexpr typename Kokkos::mdspan<ElementType, Kokkos::extents<IndexType, Exts...>, Layout, Accessor>::reference
get_broadcast_element(
  const Kokkos::mdspan<ElementType, Kokkos::extents<IndexType, Exts...>, Layout, Accessor>& x,
  typename Kokkos::extents<IndexType, Exts...>::index_type broadcast_index)
{
  return x[((void) Exts, broadcast_index)...];
}

#endif

template<class IndexType, size_t... Exts>
using nonconst_test_mdspan =
  Kokkos::mdspan<std::uint8_t, Kokkos::extents<IndexType, Exts...>>;

template<class IndexType, size_t... Exts>
using const_test_mdspan =
  Kokkos::mdspan<const std::uint8_t, Kokkos::extents<IndexType, Exts...>>;

class random_state_t {
public:
  using seed_type = std::mt19937::result_type;

  random_state_t() : gen_(default_seed) {}
  random_state_t(seed_type seed) : gen_(seed) {}

  std::mt19937& generator() noexcept { return gen_; }

private:
  static constexpr seed_type default_seed = 1234u;
  std::mt19937 gen_;
};

template<class ExecutionSpace, class ValueType>
struct array_deleter {};

template<class ExecutionSpace, class ValueType>
using array_deleter_t = typename array_deleter<ExecutionSpace, ValueType>::type;

struct host_execution_space {};

template<class ValueType>
struct array_deleter<host_execution_space, ValueType> {
  using type = std::default_delete<ValueType[]>;
};

template<class ValueType>
std::unique_ptr<ValueType[], array_deleter_t<host_execution_space, ValueType>>
allocate_buffer(host_execution_space, size_t num_elements) {
  return std::make_unique<ValueType[]>(num_elements);
}

template <class IndexType, size_t... Exts>
void fill_with_random_values(
  host_execution_space,
  random_state_t& state,
  nonconst_test_mdspan<IndexType, Exts...> s)
{
  auto val_dist = std::uniform_int_distribution<std::uint8_t>(0u, 255u);
  auto next = [&] () {
    return val_dist(state.generator());
  };
  std::generate(s.data_handle(), s.data_handle() + s.size(), next);
}

template<class ExecutionSpace, class IndexType, size_t... Exts>
class benchmark_buffer {
public:
  using value_type = std::uint8_t;

  benchmark_buffer(ExecutionSpace exec_space, Kokkos::extents<IndexType, Exts...> exts) :
    mapping_{exts},
    buffer_{allocate_buffer<value_type>(exec_space, mapping_.required_span_size())}
  {}

  size_t size() const {
    return mapping_.required_span_size();
  }

  nonconst_test_mdspan<IndexType, Exts...> get_mdspan() {
    return {buffer_.get(), mapping_};
  }

  const_test_mdspan<IndexType, Exts...> get_mdspan() const {
    return {static_cast<const value_type*>(buffer_.get()), mapping_};
  }

private:
  Kokkos::layout_right::template mapping<Kokkos::extents<IndexType, Exts...>> mapping_;
  std::unique_ptr<value_type[], array_deleter_t<ExecutionSpace, value_type>> buffer_;
};

template<class ExecutionSpace, class IndexType, size_t... Exts>
size_t benchmark1_impl(ExecutionSpace /* exec_space */,
  benchmark::State& state,
  nonconst_test_mdspan<IndexType, Exts...> out);

// This works for host_execution_space and cuda_execution_space.
template<class ExecutionSpace, class IndexType, size_t... Exts>
void benchmark1(ExecutionSpace exec_space,
  benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  random_state_t random_state{};
  auto buf = benchmark_buffer{exec_space, exts};
  fill_with_random_values(exec_space, random_state, buf.get_mdspan());

  size_t count_not_same = benchmark1_impl(exec_space, state, buf.get_mdspan());
  if (count_not_same != 0) {
    std::cerr << "benchmark1 failed: count not same = " << count_not_same << std::endl;
    std::terminate();
  }

  auto buf_0s_after = get_broadcast_element(buf.get_mdspan(), 0);
  benchmark::DoNotOptimize(buf_0s_after);
}

// Index or slice type that's convertible to IndexType,
// but neither integral nor integral-constant-like.
MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  /* requires */ (
    std::is_signed_v<IndexType> || std::is_unsigned_v<IndexType>
  )
)
class index_holder {
public:
  constexpr MDSPAN_FUNCTION index_holder(IndexType i) : i_{i} {}
  constexpr MDSPAN_FUNCTION operator IndexType() const noexcept { return i_; }
  constexpr MDSPAN_FUNCTION index_holder& operator++() noexcept {
    ++i_;
    return *this;
  }
#if defined(__cpp_impl_three_way_comparison)
  constexpr MDSPAN_FUNCTION auto operator<=>(const index_holder&) const noexcept = default;
#else
  friend constexpr MDSPAN_FUNCTION bool operator<(const index_holder& x, const index_holder& y) noexcept {
    return x.i_ < y.i_;
  }
  friend constexpr MDSPAN_FUNCTION bool operator==(const index_holder& x, const index_holder& y) noexcept {
    return x.i_ == y.i_;
  }
#endif

private:
  IndexType i_;
};
static_assert(std::is_convertible_v<index_holder<int>, int>);
static_assert(std::is_convertible_v<index_holder<size_t>, size_t>);
static_assert(std::is_nothrow_constructible_v<int, index_holder<int>>);
static_assert(std::is_nothrow_constructible_v<size_t, index_holder<size_t>>);

// Slice type that's convertible to full_extent_t, but is not full_extent_t.
struct full_extent_wrapper_t {
  constexpr operator Kokkos::full_extent_t() const noexcept{
    return Kokkos::full_extent;
  }
};

template<class ElementType, class Layout, class Accessor, class Slice, class IndexType, size_t... Exts>
constexpr MDSPAN_FUNCTION auto slice_one_extent(
  Kokkos::mdspan<ElementType, Kokkos::extents<IndexType, Exts...>, Layout, Accessor> x, Slice slice)
{
  if constexpr (sizeof...(Exts) == 0) {
#if defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
    static_assert(sizeof...(Exts) != 0, "slice_one_extent called with no extents");
#else
    static_assert(false, "slice_one_extent called with no extents");
#endif
  }
  else if constexpr (sizeof...(Exts) == 1) {
    return Kokkos::submdspan(x, slice);
  }
  else {
    return [&] <size_t... Inds> (std::index_sequence<Inds...>) {
      return Kokkos::submdspan(x, slice, ((void) Inds, full_extent_wrapper_t{})...);
    } (std::make_index_sequence<sizeof...(Exts) - 1u>());
  }
}

// Elements of x are uint8_t, so computations happen modulo 256.
// For each element x_e of x, on output, result is
//
//   (x_e * 3^count) mod 256
// = ((x_e mod 256) * (3^count mod 256)) mod 256.
//
// If count is a power of two, we can compute (3^count) mod 256
// by divide and conquer.
//
//   (3^count) mod 256
// = ((3^(count/2)) mod 256) * ((3^(count/2)) mod 256) mod 256.

constexpr MDSPAN_INLINE_FUNCTION size_t
base_to_the_exponent_mod_modulus(size_t base, size_t exponent, size_t modulus)
{
  if (modulus == 1u) {
    return 0u;
  }
  // modulus - 1u) * (modulus - 1u) must not overflow base
  size_t result = 1u;
  base = base % modulus;
  while (exponent > 0u) {
    if (exponent % 2u == 1u) {
      result = (result * base) % modulus;
    }
    exponent = exponent >> 1u;
    base = (base * base) % modulus;
  }
  return result;
}

constexpr MDSPAN_INLINE_FUNCTION size_t
expected_element(size_t original_element, size_t count) {
  constexpr size_t base = 3u;
  constexpr size_t modulus = 256u;
  return ((original_element % modulus) * base_to_the_exponent_mod_modulus(base, count, modulus)) % modulus;
}

} // namespace submdspan_benchmark
