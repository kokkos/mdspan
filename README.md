# Reference `mdspan` implementation

The ISO-C++ proposal [P0009](https://wg21.link/p0009) will add support for non-owning multi-dimensional array references to the C++ standard library.  This repository aims to provide a production-quality implementation of the proposal as written (with a few caveats, see below) in preparation for the addition of `mdspan` to the standard.  Please feel free to use this, file bugs when it breaks, and let us know how it works for you :-)

[Try it out on Godbolt](https://godbolt.org/z/Mxa7cej1a){: .btn }

During the final leg of the ISO C++ committee review process a number of breaking changes were proposed and accepted (issue #136). These are now merged into the stable branch.

Note: There is a tag mdspan-0.3.0 which reflects the status of P0009 before R17 - i.e. it does not have the integral type template parameter for `extents`.
Note: There is a tag mdspan-0.4.0 which reflects the status of P0009 before

* renaming `pointer`, `data`, `is_contiguous` and `is_always_contiguous`; and before
* renaming `size_type` to `index_type` and introducing a new `size_type = make_unsigned_t<index_type>` alias.

## Using `mdspan`

A [tutorial-style introduction](https://github.com/kokkos/mdspan/wiki/A-Gentle-Introduction-to-mdspan) to the basic usage of `mdspan` is provided on the project wiki.  More advanced tutorials to come.

### Including `mdspan` in your code

`mdspan` is a header-only library, and can be included in one of three ways: as a CMake target via `find_package(mdspan <options...>)`, as an include directory, or as a single include file. You can obtain the latest generated single header file from [here](https://github.com/kokkos/mdspan/blob/single-header/mdspan.hpp). This is always kept up to date with the `stable` branch via an automated script.

There are two "modes" of including the `mdspan` headers. The primary way, which we recommend, is via the headers `<mdspan/mdspan.hpp>` and `<mdspan/mdarray.hpp>`. These will define all the mdspan constructs in namespace `Kokkos` for elements that are part of the C++23 standard, and `Kokkos::Experimental` for elements that are being proposed for the C++26 standard.

The second way, is to include the "std-mode" headers. These are `<experimental/mdspan>` and `<experimental/mdarray>`. When included in this way, all elements in the C++23 standard are defined in the `std` namespace, and elements that are proposed for C++26 are in the `std::experimental`. This mode can be useful when writing code for compilers and standard libraries that don't yet support `mdspan`. Note that while we have some compile-time tests for this mode, in general, this mode is **not** portable because adding entities to the `std` namespace is not supported by any compiler. This means that our "std-mode" support can break at any time, and is why we recommend the primary method above.

## Features in Addition To C++ Standard

- C++17 backport (e.g., concepts not required)
- C++14 backport (e.g., fold expressions not required)
  - Compile times of this backport will be substantially slower than the C++17 version
- Macros to enable, e.g., `__device__` marking of all functions for CUDA compatibility

## Building and Installation

This implementation is header-only, with compiler features detected using feature test macros, so you can just use it directly with no building or installation.  If you would like to run the included tests or benchmarks, you'll need CMake.

`mdspan` requires CMake 3.14 or higher, and can build with no dependencies. If you want to build the tests with various backends, such as Cuda or Sycl, these will have to be installed first. Configuring is done in the usual way with CMake. The possible CMake options are documented below:

| Option                     | Description                                                                    | Default  |
| -------------------------- | ------------------------------------------------------------------------------ | -------- |
| `MDSPAN_ENABLE_TESTS`      | Enable tests                                                                   | `OFF`    |
| `MDSPAN_ENABLE_EXAMPLES`   | Enable examples                                                                | `OFF`    |
| `MDSPAN_ENABLE_BENCHMARKS` | Enable Benchmarks                                                              | `OFF`    |
| `MDSPAN_ENABLE_COMP_BENCH` | Enable compilation benchmarks                                                  | `OFF`    |
| `MDSPAN_ENABLE_CUDA`       | Enable Cuda tests/benchmarks/examples if tests/benchmarks/examples are enabled | `OFF`    |
| `MDSPAN_ENABLE_SYCL`       | Enable SYCL tests/benchmarks/examples if tests/benchmarks/examples are enabled | `OFF`    |
| `MDSPAN_ENABLE_HIP`        | Enable HIP tests/benchmarks/examples if tests/benchmarks/examples are enabled  | `OFF`    |
| `MDSPAN_ENABLE_OPENMP`     | Enable OpenMP benchmarks if benchmarks are enabled                             | `ON`     |
| `MDSPAN_USE_SYSTEM_GTEST`  | Use system-installed GoogleTest library for tests                              | `OFF`    |
| `MDSPAN_CXX_STANDARD`      | Override the default CXX_STANDARD to compile with                              | `DETECT` |
| `MDSPAN_ENABLE_CONCEPTS`   | Try to enable concepts support by giving extra flags                           | `ON`     |

### Running tests

#### Configurations

- clang-15 / cmake 3.23
  - Warning free with  `-Wall -Wextra -pedantic` for C++23/20. In C++17 pedantic will give a few warnings, in C++14 Wextra will also give some.
  - `cmake -DMDSPAN_ENABLE_TESTS=ON -DMDSPAN_ENABLE_BENCHMARKS=ON -DCMAKE_CXX_FLAGS="-Werror -Wall -Wextra -pedantic" -DCMAKE_CXX_STANDARD=23 -DMDSPAN_CXX_STANDARD=23 -DCMAKE_CXX_COMPILER=clang++`
- gcc-11 / cmake 3.23
  - Warning free with  `-Wall -Wextra -pedantic` for C++23/20. In C++17 and C++14 pedantic will give a warning (note only with `CMAKE_CXX_EXTENSION=OFF`).
  - `cmake -DMDSPAN_ENABLE_TESTS=ON -DMDSPAN_ENABLE_BENCHMARKS=ON -DCMAKE_CXX_FLAGS="-Werror -Wall -Wextra -pedantic" -DCMAKE_CXX_STANDARD=17 -DMDSPAN_CXX_STANDARD=17 -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_EXTENSIONS=OFF`
- CUDA 11.x / gcc 9.1 / cmake 3.23
  - has a few warnings in C++17 mostly in `mdarray` due to the use of `vector` as container for the tests.
  - Note with CUDA 11.7 and GCC 11.1 as host compiler we observe some issues around CTAD, some of the layout tests won't compile
    - CUDA 11.7 with GCC 9.1 works however
  - `cmake -DMDSPAN_ENABLE_TESTS=ON -DMDSPAN_ENABLE_CUDA=ON -DMDSPAN_ENABLE_BENCHMARKS=ON -DCMAKE_CXX_STANDARD=17 -DCMAKE_CUDA_ARCHITECTURES=70 -DMDSPAN_CXX_STANDARD=17 -DCMAKE_CUDA_FLAGS="--expt-relaxed-constexpr --extended-lambda"`

### Running benchmarks

TODO write this

## Caveats

This implementation is fully conforming with the version of `mdspan` voted into the C++23 draft standard in July 2022.
When not in C++23 mode the implementation deviates from the proposal as follows:

### C++20
- implements `operator()` not `operator[]`
  - note you can control which operator is available with defining `MDSPAN_USE_BRACKET_OPERATOR=[0,1]` and `MDSPAN_USE_PAREN_OPERATOR=[0,1]` irrespective of whether multi dimensional subscript support is detected.

### C++17
- mdspan has a default constructor even in cases where it shouldn't (i.e. all static extents, and default constructible mapping/accessor)
- the conditional explicit markup is missing, making certain constructors implicit
  - most notably you can implicitly convert from dynamic extent to static extent, which you can't in C++20 mode
- there is a constraint on `layout_left::mapping::stride()`, `layout_right::mapping::stride()` and `layout_stride::mapping::stride()` that `extents_type::rank() > 0` is `true`, which is not implemented in C++17 or C++14.

### C++14
- deduction guides don't exist
- submdspan (P2630) is not available - an earlier variant of submdspan is available up to release 0.5 in C++14 mode
- benchmarks are not available (they need submdspan)



# Acknowledgements

This work was undertaken as part of the [Kokkos project](https://github.com/kokkos/kokkos) at Sandia National Laboratories.  Sandia National Laboratories is a multimission laboratory managed and operated by National Technology & Engineering Solutions of Sandia, LLC, a wholly owned subsidary of Honeywell International Inc., for the U. S. Department of Energy's National Nuclear Security Administration under contract DE-NA0003525.

