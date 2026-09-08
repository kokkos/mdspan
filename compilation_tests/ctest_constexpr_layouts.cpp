// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include "ctest_common.hpp"

#include <mdspan/mdspan.hpp>


// Only works with newer constexpr
#if defined(MDSPAN_IMPL_USE_CONSTEXPR_14) && MDSPAN_IMPL_USE_CONSTEXPR_14

constexpr std::ptrdiff_t
layout_stride_simple(int i) {
  using map_t = Kokkos::layout_stride::template mapping<
    Kokkos::extents<size_t,3>
  >;
  return map_t(Kokkos::extents<size_t,3>{}, std::array<size_t,1>{1})(i);
}

MDSPAN_STATIC_TEST(
  layout_stride_simple(0) == 0
);
MDSPAN_STATIC_TEST(
  layout_stride_simple(1) == 1
);

#endif // MDSPAN_IMPL_USE_CONSTEXPR_14
