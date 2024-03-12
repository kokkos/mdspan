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

#include <mdspan/mdspan.hpp>
#include <mdspan/mdarray.hpp>

#include <cassert>

#define SUPPORT_ALLOC

template<class mda_t, class ext_t, class map_t, class Container>
void check(mda_t& a, ext_t ext, map_t map, Container& c) {
  assert(a.extents() == ext);
  assert(a.mapping() == map);
  assert(a.container_size() == c.size());
}

// 11 ctors
template<class mda_t, class Container>
void test_minimal_set() {
  using ext_t = typename mda_t::extents_type;
  using map_t = typename mda_t::mapping_type;
  ext_t ext(10, 15);
  map_t map(ext);
  Container c(map.required_span_size());

  { // default construction
    mda_t a;
    assert(a.extents() == ext_t());
    assert(a.container_size() == map_t(ext_t()).required_span_size());
  }
  { // copy constructor
    mda_t a(10, 15);
    auto ptr = a.data();
    mda_t b(a);
    check(b, ext, map, c);
    assert(b.data() != a.data());
    assert(a.data() == ptr);
  }
  { // move constructor
    mda_t a(10, 15);
    auto ptr = a.data();
    mda_t b(std::move(a));
    check(b, ext, map, c);
    assert(b.data() == ptr);
  }
  { // integrals
    mda_t a(10, 15);
    check(a, ext, map, c);
  }
  { // extents
    mda_t a(ext);
    check(a, ext, map, c);
  }
  { // mapping
    mda_t a(map);
    check(a, ext, map, c);
  }
  { // extents + container
    mda_t a(ext, c);
    check(a, ext, map, c);
  }
  { // mapping + container
    mda_t a(map, c);
    check(a, ext, map, c);
  }
  { // extents + move(container)
    auto c2 = c;
    double* ptr = c2.data();
    mda_t a(ext, std::move(c2));
    check(a, ext, map, c);
    assert(a.data() == ptr);
  }
  { // mapping + move(container)
    auto c2 = c;
    double* ptr = c2.data();
    mda_t a(map, std::move(c2));
    check(a, ext, map, c);
    assert(a.data() == ptr);
  }
  { // mdspan
    mda_t a(10, 15);
    a(0,0) = 99;
    mda_t b(a.to_mdspan());
    check(b, ext, map, c);
    assert(b(0,0) == 99);
  }
}

// baseline allocator support adds 6 ctors
template<class mda_t, class Container>
void test_alloc_set() {
  using ext_t = typename mda_t::extents_type;
  using map_t = typename mda_t::mapping_type;
  ext_t ext(10, 15);
  map_t map(ext);
  Container c(map.required_span_size());
  auto alloc = std::allocator<typename mda_t::element_type>();

  { // default construction
    mda_t a;
    assert(a.extents() == ext_t());
    assert(a.container_size() == map_t(ext_t()).required_span_size());
  }
  { // integrals -> never directly supported
    #ifdef SUPPORT_ALLOC
    mda_t a(ext_t(10, 15), alloc);
    check(a, ext, map, c);
    #endif
  }
  { // extents
    #ifdef SUPPORT_ALLOC
    mda_t a(ext, alloc);
    check(a, ext, map, c);
    #endif
  }
  { // mapping
    #ifdef SUPPORT_ALLOC
    mda_t a(map, alloc);
    check(a, ext, map, c);
    #endif
  }
  { // extents + container
    #ifdef SUPPORT_ALLOC
    mda_t a(ext, c, alloc);
    #else
    mda_t a(ext, std::move(Container(c,alloc)));
    #endif
    check(a, ext, map, c);
  }
  { // mapping + container
    #ifdef SUPPORT_ALLOC
    mda_t a(map, c, alloc);
    #else
    mda_t a(map, std::move(Container(c,alloc)));
    #endif
    check(a, ext, map, c);
  }
  { // extents + move(container)
    auto c2 = c;
    double* ptr = c2.data();
    #ifdef SUPPORT_ALLOC
    mda_t a(ext, std::move(c2), alloc);
    #else
    mda_t a(ext, std::move(Container(std::move(c2),alloc)));
    #endif
    check(a, ext, map, c);
    assert(a.data() == ptr);
  }
  { // mapping + move(container)
    auto c2 = c;
    double* ptr = c2.data();
    #ifdef SUPPORT_ALLOC
    mda_t a(map, std::move(c2), alloc);
    #else
    mda_t a(map, std::move(Container(std::move(c2),alloc)));
    #endif
    check(a, ext, map, c);
    assert(a.data() == ptr);
  }
}

// construct with fill value adds 2+2(alloc) ctors
template<class mda_t, class Container>
void test_value_set() {
  using ext_t = typename mda_t::extents_type;
  using map_t = typename mda_t::mapping_type;
  ext_t ext(10, 15);
  map_t map(ext);
  Container c(map.required_span_size());
  auto alloc = std::allocator<typename mda_t::element_type>();

  { // default construction
    mda_t a;
    assert(a.extents() == ext_t());
    assert(a.container_size() == map_t(ext_t()).required_span_size());
  }
  { // integrals -> never directly supported
    mda_t a(ext_t(10, 15), 99);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // extents
    mda_t a(ext, 99);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // mapping
    mda_t a(map, 99);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // extents
    mda_t a(ext, 99, alloc);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // mapping
    mda_t a(map, 99, alloc);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
}

template<class mda_t, class Container>
void test_value_set() {
  using ext_t = typename mda_t::extents_type;
  using map_t = typename mda_t::mapping_type;
  ext_t ext(10, 15);
  map_t map(ext);
  Container c(map.required_span_size());
  auto alloc = std::allocator<typename mda_t::element_type>();

  { // default construction
    mda_t a;
    assert(a.extents() == ext_t());
    assert(a.container_size() == map_t(ext_t()).required_span_size());
  }
  { // integrals -> never directly supported
    mda_t a(ext_t(10, 15), 99);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // extents
    mda_t a(ext, 99);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // mapping
    mda_t a(map, 99);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // extents
    mda_t a(ext, 99, alloc);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
  { // mapping
    mda_t a(map, 99, alloc);
    check(a, ext, map, c);
    assert(a(0,0)==99);
  }
}



int main(int argc, char* argv[]) {
  test_minimal_set<Kokkos::Experimental::mdarray<double, Kokkos::extents<int, std::dynamic_extent, std::dynamic_extent>>, std::vector<double>>();
  test_alloc_set<Kokkos::Experimental::mdarray<double, Kokkos::extents<int, std::dynamic_extent, std::dynamic_extent>>, std::vector<double>>();
  test_value_set<Kokkos::Experimental::mdarray<double, Kokkos::extents<int, std::dynamic_extent, std::dynamic_extent>>, std::vector<double>>();
  return 0;
}
