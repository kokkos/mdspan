/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

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
) //requires ExtsA::rank() == ExtsB::rank() && ExtsA::rank() == 2
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
) // requires ExtsA::rank() == 2
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
