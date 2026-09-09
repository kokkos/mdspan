// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include "ctest_common.hpp"

#include <mdspan/mdspan.hpp>

#include <type_traits>


//==============================================================================
// <editor-fold desc="mdspan"> {{{1

MDSPAN_STATIC_TEST(
  std::is_convertible<
    Kokkos::mdspan<double, Kokkos::dextents<size_t,1>>,
    Kokkos::mdspan<double const, Kokkos::dextents<size_t,1>>
  >::value
);

MDSPAN_STATIC_TEST(
  !std::is_convertible<
    Kokkos::mdspan<double const, Kokkos::dextents<size_t,1>>,
    Kokkos::mdspan<double, Kokkos::dextents<size_t,1>>
  >::value
);

// </editor-fold> end mdspan }}}1
//==============================================================================

