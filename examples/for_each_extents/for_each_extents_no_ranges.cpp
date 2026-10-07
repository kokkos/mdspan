#include <mdspan/mdspan.hpp>
#include <array>
#include <iostream>
#include <tuple>
#include <type_traits>

// There's no separate feature test macro for the C++20 feature
// of lambdas with named template parameters (P0428R2).
#if __cplusplus >= 202002L
#  define MDSPAN_EXAMPLE_CAN_USE_LAMBDA_TEMPLATE_PARAM_LIST 1
#endif

// This example doesn't currently work with Clang,
// because Clang doesn't like structured binding results
// being captured by inner lambdas.
#if ! defined(__clang__) && defined(MDSPAN_EXAMPLE_CAN_USE_LAMBDA_TEMPLATE_PARAM_LIST)

//////////////////////////////////////////////////////////////////////////
// Part 1: Compile-time iteration
//////////////////////////////////////////////////////////////////////////

// C++20 lets you write lambdas with explicitly named template
// parameters (vs. C++14 lambdas with "auto" parameters).  If you have
// a lambda templated on <std::size_t ... Indices> that takes a
// std::index_sequence<Indices...> parameter, you can then call the
// lambda with the result of std::make_index_sequence<N>.  This calls
// the lambda with the template arguments 0, 1, 2, ..., N-1.  You can
// then use these as "loop indices" to "iterate" at compile time over
// a parameter pack.
//
// If you don't have C++20, you can replace the lambda with a
// separate, named helper function.
//
// Another approach would be to write a reusable "template for each".
// This example doesn't do that, but it could be useful for
// backporting or for documenting intent.

// Print all the elements of a parameter pack.
//
// This is a lambda and not a function because you can't
// straightforwardly use std::apply on templated nonmember functions
// (as it doesn't know which overload to use), but you can use it on
// generic lambdas.  See the example here:
//
// https://en.cppreference.com/w/cpp/utility/apply
auto print_pack = []<class ... InputTypes>(InputTypes&& ... input) {
  auto print_all = [&]<std::size_t ... Indices>( std::index_sequence<Indices...> ) {
    auto print_one = [&] (std::size_t index, auto&& in) {
      std::cout << in;
      if(index + 1 < sizeof...(Indices)) {
        std::cout << ", ";
      }
    };
    (print_one(Indices, input), ...);
  };
  std::cout << '(';
  print_all(std::make_index_sequence<sizeof...(InputTypes)>());
  std::cout << ")\n";
};

//////////////////////////////////////////////////////////////////////////
// Part 2: Splitting extents
//
// extents<integral-not-bool IndexType, size_t Extents...> is part of
// mdspan.  It can mix run-time and compile-time extents values.
//
// We can express multidimensional iteration recursively
// by splitting an extents object into two parts (left and right),
// and iterating over one part while fixing the other.
//////////////////////////////////////////////////////////////////////////

// Returns a new extents object representing
// all but the leftmost extent of e.
//
// extents<int, 2, 3, 4> -> extents<int, 3, 4>
// extents<int, dynamic_extent, 3, 4> -> extents<int, 3, 4>
//
// This example shows that you can do
// index arithmetic on an index sequence.
template<class IndexType, std::size_t ... Extents>
auto right_extents( Kokkos::extents<IndexType, Extents...> e )
{
  static_assert(sizeof...(Extents) != 0);
  return [&]<std::size_t ... Indices>( std::index_sequence<Indices...> ) {
    return Kokkos::extents<IndexType, e.static_extent(Indices + 1)...>{
      e.extent(Indices + 1)...
    }; 
  }( std::make_index_sequence<sizeof...(Extents) - 1>() );
}

// Return two things:
// 
// * the leftmost extent as an extents object, and
// * all the other (right) extents as a (single) extents object.
//
// Encoding the leftmost extent as an extents object
// lets us preserve its compile-time-ness.
//
// This needs to be a lambda or function object,
// not a templated function.
auto split_extents_at_leftmost =
  []<class IndexType, std::size_t... Extents>(Kokkos::extents<IndexType, Extents...> e)
{
  static_assert(sizeof...(Extents) != 0);
  Kokkos::extents<IndexType, e.static_extent(0)> left_ext(
    e.extent(0));
  return std::tuple{left_ext, right_extents(e)};
};

// right_extents can be implemented by overloading for
// extents<IndexType, LeftExtent, RightExtents...>.
// That approach doesn't work for left_extents.

// Returns a new extents object representing
// all but the rightmost extent of e.
template<class IndexType, std::size_t ... Extents>
auto left_extents( Kokkos::extents<IndexType, Extents...> e )
{
  static_assert(sizeof...(Extents) != 0);
  return [&]<std::size_t ... Indices>( std::index_sequence<Indices...> ) {
    return Kokkos::extents<IndexType, e.static_extent(Indices)...>{
      e.extent(Indices)...
    };
  }( std::make_index_sequence<sizeof...(Extents) - 1>() );
}

// This needs to be a lambda or function object, not a templated function.
auto split_extents_at_rightmost =
  []<class IndexType, std::size_t ... Extents>(Kokkos::extents<IndexType, Extents...> e)
{
  static_assert(sizeof...(Extents) != 0);
  Kokkos::extents<IndexType, e.static_extent(e.rank() - 1)> right_ext(
    e.extent(e.rank() - 1));
  return std::tuple{left_extents(e), right_ext};
};

//////////////////////////////////////////////////////////////////////////
// Part 3: Recursing on extents
//////////////////////////////////////////////////////////////////////////

// This is a loop over one extent (dimension).
// By packaging up lambdas that fix other extents,
// we can use this as a building block
// for iterating over all the extents of a multidimensional array.
// 
// This could also serve as a hook for passing along
// optimization information -- e.g., whether we want
// to apply "#pragma omp simd" to a particular extent.
template<class Callable, class IndexType, std::size_t Extent>
void for_each_one_extent(Callable&& callable, Kokkos::extents<IndexType, Extent> ext)
{
  // If it's a run-time extent, do a run-time loop.
  if constexpr(ext.static_extent(0) == Kokkos::dynamic_extent) {
    for(IndexType index = 0; index < ext.extent(0); ++index) {
      std::forward<Callable>(callable)(index);  
    }
  }
  else {
    // It's a compile-time extent, so use a fold expression
    // to "iterate at compile time."
    // This effectively unrolls the loop.
    //
    // Since we know the extent at compile time,
    // we could also apply other optimizations here,
    // like unrolling for specific SIMD widths.
    [&]<std::size_t ... Indices> ( std::index_sequence<Indices...> ) {
      (std::forward<Callable>(callable)(Indices), ...);
    }( std::make_index_sequence<Extent>() );
  }
}

// Call callable on each multidimensional index in the extents,
// iterating in row-major order.
template<class Callable, class IndexType, std::size_t ... Extents>
void for_each_in_extents_row_major(
  Callable&& callable,
  Kokkos::extents<IndexType, Extents...> ext)
{
  if constexpr(ext.rank() == 0) {
    return;
  } else if constexpr(ext.rank() == 1) {
    for_each_one_extent(callable, ext);
  } else {
    auto [left_exts, right_exts] = split_extents_at_leftmost(ext);
    auto inner = [&](auto... left_indices) {
      auto next = [&] (auto... right_indices) {
        // left_indices is really only one index here,
        // but it's still a parameter pack.
        // Writing the code this way suggests a more general approach.
        std::forward<Callable>(callable)(left_indices..., right_indices...);
      };
      for_each_in_extents_row_major(next, right_exts);
    };
    for_each_one_extent(inner, left_exts);
  }
}

// Call callable on each multidimensional index in the extents,
// iterating in column-major order.
//
// The implementation differs in only two places from the row-major version.
// This suggests a way to generalize.
//
// Overloading on extents<IndexType, LeftExtents..., RightExtent>
// works fine for the row major case, but not for the column major case.
template<class Callable, class IndexType, std::size_t ... Extents>
void for_each_in_extents_col_major(
  Callable&& callable,
  Kokkos::extents<IndexType, Extents...> ext)
{
  if constexpr(ext.rank() == 0) {
    return;
  } else if constexpr (ext.rank() == 1) {
    for_each_one_extent(callable, ext);
  } else {
    // 1. Split rightmost instead of leftmost.
    auto [left_exts, right_exts] = split_extents_at_rightmost(ext);
    auto inner = [&](auto... right_indices) {
      // 2. Put the left indices in the inner loop,
      //    instead of the right indices.
      auto next = [&] (auto... left_indices) {
        std::forward<Callable>(callable)(left_indices..., right_indices...);
      };
      for_each_in_extents_col_major(next, left_exts);
    };
    for_each_in_extents_col_major(inner, right_exts);
  }
}

//////////////////////////////////////////////////////////////////////////
// Part 4: Generalize iteration order
//////////////////////////////////////////////////////////////////////////

// We revise the above example
// by picking one iteration order as canonical
// (we've chosen row-major order above),
// and implementing other orders
// by changing the orders of extents and indices.

template<class Callable, class IndexType, std::size_t ... Extents,
  class ExtentsReorderer, class ExtentsSplitter, class IndicesReorderer>
void for_each_in_extents_impl(Callable&& callable,
  Kokkos::extents<IndexType, Extents...> ext,
  ExtentsReorderer reorder_extents,
  ExtentsSplitter split_extents,
  IndicesReorderer reorder_indices)
{
  if constexpr(ext.rank() == 0) {
    return;
  } else if constexpr(ext.rank() == 1) {
    for_each_one_extent(callable, ext);
  } else {
    // 1. Reorder the input extents.
    auto reordered_extents = reorder_extents(ext);

    // 2. Split into "left" and "right."
    //    For row-major and column-major, the resulting left_exts
    //    should always have rank 1 (i.e., only contain one extent).
    auto [left_exts, right_exts] = split_extents(reordered_extents);

    // 3. Create a lambda that loops over the right extents,
    //    and takes the left extent(s) as input.
    auto inner = [&] (auto... left_indices) {
      auto next = [&] (auto... right_indices) {
        // 4. "Fix" the order of indices to match
        //    the above reordering of extents.
        std::apply(std::forward<Callable>(callable),
          reorder_indices(left_indices..., right_indices...));
      };
      for_each_in_extents_impl(next, right_exts, reorder_extents,
                                 split_extents, reorder_indices);
    };

    // 5. Take the above lambda and loop over the left extent(s).
    for_each_in_extents_impl(inner, left_exts, reorder_extents,
                               split_extents, reorder_indices);
  }
}

auto extents_identity = []<class IndexType, std::size_t ... Extents>(
  Kokkos::extents<IndexType, Extents...> ext)
{
  return ext;
};

auto extents_reverse = []<class IndexType, std::size_t ... Extents>(
  Kokkos::extents<IndexType, Extents...> ext)
{
  constexpr std::size_t N = ext.rank();

  return [&]<std::size_t ... Indices>( std::index_sequence<Indices...> ) {
    return Kokkos::extents<
        IndexType,
        ext.static_extent(N - 1 - Indices)...
      >{ ext.extent(N - 1 - Indices)... };
  }( std::make_index_sequence<N>() );
};

// Return a parameter pack as a tuple.
auto indices_identity = [](auto... indices) {
  return std::tuple{indices...};
};

// Get the n-th item in a parameter pack,
// where n is a compile-time value.
template<std::size_t n, class ... Args>
auto get_pack(Args... args)
{
  std::common_type_t<decltype(args)...> result;
  std::size_t i = 0;
  return ((i++ == n ? (result = args, true) : false) || ...);
}

// Return the reverse of a parameter pack as a std::tuple.
auto indices_reverse = [](auto... args) {
  constexpr std::size_t N = sizeof...(args);

  return [&]<std::size_t ... Indices>( std::index_sequence<Indices...> ) {
    return std::tuple{ get_pack<N - 1 - Indices>(args)... };
  }( std::make_index_sequence<N>() );
};

// Row-major iteration
template<class Callable, class IndexType, std::size_t ... Extents>
void for_each_in_extents(Callable&& callable,
  Kokkos::extents<IndexType, Extents...> ext,
  Kokkos::layout_right)
{
  for_each_in_extents_impl(std::forward<Callable>(callable), ext,
    extents_identity, split_extents_at_leftmost, indices_identity);
}

// Column-major iteration
template<class Callable, class IndexType, std::size_t ... Extents>
void for_each_in_extents(Callable&& callable,
  Kokkos::extents<IndexType, Extents...> ext,
  Kokkos::layout_left)
{
  for_each_in_extents_impl(std::forward<Callable>(callable), ext,
    extents_reverse, split_extents_at_rightmost, indices_reverse);
}

#endif // ! defined(__clang__) && defined(MDSPAN_EXAMPLE_CAN_USE_LAMBDA_TEMPLATE_PARAM_LIST)

int main() {

#if ! defined(__clang__) && defined(MDSPAN_EXAMPLE_CAN_USE_LAMBDA_TEMPLATE_PARAM_LIST)
  // The functions work for any combination
  // of compile-time or run-time extents.
  Kokkos::extents<int, 3, Kokkos::dynamic_extent, 5> e{4};

  std::cout << "\nRow major:\n";
  for_each_in_extents_row_major(print_pack, e);

  std::cout << "\nColumn major\n";
  for_each_in_extents_col_major(print_pack, e);

  std::cout << "\nfor_each_in_extents: row major:\n";
  for_each_in_extents(print_pack, e, Kokkos::layout_right{});

  std::cout << "\nfor_each_in_extents: column major:\n";
  for_each_in_extents(print_pack, e, Kokkos::layout_left{});
#endif // defined(MDSPAN_EXAMPLE_CAN_USE_LAMBDA_TEMPLATE_PARAM_LIST)

  return 0;
}
