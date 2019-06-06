
#include <experimental/mdspan>

#include <iostream>
#include <iomanip>
#include <memory>
#include <cassert>

//================================================================================

int main() {

  {
    // static sized
    double buffer[2*3*4] = { };
    auto s1 = std::mdspan<double, 2, 3, 4>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = std::subspan(s1, 1, 1, std::all);
    assert(sub1[1] == 42);
  }

  {
    // static sized
    double buffer[2*3*4] = { };
    auto s1 = std::basic_mdspan<double, std::extents<2, 3, 4>, std::layout_left>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = std::subspan(s1, 1, std::all, std::all);
    auto sub2 = std::subspan(sub1, 1, std::all);
    assert(sub2[1] == 42);
  }

  {
    // static sized, all subspans
    double buffer[2*3*4] = { };
    auto s1 = std::mdspan<double, 2, 3, 4>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = std::subspan(s1, 1, std::all, std::all);
    auto sub2 = std::subspan(sub1, 1, std::all);
    auto sub3 = std::subspan(sub2, 1);
    assert(sub3() == 42);
  }

  {
    // static sized, all subspans
    double buffer[2*3*4] = { };
    auto s1 = std::basic_mdspan<double, std::extents<2, 3, 4>, std::layout_left>(buffer);
    s1(1, 1, 1) = 42;
    auto sub1 = std::subspan(s1, 1, std::all, std::all);
    auto sub2 = std::subspan(sub1, 1, std::all);
    auto sub3 = std::subspan(sub2, 1);
    assert(sub3() == 42);
  }

}
