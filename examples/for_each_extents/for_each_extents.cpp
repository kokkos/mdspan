#include <mdspan/mdspan.hpp>
#include <cassert>
#include <iostream>
#include <type_traits>

// "gcc trunk" on godbolt.org as of 2023/03/21
// (> 12.2) does not define __cpp_lib_ranges_iota,
// yet std::views::iota works just fine.
//
// "icpx C++23" github.com/kokkos/mdspan test build
// has a broken <ranges> header as of 2024/04/02.
#if defined(__cpp_lib_ranges_cartesian_product) && (! defined(__INTEL_LLVM_COMPILER)) // && defined(__cpp_lib_ranges_iota)
#  define MDSPAN_EXAMPLE_CAN_USE_STD_RANGES 1
#endif

#if defined(MDSPAN_EXAMPLE_CAN_USE_STD_RANGES)

// GCC >= 13 ("gcc trunk" on godbolt.org as of 2023/03/21)
// implements std::views::cartesian_product.
// If you don't have it, you can use range-v3 instead.
// Note that mixing std::views::iota with
// ranges::views::cartesian_product doesn't work.
// The range-v3 work-around looks like this.
//
// #include <range/v3/view/cartesian_product.hpp>
// #include <range/v3/view/indices.hpp>
// namespace ranges_views = ranges::views;

#include <ranges>
namespace ranges_views = std::views;

auto print_args = [] <class ... Args> (Args&&... args) {
  ((std::cout << std::forward<Args>(args) << '\n'), ...);
};

template <std::size_t... Is>
auto reverse(std::index_sequence<Is...>) ->
  std::index_sequence<sizeof...(Is) - 1 - Is...>;

template <std::size_t N>
using reverse_index_sequence_t =
  decltype(reverse(std::make_index_sequence<N>()));

template<class Callable, class IndexType,
  std::size_t ... Extents, std::size_t ... RankIndices>
void for_each_in_extents_impl(Callable&& f,
  Kokkos::extents<IndexType, Extents...> e,
  std::index_sequence<RankIndices...> rank_sequence)
{
  // In the layout_left case, caller passes in N-1, N-2, ..., 1, 0.
  // This reverses the order of the Cartesian product,
  // but also reverses the order of indices in each tuple.
  [&] <std::size_t ... Indices> (std::index_sequence<Indices...>) {
    auto v = std::views::cartesian_product(
      std::views::iota(IndexType(0), e.extent(Indices))...);
    for (const auto& tuple_of_indices : v) {
      // In the layout_left case, we undo the reversal of each tuple
      // by getting its elements in reverse order.
      [&] <std::size_t ... InnerIndices> (std::index_sequence<InnerIndices...>) {
          std::forward<Callable>(f)(std::get<InnerIndices>(tuple_of_indices)...);
        } (rank_sequence);
    }
  } (rank_sequence);
}

template<class Callable, class IndexType, std::size_t ... Extents, class Layout>
void for_each_in_extents(Callable&& f,
  Kokkos::extents<IndexType, Extents...> e,
  Layout)
{
  using layout_type = std::remove_cvref_t<Layout>;
  if constexpr (std::is_same_v<layout_type, Kokkos::layout_left>) {
    for_each_in_extents_impl(std::forward<Callable>(f), e,
      reverse_index_sequence_t<e.rank()>{});
  }
  else { // layout_right or any other layout
    for_each_in_extents_impl(std::forward<Callable>(f), e,
      reverse_index_sequence_t<e.rank()>{});
  }
}

#endif // defined(MDSPAN_EXAMPLE_CAN_USE_STD_RANGES)

int main() {

#if defined(MDSPAN_EXAMPLE_CAN_USE_STD_RANGES)
  Kokkos::extents<int, 2, 3> e;
  auto printer = [] (int i, int j) {
    std::cout << "(" << i << "," << j << ")\n";
  };
  std::cout << "layout_right:\n";
  for_each_in_extents(printer, e, Kokkos::layout_right{});
  std::cout << "\nlayout_left:\n";
  for_each_in_extents(printer, e, Kokkos::layout_left{});
#endif // defined(MDSPAN_EXAMPLE_CAN_USE_STD_RANGES)

  return 0;
}
