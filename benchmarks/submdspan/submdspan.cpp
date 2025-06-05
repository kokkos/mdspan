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
// so we can use char to minimize storage.

template<class IndexType, size_t... Exts>
using nonconst_test_mdspan = Kokkos::mdspan<char, Kokkos::extents<IndexType, Exts...>>;

template<class IndexType, size_t... Exts>
using const_test_mdspan = Kokkos::mdspan<const char, Kokkos::extents<IndexType, Exts...>>;

template<class IndexType, size_t... Exts>
size_t submdspan_benchmark(benchmark::State& state, const_test_mdspan<IndexType, Exts...> x) {
  size_t count_not_same = 0;
  for (auto _ : state) {
    const auto p = std::pair{IndexType(0), IndexType(1)};  
    auto x_sub = Kokkos::submdspan(x, ((void) Exts, p)...);
    if (x_sub[((void) Exts, 0)...] != x[((void) Exts, p.first)...]) {
      ++count_not_same;
    }
    benchmark::DoNotOptimize(count_not_same);
  }
  return count_not_same;
}

template<class IndexType, size_t... Exts>
class benchmark_buffer {
public:
  benchmark_buffer(Kokkos::extents<IndexType, Exts...> exts) :
    mapping_{exts},
    buffer_{std::make_unique<char[]>(mapping_.required_span_size())}
  {}

  nonconst_test_mdspan<IndexType, Exts...> get_mdspan() {
    return {buffer_.get(), mapping_};
  }

  const_test_mdspan<IndexType, Exts...> get_mdspan() const {
    return {static_cast<const char*>(buffer_.get()), mapping_};
  }

private:
  Kokkos::layout_right::template mapping<Kokkos::extents<IndexType, Exts...>> mapping_;
  std::unique_ptr<char[]> buffer_;
};

template<class IndexType, size_t... Exts>
void submdspan_run_benchmark(benchmark::State& state, Kokkos::extents<IndexType, Exts...> exts) {
  auto buffer = benchmark_buffer{exts};
  mdspan_benchmark::fill_random(buffer.get_mdspan());
  size_t count_not_same = submdspan_benchmark(state, std::as_const(buffer).get_mdspan());
  if (count_not_same != 0) {
    std::cerr << "submdspan_benchmark failed: count not same = " << count_not_same << std::endl;
  }
}

BENCHMARK_CAPTURE(submdspan_run_benchmark, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(submdspan_run_benchmark, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

BENCHMARK_MAIN();
