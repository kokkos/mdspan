// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include <mdspan/mdspan.hpp>

#include <gtest/gtest.h>
#include <limits>

template <class Layout>
constexpr bool test_empty_required_span_size() {
  using E             = Kokkos::dextents<int, 3>;
  constexpr int large = std::numeric_limits<int>::max();
  const E extents[]   = {E(0, large, large), E(large, 0, large),
                         E(large, large, 0)};
  for (const auto& ext : extents) {
    const typename Layout::template mapping<E> mapping(ext);
    if (mapping.required_span_size() != 0) return false;
  }
  return true;
}

TEST(TestLayoutRequiredSpanSize, empty_index_space) {
  static_assert(test_empty_required_span_size<Kokkos::layout_left>(), "");
  static_assert(test_empty_required_span_size<Kokkos::layout_right>(), "");
  EXPECT_TRUE(test_empty_required_span_size<Kokkos::layout_left>());
  EXPECT_TRUE(test_empty_required_span_size<Kokkos::layout_right>());
#if MDSPAN_HAS_CXX_17
  static_assert(test_empty_required_span_size<Kokkos::layout_left_padded<>>(),
                "");
  static_assert(test_empty_required_span_size<Kokkos::layout_right_padded<>>(),
                "");
  EXPECT_TRUE(test_empty_required_span_size<Kokkos::layout_left_padded<>>());
  EXPECT_TRUE(test_empty_required_span_size<Kokkos::layout_right_padded<>>());
#endif
}

TEST(TestConvertingConstructionFromLayoutStride, precondition_failure) {
  using E = Kokkos::extents<size_t, 2, 2>;

  const auto stride =
      Kokkos::layout_stride::mapping<E>{E{}, std::array<size_t, 2>{2, 8}};

#if defined(MDSPAN_IMPL_HAS_CUDA) || defined(MDSPAN_IMPL_HAS_HIP) || \
    defined(MDSPAN_IMPL_HAS_SYCL)
  ASSERT_DEATH(Kokkos::layout_left::mapping<E>{stride}, "");
  ASSERT_DEATH(Kokkos::layout_right::mapping<E>{stride}, "");
#else
  ASSERT_DEATH(Kokkos::layout_left::mapping<E>{stride}, "invalid strides");
  ASSERT_DEATH(Kokkos::layout_right::mapping<E>{stride}, "invalid strides");
#endif
}
