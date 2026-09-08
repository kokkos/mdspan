// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

// These need to be ordered first or the test, well, fails
#include <experimental/mdspan>
#include <experimental/mdarray>

#include "ctest_common.hpp"

using test_extents_type = std::extents<int, std::dynamic_extent>;
using test_mdspan_type = std::mdspan<double, test_extents_type>;
using test_mdarray_type = std::experimental::mdarray<double, test_extents_type>;
