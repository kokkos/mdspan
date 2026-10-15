Reference `mdspan` implementation
==========================================

This is the Kokkos Project's implementation of the ISO C++ `mdspan` feature with extensions for High Performance Computing (HPC) use-cases.
The implementation underpins the primary data structures of the Kokkos Project and is used in production environments.

**Kokkos MDSpan is part of the [Kokkos C++ Performance Portability Programming Ecosystem](https://kokkos.org).**

Kokkos is a [Linux Foundation](https://linuxfoundation.org) project and a *Core* stage member of the LF's
[High Performance Software Foundation](https://hpsf.io).

Features in Addition To C++ Standard
------------------------------------

* Backport to C++14/17/20/23
  * Not all features are supported in C++14
* Macros to enable, e.g., `__device__` marking of all functions for CUDA compatibility
* Non-standard extensions for device code compatibility

Obtaining Kokkos MDSpan
-----------------------

The latest release of Kokkos's mdspan can be obtained from the [GitHub releases page](https://github.com/kokkos/mdspan/releases/latest).

Support
-------

For questions find us on Slack: https://kokkos.org/community/chat/#slack or open a GitHub issue.

Caveats
-------

This implementation is fully conforming with the version of `mdspan` voted into the C++26 draft standard.
When not at least in C++23 mode the implementation deviates from the proposal as follows:

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
- `layout_left_padded` and `layout_right_padded` are not available.
- benchmarks are not available (they need submdspan)


Building and Installation
-------------------------

This project is a CMake project.

```
cmake -B builddir [<options...>]
cmake --build builddir
cmake --install builddir [--prefix <prefix>]
```

mdspan specific options:

- `MDSPAN_ENABLE_TESTS`: Enable tests. Default: Off
- `MDSPAN_ENABLE_EXAMPLES`: Build examples. Default: Off
- `MDSPAN_ENABLE_BENCHMARKS`: Enable benchmarks. Default: Off
- `MDSPAN_ENABLE_COMP_BENCH`: Enable compilation benchmarks. Default: Off
- `MDSPAN_ENABLE_CUDA`: Enable Cuda tests/benchmarks/examples if tests/benchmarks/examples are enabled. Default: Off
- `MDSPAN_ENABLE_SYCL`: Enable SYCL tests/benchmarks/examples if tests/benchmarks/examples are enabled. Default: Off
- `MDSPAN_ENABLE_HIP`: Enable HIP tests/benchmarks/examples if tests/benchmarks/examples are enabled. Default: Off
- `MDSPAN_ENABLE_OPENMP`: Enable OpenMP benchmarks if benchmarks are enabled. Default: On
- `MDSPAN_CXX_STANDARD`: Set the C++ standard for compiling tests/benchmarks/examples. Default: Auto-Detect
- `MDSPAN_USE_SYSTEM_GTEST`: Use system-installed GoogleTest library for tests. Default: Off
- `MDSPAN_USE_SYSTEM_BENCHMARK`: Use system-installed Google Benchmark library for benchmarks. Default: On

Note: if you only install mdspan, the CUDA/SYCL/HIP/OPENMP options have no real effect.
MDSpan is installed in a *headers only* fashion, and discovers use of CUDA, HIP, SYCL and OpenMP from compiler macros.
Thus a single install of MDSpan can be used for all such downstream use cases.

Contributing
------------

Please see [this page](https://kokkos.org/kokkos-core-wiki/contributing.html) for details on how to contribute.

License
-------

[![License](https://img.shields.io/badge/License-Apache--2.0_WITH_LLVM--exception-blue)](https://spdx.org/licenses/LLVM-exception.html)

The full license statement used in all headers is available [here](https://kokkos.org/kokkos-core-wiki/license.html).

