
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

}
