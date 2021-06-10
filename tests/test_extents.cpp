/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2021) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include <experimental/mdspan>

#include <gtest/gtest.h>

namespace stdex = std::experimental;

template <class> struct TestExtents;
template <size_t... Extents, size_t... DynamicSizes>
struct TestExtents<std::tuple<
  stdex::extents<Extents...>,
  std::integer_sequence<size_t, DynamicSizes...>
>> : public ::testing::Test {
  using extents_type = stdex::extents<Extents...>;
  // Double Braces here to make it work with GCC 5
  // Otherwise: "error: array must be initialized with a brace-enclosed initializer"
  const std::array<size_t, sizeof...(Extents)> static_sizes {{ Extents... }};
  const std::array<size_t, sizeof...(DynamicSizes)> dyn_sizes {{ DynamicSizes... }};
  extents_type exts { DynamicSizes... };
};

template <size_t... Ds>
using _sizes = std::integer_sequence<size_t, Ds...>;
template <size_t... Ds>
using _exts = stdex::extents<Ds...>;

using extents_test_types =
  ::testing::Types<
    std::tuple<_exts<10>, _sizes<>>,
    std::tuple<_exts<stdex::dynamic_extent>, _sizes<10>>,
    std::tuple<_exts<10, 3>, _sizes<>>,
    std::tuple<_exts<stdex::dynamic_extent, 3>, _sizes<10>>,
    std::tuple<_exts<10, stdex::dynamic_extent>, _sizes<3>>,
    std::tuple<_exts<stdex::dynamic_extent, stdex::dynamic_extent>, _sizes<10, 3>>
  >;

TYPED_TEST_SUITE(TestExtents, extents_test_types);

TYPED_TEST(TestExtents, rank) {
  EXPECT_EQ(this->exts.rank(), this->static_sizes.size());
}

TYPED_TEST(TestExtents, dynamic_rank) {
  EXPECT_EQ(this->exts.rank_dynamic(), this->dyn_sizes.size());
}

TYPED_TEST(TestExtents, static_extent) {
  for (size_t r = 0; r < this->exts.rank(); ++r) {
    EXPECT_EQ(this->exts.static_extent(r), this->static_sizes[r]);
  }
}

TYPED_TEST(TestExtents, extent_method) {
  size_t dyn_count = 0;
  for (size_t r = 0; r < this->exts.rank(); ++r) {
    bool is_dynamic = (this->exts.static_extent(r) == stdex::dynamic_extent);
    EXPECT_EQ(this->exts.extent(r), is_dynamic ? this->dyn_sizes[dyn_count++] : this->static_sizes[r]);
  }
}

TYPED_TEST(TestExtents, default_ctor) {
  auto e = typename TestFixture::extents_type();
  auto e2 = typename TestFixture::extents_type{};
  EXPECT_EQ(e, e2);
  for (size_t r = 0; r < e.rank(); ++r) {
    bool is_dynamic = (e.static_extent(r) == stdex::dynamic_extent);
    EXPECT_EQ(e.extent(r), is_dynamic ? 0 : e.static_extent(r));
  }
}

TYPED_TEST(TestExtents, array_ctor) {
  auto e = typename TestFixture::extents_type(this->dyn_sizes);
  EXPECT_EQ(e, this->exts);
}

TYPED_TEST(TestExtents, copy_ctor) {
  typename TestFixture::extents_type e { this->exts };
  EXPECT_EQ(e, this->exts);
}

TYPED_TEST(TestExtents, copy_assign) {
  typename TestFixture::extents_type e;
  e = this->exts;
  EXPECT_EQ(e, this->exts);
}

template <class> struct TestExtentsCompatCtors;
template <size_t... Extents, size_t... DynamicSizes, size_t... Extents2, size_t... DynamicSizes2>
struct TestExtentsCompatCtors<std::tuple<
  stdex::extents<Extents...>,
  std::integer_sequence<size_t, DynamicSizes...>,
  stdex::extents<Extents2...>,
  std::integer_sequence<size_t, DynamicSizes2...>
>> : public ::testing::Test {
  using extents_type1 = stdex::extents<Extents...>;
  using extents_type2 = stdex::extents<Extents2...>;
  extents_type1 exts1 { DynamicSizes... };
  extents_type2 exts2 { DynamicSizes2... };
};

using compatible_extents_test_types =
  ::testing::Types<
    std::tuple<_exts<stdex::dynamic_extent>, _sizes<10>, _exts<10>, _sizes<>>,
    //--------------------
    std::tuple<_exts<stdex::dynamic_extent, 10>, _sizes<5>, _exts<5, stdex::dynamic_extent>, _sizes<10>>,
    std::tuple<_exts<stdex::dynamic_extent, stdex::dynamic_extent>, _sizes<5, 10>, _exts<5, stdex::dynamic_extent>, _sizes<10>>,
    std::tuple<_exts<stdex::dynamic_extent, stdex::dynamic_extent>, _sizes<5, 10>, _exts<stdex::dynamic_extent, 10>, _sizes<5>>,
    std::tuple<_exts<stdex::dynamic_extent, stdex::dynamic_extent>, _sizes<5, 10>, _exts<5, 10>, _sizes<>>,
    std::tuple<_exts<5, 10>, _sizes<>, _exts<5, stdex::dynamic_extent>, _sizes<10>>,
    std::tuple<_exts<5, 10>, _sizes<>, _exts<stdex::dynamic_extent, 10>, _sizes<5>>,
    //--------------------
    std::tuple<_exts<stdex::dynamic_extent, stdex::dynamic_extent, 15>, _sizes<5, 10>, _exts<5, stdex::dynamic_extent, 15>, _sizes<10>>,
    std::tuple<_exts<5, 10, 15>, _sizes<>, _exts<5, stdex::dynamic_extent, 15>, _sizes<10>>,
    std::tuple<_exts<5, 10, 15>, _sizes<>, _exts<stdex::dynamic_extent, stdex::dynamic_extent, stdex::dynamic_extent>, _sizes<5, 10, 15>>
  >;

TYPED_TEST_SUITE(TestExtentsCompatCtors, compatible_extents_test_types);

TYPED_TEST(TestExtentsCompatCtors, compatible_construct_1) {
  auto e1 = typename TestFixture::extents_type1(this->exts2);
  EXPECT_EQ(e1, this->exts2);
}

TYPED_TEST(TestExtentsCompatCtors, compatible_construct_2) {
  auto e2 = typename TestFixture::extents_type2(this->exts1);
  EXPECT_EQ(e2, this->exts1);
}

TYPED_TEST(TestExtentsCompatCtors, compatible_assign_1) {
  this->exts1 = this->exts2;
  EXPECT_EQ(this->exts1, this->exts2);
}

TYPED_TEST(TestExtentsCompatCtors, compatible_assign_2) {
  this->exts2 = this->exts1;
  EXPECT_EQ(this->exts1, this->exts2);
}

TEST(TestExtentsCtorStdArrayConvertibleToSizeT, test_extents_ctor_std_array_convertible_to_size_t) {
  std::array<int, 2> i{2, 2};
  stdex::dextents<2> e{i};
  ASSERT_EQ(e.rank(), 2);
  ASSERT_EQ(e.rank_dynamic(), 2);
  ASSERT_EQ(e.extent(0), 2);
  ASSERT_EQ(e.extent(1), 2);
}

#if defined(_MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION)
TEST(TestExtentsCTADPack, test_extents_ctad_pack) {
  stdex::extents m0;
  ASSERT_EQ(m0.rank(), 0);
  ASSERT_EQ(m0.rank_dynamic(), 0);

  stdex::extents m1(64);
  ASSERT_EQ(m1.rank(), 1);
  ASSERT_EQ(m1.rank_dynamic(), 1);
  ASSERT_EQ(m1.extent(0), 64);

  stdex::extents m2(64, 128);
  ASSERT_EQ(m2.rank(), 2);
  ASSERT_EQ(m2.rank_dynamic(), 2);
  ASSERT_EQ(m2.extent(0), 64);
  ASSERT_EQ(m2.extent(1), 128);

  stdex::extents m3(64, 128, 256);
  ASSERT_EQ(m3.rank(), 3);
  ASSERT_EQ(m3.rank_dynamic(), 3);
  ASSERT_EQ(m3.extent(0), 64);
  ASSERT_EQ(m3.extent(1), 128);
  ASSERT_EQ(m3.extent(2), 256);
}

// TODO: It appears to currently be impossible to write a deduction guide that
// makes this work.
/*
TEST(TestExtentsCTADStdArray, test_extents_ctad_std_array) {
  stdex::extents m0{std::array<size_t, 0>{}};
  ASSERT_EQ(m0.rank(), 0);
  ASSERT_EQ(m0.rank_dynamic(), 0);

  // TODO: `extents` should accept an array of any type convertible to `size_t`.
  stdex::extents m1{std::array{64UL}};
  ASSERT_EQ(m1.rank(), 1);
  ASSERT_EQ(m1.rank_dynamic(), 1);
  ASSERT_EQ(m1.extent(0), 64);

  // TODO: `extents` should accept an array of any type convertible to `size_t`.
  stdex::extents m2{std::array{64UL, 128UL}};
  ASSERT_EQ(m2.rank(), 2);
  ASSERT_EQ(m2.rank_dynamic(), 2);
  ASSERT_EQ(m2.extent(0), 64);
  ASSERT_EQ(m2.extent(1), 128);

  // TODO: `extents` should accept an array of any type convertible to `size_t`.
  stdex::extents m3{std::array{64UL, 128UL, 256UL}};
  ASSERT_EQ(m3.rank(), 3);
  ASSERT_EQ(m3.rank_dynamic(), 3);
  ASSERT_EQ(m3.extent(0), 64);
  ASSERT_EQ(m3.extent(1), 128);
  ASSERT_EQ(m3.extent(2), 256);
}
*/
#endif
