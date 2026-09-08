
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include <mdspan/mdspan.hpp>

#include <gtest/gtest.h>


TEST(TestMdspanConversionConst, test_mdspan_conversion_const) {
  std::array<double, 6> a{};
  Kokkos::mdspan<double, Kokkos::extents<uint32_t, 2, 3>> s(a.data());
  ASSERT_EQ(s.data_handle(), a.data());
  MDSPAN_IMPL_OP(s, 0, 1) = 3.14;
  Kokkos::mdspan<double const, Kokkos::extents<uint64_t, 2, 3>> c_s(s);
  ASSERT_EQ((MDSPAN_IMPL_OP(c_s, 0, 1)), 3.14);
}
