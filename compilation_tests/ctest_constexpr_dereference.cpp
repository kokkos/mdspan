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

#include "ctest_common.hpp"

#include <experimental/mdspan>

namespace stdex = std::experimental;

// Only works with newer constexpr
#if defined(_MDSPAN_USE_CONSTEXPR_14) && _MDSPAN_USE_CONSTEXPR_14

//==============================================================================

constexpr int
simple_static_sum_test_1(int add_to_row) {
  int data[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  auto s = stdex::mdspan<int, 3, 3>(data);
  int result = 0;
  for(int col = 0; col < 3; ++col) {
    for(int row = 0; row < 3; ++row) {
      result += s(row, col) * (row + add_to_row);
    }
  }
  return result;
}

MDSPAN_STATIC_TEST(
  // 1 + 2 + 3 + 2*(4 + 5 + 6) + 3*(7 + 8 + 9) = 108
  simple_static_sum_test_1(1) == 108
);

MDSPAN_STATIC_TEST(
  // -1 - 2 - 3 + 7 + 8 + 9 = 18
  simple_static_sum_test_1(-1) == 18
);

MDSPAN_STATIC_TEST(
  // -1 - 2 - 3 + 7 + 8 + 9 = 18
  stdex::mdspan<double, simple_static_sum_test_1(-1)>{nullptr}.extent(0) == 18
);

//==============================================================================

constexpr int
simple_test_1d_constexpr_in_type() {
  int data[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18
  };
  auto s = stdex::mdspan<int, simple_static_sum_test_1(-1)>(data);
  // 4 + 14 + 18 + 1 = 37
  return s[3] + s[13] + s[17] + s[0];
}

MDSPAN_STATIC_TEST(
  simple_test_1d_constexpr_in_type() == 37
);

//==============================================================================

constexpr int
simple_dynamic_sum_test_2(int add_to_row) {
  int data[] = {
    1, 2, 3, 0,
    4, 5, 6, 0,
    7, 8, 9, 0
  };
  auto s = stdex::mdspan<int, stdex::dynamic_extent, stdex::dynamic_extent>(data, 3, 4);
  int result = 0;
  for(int col = 0; col < 3; ++col) {
    for(int row = 0; row < 3; ++row) {
      result += s(row, col) * (row + add_to_row);
    }
  }
  return result;
}

MDSPAN_STATIC_TEST(
  // 1 + 2 + 3 + 2*(4 + 5 + 6) + 3*(7 + 8 + 9) = 108
  simple_dynamic_sum_test_2(1) == 108
);

MDSPAN_STATIC_TEST(
  // -1 - 2 - 3 + 7 + 8 + 9 = 18
  simple_dynamic_sum_test_2(-1) == 18
);

//==============================================================================

constexpr int
simple_mixed_layout_left_sum_test_3(int add_to_row) {
  int data[] = {
    1, 4, 7,
    2, 5, 8,
    3, 6, 9,
    0, 0, 0
  };
  auto s = stdex::basic_mdspan<
    int, stdex::extents<stdex::dynamic_extent, stdex::dynamic_extent>,
    stdex::layout_left
  >(data, 3, 4);
  int result = 0;
  for(int col = 0; col < 3; ++col) {
    for(int row = 0; row < 3; ++row) {
      result += s(row, col) * (row + add_to_row);
    }
  }
  return result;
}

MDSPAN_STATIC_TEST(
  // 1 + 2 + 3 + 2*(4 + 5 + 6) + 3*(7 + 8 + 9) = 108
  simple_mixed_layout_left_sum_test_3(1) == 108
);

//==============================================================================

#endif //defined(_MDSPAN_USE_CONSTEXPR_14) && _MDSPAN_USE_CONSTEXPR_14