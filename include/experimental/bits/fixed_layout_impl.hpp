

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
  _MDSPAN_NO_UNIQUE_ADDRESS extents_type _extents = {};
public:
  constexpr extents_storage() noexcept = default;
  constexpr extents_storage(extents_storage const&) noexcept = default;
  constexpr extents_storage(extents_storage&&) noexcept = default;
  constexpr extents_storage& operator=(extents_storage const&) noexcept = default;
  constexpr extents_storage& operator=(extents_storage&&) noexcept = default;
  ~extents_storage() noexcept = default;

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

template <class, class, class> struct stride_storage_impl;

template <ptrdiff_t... Exts, size_t... Idxs, class IdxConditional>
struct stride_storage_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
  : extents_storage<std::extents<Exts...>>
{
private:
  using base_t = extents_storage<std::extents<Exts...>>;  
public:

  constexpr stride_storage_impl() noexcept = default;
  constexpr stride_storage_impl(stride_storage_impl const&) noexcept = default;
  constexpr stride_storage_impl(stride_storage_impl&&) noexcept = default;
  constexpr stride_storage_impl& operator=(stride_storage_impl const&) noexcept = default;
  constexpr stride_storage_impl& operator=(stride_storage_impl&&) noexcept = default;
  ~stride_storage_impl() noexcept = default;

  using base_t::base_t;

  MDSPAN_INLINE_FUNCTION constexpr typename base_t::extents_type extents() const noexcept { return this->base_t::extents(); };

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t get_stride() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((IdxConditional{}(Idxs, N) ? extents().template __extent<Idxs>() : 1), /* * ... * */ 1);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t get_stride(size_t n) const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((IdxConditional{}(Idxs, n) ? extents().template __extent<Idxs>() : 1), /* * ... * */ 1);
  }

};

//==============================================================================================================

template <class, class, class>
class fixed_layout_common_impl;

template <ptrdiff_t... Exts, size_t... Idxs, class IdxConditional>
class fixed_layout_common_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
  : protected stride_storage_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
{
private:

  using base_t = stride_storage_impl<std::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>;

public:

  constexpr fixed_layout_common_impl() noexcept = default;
  constexpr fixed_layout_common_impl(fixed_layout_common_impl const&) noexcept = default;
  constexpr fixed_layout_common_impl(fixed_layout_common_impl&&) noexcept = default;
  constexpr fixed_layout_common_impl& operator=(fixed_layout_common_impl const&) noexcept = default;
  constexpr fixed_layout_common_impl& operator=(fixed_layout_common_impl&&) noexcept = default;
  ~fixed_layout_common_impl() noexcept = default;

  using base_t::base_t;
  using base_t::extents;

  template <class... Integral>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr ptrdiff_t operator()(Integral... idxs) const noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT((idxs * this->base_t::template get_stride<Idxs>()), /* + ... + */ 0);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr ptrdiff_t required_span_size() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((base_t::extents().template __extent<Idxs>()), /* * ... * */ 1);
  }

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

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
    constexpr ptrdiff_t result = _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, N) ? base_t::extents_type::template __static_extent<Idxs, 0>() : 1), /* * ... * */ 1
    );
    return result == 0 ? Default : result;
  }


};

//==============================================================================================================

} // namespace detail
} // namespace std