
#include <experimental/mdspan>

#include <memory>
#include <random>

#include "sum_3d_common.hpp"
#include "fill.hpp"

//================================================================================

template <class T, ptrdiff_t... Es>
using lmdspan = std::basic_mdspan<T, std::extents<Es...>, std::layout_left>;

//================================================================================

template <class MDSpan, class... DynSizes>
void BM_MDSpan_Sum_Subspan_3D_right(benchmark::State& state, MDSpan, DynSizes... dyn) {
  using value_type = typename MDSpan::value_type;
  auto buffer = std::make_unique<value_type[]>(
    MDSpan{nullptr, dyn...}.mapping().required_span_size()
  );
  auto s = MDSpan{buffer.get(), dyn...};
  mdspan_benchmark::fill_random(s);
  for (auto _ : state) {
    value_type sum = 0;
    for(ptrdiff_t i = 0; i < s.extent(0); ++i) {
      auto sub_i = std::subspan(s, i, std::all, std::all);
      for (ptrdiff_t j = 0; j < s.extent(1); ++j) {
        auto sub_i_j = std::subspan(sub_i, j, std::all);
        for (ptrdiff_t k = 0; k < s.extent(2); ++k) {
          sum += sub_i_j(k);
        }
      }
    }
    benchmark::DoNotOptimize(sum);
    benchmark::DoNotOptimize(s.data());
  }
  state.SetBytesProcessed(s.size() * sizeof(value_type) * state.iterations());
}
MDSPAN_BENCHMARK_ALL_3D(BM_MDSpan_Sum_Subspan_3D_right, right_, std::mdspan, 20, 20, 20);
MDSPAN_BENCHMARK_ALL_3D(BM_MDSpan_Sum_Subspan_3D_right, left_, lmdspan, 20, 20, 20);
MDSPAN_BENCHMARK_ALL_3D(BM_MDSpan_Sum_Subspan_3D_right, right_, std::mdspan, 200, 200, 200);
MDSPAN_BENCHMARK_ALL_3D(BM_MDSpan_Sum_Subspan_3D_right, left_, lmdspan, 200, 200, 200);

//================================================================================

BENCHMARK_CAPTURE(
  BM_Raw_Sum_3D_right, size_20_20_20, int(), 20, 20, 20
);
BENCHMARK_CAPTURE(
  BM_Raw_Sum_3D_right, size_200_200_200, int(), 200, 200, 200
);

BENCHMARK_CAPTURE(
  BM_Raw_Static_Sum_3D_right, size_20_20_20, int(),
  std::integral_constant<ptrdiff_t, 20>{},
  std::integral_constant<ptrdiff_t, 20>{},
  std::integral_constant<ptrdiff_t, 20>{}
);
BENCHMARK_CAPTURE(
  BM_Raw_Static_Sum_3D_right, size_200_200_200, int(),
  std::integral_constant<ptrdiff_t, 200>{},
  std::integral_constant<ptrdiff_t, 200>{},
  std::integral_constant<ptrdiff_t, 200>{}
);
BENCHMARK_CAPTURE(
  BM_Raw_Sum_3D_right_iter_left, size_20_20_20, int(), 20, 20, 20
);
BENCHMARK_CAPTURE(
  BM_Raw_Sum_3D_right_iter_left, size_200_200_200, int(), 200, 200, 200
);
BENCHMARK_CAPTURE(
  BM_Raw_Static_Sum_3D_right_iter_left, size_20_20_20, int(),
  std::integral_constant<ptrdiff_t, 20>{},
  std::integral_constant<ptrdiff_t, 20>{},
  std::integral_constant<ptrdiff_t, 20>{}
);
BENCHMARK_CAPTURE(
  BM_Raw_Static_Sum_3D_right_iter_left, size_200_200_200, int(),
  std::integral_constant<ptrdiff_t, 200>{},
  std::integral_constant<ptrdiff_t, 200>{},
  std::integral_constant<ptrdiff_t, 200>{}
);

//================================================================================

namespace _impl {

template <class, class T>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr decltype(auto) _repeated_with(T&& v) noexcept { return std::forward<T>(v); }

template <class T, class LP, class AP>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr void _do_sum_subspan(
  T& sum,
  std::basic_mdspan<T, std::extents<>, LP, AP> s
)
{
  sum += s();
}

template <class T, ptrdiff_t E, ptrdiff_t... Es, class LP, class AP>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr void _do_sum_subspan(
  T& sum,
  std::basic_mdspan<T, std::extents<E, Es...>, LP, AP> s
)
{
  for(ptrdiff_t i = 0; i < s.extent(0); ++i) {
    _impl::_do_sum_subspan(sum, std::subspan(
      s, i, _repeated_with<decltype(Es)>(std::all)...)
    );
  }
}

} // end namespace _impl

template <class MDSpan, class... DynSizes>
void BM_MDSpan_Sum_Subspan_MD_right(benchmark::State& state, MDSpan, DynSizes... dyn) {
  using value_type = typename MDSpan::value_type;
  auto buffer = std::make_unique<value_type[]>(
    MDSpan{nullptr, dyn...}.mapping().required_span_size()
  );
  auto s = MDSpan{buffer.get(), dyn...};
  mdspan_benchmark::fill_random(s);
  for (auto _ : state) {
    value_type sum = 0;
    _impl::_do_sum_subspan(sum, s);
    benchmark::DoNotOptimize(sum);
    benchmark::DoNotOptimize(s.data());
  }
  state.SetBytesProcessed(s.size() * sizeof(value_type) * state.iterations());
}

BENCHMARK_CAPTURE(
  BM_MDSpan_Sum_Subspan_MD_right, fixed_10D_size_1024,
  std::mdspan<int, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2>{}
);
BENCHMARK_CAPTURE(
  BM_MDSpan_Sum_Subspan_MD_right, dyn_10D_size_1024,
  std::mdspan<int,
    std::dynamic_extent, std::dynamic_extent, std::dynamic_extent, std::dynamic_extent, std::dynamic_extent,
    std::dynamic_extent, std::dynamic_extent, std::dynamic_extent, std::dynamic_extent, std::dynamic_extent
  >{},
  2, 2, 2, 2, 2,
  2, 2, 2, 2, 2
);
BENCHMARK_CAPTURE(
  BM_MDSpan_Sum_Subspan_MD_right, fixed5_dyn5_10D_alternate_size_1024,
  std::mdspan<int, 2, std::dynamic_extent, 2, std::dynamic_extent, 2, std::dynamic_extent, 2, std::dynamic_extent, 2, std::dynamic_extent>{},
  2, 2, 2, 2, 2
);
BENCHMARK_CAPTURE(
  BM_MDSpan_Sum_Subspan_MD_right, fixed8_dyn2_10D_alternate_size_1024,
  std::mdspan<int, 2, 2, 2, 2, std::dynamic_extent, 2, 2, 2, 2, std::dynamic_extent>{},
  2, 2
);
BENCHMARK_CAPTURE(
  BM_MDSpan_Sum_Subspan_MD_right, fixed_5D_size_1024,
  std::mdspan<int, 4, 4, 4, 4, 4>{}
);
BENCHMARK_CAPTURE(
  BM_MDSpan_Sum_Subspan_MD_right, dyn_5D_size_1024,
  std::mdspan<int,
    std::dynamic_extent, std::dynamic_extent, std::dynamic_extent, std::dynamic_extent, std::dynamic_extent
  >{},
  4, 4, 4, 4, 4
);
BENCHMARK_CAPTURE(
  BM_Raw_Sum_1D, size_1024, int(), 1024
);

//================================================================================

BENCHMARK_MAIN();
