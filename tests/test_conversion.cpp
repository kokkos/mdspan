#include <experimental/mdspan>

#include <gtest/gtest.h>

namespace stdex = std::experimental;

TEST(TestConversion, const_element) {
    std::array<double, 6> a{};
    stdex::mdspan<double, 2, 3> s(a.data());
    s(0, 1) = 3.14;
    stdex::mdspan<double const, 2, 3> c_s(s);
    ASSERT_EQ(c_s(0, 1), 3.14);
}
