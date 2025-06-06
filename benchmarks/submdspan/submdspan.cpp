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
#include "fill.hpp"

#include <mdspan/mdspan.hpp>

#include <benchmark/benchmark.h>

#include <bit>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>

// This benchmark measures the overhead of submdspan slice
// canonicalization as proposed by P3663R2.
//
// Slice canonicalization happens in the submdspan function,
// before slices reach the layout mapping's submdspan_mapping
// customization.  Thus, we need to call submdspan itself,
// but the layout mapping type does not matter.
// We do want to exercise a Standard layout mapping, though.
//
// The mdspan's value type doesn't matter either,
// so we can use a char-sized type to minimize storage.
// Using unsigned char makes overflow defined behavior.

template<class IndexType, size_t... Exts>
using nonconst_test_mdspan =
  Kokkos::mdspan<unsigned char, Kokkos::extents<IndexType, Exts...>>;

template<class IndexType, size_t... Exts>
using const_test_mdspan =
  Kokkos::mdspan<const unsigned char, Kokkos::extents<IndexType, Exts...>>;

template<class IndexType, size_t... Exts>
size_t submdspan_benchmark(benchmark::State& state,
  nonconst_test_mdspan<IndexType, Exts...> out)
{
  size_t count_not_same = 0;
  for (auto _ : state) {
    const auto p = std::pair{IndexType(0), IndexType(1)};
    auto out_sub = Kokkos::submdspan(out, ((void) Exts, p)...);
    if (out_sub[((void) Exts, 0)...] != out[((void) Exts, p.first)...]) {
      ++count_not_same;
    }
    out_sub[((void) Exts, 0)...] += static_cast<unsigned char>(1u);

    benchmark::DoNotOptimize(count_not_same);
  }
  return count_not_same;
}

template<class IndexType, size_t... Exts>
class benchmark_buffer {
public:
  using value_type = unsigned char;

  benchmark_buffer(Kokkos::extents<IndexType, Exts...> exts) :
    mapping_{exts},
    buffer_{std::make_unique<value_type[]>(mapping_.required_span_size())}
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
  std::unique_ptr<value_type[]> buffer_;
};

template<class IndexType, size_t... Exts>
void submdspan_run_benchmark(benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  auto buf = benchmark_buffer{exts};
  mdspan_benchmark::fill_random(buf.get_mdspan());

  size_t count_not_same = submdspan_benchmark(state, buf.get_mdspan());
  if (count_not_same != 0) {
    std::cerr << "submdspan_benchmark failed: count not same = " << count_not_same << std::endl;
    std::terminate();
  }

  auto get_0th_element = [] (auto x) { return x[((void) Exts, 0)...]; };
  auto buf_0s_after = get_0th_element(buf.get_mdspan());
  benchmark::DoNotOptimize(buf_0s_after);
}

BENCHMARK_CAPTURE(submdspan_run_benchmark, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

// Make the compiler work harder by using a slice type
// that's convertible to index_type, but neither integral
// nor integral-constant-like.
template<class IndexType>
  requires (std::is_signed_v<IndexType> || std::is_unsigned_v<IndexType>)
class index_holder {
public:
  index_holder(IndexType i) : i_{i} {}
  constexpr operator IndexType() const noexcept { return i_; }
  constexpr index_holder& operator++() noexcept {
    ++i_;
    return *this;
  }
  constexpr auto operator<=>(const index_holder&) const noexcept = default;

private:
  IndexType i_;
};
static_assert(std::is_convertible_v<index_holder<int>, int>);
static_assert(std::is_convertible_v<index_holder<size_t>, size_t>);
static_assert(std::is_nothrow_constructible_v<int, index_holder<int>>);
static_assert(std::is_nothrow_constructible_v<size_t, index_holder<size_t>>);

// Make the compiler work harder by using a slice type
// that's convertible to full_extent_t, but not full_extent_t.
struct same_as_full_extent_t {
  constexpr operator Kokkos::full_extent_t() const noexcept {
    return Kokkos::full_extent;
  }
};

template<class ElementType, class Layout, class Accessor, class Slice, class IndexType, size_t... Exts>
constexpr auto slice_one_extent(
  Kokkos::mdspan<ElementType, Kokkos::extents<IndexType, Exts...>, Layout, Accessor> x, Slice slice)
{
  if constexpr (sizeof...(Exts) == 0) {
    static_assert(false, "slice_one_extent called with no extents");
  }
  else if constexpr (sizeof...(Exts) == 1) {
    return Kokkos::submdspan(x, slice);
  }
  else {
    return [&] <size_t... Inds> (std::index_sequence<Inds...>) {
      return Kokkos::submdspan(x, slice, ((void) Inds, same_as_full_extent_t{})...);
    } (std::make_index_sequence<sizeof...(Exts) - 1u>());
  }
}

// Multiply elements by 3, using 1-D slices.
template<class OutMdspan>
void submdspan_benchmark2_loop(const OutMdspan& out) {
  using index_type = typename OutMdspan::index_type;

  if constexpr (OutMdspan::rank() == 0) {
    return;
  }
  else if constexpr (OutMdspan::rank() == 1) {
    const auto ext0 = out.extent(0);
    for (index_type k = 0; k < ext0; ++k) {
      out[k] *= 3u;
    }
  }
  else {
    const auto ext0 = index_holder{index_type(out.extent(0))};
    for (auto k = index_holder{index_type(0)}; k < ext0; ++k) {
      submdspan_benchmark2_loop(slice_one_extent(out, k));
    }
  }
}

template<class IndexType, size_t... Exts>
size_t submdspan_benchmark2(benchmark::State& state,
  nonconst_test_mdspan<IndexType, Exts...> out)
{
  size_t count = 0;
  for (auto _ : state) {
    submdspan_benchmark2_loop(out);
    ++count;
  }
  benchmark::DoNotOptimize(count);
  return count;
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

inline constexpr size_t
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

inline constexpr size_t
expected_element(size_t original_element, size_t count) {
  constexpr size_t base = 3u;
  constexpr size_t modulus = 256u;
  return ((original_element % modulus)* base_to_the_exponent_mod_modulus(base, count, modulus)) % modulus;
};

template<class IndexType, size_t... Exts>
void submdspan_run_benchmark2(benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  auto in_buf = benchmark_buffer{exts};
  auto out_buf = benchmark_buffer{exts};
  mdspan_benchmark::fill_random(in_buf.get_mdspan());

  // We're using layout_right, so we don't need the layout mapping to iterate over the elements.
  const size_t num_elements = out_buf.size();
  {
    auto in = in_buf.get_mdspan().data_handle();
    auto out = out_buf.get_mdspan().data_handle();
    for (size_t i = 0; i < num_elements; ++i) {
      out[i] = in[i];
    }
  }
  const size_t count = submdspan_benchmark2(state,out_buf.get_mdspan());
  {
    auto in = in_buf.get_mdspan().data_handle();
    auto out = out_buf.get_mdspan().data_handle();
    for (size_t i = 0; i < num_elements; ++i) {
      const auto original = in[i];
      const auto expected = expected_element(original, count);
      if (out[i] != expected) {
        std::cerr << "submdspan_benchmark2 failed: out[" << i << "] = "
          << out[i] << " != " << expected << std::endl;
        std::terminate();
      }
    }
  }
}

BENCHMARK_CAPTURE(submdspan_run_benchmark2, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark2, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(submdspan_run_benchmark2, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark2, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

BENCHMARK_MAIN();
