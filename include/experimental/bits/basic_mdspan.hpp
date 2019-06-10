

#pragma once

#include "accessor_basic.hpp"
#include "layout_right.hpp"
#include "extents.hpp"

#include <utility> // make_index_sequence
#include <tuple> // std::apply

namespace std {

namespace detail {

template <class Derived, class ExtentsIdxs>
struct _basic_mdspan_crtp_helper;

// Workaround for not being able to give explicit template parameters to lambdas in older
// versions of C++, thus making expanding parameter packs with indices more difficult
template <class Derived, size_t... ExtIdxs>
struct _basic_mdspan_crtp_helper<
  Derived, std::index_sequence<ExtIdxs...>
>
{
protected:
  MDSPAN_FORCE_INLINE_FUNCTION Derived& __self() noexcept { return *static_cast<Derived*>(this); }
  MDSPAN_FORCE_INLINE_FUNCTION Derived const& __self() const noexcept { return *static_cast<Derived const*>(this); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr auto __size() const noexcept {
    return (__self().map_.extents().template __extent<ExtIdxs>() * ... * 1);
  }
};

} // namespace detail


template <
  class ElementType,
  class Extents,
  class LayoutPolicy = layout_right,
  class AccessorPolicy = accessor_basic<ElementType>
>
class basic_mdspan;


template <
  class ElementType,
  ptrdiff_t... Exts,
  class LayoutPolicy,
  class AccessorPolicy
>
class basic_mdspan<
  ElementType,
  std::extents<Exts...>,
  LayoutPolicy,
  AccessorPolicy
>
  : detail::_basic_mdspan_crtp_helper<
      basic_mdspan<ElementType, std::extents<Exts...>, LayoutPolicy, AccessorPolicy>,
      std::make_index_sequence<sizeof...(Exts)>
    >
{
private:
  using _crtp_base_t = detail::_basic_mdspan_crtp_helper<
      basic_mdspan<ElementType, std::extents<Exts...>, LayoutPolicy, AccessorPolicy>,
      std::make_index_sequence<sizeof...(Exts)>
    >;
public:
  
  //--------------------------------------------------------------------------------
  // Domain and codomain types

  using extents_type = std::extents<Exts...>;
  using layout_type = LayoutPolicy;
  using accessor_type = AccessorPolicy;
  using mapping_type = typename layout_type::template mapping<extents_type>;
  using element_type = ElementType;
  using value_type = remove_cv_t<element_type>;
  using index_type = ptrdiff_t;
  using difference_type = ptrdiff_t;
  using pointer = typename accessor_type::pointer;
  using reference = typename accessor_type::reference;

  //--------------------------------------------------------------------------------
  // [mdspan.basic.cons], basic_mdspan constructors, assignment, and destructor

  MDSPAN_INLINE_FUNCTION constexpr basic_mdspan() noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr basic_mdspan(const basic_mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr basic_mdspan(basic_mdspan&&) noexcept = default;

  // TODO noexcept specification
  template<class... IndexType>
  MDSPAN_INLINE_FUNCTION 
  explicit constexpr basic_mdspan(pointer p, IndexType... dynamic_extents)
    MDSPAN_NOEXCEPT_REQUIRES(
      (is_convertible_v<IndexType, index_type> && ...)
      && (sizeof...(IndexType) == extents_type::rank_dynamic())
      && is_constructible_v<mapping_type, extents_type>
      && is_default_constructible_v<accessor_type>
    )
    : ptr_(p),
      map_(extents_type(dynamic_extents...)),
      acc_()
  { }

  // TODO noexcept specification
  template<class IndexType, size_t N>
  MDSPAN_INLINE_FUNCTION 
  explicit constexpr basic_mdspan(pointer p, const array<IndexType, N>& dynamic_extents)
    MDSPAN_NOEXCEPT_REQUIRES(
      is_convertible_v<IndexType, index_type>
      && (N == extents_type::rank_dynamic())
      && is_constructible_v<mapping_type, extents_type>
      && is_default_constructible_v<accessor_type>
    )
    : ptr_(p),
      map_(extents_type(dynamic_extents)),
      acc_()
  { }

  // TODO noexcept specification
  MDSPAN_INLINE_FUNCTION 
  constexpr basic_mdspan(pointer p, const mapping_type& m)
    MDSPAN_NOEXCEPT_REQUIRES(is_default_constructible_v<accessor_type>)
    : ptr_(p),
      map_(m),
      acc_()
  { }

  // TODO noexcept specification
  MDSPAN_INLINE_FUNCTION 
  constexpr basic_mdspan(pointer p, const mapping_type& m, const accessor_type& a) noexcept
    : ptr_(p),
      map_(m),
      acc_(a)
  { }

  // TODO noexcept specification
  template<class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherAccessor>
  MDSPAN_INLINE_FUNCTION 
  constexpr basic_mdspan(const basic_mdspan<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>& other)
    MDSPAN_NOEXCEPT_REQUIRES(
      is_convertible_v<typename OtherLayoutPolicy::template mapping<OtherExtents>, mapping_type>
      && is_convertible_v<OtherAccessor, accessor_type>
      && is_convertible_v<typename OtherAccessor::pointer, pointer>
      && is_convertible_v<OtherExtents, extents_type>
    )
    : ptr_(other.ptr_),
      map_(other.map_),
      acc_(other.acc_)
  { }

  // TODO noexcept specification
  ~basic_mdspan() = default;

  MDSPAN_INLINE_FUNCTION constexpr basic_mdspan& operator=(const basic_mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr basic_mdspan& operator=(basic_mdspan&&) noexcept = default;

  // TODO constraints, noexcept specification
  template<class OtherElementType, ptrdiff_t... OtherExtents, class OtherLayoutPolicy, class OtherAccessorPolicy>
  MDSPAN_INLINE_FUNCTION
  constexpr basic_mdspan& operator=(
    const basic_mdspan<OtherElementType, std::extents<OtherExtents...>, OtherLayoutPolicy, OtherAccessorPolicy>& other
  )
    MDSPAN_NOEXCEPT_REQUIRES(
      is_assignable_v<mapping_type, typename OtherLayoutPolicy::template mapping<std::extents<OtherExtents...>>>
      && is_assignable_v<accessor_type, OtherAccessorPolicy>
      && is_assignable_v<pointer, typename OtherAccessorPolicy::pointer>
      && sizeof...(OtherExtents) == extents_type::rank()
      // "For all r in the range [0, rank()), if other.static_extent(r) != dynamic_extent
      //   && static_extent(r) != dynamic_extent is true, then
      //   other.static_extent(r) == static_extent(r) is true."
      && (
        (
          Exts == dynamic_extent
          || OtherExtents == dynamic_extent
          || Exts == OtherExtents
        ) && ...
      )
    )
  {
    ptr_ = other.ptr_;
    map_ = other.map_;
    acc_ = other.acc_;
  }

  //--------------------------------------------------------------------------------
  // [mdspan.basic.mapping], basic_mdspan mapping domain multidimensional index to access codomain element

  template <class Index>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](Index idx) const
    MDSPAN_NOEXCEPT_REQUIRES(
      is_convertible_v<Index, index_type>
      && sizeof...(Exts) == 1
    )
  {
    return acc_.access(ptr_, map_(idx));
  }

  template<class... IndexType>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(IndexType... indices) const
    MDSPAN_NOEXCEPT_REQUIRES(
      (is_convertible_v<IndexType, index_type> && ...)
      && sizeof...(Exts) == extents_type::rank()
    )
  {
    return acc_.access(ptr_, map_(indices...)); 
  }

  template<class IndexType, size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(const array<IndexType, N>& indices) const
    MDSPAN_NOEXCEPT_REQUIRES(
      is_convertible_v<IndexType, index_type>
      && N == extents_type::rank()
    )
  {
    return acc_.access(ptr_, std::apply(map_, indices));
  }

  MDSPAN_INLINE_FUNCTION
  accessor_type accessor() const { return acc_; };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.domobs], basic_mdspan observers of the domain multidimensional index space

  MDSPAN_INLINE_FUNCTION static constexpr int rank() noexcept { return extents_type::rank(); };
  MDSPAN_INLINE_FUNCTION static constexpr int rank_dynamic() noexcept { return extents_type::rank_dynamic(); };;
  MDSPAN_INLINE_FUNCTION static constexpr index_type static_extent(size_t r) noexcept { return extents_type::static_extent(r); }

  MDSPAN_INLINE_FUNCTION constexpr extents_type extents() const noexcept { return map_.extents(); };
  MDSPAN_INLINE_FUNCTION constexpr index_type extent(size_t r) const noexcept { return map_.extents().extent(r); };
  MDSPAN_INLINE_FUNCTION constexpr index_type size() const noexcept {
    return this->_crtp_base_t::__size();
  };

  MDSPAN_INLINE_FUNCTION constexpr index_type unique_size() const noexcept { return map_.required_span_size(); }

  // [mdspan.basic.codomain], basic_mdspan observers of the codomain
  // TODO span (or just `codomain` function, as discussed)
  // constexpr span<element_type> span() const noexcept;

  MDSPAN_INLINE_FUNCTION constexpr pointer data() const noexcept { return ptr_; };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.obs], basic_mdspan observers of the mapping

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return mapping_type::is_always_contiguous(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return mapping_type::is_always_strided(); };

  MDSPAN_INLINE_FUNCTION constexpr mapping_type mapping() const noexcept { return map_; };
  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return map_.is_unique(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return map_.is_contiguous(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return map_.is_strided(); };
  MDSPAN_INLINE_FUNCTION constexpr index_type stride(size_t r) const { return map_.stride(r); };

private:

  pointer ptr_ = nullptr;
  [[no_unique_address]] mapping_type map_ = {};
  [[no_unique_address]] accessor_type acc_ = {};

  template <class, class, class, class>
  friend class basic_mdspan;

  template <class, class>
  friend struct detail::_basic_mdspan_crtp_helper;

};


template <class T, ptrdiff_t... Exts>
using mdspan = basic_mdspan<T, std::extents<Exts...>>;

} // end namespace std
