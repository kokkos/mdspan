#include <mdspan/mdspan.hpp>
#include <gtest/gtest.h>

TEST(mdspan_macros, precondition_violation)
{
  constexpr auto msg = "hello, world!";

  ASSERT_DEATH(MDSPAN_PRECONDITION(false and "hello, world!"), msg);
}

TEST(mdspan_macros, precondition_check_constexpr_invocable)
{
  struct fn
  {
    constexpr auto operator()() const
    {
      MDSPAN_PRECONDITION(1 + 1 == 2);
      return 42;
    }
  };

  static constexpr auto x = fn{}();
  (void)x;
}
