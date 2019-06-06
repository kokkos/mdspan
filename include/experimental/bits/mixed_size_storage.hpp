
#pragma once

#include "dynamic_extent.hpp"

#include <cstddef> // ptrdiff_t
#include <utility> // integer_sequence
#include <array>

namespace std {
namespace detail {

inline constexpr struct construct_mixed_storage_from_sizes_tag_t { } construct_mixed_storage_from_sizes_tag = { };

template <class, class>
class mixed_static_and_dynamic_size_storage;

template <
  ptrdiff_t... Sizes,
  ptrdiff_t... DynamicOffsets
>
class mixed_static_and_dynamic_size_storage<
  integer_sequence<ptrdiff_t, Sizes...>,
  integer_sequence<ptrdiff_t, DynamicOffsets...>
>
{
public:

  static_assert(sizeof...(Sizes) > 0);

  static inline constexpr auto size_dynamic = (static_cast<int>((Sizes == dynamic_extent)) + ... + 0);

private:

  [[no_unique_address]] array<ptrdiff_t, size_dynamic> dynamic_sizes;

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  inline constexpr ptrdiff_t _select(true_type) const noexcept { return std::get<DynamicOffset>(dynamic_sizes); }
  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  inline constexpr ptrdiff_t _select(false_type) const noexcept { return Size; }

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  inline constexpr ptrdiff_t _select_set(true_type, ptrdiff_t value) noexcept { dynamic_sizes[DynamicOffset] = value; return 0; }
  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  inline constexpr ptrdiff_t _select_set(false_type, ptrdiff_t) noexcept { return 0; }

public:

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset>
  inline constexpr ptrdiff_t select() const noexcept {
    return _select<Size, DynamicOffset>(bool_constant<Size == dynamic_extent>{});
  }

  template <ptrdiff_t Size, ptrdiff_t DynamicOffset, ptrdiff_t Default=dynamic_extent>
  static inline constexpr ptrdiff_t select_static() noexcept {
    return Size == dynamic_extent ? Default : Size;
  }


  template <ptrdiff_t Size, ptrdiff_t DynamicOffset, size_t Idx, ptrdiff_t N>
  inline constexpr ptrdiff_t select_set(ptrdiff_t value) noexcept {
    return _select_set<Size, DynamicOffset>(bool_constant<Size == dynamic_extent && Idx == N>{}, value);
  }
 
 
  template <size_t N>
  inline constexpr ptrdiff_t get() const noexcept {
    return std::get<N>(
      array<ptrdiff_t, sizeof...(Sizes)>{select<Sizes, DynamicOffsets>()...}
    );
  }

  template <size_t N, ptrdiff_t Default>
  static inline constexpr ptrdiff_t get_static() noexcept {
    return std::get<N>(
      array<ptrdiff_t, sizeof...(Sizes)>{select_static<Sizes, DynamicOffsets, Default>()...}
    );
  }

  inline constexpr ptrdiff_t get(size_t n) const noexcept {
    return array<ptrdiff_t, sizeof...(Sizes)>{select<Sizes, DynamicOffsets>()...}[n];
  }

  template <size_t N>
  inline constexpr void set(ptrdiff_t value) noexcept {
    [this, value]<size_t... Idxs>(integer_sequence<size_t, Idxs...>) {
      (select_set<Sizes, DynamicOffsets, Idxs, N>(value), ...);  
    }(make_index_sequence<sizeof...(Sizes)>{});
  }

  constexpr mixed_static_and_dynamic_size_storage() = default;

  template <class... Integral>
  constexpr mixed_static_and_dynamic_size_storage(construct_mixed_storage_from_sizes_tag_t, Integral... dyn_sizes)
    : dynamic_sizes{dyn_sizes...}
  { }

  template <class Integral>
  MDSPAN_INLINE_FUNCTION
  constexpr mixed_static_and_dynamic_size_storage(std::array<Integral, size_dynamic> const& dyn)
    : dynamic_sizes(dyn)
  { }

};

template <class Sequence>
struct _make_mixed_impl;
template <class T, T... Sizes>
struct _make_mixed_impl<integer_sequence<T, Sizes...>> {
  using type = mixed_static_and_dynamic_size_storage<
      integer_sequence<ptrdiff_t, Sizes...>,
      decltype(
        []<size_t... Idxs>(integer_sequence<size_t, Idxs...>) {
          return integer_sequence<ptrdiff_t,
            [](ptrdiff_t N){ return (int(Idxs < size_t(N) && Sizes == dynamic_extent) + ...); }(Idxs)...
          >{};
        }(make_index_sequence<sizeof...(Sizes)>{})
      )
    >;
};

} // namespace detail
} // namespace std
