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

#include <cassert>
#include <iostream>
#include <type_traits>

namespace stdex = std::experimental;

namespace details {

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

} // namespace details

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


// This layout is like layout_left,
// except that stride(0) == 1 always,
// and the leftmost extent may be padded
// (so that stride(1) could possibly be greater than extent(0)).
//
// This layout exists for two reasons:
//
// 1. Appropriate choice of padding, plus use of overaligned memory,
//    can ensure any desired power-of-two overalignment of the
//    beginning of each contiguous segment of elements in an mdspan.
//    This is useful for hardware that optimizes for overaligned
//    access.
//
// 2. For rank-2 mdspan, this is exactly the layout supported by the
//    BLAS and LAPACK (where the "leading dimension" of the matrix
//    (LDA), i.e., the stride, is greater than or equal to the number
//    of rows).
//
// The padding can be either a compile-time value or a run-time value.
// It is a template parameter of layout_left_padded (the "tag type"),
// and NOT of the mapping, because mdspan requires that the mapping be
// a metafunction of the tag type and the extents specialization type.
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

    struct unusable_tag_t {};
    static constexpr unusable_tag_t unusable_tag{};

  public:
    // mapping constructor that takes ONLY an extents_type.
    //
    // This constructor ONLY EXISTS if padding is known
    // at compile time, that is, if (the template parameter)
    // padding != dynamic_extent.
    //
    // This constructor makes it possible to construct an mdspan
    // from a pointer and extents, since that requires that
    // the mapping be constructible from extents alone.
    template<class T = unusable_tag_t>
    MDSPAN_INLINE_FUNCTION constexpr
    mapping(const extents_type& ext,
	    std::enable_if_t<padding != stdex::dynamic_extent
	    and std::is_same_v<T, unusable_tag_t>
	    , unusable_tag_t> = unusable_tag) :
      inner_mapping_(details::pad_extents_left(ext, padding_extents_type{padding})),
      pre_padded_extent_(ext.extent(0))
    {}

    // mapping constructor that takes an extents_type,
    // AND an integral padding_value.
    //
    // This constructor always exists, even if padding is known at
    // compile time -- just like the extents constructor lets you pass
    // in all rank() extents, even if some of them are known at
    // compile time.
    //
    // If padding is NOT known at compile time
    // (i.e., the template parameter padding equals dynamic_extent),
    // then you MUST pass it into the constructor,
    // either as an integral value (the first constructor below),
    // or as an extents object of the right type
    // (the second constructor below).

    template<class Size>
    MDSPAN_INLINE_FUNCTION constexpr
    mapping(const extents_type& ext,
	    std::enable_if_t<padding == stdex::dynamic_extent &&
	      std::is_integral_v<Size>,
	    Size> padding_value = 0) :
      inner_mapping_(details::pad_extents_left(ext, padding_extents_type{padding_value})),
      pre_padded_extent_(ext.extent(0))
    {
      // We don't have to check padding_value here, because the
      // padding_extents_type constructor already has a precondition.
    }

    // It's always legal to pass in the padding as an extents object.
    MDSPAN_INLINE_FUNCTION
    mapping(const extents_type& ext, const padding_extents_type& padding_extents) :
      inner_mapping_(details::pad_extents_left(ext, padding_extents)),
      pre_padded_extent_(ext.extent(0))
    {}

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

  // Uncomment to test that constructing a padding=dynamic_extent
  // mapping without a padding value is forbidden at compile time.
  //
  //if constexpr (PaddedExtent == stdex::dynamic_extent) {
  //  mapping_type mapping2(input);
  //}

  if constexpr (PaddedExtent != stdex::dynamic_extent) {
    mapping_type mapping2(input);
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
  test_layout_left_padded<std::int64_t>();
  test_layout_left_padded<std::uint64_t>();
  test_layout_left_padded<std::int32_t>();
  test_layout_left_padded<std::uint32_t>();
  test_layout_left_padded<std::int16_t>();
  test_layout_left_padded<std::uint16_t>();

  return 0;
}
