//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

// Test the case where an index is not integral-not-bool
// but is convertible to integral-not-bool, as permitted
// by e.g., [mdspan.layout.left.obs] 2.

#include <mdspan/mdspan.hpp>
#include <type_traits>
#include <gtest/gtest.h>


namespace test {

// Index or slice type that's convertible to IndexType,
// but neither integral nor integral-constant-like.
MDSPAN_TEMPLATE_REQUIRES(
  class IndexType,
  /* requires */ (
    std::is_signed_v<IndexType> || std::is_unsigned_v<IndexType>
  )
)
class index_holder {
public:
  constexpr index_holder(IndexType i) : i_{i} {}
  constexpr operator IndexType() const noexcept { return i_; }
  constexpr index_holder& operator++() noexcept {
    ++i_;
    return *this;
  }
#if defined(__cpp_impl_three_way_comparison)
  constexpr auto operator<=>(const index_holder&) const noexcept = default;
#else
  friend constexpr bool operator<(const index_holder& x, const index_holder& y) noexcept {
    return x.i_ < y.i_;
  }
  friend constexpr bool operator==(const index_holder& x, const index_holder& y) noexcept {
    return x.i_ == y.i_;
  }
#endif

private:
  IndexType i_;
};
static_assert(std::is_convertible_v<index_holder<int>, int>);
static_assert(std::is_convertible_v<index_holder<size_t>, size_t>);
static_assert(std::is_nothrow_constructible_v<int, index_holder<int>>);
static_assert(std::is_nothrow_constructible_v<size_t, index_holder<size_t>>);

// Slice type that's convertible to full_extent_t, but is not full_extent_t.
struct full_extent_wrapper_t {
  constexpr operator Kokkos::full_extent_t() const noexcept{
    return Kokkos::full_extent;
  }
};

template<class Layout, class IndexType, size_t... Exts>
void test_mapping_call_operator(Layout, Kokkos::extents<IndexType, Exts...> exts) {
  using extents_type = Kokkos::extents<IndexType, Exts...>;
  using mapping_type = typename Layout::template mapping<extents_type>;
  mapping_type mapping(exts);

  const index_holder<IndexType> wrapped_zero(0);
  const IndexType zero(0);

  for (size_t i = 0; i < exts.rank(); ++i) {
    auto result = mapping(((void) Exts, wrapped_zero)...);
    auto expected_result = mapping(((void) Exts, zero)...);
    EXPECT_EQ(result, expected_result);
  }
}

template<class Layout, class IndexType, size_t... Exts>
void test_submdspan1(Layout, Kokkos::extents<IndexType, Exts...> exts) {
  using extents_type = Kokkos::extents<IndexType, Exts...>;
  using mapping_type = typename Layout::template mapping<extents_type>;
  mapping_type mapping(exts);

  auto buffer = std::make_unique<uint8_t[]>(mapping.required_span_size());
  auto view = Kokkos::mdspan<uint8_t, extents_type, Layout>(buffer.get(), mapping);

  const index_holder<IndexType> wrapped_zero(0);
  const IndexType zero(0);

  auto result = Kokkos::submdspan(view, ((void) Exts, wrapped_zero)...);
  auto expected_result = Kokkos::submdspan(view, ((void) Exts, zero)...);
  static_assert(std::is_same_v<decltype(result), decltype(expected_result)>);
  EXPECT_EQ(result.mapping(), expected_result.mapping());
}

template<class Mdspan, size_t... Inds>
void test_submdspan2_inner(const Mdspan& view, std::index_sequence<Inds...>) {
  using index_type = typename Mdspan::index_type;

  const index_holder<index_type> wrapped_zero(0);
  const index_type zero(0);

  auto result = Kokkos::submdspan(view, wrapped_zero, ((void) Inds, Kokkos::full_extent)...);
  auto expected_result = Kokkos::submdspan(view, zero, ((void) Inds, Kokkos::full_extent)...);
  static_assert(std::is_same_v<decltype(result), decltype(expected_result)>);
  EXPECT_EQ(result.mapping(), expected_result.mapping());
}

template<class Layout, class IndexType, size_t... Exts>
void test_submdspan2(Layout, Kokkos::extents<IndexType, Exts...> exts) {
  using extents_type = Kokkos::extents<IndexType, Exts...>;
  using mapping_type = typename Layout::template mapping<extents_type>;
  mapping_type mapping(exts);

  auto buffer = std::make_unique<uint8_t[]>(mapping.required_span_size());
  auto view = Kokkos::mdspan<uint8_t, extents_type, Layout>(buffer.get(), mapping);

  static_assert(sizeof...(Exts) != 0);
  test_submdspan2_inner(view, std::make_index_sequence<sizeof...(Exts) - 1u>{});
}

template<class Mdspan, size_t... Inds>
void test_submdspan3_inner(const Mdspan& view, std::index_sequence<Inds...>) {
  using index_type = typename Mdspan::index_type;

  const index_holder<index_type> wrapped_zero(0);
  const index_type zero(0);

  auto result = Kokkos::submdspan(view, wrapped_zero, ((void) Inds, full_extent_wrapper_t{})...);
  auto expected_result = Kokkos::submdspan(view, zero, ((void) Inds, full_extent_wrapper_t{})...);
  static_assert(std::is_same_v<decltype(result), decltype(expected_result)>);
  EXPECT_EQ(result.mapping(), expected_result.mapping());
}

template<class Layout, class IndexType, size_t... Exts>
void test_submdspan3(Layout, Kokkos::extents<IndexType, Exts...> exts) {
  using extents_type = Kokkos::extents<IndexType, Exts...>;
  using mapping_type = typename Layout::template mapping<extents_type>;
  mapping_type mapping(exts);

  auto buffer = std::make_unique<uint8_t[]>(mapping.required_span_size());
  auto view = Kokkos::mdspan<uint8_t, extents_type, Layout>(buffer.get(), mapping);

  static_assert(sizeof...(Exts) != 0);
  test_submdspan3_inner(view, std::make_index_sequence<sizeof...(Exts) - 1u>{});
}

} // namespace test

TEST(ConvertibleToIndexType, CallOperatorLayoutLeft)
{
  test::test_mapping_call_operator(Kokkos::layout_left{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_mapping_call_operator(Kokkos::layout_left{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}

TEST(ConvertibleToIndexType, CallOperatorLayoutRight)
{
  test::test_mapping_call_operator(Kokkos::layout_right{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_mapping_call_operator(Kokkos::layout_right{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}

TEST(ConvertibleToIndexType, Submdspan1_LayoutLeft)
{
  test::test_submdspan1(Kokkos::layout_left{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_submdspan1(Kokkos::layout_left{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}

TEST(ConvertibleToIndexType, Submdspan1_LayoutRight)
{
  test::test_submdspan1(Kokkos::layout_right{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_submdspan1(Kokkos::layout_right{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}

TEST(ConvertibleToIndexType, Submdspan2_LayoutLeft)
{
  test::test_submdspan2(Kokkos::layout_left{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_submdspan2(Kokkos::layout_left{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}

TEST(ConvertibleToIndexType, Submdspan2_LayoutRight)
{
  test::test_submdspan2(Kokkos::layout_right{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_submdspan2(Kokkos::layout_right{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}

TEST(ConvertibleToIndexType, Submdspan3_LayoutLeft)
{
  test::test_submdspan3(Kokkos::layout_left{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_submdspan3(Kokkos::layout_left{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}

TEST(ConvertibleToIndexType, Submdspan3_LayoutRight)
{
  test::test_submdspan3(Kokkos::layout_right{}, Kokkos::extents<int, 2, 2, 2, 2, 2, 2>{});
  test::test_submdspan3(Kokkos::layout_right{}, Kokkos::dextents<int, 6>{2, 2, 2, 2, 2, 2});
}
