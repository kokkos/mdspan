/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
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

#include <tuple>
#include <utility>

namespace stdex = std::experimental;
_MDSPAN_INLINE_VARIABLE constexpr auto dyn = stdex::dynamic_extent;

template <class Extents>
size_t get_expected_mapping(
  typename stdex::layout_left::template mapping<Extents> const& map,
  size_t i, size_t j, size_t k
)
{
  auto const& extents = map.extents();
  return i + j*extents.extent(0) + k*extents.extent(0)*extents.extent(1);
}

template <class Extents>
size_t get_expected_mapping(
  typename stdex::layout_right::template mapping<Extents> const& map,
  size_t i, size_t j, size_t k
)
{
  auto const& extents = map.extents();
  return k + j*extents.extent(2) + i*extents.extent(1)*extents.extent(2);
}

template <class> struct TestLayout;

template <class Mapping, size_t... DynamicSizes>
struct TestLayout<std::tuple<
  Mapping,
  std::integer_sequence<size_t, DynamicSizes...>
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
  size_t expected_mapping(Index... idxs) const {
    return get_expected_mapping(map, idxs...);
  }
};

template <class Extents, size_t... DynamicSizes>
using test_3d_left_types = std::tuple<
  typename stdex::layout_left::template mapping<Extents>,
  std::integer_sequence<size_t, DynamicSizes...>
>;

template <class Extents, size_t... DynamicSizes>
using test_3d_right_types = std::tuple<
  typename stdex::layout_right::template mapping<Extents>,
  std::integer_sequence<size_t, DynamicSizes...>
>;

using layout_test_types_3d =
  ::testing::Types<
    test_3d_left_types<stdex::extents<3, 4, 5>>,
    test_3d_left_types<stdex::extents<5, 4, 3>>,
    test_3d_left_types<stdex::extents<3, 4, dyn>, 5>,
    test_3d_left_types<stdex::extents<5, 4, dyn>, 3>,
    test_3d_left_types<stdex::extents<3, dyn, 5>, 4>,
    test_3d_left_types<stdex::extents<5, dyn, 3>, 4>,
    test_3d_left_types<stdex::extents<dyn, 4, 5>, 3>,
    test_3d_left_types<stdex::extents<dyn, 4, 3>, 5>,
    test_3d_left_types<stdex::extents<dyn, dyn, 5>, 3, 4>,
    test_3d_left_types<stdex::extents<dyn, dyn, 3>, 5, 4>,
    test_3d_left_types<stdex::extents<dyn, 4, dyn>, 3, 5>,
    test_3d_left_types<stdex::extents<dyn, 4, dyn>, 5, 3>,
    test_3d_left_types<stdex::extents<3, dyn, dyn>, 4, 5>,
    test_3d_left_types<stdex::extents<5, dyn, dyn>, 4, 3>,
    test_3d_left_types<stdex::extents<dyn, dyn, dyn>, 3, 4, 5>,
    test_3d_left_types<stdex::extents<dyn, dyn, dyn>, 5, 4, 3>,
    test_3d_right_types<stdex::extents<3, 4, 5>>,
    test_3d_right_types<stdex::extents<5, 4, 3>>,
    test_3d_right_types<stdex::extents<3, 4, dyn>, 5>,
    test_3d_right_types<stdex::extents<5, 4, dyn>, 3>,
    test_3d_right_types<stdex::extents<3, dyn, 5>, 4>,
    test_3d_right_types<stdex::extents<5, dyn, 3>, 4>,
    test_3d_right_types<stdex::extents<dyn, 4, 5>, 3>,
    test_3d_right_types<stdex::extents<dyn, 4, 3>, 5>,
    test_3d_right_types<stdex::extents<dyn, dyn, 5>, 3, 4>,
    test_3d_right_types<stdex::extents<dyn, dyn, 3>, 5, 4>,
    test_3d_right_types<stdex::extents<dyn, 4, dyn>, 3, 5>,
    test_3d_right_types<stdex::extents<dyn, 4, dyn>, 5, 3>,
    test_3d_right_types<stdex::extents<3, dyn, dyn>, 4, 5>,
    test_3d_right_types<stdex::extents<5, dyn, dyn>, 4, 3>,
    test_3d_right_types<stdex::extents<dyn, dyn, dyn>, 3, 4, 5>,
    test_3d_right_types<stdex::extents<dyn, dyn, dyn>, 5, 4, 3>
  >;

template <class T> struct TestLayout3D : TestLayout<T> { };

TYPED_TEST_SUITE(TestLayout3D, layout_test_types_3d);

TYPED_TEST(TestLayout3D, mapping_works) {
  for(size_t i = 0; i < this->map.extents().extent(0); ++i) {
    for(size_t j = 0; j < this->map.extents().extent(1); ++j) {
      for(size_t k = 0; k < this->map.extents().extent(2); ++k) {
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

TEST(TestLayoutLeftListInitialization, test_layout_left_list_initialization) {
  double* data = nullptr;
  stdex::basic_mdspan<double, stdex::extents<dyn, dyn>, stdex::layout_left> m(data, {{16, 32}});
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(m.stride(1), 16);
  ASSERT_EQ(m.extent(0), 16);
  ASSERT_EQ(m.extent(1), 32);
}

// GCC 10 ICEs if I stick this in the body of the below test.
template <typename M>
void test_layout_left_ctad_gcc_10_workaround(M m) {
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(m.stride(1), 32);
  ASSERT_EQ(m.extent(0), 16);
  ASSERT_EQ(m.extent(1), 32);
}

TEST(TestLayoutLeftCTAD, test_layout_right_ctad) {
  double* data = nullptr;
  stdex::basic_mdspan m(data, stdex::layout_left::mapping{stdex::extents{16, 32}});
  test_layout_left_ctad_gcc_10_workaround(m);
}

TEST(TestLayoutRightListInitialization, test_layout_right_list_initialization) {
  double* data = nullptr;
  stdex::basic_mdspan<double, stdex::extents<dyn, dyn>, stdex::layout_right> m(data, {{16, 32}});
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.stride(0), 32);
  ASSERT_EQ(m.stride(1), 1);
  ASSERT_EQ(m.extent(0), 16);
  ASSERT_EQ(m.extent(1), 32);
}

// GCC 10 ICEs if I stick this in the body of the below test.
template <typename M>
void test_layout_right_ctad_gcc_10_workaround(M m) {
  ASSERT_EQ(m.rank(), 2);
  ASSERT_EQ(m.rank_dynamic(), 2);
  ASSERT_EQ(m.stride(0), 1);
  ASSERT_EQ(m.stride(1), 32);
  ASSERT_EQ(m.extent(0), 16);
  ASSERT_EQ(m.extent(1), 32);
}

TEST(TestLayoutRightCTAD, test_layout_right_ctad) {
  double* data = nullptr;
  stdex::basic_mdspan m(data, stdex::layout_right::mapping{stdex::extents{16, 32}});
  test_layout_right_ctad_gcc_10_workaround(m);
}
