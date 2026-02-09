#pragma once

#include "equality_comparable.hpp"
#include "remove_cvref.hpp"
#if defined(__cpp_lib_concepts)
#  include <concepts>
#endif // __cpp_lib_concepts

#if defined(__cpp_lib_concepts)

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
  namespace detail { 

    template<class T>
    concept integral_constant_like =
      std::is_integral_v<std::remove_cvref_t<decltype(T::value)>> &&
      !std::is_same_v<bool, std::remove_cvref_t<decltype(T::value)>> &&
      std::convertible_to<T, decltype(T::value)> &&
      std::equality_comparable_with<T, decltype(T::value)> &&
      std::bool_constant<T() == T::value>::value &&
      std::bool_constant<static_cast<decltype(T::value)>(T()) == T::value>::value;

    template<class T>
    constexpr bool is_integral_constant_like_v = integral_constant_like<T>;

  } // namespace detail
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE

#else

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
  namespace detail { 

    template<class T>
    constexpr bool is_integral_constant_like_v =
      std::is_integral_v<remove_cvref_t<decltype(T::value)>> &&
      ! std::is_same_v<bool, remove_cvref_t<decltype(T::value)>> &&
      std::is_convertible_v<T, decltype(T::value)> &&
      is_equality_comparable_with<T, decltype(T::value)>::value &&
      std::bool_constant<T() == T::value>::value &&
      std::bool_constant<static_cast<decltype(T::value)>(T()) == T::value>::value;

  } // namespace detail
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE

#endif // __cpp_lib_concepts
