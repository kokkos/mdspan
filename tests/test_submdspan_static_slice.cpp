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

template<class Integral, Integral Value>
using IC = std::integral_constant<Integral, Value>;

template<class ExpectedOutputMdspan, class InputMdspan, class ... Slices>
void test_submdspan_static_slice(
  typename InputMdspan::mapping_type input_mapping,
  Slices&&... slices)
{
  using input_type = InputMdspan;
  std::vector<typename InputMdspan::value_type> storage(input_mapping.required_span_size());

  input_type input(storage.data(), input_mapping);
  auto output = stdex::submdspan(input, std::forward<Slices>(slices)...);
  using output_mdspan_type = decltype(output);
  static_assert(std::is_same<typename output_mdspan_type::extents_type, typename ExpectedOutputMdspan::extents_type>::value, "Extents don't match.");
  static_assert(std::is_same<typename output_mdspan_type::layout_type, typename ExpectedOutputMdspan::layout_type>::value, "Layouts don't match.");
  static_assert(std::is_same<output_mdspan_type, ExpectedOutputMdspan>::value, "submdspan return types don't match.");
}

template<class ExpectedOutputMdspan, class InputMdspan, class ... Slices>
void test_submdspan_static_slice(
  typename InputMdspan::extents_type input_extents,
  Slices&&... slices)
{
  using input_mapping_type = typename InputMdspan::mapping_type;
  input_mapping_type input_mapping(input_extents);
  test_submdspan_static_slice<ExpectedOutputMdspan, InputMdspan>(input_mapping, std::forward<Slices>(slices)...);
}

TEST(TestMdspan, StaticAsserts) {
  static_assert(std::is_convertible<IC<std::size_t, 1>, std::size_t>::value, "Just a check.");
  static_assert(std::is_convertible<IC<int32_t, 1>, std::size_t>::value, "Just a check.");
  static_assert(std::is_convertible<IC<uint32_t, 1>, std::size_t>::value, "Just a check.");
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_iddd_FullFullIndex) {
  using input_extents_type = stdex::dextents<int, 3>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents{3, 4, 5};

  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto integralConstant) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
	input_extents, stdex::full_extent, stdex::full_extent, integralConstant);
    };
    runTest(int(1));
    runTest(std::size_t(1));
    runTest(std::int64_t(1));
    runTest(std::uint32_t(1));
    runTest(IC<int, 1>{});
    runTest(IC<std::size_t, 1>{});
    runTest(IC<std::int64_t, 1>{});
    runTest(IC<std::uint32_t, 1>{});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_i345_FullFullIndex) {
  using input_extents_type = stdex::extents<int, 3, 4, 5>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents;

  {
    using expected_extents_type = stdex::extents<int, 3, 4>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto integralConstant) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
	input_extents, stdex::full_extent, stdex::full_extent, integralConstant);
    };
    runTest(int(1));
    runTest(std::size_t(1));
    runTest(std::int64_t(1));
    runTest(std::uint32_t(1));
    runTest(IC<int, 1>{});
    runTest(IC<std::size_t, 1>{});
    runTest(IC<std::int64_t, 1>{});
    runTest(IC<std::uint32_t, 1>{});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_iddd_FullFullIndex) {
  using input_extents_type = stdex::dextents<int, 3>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents{3, 4, 5};

  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
	input_extents, stdex::full_extent, stdex::full_extent, sliceSpec);
    };
    runTest(int(1));
    runTest(std::size_t(1));
    runTest(std::int64_t(1));
    runTest(std::uint32_t(1));
    runTest(IC<int, 1>{});
    runTest(IC<std::size_t, 1>{});
    runTest(IC<std::int64_t, 1>{});
    runTest(IC<std::uint32_t, 1>{});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_i345_FullFullIndex) {
  using input_extents_type = stdex::extents<int, 3, 4, 5>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents;

  {
    using expected_extents_type = stdex::extents<int, 3, 4>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto integralConstant) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
	input_extents, stdex::full_extent, stdex::full_extent, integralConstant);
    };
    runTest(int(1));
    runTest(std::size_t(1));
    runTest(std::int64_t(1));
    runTest(std::uint32_t(1));
    runTest(IC<int, 1>{});
    runTest(IC<std::size_t, 1>{});
    runTest(IC<std::int64_t, 1>{});
    runTest(IC<std::uint32_t, 1>{});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_iddd_FullIndexFull) {
  using input_extents_type = stdex::dextents<int, 3>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents{3, 4, 5};

  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto integralConstant) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, integralConstant, stdex::full_extent);
    };
    runTest(int(1));
    runTest(std::size_t(1));
    runTest(std::int64_t(1));
    runTest(std::uint32_t(1));
    runTest(IC<int, 1>{});
    runTest(IC<std::size_t, 1>{});
    runTest(IC<std::int64_t, 1>{});
    runTest(IC<std::uint32_t, 1>{});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_i345_FullIndexFull) {
  using input_extents_type = stdex::extents<int, 3, 4, 5>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents;

  {
    using expected_extents_type = stdex::extents<int, 3, 5>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto integralConstant) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, integralConstant, stdex::full_extent);
    };
    runTest(int(1));
    runTest(std::size_t(1));
    runTest(std::int64_t(1));
    runTest(std::uint32_t(1));
    runTest(IC<int, 1>{});
    runTest(IC<std::size_t, 1>{});
    runTest(IC<std::int64_t, 1>{});
    runTest(IC<std::uint32_t, 1>{});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_iddd_FullTupleFull) {
  using std::tuple;
  using input_extents_type = stdex::dextents<int, 3>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents{3, 4, 5};

  {
    using expected_extents_type = stdex::dextents<int, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<int, int>{int(1), int{3}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent, 2, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}});
    runTest(tuple<IC<std::size_t,1 >, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_i345_FullTupleFull) {
  using std::tuple;
  using input_extents_type = stdex::extents<int, 3, 4, 5>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents;

  {
    using expected_extents_type = stdex::extents<int, 3, stdex::dynamic_extent, 5>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<int, int>{int(1), int{3}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 3, 2, 5>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}});
    runTest(tuple<IC<std::size_t,1 >, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_iddd_FullTupleFull) {
  using std::tuple;
  using input_extents_type = stdex::dextents<int, 3>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents{3, 4, 5};

  {
    using expected_extents_type = stdex::dextents<int, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<int, int>{int(1), int{3}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent, 2, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}});
    runTest(tuple<IC<std::size_t,1 >, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_i345_FullTupleFull) {
  using std::tuple;
  using input_extents_type = stdex::extents<int, 3, 4, 5>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents;

  {
    using expected_extents_type = stdex::extents<int, 3, stdex::dynamic_extent, 5>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<int, int>{int(1), int{3}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 3, 2, 5>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, stdex::full_extent, sliceSpec, stdex::full_extent);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}});
    runTest(tuple<IC<std::size_t,1 >, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_iddd_TupleFullTuple) {
  using std::tuple;
  using input_extents_type = stdex::dextents<int, 3>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents{3, 4, 5};

  {
    using expected_extents_type = stdex::dextents<int, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<int, int>{int{1}, int{3}}, tuple<int, int>{int{1}, int{4}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{3}}, tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{4}});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{3}}, tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{4}});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{3}}, tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{4}});
  }
  {
    using expected_extents_type = stdex::extents<int, 2, stdex::dynamic_extent, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}},
	    tuple<IC<int, 1>, IC<int, 4>>{IC<int, 1>{}, IC<int, 4>{}});
    runTest(tuple<IC<std::size_t, 1>, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}},
	    tuple<IC<std::size_t, 1>, IC<std::size_t, 4>>{IC<std::size_t, 1>{}, IC<std::size_t, 4>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}},
	    tuple<IC<std::int64_t, 1>, IC<std::int64_t, 4>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 4>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}},
	    tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 4>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 4>{}});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_i345_TupleFullTuple) {
  using std::tuple;
  using input_extents_type = stdex::extents<int, 3, 4, 5>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents;

  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent, 4, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<int, int>{int{1}, int{3}}, tuple<int, int>{int{1}, int{4}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{3}}, tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{4}});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{3}}, tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{4}});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{3}}, tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{4}});
  }
  {
    using expected_extents_type = stdex::extents<int, 2, 4, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}},
	    tuple<IC<int, 1>, IC<int, 4>>{IC<int, 1>{}, IC<int, 4>{}});
    runTest(tuple<IC<std::size_t, 1>, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}},
	    tuple<IC<std::size_t, 1>, IC<std::size_t, 4>>{IC<std::size_t, 1>{}, IC<std::size_t, 4>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}},
	    tuple<IC<std::int64_t, 1>, IC<std::int64_t, 4>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 4>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}},
	    tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 4>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 4>{}});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_iddd_TupleFullTuple) {
  using std::tuple;
  using input_extents_type = stdex::dextents<int, 3>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents{3, 4, 5};

  {
    using expected_extents_type = stdex::dextents<int, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<int, int>{int{1}, int{3}}, tuple<int, int>{int{1}, int{4}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{3}}, tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{4}});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{3}}, tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{4}});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{3}}, tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{4}});
  }
  {
    using expected_extents_type = stdex::extents<int, 2, stdex::dynamic_extent, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}},
	    tuple<IC<int, 1>, IC<int, 4>>{IC<int, 1>{}, IC<int, 4>{}});
    runTest(tuple<IC<std::size_t, 1>, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}},
	    tuple<IC<std::size_t, 1>, IC<std::size_t, 4>>{IC<std::size_t, 1>{}, IC<std::size_t, 4>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}},
	    tuple<IC<std::int64_t, 1>, IC<std::int64_t, 4>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 4>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}},
	    tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 4>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 4>{}});
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_i345_TupleFullTuple) {
  using std::tuple;
  using input_extents_type = stdex::extents<int, 3, 4, 5>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;
  input_extents_type input_extents;

  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent, 4, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<int, int>{int{1}, int{3}}, tuple<int, int>{int{1}, int{4}});
    runTest(tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{3}}, tuple<std::size_t, std::size_t>{std::size_t{1}, std::size_t{4}});
    runTest(tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{3}}, tuple<std::int64_t, std::int64_t>{std::int64_t{1}, std::int64_t{4}});
    runTest(tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{3}}, tuple<std::uint32_t, std::uint32_t>{std::uint32_t{1}, std::uint32_t{4}});
  }
  {
    using expected_extents_type = stdex::extents<int, 2, 4, 3>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&] (auto sliceSpec0, auto sliceSpec1) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(
        input_extents, sliceSpec0, stdex::full_extent, sliceSpec1);
    };
    runTest(tuple<IC<int, 1>, IC<int, 3>>{IC<int, 1>{}, IC<int, 3>{}},
	    tuple<IC<int, 1>, IC<int, 4>>{IC<int, 1>{}, IC<int, 4>{}});
    runTest(tuple<IC<std::size_t, 1>, IC<std::size_t, 3>>{IC<std::size_t, 1>{}, IC<std::size_t, 3>{}},
	    tuple<IC<std::size_t, 1>, IC<std::size_t, 4>>{IC<std::size_t, 1>{}, IC<std::size_t, 4>{}});
    runTest(tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 3>{}},
	    tuple<IC<std::int64_t, 1>, IC<std::int64_t, 4>>{IC<std::int64_t, 1>{}, IC<std::int64_t, 4>{}});
    runTest(tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 3>{}},
	    tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 4>>{IC<std::uint32_t, 1>{}, IC<std::uint32_t, 4>{}});
  }
}

// Simpler, rank-2 tests follow.  If you have a build regression,
// it may help to comment out all the tests but the ones below.

TEST(TestMdspan, SubmdspanStaticSlice_Left_idd_FullTuple) {
  // tuple of two integral_constant is convertible to tuple of two size_t.
  // Nevertheless, submdspan needs special handling to be able to compile
  // with a tuple of two integral_constant as a slice specifier.
  // For example, mdspan needs an overload of
  // __assign_op_slice_handler::operator=
  // in order for the output's extents type to be able to encode
  // the compile-time slice information.
  static_assert(std::is_convertible<std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>>,
                                    std::tuple<std::size_t, std::size_t>>::value, "convertability of tuples of integral constant to size_t is false");

  using input_extents_type = stdex::dextents<int, 2>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents{3, 4};
  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, sliceSpec);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent, 2>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, sliceSpec);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<uint32_t, 1>, IC<uint32_t, 3>> {} );
    runTest(std::tuple<IC<int64_t, 1>, IC<int64_t, 3>> {} );
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_idd_FullTuple) {
  using input_extents_type = stdex::dextents<int, 2>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents{3, 4};
  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, sliceSpec);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent, 2>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, stdex::full_extent, sliceSpec);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<uint32_t, 1>, IC<uint32_t, 3>> {} );
    runTest(std::tuple<IC<int64_t, 1>, IC<int64_t, 3>> {} );
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_idd_TupleFull) {
  using input_extents_type = stdex::dextents<int, 2>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents{3, 4};
  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec, stdex::full_extent);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 2, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec, stdex::full_extent);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>> {} );
    runTest(std::tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>> {} );
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_idd_TupleFull) {
  using input_extents_type = stdex::dextents<int, 2>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents{3, 4};
  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_right;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec, stdex::full_extent);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 2, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_right;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec, stdex::full_extent);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>> {} );
    runTest(std::tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>> {} );
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Stride_idd_TupleFull) {
  using input_extents_type = stdex::dextents<int, 2>;
  using input_layout_type = stdex::layout_stride;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents{3, 4};
  std::array<int, 2> input_strides{1, 4}; // like layout_left
  using input_mapping_type = typename input_mdspan_type::mapping_type;
  input_mapping_type input_mapping(input_extents, input_strides);
  {
    using expected_extents_type = stdex::dextents<int, 2>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_mapping, sliceSpec, stdex::full_extent);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 2, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_stride;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_mapping, sliceSpec, stdex::full_extent);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>> {} );
    runTest(std::tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>> {} );
  }
}

// Rank 1 tests

TEST(TestMdspan, SubmdspanStaticSlice_Left_id_Tuple) {
  using input_extents_type = stdex::extents<int, stdex::dynamic_extent>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents{5};
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 2>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>> {} );
    runTest(std::tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>> {} );
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Left_i5_Tuple) {
  using input_extents_type = stdex::extents<int, 5>;
  using input_layout_type = stdex::layout_left;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents;
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 2>;
    using expected_layout_type = stdex::layout_left;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>> {} );
    runTest(std::tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>> {} );
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_id_Tuple) {
  using input_extents_type = stdex::extents<int, stdex::dynamic_extent>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents{5};
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_right;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 2>;
    using expected_layout_type = stdex::layout_right;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>> {} );
    runTest(std::tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>> {} );
  }
}

TEST(TestMdspan, SubmdspanStaticSlice_Right_i5_Tuple) {
  using input_extents_type = stdex::extents<int, 5>;
  using input_layout_type = stdex::layout_right;
  using input_mdspan_type = stdex::mdspan<float, input_extents_type, input_layout_type>;

  input_extents_type input_extents;
  {
    using expected_extents_type = stdex::extents<int, stdex::dynamic_extent>;
    using expected_layout_type = stdex::layout_right;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<int, int>{int(1), int(3)});
    runTest(std::tuple<std::size_t, std::size_t>{std::size_t(1), std::size_t(3)});
    runTest(std::tuple<std::uint32_t, std::uint32_t>{std::uint32_t(1), std::uint32_t(3)});
    runTest(std::tuple<std::int64_t, std::int64_t>{std::int64_t(1), std::int64_t(3)});
  }
  {
    using expected_extents_type = stdex::extents<int, 2>;
    using expected_layout_type = stdex::layout_right;
    using expected_output_mdspan_type = stdex::mdspan<float, expected_extents_type, expected_layout_type>;

    auto runTest = [&](auto sliceSpec) {
      test_submdspan_static_slice<expected_output_mdspan_type, input_mdspan_type>(input_extents, sliceSpec);
    };
    runTest(std::tuple<IC<int, 1>, IC<int, 3>> {} );
    runTest(std::tuple<IC<std::size_t, 1>, IC<std::size_t, 3>> {} );
    runTest(std::tuple<IC<std::uint32_t, 1>, IC<std::uint32_t, 3>> {} );
    runTest(std::tuple<IC<std::int64_t, 1>, IC<std::int64_t, 3>> {} );
  }
}

} // namespace (anonymous)
