#pragma once

#include "../__p0009_bits/utility.hpp"
#include <type_traits>
#include <utility>

// Implementation borrowed from
// https://github.com/tzlaine/constexpr/blob/master/include/constant_wrapper.hpp
// to which P2781 links.

#if defined(__cpp_lib_constant_wrapper)

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
  using std::constant_wrapper;
  using std::cw;
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE

#elif ! defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {

namespace exposition_only {
  template<typename T>
  struct cw_fixed_value; // exposition only
}

template<
  exposition_only::cw_fixed_value X,
  typename unspecified =
    typename decltype(exposition_only::cw_fixed_value(X))::type // exposition only
>
struct constant_wrapper;

template<class T>
concept constexpr_param = requires { typename constant_wrapper<T::value>; }; // exposition only

namespace exposition_only {
  template<typename T>
  struct cw_fixed_value { // exposition only
    using type = T;
    constexpr cw_fixed_value(type v) noexcept: data(v) { }
    T data;
  };

  template<typename T, size_t Extent>
  struct cw_fixed_value<T[Extent]> { // exposition only
    using type = T[Extent];
    constexpr cw_fixed_value(T (&arr)[Extent]) noexcept: cw_fixed_value(arr, std::make_index_sequence<Extent>()) { }
    T data[Extent];

  private:
    template<size_t... Idx>
    constexpr cw_fixed_value(T (&arr)[Extent], std::index_sequence<Idx...>) noexcept: data{arr[Idx]...} { }
  };

  template<typename T, size_t Extent>
  cw_fixed_value(T (&)[Extent]) -> cw_fixed_value<T[Extent]>; // exposition only
  template<typename T>
  cw_fixed_value(T) -> cw_fixed_value<T>;                     // exposition only

  struct cw_operators { // exposition only
    // unary operators
    template<constexpr_param T>
      friend constexpr auto operator+(T) noexcept -> constant_wrapper<(+T::value)> { return {}; }
    template<constexpr_param T>
      friend constexpr auto operator-(T) noexcept -> constant_wrapper<(-T::value)> { return {}; }
    template<constexpr_param T>
      friend constexpr auto operator~(T) noexcept -> constant_wrapper<(~T::value)> { return {}; }
    template<constexpr_param T>
      friend constexpr auto operator!(T) noexcept -> constant_wrapper<(!T::value)> { return {}; }
    template<constexpr_param T>
      friend constexpr auto operator&(T) noexcept -> constant_wrapper<(&T::value)> { return {}; }
    template<constexpr_param T>
      friend constexpr auto operator*(T) noexcept -> constant_wrapper<(*T::value)> { return {}; }

    // binary operators
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator+(L, R) noexcept -> constant_wrapper<(L::value + R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator-(L, R) noexcept -> constant_wrapper<(L::value - R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator*(L, R) noexcept -> constant_wrapper<(L::value * R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator/(L, R) noexcept -> constant_wrapper<(L::value / R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator%(L, R) noexcept -> constant_wrapper<(L::value % R::value)> { return {}; }

    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator<<(L, R) noexcept -> constant_wrapper<(L::value << R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator>>(L, R) noexcept -> constant_wrapper<(L::value >> R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator&(L, R) noexcept -> constant_wrapper<(L::value & R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator|(L, R) noexcept -> constant_wrapper<(L::value | R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator^(L, R) noexcept -> constant_wrapper<(L::value ^ R::value)> { return {}; }

    template<constexpr_param L, constexpr_param R>
      requires (!is_constructible_v<bool, decltype(L::value)> || !is_constructible_v<bool, decltype(R::value)>)
        friend constexpr auto operator&&(L, R) noexcept -> constant_wrapper<(L::value && R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      requires (!is_constructible_v<bool, decltype(L::value)> || !is_constructible_v<bool, decltype(R::value)>)
        friend constexpr auto operator||(L, R) noexcept -> constant_wrapper<(L::value || R::value)> { return {}; }

    // comparisons
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator<=>(L, R) noexcept -> constant_wrapper<(L::value <=> R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator<(L, R) noexcept -> constant_wrapper<(L::value < R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator<=(L, R) noexcept -> constant_wrapper<(L::value <= R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator==(L, R) noexcept -> constant_wrapper<(L::value == R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator!=(L, R) noexcept -> constant_wrapper<(L::value != R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator>(L, R) noexcept -> constant_wrapper<(L::value > R::value)> { return {}; }
    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator>=(L, R) noexcept -> constant_wrapper<(L::value >= R::value)> { return {}; }

    template<constexpr_param L, constexpr_param R>
      friend constexpr auto operator->*(L, R) noexcept -> constant_wrapper<L::value->*R::value> { return {}; }

#  if defined(__cpp_explicit_this_parameter)
    // call and index
    template<constexpr_param T, constexpr_param... Args>
      constexpr auto operator()(this T, Args...) noexcept
        requires requires(Args...) { constant_wrapper<T::value(Args::value...)>(); }
          { return constant_wrapper<T::value(Args::value...)>{}; }
    template<constexpr_param T, constexpr_param... Args>
      constexpr auto operator[](this T, Args...) noexcept -> constant_wrapper<(T::value[Args::value...])>
        { return {}; }

    // pseudo-mutators
    template<constexpr_param T>
      constexpr auto operator++(this T) noexcept requires requires(T::value_type x) { ++x; }
        { return constant_wrapper<[] { auto c = T::value; return ++c; }()>{}; }
    template<constexpr_param T>
      constexpr auto operator++(this T, int) noexcept requires requires(T::value_type x) { x++; }
        { return constant_wrapper<[] { auto c = T::value; return c++; }()>{}; }

    template<constexpr_param T>
      constexpr auto operator--(this T) noexcept requires requires(T::value_type x) { --x; }
        { return constant_wrapper<[] { auto c = T::value; return --c; }()>{}; }
    template<constexpr_param T>
      constexpr auto operator--(this T, int) noexcept requires requires(T::value_type x) { x--; }
        { return constant_wrapper<[] { auto c = T::value; return c--; }()>{}; }

    template<constexpr_param T, constexpr_param R>
      constexpr auto operator+=(this T, R) noexcept requires requires(T::value_type x) { x += R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v += R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator-=(this T, R) noexcept requires requires(T::value_type x) { x -= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v -= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator*=(this T, R) noexcept requires requires(T::value_type x) { x *= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v *= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator/=(this T, R) noexcept requires requires(T::value_type x) { x /= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v /= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator%=(this T, R) noexcept requires requires(T::value_type x) { x %= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v %= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator&=(this T, R) noexcept requires requires(T::value_type x) { x &= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v &= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator|=(this T, R) noexcept requires requires(T::value_type x) { x |= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v |= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator^=(this T, R) noexcept requires requires(T::value_type x) { x ^= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v ^= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator<<=(this T, R) noexcept requires requires(T::value_type x) { x <<= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v <<= R::value; }()>{}; }
    template<constexpr_param T, constexpr_param R>
      constexpr auto operator>>=(this T, R) noexcept requires requires(T::value_type x) { x >>= R::value; }
        { return constant_wrapper<[] { auto v = T::value; return v >>= R::value; }()>{}; }
#  endif // __cpp_explicit_this_parameter
  };
}

template<exposition_only::cw_fixed_value X, typename>
struct constant_wrapper : exposition_only::cw_operators {
  static constexpr const auto & value = X.data;
  using type = constant_wrapper;
  using value_type = typename decltype(X)::type;

  template<constexpr_param R>
  constexpr auto operator=(R) const noexcept
  requires requires(value_type x) { x = R::value; }
  {
    return constant_wrapper<
      [] { auto v = value; return v = R::value; }()
    >{};
  }

  constexpr operator decltype(auto)() const noexcept { return value; }
  constexpr decltype(auto) operator()() const noexcept requires (!std::invocable<value_type>) { return value; }

#  if defined(__cpp_explicit_this_parameter)
  using exposition_only::cw_operators::operator();
#  endif // defined(__cpp_explicit_this_parameter)
};

template<exposition_only::cw_fixed_value X>
  constinit auto cw = constant_wrapper<X>{};

} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE

#else // defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {

// GCC 11.4.0 (C++20) has an internal compiler error (ICE) with
// "typename unspecified = typename decltype(exposition_only::cw_fixed_value(X))::type"
// as second template parameter of constant_wrapper below.
//
// Replacing that expression with use of the following alias doesn't help.
//
// namespace exposition_only {
//   template<auto X>
//   using unspecified_t = typename decltype(cw_fixed_value(X))::type;
// }
//
// Moving the definitions of the various specializations of cw_fixed_value
// above this point doesn't help either.
//
// Replacing the offending expression with
//
//   typename unspecified = typename decltype(X)::type // exposition only
//
// gets us only part of the way there.  The problem ultimately relates to
// GCC 11.4.0 being unable to find the overloaded arithmetic operators.
// Our P3663 implementation doesn't depend on them, so we don't need
// the operators at all.

// Clang 14 doesn't like the forward declaration of constant_wrapper,
// because it claims that the non-type template parameter X has a different
// type in the definition versus in the declaration.

namespace detail {

template<class T, T Value>
struct constant_wrapper_impl
{
    static constexpr T value = Value;
    using value_type = T;
    using type = constant_wrapper_impl;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

} // namespace detail

template<auto Value, class T = decltype(Value)>
using constant_wrapper = detail::constant_wrapper_impl<T, Value>;

template<auto Value>
  constexpr auto cw = constant_wrapper<Value>{};

} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE

#endif // defined(MDSPAN_CONSTANT_WRAPPER_WORKAROUND)
