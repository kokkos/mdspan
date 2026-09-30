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
#include <mdspan/mdarray.hpp>
#include <vector>

#include <gtest/gtest.h>
#include "offload_utils.hpp"

namespace KokkosEx = MDSPAN_IMPL_STANDARD_NAMESPACE::MDSPAN_IMPL_PROPOSED_NAMESPACE;

_MDSPAN_INLINE_VARIABLE constexpr auto dyn = MDSPAN_IMPL_STANDARD_NAMESPACE::dynamic_extent;

template<class ValueType, std::size_t Extent>
_MDSPAN_HOST_DEVICE
void fill_values(ValueType values[Extent])
{
  for (std::size_t k = 0; k < Extent; ++k) {
    values[k] = static_cast<ValueType>(1) + static_cast<ValueType>(k);
  }
}

template<class ValueType, std::size_t Extent0, std::size_t Extent1>
_MDSPAN_HOST_DEVICE
void fill_values(ValueType values[Extent0][Extent1])
{
  std::size_t k = 0;
  for (std::size_t r = 0; r < Extent0; ++r) {
    for (std::size_t c = 0; c < Extent1; ++c, ++k) {
      values[r][c] = static_cast<ValueType>(1) + static_cast<ValueType>(k);
    }
  }
}

template<class ValueType, std::size_t Extent0, std::size_t Extent1, std::size_t Extent2>
_MDSPAN_HOST_DEVICE
void fill_values(ValueType values[Extent0][Extent1][Extent2])
{
  std::size_t k = 0;
  for (std::size_t x = 0; x < Extent0; ++x) {
    for (std::size_t y = 0; y < Extent1; ++y) {
      for (std::size_t z = 0; z < Extent2; ++z, ++k) {
        values[x][y][z] = static_cast<ValueType>(1) + static_cast<ValueType>(k);
      }
    }
  }
}

struct ErrorBufferDeleter {
  void operator() (std::size_t* ptr) const {
    free_array(ptr);
  }
};

std::unique_ptr<std::size_t, ErrorBufferDeleter> allocate_error_buffer() {
  return {allocate_array<std::size_t>(1u), ErrorBufferDeleter{}};
}

template<class ValueType, std::size_t Extent>
void test_mdarray_ctad_carray_rank1() {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::extents;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::layout_right;

  auto error_buffer = allocate_error_buffer();
  {
    std::size_t* errors = error_buffer.get();
    errors[0] = 0;
    dispatch([errors] _MDSPAN_HOST_DEVICE () {
      ValueType values[Extent];
      fill_values<ValueType, Extent>(values);

      KokkosEx::mdarray m{values};
      static_assert(std::is_same_v<typename decltype(m)::extents_type,
                    extents<std::size_t, Extent>>);
      static_assert(std::is_same_v<typename decltype(m)::layout_type,
                    layout_right>);
      static_assert(std::is_same_v<typename decltype(m)::container_type,
                    std::array<ValueType, Extent>>);

      __MDSPAN_DEVICE_ASSERT_EQ(m.rank(), 1);
      __MDSPAN_DEVICE_ASSERT_EQ(m.rank_dynamic(), 0);
      __MDSPAN_DEVICE_ASSERT_EQ(m.extent(0), Extent);
      __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(0), Extent);

      for (std::size_t k = 0; k < Extent; ++k) {
#if defined(MDSPAN_USE_BRACKET_OPERATOR) && (MDSPAN_USE_BRACKET_OPERATOR != 0)
        __MDSPAN_DEVICE_ASSERT_EQ(m[k], values[k]);
#else
        __MDSPAN_DEVICE_ASSERT_EQ(m(k), values[k]);
#endif
      }
    });
    ASSERT_EQ(errors[0], 0);
  }
}

template<class ValueType, std::size_t Extent0, std::size_t Extent1>
void test_mdarray_ctad_carray_rank2() {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::extents;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::layout_right;

  auto error_buffer = allocate_error_buffer();
  {
    std::size_t* errors = error_buffer.get();
    errors[0] = 0;
    dispatch([errors] _MDSPAN_HOST_DEVICE () {
      ValueType values[Extent0][Extent1];
      fill_values<ValueType, Extent0, Extent1>(values);

      KokkosEx::mdarray m{values};
      static_assert(std::is_same_v<typename decltype(m)::extents_type,
                    extents<std::size_t, Extent0, Extent1>>);
      static_assert(std::is_same_v<typename decltype(m)::layout_type,
                    layout_right>);
      static_assert(std::is_same_v<typename decltype(m)::container_type,
                    std::array<ValueType, Extent0 * Extent1>>);

      __MDSPAN_DEVICE_ASSERT_EQ(m.rank(), 2);
      __MDSPAN_DEVICE_ASSERT_EQ(m.rank_dynamic(), 0);
      __MDSPAN_DEVICE_ASSERT_EQ(m.extent(0), Extent0);
      __MDSPAN_DEVICE_ASSERT_EQ(m.extent(1), Extent1);
      __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(0), Extent0);
      __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(1), Extent1);

      for (std::size_t r = 0; r < Extent0; ++r) {
        for (std::size_t c = 0; c < Extent1; ++c) {
#if defined(MDSPAN_USE_BRACKET_OPERATOR) && (MDSPAN_USE_BRACKET_OPERATOR != 0)
          __MDSPAN_DEVICE_ASSERT_EQ(m[r, c], values[r][c]);
#else
          __MDSPAN_DEVICE_ASSERT_EQ(m(r, c), values[r][c]);
#endif
        }
      }
    });
    ASSERT_EQ(errors[0], 0);
  }
}

template<class ValueType, std::size_t Extent0, std::size_t Extent1, std::size_t Extent2>
void test_mdarray_ctad_carray_rank3() {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::extents;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::layout_right;

  auto error_buffer = allocate_error_buffer();
  {
    std::size_t* errors = error_buffer.get();
    errors[0] = 0;
    dispatch([errors] _MDSPAN_HOST_DEVICE () {
      ValueType values[Extent0][Extent1][Extent2];
      fill_values<ValueType, Extent0, Extent1, Extent2>(values);

      KokkosEx::mdarray m{values};
      static_assert(std::is_same_v<typename decltype(m)::extents_type,
                    extents<std::size_t, Extent0, Extent1, Extent2>>);
      static_assert(std::is_same_v<typename decltype(m)::layout_type,
                    layout_right>);
      static_assert(std::is_same_v<typename decltype(m)::container_type,
                    std::array<ValueType, Extent0 * Extent1 * Extent2>>);

      __MDSPAN_DEVICE_ASSERT_EQ(m.rank(), 3);
      __MDSPAN_DEVICE_ASSERT_EQ(m.rank_dynamic(), 0);
      __MDSPAN_DEVICE_ASSERT_EQ(m.extent(0), Extent0);
      __MDSPAN_DEVICE_ASSERT_EQ(m.extent(1), Extent1);
      __MDSPAN_DEVICE_ASSERT_EQ(m.extent(2), Extent2);
      __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(0), Extent0);
      __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(1), Extent1);
      __MDSPAN_DEVICE_ASSERT_EQ(m.static_extent(2), Extent2);

      for (std::size_t x = 0; x < Extent0; ++x) {
        for (std::size_t y = 0; y < Extent1; ++y) {
          for (std::size_t z = 0; z < Extent2; ++z) {
#if defined(MDSPAN_USE_BRACKET_OPERATOR) && (MDSPAN_USE_BRACKET_OPERATOR != 0)
            __MDSPAN_DEVICE_ASSERT_EQ((m[x, y, z]), values[x][y][z]);
#else
            __MDSPAN_DEVICE_ASSERT_EQ((m(x, y, z)), values[x][y][z]);
#endif
          }
        }
      }
    });
    ASSERT_EQ(errors[0], 0);
  }
}

TEST(TestMdarrayCtorDataCArray, test_mdarray_carray_ctad) {
  __MDSPAN_TESTS_RUN_TEST((test_mdarray_ctad_carray_rank1<float, 5>()))
  __MDSPAN_TESTS_RUN_TEST((test_mdarray_ctad_carray_rank2<float, 3, 4>()))
  __MDSPAN_TESTS_RUN_TEST((test_mdarray_ctad_carray_rank3<float, 3, 4, 5>()))
}

#if 0
TEST(TestMdarrayCtorInitializerList, Rank1) {
  using MDSPAN_IMPL_STANDARD_NAMESPACE::dextents;  
  using MDSPAN_IMPL_STANDARD_NAMESPACE::extents;
  using MDSPAN_IMPL_STANDARD_NAMESPACE::layout_right;

  auto error_buffer = allocate_error_buffer();
  {
    std::size_t* errors = error_buffer.get();
    errors[0] = 0;
    dispatch([errors] _MDSPAN_HOST_DEVICE () {
      KokkosEx::mdarray m{{1.0f, 2.0f, 3.0f}};
      static_assert(std::is_same_v<typename decltype(m)::extents_type,
                    dextents<std::size_t, 1>>);
      static_assert(std::is_same_v<typename decltype(m)::layout_type,
                    layout_right>);
      static_assert(std::is_same_v<typename decltype(m)::container_type,
                    std::vector<float>>);

      __MDSPAN_DEVICE_ASSERT_EQ(m.rank(), 1);
      __MDSPAN_DEVICE_ASSERT_EQ(m.rank_dynamic(), 1);
      __MDSPAN_DEVICE_ASSERT_EQ(m.extent(0), 3);

      for (std::size_t k = 0; k < 3; ++k) {
#if defined(MDSPAN_USE_BRACKET_OPERATOR) && (MDSPAN_USE_BRACKET_OPERATOR != 0)
        __MDSPAN_DEVICE_ASSERT_EQ(m[k], (static_cast<float>(k) + 1.0f));
#else
        __MDSPAN_DEVICE_ASSERT_EQ(m(k), (static_cast<float>(k) + 1.0f));        
#endif
      }
    });
    ASSERT_EQ(errors[0], 0);
  }
}
#endif // 0
