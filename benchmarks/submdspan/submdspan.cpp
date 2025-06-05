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

#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <chrono>

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
  std::ostream& output,
  nonconst_test_mdspan<IndexType, Exts...> out)
{
  output << "buf_0s_before = " << static_cast<unsigned int>(out[((void) Exts, 0)...]) << '\n';

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

  size_t count_not_same = submdspan_benchmark(state, std::cerr, buf.get_mdspan());
  if (count_not_same != 0) {
    std::cerr << "submdspan_benchmark failed: count not same = " << count_not_same << std::endl;
    std::terminate();
  }

  auto get_0th_element = [] (auto x) { return x[((void) Exts, 0)...]; };
  const auto buf_0s_after = get_0th_element(buf.get_mdspan());
  std::cerr << "buf_0s_after = " << static_cast<unsigned int>(buf_0s_after) << '\n';
}

BENCHMARK_CAPTURE(submdspan_run_benchmark, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

BENCHMARK_MAIN();
