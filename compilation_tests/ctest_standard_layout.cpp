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
// <editor-fold desc="extents"> {{{1

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::extents<size_t,1, 2, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::extents<size_t,stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::extents<size_t,stdex::dynamic_extent, 1, 2, 45>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::extents<size_t,45, stdex::dynamic_extent, 1>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::extents<size_t,1, 2, 3>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::extents<size_t,42>
  >::value
);

// </editor-fold> end extents }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="layouts"> {{{1

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::layout_left::template mapping<
      stdex::extents<size_t,42, stdex::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::layout_right::template mapping<
      stdex::extents<size_t,42, stdex::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::layout_right::template mapping<
      stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::layout_stride::template mapping<
      stdex::extents<size_t,42, stdex::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::layout_stride::template mapping<
      stdex::extents<size_t,42, 27, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::layout_stride::template mapping<
      stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent>
    >
  >::value
);

// TODO: Remove this test alltogether?
// CT: Fails with GCC too after I removed the template parameter
// I guess there is padding added after foo?
#if 0
struct layout_stride_as_member_should_be_standard_layout :
  stdex::layout_stride::template mapping<
    stdex::extents<size_t,1, 2, 3>>
{
  int foo;
};

// Fails with MSVC which adds some padding
#ifndef _MDSPAN_COMPILER_MSVC
MDSPAN_STATIC_TEST(
  std::is_standard_layout<layout_stride_as_member_should_be_standard_layout>::value
);
#endif
#endif

// </editor-fold> end layouts }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="mdspan"> {{{1

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::mdspan<double, stdex::extents<size_t,1, 2, 3>>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::mdspan<int, stdex::dextents<size_t,2>>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_standard_layout<
    stdex::mdspan<
      double, stdex::dextents<size_t,2>,
      stdex::layout_left, stdex::default_accessor<double>
    >
  >::value
);

// </editor-fold> end mdspan }}}1
//==============================================================================



