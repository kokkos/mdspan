// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#pragma once

#include "../../mdspan/mdspan.hpp"
#include <cassert>
#include <vector>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
namespace MDSPAN_IMPL_PROPOSED_NAMESPACE {

namespace {
  template<class Extents>
  struct size_of_extents;

  template<class IndexType, size_t ... Extents>
  struct size_of_extents<extents<IndexType, Extents...>> {
    constexpr static size_t value() {
      size_t size = 1;
      for(size_t r=0; r<extents<IndexType, Extents...>::rank(); r++)
        size *= extents<IndexType, Extents...>::static_extent(r);
      return size;
    }
  };
}

namespace {
  template<class C>
  struct container_is_array :  std::false_type {
    template<class M>
    static constexpr C construct(const M& m) { return C(m.required_span_size()); }
  };
  template<class T, size_t N>
  struct container_is_array<std::array<T,N>> : std::true_type {
    template<class M>
    static constexpr std::array<T,N> construct(const M&) { return std::array<T,N>(); }
  };
}

namespace impl {

template<class CArray, std::size_t ... Indices> requires (
  std::is_array_v<CArray> &&
  std::rank_v<CArray> == 1u
  )
constexpr std::array<std::remove_all_extents_t<CArray>, std::extent_v<CArray, 0>>
carray_to_array_impl(CArray& values, std::index_sequence<Indices...>)
{
  return std::array{values[Indices]...};
}

template<class CArray> requires (
  std::is_array_v<CArray> &&
  std::rank_v<CArray> == 1u
  )
constexpr std::array<std::remove_all_extents_t<CArray>, std::extent_v<CArray, 0>>
carray_to_array(CArray& values)
{
  return carray_to_array_impl(values,
    std::make_index_sequence<std::extent_v<CArray, 0>>());
}

template<class ElementType, std::size_t Size, std::size_t ... Indices>
constexpr std::array<std::remove_cv_t<ElementType>, Size>
ptr_to_array_impl(ElementType values[],
  std::integral_constant<std::size_t, Size>,
  std::index_sequence<Indices...>)
{
  static_assert(! std::is_array_v<ElementType>);
  return {values[Indices]...};
}

template<std::size_t Index>
constexpr auto tail(std::index_sequence<Index>) {
  return std::index_sequence<>{};
}

template<std::size_t First, std::size_t ... Rest>
constexpr auto tail(std::index_sequence<First, Rest...>) {
  return std::index_sequence<Rest...>{};
}

// Forward declaration is necessary for "recursion"
// inside carray_to_array_impl.
template<class CArray> requires (
  std::is_array_v<CArray> &&
  std::rank_v<CArray> > 1u
  )
constexpr auto
carray_to_array(CArray& values);

template<class CArray, std::size_t ... Indices> requires (
  std::is_array_v<CArray> &&
  std::rank_v<CArray> > 1u
  )
constexpr auto
carray_to_array_impl(CArray& values, std::index_sequence<Indices...> seq)
  -> std::array<
    std::remove_all_extents_t<CArray>,
    ((std::extent_v<CArray, Indices>) * ...)
  >
{
  constexpr std::size_t rank = std::rank_v<CArray>;
  constexpr std::size_t size = ((std::extent_v<CArray, Indices>) * ...);
  if constexpr (size == 0) {
    return {}; // &values[0] is UB if values has zero length
  }
  else {
    std::array<std::remove_all_extents_t<CArray>, size> result;
    auto seq_tail = tail(seq);

    std::size_t curpos = 0;
    for (std::size_t row = 0; row < std::extent_v<CArray, 0>; ++row) {
      // For rank > 1, &values[row] is an array of one less rank, not
      // a pointer to the beginning of the data.  Multidimensional
      // "raw" (C) arrays aren't guaranteed to be contiguous anyway,
      // so we can't just copy `values` as a flat array).
      std::array values_row = carray_to_array(values[row]);
      for (std::size_t k = 0; k < values_row.size(); ++k, ++curpos) {
        result[curpos] = values_row[k];
      }
    }
    return result;
  }
}

template<class CArray> requires (
  std::is_array_v<CArray> &&
  std::rank_v<CArray> > 1u
  )
constexpr auto
carray_to_array(CArray& values)
{
  return carray_to_array_impl(values,
    std::make_index_sequence<std::rank_v<CArray>>());
}

template<class CArray, std::size_t ... Indices> requires (
  std::is_array_v<CArray> &&
  std::rank_v<CArray> >= 1u
)
constexpr auto
extents_of_carray_impl(CArray&, std::index_sequence<Indices...>) ->
  extents<std::size_t, std::extent_v<CArray, Indices>...>
{
  return {};
};

template<class CArray> requires (
  std::is_array_v<CArray> &&
  std::rank_v<CArray> >= 1u
)
constexpr auto
extents_of_carray(CArray& values)
{
  return extents_of_carray_impl(values, std::make_index_sequence<std::rank_v<CArray>>());
};

} // namespace impl

template <
  class ElementType,
  class Extents,
  class LayoutPolicy = layout_right,
  class Container = std::vector<ElementType>
>
class mdarray {
private:
  static_assert(::MDSPAN_IMPL_STANDARD_NAMESPACE::detail::impl_is_extents_v<Extents>,
                MDSPAN_IMPL_PROPOSED_NAMESPACE_STRING "::mdspan's Extents template parameter must be a specialization of " MDSPAN_IMPL_STANDARD_NAMESPACE_STRING "::extents.");

public:

  //--------------------------------------------------------------------------------
  // Domain and codomain types

  using extents_type = Extents;
  using layout_type = LayoutPolicy;
  using container_type = Container;
  using mapping_type = typename layout_type::template mapping<extents_type>;
  using element_type = ElementType;
  using mdspan_type = mdspan<element_type, extents_type, layout_type>;
  using const_mdspan_type = mdspan<const element_type, extents_type, layout_type>;
  using value_type = std::remove_cv_t<element_type>;
  using index_type = typename Extents::index_type;
  using size_type = typename Extents::size_type;
  using rank_type = typename Extents::rank_type;
  using pointer = typename container_type::pointer;
  using reference = typename container_type::reference;
  using const_pointer = typename container_type::const_pointer;
  using const_reference = typename container_type::const_reference;

public:

  //--------------------------------------------------------------------------------
  // [mdspan.basic.cons], mdspan constructors, assignment, and destructor

#if !(MDSPAN_HAS_CXX_20)
  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr),
    mdarray, (), ,
    /* requires */ (extents_type::rank_dynamic()!=0)) {}
#else
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray() requires(extents_type::rank_dynamic()!=0) = default;
#endif
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray(const mdarray&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray(mdarray&&) = default;

  // Constructors for container types constructible from a size
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      (::MDSPAN_IMPL_STANDARD_NAMESPACE::detail::are_valid_indices<index_type, SizeTypes...>()) &&
        MDSPAN_IMPL_TRAIT( std::is_constructible, extents_type, SizeTypes...) &&
      MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, extents_type) &&
      (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, size_t) ||
       container_is_array<container_type>::value) &&
      (extents_type::rank()>0 || extents_type::rank_dynamic()==0)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr mdarray(SizeTypes... dynamic_extents)
    : map_(extents_type(dynamic_extents...)), ctr_(container_is_array<container_type>::construct(map_))
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (const extents_type& exts), ,
    /* requires */ ((MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, size_t) ||
                     container_is_array<container_type>::value) &&
                    MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, extents_type))
  ) : map_(exts), ctr_(container_is_array<container_type>::construct(map_))
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (const mapping_type& m), ,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, size_t) ||
                    container_is_array<container_type>::value)
  ) : map_(m), ctr_(container_is_array<container_type>::construct(map_))
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (const extents_type& exts, const container_type& ctr), ,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, extents_type))
  ) : map_(exts), ctr_(ctr)
  { assert(ctr.size() >= static_cast<size_t>(map_.required_span_size())); }

  constexpr mdarray(const mapping_type& m, const container_type& ctr)
    : map_(m), ctr_(ctr)
  { assert(ctr.size() >= static_cast<size_t>(map_.required_span_size())); }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (const extents_type& exts, container_type&& ctr), ,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, extents_type))
  ) : map_(exts), ctr_(std::move(ctr))
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  constexpr mdarray(const mapping_type& m, container_type&& ctr)
    : map_(m), ctr_(std::move(ctr))
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }


  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherContainer,
    /* requires */ (
      MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, typename OtherLayoutPolicy::template mapping<OtherExtents>) &&
      MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, OtherContainer)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mdarray<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherContainer>& other)
    : map_(other.mapping()), ctr_(other.container())
  {
    static_assert( std::is_constructible<extents_type, OtherExtents>::value, "");
  }

  // Constructors for container types constructible from a size and allocator
  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, size_t, Alloc) &&
                    MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, extents_type))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const extents_type& exts, const Alloc& a)
    : map_(exts), ctr_(map_.required_span_size(), a)
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, size_t, Alloc))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mapping_type& map, const Alloc& a)
    : map_(map), ctr_(map_.required_span_size(), a)
  { }

  // Constructors for container types constructible from a container and allocator
  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, container_type, Alloc) &&
                    MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, extents_type))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const extents_type& exts, const container_type& ctr, const Alloc& a)
    : map_(exts), ctr_(ctr, a)
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, size_t, Alloc))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mapping_type& map, const container_type& ctr, const Alloc& a)
    : map_(map), ctr_(ctr, a)
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, container_type, Alloc) &&
                    MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, extents_type))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const extents_type& exts, container_type&& ctr, const Alloc& a)
    : map_(exts), ctr_(std::move(ctr), a)
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, size_t, Alloc))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mapping_type& map, container_type&& ctr, const Alloc& a)
    : map_(map), ctr_(std::move(ctr), a)
  { assert(ctr_.size() >= map_.required_span_size()); }

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherContainer, class Alloc,
    /* requires */ (
      MDSPAN_IMPL_TRAIT( std::is_constructible, mapping_type, typename OtherLayoutPolicy::template mapping<OtherExtents>) &&
      MDSPAN_IMPL_TRAIT( std::is_constructible, container_type, OtherContainer, Alloc)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mdarray<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherContainer>& other, const Alloc& a)
    : map_(other.mapping()), ctr_(other.container(), a)
  {
    static_assert( std::is_constructible<extents_type, OtherExtents>::value, "");
  }

#if 0
  // Corresponds to deduction guide from std::initializer_list<value_type>
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(std::initializer_list<value_type> values)
    : map_(extents_type{}), ctr_{values}
  {}
#endif // 0
  
  // Corresponds to deduction guide from C array
  MDSPAN_TEMPLATE_REQUIRES(
    class CArray,
    /* requires */ (
      std::is_array_v<CArray> &&
      std::rank_v<CArray> >= 1u
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(CArray& values)
    : map_(extents_type{}), ctr_{impl::carray_to_array(values)}
  {}

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray& operator= (const mdarray&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray& operator= (mdarray&&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~mdarray() = default;

  //--------------------------------------------------------------------------------
  // [mdspan.basic.mapping], mdspan mapping domain multidimensional index to access codomain element

  #if MDSPAN_USE_BRACKET_OPERATOR
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      MDSPAN_IMPL_FOLD_AND(MDSPAN_IMPL_TRAIT( std::is_convertible, SizeTypes, index_type) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator[](SizeTypes... indices) const noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      MDSPAN_IMPL_FOLD_AND(MDSPAN_IMPL_TRAIT( std::is_convertible, SizeTypes, index_type) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](SizeTypes... indices) noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }
  #endif

#if 0
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      MDSPAN_IMPL_TRAIT( std::is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator[](const std::array<SizeType, N>& indices) const noexcept
  {
    return impl::template callop<reference>(*this, indices);
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      MDSPAN_IMPL_TRAIT( std::is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](const std::array<SizeType, N>& indices) noexcept
  {
    return impl::template callop<reference>(*this, indices);
  }
#endif


  #if MDSPAN_USE_PAREN_OPERATOR
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
        (::MDSPAN_IMPL_STANDARD_NAMESPACE::detail::are_valid_indices<index_type, SizeTypes...>()) &&
        extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator()(SizeTypes... indices) const noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
        (::MDSPAN_IMPL_STANDARD_NAMESPACE::detail::are_valid_indices<index_type, SizeTypes...>()) &&
        extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(SizeTypes... indices) noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }

#if 0
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      MDSPAN_IMPL_TRAIT( std::is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator()(const std::array<SizeType, N>& indices) const noexcept
  {
    return impl::template callop<reference>(*this, indices);
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      MDSPAN_IMPL_TRAIT( std::is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(const std::array<SizeType, N>& indices) noexcept
  {
    return impl::template callop<reference>(*this, indices);
  }
#endif
  #endif

  MDSPAN_INLINE_FUNCTION constexpr pointer data() noexcept { return ctr_.data(); }
  MDSPAN_INLINE_FUNCTION constexpr const_pointer data() const noexcept { return ctr_.data(); }
  MDSPAN_INLINE_FUNCTION constexpr container_type& container() noexcept { return ctr_; }
  MDSPAN_INLINE_FUNCTION constexpr const container_type& container() const noexcept { return ctr_; }

  //--------------------------------------------------------------------------------
  // [mdspan.basic.domobs], mdspan observers of the domain multidimensional index space

  MDSPAN_INLINE_FUNCTION static constexpr rank_type rank() noexcept { return extents_type::rank(); }
  MDSPAN_INLINE_FUNCTION static constexpr rank_type rank_dynamic() noexcept { return extents_type::rank_dynamic(); }
  MDSPAN_INLINE_FUNCTION static constexpr size_t static_extent(size_t r) noexcept { return extents_type::static_extent(r); }

  MDSPAN_INLINE_FUNCTION constexpr const extents_type& extents() const noexcept { return map_.extents(); }
  MDSPAN_INLINE_FUNCTION constexpr index_type extent(size_t r) const noexcept { return map_.extents().extent(r); }
  MDSPAN_INLINE_FUNCTION constexpr index_type size() const noexcept {
//    return impl::size(*this);
    return ctr_.size();
  }


  //--------------------------------------------------------------------------------
  // [mdspan.basic.obs], mdspan observers of the mapping

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept { return mapping_type::is_always_exhaustive(); }
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return mapping_type::is_always_strided(); }

  MDSPAN_INLINE_FUNCTION constexpr const mapping_type& mapping() const noexcept { return map_; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return map_.is_unique(); }
  MDSPAN_INLINE_FUNCTION constexpr bool is_exhaustive() const noexcept { return map_.is_exhaustive(); }
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return map_.is_strided(); }
  MDSPAN_INLINE_FUNCTION constexpr index_type stride(size_t r) const { return map_.stride(r); }

  // Converstion to mdspan
  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents,
    class OtherLayoutType, class OtherAccessorType,
    /* requires */ (
      MDSPAN_IMPL_TRAIT(std::is_assignable,
                      mdspan<OtherElementType, OtherExtents, OtherLayoutType, OtherAccessorType>,
                      mdspan_type)
    )
  )
  constexpr operator mdspan<OtherElementType, OtherExtents, OtherLayoutType, OtherAccessorType> () {
    return mdspan_type(data(), map_);
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents,
    class OtherLayoutType, class OtherAccessorType,
    /* requires */ (
      MDSPAN_IMPL_TRAIT(std::is_assignable,
                      mdspan<OtherElementType, OtherExtents, OtherLayoutType, OtherAccessorType>,
                      const_mdspan_type)
    )
  )
  constexpr operator mdspan<OtherElementType, OtherExtents, OtherLayoutType, OtherAccessorType> () const {
    return const_mdspan_type(data(), map_);
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherAccessorType = default_accessor<element_type>,
    /* requires */ (
      MDSPAN_IMPL_TRAIT(std::is_assignable, mdspan_type,
                      mdspan<element_type, extents_type, layout_type, OtherAccessorType>)
    )
  )
  constexpr mdspan<element_type, extents_type, layout_type, OtherAccessorType>
    to_mdspan(const OtherAccessorType& a = default_accessor<element_type>()) {
      return mdspan<element_type, extents_type, layout_type, OtherAccessorType>(data(), map_, a);
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherAccessorType = default_accessor<const element_type>,
    /* requires */ (
      MDSPAN_IMPL_TRAIT(std::is_assignable, const_mdspan_type,
                      mdspan<const element_type, extents_type, layout_type, OtherAccessorType>)
    )
  )
  constexpr mdspan<const element_type, extents_type, layout_type, OtherAccessorType>
    to_mdspan(const OtherAccessorType& a = default_accessor<const element_type>()) const {
      return mdspan<const element_type, extents_type, layout_type, OtherAccessorType>(data(), map_, a);
  }

private:
  mapping_type map_;
  container_type ctr_;

  template <class, class, class, class>
  friend class mdarray;
};

// Rank >= 1 C array -> layout_right mdarray
// with container_type = std::array
template<class CArray>
requires (std::is_array_v<CArray> && std::rank_v<CArray> >= 1u)
mdarray(CArray& values) -> mdarray<
  std::remove_all_extents_t<CArray>,
  decltype(impl::extents_of_carray(values)),
  layout_right,
  decltype(impl::carray_to_array(values))
>;

#if 0
// Adding a deduction guide from initializer_list<T> breaks the above
// C array deduction guide, because construction from
// initializer_list<T> catches every possible creation of an mdarray
// from curly braces.
//
// We may not know values.size() at compile time,
// so we have to use a dynamically allocated container.
template<class T>
mdarray(std::initializer_list<T> values) ->
mdarray<
  std::remove_cvref_t<T>,
  dextents<std::size_t, 1>,
  layout_right,
  std::vector<std::remove_cvref_t<T>>
>;
#endif // 0  

} // end namespace MDSPAN_IMPL_PROPOSED_NAMESPACE
} // end namespace MDSPAN_IMPL_STANDARD_NAMESPACE
