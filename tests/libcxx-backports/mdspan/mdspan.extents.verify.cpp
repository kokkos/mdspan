//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20

// <mdspan/mdspan.hpp>

// template<class ElementType, class Extents, class LayoutPolicy = layout_right, class AccessorPolicy = default_accessor>
// class mdspan;
//
// Mandates:
//  - Extents is a specialization of extents

#include <mdspan/mdspan.hpp>

void not_extents() {
  // expected-error-re@*:* {{static assertion failed {{.*}}mdspan: Extents template parameter must be a specialization of extents.}}
  [[maybe_unused]] std::mdspan<int, int> m;
}
