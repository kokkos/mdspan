
Production-quality `mdspan` implementation
==========================================

The ISO-C++ proposal [P0009](wg21.link/p0009) will add support for non-owning multi-dimensional array references to the C++ standard library.  This repository aims to provide a production-quality implementation of the proposal (with a few caveats, see below) in preparation for the addition of `mdspan` to the standard.

Using `mdspan`
--------------

TODO write this

Features
--------

- C++17 backport (e.g., concepts not required)
- C++14 backport (e.g., fold expressions not required)
  - Compile times of this backport will be substantially slower than the C++17 version
- C++11 backport
  - Compile times of this backport will be substantially slower than the C++14 backport
- Macros to enable, e.g., `__device__` marking of all functions for CUDA compatibility

Building and Installation
-------------------------

TODO write this

### Running tests

TODO write this

### Running benchmarks

TODO write this

Caveats
-------

TODO write this
