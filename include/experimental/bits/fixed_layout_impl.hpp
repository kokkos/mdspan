

#pragma once

#include "mixed_size_storage.hpp"
#include "dynamic_extent.hpp"
#include "extents.hpp"
#include "macros.hpp"

#include <type_traits>
#include <utility>
#include <cstddef>
#include <array>

//==============================================================================================================

namespace std {

namespace detail {

//==============================================================================================================

template <class Extents>
struct extents_storage
{
public:
  using extents_type = Extents;
protected:
  [[no_unique_address]] extents_type _extents;
public:
  MDSPAN_INLINE_FUNCTION
  constexpr extents_storage(extents_type const& exts)
    : _extents(exts)
  { }  

  MDSPAN_INLINE_FUNCTION
  constexpr extents_type extents() const noexcept {
    return _extents;
  }
};

//==============================================================================================================

template <class, class, class, bool> struct stride_storage_impl;

template <ptrdiff_t... Exts, size_t... Idxs, class IdxConditional>
struct stride_storage_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional, true>
  : extents_storage<std::extents<Exts...>>
{
private:

  using base_t = extents_storage<std::extents<Exts...>>;  
  using strides_sequence = integer_sequence<ptrdiff_t,
    [](ptrdiff_t Stride){
      return (Stride == 0) ? dynamic_extent : Stride;
    }(
      []<ptrdiff_t N>(integral_constant<ptrdiff_t, N>){ 
        return (((IdxConditional{}(Idxs, size_t(N))) ? (Exts == dynamic_extent ? 0 : Exts) : 1) * ... * 1);
      }(integral_constant<ptrdiff_t, Idxs>{})
    )...
  >;
  using storage_type = typename _make_mixed_impl<strides_sequence>::type;
  [[no_unique_address]] storage_type _strides_storage;

public:

  using base_t::extents;

  template <size_t N>
  inline constexpr ptrdiff_t get_stride() const noexcept {
    return _strides_storage.template get<N>();
  }

  inline constexpr ptrdiff_t get_stride(size_t n) const noexcept {
    return _strides_storage.get(n);
  }

  template <size_t N>
  constexpr inline void _setup_stride() noexcept {
    _strides_storage.template set<N>(
      ((IdxConditional{}(Idxs, N) ? extents().template __extent<Idxs>() : 1) * ... * 1)
    );  
  }

  constexpr inline
  stride_storage_impl(typename base_t::extents_type const& exts)
    : base_t(exts)
  {
    (_setup_stride<Idxs>(), ...); 
  }

};

//--------------------------------------------------------------------------------------------------------------

template <ptrdiff_t... Exts, size_t... Idxs, class IdxConditional>
struct stride_storage_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional, false>
  : extents_storage<std::extents<Exts...>>
{
private:
  using base_t = extents_storage<std::extents<Exts...>>;  
public:

  using base_t::base_t;

  MDSPAN_INLINE_FUNCTION constexpr base_t::extents_type extents() const noexcept { return this->base_t::_extents; };

  template <size_t N>
  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t get_stride() const noexcept {
    return ((IdxConditional{}(Idxs, N) ? extents().template __extent<Idxs>() : 1) * ... * 1);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t get_stride(size_t n) const noexcept {
    return ((IdxConditional{}(Idxs, n) ? extents().template __extent<Idxs>() : 1) * ... * 1);
  }

};

//==============================================================================================================

template <class, class, class, bool>
class fixed_layout_common_impl;

template <ptrdiff_t... Exts, size_t... Idxs, class IdxConditional, bool StoreStrides>
class fixed_layout_common_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional, StoreStrides>
  : protected stride_storage_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional, StoreStrides>
{
private:

  using base_t = stride_storage_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional, StoreStrides>;

public:

  using base_t::base_t;
  using base_t::extents;

  template <class... Integral>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t operator()(Integral... idxs) const noexcept {
    return ((idxs * this->base_t::template get_stride<Idxs>()) + ...);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t required_span_size() const noexcept {
    return (base_t::extents().template __extent<Idxs>() * ... * 1);
  }

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return sizeof...(Exts) > 1; /* TODO Check this! */ }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t stride(size_t r) const noexcept {
    return this->base_t::get_stride(r);
  }

  //--------------------------------------------------------------------------------

public:  // (but not really)

  template <size_t R>
  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t __stride() const noexcept {
    return this->base_t::template get_stride<R>();
  }
  
  template <size_t N, ptrdiff_t Default=dynamic_extent>
  MDSPAN_INLINE_FUNCTION
  static constexpr ptrdiff_t __static_stride() noexcept
  {
    constexpr ptrdiff_t result =
      ((IdxConditional{}(Idxs, N) ? base_t::extents_type::template __static_extent<Idxs, 0>() : 1) * ... * 1);
    return result == 0 ? Default : result;
  }


};

//==============================================================================================================

} // namespace detail
} // namespace std