// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include "ctest_common.hpp"

#include <mdspan/mdspan.hpp>

#include <type_traits>



//==============================================================================
// <editor-fold desc="extents"> {{{1

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::extents<size_t,1, 2, Kokkos::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::extents<size_t,Kokkos::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::extents<size_t,Kokkos::dynamic_extent, Kokkos::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::extents<size_t,Kokkos::dynamic_extent, 1, 2, 45>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::extents<size_t,45, Kokkos::dynamic_extent, 1>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::extents<size_t,1, 2, 3>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::extents<size_t,42>
  >::value
);

// </editor-fold> end extents }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="layouts"> {{{1

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::layout_left::template mapping<
      Kokkos::extents<size_t,42, Kokkos::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::layout_right::template mapping<
      Kokkos::extents<size_t,42, Kokkos::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::layout_right::template mapping<
      Kokkos::extents<size_t,Kokkos::dynamic_extent, Kokkos::dynamic_extent>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::layout_stride::template mapping<
      Kokkos::extents<size_t,42, Kokkos::dynamic_extent, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::layout_stride::template mapping<
      Kokkos::extents<size_t,42, 27, 73>
    >
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::layout_stride::template mapping<
      Kokkos::extents<size_t,Kokkos::dynamic_extent, Kokkos::dynamic_extent>
    >
  >::value
);

struct layout_stride_as_member_should_be_standard_layout :
  Kokkos::layout_stride::template mapping<
    Kokkos::extents<size_t,1, 2, 3>
  >
{
  int foo;
};

// Fails with MSVC which adds some padding
#ifndef MDSPAN_IMPL_COMPILER_MSVC
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
    Kokkos::mdspan<double, Kokkos::extents<size_t,1, 2, 3>>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::mdspan<int, Kokkos::dextents<size_t,2>>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_trivially_copyable<
    Kokkos::mdspan<
      double, Kokkos::extents<size_t,Kokkos::dynamic_extent, Kokkos::dynamic_extent>,
      Kokkos::layout_left, Kokkos::default_accessor<double>
    >
  >::value
);

// </editor-fold> end mdspan }}}1
//==============================================================================
