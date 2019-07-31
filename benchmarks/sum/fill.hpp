/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#pragma once

#include <experimental/mdspan>
#include <memory>

#if !(defined(__cpp_lib_make_unique) && __cpp_lib_make_unique >= 201304) && !MDSPAN_HAS_CXX_14
// Not actually conforming, but it works for the purposes of this file
namespace std {
template <class T>
struct __unique_ptr_new_impl {
  template <class... Args>
  static T* __impl(Args&&... args) {
    return new T((Args&&)args...);
  }
};

template <class T>
struct __unique_ptr_new_impl<T[]> {
  static T* __impl(size_t size) {
    return new T[size];
  }
};

template <class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(__unique_ptr_new_impl<T>::__impl((Args&&)args...));
}
} // end namespace std
#endif

namespace mdspan_benchmark {

namespace _impl {

template <class, class T>
T&& _repeated_with(T&& v) noexcept { return std::forward<T>(v); }

template <class T, class LP, class AP, class RNG, class Dist>
void _do_fill_random(
  std::experimental::basic_mdspan<T, std::experimental::extents<>, LP, AP> s,
  RNG& gen,
  Dist& dist
)
{
  s() = dist(gen);
}

template <class T, ptrdiff_t E, ptrdiff_t... Es, class LP, class AP, class RNG, class Dist>
void _do_fill_random(
  std::experimental::basic_mdspan<T, std::experimental::extents<E, Es...>, LP, AP> s,
  RNG& gen,
  Dist& dist
)
{
  for(ptrdiff_t i = 0; i < s.extent(0); ++i) {
    _do_fill_random(std::experimental::subspan(s, i, _repeated_with<decltype(Es)>(std::experimental::all)...), gen, dist);
  }
}

} // end namespace _impl

template <class T, class E, class LP, class AP>
void fill_random(std::experimental::basic_mdspan<T, E, LP, AP> s, long long seed = 1234) {
  std::mt19937 gen(seed);
  auto val_dist = std::uniform_int_distribution<>(0, 127);
  _impl::_do_fill_random(s, gen, val_dist);
}



} // namespace mdspan_benchmark