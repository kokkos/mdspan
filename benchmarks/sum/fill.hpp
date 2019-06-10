
#pragma once

#include <experimental/mdspan>

namespace mdspan_benchmark {

namespace _impl {

template <class, class T>
decltype(auto) _repeated_with(T&& v) noexcept { return std::forward<T>(v); }

template <class T, class LP, class AP, class RNG, class Dist>
void _do_fill_random(
  std::basic_mdspan<T, std::extents<>, LP, AP> s,
  RNG& gen,
  Dist& dist
)
{
  s() = dist(gen);
}

template <class T, ptrdiff_t E, ptrdiff_t... Es, class LP, class AP, class RNG, class Dist>
void _do_fill_random(
  std::basic_mdspan<T, std::extents<E, Es...>, LP, AP> s,
  RNG& gen,
  Dist& dist
)
{
  for(ptrdiff_t i = 0; i < s.extent(0); ++i) {
    _do_fill_random(std::subspan(s, i, _repeated_with<decltype(Es)>(std::all)...), gen, dist);
  }
}

} // end namespace _impl

template <class T, class E, class LP, class AP>
void fill_random(std::basic_mdspan<T, E, LP, AP> s, long long seed = 1234) {
  std::mt19937 gen(seed);
  auto val_dist = std::uniform_int_distribution<>(0, 127);
  _impl::_do_fill_random(s, gen, val_dist);
}



} // namespace mdspan_benchmark