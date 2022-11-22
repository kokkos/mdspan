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

#include "ctest_common.hpp"

#include <experimental/mdarray>
#include <complex>

#if defined(_MDSPAN_USE_CONCEPTS) && MDSPAN_HAS_CXX_20
#include <concepts>
#endif

namespace stdex = std::experimental;

using E1 = stdex::extents<int32_t, stdex::dynamic_extent, 3>;
using M1 = stdex::mdarray<float, E1, stdex::layout_left>;

#if defined(_MDSPAN_USE_CONCEPTS) && MDSPAN_HAS_CXX_20
template<class T>
constexpr bool is_copyable = std::copyable<T>;
#else
template<class T>
constexpr bool is_copyable =
  std::is_assignable<T,T>::value &&
  std::is_move_assignable<T>::value &&
  std::is_copy_constructible<T>::value &&
  std::is_move_constructible<T>::value;
#endif

MDSPAN_STATIC_TEST(
  std::is_same<typename M1::element_type, float>::value &&
  std::is_same<typename M1::index_type, int32_t>::value &&
  std::is_same<typename M1::size_type, uint32_t>::value &&
  std::is_same<typename M1::rank_type, size_t>::value &&
  std::is_same<typename M1::layout_type, stdex::layout_left>::value &&
  std::is_same<typename M1::container_type, std::vector<float>>::value &&
  std::is_same<decltype(M1::rank()), typename M1::rank_type>::value &&
  std::is_same<decltype(M1::rank_dynamic()), typename M1::rank_type>::value &&
  std::is_same<decltype(M1::static_extent(0)), size_t>::value &&
  std::is_same<decltype(M1::static_extent(1)), size_t>::value &&
  std::is_same<decltype(std::declval<M1>().extent(0)), typename E1::index_type>::value &&
  std::is_same<decltype(std::declval<M1>().extent(1)), typename E1::index_type>::value &&
  (M1::rank()==2) &&
  (M1::rank_dynamic()==1) &&
  (M1::static_extent(0) == stdex::dynamic_extent) &&
  (M1::static_extent(1) == 3) &&
  is_copyable<M1> &&
  std::is_default_constructible<M1>::value
);

using E2 = stdex::extents<int64_t, stdex::dynamic_extent, 3, stdex::dynamic_extent>;
using M2 = stdex::mdarray<std::complex<double>, E2, stdex::layout_right, std::array<std::complex<double>,24>>;

MDSPAN_STATIC_TEST(
  std::is_same<typename M2::element_type, std::complex<double>>::value &&
  std::is_same<typename M2::index_type, int64_t>::value &&
  std::is_same<typename M2::size_type, uint64_t>::value &&
  std::is_same<typename M2::rank_type, size_t>::value &&
  std::is_same<typename M2::layout_type, stdex::layout_right>::value &&
  std::is_same<typename M2::container_type, std::array<std::complex<double>,24>>::value &&
  std::is_same<decltype(M2::rank()), typename E2::rank_type>::value &&
  std::is_same<decltype(M2::rank_dynamic()), typename E2::rank_type>::value &&
  std::is_same<decltype(M2::static_extent(0)), size_t>::value &&
  std::is_same<decltype(M2::static_extent(1)), size_t>::value &&
  std::is_same<decltype(M2::static_extent(2)), size_t>::value &&
  std::is_same<decltype(std::declval<M2>().extent(0)), typename E2::index_type>::value &&
  std::is_same<decltype(std::declval<M2>().extent(1)), typename E2::index_type>::value &&
  std::is_same<decltype(std::declval<M2>().extent(2)), typename E2::index_type>::value &&
  (M2::rank()==3) &&
  (M2::rank_dynamic()==2) &&
  (M2::static_extent(0) == stdex::dynamic_extent) &&
  (M2::static_extent(1) == 3) &&
  (M2::static_extent(2) == stdex::dynamic_extent) &&
  is_copyable<M2> &&
  std::is_default_constructible<M2>::value
);

using E3 = stdex::extents<uint32_t, stdex::dynamic_extent, 3, stdex::dynamic_extent>;
using M3 = stdex::mdarray<uint32_t, E3>;

MDSPAN_STATIC_TEST(
  std::is_same<typename M3::element_type, uint32_t>::value &&
  std::is_same<typename M3::index_type, uint32_t>::value &&
  std::is_same<typename M3::size_type, uint32_t>::value &&
  std::is_same<typename M3::rank_type, size_t>::value &&
  std::is_same<typename M3::layout_type, stdex::layout_right>::value &&
  std::is_same<typename M3::container_type, std::vector<uint32_t>>::value &&
  std::is_same<decltype(M3::rank()), typename E3::rank_type>::value &&
  std::is_same<decltype(M3::rank_dynamic()), typename E3::rank_type>::value &&
  std::is_same<decltype(M3::static_extent(0)), size_t>::value &&
  std::is_same<decltype(M3::static_extent(1)), size_t>::value &&
  std::is_same<decltype(M3::static_extent(2)), size_t>::value &&
  std::is_same<decltype(std::declval<M3>().extent(0)), typename E3::index_type>::value &&
  std::is_same<decltype(std::declval<M3>().extent(1)), typename E3::index_type>::value &&
  std::is_same<decltype(std::declval<M3>().extent(2)), typename E3::index_type>::value &&
  (M3::rank()==3) &&
  (M3::rank_dynamic()==2) &&
  (M3::static_extent(0) == stdex::dynamic_extent) &&
  (M3::static_extent(1) == 3) &&
  (M3::static_extent(2) == stdex::dynamic_extent) &&
  is_copyable<M3> &&
  std::is_default_constructible<M3>::value
);
