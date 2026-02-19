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

#pragma once

#include <type_traits>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
  namespace detail {

#if (__cplusplus >= 202002L)
    using std::remove_cvref_t;
#else
    template<class T>
    struct remove_cvref {
      using type = typename std::remove_cv_t<std::remove_reference_t<T>>;
    };
    template<class T>
    using remove_cvref_t = typename remove_cvref<T>::type;
#endif // __cplusplus >= 202002L

  } // namespace detail
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
