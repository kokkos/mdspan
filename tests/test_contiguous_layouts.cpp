

#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>
#include <experimental/mdspan>

#include <tuple>
#include <utility>

template <class Extents>
ptrdiff_t get_expected_mapping(
  typename std::layout_left::template mapping<Extents> const& map,
  ptrdiff_t i, ptrdiff_t j, ptrdiff_t k
)
{
  auto const& extents = map.extents();
  return i + j*extents.extent(0) + k*extents.extent(0)*extents.extent(1);
}

template <class Extents>
ptrdiff_t get_expected_mapping(
  typename std::layout_right::template mapping<Extents> const& map,
  ptrdiff_t i, ptrdiff_t j, ptrdiff_t k
)
{
  auto const& extents = map.extents();
  return k + j*extents.extent(2) + i*extents.extent(1)*extents.extent(2);
}

template <class> struct TestLayout;

template <class Mapping, ptrdiff_t... DynamicSizes>
struct TestLayout<std::tuple<
  Mapping,
  std::integer_sequence<ptrdiff_t, DynamicSizes...>
>> : public ::testing::Test
{
  Mapping map;

  void initialize_mapping() {
    using extents_type = decltype(map.extents());
    map = Mapping(extents_type(DynamicSizes...));
  }

  void SetUp() override {
    initialize_mapping();
  }

  template <class... Index>
  ptrdiff_t expected_mapping(Index... idxs) const {
    return get_expected_mapping(map, idxs...);
  }
};

template <class Extents, ptrdiff_t... DynamicSizes>
using test_3d_left_types = std::tuple<
  typename std::layout_left::template mapping<Extents>,
  std::integer_sequence<ptrdiff_t, DynamicSizes...>
>;

template <class Extents, ptrdiff_t... DynamicSizes>
using test_3d_right_types = std::tuple<
  typename std::layout_right::template mapping<Extents>,
  std::integer_sequence<ptrdiff_t, DynamicSizes...>
>;

using layout_test_types_3d =
  ::testing::Types<
    test_3d_left_types<std::extents<3, 4, 5>>,
    test_3d_left_types<std::extents<5, 4, 3>>,
    test_3d_left_types<std::extents<3, 4, std::dynamic_extent>, 5>,
    test_3d_left_types<std::extents<5, 4, std::dynamic_extent>, 3>,
    test_3d_left_types<std::extents<3, std::dynamic_extent, 5>, 4>,
    test_3d_left_types<std::extents<5, std::dynamic_extent, 3>, 4>,
    test_3d_left_types<std::extents<std::dynamic_extent, 4, 5>, 3>,
    test_3d_left_types<std::extents<std::dynamic_extent, 4, 3>, 5>,
    test_3d_left_types<std::extents<std::dynamic_extent, std::dynamic_extent, 5>, 3, 4>,
    test_3d_left_types<std::extents<std::dynamic_extent, std::dynamic_extent, 3>, 5, 4>,
    test_3d_left_types<std::extents<std::dynamic_extent, 4, std::dynamic_extent>, 3, 5>,
    test_3d_left_types<std::extents<std::dynamic_extent, 4, std::dynamic_extent>, 5, 3>,
    test_3d_left_types<std::extents<3, std::dynamic_extent, std::dynamic_extent>, 4, 5>,
    test_3d_left_types<std::extents<5, std::dynamic_extent, std::dynamic_extent>, 4, 3>,
    test_3d_left_types<std::extents<std::dynamic_extent, std::dynamic_extent, std::dynamic_extent>, 3, 4, 5>,
    test_3d_left_types<std::extents<std::dynamic_extent, std::dynamic_extent, std::dynamic_extent>, 5, 4, 3>,
    test_3d_right_types<std::extents<3, 4, 5>>,
    test_3d_right_types<std::extents<5, 4, 3>>,
    test_3d_right_types<std::extents<3, 4, std::dynamic_extent>, 5>,
    test_3d_right_types<std::extents<5, 4, std::dynamic_extent>, 3>,
    test_3d_right_types<std::extents<3, std::dynamic_extent, 5>, 4>,
    test_3d_right_types<std::extents<5, std::dynamic_extent, 3>, 4>,
    test_3d_right_types<std::extents<std::dynamic_extent, 4, 5>, 3>,
    test_3d_right_types<std::extents<std::dynamic_extent, 4, 3>, 5>,
    test_3d_right_types<std::extents<std::dynamic_extent, std::dynamic_extent, 5>, 3, 4>,
    test_3d_right_types<std::extents<std::dynamic_extent, std::dynamic_extent, 3>, 5, 4>,
    test_3d_right_types<std::extents<std::dynamic_extent, 4, std::dynamic_extent>, 3, 5>,
    test_3d_right_types<std::extents<std::dynamic_extent, 4, std::dynamic_extent>, 5, 3>,
    test_3d_right_types<std::extents<3, std::dynamic_extent, std::dynamic_extent>, 4, 5>,
    test_3d_right_types<std::extents<5, std::dynamic_extent, std::dynamic_extent>, 4, 3>,
    test_3d_right_types<std::extents<std::dynamic_extent, std::dynamic_extent, std::dynamic_extent>, 3, 4, 5>,
    test_3d_right_types<std::extents<std::dynamic_extent, std::dynamic_extent, std::dynamic_extent>, 5, 4, 3>
  >;

template <class T> struct TestLayout3D : TestLayout<T> { };


TYPED_TEST_SUITE(TestLayout3D, layout_test_types_3d);

TYPED_TEST(TestLayout3D, mapping_works) {
  for(ptrdiff_t i = 0; i < this->map.extents().extent(0); ++i) {
    for(ptrdiff_t j = 0; j < this->map.extents().extent(1); ++j) {
      for(ptrdiff_t k = 0; k < this->map.extents().extent(2); ++k) {
        EXPECT_EQ(this->map(i, j, k), this->expected_mapping(i, j, k))
          << "Incorrect mapping for index " << i << ", " << j << ", " << k
          << " with extents "
          << this->map.extents().extent(0) << ", "
          << this->map.extents().extent(1) << ", "
          << this->map.extents().extent(2) << ".";
      }
    }
  }
}

TYPED_TEST(TestLayout3D, required_span_size_works) {
  ASSERT_EQ(this->map.required_span_size(), 3*4*5);
}
