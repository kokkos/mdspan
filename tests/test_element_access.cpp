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

#include <mdspan.hpp>

#include <gtest/gtest.h>

namespace stdex = MDSPAN_IMPL_STANDARD_NAMESPACE;

TEST(TestElementAccess, element_access_with_std_array) {
    std::array<double, 6> a{};
    md::mdspan<double, md::extents<size_t,2, 3>> s(a.data());
    ASSERT_EQ(__MDSPAN_OP(s, (std::array<int, 2>{1, 2})), 0);
    __MDSPAN_OP(s, (std::array<int, 2>{0, 1})) = 3.14;
    ASSERT_EQ(__MDSPAN_OP(s, (std::array<int, 2>{0, 1})), 3.14);
}
