
#include "ctest_common.hpp"

#include <experimental/mdspan>

#include <type_traits>

//==============================================================================
// <editor-fold desc="Test allowed pointer + extents ctors"> {{{1

MDSPAN_STATIC_TEST(
    std::is_constructible_v<
        std::mdspan<int, 2, std::dynamic_extent>,
        int*, int
    >
);

MDSPAN_STATIC_TEST(
    std::is_constructible_v<
        std::mdspan<double, std::dynamic_extent, 2, std::dynamic_extent>,
        double*, unsigned, int
    >
);

// </editor-fold> end Test allowed pointer + extents ctors }}}1
//==============================================================================


//==============================================================================
// <editor-fold desc="Test forbidden pointer + extents ctors"> {{{1

MDSPAN_STATIC_TEST(
    !std::is_constructible_v<
        std::mdspan<int, 2, std::dynamic_extent>,
        double*, int
    >
);

MDSPAN_STATIC_TEST(
    !std::is_constructible_v<
        std::mdspan<int, 2, std::dynamic_extent>,
        int*, int, int
    >
);


// </editor-fold> end Test forbidden pointer + extents ctors }}}1
//==============================================================================