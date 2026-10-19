// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include <mdspan/mdspan.hpp>

#include <gtest/gtest.h>
#include <limits>

template <class Layout, class IndexType>
constexpr bool test_empty_required_span_size() {
  using E                   = Kokkos::dextents<IndexType, 3>;
  constexpr IndexType large = std::numeric_limits<IndexType>::max();
  const E extents[]         = {E(0, large, large), E(large, 0, large),
                               E(large, large, 0)};
  for (const auto& ext : extents) {
    const typename Layout::template mapping<E> mapping(ext);
    if (mapping.required_span_size() != 0) return false;
  }
  return true;
}

#if MDSPAN_HAS_CXX_17
// The padded extent is empty but the padding stride is not
template <class IndexType>
constexpr bool test_empty_padded_extent_required_span_size() {
  using E       = Kokkos::dextents<IndexType, 2>;
  using strides = std::array<IndexType, 2>;
  const Kokkos::layout_left_padded<>::mapping<E> left(
      Kokkos::layout_stride::mapping<E>(E(0, 3), strides{1, 4}));
  const Kokkos::layout_right_padded<>::mapping<E> right(
      Kokkos::layout_stride::mapping<E>(E(3, 0), strides{4, 1}));
  return left.stride(1) == 4 && left.required_span_size() == 0 &&
         right.stride(0) == 4 && right.required_span_size() == 0;
}
#endif

template <class IndexType>
struct TestLayoutRequiredSpanSize : public ::testing::Test {};

// Signed, unsigned, and unsigned promoted to int
using required_span_size_index_types =
    ::testing::Types<int, unsigned, unsigned short, size_t>;

TYPED_TEST_SUITE(TestLayoutRequiredSpanSize, required_span_size_index_types);

TYPED_TEST(TestLayoutRequiredSpanSize, empty_index_space) {
  using index_type = TypeParam;
  static_assert(
      test_empty_required_span_size<Kokkos::layout_left, index_type>(), "");
  static_assert(
      test_empty_required_span_size<Kokkos::layout_right, index_type>(), "");
  EXPECT_TRUE(
      (test_empty_required_span_size<Kokkos::layout_left, index_type>()));
  EXPECT_TRUE(
      (test_empty_required_span_size<Kokkos::layout_right, index_type>()));
#if MDSPAN_HAS_CXX_17
  static_assert(
      test_empty_required_span_size<Kokkos::layout_left_padded<>, index_type>(),
      "");
  static_assert(test_empty_required_span_size<Kokkos::layout_right_padded<>,
                                              index_type>(),
                "");
  EXPECT_TRUE((test_empty_required_span_size<Kokkos::layout_left_padded<>,
                                             index_type>()));
  EXPECT_TRUE((test_empty_required_span_size<Kokkos::layout_right_padded<>,
                                             index_type>()));
  static_assert(test_empty_padded_extent_required_span_size<index_type>(), "");
  EXPECT_TRUE(test_empty_padded_extent_required_span_size<index_type>());
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
