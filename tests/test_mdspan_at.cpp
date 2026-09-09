// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include <array>
#include <mdspan/mdspan.hpp>

#include <gtest/gtest.h>


TEST(TestMdspanAt, test_mdspan_at) {
    std::array<double, 6> a{};
    Kokkos::mdspan<double, Kokkos::extents<size_t, 2, 3>> s(a.data());

    s.at(0, 0) = 3.14;
    s.at(std::array<int, 2>{1, 2}) = 2.72;
    ASSERT_EQ(s.at(0, 0), 3.14);
    ASSERT_EQ(s.at(std::array<int, 2>{1, 2}), 2.72);

    EXPECT_THROW(s.at(2, 3), std::out_of_range);
    EXPECT_THROW(s.at(std::array<int, 2>{3, 1}), std::out_of_range);
}
