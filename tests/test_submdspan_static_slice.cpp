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
#include <cstdint>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

namespace {

namespace stdex = std::experimental;

template<class ExpectedOutputMdspan, class InputMdspan, class ... Slices>
void test_submdspan_static_slice(
  typename InputMdspan::extents_type input_extents,
  Slices&&... slices)
{
  using input_type = InputMdspan;
  using input_mapping_type = typename input_type::mapping_type;
  input_mapping_type input_mapping(input_extents);
  std::vector<typename InputMdspan::value_type> storage(input_mapping.required_span_size());

  input_type input(storage.data(), input_mapping);
  auto output = stdex::submdspan(input, std::forward<Slices>(slices)...);
  using output_mdspan_type = decltype(output);
  static_assert(std::is_same_v<typename output_mdspan_type::extents_type, typename ExpectedOutputMdspan::extents_type>, "Extents don't match.");
  static_assert(std::is_same_v<typename output_mdspan_type::layout_type, typename ExpectedOutputMdspan::layout_type>, "Layouts don't match.");
  static_assert(std::is_same_v<output_mdspan_type, ExpectedOutputMdspan>, "submdspan return types don't match.");
}

TEST(TestMdspan, submdspan_static_slice_full_index) {
  static_assert(std::is_convertible<std::integral_constant<std::size_t, 1>, std::size_t>::value, "Just a check.");
  static_assert(std::is_convertible<std::integral_constant<int32_t, 1>, std::size_t>::value, "Just a check.");
  static_assert(std::is_convertible<std::integral_constant<uint32_t, 1>, std::size_t>::value, "Just a check.");

  using input_extents_type = stdex::dextents<int, 2>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  using expected_extents_type = stdex::dextents<int, 1>;
  using expected_layout_type = stdex::layout_left;
  using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

  input_extents_type input_extents{3, 4};
  test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, 1);
  test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, std::integral_constant<int, 1>{});
  test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, std::integral_constant<std::size_t, 1>{});
  test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, std::integral_constant<int64_t, 1>{});
  test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, std::integral_constant<uint32_t, 1>{});
}

TEST(TestMdspan, submdspan_static_slice_full_tuple) {
  // tuple of integral_constant, integral_constant is convertible to tuple of size_t, size_t.
  // Nevertheless, submdspan won't compile out of the box with the former.
  static_assert(std::is_convertible<
      std::tuple<std::integral_constant<std::size_t, 1>, std::integral_constant<std::size_t, 3>>,
      std::tuple<std::size_t, std::size_t>
    >::value, "Just a check.");
  std::tuple<std::size_t, std::size_t> t = std::tuple<std::integral_constant<std::size_t, 1>, std::integral_constant<std::size_t, 3>>{};

  using input_extents_type = stdex::dextents<int, 2>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  using expected_extents_type = stdex::dextents<int, 2>;
  using expected_layout_type = stdex::layout_left;
  using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

  input_extents_type input_extents{3, 4};
  test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, std::tuple<std::size_t, std::size_t>{1, 3});
  // This doesn't compile yet.
  test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, std::tuple<std::integral_constant<std::size_t, 1>, std::integral_constant<std::size_t, 3>> {} );
}

}
