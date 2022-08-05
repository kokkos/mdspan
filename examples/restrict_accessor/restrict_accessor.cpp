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

#include <experimental/mdspan>

#include <cassert>
#include <chrono>
#include <iostream>
#include <type_traits>

// mfh 2022/08/04: This is based on my comments on reference mdspan
// implementation issue https://github.com/kokkos/mdspan/issues/169.

namespace {

namespace stdex = std::experimental;

#if defined(_MDSPAN_COMPILER_MSVC) || defined(__INTEL_COMPILER)
#  define _MDSPAN_RESTRICT_KEYWORD __restrict
#elif defined(__GNUC__) || defined(__clang__)
#  define _MDSPAN_RESTRICT_KEYWORD __restrict__
#else
#  define _MDSPAN_RESTRICT_KEYWORD
#endif

#define _MDSPAN_RESTRICT_POINTER( ELEMENT_TYPE ) ELEMENT_TYPE * _MDSPAN_RESTRICT_KEYWORD

// https://en.cppreference.com/w/c/language/restrict gives examples
// of the kinds of optimizations that may apply to restrict.  For instance,
// "[r]estricted pointers can be assigned to unrestricted pointers freely,
// the optimization opportunities remain in place
// as long as the compiler is able to analyze the code:"
//
// void f(int n, float * restrict r, float * restrict s) {
//   float * p = r, * q = s; // OK
//   while(n-- > 0) *p++ = *q++; // almost certainly optimized just like *r++ = *s++
// }
//
// This is relevant because restrict_accessor<ElementType>::reference is _not_ restrict.
// (It's not formally correct to apply C restrict wording to C++ references.
// However, GCC defines this extension:
//
// https://gcc.gnu.org/onlinedocs/gcc/Restricted-Pointers.html
//
// In what follows, I'll assume that this has a reasonable definition.)
// The idea is that even though p[i] has type ElementType& and not ElementType& restrict,
// the compiler can figure out that the reference comes from a pointer based on p,
// which is marked restrict.
//
// Note that any performance improvements can only be determined by experiment.
// Compilers are not required to do anything with restrict.
// Any use of this keyword is not Standard C++,
// so you'll have to refer to the compiler's documentation,
// look at the assembler output, and do performance experiments.
template<class ElementType>
struct restrict_accessor {
  using offset_policy = stdex::default_accessor<ElementType>;
  using element_type = ElementType;
  using reference = ElementType&;
  using data_handle_type = _MDSPAN_RESTRICT_POINTER( ElementType );

  constexpr restrict_accessor() noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType,
    /* requires */ (std::is_convertible<OtherElementType(*)[], element_type(*)[]>::value)
    )
  constexpr restrict_accessor(restrict_accessor<OtherElementType>) noexcept {}

  constexpr reference access(data_handle_type p, size_t i) const noexcept {
    return p[i];
  }
  constexpr typename offset_policy::data_handle_type
  offset(data_handle_type p, size_t i) const noexcept {
    return p + i;
  }
};

// Use int, not size_t, as the index_type.
// Some compilers have trouble optimizing loops with unsigned or 64-bit index types.
using index_type = int;

template<class ElementType>
using restrict_mdspan_1d =
  stdex::mdspan<ElementType, stdex::dextents<index_type, 1>, stdex::layout_right, restrict_accessor<ElementType>>;

template<class ElementType>
using mdspan_1d =
  stdex::mdspan<ElementType, stdex::dextents<index_type, 1>, stdex::layout_right, stdex::default_accessor<ElementType>>;

#define TICK() const auto tick = std::chrono::steady_clock::now()

using double_seconds = std::chrono::duration<double, std::ratio<1>>;
  
#define TOCK() std::chrono::duration_cast<double_seconds>(std::chrono::steady_clock::now() - tick).count()

template<class ElementType>
void add_restrict_mdspan_1d(restrict_mdspan_1d<const ElementType> x, restrict_mdspan_1d<const ElementType> y, restrict_mdspan_1d<ElementType> z)
{
  const index_type n = z.extent(0);
  for (index_type i = 0; i < n; ++i) {
    z[i] = x[i] + y[i];
  }
}

template<class ElementType>
auto benchmark_add_restrict_mdspan_1d(const std::size_t num_trials, const index_type n, const ElementType* x, const ElementType* y, ElementType* z)
{
  TICK();
  restrict_mdspan_1d<const ElementType> x2{x, n};
  restrict_mdspan_1d<const ElementType> y2{y, n};
  restrict_mdspan_1d<ElementType> z2{z, n};
  for (std::size_t trial = 0; trial < num_trials; ++trial) {
    add_restrict_mdspan_1d(x2, y2, z2);
  }
  return TOCK();
}

template<class ElementType>
void add_mdspan_1d(mdspan_1d<const ElementType> x, mdspan_1d<const ElementType> y, mdspan_1d<ElementType> z)
{
  const index_type n = z.extent(0);
  for (index_type i = 0; i < n; ++i) {
    z[i] = x[i] + y[i];
  }
}

template<class ElementType>
auto benchmark_add_mdspan_1d(const std::size_t num_trials, const index_type n, const ElementType* x, const ElementType* y, ElementType* z)
{
  TICK();
  mdspan_1d<const ElementType> x2{x, n};
  mdspan_1d<const ElementType> y2{y, n};
  mdspan_1d<ElementType> z2{z, n};
  for (std::size_t trial = 0; trial < num_trials; ++trial) {
    add_mdspan_1d(x2, y2, z2);
  }
  return TOCK();
}

template<class ElementType>
void add_raw_1d(const index_type n, const ElementType x[], const ElementType y[], ElementType z[])
{
  for (index_type i = 0; i < n; ++i) {
    z[i] = x[i] + y[i];
  }
}

template<class ElementType>
auto benchmark_add_raw_1d(const std::size_t num_trials, const index_type n, const ElementType* x, const ElementType* y, ElementType* z)
{
  TICK();
  for (std::size_t trial = 0; trial < num_trials; ++trial) {
    add_raw_1d(n, x, y, z);
  }
  return TOCK();
}

template<class ElementType>
void add_restrict_raw_1d(const index_type n,
  _MDSPAN_RESTRICT_POINTER(const ElementType) x,
  _MDSPAN_RESTRICT_POINTER(const ElementType) y,
  _MDSPAN_RESTRICT_POINTER(ElementType) z)
{
  for (index_type i = 0; i < n; ++i) {
    z[i] = x[i] + y[i];
  }
}

template<class ElementType>
auto benchmark_add_restrict_raw_1d(const std::size_t num_trials, const index_type n, const ElementType* x, const ElementType* y, ElementType* z)
{
  TICK();
  _MDSPAN_RESTRICT_POINTER(const ElementType) x2 = x;
  _MDSPAN_RESTRICT_POINTER(const ElementType) y2 = y;
  _MDSPAN_RESTRICT_POINTER(ElementType) z2 = z;
  for (std::size_t trial = 0; trial < num_trials; ++trial) {
    add_restrict_raw_1d(n, x2, y2, z2);
  }
  return TOCK();
}

// Start with restrict pointers, then assign to nonrestrict pointers.
// This checks whether the compiler's alias analysis suffices.
template<class ElementType>
void add_unrestrict_raw_1d(const index_type n,
  _MDSPAN_RESTRICT_POINTER(const ElementType) x,
  _MDSPAN_RESTRICT_POINTER(const ElementType) y,
  _MDSPAN_RESTRICT_POINTER(ElementType) z)
{
  const ElementType* x2 = x;
  const ElementType* y2 = y;
  ElementType* z2 = z;
  add_raw_1d(n, x2, y2, z2);
}

template<class ElementType>
auto benchmark_add_unrestrict_raw_1d(const std::size_t num_trials, const index_type n, const ElementType* x, const ElementType* y, ElementType* z)
{
  TICK();
  _MDSPAN_RESTRICT_POINTER(const ElementType) x2 = x;
  _MDSPAN_RESTRICT_POINTER(const ElementType) y2 = y;
  _MDSPAN_RESTRICT_POINTER(ElementType) z2 = z;
  for (std::size_t trial = 0; trial < num_trials; ++trial) {
    add_unrestrict_raw_1d(n, x2, y2, z2);
  }
  return TOCK();
}

template<class ElementType>
auto warmup(const std::size_t num_trials, const index_type n, const ElementType* x, const ElementType* y, ElementType* z)
{
  return benchmark_add_raw_1d(num_trials, n, x, y, z);
}

} // namespace (anonymous)

int main(int argc, char* argv[])
{
  using std::cout;
  using std::cerr;
  using std::endl;
  
  if(argc != 3) {
    cerr << "Usage: main <n> <num_trials>" << endl;
    return -1;
  }
  
  int n = 10000;
  int num_trials = 100;
  n = std::stoi(argv[1]);
  num_trials = std::stoi(argv[2]);

  std::vector<double> x(n);
  std::vector<double> y(n);
  std::vector<double> z(n);

  auto warmup_result = warmup(num_trials, n, x.data(), y.data(), z.data());
  auto restrict_mdspan_result = benchmark_add_restrict_mdspan_1d(num_trials, n, x.data(), y.data(), z.data());
  auto mdspan_result = benchmark_add_mdspan_1d(num_trials, n, x.data(), y.data(), z.data());
  auto raw_result = benchmark_add_raw_1d(num_trials, n, x.data(), y.data(), z.data());
  auto restrict_raw_result = benchmark_add_restrict_raw_1d(num_trials, n, x.data(), y.data(), z.data());
  auto unrestrict_raw_result = benchmark_add_unrestrict_raw_1d(num_trials, n, x.data(), y.data(), z.data());

  cout << "num_trials: " << num_trials << ", n: " << n << endl
       << "Total time (unit: second):" << endl
       << "  warmup: " << warmup_result << endl
       << "  restrict_mdspan: " << restrict_mdspan_result << endl
       << "  mdspan: " << mdspan_result << endl
       << "  raw_mdspan: " << raw_result << endl
       << "  restrict_raw: " << restrict_raw_result << endl
       << "  unrestrict_raw: " << unrestrict_raw_result << endl;
  return 0;
}
