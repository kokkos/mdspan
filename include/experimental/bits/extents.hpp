
#pragma once

#include "macros.hpp"
#include "mixed_size_storage.hpp"

#include <cstddef>

namespace std {

template <ptrdiff_t... Extents>
class extents
{
public:

  using index_type = ptrdiff_t;

private:

  using storage_type = typename detail::_make_mixed_impl<integer_sequence<ptrdiff_t, Extents...>>::type;
  [[no_unique_address]] storage_type _storage;

  template <size_t... Idxs>
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr
  index_type _static_extent_impl(size_t n, std::integer_sequence<size_t, Idxs...>) noexcept {
    return (((Idxs == n) ? Extents : 0) + ... + 0); 
  }

  template <ptrdiff_t...>
  friend class extents;

  template <ptrdiff_t... OtherExtents>
  static std::false_type _check_compatible_extents(std::false_type);
  template <ptrdiff_t... OtherExtents>
  static std::integral_constant<
    bool,
    (
      (
        Extents == dynamic_extent
          || OtherExtents == dynamic_extent
          || Extents == OtherExtents
      ) && ...
    )
  >
  _check_compatible_extents(std::true_type);

  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(std::extents<OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return false; }
  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(
    std::extents<OtherExtents...> other,
    true_type, index_sequence<Idxs...>
  ) const noexcept {
    return ((_storage.template get<Idxs>() == other._storage.template get<Idxs>()) && ...);
  }

  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(std::extents<OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return true; }
  template <ptrdiff_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(
    std::extents<OtherExtents...> other,
    true_type, index_sequence<Idxs...>
  ) const noexcept {
    return ((_storage.template get<Idxs>() != other._storage.template get<Idxs>()) || ...);
  }

public:

  static constexpr size_t rank() noexcept { return sizeof...(Extents); }
  static constexpr size_t rank_dynamic() noexcept { return (int(Extents == dynamic_extent) + ...); }

  //--------------------------------------------------------------------------------
  // Constructors, Destructors, and Assignment

  MDSPAN_INLINE_FUNCTION constexpr extents() noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents& operator=(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents& operator=(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION ~extents() noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class... Integral,
    /* requires */ (
      (std::is_convertible_v<Integral, index_type> && ...) && sizeof...(Integral) == rank_dynamic()
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(Integral... dyn) noexcept
    : _storage(detail::construct_mixed_storage_from_sizes_tag, dyn...)
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType,
    /* requires */ (
      is_convertible_v<IndexType, index_type>
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(std::array<IndexType, storage_type::size_dynamic> const& dyn) noexcept
    : _storage(dyn)
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    ptrdiff_t... OtherExtents,
    /* requires */ (
      /* multi-stage check to protect from invalid pack expansion when sizes don't match? */
      decltype(extents<Extents...>::template _check_compatible_extents<OtherExtents...>(
        std::integral_constant<bool, sizeof...(Extents) == sizeof...(OtherExtents)>{}
      ))::value
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(const extents<OtherExtents...>& other)
    noexcept
    : _storage(other._storage)
  { }

  //--------------------------------------------------------------------------------
  
  MDSPAN_INLINE_FUNCTION
  static constexpr
  index_type static_extent(size_t n) noexcept {
    return _static_extent_impl(n, std::make_integer_sequence<size_t, sizeof...(Extents)>{});
  }

  MDSPAN_INLINE_FUNCTION
  constexpr
  index_type extent(size_t n) const noexcept {
    return _storage.get(n);
  }

  //--------------------------------------------------------------------------------

  template<ptrdiff_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator==(extents const& lhs, extents<RHS...> const& rhs) noexcept {
    return lhs._eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(Extents) == sizeof...(RHS))>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }

  template<ptrdiff_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator!=(extents const& lhs, extents<RHS...> const& rhs) noexcept {
    return lhs._not_eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(Extents) == sizeof...(RHS))>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }

public:  // (but not really)

  template <size_t N>
  MDSPAN_INLINE_FUNCTION
  constexpr
  index_type __extent() const noexcept {
    return _storage.template get<N>();
  }

  template <size_t N, ptrdiff_t Default=dynamic_extent>
  MDSPAN_INLINE_FUNCTION
  static constexpr
  index_type __static_extent() noexcept {
    return storage_type::template get_static<N, Default>();
  }


};


} // namespace std
