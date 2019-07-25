
#include "experimental/bits/macros.hpp"

#pragma once

#define MDSPAN_STATIC_TEST(...) \
  static_assert(__VA_ARGS__, "MDSpan compile time test failed at "  __FILE__ ":" MDSPAN_PP_STRINGIFY(__LINE__))

// All tests need a main so that they'll link
int main() { }
