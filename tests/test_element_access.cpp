// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include <mdspan/mdspan.hpp>

#include <gtest/gtest.h>


TEST(TestElementAccess, element_access_with_std_array) {
    std::array<double, 6> a{};
    Kokkos::mdspan<double, Kokkos::extents<size_t,2, 3>> s(a.data());
    ASSERT_EQ(MDSPAN_IMPL_OP(s, (std::array<int, 2>{1, 2})), 0);
    MDSPAN_IMPL_OP(s, (std::array<int, 2>{0, 1})) = 3.14;
    ASSERT_EQ(MDSPAN_IMPL_OP(s, (std::array<int, 2>{0, 1})), 3.14);
}
