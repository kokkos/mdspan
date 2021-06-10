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

#include <iostream>
#include <experimental/mdspan>

#include <iomanip>
#include <memory>
#include <cassert>

namespace stdex = std::experimental;

//================================================================================

MDSPAN_INLINE_FUNCTION
void test() {
  {
    // static sized
    double buffer[2 * 3 * 4] = {};
    auto s1 = stdex::mdspan<double, stdex::extents<2, 3, 4>>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = stdex::submdspan(s1, 1, 1, stdex::full_extent);
    std::cout << std::boolalpha << (sub1[1] == 42) << std::endl;
  }

  {
    // static sized
    double buffer[2 * 3 * 4] = {};
    auto s1 = stdex::mdspan<double, stdex::extents<2, 3, 4>, stdex::layout_left>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = stdex::submdspan(s1, 1, stdex::full_extent, stdex::full_extent);
    auto sub2 = stdex::submdspan(sub1, 1, stdex::full_extent);
    std::cout << std::boolalpha << (sub2[1] == 42) << std::endl;
  }

  {
    // static sized, all submdspans
    double buffer[2 * 3 * 4] = {};
    auto s1 = stdex::mdspan<double, stdex::extents<2, 3, 4>>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = stdex::submdspan(s1, 1, stdex::full_extent, stdex::full_extent);
    auto sub2 = stdex::submdspan(sub1, 1, stdex::full_extent);
    auto sub3 = stdex::submdspan(sub2, 1);
    std::cout << std::boolalpha << (sub3() == 42) << std::endl;
  }

  {
    // static sized, all submdspans
    double buffer[2 * 3 * 4] = {};
    auto s1 = stdex::mdspan<double, stdex::extents<2, 3, 4>, stdex::layout_left>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = stdex::submdspan(s1, 1, stdex::full_extent, stdex::full_extent);
    auto sub2 = stdex::submdspan(sub1, 1, stdex::full_extent);
    auto sub3 = stdex::submdspan(sub2, 1);
    std::cout << std::boolalpha << (sub3() == 42) << std::endl;
  }
}

#ifdef __NVCC__
__global__ void force_compile_test() { test(); }
#endif

int main() {
  test();
}
