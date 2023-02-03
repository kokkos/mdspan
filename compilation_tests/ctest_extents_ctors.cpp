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

namespace stdex = std::experimental;


MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,1, 2, stdex::dynamic_extent>,
    int
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_copy_constructible<
    stdex::extents<size_t,1, 2, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_copy_constructible<
    stdex::extents<size_t,1, 2>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_copy_constructible<
    stdex::extents<size_t,stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_move_constructible<
    stdex::extents<size_t,1, 2, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_default_constructible<
    stdex::extents<size_t,1, 2, 3>
  >::value
);

// constructibility test from integrals
MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent, stdex::dynamic_extent>,
    int, size_t, int
  >::value
);

MDSPAN_STATIC_TEST(
  !std::is_constructible<
    stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent, stdex::dynamic_extent>,
    int, int
  >::value
);

MDSPAN_STATIC_TEST(
  !std::is_constructible<
    stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent, stdex::dynamic_extent>,
    int
  >::value
);

// conversion construction from extents
MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent, stdex::dynamic_extent>,
    stdex::extents<size_t,stdex::dynamic_extent, 2, 3>
  >::value
);


MDSPAN_STATIC_TEST(
  std::is_convertible<
    stdex::extents<size_t,2, 3>,
    stdex::extents<size_t,2, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    stdex::extents<size_t,2, 3>
  >::value
);

#if MDSPAN_HAS_CXX_20
// GNU gets the is_convertible with conditional explicit
// wrong in some older versions.
#if !defined(__GNUC__) || (__GNUC__ > 10)
MDSPAN_STATIC_TEST(
  !std::is_convertible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    stdex::extents<size_t,2, 3>
  >::value
);
#endif
#endif


MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t>,
    stdex::extents<int>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_convertible<
    stdex::extents<int>,
    stdex::extents<size_t>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<int>,
    stdex::extents<size_t>
  >::value
);

#if MDSPAN_HAS_CXX_20
// GNU gets the is_convertible with conditional explicit
// wrong in some older versions.
#if !defined(__GNUC__) || (__GNUC__ > 10)
MDSPAN_STATIC_TEST(
  !std::is_convertible<
    stdex::extents<size_t>,
    stdex::extents<int>
  >::value
);
#endif
#endif

MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    std::array<int, 1>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_convertible<
    std::array<int, 1>,
    stdex::extents<size_t,2, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    std::array<int, 2>
  >::value
);

#if MDSPAN_HAS_CXX_20
// GNU gets the is_convertible with conditional explicit
// wrong in some older versions.
#if !defined(__GNUC__) || (__GNUC__ > 10)
MDSPAN_STATIC_TEST(
  !std::is_convertible<
    std::array<int, 2>,
    stdex::extents<size_t,2, stdex::dynamic_extent>
  >::value
);
#endif
#endif

MDSPAN_STATIC_TEST(
  !std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    std::array<int,3>
  >::value
);

#ifdef __cpp_lib_span
MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    std::span<int,1>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_convertible<
    std::span<int,1>,
    stdex::extents<size_t,2, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    std::span<int,2>
  >::value
);

#if MDSPAN_HAS_CXX_20
// GNU gets the is_convertible with conditional explicit
// wrong in some older versions.
#if !defined(__GNUC__) || (__GNUC__ > 10)
MDSPAN_STATIC_TEST(
  !std::is_convertible<
    std::span<int, 2>,
    stdex::extents<size_t,2, stdex::dynamic_extent>
  >::value
);
#endif
#endif

// this is not supported in the standard
MDSPAN_STATIC_TEST(
  !std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    std::span<int,std::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  !std::is_constructible<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    std::span<int,3>
  >::value
);
#endif // __cpp_lib_span

MDSPAN_STATIC_TEST(
  !std::is_constructible<
    stdex::extents<size_t,3, stdex::dynamic_extent>,
    stdex::extents<size_t,2, 3>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_assignable<
    stdex::extents<size_t,2, stdex::dynamic_extent>,
    stdex::extents<size_t,2, 3>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_same<
    stdex::dextents<size_t,0>,
    stdex::extents<size_t>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_same<
    stdex::dextents<size_t,1>,
    stdex::extents<size_t,stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_same<
    stdex::dextents<size_t,2>,
    stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent>
  >::value
);

MDSPAN_STATIC_TEST(
  std::is_same<
    stdex::dextents<size_t,3>,
    stdex::extents<size_t,stdex::dynamic_extent, stdex::dynamic_extent, stdex::dynamic_extent>
  >::value
);

