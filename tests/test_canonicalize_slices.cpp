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
#include <mdspan/mdspan.hpp>
#include <type_traits>

#include <gtest/gtest.h>

#if ! defined(MDSPAN_ENABLE_P3663)
#  error "This file requires MDSPAN_ENABLE_P3663=ON"
#endif

namespace {

TEST(CanonicalizeSlices, Rank0) {
  {
    Kokkos::extents<int> exts{};
    auto canonical = Kokkos::submdspan_canonicalize_slices(exts);
    static_assert(std::is_same_v<decltype(canonical), std::tuple<>>);
  }
  {
    Kokkos::extents<size_t> exts{};
    auto canonical = Kokkos::submdspan_canonicalize_slices(exts);
    static_assert(std::is_same_v<decltype(canonical), std::tuple<>>);
  }
}

} // namespace (anonymous)
