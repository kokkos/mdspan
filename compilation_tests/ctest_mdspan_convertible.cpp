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
#include "ctest_common.hpp"

#include <experimental/mdspan>

#include <type_traits>

namespace stdex = std::experimental;

//==============================================================================
// <editor-fold desc="mdspan"> {{{1

MDSPAN_STATIC_TEST(
  std::is_convertible<
    stdex::mdspan<double, stdex::dextents<size_t,1>>,
    stdex::mdspan<double const, stdex::dextents<size_t,1>>
  >::value
);

MDSPAN_STATIC_TEST(
  !std::is_convertible<
    stdex::mdspan<double const, stdex::dextents<size_t,1>>,
    stdex::mdspan<double, stdex::dextents<size_t,1>>
  >::value
);

// </editor-fold> end mdspan }}}1
//==============================================================================

