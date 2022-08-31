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

// Just checking __cpp_lib_int_pow2 isn't enough for some GCC versions.
// The <bit> header exists, but std::has_single_bit does not.
#if defined(__cpp_lib_int_pow2) && __cplusplus >= 202002L
#  include <bit>
#else
#  include <limits>
#endif
#include <cassert>
#include <iostream>
#include <type_traits>

#undef NDEBUG

namespace stdex = std::experimental;

enum class StorageOrder {
  LEFT, RIGHT
};

namespace details {

  // Reimplementation of std::bit_width (C++20, in <bit> header)
  // for pre-C++20 compilers.
  MDSPAN_INLINE_FUNCTION constexpr std::size_t my_bit_width(std::size_t x)
  {
    if(x == 0) {
      return 0;
    }
    constexpr std::size_t one(1);
    std::size_t result = 0;

    x = x >> one;
    while(x != 0) {
      ++result;
      x = x >> one;
    }
    return result + one;
  }

  MDSPAN_INLINE_FUNCTION constexpr std::size_t ceiling_power_of_two(const std::size_t x)
  {
#if defined(__cpp_lib_int_pow2) && __cplusplus >= 202002L
    // NOTE: Whether or not we can use bit_ceil depends on
    // whether bit_ceil is callable from device code.
    // If not, we always have the fall-back implementation below.
    return std::bit_ceil(x);
    #else
    if (x <= 1u) {
      return std::size_t(1);
    }
    return std::size_t(1) << my_bit_width(std::size_t(x - 1));
    #endif
  }

  // Returns the power of two p not less than d
  // such that p is divisible by overalignment_factor.
  // overalignment_factor must be a power of two.
  // Taking overalignment_factor by template parameter
  // lets us check at compile time whether it's a power of two,
  // even if this function is called in a non-(constant expression).
  template<std::size_t overalignment_factor>
  MDSPAN_INLINE_FUNCTION constexpr std::size_t round_up(
    const std::size_t d,
    std::integral_constant<std::size_t, overalignment_factor>)
  {
    static_assert(overalignment_factor != 0, "overalignment_factor must be nonzero.");
    static_assert(ceiling_power_of_two(overalignment_factor) == overalignment_factor,
		  "overalignment_factor must be a power of two.");

    const std::size_t power_of_two = ceiling_power_of_two(d);
    return power_of_two >= overalignment_factor ? power_of_two : overalignment_factor;
  }

  namespace {

    template<std::size_t Value>
    using IC = std::integral_constant<std::size_t, Value>;

    static_assert(round_up(3, IC<8>{}) == 8);
    static_assert(round_up(3, IC<2>{}) == 4);
    static_assert(round_up(3, IC<1>{}) == 4);

    static_assert(round_up(7, IC<16>{}) == 16);
    static_assert(round_up(7, IC<2>{}) == 8);
    static_assert(round_up(7, IC<1>{}) == 8);

  } // namespace (anonymous)

  // offset_index_sequence idea comes from "offset_sequence" here:
  // https://devblogs.microsoft.com/oldnewthing/20200625-00/?p=103903
  //
  // offset_index_sequence adds N to each element of the given IndexSequence.
  // We can't just template on the parameter pack of indices directly;
  // the pack needs to be contained in some type.
  // We choose index_sequence because it stores no run-time data.
  template<std::size_t N, class IndexSequence> struct offset_index_sequence;

  template<std::size_t N, std::size_t... Indices>
  struct offset_index_sequence<N, std::index_sequence<Indices...>>
  {
    using type = std::index_sequence<(Indices + N)...>;
  };

  template<std::size_t N, typename IndexSequence>
  using offset_index_sequence_t = typename offset_index_sequence<N, IndexSequence>::type;

  static_assert(std::is_same<
    offset_index_sequence_t<3, std::make_index_sequence<4>>,
    std::index_sequence<3, 4, 5, 6>>::value,
    "offset_index_sequence defined incorrectly." );

  // iota_index_sequence defines the half-open sequence
  // begin, begin+1, begin+2, ..., end-1.
  // If end == begin, then the sequence is empty (we permit this).
  //
  // Defining the struct first, rather than going straight to the type alias,
  // lets us check the template arguments.
  template<std::size_t begin, std::size_t end>
  struct iota_index_sequence {
    static_assert(end >= begin, "end must be >= begin.");
    using type = offset_index_sequence_t< begin, std::make_index_sequence<end - begin> >;
  };

  // iota_index_sequence_t is like make_index_sequence,
  // except that it starts with begin instead of 0.
  template<std::size_t begin, std::size_t end>
  using iota_index_sequence_t = typename iota_index_sequence<begin, end>::type;

  static_assert(std::is_same<
		iota_index_sequence_t<3, 6>,
		std::index_sequence<3, 4, 5>>::value,
		"iota_index_sequence defined incorrectly." );

  static_assert(std::is_same<
		iota_index_sequence_t<3, 3>,
		std::index_sequence<>>::value,
		"iota_index_sequence defined incorrectly." );

  static_assert(std::is_same<
		iota_index_sequence_t<3, 4>,
		std::index_sequence<3>>::value,
		"iota_index_sequence defined incorrectly." );

  // InputExtentsType is a specialization of extents.
  template<class InputExtentsType, std::size_t Index, std::size_t overalignment_factor>
  MDSPAN_INLINE_FUNCTION constexpr std::size_t
  round_up_static_extent(std::integral_constant<std::size_t, overalignment_factor> overalignment)
  {
    return InputExtentsType::static_extent(Index) == stdex::dynamic_extent ?
      stdex::dynamic_extent :
      round_up(InputExtentsType::static_extent(Index), overalignment);
  }

  // These "helper" functions work around compilers not having support
  // for templated lambdas []<size_t... Indices>{},
  // that would otherwise let us write the body of the helper function in place
  // in pad_extents.

  // For a column-major mdspan, we need to pad the leftmost extent.
  //
  // Indices needs to be a sequence 1, 2, ..., rank-1.
  template<std::size_t overalignment_factor,
    class InputExtentsType, std::size_t ... Indices>
  MDSPAN_INLINE_FUNCTION constexpr auto
  pad_extents_helper(InputExtentsType input,
		     std::index_sequence<Indices...> /* indices */,
		     std::integral_constant<StorageOrder, StorageOrder::LEFT> /* order */,
		     std::integral_constant<std::size_t, overalignment_factor> overalignment)
  {
    using input_type = std::remove_cv_t<std::remove_reference_t<InputExtentsType>>;
    constexpr std::size_t rank = input_type::rank();
    static_assert(sizeof...(Indices) == std::size_t(rank - 1), "Indices pack has the wrong size.");

    using index_type = typename input_type::index_type;
    using return_type = stdex::extents<index_type,
      round_up_static_extent<input_type, 0>(overalignment),
      input_type::static_extent(Indices)...>;

    const std::size_t rounded_up_extent = round_up(input.extent(0), overalignment);
    assert(std::size_t(std::numeric_limits<index_type>::max()) >= rounded_up_extent);

    return return_type{index_type(rounded_up_extent), input.extent(Indices)...};
  }

  // For a row-major mdspan, we need to pad the rightmost extent.
  //
  // Indices needs to be a sequence 0, 1, ..., rank-2.
  template<std::size_t overalignment_factor,
    class InputExtentsType, std::size_t ... Indices>
  MDSPAN_INLINE_FUNCTION constexpr auto
  pad_extents_helper(InputExtentsType input,
		     std::index_sequence<Indices...> indices,
		     std::integral_constant<StorageOrder, StorageOrder::RIGHT> /* order */,
		     std::integral_constant<std::size_t, overalignment_factor> overalignment)
  {
    using input_type = std::remove_cv_t<std::remove_reference_t<InputExtentsType>>;
    constexpr std::size_t rank = input_type::rank();
    static_assert(sizeof...(Indices) == std::size_t(rank - 1), "Indices pack has the wrong size.");

    using index_type = typename input_type::index_type;
    using return_type = stdex::extents<index_type,
      input_type::static_extent(Indices)...,
      round_up_static_extent<input_type, rank - 1>(overalignment)>;

    const std::size_t rounded_up_extent = round_up(input.extent(rank - 1), overalignment);
    assert(std::size_t(std::numeric_limits<index_type>::max()) >= rounded_up_extent);

    return return_type{input.extent(Indices)..., index_type(rounded_up_extent)};
  }

} // namespace details

// Rank-0 and rank-1 mdspan don't need extra padding from their layout.
// They rely on an "aligned_accessor" and on the data_handle's alignment.

MDSPAN_TEMPLATE_REQUIRES(
  std::size_t overalignment_factor,
  StorageOrder order,
  class IndexType, std::size_t ... Extents,
  /* requires */ (sizeof...(Extents) <= std::size_t(1))
)
MDSPAN_INLINE_FUNCTION constexpr auto
pad_extents(const stdex::extents<IndexType, Extents...>& input,
	    std::integral_constant<StorageOrder, order> /* order */,
	    std::integral_constant<std::size_t, overalignment_factor> /* overalignment */ )
{
  return input;
}

// Rank-2 or greater mdspan need to pad one extent.
// Column-major (LEFT) mdspan need to pad the leftmost extent.
// Row-major (RIGHT) mdspan need to pad the rightmost extent.
//
// These overloads are _not_ recursive; pad_extents_helper exists
// only because we can't do "[]<size_t...>{}" lambdas in C++ < 20.

MDSPAN_TEMPLATE_REQUIRES(
  std::size_t overalignment_factor,
  class IndexType, std::size_t ... Extents,
  /* requires */ (sizeof...(Extents) > std::size_t(1))
)
MDSPAN_INLINE_FUNCTION constexpr auto
pad_extents(const stdex::extents<IndexType, Extents...>& input,
	    std::integral_constant<StorageOrder, StorageOrder::LEFT> order,
	    std::integral_constant<std::size_t, overalignment_factor> overalignment)
{
  constexpr std::size_t rank = sizeof...(Extents);
  return details::pad_extents_helper(input, details::iota_index_sequence_t<1, rank>{}, order, overalignment);
}

MDSPAN_TEMPLATE_REQUIRES(
  std::size_t overalignment_factor,
  class IndexType, std::size_t ... Extents,
  /* requires */ (sizeof...(Extents) > std::size_t(1))
)
MDSPAN_INLINE_FUNCTION constexpr auto
pad_extents(const stdex::extents<IndexType, Extents...>& input,
	    std::integral_constant<StorageOrder, StorageOrder::RIGHT> order,
	    std::integral_constant<std::size_t, overalignment_factor> overalignment)
{
  constexpr std::size_t rank = sizeof...(Extents);
  return details::pad_extents_helper(input, details::iota_index_sequence_t<0, rank - 1>{}, order, overalignment);
}

// pad_extents tests

template<class InputExtentsType,
	 class ExpectedOutputExtentsType,
	 StorageOrder order,
	 std::size_t overalignment_factor>
void test_pad_extents(InputExtentsType input,
		      ExpectedOutputExtentsType expected_output,
		      const std::integral_constant<StorageOrder, order> storage_order,
		      const std::integral_constant<std::size_t, overalignment_factor> overalignment)
{
  auto output = pad_extents(input, storage_order, overalignment);
  static_assert(std::is_same<decltype(output), ExpectedOutputExtentsType>::value, "not same");
  assert(output == expected_output);
}

template<class IndexType>
void test_pad_extents_on_index()
{
  using stdex::extents;
  constexpr auto left = std::integral_constant<StorageOrder, StorageOrder::LEFT>{};
  constexpr auto right = std::integral_constant<StorageOrder, StorageOrder::RIGHT>{};
  constexpr auto dyn = stdex::dynamic_extent;
  {
    constexpr std::integral_constant<std::size_t, 4> overalignment_factor;

    test_pad_extents(extents<IndexType>{}, extents<IndexType>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType>{}, extents<IndexType>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3>{}, extents<IndexType, 3>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3>{}, extents<IndexType, 3>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn>{3}, extents<IndexType, dyn>{3}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn>{3}, extents<IndexType, dyn>{3}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, 5>{}, extents<IndexType, 4, 5>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, 5>{}, extents<IndexType, 3, 8>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn, 5>{3}, extents<IndexType, dyn, 5>{4}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn, 5>{3}, extents<IndexType, dyn, 8>{3}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, dyn>{5}, extents<IndexType, 4, dyn>{5}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, dyn>{5}, extents<IndexType, 3, dyn>{8}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn, dyn>{3, 5}, extents<IndexType, dyn, dyn>{4, 5}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn, dyn>{3, 5}, extents<IndexType, dyn, dyn>{3, 8}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, 5, 7>{}, extents<IndexType, 4, 5, 7>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, 5, 7>{}, extents<IndexType, 3, 5, 8>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn, 5, 7>{3}, extents<IndexType, dyn, 5, 7>{4}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn, 5, 7>{3}, extents<IndexType, dyn, 5, 8>{3}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, 5, dyn>{7}, extents<IndexType, 4, 5, dyn>{7}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, 5, dyn>{7}, extents<IndexType, 3, 5, dyn>{8}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, dyn, 7>{5}, extents<IndexType, 4, dyn, 7>{5}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, dyn, 7>{5}, extents<IndexType, 3, dyn, 8>{5}, right, overalignment_factor);
  }
  {
    constexpr std::integral_constant<std::size_t, 16> overalignment_factor;

    test_pad_extents(extents<IndexType>{}, extents<IndexType>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType>{}, extents<IndexType>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3>{}, extents<IndexType, 3>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3>{}, extents<IndexType, 3>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn>{3}, extents<IndexType, dyn>{3}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn>{3}, extents<IndexType, dyn>{3}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, 5>{}, extents<IndexType, 16, 5>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, 5>{}, extents<IndexType, 3, 16>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn, 5>{3}, extents<IndexType, dyn, 5>{16}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn, 5>{3}, extents<IndexType, dyn, 16>{3}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, dyn>{5}, extents<IndexType, 16, dyn>{5}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, dyn>{5}, extents<IndexType, 3, dyn>{16}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn, dyn>{3, 5}, extents<IndexType, dyn, dyn>{16, 5}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn, dyn>{3, 5}, extents<IndexType, dyn, dyn>{3, 16}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, 5, 7>{}, extents<IndexType, 16, 5, 7>{}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, 5, 7>{}, extents<IndexType, 3, 5, 16>{}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, dyn, 5, 7>{3}, extents<IndexType, dyn, 5, 7>{16}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, dyn, 5, 7>{3}, extents<IndexType, dyn, 5, 16>{3}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, 5, dyn>{7}, extents<IndexType, 16, 5, dyn>{7}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, 5, dyn>{7}, extents<IndexType, 3, 5, dyn>{16}, right, overalignment_factor);

    test_pad_extents(extents<IndexType, 3, dyn, 7>{5}, extents<IndexType, 16, dyn, 7>{5}, left, overalignment_factor);
    test_pad_extents(extents<IndexType, 3, dyn, 7>{5}, extents<IndexType, 3, dyn, 16>{5}, right, overalignment_factor);
  }
}

// layout_padded implementation

namespace details {

  template<StorageOrder order>
  struct storage_order_to_layout {};

  template<>
  struct storage_order_to_layout<StorageOrder::LEFT> {
    using type = stdex::layout_left;
  };

  template<>
  struct storage_order_to_layout<StorageOrder::RIGHT> {
    using type = stdex::layout_right;
  };

  template<StorageOrder order>
  using storage_order_to_layout_t = typename storage_order_to_layout<order>::type;

} // namespace details

// layout_padded is a strided mdspan layout
// that generalizes layout_left (for storage_order = LEFT)
// or layout_right (for storage_order = RIGHT),
// where the stride-1 extent (leftmost for LEFT, rightmost for RIGHT)
// is "padded" so that the corresponding stride
// (that is, the stride of the next extent over)
// is a multiple of the given overalignment_factor.
// When used in an mdspan with aligned_accessor
// and a pointer that is overaligned by the same overalignment_factor,
// the result is that the beginning of every contiguously stored
// sequence of elements of the mdspan is overaligned by overalignment_factor.
// This makes it possible, for example, to use aligned SIMD instructions
// without needing a loop prelude or postlude.
//
// If all the extents are stored as compile-time ("static") values,
// the strides will be computable at compile time.
//
// Preconditions:
//
// overalignment_factor must be either 1, or a (positive integer) power of two.
template<StorageOrder storage_order, std::size_t overalignment_factor>
struct layout_padded {
  static_assert(details::ceiling_power_of_two(overalignment_factor) == overalignment_factor,
		"overalignment_factor must be a power of 2");

  template <class Extents>
  class mapping {
  private:
    using inner_layout_type = details::storage_order_to_layout_t<storage_order>;
    static constexpr std::integral_constant<std::size_t, overalignment_factor> overalignment{};
    static constexpr std::integral_constant<StorageOrder, storage_order> order{};
    using padded_extents_type =
      decltype(pad_extents(std::declval<Extents>(), order, overalignment));
    using inner_mapping_type = typename inner_layout_type::template mapping<padded_extents_type>;

  public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_padded<storage_order, overalignment_factor>;

    // layout_stride::mapping deliberately only defines the copy constructor
    // and copy assignment operator.
    // This is fine, because all the storage is std::array-like;
    // there's no advantage to move construction or move assignment.
    // We imitate this.
    MDSPAN_INLINE_FUNCTION_DEFAULTED
    constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED
    constexpr mapping(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED
    mapping& operator=(const mapping&) noexcept = default;

    MDSPAN_INLINE_FUNCTION
    constexpr mapping(const extents_type& e) :
      extents_(e), inner_mapping_(pad_extents(e, order, overalignment))
    {}

    MDSPAN_INLINE_FUNCTION
    constexpr const extents_type& extents() const noexcept
    {
      return extents_;
    }

    MDSPAN_INLINE_FUNCTION
    constexpr std::array<index_type, extents_type::rank()>
    strides() const noexcept
    {
      return inner_mapping_.strides();
    }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type required_span_size() const noexcept
    {
      return inner_mapping_.required_span_size();
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class... Indices,
      /* requires */ (sizeof...(Indices) == Extents::rank() &&
        _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(std::is_convertible, Indices, index_type) /*&& ...*/ ) &&
	_MDSPAN_FOLD_AND(_MDSPAN_TRAIT(std::is_nothrow_constructible, index_type, Indices) /*&& ...*/)
      )
    )
    MDSPAN_FORCE_INLINE_FUNCTION
    constexpr size_t operator()(Indices... idxs) const noexcept {
      return inner_mapping_(std::forward<Indices>(idxs)...);
    }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept {
      return false; // just like layout_stride::mapping
    }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 bool is_exhaustive() const noexcept {
      return inner_mapping_.extents() == extents_;
    }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_strided() noexcept { return true; }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type stride(rank_type r) const noexcept {
      return inner_mapping_.stride(r);
    }

  private:
    extents_type extents_;
    inner_mapping_type inner_mapping_;
  };
};

// layout_padded tests

template<StorageOrder order,
	 std::size_t overalignment_factor,
	 class ExtentsType,
	 class ExpectedInnerExtentsType>
void test_layout_padded_one(std::vector<float>& storage,
			    std::integral_constant<StorageOrder, order>,
			    std::integral_constant<std::size_t, overalignment_factor>,
			    ExtentsType e,
			    ExpectedInnerExtentsType expected_inner_extents,
			    const bool expect_exhaustive)
{
  using layout_type = layout_padded<order, overalignment_factor>;
  using extents_type = ExtentsType;
  using expected_inner_extents_type = ExpectedInnerExtentsType;

  using mdspan_type = stdex::mdspan<float, extents_type, layout_type>;
  using mapping_type = typename mdspan_type::mapping_type;
  mapping_type mapping(e);

  {
    std::size_t product_of_extents = 1;
    for(std::size_t r = 0; r < e.rank(); ++r) {
      product_of_extents *= std::size_t(e.extent(r));
    }
    const size_t min_num_elements_storage = mapping.required_span_size();
    assert(min_num_elements_storage >= product_of_extents);
    if(storage.size() < min_num_elements_storage) {
      storage.resize(min_num_elements_storage);
    }
  }

  mdspan_type x(storage.data(), mapping);

  static_assert(std::is_same<mapping_type, typename layout_type::template mapping<extents_type>>::value,
		"layout_padded::mapping type wrong");
  static_assert(not mapping_type::is_always_exhaustive());
  static_assert(mapping_type::is_always_strided());
  static_assert(mapping_type::is_always_unique());
  assert(mapping.is_exhaustive() == expect_exhaustive);
  assert(mapping.is_strided());
  assert(mapping.is_unique());

  assert(e == x.extents());
  assert(e == x.mapping().extents());

  using expected_inner_layout_type = details::storage_order_to_layout_t<order>;
  using expected_inner_mapping_type =
    typename expected_inner_layout_type::template mapping<expected_inner_extents_type>;
  expected_inner_mapping_type expected_inner_mapping{expected_inner_extents};

  for (std::size_t r = 0; r < x.rank(); ++r) {
    assert(x.stride(r) == expected_inner_mapping.stride(r));
    assert(x.stride(r) == details::ceiling_power_of_two(x.stride(r)));
  }
}

void test_layout_padded()
{
  // storage will get resized as needed in the tests.
  std::vector<float> storage;

  constexpr std::integral_constant<StorageOrder, StorageOrder::LEFT> left{};
  constexpr std::integral_constant<StorageOrder, StorageOrder::RIGHT> right{};

  {
    constexpr std::integral_constant<std::size_t, 4> overalignment_factor{};
    using extents_type = stdex::extents<int, 3, 5>;
    extents_type e{};
    {
      using expected_inner_extents_type = stdex::extents<int, 4, 5>;
      expected_inner_extents_type expected_inner_extents{};
      const bool expect_exhaustive = false;
      test_layout_padded_one(storage, left, overalignment_factor, e, expected_inner_extents, expect_exhaustive);
    }
    {
      using expected_inner_extents_type = stdex::extents<int, 3, 8>;
      expected_inner_extents_type expected_inner_extents{};
      const bool expect_exhaustive = false;
      test_layout_padded_one(storage, right, overalignment_factor, e, expected_inner_extents, expect_exhaustive);
    }
  }
}

// layout_padded_left implementation

namespace details {

  // The *_helper functions work around not having C++20
  // templated lambdas: []<size_t... TrailingIndices>{} .

  template<class ReturnExtents,
	   class InnerExtents,
	   std::size_t... TrailingIndices>
  MDSPAN_INLINE_FUNCTION constexpr ReturnExtents
  layout_left_extents_helper(std::size_t pre_padded_extent,
			     const InnerExtents& inner_extents,
			     std::index_sequence<TrailingIndices...>)
  {
    static_assert(sizeof...(TrailingIndices) + 1 == ReturnExtents::rank(),
		  "sizeof...(TrailingIndices) != ReturnExtents::rank()");
    static_assert(InnerExtents::rank() == ReturnExtents::rank(),
		  "InnerExtents::rank() != ReturnExtents::rank()");
    using index_type = typename ReturnExtents::index_type;
    return ReturnExtents{index_type(pre_padded_extent),
			 index_type(inner_extents.extent(TrailingIndices))...};
  }

  template<class ReturnExtents,
	   class IndexType,
	   std::size_t... InnerExtents>
  MDSPAN_INLINE_FUNCTION constexpr ReturnExtents
  layout_left_extents(std::size_t pre_padded_extent,
		      const stdex::extents<IndexType, InnerExtents...>& inner_extents)
  {
    return layout_left_extents_helper<ReturnExtents>
      (pre_padded_extent, inner_extents,
       details::iota_index_sequence_t<1, ReturnExtents::rank()>{});
  }

  template<
    class InputExtentsType,
    std::size_t PaddingExtent,
    std::size_t ... Indices
  >
  MDSPAN_INLINE_FUNCTION constexpr auto
  pad_extents_left_helper(const InputExtentsType& input,
			  const stdex::extents<typename InputExtentsType::index_type, PaddingExtent>& padding,
			  std::index_sequence<Indices...>)
  {
    if constexpr (PaddingExtent == stdex::dynamic_extent) {
      assert(padding.extent(0) != stdex::dynamic_extent);
    }
    using input_type = std::remove_cv_t<std::remove_reference_t<InputExtentsType>>;
    using index_type = typename input_type::index_type;
    constexpr std::size_t rank = input_type::rank();
    static_assert(sizeof...(Indices) == std::size_t(rank - 1),
		  "Indices pack has the wrong size.");
    using return_type = stdex::extents<
      index_type,
      PaddingExtent,
      input_type::static_extent(Indices)...>;
    return return_type{index_type(padding.extent(0)), input.extent(Indices)...};
  }

  // Rank-0 and rank-1 mdspan don't need extra padding from their layout.
  // They rely on an "aligned_accessor" and on the data_handle's alignment.
  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType,
    std::size_t PaddingExtent,
    std::size_t ... InputExtents,
    /* requires */ (sizeof...(InputExtents) <= std::size_t(1))
  )
  MDSPAN_INLINE_FUNCTION constexpr auto
  pad_extents_left(const stdex::extents<IndexType, InputExtents...>& input,
		   const stdex::extents<IndexType, PaddingExtent> /* padding */ )
  {
    return input;
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType,
    std::size_t PaddingExtent,
    std::size_t ... InputExtents,
    /* requires */ (sizeof...(InputExtents) > std::size_t(1))
  )
  MDSPAN_INLINE_FUNCTION constexpr auto
  pad_extents_left(const stdex::extents<IndexType, InputExtents...>& input,
		   const stdex::extents<IndexType, PaddingExtent> padding)
  {
    constexpr std::size_t rank = sizeof...(InputExtents);
    return details::pad_extents_left_helper
      (input, padding, details::iota_index_sequence_t<1, rank>{});
  }

} // namespace details

// TODO (mfh 2022/08/30) Private inheritance from layout_left::mapping
// would reduce inlining depth.

template<std::size_t padding = stdex::dynamic_extent>
struct layout_left_padded {
  template <class Extents>
  class mapping {
  public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_left_padded<padding>;

  private:
    using pre_padding_extents_type =
      stdex::extents<index_type, Extents::static_extent(0)>;
    using padding_extents_type = stdex::extents<index_type, padding>;

    using inner_layout_type = stdex::layout_left;
    using inner_extents_type =
      decltype(details::pad_extents_left(std::declval<Extents>(),
					 std::declval<padding_extents_type>()));
    using inner_mapping_type =
      typename inner_layout_type::template mapping<inner_extents_type>;

    inner_mapping_type inner_mapping_;
    pre_padding_extents_type pre_padded_extent_;

  public:
    // precondition on padding_extents_ constructor lets
    // implementations check the padding value at run time.

    /*
    MDSPAN_INLINE_FUNCTION
    mapping(const extents_type& ext, std::size_t padding_value) :
      inner_mapping_(details::pad_extents_left(ext, padding_extents_type{padding_value})),
      pre_padded_extent_(ext.extent(0))
    {}
    */

    MDSPAN_INLINE_FUNCTION
    mapping(const extents_type& ext, const padding_extents_type& padding_extents) :
      inner_mapping_(details::pad_extents_left(ext, padding_extents)),
      pre_padded_extent_(ext.extent(0))
    {}

    // If padding is known at compile time (i.e., is not
    // dynamic_extent), then you don't need to pass it into the
    // constructor.  This makes it possible to construct an mdspan
    // from a pointer and extents (since that requires that the
    // mapping be constructible from extents alone).  Note that if you
    // don't have at least C++20, the constraint will turn into a
    // mandate.
    MDSPAN_INLINE_FUNCTION
#if __cplusplus >= 202002L
    requires(padding != stdex::dynamic_extent)
#endif
    mapping(const extents_type& ext) :
      inner_mapping_(details::pad_extents_left(ext, padding_extents_type{padding})),
      pre_padded_extent_(ext.extent(0))
    {
#if __cplusplus < 202002L
      static_assert(padding != stdex::dynamic_extent,
		    "You can't use this constructor if padding is dynamic_extent.");
#endif
    }

    // layout_stride::mapping deliberately only defines the copy
    // constructor and copy assignment operator, not the move
    // constructor or move assignment operator.  This is fine because
    // all the storage is std::array-like; there's no advantage to
    // move construction or move assignment.  We imitate this.
    MDSPAN_INLINE_FUNCTION_DEFAULTED
    constexpr mapping(const mapping&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED
    mapping& operator=(const mapping&) noexcept = default;

    MDSPAN_INLINE_FUNCTION
    constexpr extents_type extents() const noexcept
    {
      return details::layout_left_extents<extents_type>
	(pre_padded_extent_.extent(0), inner_mapping_.extents());
    }

    MDSPAN_INLINE_FUNCTION
    constexpr std::array<index_type, extents_type::rank()>
    strides() const noexcept
    {
      return inner_mapping_.strides();
    }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type required_span_size() const noexcept
    {
      return inner_mapping_.required_span_size();
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class... Indices,
      /* requires */ (sizeof...(Indices) == Extents::rank() &&
        _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(std::is_convertible, Indices, index_type) /*&& ...*/ ) &&
	_MDSPAN_FOLD_AND(_MDSPAN_TRAIT(std::is_nothrow_constructible, index_type, Indices) /*&& ...*/)
      )
    )
    MDSPAN_FORCE_INLINE_FUNCTION
    constexpr size_t operator()(Indices... idxs) const noexcept {
      // TODO (mfh 2022/08/30) in debug mode, check precondition before forwarding to inner mapping.
      return inner_mapping_(std::forward<Indices>(idxs)...);
    }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept {
      return extents_type::static_extent(0) != stdex::dynamic_extent &&
	extents_type::static_extent(0) == pre_padding_extents_type::static_extent(0);
    }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 bool is_exhaustive() const noexcept {
      return inner_mapping_.extent(0) == pre_padded_extent_.extent(0);
    }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_strided() noexcept { return true; }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type stride(rank_type r) const noexcept {
      return inner_mapping_.stride(r);
    }
  };
};

template<
  class IndexType,
  std::size_t PaddedExtent,
  std::size_t ... InputExtents
>
void
test_one_layout_left_padded(std::vector<float>& storage,
			    const stdex::extents<IndexType, InputExtents...>& input,
			    const stdex::extents<IndexType, PaddedExtent>& padding)
{
  static_assert(sizeof...(InputExtents) >= std::size_t(1),
		"input must have rank at least 1.");
  using input_extents_type = stdex::extents<IndexType, InputExtents...>;
  using rank_type = typename input_extents_type::rank_type;
  constexpr rank_type rank = input_extents_type::rank();

  assert(input.extent(0) <= padding.extent(0));

  using layout_type = layout_left_padded<PaddedExtent>;
  using mapping_type =
    typename layout_type::template mapping<input_extents_type>;
  using mdspan_type = stdex::mdspan<float, input_extents_type, layout_type>;
  static_assert(std::is_same<typename mdspan_type::mapping_type, mapping_type>::value,
		"wrong mapping_type");
  static_assert(std::is_same<typename mapping_type::extents_type, input_extents_type>::value,
		"mapping_type::extents_type != input_extents_type");

  auto test_mapping = [&](const mapping_type& mapping) {
    {
      auto ext = mapping.extents();
      for (auto r = rank_type(0); r < rank; ++r) {
	assert(ext.extent(r) == input.extent(r));
      }
    }
    const std::size_t product_of_extents = [&]() {
      std::size_t prod = 1;
      for(std::size_t r = 0; r < input.rank(); ++r) {
	prod *= std::size_t(input.extent(r));
      }
      return prod;
    }();
    const size_t min_num_elements_storage = mapping.required_span_size();
    assert(min_num_elements_storage >= product_of_extents);

    std::array<std::size_t, rank> expected_strides;
    expected_strides[0] = 1;
    if (rank > 1) {
      expected_strides[1] = padding.extent(0);
      for (auto r = rank_type(2); r < rank; ++r) {
	expected_strides[r] = expected_strides[r - 1] * input.extent(r - 1);
      }
    }

    for (auto r = rank_type(0); r < rank; ++r) {
      assert(mapping.stride(r) == expected_strides[r]);
      assert(mapping.stride(r) == expected_strides[r]);
    }
  };

  mapping_type mapping1(input, padding);
  test_mapping(mapping1);

  if constexpr (PaddedExtent != stdex::dynamic_extent) {
    mapping_type mapping2(input, padding);
    test_mapping(mapping2);
  }
}

template<class IndexType>
void test_layout_left_padded()
{
  constexpr auto dyn = stdex::dynamic_extent;
  // storage will get resized as needed in the tests.
  std::vector<float> storage;

  {
    using input_extents_type = stdex::extents<IndexType, 3>;
    input_extents_type input{};
    {
      using padding_extents_type = stdex::extents<IndexType, 8>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{8};
      test_one_layout_left_padded(storage, input, padding);
    }
    { // padding doesn't need to be a power of two
      using padding_extents_type = stdex::extents<IndexType, 17>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{17};
      test_one_layout_left_padded(storage, input, padding);
    }
  }

  {
    using input_extents_type = stdex::extents<IndexType, 3, 5>;
    input_extents_type input{};
    {
      using padding_extents_type = stdex::extents<IndexType, 8>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{8};
      test_one_layout_left_padded(storage, input, padding);
    }
    { // padding doesn't need to be a power of two
      using padding_extents_type = stdex::extents<IndexType, 17>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{17};
      test_one_layout_left_padded(storage, input, padding);
    }
  }

  {
    using input_extents_type = stdex::extents<IndexType, 3, 5, 7>;
    input_extents_type input{};
    {
      using padding_extents_type = stdex::extents<IndexType, 8>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{8};
      test_one_layout_left_padded(storage, input, padding);
    }
    { // padding doesn't need to be a power of two
      using padding_extents_type = stdex::extents<IndexType, 17>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{17};
      test_one_layout_left_padded(storage, input, padding);
    }
  }

  {
    using input_extents_type = stdex::extents<IndexType, dyn, 5, 7>;
    input_extents_type input{3};
    {
      using padding_extents_type = stdex::extents<IndexType, 8>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{8};
      test_one_layout_left_padded(storage, input, padding);
    }
    { // padding doesn't need to be a power of two
      using padding_extents_type = stdex::extents<IndexType, 17>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{17};
      test_one_layout_left_padded(storage, input, padding);
    }
  }

  {
    using input_extents_type = stdex::extents<IndexType, 3, dyn, 7>;
    input_extents_type input{5};
    {
      using padding_extents_type = stdex::extents<IndexType, 8>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{8};
      test_one_layout_left_padded(storage, input, padding);
    }
    { // padding doesn't need to be a power of two
      using padding_extents_type = stdex::extents<IndexType, 17>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{17};
      test_one_layout_left_padded(storage, input, padding);
    }
  }

  {
    using input_extents_type = stdex::extents<IndexType, 3, 5, dyn>;
    input_extents_type input{7};
    {
      using padding_extents_type = stdex::extents<IndexType, 8>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{8};
      test_one_layout_left_padded(storage, input, padding);
    }
    { // padding doesn't need to be a power of two
      using padding_extents_type = stdex::extents<IndexType, 17>;
      padding_extents_type padding{};
      test_one_layout_left_padded(storage, input, padding);
    }
    {
      using padding_extents_type = stdex::extents<IndexType, dyn>;
      padding_extents_type padding{17};
      test_one_layout_left_padded(storage, input, padding);
    }
  }
}

int main()
{
  static_assert(details::my_bit_width(0) == 0);
  static_assert(details::my_bit_width(1) == 1);
  static_assert(details::my_bit_width(2) == 2);
  static_assert(details::my_bit_width(5) == 3);
  static_assert(details::my_bit_width(7) == 3);
  static_assert(details::my_bit_width(8) == 4);

  static_assert(details::ceiling_power_of_two(3) == std::size_t(4));
  static_assert(details::ceiling_power_of_two(2) == std::size_t(2));
  static_assert(details::ceiling_power_of_two(1) == std::size_t(1));

  test_pad_extents_on_index<std::int64_t>();
  test_pad_extents_on_index<std::uint64_t>();
  test_pad_extents_on_index<std::int32_t>();
  test_pad_extents_on_index<std::uint32_t>();
  test_pad_extents_on_index<std::int16_t>();
  test_pad_extents_on_index<std::uint16_t>();

  test_layout_padded();

  test_layout_left_padded<int>();

  return 0;
}
