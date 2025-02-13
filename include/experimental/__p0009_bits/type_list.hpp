//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER
#include "macros.hpp"

#include "trait_backports.hpp" // make_index_sequence

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {

//==============================================================================

namespace detail {

template <class... Ts> struct __type_list { static constexpr auto __size = sizeof...(Ts); };

// Implementation of type_list at() that's heavily optimized for small typelists
template <size_t, class> struct __type_at;
template <size_t, class _Seq, class=std::make_index_sequence<_Seq::__size>> struct __type_at_large_impl;

template <size_t _I, size_t _Idx, class T>
struct __type_at_entry { };

template <class _Result>
struct __type_at_assign_op_ignore_rest {
  template <class T>
  __type_at_assign_op_ignore_rest<_Result> operator=(T&&);
  using type = _Result;
};

struct __type_at_assign_op_impl {
  template <size_t _I, size_t _Idx, class T>
  __type_at_assign_op_impl operator=(__type_at_entry<_I, _Idx, T>&&);
  template <size_t _I, class T>
  __type_at_assign_op_ignore_rest<T> operator=(__type_at_entry<_I, _I, T>&&);
};

template <size_t _I, class... Ts, size_t... _Idxs>
struct __type_at_large_impl<_I, __type_list<Ts...>, std::integer_sequence<size_t, _Idxs...>>
  : decltype(
      MDSPAN_IMPL_FOLD_ASSIGN_LEFT(__type_at_assign_op_impl{}, /* = ... = */ __type_at_entry<_I, _Idxs, Ts>{})
    )
{ };

template <size_t _I, class... Ts>
struct __type_at<_I, __type_list<Ts...>>
    : __type_at_large_impl<_I, __type_list<Ts...>>
{ };

template <class T0, class... Ts>
struct __type_at<0, __type_list<T0, Ts...>> {
  using type = T0;
};

template <class T0, class T1, class... Ts>
struct __type_at<1, __type_list<T0, T1, Ts...>> {
  using type = T1;
};

template <class T0, class T1, class T2, class... Ts>
struct __type_at<2, __type_list<T0, T1, T2, Ts...>> {
  using type = T2;
};

template <class T0, class T1, class T2, class T3, class... Ts>
struct __type_at<3, __type_list<T0, T1, T2, T3, Ts...>> {
  using type = T3;
};


} // namespace detail

//==============================================================================

} // end namespace MDSPAN_IMPL_STANDARD_NAMESPACE
