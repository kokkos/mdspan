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

#include <iostream>
#include <iomanip>
#include <memory>

namespace stdex = std::experimental;

#if !(defined(__cpp_lib_make_unique) && __cpp_lib_make_unique >= 201304) && !MDSPAN_HAS_CXX_14
// Not actually conforming, but it works for the purposes of this file
namespace std {
template <class T>
struct __unique_ptr_new_impl {
  template <class... Args>
  static T* __impl(Args&&... args) {
    return new T((Args&&)args...);
  }
};
template <class T>
struct __unique_ptr_new_impl<T[]> {
  static T* __impl(size_t size) {
    return new T[size];
  }
};
template <class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(__unique_ptr_new_impl<T>::__impl((Args&&)args...));
}
} // end namespace std
#endif

//================================================================================

template <
  class T,
  class ExtsA, class LayA, class AccA,
  class ExtsB, class LayB, class AccB
>
T dot_product(
  stdex::mdspan<T, ExtsA, LayA, AccA> a,
  stdex::mdspan<T, ExtsB, LayB, AccB> b
) //requires ExtsA::rank() == ExtsB::rank() && ExtsA::rank() == 2
{
  T result = 0;
  for(int i = 0; i < a.extent(0); ++i) {
    for(int j = 0; j < a.extent(1); ++j) {
#if MDSPAN_USE_BRACKET_OPERATOR
      result += a[i, j] * b[i, j];
#else
      result += a(i, j) * b(i, j);
#endif
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
  stdex::mdspan<T, ExtsA, LayA, AccA> a
) // requires ExtsA::rank() == 2
{
  T count = 0;
  for(int i = 0; i < a.extent(0); ++i) {
    for(int j = 0; j < a.extent(1); ++j) {
#if MDSPAN_USE_BRACKET_OPERATOR
      a[i, j] = count++;
#else
      a(i, j) = count++;
#endif
    }
  }
}

//================================================================================

constexpr int rows = 3;
constexpr int cols = 3;

//================================================================================

int main() {
  {
    using span_2d_dynamic = stdex::mdspan<int, stdex::dextents<size_t, 2>, stdex::layout_right>;
    using span_2d_dynamic_left = stdex::mdspan<int, stdex::dextents<size_t, 2>, stdex::layout_left>;

    auto data_a = std::make_unique<int[]>(rows * cols);
    auto data_b = std::make_unique<int[]>(rows * cols);

    auto a = span_2d_dynamic(data_a.get(), rows, cols);
    auto b = span_2d_dynamic_left(data_b.get(), rows, cols);
    fill_in_order(a);
    fill_in_order(b);

    std::cout << dot_product(a, b) << std::endl;
  }

  {
    using span_2d_10_10 = stdex::mdspan<int, stdex::extents<size_t, rows, cols>, stdex::layout_right>;
    using span_2d_10_10_left = stdex::mdspan<int, stdex::extents<size_t, rows, cols>, stdex::layout_right>;

    auto data_a = std::make_unique<int[]>(100);
    auto data_b = std::make_unique<int[]>(100);

    auto a = span_2d_10_10(data_a.get());
    auto b = span_2d_10_10_left(data_b.get());
    fill_in_order(a);
    fill_in_order(b);

    std::cout << dot_product(a, b) << std::endl;
  }

}
