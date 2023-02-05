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
#include <experimental/mdspan>

#include <benchmark/benchmark.h>

#include "fill.hpp"

using index_type = int;

namespace stdex = std::experimental;
_MDSPAN_INLINE_VARIABLE constexpr auto dyn = stdex::dynamic_extent;

template <class Extents, class ... Args>
void extents_construction(benchmark::State& state, Extents, int R, Args ... args) {
  for (auto _ : state) {
    double val =0;
    for(int r=0; r<R; r++) {
       Extents ext(args...);
       val += ext.extent(0);
    }
    if(val<1.0*R*10) std::terminate();
  }
}

BENCHMARK_CAPTURE(
  extents_construction, int_int_int, stdex::dextents<int,3>(), 100000000, 100, 100, 100
);

BENCHMARK_CAPTURE(
  extents_construction, array_int_3, stdex::dextents<int,3>(), 100000000, std::array<int,3>{100, 100, 100}
);

BENCHMARK_MAIN();
