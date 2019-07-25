
#include "ctest_common.hpp"

#include <experimental/mdspan>

MDSPAN_STATIC_TEST(
  std::is_constructible_v<
    std::extents<1, 2, std::dynamic_extent>,
    int
  >
);

MDSPAN_STATIC_TEST(
  std::is_default_constructible_v<
    std::extents<1, 2, 3>
  >
);

MDSPAN_STATIC_TEST(
  std::is_constructible_v<
    std::extents<std::dynamic_extent, std::dynamic_extent, std::dynamic_extent>,
    int, int, int
  >
);

MDSPAN_STATIC_TEST(
  std::is_constructible_v<
    std::extents<std::dynamic_extent, std::dynamic_extent, std::dynamic_extent>,
    std::extents<std::dynamic_extent, 2, 3>
  >
);
