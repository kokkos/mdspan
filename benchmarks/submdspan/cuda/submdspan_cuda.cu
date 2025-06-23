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
// Using unsigned char makes overflow defined behavior.

#define CUDA_SAFE_CALL(call) \
  cuda_internal_safe_call(call, #call, __FILE__, __LINE__)

namespace submdspan_benchmark {

inline void
cuda_internal_safe_call(cudaError e, const char* name,
  const char* file, int line_number)
{
  if (cudaSuccess != e) {
    std::ostringstream out;
    out << name << " error( " << cudaGetErrorName(e)
        << "): " << cudaGetErrorString(e);
    if (file) {
      out << " " << file << ":" << line_number;
    }
    throw std::runtime_error(out.str());
  }
}

struct cuda_execution_space {};

template<class ValueType>
struct cuda_array_deleter {
  void operator() (ValueType* ptr) const {
    CUDA_SAFE_CALL(cudaFree(ptr));
  }
};

template<class ValueType>
struct array_deleter<cuda_execution_space, ValueType> {
  using type = cuda_array_deleter<ValueType>;
};

template<class ValueType>
std::unique_ptr<ValueType[], cuda_array_deleter<ValueType>>
allocate_buffer(cuda_execution_space, size_t num_elements) {
  ValueType* buf = nullptr;
  CUDA_SAFE_CALL(cudaMalloc(&buf, num_elements * sizeof(ValueType)));
  return std::unique_ptr<ValueType[], cuda_array_deleter<ValueType>>{buf, {}};
}

template <class IndexType, size_t... Exts>
void fill_with_random_values(
  cuda_execution_space,
  random_state_t& state,
  nonconst_test_mdspan<IndexType, Exts...> x_dev)
{
  benchmark_buffer buf_host{host_execution_space{}, x_dev.extents()};
  auto x_host = buf_host.get_mdspan();
  fill_with_random_values(host_execution_space{}, state, x_host);

  const size_t num_bytes = x_host.required_span_size() * sizeof(value_type);
  CUDA_SAFE_CALL(cudaMemcpy(
    x_dev.get(), x_host.get(), num_bytes, cudaMemcpyHostToDevice
  ));
}

// FIXME this should launch a device kernel
template<class IndexType, size_t... Exts>
size_t benchmark1_impl(cuda_execution_space /* exec_space */,
  benchmark::State& state,
  nonconst_test_mdspan<IndexType, Exts...> out)
{
  size_t count_not_same = 0;
  for (auto _ : state) {
    const auto p = std::pair{IndexType(0), IndexType(1)};
    auto out_sub = Kokkos::submdspan(out, ((void) Exts, p)...);
    if (out_sub[((void) Exts, 0)...] != out[((void) Exts, p.first)...]) {
      ++count_not_same;
    }
    out_sub[((void) Exts, 0)...] += static_cast<std::uint8_t>(1u);

    benchmark::DoNotOptimize(count_not_same);
  }
  return count_not_same;
}

} // namespace submdspan_benchmark

template<class IndexType, size_t... Exts>
void cuda_benchmark1(benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  return submdspan_benchmark::benchmark1(submdspan_benchmark::cuda_execution_space{}, state, exts);
}

BENCHMARK_CAPTURE(cuda_benchmark1, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(cuda_benchmark1, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(cuda_benchmark1, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(cuda_benchmark1, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

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

// FIXME this should launch a device kernel, perhaps
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
void cuda_benchmark2(benchmark::State& state,
  Kokkos::extents<IndexType, Exts...> exts)
{
  return submdspan_benchmark::benchmark2(submdspan_benchmark::cuda_execution_space{}, state, exts);
}

BENCHMARK_CAPTURE(cuda_benchmark2, int_6d, (Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(cuda_benchmark2, int_6d, (Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2}));
BENCHMARK_CAPTURE(cuda_benchmark2, size_t_6d, (Kokkos::extents<size_t, 2, 2, 2, 2, 2, 2>{}));
BENCHMARK_CAPTURE(cuda_benchmark2, size_t_6d, (Kokkos::dextents<size_t, 6>{2, 2, 2, 2, 2, 2}));

BENCHMARK_MAIN();




namespace test {

dim3 get_bench_thread_block(size_t y,size_t z) {
  cudaDeviceProp cudaProp;
  size_t dim_z = 1;
  while(dim_z*3<z && dim_z<32) dim_z*=2;
  CUDA_SAFE_CALL(cudaGetDeviceProperties(&cudaProp, 1));
  size_t dim_y = 16;
  while(dim_y*3<y && dim_y<32) dim_y*=2;

  return dim3(1, static_cast<int>(dim_y), static_cast<int>(dim_z));
}

template <class F, class... Args>
__global__
void do_run_kernel(F f, Args... args) {
  f(args...);
}

template <class F, class... Args>
float run_kernel_timed(size_t N, size_t M, size_t K, F&& f, Args&&... args) {
  cudaEvent_t start, stop;
  CUDA_SAFE_CALL(cudaEventCreate(&start));
  CUDA_SAFE_CALL(cudaEventCreate(&stop));

  CUDA_SAFE_CALL(cudaEventRecord(start));
  do_run_kernel<<<N, get_bench_thread_block(M,K)>>>(
    (F&&)f, ((Args&&) args)...
  );
  CUDA_SAFE_CALL(cudaEventRecord(stop));
  CUDA_SAFE_CALL(cudaEventSynchronize(stop));
  float milliseconds = 0;
  CUDA_SAFE_CALL(cudaEventElapsedTime(&milliseconds, start, stop));
  return milliseconds;
}

//================================================================================

template <class MDSpan, class... DynSizes>
void BM_MDSpan_Cuda_Stencil_3D(benchmark::State& state, MDSpan, DynSizes... dyn) {

  using value_type = typename MDSpan::value_type;
  auto s = fill_device_mdspan(MDSpan{}, dyn...);
  auto o = fill_device_mdspan(MDSpan{}, dyn...);

  idx_t d = static_cast<idx_t>(global_delta);
  int repeats = global_repeat==0? (s.extent(0)*s.extent(1)*s.extent(2) > (100*100*100) ? 50 : 1000) : global_repeat;

  auto lambda =
      [=] __device__ {
        for(int r = 0; r < repeats; ++r) {
          for(idx_t i = blockIdx.x+d; i < static_cast<idx_t>(s.extent(0))-d; i += gridDim.x) {
            for(idx_t j = threadIdx.z+d; j < static_cast<idx_t>(s.extent(1))-d; j += blockDim.z) {
              for(idx_t k = threadIdx.y+d; k < static_cast<idx_t>(s.extent(2))-d; k += blockDim.y) {
                for(int q=0; q<128; q++) {
                value_type sum_local = o(i,j,k);
                for(idx_t di = i-d; di < i+d+1; di++) {
                for(idx_t dj = j-d; dj < j+d+1; dj++) {
                for(idx_t dk = k-d; dk < k+d+1; dk++) {
                  sum_local += s(di, dj, dk);
                }}}
                o(i,j,k) = sum_local;
                }
              }
            }
          }
        }
      };
  run_kernel_timed(s.extent(0),s.extent(1),s.extent(2),lambda);

  for (auto _ : state) {
    auto timed = run_kernel_timed(s.extent(0),s.extent(1),s.extent(2),lambda);
    // units of cuda timer is milliseconds, units of iteration timer is seconds
    state.SetIterationTime(timed * 1e-3);
  }
  size_t num_inner_elements = (s.extent(0)-d) * (s.extent(1)-d) * (s.extent(2)-d);
  size_t stencil_num = (2*d+1) * (2*d+1) * (2*d+1);
  state.SetBytesProcessed( num_inner_elements * stencil_num * sizeof(value_type) * state.iterations() * repeats);
  state.counters["repeats"] = repeats;

  CUDA_SAFE_CALL(cudaDeviceSynchronize());
  CUDA_SAFE_CALL(cudaFree(s.data_handle()));
}
MDSPAN_BENCHMARK_ALL_3D_MANUAL(BM_MDSpan_Cuda_Stencil_3D, right_, rmdspan, 80, 80, 80);
//MDSPAN_BENCHMARK_ALL_3D_MANUAL(BM_MDSpan_Cuda_Stencil_3D, left_, lmdspan, 80, 80, 80);
//MDSPAN_BENCHMARK_ALL_3D_MANUAL(BM_MDSpan_Cuda_Stencil_3D, right_, rmdspan, 400, 400, 400);
//MDSPAN_BENCHMARK_ALL_3D_MANUAL(BM_MDSpan_Cuda_Stencil_3D, left_, lmdspan, 400, 400, 400);

//================================================================================

template <class T, class SizeX, class SizeY, class SizeZ>
void BM_Raw_Cuda_Stencil_3D_right(benchmark::State& state, T, SizeX x_, SizeY y_, SizeZ z_) {

  idx_t d = static_cast<idx_t>(global_delta);
  idx_t x = static_cast<idx_t>(x_);
  idx_t y = static_cast<idx_t>(y_);
  idx_t z = static_cast<idx_t>(z_);

  using value_type = T;
  value_type* data = nullptr;
  value_type* data_o = nullptr;
  {
    // just for setup...
    auto wrapped = Kokkos::mdspan<T, Kokkos::dextents<int, 1>>{};
    auto s = fill_device_mdspan(wrapped, x*y*z);
    data = s.data_handle();
    auto o = fill_device_mdspan(wrapped, x*y*z);
    data_o = o.data_handle();
  }

  int repeats = global_repeat==0? (x*y*z > (100*100*100) ? 50 : 1000) : global_repeat;

  auto lambda =
      [=] __device__ {
        for(int r = 0; r < repeats; ++r) {
          for(idx_t i = blockIdx.x+d; i < x-d; i += gridDim.x) {
            for(idx_t j = threadIdx.z+d; j < y-d; j += blockDim.z) {
              for(idx_t k = threadIdx.y+d; k < z-d; k += blockDim.y) {
                for(int q=0; q<128; q++) {
                value_type sum_local = data_o[k + j*z + i*z*y];
                for(idx_t di = i-d; di < i+d+1; di++) {
                for(idx_t dj = j-d; dj < j+d+1; dj++) {
                for(idx_t dk = k-d; dk < k+d+1; dk++) {
                  sum_local += data[dk + dj*z + di*z*y];
                }}}
                data_o[k + j*z + i*z*y] = sum_local;
                }
              }
            }
          }
        }
      };
  run_kernel_timed(x,y,z,lambda);

  for (auto _ : state) {
    auto timed = run_kernel_timed(x,y,z,lambda);
    // units of cuda timer is milliseconds, units of iteration timer is seconds
    state.SetIterationTime(timed * 1e-3);
  }
  size_t num_inner_elements = (x-d) * (y-d) * (z-d);
  size_t stencil_num = (2*d+1) * (2*d+1) * (2*d+1);
  state.SetBytesProcessed( num_inner_elements * stencil_num * sizeof(value_type) * state.iterations() * repeats);
  state.counters["repeats"] = repeats;

  CUDA_SAFE_CALL(cudaDeviceSynchronize());
  CUDA_SAFE_CALL(cudaFree(data));
}
BENCHMARK_CAPTURE(BM_Raw_Cuda_Stencil_3D_right, size_80_80_80, int(), 80, 80, 80);
BENCHMARK_CAPTURE(BM_Raw_Cuda_Stencil_3D_right, size_400_400_400, int(), 400, 400, 400);

//================================================================================

template <class T, class SizeX, class SizeY, class SizeZ>
void BM_Raw_Cuda_Stencil_3D_left(benchmark::State& state, T, SizeX x_, SizeY y_, SizeZ z_) {

  idx_t d = static_cast<idx_t>(global_delta);
  idx_t x = static_cast<idx_t>(x_);
  idx_t y = static_cast<idx_t>(y_);
  idx_t z = static_cast<idx_t>(z_);

  using value_type = T;
  value_type* data = nullptr;
  value_type* data_o = nullptr;
  {
    // just for setup...
    auto wrapped = Kokkos::mdspan<T, Kokkos::dextents<int,1>>{};
    auto s = fill_device_mdspan(wrapped, x*y*z);
    data = s.data_handle();
    auto o = fill_device_mdspan(wrapped, x*y*z);
    data_o = o.data_handle();
  }

  int repeats = global_repeat==0? (x*y*z > (100*100*100) ? 50 : 1000) : global_repeat;
  auto lambda =
    [=] __device__ {
      for(int r = 0; r < repeats; ++r) {
        for(idx_t i = blockIdx.x+d; i < x-d; i += gridDim.x) {
          for(idx_t j = threadIdx.z+d; j < y-d; j += blockDim.z) {
            for(idx_t k = threadIdx.y+d; k < z-d; k += blockDim.y) {
                for(int q=0; q<128; q++) {
                value_type sum_local = data_o[k*x*y + j*x + i];
                for(idx_t di = i-d; di < i+d+1; di++) {
                for(idx_t dj = j-d; dj < j+d+1; dj++) {
                for(idx_t dk = k-d; dk < k+d+1; dk++) {
                  sum_local += data[dk*x*y + dj*x + di];
                }}}
                data_o[k*x*y + j*x + i] = sum_local;
                }
            }
          }
        }
      }
    };

  run_kernel_timed(x,y,z,lambda);

  for (auto _ : state) {
    auto timed = run_kernel_timed(x,y,z,lambda);
    // units of cuda timer is milliseconds, units of iteration timer is seconds
    state.SetIterationTime(timed * 1e-3);
  }
  size_t num_inner_elements = (x-d) * (y-d) * (z-d);
  size_t stencil_num = (2*d+1) * (2*d+1) * (2*d+1);
  state.SetBytesProcessed( num_inner_elements * stencil_num * sizeof(value_type) * state.iterations() * repeats);
  state.counters["repeats"] = repeats;

  CUDA_SAFE_CALL(cudaDeviceSynchronize());
  CUDA_SAFE_CALL(cudaFree(data));
}
BENCHMARK_CAPTURE(BM_Raw_Cuda_Stencil_3D_left, size_80_80_80, int(), 80, 80, 80);
//BENCHMARK_CAPTURE(BM_Raw_Cuda_Stencil_3D_left, size_400_400_400, int(), 400, 400, 400);
