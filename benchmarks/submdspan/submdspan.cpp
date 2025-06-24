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

#include "submdspan_generic.hpp"

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
// An unsigned integer type makes overflow defined behavior.

namespace submdspan_benchmark {

template<class IndexType, size_t... Exts>
size_t benchmark1_impl(host_execution_space /* exec_space */,
  benchmark::State& state,
  nonconst_test_mdspan<IndexType, Exts...> out)
{
  size_t count_not_same = 0;
  for (auto _ : state) {
    const auto p = std::pair{IndexType(0), IndexType(1)};
    auto out_sub = Kokkos::submdspan(out, ((void) Exts, p)...);
    if (get_broadcast_element(out_sub, 0) != get_broadcast_element(out, p.first)) {
      ++count_not_same;
    }
    get_broadcast_element(out_sub, 0) += static_cast<std::uint8_t>(1u);

    benchmark::DoNotOptimize(count_not_same);
  }
  return count_not_same;
}

} // namespace submdspan_benchmark

template<class IndexType, size_t... Exts>
void host_benchmark1(benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  return submdspan_benchmark::benchmark1(submdspan_benchmark::host_execution_space{}, state, exts);
}

BENCHMARK_CAPTURE(host_benchmark1, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(host_benchmark1, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(host_benchmark1, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(host_benchmark1, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

namespace submdspan_benchmark {

// Multiply elements by 3, using 1-D slices.
template<class ExecutionSpace, class IndexType, size_t... Exts>
void benchmark2_loop(ExecutionSpace exec_space,
  nonconst_test_mdspan<IndexType, Exts...> out)
{
  using mdspan_type = nonconst_test_mdspan<IndexType, Exts...>;

  if constexpr (mdspan_type::rank() == 0) {
    return;
  }
  else if constexpr (mdspan_type::rank() == 1) {
    const IndexType ext0 = out.extent(0);
    for (IndexType k = 0; k < ext0; ++k) {
      out[k] *= 3u;
    }
  }
  else {
    const auto ext0 = index_holder{out.extent(0)};
    for (auto k = index_holder{IndexType(0)}; k < ext0; ++k) {
      benchmark2_loop(exec_space, slice_one_extent(out, k));
    }
  }
}

template<class IndexType, size_t... Exts>
size_t benchmark2_impl(host_execution_space exec_space,
  benchmark::State& state,
  nonconst_test_mdspan<IndexType, Exts...> out)
{
  size_t count = 0;
  for (auto _ : state) {
    benchmark2_loop(exec_space, out);
    ++count;
  }
  benchmark::DoNotOptimize(count);
  return count;
}

template<class IndexType, size_t... Exts>
void benchmark2(host_execution_space exec_space,
  benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  auto in_buf = benchmark_buffer{exec_space, exts};
  auto out_buf = benchmark_buffer{exec_space, exts};
  random_state_t random_state{};
  fill_with_random_values(exec_space, random_state, in_buf.get_mdspan());

  // We're using layout_right, so we don't need the layout mapping to iterate over the elements.
  const size_t num_elements = out_buf.size();
  {
    auto in = in_buf.get_mdspan().data_handle();
    auto out = out_buf.get_mdspan().data_handle();
    for (size_t i = 0; i < num_elements; ++i) {
      out[i] = in[i];
    }
  }
  const size_t count = benchmark2_impl(exec_space, state, out_buf.get_mdspan());
  {
    auto in = in_buf.get_mdspan().data_handle();
    auto out = out_buf.get_mdspan().data_handle();
    for (size_t i = 0; i < num_elements; ++i) {
      const auto original = in[i];
      const auto expected = expected_element(original, count);
      if (out[i] != expected) {
        std::cerr << "benchmark2 failed: out[" << i << "] = "
          << out[i] << " != " << expected << std::endl;
        std::terminate();
      }
    }
  }
}

} // namespace submdspan_benchmark

template<class IndexType, size_t... Exts>
void host_benchmark2(benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  return submdspan_benchmark::benchmark2(submdspan_benchmark::host_execution_space{}, state, exts);
}

BENCHMARK_CAPTURE(host_benchmark2, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(host_benchmark2, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(host_benchmark2, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(host_benchmark2, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

BENCHMARK_MAIN();
