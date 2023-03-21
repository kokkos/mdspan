#include <experimental/mdspan>
#include <cassert>
#include <iostream>
#include <type_traits>

// "gcc trunk" on godbolt.org as of 2023/03/21
// (> 12.2) does not define __cpp_lib_ranges_iota,
// yet std::views::iota works just fine.
#if defined(__cpp_lib_ranges_cartesian_product) // && defined(__cpp_lib_ranges_iota)
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

namespace stdex = std::experimental;

auto print_args = [] <class ... Args> (Args&&... args) {
  ((std::cout << std::forward<Args>(args) << '\n'), ...);
};

template<size_t ... Lefts, size_t ... Rights>
auto concat_index_sequence(std::index_sequence<Lefts...>,
  std::index_sequence<Rights...>)
{
  return std::index_sequence<Lefts..., Rights...>{};
}

auto reverse_index_sequence(std::index_sequence<> x)
{
  return x;  
}

template<size_t First, size_t ... Rest>
auto reverse_index_sequence(std::index_sequence<First, Rest...>)
{
  return concat_index_sequence(
    reverse_index_sequence(std::index_sequence<Rest...>{}),
    std::index_sequence<First>{});
}

template<size_t N>
auto make_reverse_index_sequence()
{
  return reverse_index_sequence(std::make_index_sequence<N>());
}

template<class Callable, class IndexType,
  std::size_t ... Extents, std::size_t ... RankIndices>
void for_each_in_extents_impl(Callable&& f,
  stdex::extents<IndexType, Extents...> e,
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
  stdex::extents<IndexType, Extents...> e,
  Layout)
{
  using layout_type = std::remove_cvref_t<Layout>;
  if constexpr (std::is_same_v<layout_type, stdex::layout_left>) {
    for_each_in_extents_impl(std::forward<Callable>(f), e,
      make_reverse_index_sequence<e.rank()>());
  }
  else { // layout_right or any other layout
    for_each_in_extents_impl(std::forward<Callable>(f), e,
      std::make_index_sequence<e.rank()>());
  }
}

#endif // defined(MDSPAN_EXAMPLE_CAN_USE_STD_RANGES)

int main() {

#if defined(MDSPAN_EXAMPLE_CAN_USE_STD_RANGES)
  stdex::extents<int, 2, 3> e;
  auto printer = [] (int i, int j) {
    std::cout << "(" << i << "," << j << ")\n";
  };
  std::cout << "layout_right:\n";
  for_each_in_extents(printer, e, stdex::layout_right{});
  std::cout << "\nlayout_left:\n";
  for_each_in_extents(printer, e, stdex::layout_left{});
#endif // defined(MDSPAN_EXAMPLE_CAN_USE_STD_RANGES)

  return 0;
}
