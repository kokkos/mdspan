
#include <experimental/mdspan>

#include <iostream>
#include <iomanip>
#include <memory>

//================================================================================

template <
  class T,
  class ExtsA, class LayA, class AccA,
  class ExtsB, class LayB, class AccB
>
T dot_product(
  std::basic_mdspan<T, ExtsA, LayA, AccA> a,
  std::basic_mdspan<T, ExtsB, LayB, AccB> b
) requires ExtsA::rank() == ExtsB::rank() && ExtsA::rank() == 2
{
  T result = 0;
  for(int i = 0; i < a.extent(0); ++i) {
    for(int j = 0; j < a.extent(1); ++j) {
      result += a(i, j) * b(i, j);
    }
  }
  return result;
}

//================================================================================

template <
  class T,
  class ExtsA, class LayA, class AccA
>
void fill_in_order(
  std::basic_mdspan<T, ExtsA, LayA, AccA> a
) requires ExtsA::rank() == 2
{
  T count = 0;
  for(int i = 0; i < a.extent(0); ++i) {
    for(int j = 0; j < a.extent(1); ++j) {
      a(i, j) = count++;
    }
  }
}

//================================================================================

constexpr int rows = 3;
constexpr int cols = 3;

//================================================================================

int main() {
  {
    using span_2d_dynamic = std::basic_mdspan<int, std::extents<std::dynamic_extent, std::dynamic_extent>, std::layout_right>;
    using span_2d_dynamic_left = std::basic_mdspan<int, std::extents<std::dynamic_extent, std::dynamic_extent>, std::layout_left>;

    auto data_a = std::make_unique<int[]>(rows * cols);
    auto data_b = std::make_unique<int[]>(rows * cols);

    auto a = span_2d_dynamic(data_a.get(), rows, cols);
    auto b = span_2d_dynamic_left(data_b.get(), rows, cols);
    fill_in_order(a);
    fill_in_order(b);
    
    std::cout << dot_product(a, b) << std::endl;
  }

  {
    using span_2d_10_10 = std::basic_mdspan<int, std::extents<rows, cols>, std::layout_right>;
    using span_2d_10_10_left = std::basic_mdspan<int, std::extents<rows, cols>, std::layout_right>;

    auto data_a = std::make_unique<int[]>(100);
    auto data_b = std::make_unique<int[]>(100);

    auto a = span_2d_10_10(data_a.get());
    auto b = span_2d_10_10_left(data_b.get());
    fill_in_order(a);
    fill_in_order(b);
    
    std::cout << dot_product(a, b) << std::endl;
  }

}
