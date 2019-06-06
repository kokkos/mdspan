
#pragma once

#include "macros.hpp"

#include <cstddef>

namespace std {

template <class ElementType>
struct accessor_basic {
  
  using offset_policy = accessor_basic;
  using element_type = ElementType;
  using reference = ElementType&;
  using pointer = ElementType*;

  MDSPAN_INLINE_FUNCTION
  constexpr pointer
  offset(pointer p, ptrdiff_t i) const noexcept {
    return p + i;
  }

  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference access(pointer p, ptrdiff_t i) const noexcept {
    return p[i];
  }

  MDSPAN_INLINE_FUNCTION
  constexpr pointer decay(pointer p) const noexcept {
    return p;
  }

};

} // end namespace std