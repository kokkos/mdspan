#define MDSPAN_INTERNAL_TEST

#include <experimental/mdspan>
#include <gtest/gtest.h>

namespace stdex = std::experimental;

// Compile time tests

// actual padding stride
// If extents_type::rank() equals zero or one, then padding_stride.
static_assert(stdex::layout_left_padded<0>::mapping<stdex::extents<std::size_t, 0>>::__actual_padding_stride == 0);
static_assert(stdex::layout_left_padded<2>::mapping<stdex::extents<std::size_t, 0>>::__actual_padding_stride == 2);
static_assert(stdex::layout_left_padded<2>::mapping<stdex::extents<std::size_t, stdex::dynamic_extent>>::__actual_padding_stride == 2);
static_assert(stdex::layout_left_padded<2>::mapping<stdex::extents<std::size_t>>::__actual_padding_stride == 2);
static_assert(stdex::layout_left_padded<stdex::dynamic_extent>::mapping<stdex::extents<std::size_t, 3>>::__actual_padding_stride == stdex::dynamic_extent);
static_assert(stdex::layout_left_padded<stdex::dynamic_extent>::mapping<stdex::extents<std::size_t, 0>>::__actual_padding_stride == stdex::dynamic_extent);
static_assert(stdex::layout_left_padded<stdex::dynamic_extent>::mapping<stdex::extents<std::size_t>>::__actual_padding_stride == stdex::dynamic_extent);

// Else, if
// - padding_stride does not equal dynamic_extent and
// - extents_type::static_extent(0) does not equal dynamic_extent,
// then the size_t value which is the least multiple of padding_stride that is greater than or equal to extents_type::static_extent(0).
static_assert(stdex::layout_left_padded<2>::mapping<stdex::extents<std::size_t, 3, 7>>::__actual_padding_stride == 4);

// Otherwise, dynamic_extent.
static_assert(stdex::layout_left_padded<2>::mapping<stdex::extents<std::size_t, stdex::dynamic_extent, 7>>::__actual_padding_stride == stdex::dynamic_extent);
static_assert(stdex::layout_left_padded<stdex::dynamic_extent>::mapping<stdex::extents<std::size_t, stdex::dynamic_extent, 7>>::__actual_padding_stride == stdex::dynamic_extent);
static_assert(stdex::layout_left_padded<stdex::dynamic_extent>::mapping<stdex::extents<std::size_t, 3, 7>>::__actual_padding_stride == stdex::dynamic_extent);

// inner extents type
// If extents_type::rank() equals zero or one, then inner-extents-type names the type extents_type.
namespace
{
template<class LayoutLeftPadded, class Extents, class DesiredExtents>
inline constexpr bool has_inner_extents_type = std::is_same_v<
    typename LayoutLeftPadded::template mapping<Extents>::__inner_extents_type,
    DesiredExtents >;
template<class LayoutLeftPadded, class Extents>
inline constexpr bool is_0_or_1_rank_inner_extents_type = has_inner_extents_type<LayoutLeftPadded, Extents, typename LayoutLeftPadded::template mapping<Extents>::extents_type>;
}
static_assert(is_0_or_1_rank_inner_extents_type<stdex::layout_left_padded<0>, stdex::extents<std::size_t, 0>>);
static_assert(is_0_or_1_rank_inner_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t>>);
static_assert(is_0_or_1_rank_inner_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, 3>>);
static_assert(is_0_or_1_rank_inner_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, stdex::dynamic_extent>>);
static_assert(is_0_or_1_rank_inner_extents_type<stdex::layout_left_padded<stdex::dynamic_extent>, stdex::extents<std::size_t, 3>>);
static_assert(is_0_or_1_rank_inner_extents_type<stdex::layout_left_padded<stdex::dynamic_extent>, stdex::extents<std::size_t, stdex::dynamic_extent>>);

// Otherwise, inner-extents-type names the type extents<index_type,actual-padding-stride, extents_type::static_extent(P_left)...>.
static_assert(has_inner_extents_type<stdex::layout_left_padded<0>, stdex::extents<std::size_t, 0, 5>, stdex::extents<std::size_t, 0, 5>>);
static_assert(has_inner_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, 3, 5>, stdex::extents<std::size_t, 4, 5>>);
static_assert(has_inner_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, stdex::dynamic_extent, 5>, stdex::extents<std::size_t, stdex::dynamic_extent, 5>>);
static_assert(has_inner_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, 3, stdex::dynamic_extent>, stdex::extents<std::size_t, 4, stdex::dynamic_extent>>);
static_assert(has_inner_extents_type<stdex::layout_left_padded<stdex::dynamic_extent>, stdex::extents<std::size_t, 3, 5>, stdex::extents<std::size_t, stdex::dynamic_extent, 5>>);

// unpadded extent type
namespace
{
template<class LayoutLeftPadded, class Extents, class DesiredExtents>
inline constexpr bool has_unpadded_extents_type = std::is_same_v<
    typename LayoutLeftPadded::template mapping<Extents>::__unpadded_extent_type,
    DesiredExtents >;
}
// If extents_type::rank() equals zero, then unpadded-extent-type names the type extents<index_type>.
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<0>, stdex::extents<std::size_t>, stdex::extents<std::size_t>>);
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t>, stdex::extents<std::size_t>>);
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<stdex::dynamic_extent>, stdex::extents<std::size_t>, stdex::extents<std::size_t>>);

// Otherwise, unpadded-extent-type names the type extents<index_type, extents_type::static_extent(0)>.
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<0>, stdex::extents<std::size_t, 0>, stdex::extents<std::size_t, 0>>);
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, 3>, stdex::extents<std::size_t, 3>>);
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, stdex::dynamic_extent>, stdex::extents<std::size_t, stdex::dynamic_extent>>);
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<0>, stdex::extents<std::size_t, 0, 7>, stdex::extents<std::size_t, 0>>);
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, 3, 5>, stdex::extents<std::size_t, 3>>);
static_assert(has_unpadded_extents_type<stdex::layout_left_padded<2>, stdex::extents<std::size_t, stdex::dynamic_extent, 13>, stdex::extents<std::size_t, stdex::dynamic_extent>>);

namespace
{
template<class LayoutLeftPadded, class InnerExtents, class TestExtents>
void test_inner_mapping_extent(const InnerExtents &inner_extents, const TestExtents &test_extents)
{
  auto mapping = typename LayoutLeftPadded::template mapping<InnerExtents>(inner_extents);
  ASSERT_EQ(mapping.__inner_mapping.extents(), test_extents);
}

template<class LayoutLeftPadded, class Extents>
void test_0_or_1_rank_inner_mapping_extents(const Extents &extents)
{
  test_inner_mapping_extent<LayoutLeftPadded>(extents, extents);
}
}

TEST(LayoutLeftTests, construction)
{
  // Direct-non-list-initializes inner-mapping with:
  // - ext, if extents_type::rank() is zero or one; else,
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<4>>(stdex::extents<std::size_t>{});
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<0>>(stdex::extents<std::size_t, 0>{});
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<4>>(stdex::extents<std::size_t, 5>{});
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<4>>(stdex::extents<std::size_t, stdex::dynamic_extent>{7});
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<stdex::dynamic_extent>>(stdex::extents<std::size_t>{});
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<stdex::dynamic_extent>>(stdex::extents<std::size_t, 0>{});
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<stdex::dynamic_extent>>(stdex::extents<std::size_t, 5>{});
  test_0_or_1_rank_inner_mapping_extents<stdex::layout_left_padded<stdex::dynamic_extent>>(stdex::extents<std::size_t, stdex::dynamic_extent>{7});

  // - ext.extent(0), ext.extent(P_left)..., if padding_stride is dynamic_extent
  test_inner_mapping_extent<stdex::layout_left_padded<stdex::dynamic_extent>>(stdex::extents<std::size_t, 0, 7>{}, stdex::extents<std::size_t, stdex::dynamic_extent, 7>{ 0 });
  test_inner_mapping_extent<stdex::layout_left_padded<stdex::dynamic_extent>>(stdex::extents<std::size_t, 5, 7>{}, stdex::extents<std::size_t, stdex::dynamic_extent, 7>{ 5 });
  test_inner_mapping_extent<stdex::layout_left_padded<stdex::dynamic_extent>>(stdex::extents<std::size_t, stdex::dynamic_extent, 13>{7}, stdex::extents<std::size_t, stdex::dynamic_extent, 13>{7});

  // - S_left, ext.extent(P_left)..., where S_left is the least multiple of padding_stride greater than or equal to ext.extent(0)
  test_inner_mapping_extent<stdex::layout_left_padded<0>>(stdex::extents<std::size_t, 0, 7>{}, stdex::extents<std::size_t, 0, 7>{});
  test_inner_mapping_extent<stdex::layout_left_padded<4>>(stdex::extents<std::size_t, 5, 7>{}, stdex::extents<std::size_t, 8, 7>{});
  test_inner_mapping_extent<stdex::layout_left_padded<4>>(stdex::extents<std::size_t, stdex::dynamic_extent, 13>{7}, stdex::extents<std::size_t, stdex::dynamic_extent, 13>{8});

}
