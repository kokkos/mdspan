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

namespace stdex = MDSPAN_IMPL_STANDARD_NAMESPACE;


//==============================================================================
// <editor-fold desc="extents"> {{{1

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::extents<size_t,1, 2, md::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::extents<size_t,md::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::extents<size_t,md::dynamic_extent, md::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::extents<size_t,md::dynamic_extent, 1, 2, 45>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::extents<size_t,45, md::dynamic_extent, 1>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::extents<size_t,1, 2, 3>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::extents<size_t,42>
  >::value
);

// </editor-fold> end extents }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="layouts"> {{{1

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::layout_left::template mapping<
      md::extents<size_t,42, md::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::layout_right::template mapping<
      md::extents<size_t,42, md::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::layout_right::template mapping<
      md::extents<size_t,md::dynamic_extent, md::dynamic_extent>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::layout_stride::template mapping<
      md::extents<size_t,42, md::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::layout_stride::template mapping<
      md::extents<size_t,42, 27, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::layout_stride::template mapping<
      md::extents<size_t,md::dynamic_extent, md::dynamic_extent>
    >
  >::value
);

struct layout_stride_as_member_should_be_standard_layout :
  md::layout_stride::template mapping<
    md::extents<size_t,1, 2, 3>
  >
{
  int foo;
};

// Fails with MSVC which adds some padding
#ifndef _MDSPAN_COMPILER_MSVC
MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<layout_stride_as_member_should_be_standard_layout>::value
);
#endif

// </editor-fold> end layouts }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="mdspan"> {{{1

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::mdspan<double, md::extents<size_t,1, 2, 3>>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::mdspan<int, md::dextents<size_t,2>>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    md::mdspan<
      double, md::extents<size_t,md::dynamic_extent, md::dynamic_extent>,
      md::layout_left, md::default_accessor<double>
    >
  >::value
);

// </editor-fold> end mdspan }}}1
//==============================================================================



