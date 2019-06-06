
#pragma once

#include "macros.hpp"
#include "mixed_size_storage.hpp"

#include <cstddef>

namespace std {

template <ptrdiff_t... Extents>
class extents {
private:

  using storage_type = typename detail::_make_mixed_impl<integer_sequence<ptrdiff_t, Extents...>>::type;
  [[no_unique_address]] storage_type _storage;


public:

  //--------------------------------------------------------------------------------
  // Constructors, Destructors, and Assignment

  using index_type = ptrdiff_t;

  MDSPAN_INLINE_FUNCTION constexpr extents() noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents& operator=(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION constexpr extents& operator=(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION ~extents() noexcept = default;

  // TODO constrain 
  template <class... Integral>
  MDSPAN_INLINE_FUNCTION
  constexpr extents(Integral... dyn)
    requires (std::is_integral_v<Integral> && ...)
    : _storage(detail::construct_mixed_storage_from_sizes_tag, dyn...)
  { }

  template <class Integral>
  MDSPAN_INLINE_FUNCTION
  constexpr extents(std::array<Integral, storage_type::size_dynamic> const& dyn)
    : _storage(dyn)
  { }

  // TODO convertible extents ctors

  //--------------------------------------------------------------------------------

  static constexpr size_t rank() noexcept { return sizeof...(Extents); }
  static constexpr size_t rank_dynamic() noexcept { return (int(Extents == dynamic_extent) + ...); }
  
  MDSPAN_INLINE_FUNCTION
  static constexpr
  index_type static_extent(size_t n) noexcept {
    return [n]<size_t... Idxs>(index_sequence<Idxs...>){
      return (((Idxs == n) ? Extents : 0) + ...); 
    }(make_index_sequence<sizeof...(Extents)>());
  }

  MDSPAN_INLINE_FUNCTION
  constexpr
  index_type extent(size_t n) const noexcept {
    return _storage.get(n);
  }

  //--------------------------------------------------------------------------------

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
    return storage_type::template get_static<N, dynamic_extent>();
  }

};

} // namespace std
