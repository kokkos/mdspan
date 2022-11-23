#ifndef _MDSPAN_SINGLE_HEADER_INCLUDE_GUARD_
#define _MDSPAN_SINGLE_HEADER_INCLUDE_GUARD_
#  include <version>
#  include <type_traits>
#  include <utility>
#include <type_traits> // std::is_void
#include <cstddef> // size_t
#include <type_traits>
#include <utility> // integer_sequence
#include <cstddef>  // size_t
#include <limits>   // numeric_limits
#include <array>
#include <span>
#include <utility> // integer_sequence
#include <cstddef>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <array>
#include <span>
#include<concepts>
#include <tuple> // std::apply
#include <utility> // std::pair
#include <cassert>
#include <vector>

//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/mdarray
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


//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/mdspan
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


//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/default_accessor.hpp
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


//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/macros.hpp
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



//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/config.hpp
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


#ifndef __has_include
#  define __has_include(x) 0
#endif

#if __has_include(<version>)
#else
#endif

#ifdef _MSVC_LANG
#define _MDSPAN_CPLUSPLUS _MSVC_LANG
#else
#define _MDSPAN_CPLUSPLUS __cplusplus
#endif

#define MDSPAN_CXX_STD_14 201402L
#define MDSPAN_CXX_STD_17 201703L
#define MDSPAN_CXX_STD_20 202002L

#define MDSPAN_HAS_CXX_14 (_MDSPAN_CPLUSPLUS >= MDSPAN_CXX_STD_14)
#define MDSPAN_HAS_CXX_17 (_MDSPAN_CPLUSPLUS >= MDSPAN_CXX_STD_17)
#define MDSPAN_HAS_CXX_20 (_MDSPAN_CPLUSPLUS >= MDSPAN_CXX_STD_20)

static_assert(_MDSPAN_CPLUSPLUS >= MDSPAN_CXX_STD_14, "mdspan requires C++14 or later.");

#ifndef _MDSPAN_COMPILER_CLANG
#  if defined(__clang__)
#    define _MDSPAN_COMPILER_CLANG __clang__
#  endif
#endif

#if !defined(_MDSPAN_COMPILER_MSVC) && !defined(_MDSPAN_COMPILER_MSVC_CLANG)
#  if defined(_MSC_VER)
#    if !defined(_MDSPAN_COMPILER_CLANG)
#      define _MDSPAN_COMPILER_MSVC _MSC_VER
#    else
#      define _MDSPAN_COMPILER_MSVC_CLANG _MSC_VER
#    endif
#  endif
#endif

#ifndef _MDSPAN_COMPILER_INTEL
#  ifdef __INTEL_COMPILER
#    define _MDSPAN_COMPILER_INTEL __INTEL_COMPILER
#  endif
#endif

#ifndef _MDSPAN_COMPILER_APPLECLANG
#  ifdef __apple_build_version__
#    define _MDSPAN_COMPILER_APPLECLANG __apple_build_version__
#  endif
#endif

#ifndef _MDSPAN_HAS_CUDA
#  if defined(__CUDACC__)
#    define _MDSPAN_HAS_CUDA __CUDACC__
#  endif
#endif

#ifndef _MDSPAN_HAS_HIP
#  if defined(__HIPCC__)
#    define _MDSPAN_HAS_HIP __HIPCC__
#  endif
#endif

#ifndef __has_cpp_attribute
#  define __has_cpp_attribute(x) 0
#endif

#ifndef _MDSPAN_PRESERVE_STANDARD_LAYOUT
// Preserve standard layout by default, but we're not removing the old version
// that turns this off until we're sure this doesn't have an unreasonable cost
// to the compiler or optimizer.
#  define _MDSPAN_PRESERVE_STANDARD_LAYOUT 1
#endif

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#  if ((__has_cpp_attribute(no_unique_address) >= 201803L) && \
       (!defined(__NVCC__) || MDSPAN_HAS_CXX_20) && \
       (!defined(_MDSPAN_COMPILER_MSVC) || MDSPAN_HAS_CXX_20))
#    define _MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS 1
#    define _MDSPAN_NO_UNIQUE_ADDRESS [[no_unique_address]]
#  else
#    define _MDSPAN_NO_UNIQUE_ADDRESS
#  endif
#endif

// NVCC older than 11.6 chokes on the no-unique-address-emulation
// so just pretend to use it (to avoid the full blown EBO workaround
// which NVCC also doesn't like ...), and leave the macro empty
#ifndef _MDSPAN_NO_UNIQUE_ADDRESS
#  if defined(__NVCC__)
#    define _MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS 1
#    define _MDSPAN_USE_FAKE_ATTRIBUTE_NO_UNIQUE_ADDRESS
#  endif
#  define _MDSPAN_NO_UNIQUE_ADDRESS
#endif

#ifndef _MDSPAN_USE_CONCEPTS
#  if defined(__cpp_concepts) && __cpp_concepts >= 201507L
#    define _MDSPAN_USE_CONCEPTS 1
#  endif
#endif

#ifndef _MDSPAN_USE_FOLD_EXPRESSIONS
#  if (defined(__cpp_fold_expressions) && __cpp_fold_expressions >= 201603L) \
          || (!defined(__cpp_fold_expressions) && MDSPAN_HAS_CXX_17)
#    define _MDSPAN_USE_FOLD_EXPRESSIONS 1
#  endif
#endif

#ifndef _MDSPAN_USE_INLINE_VARIABLES
#  if defined(__cpp_inline_variables) && __cpp_inline_variables >= 201606L \
         || (!defined(__cpp_inline_variables) && MDSPAN_HAS_CXX_17)
#    define _MDSPAN_USE_INLINE_VARIABLES 1
#  endif
#endif

#ifndef _MDSPAN_NEEDS_TRAIT_VARIABLE_TEMPLATE_BACKPORTS
#  if (!(defined(__cpp_lib_type_trait_variable_templates) && __cpp_lib_type_trait_variable_templates >= 201510L) \
          || !MDSPAN_HAS_CXX_17)
#    if !(defined(_MDSPAN_COMPILER_APPLECLANG) && MDSPAN_HAS_CXX_17)
#      define _MDSPAN_NEEDS_TRAIT_VARIABLE_TEMPLATE_BACKPORTS 1
#    endif
#  endif
#endif

#ifndef _MDSPAN_USE_VARIABLE_TEMPLATES
#  if (defined(__cpp_variable_templates) && __cpp_variable_templates >= 201304 && MDSPAN_HAS_CXX_17) \
        || (!defined(__cpp_variable_templates) && MDSPAN_HAS_CXX_17)
#    define _MDSPAN_USE_VARIABLE_TEMPLATES 1
#  endif
#endif // _MDSPAN_USE_VARIABLE_TEMPLATES

#ifndef _MDSPAN_USE_CONSTEXPR_14
#  if (defined(__cpp_constexpr) && __cpp_constexpr >= 201304) \
        || (!defined(__cpp_constexpr) && MDSPAN_HAS_CXX_14) \
        && (!(defined(__INTEL_COMPILER) && __INTEL_COMPILER <= 1700))
#    define _MDSPAN_USE_CONSTEXPR_14 1
#  endif
#endif

#ifndef _MDSPAN_USE_INTEGER_SEQUENCE
#  if defined(_MDSPAN_COMPILER_MSVC)
#    if (defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304)
#      define _MDSPAN_USE_INTEGER_SEQUENCE 1
#    endif
#  endif
#endif
#ifndef _MDSPAN_USE_INTEGER_SEQUENCE
#  if (defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304) \
        || (!defined(__cpp_lib_integer_sequence) && MDSPAN_HAS_CXX_14) \
        /* as far as I can tell, libc++ seems to think this is a C++11 feature... */ \
        || (defined(__GLIBCXX__) && __GLIBCXX__ > 20150422 && __GNUC__ < 5 && !defined(__INTEL_CXX11_MODE__))
     // several compilers lie about integer_sequence working properly unless the C++14 standard is used
#    define _MDSPAN_USE_INTEGER_SEQUENCE 1
#  elif defined(_MDSPAN_COMPILER_APPLECLANG) && MDSPAN_HAS_CXX_14
     // appleclang seems to be missing the __cpp_lib_... macros, but doesn't seem to lie about C++14 making
     // integer_sequence work
#    define _MDSPAN_USE_INTEGER_SEQUENCE 1
#  endif
#endif

#ifndef _MDSPAN_USE_RETURN_TYPE_DEDUCTION
#  if (defined(__cpp_return_type_deduction) && __cpp_return_type_deduction >= 201304) \
          || (!defined(__cpp_return_type_deduction) && MDSPAN_HAS_CXX_14)
#    define _MDSPAN_USE_RETURN_TYPE_DEDUCTION 1
#  endif
#endif

#ifndef _MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION
// GCC 10's CTAD seems sufficiently broken to prevent its use.
#  if (defined(_MDSPAN_COMPILER_CLANG) || !defined(__GNUC__) || __GNUC__ >= 11) \
      && ((defined(__cpp_deduction_guides) && __cpp_deduction_guides >= 201703) \
         || (!defined(__cpp_deduction_guides) && MDSPAN_HAS_CXX_17))
#    define _MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION 1
#  endif
#endif

#ifndef _MDSPAN_USE_ALIAS_TEMPLATE_ARGUMENT_DEDUCTION
// GCC 10's CTAD seems sufficiently broken to prevent its use.
#  if (defined(_MDSPAN_COMPILER_CLANG) || !defined(__GNUC__) || __GNUC__ >= 11) \
      && ((defined(__cpp_deduction_guides) && __cpp_deduction_guides >= 201907) \
          || (!defined(__cpp_deduction_guides) && MDSPAN_HAS_CXX_20))
#    define _MDSPAN_USE_ALIAS_TEMPLATE_ARGUMENT_DEDUCTION 1
#  endif
#endif

#ifndef _MDSPAN_USE_STANDARD_TRAIT_ALIASES
#  if (defined(__cpp_lib_transformation_trait_aliases) && __cpp_lib_transformation_trait_aliases >= 201304) \
          || (!defined(__cpp_lib_transformation_trait_aliases) && MDSPAN_HAS_CXX_14)
#    define _MDSPAN_USE_STANDARD_TRAIT_ALIASES 1
#  elif defined(_MDSPAN_COMPILER_APPLECLANG) && MDSPAN_HAS_CXX_14
     // appleclang seems to be missing the __cpp_lib_... macros, but doesn't seem to lie about C++14
#    define _MDSPAN_USE_STANDARD_TRAIT_ALIASES 1
#  endif
#endif

#ifndef _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND
#  ifdef __GNUC__
#    if __GNUC__ < 9
#      define _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND 1
#    endif
#  endif
#endif

#ifndef MDSPAN_CONDITIONAL_EXPLICIT
#  if MDSPAN_HAS_CXX_20 && !defined(_MDSPAN_COMPILER_MSVC)
#    define MDSPAN_CONDITIONAL_EXPLICIT(COND) explicit(COND)
#  else
#    define MDSPAN_CONDITIONAL_EXPLICIT(COND)
#  endif
#endif

#ifndef MDSPAN_USE_BRACKET_OPERATOR
#  if defined(__cpp_multidimensional_subscript)
#    define MDSPAN_USE_BRACKET_OPERATOR 1
#  else
#    define MDSPAN_USE_BRACKET_OPERATOR 0
#  endif
#endif

#ifndef MDSPAN_USE_PAREN_OPERATOR
#  if !MDSPAN_USE_BRACKET_OPERATOR
#    define MDSPAN_USE_PAREN_OPERATOR 1
#  else
#    define MDSPAN_USE_PAREN_OPERATOR 0
#  endif
#endif

#if MDSPAN_USE_BRACKET_OPERATOR
#  define __MDSPAN_OP(mds,...) mds[__VA_ARGS__]
// Corentins demo compiler for subscript chokes on empty [] call,
// though I believe the proposal supports it?
#ifdef MDSPAN_NO_EMPTY_BRACKET_OPERATOR
#  define __MDSPAN_OP0(mds) mds.accessor().access(mds.data_handle(),0)
#else
#  define __MDSPAN_OP0(mds) mds[]
#endif
#  define __MDSPAN_OP1(mds, a) mds[a]
#  define __MDSPAN_OP2(mds, a, b) mds[a,b]
#  define __MDSPAN_OP3(mds, a, b, c) mds[a,b,c]
#  define __MDSPAN_OP4(mds, a, b, c, d) mds[a,b,c,d]
#  define __MDSPAN_OP5(mds, a, b, c, d, e) mds[a,b,c,d,e]
#  define __MDSPAN_OP6(mds, a, b, c, d, e, f) mds[a,b,c,d,e,f]
#else
#  define __MDSPAN_OP(mds,...) mds(__VA_ARGS__)
#  define __MDSPAN_OP0(mds) mds()
#  define __MDSPAN_OP1(mds, a) mds(a)
#  define __MDSPAN_OP2(mds, a, b) mds(a,b)
#  define __MDSPAN_OP3(mds, a, b, c) mds(a,b,c)
#  define __MDSPAN_OP4(mds, a, b, c, d) mds(a,b,c,d)
#  define __MDSPAN_OP5(mds, a, b, c, d, e) mds(a,b,c,d,e)
#  define __MDSPAN_OP6(mds, a, b, c, d, e, f) mds(a,b,c,d,e,f)
#endif
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/config.hpp


#ifndef _MDSPAN_HOST_DEVICE
#  if defined(_MDSPAN_HAS_CUDA) || defined(_MDSPAN_HAS_HIP)
#    define _MDSPAN_HOST_DEVICE __host__ __device__
#  else
#    define _MDSPAN_HOST_DEVICE
#  endif
#endif

#ifndef MDSPAN_FORCE_INLINE_FUNCTION
#  ifdef _MDSPAN_COMPILER_MSVC // Microsoft compilers
#    define MDSPAN_FORCE_INLINE_FUNCTION __forceinline _MDSPAN_HOST_DEVICE
#  else
#    define MDSPAN_FORCE_INLINE_FUNCTION __attribute__((always_inline)) _MDSPAN_HOST_DEVICE
#  endif
#endif

#ifndef MDSPAN_INLINE_FUNCTION
#  define MDSPAN_INLINE_FUNCTION inline _MDSPAN_HOST_DEVICE
#endif

// In CUDA defaulted functions do not need host device markup
#ifndef MDSPAN_INLINE_FUNCTION_DEFAULTED
#  define MDSPAN_INLINE_FUNCTION_DEFAULTED
#endif

//==============================================================================
// <editor-fold desc="Preprocessor helpers"> {{{1

#define MDSPAN_PP_COUNT(...) \
  _MDSPAN_PP_INTERNAL_EXPAND_ARGS_PRIVATE( \
    _MDSPAN_PP_INTERNAL_ARGS_AUGMENTER(__VA_ARGS__) \
  )

#define _MDSPAN_PP_INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#define _MDSPAN_PP_INTERNAL_EXPAND(x) x
#define _MDSPAN_PP_INTERNAL_EXPAND_ARGS_PRIVATE(...) \
  _MDSPAN_PP_INTERNAL_EXPAND( \
    _MDSPAN_PP_INTERNAL_COUNT_PRIVATE( \
      __VA_ARGS__, 69, 68, 67, 66, 65, 64, 63, 62, 61, \
      60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49,  \
      48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37,  \
      36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25,  \
      24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13,  \
      12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 \
    ) \
  )
# define _MDSPAN_PP_INTERNAL_COUNT_PRIVATE( \
         _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, \
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
    _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, \
    _70, count, ...) count \
    /**/

#define MDSPAN_PP_STRINGIFY_IMPL(x) #x
#define MDSPAN_PP_STRINGIFY(x) MDSPAN_PP_STRINGIFY_IMPL(x)

#define MDSPAN_PP_CAT_IMPL(x, y) x ## y
#define MDSPAN_PP_CAT(x, y) MDSPAN_PP_CAT_IMPL(x, y)

#define MDSPAN_PP_EVAL(X, ...) X(__VA_ARGS__)

#define MDSPAN_PP_REMOVE_PARENS_IMPL(...) __VA_ARGS__
#define MDSPAN_PP_REMOVE_PARENS(...) MDSPAN_PP_REMOVE_PARENS_IMPL __VA_ARGS__

// </editor-fold> end Preprocessor helpers }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="Concept emulation"> {{{1

// These compatibility macros don't help with partial ordering, but they should do the trick
// for what we need to do with concepts in mdspan
#ifdef _MDSPAN_USE_CONCEPTS
#  define MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) > requires REQ
#  define MDSPAN_FUNCTION_REQUIRES(PAREN_PREQUALS, FNAME, PAREN_PARAMS, QUALS, REQ) \
     MDSPAN_PP_REMOVE_PARENS(PAREN_PREQUALS) FNAME PAREN_PARAMS QUALS requires REQ \
     /**/
#else
#  define MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) , typename ::std::enable_if<(REQ), int>::type = 0>
#  define MDSPAN_FUNCTION_REQUIRES(PAREN_PREQUALS, FNAME, PAREN_PARAMS, QUALS, REQ) \
     MDSPAN_TEMPLATE_REQUIRES( \
       class __function_requires_ignored=void, \
       (std::is_void<__function_requires_ignored>::value && REQ) \
     ) MDSPAN_PP_REMOVE_PARENS(PAREN_PREQUALS) FNAME PAREN_PARAMS QUALS \
     /**/
#endif


#if defined(_MDSPAN_COMPILER_MSVC)
#  define MDSPAN_TEMPLATE_REQUIRES(...) \
      MDSPAN_PP_CAT( \
        MDSPAN_PP_CAT(MDSPAN_TEMPLATE_REQUIRES_, MDSPAN_PP_COUNT(__VA_ARGS__))\
        (__VA_ARGS__), \
      ) \
    /**/
#else
#  define MDSPAN_TEMPLATE_REQUIRES(...) \
    MDSPAN_PP_EVAL( \
        MDSPAN_PP_CAT(MDSPAN_TEMPLATE_REQUIRES_, MDSPAN_PP_COUNT(__VA_ARGS__)), \
        __VA_ARGS__ \
    ) \
    /**/
#endif

#define MDSPAN_TEMPLATE_REQUIRES_2(TP1, REQ) \
  template<TP1 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_3(TP1, TP2, REQ) \
  template<TP1, TP2 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_4(TP1, TP2, TP3, REQ) \
  template<TP1, TP2, TP3 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_5(TP1, TP2, TP3, TP4, REQ) \
  template<TP1, TP2, TP3, TP4 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_6(TP1, TP2, TP3, TP4, TP5, REQ) \
  template<TP1, TP2, TP3, TP4, TP5 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_7(TP1, TP2, TP3, TP4, TP5, TP6, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_8(TP1, TP2, TP3, TP4, TP5, TP6, TP7, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_9(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_10(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_11(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_12(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_13(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_14(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_15(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_16(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_17(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_18(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16, TP17, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16, TP17 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_19(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16, TP17, TP18, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16, TP17, TP18 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/
#define MDSPAN_TEMPLATE_REQUIRES_20(TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16, TP17, TP18, TP19, REQ) \
  template<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10, TP11, TP12, TP13, TP14, TP15, TP16, TP17, TP18, TP19 \
    MDSPAN_CLOSE_ANGLE_REQUIRES(REQ) \
    /**/

#define MDSPAN_INSTANTIATE_ONLY_IF_USED \
  MDSPAN_TEMPLATE_REQUIRES( \
    class __instantiate_only_if_used_tparam=void, \
    ( _MDSPAN_TRAIT(std::is_void, __instantiate_only_if_used_tparam) ) \
  ) \
  /**/

// </editor-fold> end Concept emulation }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="inline variables"> {{{1

#ifdef _MDSPAN_USE_INLINE_VARIABLES
#  define _MDSPAN_INLINE_VARIABLE inline
#else
#  define _MDSPAN_INLINE_VARIABLE
#endif

// </editor-fold> end inline variables }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="Return type deduction"> {{{1

#if _MDSPAN_USE_RETURN_TYPE_DEDUCTION
#  define _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(SIGNATURE, BODY) \
    auto MDSPAN_PP_REMOVE_PARENS(SIGNATURE) { return MDSPAN_PP_REMOVE_PARENS(BODY); }
#  define _MDSPAN_DEDUCE_DECLTYPE_AUTO_RETURN_TYPE_SINGLE_LINE(SIGNATURE, BODY) \
    decltype(auto) MDSPAN_PP_REMOVE_PARENS(SIGNATURE) { return MDSPAN_PP_REMOVE_PARENS(BODY); }
#else
#  define _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(SIGNATURE, BODY) \
    auto MDSPAN_PP_REMOVE_PARENS(SIGNATURE) \
      -> std::remove_cv_t<std::remove_reference_t<decltype(BODY)>> \
    { return MDSPAN_PP_REMOVE_PARENS(BODY); }
#  define _MDSPAN_DEDUCE_DECLTYPE_AUTO_RETURN_TYPE_SINGLE_LINE(SIGNATURE, BODY) \
    auto MDSPAN_PP_REMOVE_PARENS(SIGNATURE) \
      -> decltype(BODY) \
    { return MDSPAN_PP_REMOVE_PARENS(BODY); }

#endif

// </editor-fold> end Return type deduction }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="fold expressions"> {{{1

struct __mdspan_enable_fold_comma { };

#ifdef _MDSPAN_USE_FOLD_EXPRESSIONS
#  define _MDSPAN_FOLD_AND(...) ((__VA_ARGS__) && ...)
#  define _MDSPAN_FOLD_AND_TEMPLATE(...) ((__VA_ARGS__) && ...)
#  define _MDSPAN_FOLD_OR(...) ((__VA_ARGS__) || ...)
#  define _MDSPAN_FOLD_ASSIGN_LEFT(INIT, ...) (INIT = ... = (__VA_ARGS__))
#  define _MDSPAN_FOLD_ASSIGN_RIGHT(PACK, ...) (PACK = ... = (__VA_ARGS__))
#  define _MDSPAN_FOLD_TIMES_RIGHT(PACK, ...) (PACK * ... * (__VA_ARGS__))
#  define _MDSPAN_FOLD_PLUS_RIGHT(PACK, ...) (PACK + ... + (__VA_ARGS__))
#  define _MDSPAN_FOLD_COMMA(...) ((__VA_ARGS__), ...)
#else

namespace std {

namespace __fold_compatibility_impl {

// We could probably be more clever here, but at the (small) risk of losing some compiler understanding.  For the
// few operations we need, it's not worth generalizing over the operation

#if _MDSPAN_USE_RETURN_TYPE_DEDUCTION

MDSPAN_FORCE_INLINE_FUNCTION
constexpr decltype(auto) __fold_right_and_impl() {
  return true;
}

template <class Arg, class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr decltype(auto) __fold_right_and_impl(Arg&& arg, Args&&... args) {
  return ((Arg&&)arg) && __fold_compatibility_impl::__fold_right_and_impl((Args&&)args...);
}

MDSPAN_FORCE_INLINE_FUNCTION
constexpr decltype(auto) __fold_right_or_impl() {
  return false;
}

template <class Arg, class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_right_or_impl(Arg&& arg, Args&&... args) {
  return ((Arg&&)arg) || __fold_compatibility_impl::__fold_right_or_impl((Args&&)args...);
}

template <class Arg1>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_left_assign_impl(Arg1&& arg1) {
  return (Arg1&&)arg1;
}

template <class Arg1, class Arg2, class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_left_assign_impl(Arg1&& arg1, Arg2&& arg2, Args&&... args) {
  return __fold_compatibility_impl::__fold_left_assign_impl((((Arg1&&)arg1) = ((Arg2&&)arg2)), (Args&&)args...);
}

template <class Arg1>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_right_assign_impl(Arg1&& arg1) {
  return (Arg1&&)arg1;
}

template <class Arg1, class Arg2, class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_right_assign_impl(Arg1&& arg1, Arg2&& arg2,  Args&&... args) {
  return ((Arg1&&)arg1) = __fold_compatibility_impl::__fold_right_assign_impl((Arg2&&)arg2, (Args&&)args...);
}

template <class Arg1>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_right_plus_impl(Arg1&& arg1) {
  return (Arg1&&)arg1;
}

template <class Arg1, class Arg2, class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_right_plus_impl(Arg1&& arg1, Arg2&& arg2, Args&&... args) {
  return ((Arg1&&)arg1) + __fold_compatibility_impl::__fold_right_plus_impl((Arg2&&)arg2, (Args&&)args...);
}

template <class Arg1>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_right_times_impl(Arg1&& arg1) {
  return (Arg1&&)arg1;
}

template <class Arg1, class Arg2, class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr auto __fold_right_times_impl(Arg1&& arg1, Arg2&& arg2, Args&&... args) {
  return ((Arg1&&)arg1) * __fold_compatibility_impl::__fold_right_times_impl((Arg2&&)arg2, (Args&&)args...);
}

#else

//------------------------------------------------------------------------------
// <editor-fold desc="right and"> {{{2

template <class... Args>
struct __fold_right_and_impl_;
template <>
struct __fold_right_and_impl_<> {
  using __rv = bool;
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl() noexcept {
    return true;
  }
};
template <class Arg, class... Args>
struct __fold_right_and_impl_<Arg, Args...> {
  using __next_t = __fold_right_and_impl_<Args...>;
  using __rv = decltype(std::declval<Arg>() && std::declval<typename __next_t::__rv>());
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg&& arg, Args&&... args) noexcept {
    return ((Arg&&)arg) && __next_t::__impl((Args&&)args...);
  }
};

template <class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr typename __fold_right_and_impl_<Args...>::__rv
__fold_right_and_impl(Args&&... args) {
  return __fold_right_and_impl_<Args...>::__impl((Args&&)args...);
}

// </editor-fold> end right and }}}2
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// <editor-fold desc="right or"> {{{2

template <class... Args>
struct __fold_right_or_impl_;
template <>
struct __fold_right_or_impl_<> {
  using __rv = bool;
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl() noexcept {
    return false;
  }
};
template <class Arg, class... Args>
struct __fold_right_or_impl_<Arg, Args...> {
  using __next_t = __fold_right_or_impl_<Args...>;
  using __rv = decltype(std::declval<Arg>() || std::declval<typename __next_t::__rv>());
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg&& arg, Args&&... args) noexcept {
    return ((Arg&&)arg) || __next_t::__impl((Args&&)args...);
  }
};

template <class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr typename __fold_right_or_impl_<Args...>::__rv
__fold_right_or_impl(Args&&... args) {
  return __fold_right_or_impl_<Args...>::__impl((Args&&)args...);
}

// </editor-fold> end right or }}}2
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// <editor-fold desc="right plus"> {{{2

template <class... Args>
struct __fold_right_plus_impl_;
template <class Arg>
struct __fold_right_plus_impl_<Arg> {
  using __rv = Arg&&;
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg&& arg) noexcept {
    return (Arg&&)arg;
  }
};
template <class Arg1, class Arg2, class... Args>
struct __fold_right_plus_impl_<Arg1, Arg2, Args...> {
  using __next_t = __fold_right_plus_impl_<Arg2, Args...>;
  using __rv = decltype(std::declval<Arg1>() + std::declval<typename __next_t::__rv>());
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg1&& arg, Arg2&& arg2, Args&&... args) noexcept {
    return ((Arg1&&)arg) + __next_t::__impl((Arg2&&)arg2, (Args&&)args...);
  }
};

template <class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr typename __fold_right_plus_impl_<Args...>::__rv
__fold_right_plus_impl(Args&&... args) {
  return __fold_right_plus_impl_<Args...>::__impl((Args&&)args...);
}

// </editor-fold> end right plus }}}2
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// <editor-fold desc="right times"> {{{2

template <class... Args>
struct __fold_right_times_impl_;
template <class Arg>
struct __fold_right_times_impl_<Arg> {
  using __rv = Arg&&;
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg&& arg) noexcept {
    return (Arg&&)arg;
  }
};
template <class Arg1, class Arg2, class... Args>
struct __fold_right_times_impl_<Arg1, Arg2, Args...> {
  using __next_t = __fold_right_times_impl_<Arg2, Args...>;
  using __rv = decltype(std::declval<Arg1>() * std::declval<typename __next_t::__rv>());
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg1&& arg, Arg2&& arg2, Args&&... args) noexcept {
    return ((Arg1&&)arg) * __next_t::__impl((Arg2&&)arg2, (Args&&)args...);
  }
};

template <class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr typename __fold_right_times_impl_<Args...>::__rv
__fold_right_times_impl(Args&&... args) {
  return __fold_right_times_impl_<Args...>::__impl((Args&&)args...);
}

// </editor-fold> end right times }}}2
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// <editor-fold desc="right assign"> {{{2

template <class... Args>
struct __fold_right_assign_impl_;
template <class Arg>
struct __fold_right_assign_impl_<Arg> {
  using __rv = Arg&&;
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg&& arg) noexcept {
    return (Arg&&)arg;
  }
};
template <class Arg1, class Arg2, class... Args>
struct __fold_right_assign_impl_<Arg1, Arg2, Args...> {
  using __next_t = __fold_right_assign_impl_<Arg2, Args...>;
  using __rv = decltype(std::declval<Arg1>() = std::declval<typename __next_t::__rv>());
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg1&& arg, Arg2&& arg2, Args&&... args) noexcept {
    return ((Arg1&&)arg) = __next_t::__impl((Arg2&&)arg2, (Args&&)args...);
  }
};

template <class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr typename __fold_right_assign_impl_<Args...>::__rv
__fold_right_assign_impl(Args&&... args) {
  return __fold_right_assign_impl_<Args...>::__impl((Args&&)args...);
}

// </editor-fold> end right assign }}}2
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// <editor-fold desc="left assign"> {{{2

template <class... Args>
struct __fold_left_assign_impl_;
template <class Arg>
struct __fold_left_assign_impl_<Arg> {
  using __rv = Arg&&;
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg&& arg) noexcept {
    return (Arg&&)arg;
  }
};
template <class Arg1, class Arg2, class... Args>
struct __fold_left_assign_impl_<Arg1, Arg2, Args...> {
  using __assign_result_t = decltype(std::declval<Arg1>() = std::declval<Arg2>());
  using __next_t = __fold_left_assign_impl_<__assign_result_t, Args...>;
  using __rv = typename __next_t::__rv;
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr __rv
  __impl(Arg1&& arg, Arg2&& arg2, Args&&... args) noexcept {
    return __next_t::__impl(((Arg1&&)arg) = (Arg2&&)arg2, (Args&&)args...);
  }
};

template <class... Args>
MDSPAN_FORCE_INLINE_FUNCTION
constexpr typename __fold_left_assign_impl_<Args...>::__rv
__fold_left_assign_impl(Args&&... args) {
  return __fold_left_assign_impl_<Args...>::__impl((Args&&)args...);
}

// </editor-fold> end left assign }}}2
//------------------------------------------------------------------------------

#endif


template <class... Args>
constexpr __mdspan_enable_fold_comma __fold_comma_impl(Args&&... args) noexcept { return { }; }

template <bool... Bs>
struct __bools;

} // __fold_compatibility_impl

} // end namespace std

#  define _MDSPAN_FOLD_AND(...) std::__fold_compatibility_impl::__fold_right_and_impl((__VA_ARGS__)...)
#  define _MDSPAN_FOLD_OR(...) std::__fold_compatibility_impl::__fold_right_or_impl((__VA_ARGS__)...)
#  define _MDSPAN_FOLD_ASSIGN_LEFT(INIT, ...) std::__fold_compatibility_impl::__fold_left_assign_impl(INIT, (__VA_ARGS__)...)
#  define _MDSPAN_FOLD_ASSIGN_RIGHT(PACK, ...) std::__fold_compatibility_impl::__fold_right_assign_impl((PACK)..., __VA_ARGS__)
#  define _MDSPAN_FOLD_TIMES_RIGHT(PACK, ...) std::__fold_compatibility_impl::__fold_right_times_impl((PACK)..., __VA_ARGS__)
#  define _MDSPAN_FOLD_PLUS_RIGHT(PACK, ...) std::__fold_compatibility_impl::__fold_right_plus_impl((PACK)..., __VA_ARGS__)
#  define _MDSPAN_FOLD_COMMA(...) std::__fold_compatibility_impl::__fold_comma_impl((__VA_ARGS__)...)

#  define _MDSPAN_FOLD_AND_TEMPLATE(...) \
  _MDSPAN_TRAIT(std::is_same, __fold_compatibility_impl::__bools<(__VA_ARGS__)..., true>, __fold_compatibility_impl::__bools<true, (__VA_ARGS__)...>)

#endif

// </editor-fold> end fold expressions }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="Variable template compatibility"> {{{1

#if _MDSPAN_USE_VARIABLE_TEMPLATES
#  define _MDSPAN_TRAIT(TRAIT, ...) TRAIT##_v<__VA_ARGS__>
#else
#  define _MDSPAN_TRAIT(TRAIT, ...) TRAIT<__VA_ARGS__>::value
#endif

// </editor-fold> end Variable template compatibility }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="Pre-C++14 constexpr"> {{{1

#if _MDSPAN_USE_CONSTEXPR_14
#  define _MDSPAN_CONSTEXPR_14 constexpr
// Workaround for a bug (I think?) in EDG frontends
#  ifdef __EDG__
#    define _MDSPAN_CONSTEXPR_14_DEFAULTED
#  else
#    define _MDSPAN_CONSTEXPR_14_DEFAULTED constexpr
#  endif
#else
#  define _MDSPAN_CONSTEXPR_14
#  define _MDSPAN_CONSTEXPR_14_DEFAULTED
#endif

// </editor-fold> end Pre-C++14 constexpr }}}1
//==============================================================================
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/macros.hpp


namespace std {
namespace experimental {

template <class ElementType>
struct default_accessor {

  using offset_policy = default_accessor;
  using element_type = ElementType;
  using reference = ElementType&;
  using data_handle_type = ElementType*;

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr default_accessor() noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, OtherElementType(*)[], element_type(*)[])
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr default_accessor(default_accessor<OtherElementType>) noexcept {}

  MDSPAN_INLINE_FUNCTION
  constexpr data_handle_type
  offset(data_handle_type p, size_t i) const noexcept {
    return p + i;
  }

  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference access(data_handle_type p, size_t i) const noexcept {
    return p[i];
  }

};

} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/default_accessor.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/full_extent_t.hpp
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



namespace std {
namespace experimental {

struct full_extent_t { explicit full_extent_t() = default; };

_MDSPAN_INLINE_VARIABLE constexpr auto full_extent = full_extent_t{ };

} // end namespace experimental
} // namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/full_extent_t.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/mdspan.hpp
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



//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_right.hpp
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


//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/trait_backports.hpp
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

#ifndef MDSPAN_INCLUDE_EXPERIMENTAL_BITS_TRAIT_BACKPORTS_HPP_
#define MDSPAN_INCLUDE_EXPERIMENTAL_BITS_TRAIT_BACKPORTS_HPP_



//==============================================================================
// <editor-fold desc="Variable template trait backports (e.g., is_void_v)"> {{{1

#ifdef _MDSPAN_NEEDS_TRAIT_VARIABLE_TEMPLATE_BACKPORTS

#if _MDSPAN_USE_VARIABLE_TEMPLATES
namespace std {

#define _MDSPAN_BACKPORT_TRAIT(TRAIT) \
  template <class... Args> _MDSPAN_INLINE_VARIABLE constexpr auto TRAIT##_v = TRAIT<Args...>::value;

_MDSPAN_BACKPORT_TRAIT(is_assignable)
_MDSPAN_BACKPORT_TRAIT(is_constructible)
_MDSPAN_BACKPORT_TRAIT(is_convertible)
_MDSPAN_BACKPORT_TRAIT(is_default_constructible)
_MDSPAN_BACKPORT_TRAIT(is_trivially_destructible)
_MDSPAN_BACKPORT_TRAIT(is_same)
_MDSPAN_BACKPORT_TRAIT(is_empty)
_MDSPAN_BACKPORT_TRAIT(is_void)

#undef _MDSPAN_BACKPORT_TRAIT

} // end namespace std

#endif // _MDSPAN_USE_VARIABLE_TEMPLATES

#endif // _MDSPAN_NEEDS_TRAIT_VARIABLE_TEMPLATE_BACKPORTS

// </editor-fold> end Variable template trait backports (e.g., is_void_v) }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="integer sequence (ugh...)"> {{{1

#if !defined(_MDSPAN_USE_INTEGER_SEQUENCE) || !_MDSPAN_USE_INTEGER_SEQUENCE

namespace std {

template <class T, T... Vals>
struct integer_sequence {
  static constexpr std::size_t size() noexcept { return sizeof...(Vals); }
  using value_type = T;
};

template <std::size_t... Vals>
using index_sequence = std::integer_sequence<std::size_t, Vals...>;

namespace __detail {

template <class T, T N, T I, class Result>
struct __make_int_seq_impl;

template <class T, T N, T... Vals>
struct __make_int_seq_impl<T, N, N, integer_sequence<T, Vals...>>
{
  using type = integer_sequence<T, Vals...>;
};

template <class T, T N, T I, T... Vals>
struct __make_int_seq_impl<
  T, N, I, integer_sequence<T, Vals...>
> : __make_int_seq_impl<T, N, I+1, integer_sequence<T, Vals..., I>>
{ };

} // end namespace __detail

template <class T, T N>
using make_integer_sequence = typename __detail::__make_int_seq_impl<T, N, 0, integer_sequence<T>>::type;

template <std::size_t N>
using make_index_sequence = typename __detail::__make_int_seq_impl<size_t, N, 0, integer_sequence<size_t>>::type;

template <class... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

} // end namespace std

#endif

// </editor-fold> end integer sequence (ugh...) }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="standard trait aliases"> {{{1

#if !defined(_MDSPAN_USE_STANDARD_TRAIT_ALIASES) || !_MDSPAN_USE_STANDARD_TRAIT_ALIASES

namespace std {

#define _MDSPAN_BACKPORT_TRAIT_ALIAS(TRAIT) \
  template <class... Args> using TRAIT##_t = typename TRAIT<Args...>::type;

_MDSPAN_BACKPORT_TRAIT_ALIAS(remove_cv)
_MDSPAN_BACKPORT_TRAIT_ALIAS(remove_reference)

template <bool _B, class _T=void>
using enable_if_t = typename enable_if<_B, _T>::type;

#undef _MDSPAN_BACKPORT_TRAIT_ALIAS

} // end namespace std

#endif

// </editor-fold> end standard trait aliases }}}1
//==============================================================================

#endif //MDSPAN_INCLUDE_EXPERIMENTAL_BITS_TRAIT_BACKPORTS_HPP_
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/trait_backports.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/extents.hpp
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


//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/static_array.hpp
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



//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/dynamic_extent.hpp
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




namespace std {
namespace experimental {

_MDSPAN_INLINE_VARIABLE constexpr auto dynamic_extent = std::numeric_limits<size_t>::max();

} // end namespace experimental
} // namespace std

//==============================================================================================================
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/dynamic_extent.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/maybe_static_value.hpp
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



#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/no_unique_address.hpp
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



namespace std {
namespace experimental {
namespace detail {

//==============================================================================

template <class _T, size_t _Disambiguator = 0, class _Enable = void>
struct __no_unique_address_emulation {
  using __stored_type = _T;
  _T __v;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T const &__ref() const noexcept {
    return __v;
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__ref() noexcept {
    return __v;
  }
};

// Empty case
// This doesn't work if _T is final, of course, but we're not using anything
// like that currently. That kind of thing could be added pretty easily though
template <class _T, size_t _Disambiguator>
struct __no_unique_address_emulation<
    _T, _Disambiguator,
    enable_if_t<_MDSPAN_TRAIT(is_empty, _T) &&
                // If the type isn't trivially destructible, its destructor
                // won't be called at the right time, so don't use this
                // specialization
                _MDSPAN_TRAIT(is_trivially_destructible, _T)>> : 
#ifdef _MDSPAN_COMPILER_MSVC
    // MSVC doesn't allow you to access public static member functions of a type
    // when you *happen* to privately inherit from that type.
    protected
#else
    // But we still want this to be private if possible so that we don't accidentally 
    // access members of _T directly rather than calling __ref() first, which wouldn't
    // work if _T happens to be stateful and thus we're using the unspecialized definition
    // of __no_unique_address_emulation above.
    private
#endif
    _T {
  using __stored_type = _T;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T const &__ref() const noexcept {
    return *static_cast<_T const *>(this);
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__ref() noexcept {
    return *static_cast<_T *>(this);
  }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __no_unique_address_emulation() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __no_unique_address_emulation(
      __no_unique_address_emulation const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __no_unique_address_emulation(
      __no_unique_address_emulation &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __no_unique_address_emulation &
  operator=(__no_unique_address_emulation const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __no_unique_address_emulation &
  operator=(__no_unique_address_emulation &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__no_unique_address_emulation() noexcept = default;

  // Explicitly make this not a reference so that the copy or move
  // constructor still gets called.
  MDSPAN_INLINE_FUNCTION
  explicit constexpr __no_unique_address_emulation(_T const& __v) noexcept : _T(__v) {}
  MDSPAN_INLINE_FUNCTION
  explicit constexpr __no_unique_address_emulation(_T&& __v) noexcept : _T(::std::move(__v)) {}
};

//==============================================================================

} // end namespace detail
} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/no_unique_address.hpp
#endif

// This is only needed for the non-standard-layout version of partially
// static array.
// Needs to be after the includes above to work with the single header generator
#if !_MDSPAN_PRESERVE_STANDARD_LAYOUT
namespace std {
namespace experimental {

//==============================================================================

namespace detail {

// static case
template <class _dynamic_t, class static_t, _static_t __v,
          _static_t __is_dynamic_sentinal = dynamic_extent,
          size_t __array_entry_index = 0>
struct __maybe_static_value {
  static constexpr _static_t __static_value = __v;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _dynamic_t __value() const noexcept {
    return static_cast<_dynamic_t>(__v);
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& /*__rhs*/) noexcept {
    // Should we assert that the value matches the static value here?
    return {};
  }

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value(__maybe_static_value const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __maybe_static_value(__maybe_static_value&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __maybe_static_value& operator=(__maybe_static_value const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __maybe_static_value& operator=(__maybe_static_value&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__maybe_static_value() noexcept = default;

  MDSPAN_INLINE_FUNCTION
  constexpr explicit __maybe_static_value(_dynamic_t const&) noexcept {
    // Should we assert that the value matches the static value here?
  }

  //--------------------------------------------------------------------------

};

// dynamic case
template <class _dynamic_t, class _static_t, _static_t __is_dynamic_sentinal, size_t __array_entry_index>
struct __maybe_static_value<_dynamic_t, _static_t, __is_dynamic_sentinal, __is_dynamic_sentinal,
                            __array_entry_index>
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __no_unique_address_emulation<_T>
#endif
{
  static constexpr _static_t __static_value = __is_dynamic_sentinal;
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS _dynamic_t __v = {};
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _dynamic_t __value() const noexcept {
    return __v;
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _dynamic_t &__ref() noexcept {
    return __v;
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
    __v = (_U &&)rhs;
    return {};
  }
#else
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _dynamic_t __value() const noexcept {
    return this->__no_unique_address_emulation<_dynamic_t>::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _dynamic_t &__ref() noexcept {
    return this->__no_unique_address_emulation<_dynamic_t>::__ref();
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
    this->__no_unique_address_emulation<_dynamic_t>::__ref() = (_U &&)__rhs;
    return {};
  }
#endif
};

} // namespace detail

//==============================================================================

} // end namespace experimental
} // end namespace std

#endif // !_MDSPAN_PRESERVE_STANDARD_LAYOUT
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/maybe_static_value.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/standard_layout_static_array.hpp
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


//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/compressed_pair.hpp
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



#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#endif

namespace std {
namespace experimental {
namespace detail {

// For no unique address emulation, this is the case taken when neither are empty.
// For real `[[no_unique_address]]`, this case is always taken.
template <class _T, class _U, class _Enable = void> struct __compressed_pair {
  _MDSPAN_NO_UNIQUE_ADDRESS _T __t_val;
  _MDSPAN_NO_UNIQUE_ADDRESS _U __u_val;
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__first() noexcept { return __t_val; }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T const &__first() const noexcept {
    return __t_val;
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _U &__second() noexcept { return __u_val; }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _U const &__second() const noexcept {
    return __u_val;
  }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__compressed_pair() noexcept = default;
  template <class _TLike, class _ULike>
  MDSPAN_INLINE_FUNCTION constexpr __compressed_pair(_TLike &&__t, _ULike &&__u)
      : __t_val((_TLike &&) __t), __u_val((_ULike &&) __u) {}
};

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)

// First empty.
template <class _T, class _U>
struct __compressed_pair<
    _T, _U,
    enable_if_t<_MDSPAN_TRAIT(is_empty, _T) && !_MDSPAN_TRAIT(is_empty, _U)>>
    : private _T {
  _U __u_val;
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__first() noexcept {
    return *static_cast<_T *>(this);
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T const &__first() const noexcept {
    return *static_cast<_T const *>(this);
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _U &__second() noexcept { return __u_val; }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _U const &__second() const noexcept {
    return __u_val;
  }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__compressed_pair() noexcept = default;
  template <class _TLike, class _ULike>
  MDSPAN_INLINE_FUNCTION constexpr __compressed_pair(_TLike &&__t, _ULike &&__u)
      : _T((_TLike &&) __t), __u_val((_ULike &&) __u) {}
};

// Second empty.
template <class _T, class _U>
struct __compressed_pair<
    _T, _U,
    enable_if_t<!_MDSPAN_TRAIT(is_empty, _T) && _MDSPAN_TRAIT(is_empty, _U)>>
    : private _U {
  _T __t_val;
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__first() noexcept { return __t_val; }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T const &__first() const noexcept {
    return __t_val;
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _U &__second() noexcept {
    return *static_cast<_U *>(this);
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _U const &__second() const noexcept {
    return *static_cast<_U const *>(this);
  }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__compressed_pair() noexcept = default;

  template <class _TLike, class _ULike>
  MDSPAN_INLINE_FUNCTION constexpr __compressed_pair(_TLike &&__t, _ULike &&__u)
      : _U((_ULike &&) __u), __t_val((_TLike &&) __t) {}
};

// Both empty.
template <class _T, class _U>
struct __compressed_pair<
    _T, _U,
    enable_if_t<_MDSPAN_TRAIT(is_empty, _T) && _MDSPAN_TRAIT(is_empty, _U)>>
    // We need to use the __no_unique_address_emulation wrapper here to avoid
    // base class ambiguities.
#ifdef _MDSPAN_COMPILER_MSVC
// MSVC doesn't allow you to access public static member functions of a type
// when you *happen* to privately inherit from that type.
    : protected __no_unique_address_emulation<_T, 0>,
      protected __no_unique_address_emulation<_U, 1>
#else
    : private __no_unique_address_emulation<_T, 0>,
      private __no_unique_address_emulation<_U, 1>
#endif
{
  using __first_base_t = __no_unique_address_emulation<_T, 0>;
  using __second_base_t = __no_unique_address_emulation<_U, 1>;

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__first() noexcept {
    return this->__first_base_t::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T const &__first() const noexcept {
    return this->__first_base_t::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _U &__second() noexcept {
    return this->__second_base_t::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _U const &__second() const noexcept {
    return this->__second_base_t::__ref();
  }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __compressed_pair(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __compressed_pair &
  operator=(__compressed_pair &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__compressed_pair() noexcept = default;
  template <class _TLike, class _ULike>
  MDSPAN_INLINE_FUNCTION constexpr __compressed_pair(_TLike &&__t, _ULike &&__u) noexcept
    : __first_base_t(_T((_TLike &&) __t)),
      __second_base_t(_U((_ULike &&) __u))
  { }
};

#endif // !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)

} // end namespace detail
} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/compressed_pair.hpp

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#endif

#ifdef __cpp_lib_span
#endif

namespace std {
namespace experimental {
namespace detail {

//==============================================================================

_MDSPAN_INLINE_VARIABLE constexpr struct
    __construct_psa_from_dynamic_exts_values_tag_t {
} __construct_psa_from_dynamic_exts_values_tag = {};

_MDSPAN_INLINE_VARIABLE constexpr struct
    __construct_psa_from_all_exts_values_tag_t {
} __construct_psa_from_all_exts_values_tag = {};

struct __construct_psa_from_all_exts_array_tag_t {};
template <size_t _N = 0> struct __construct_psa_from_dynamic_exts_array_tag_t {};

//==============================================================================

template <size_t _I, class _T> using __repeated_with_idxs = _T;

//==============================================================================

#if _MDSPAN_PRESERVE_STANDARD_LAYOUT

/**
 *  PSA = "partially static array"
 *
 * @tparam _T
 * @tparam _ValsSeq
 * @tparam __sentinal
 */
template <class _Tag, class _T, class _static_t, class _ValsSeq, _static_t __sentinal = static_cast<_static_t>(dynamic_extent),
          class _IdxsSeq = make_index_sequence<_ValsSeq::size()>>
struct __standard_layout_psa;

//==============================================================================
// Static case
template <class _Tag, class _T, class _static_t, _static_t __value, _static_t... __values_or_sentinals,
          _static_t __sentinal, size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _Tag, _T, _static_t, integer_sequence<_static_t, __value, __values_or_sentinals...>,
    __sentinal, integer_sequence<size_t, _Idx, _Idxs...>>
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : private __no_unique_address_emulation<__standard_layout_psa<
          _Tag, _T, _static_t, integer_sequence<_static_t, __values_or_sentinals...>, __sentinal,
          integer_sequence<size_t, _Idxs...>>>
#endif
{

  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_Tag, _T, _static_t,
                            integer_sequence<_static_t, __values_or_sentinals...>,
                            __sentinal, integer_sequence<size_t, _Idxs...>>;

#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS __next_t __next_;
#else
  using __base_t = __no_unique_address_emulation<__next_t>;
#endif

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 __next_t &__next() noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __next_;
#else
    return this->__base_t::__ref();
#endif
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __next_t const &__next() const noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __next_;
#else
    return this->__base_t::__ref();
#endif
  }

  static constexpr auto __size = sizeof...(_Idxs) + 1;
  static constexpr auto __size_dynamic = __next_t::__size_dynamic;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa const &) noexcept =
      default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__standard_layout_psa() noexcept = default;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION
  constexpr __standard_layout_psa(
      __construct_psa_from_all_exts_values_tag_t, _T const & /*__val*/,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __construct_psa_from_all_exts_values_tag, __vals...
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_psa_from_dynamic_exts_values_tag_t,
      _Ts const &... __vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __construct_psa_from_dynamic_exts_values_tag, __vals...
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_U, _N> const &__vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __vals
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  template <class _U, size_t _NStatic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_all_exts_array_tag_t const & __tag,
      array<_U, _NStatic> const &__vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __tag, __vals
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_exts_array_tag_t<_IDynamic> __tag,
      array<_U, _NDynamic> const &__vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __tag, __vals
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

#ifdef __cpp_lib_span
  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      span<_U, _N> const &__vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __vals
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  template <class _U, size_t _NStatic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_all_exts_array_tag_t const & __tag,
      span<_U, _NStatic> const &__vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __tag, __vals
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_exts_array_tag_t<_IDynamic> __tag,
      span<_U, _NDynamic> const &__vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __tag, __vals
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }
#endif

  template <class _UTag, class _U, class _static_U, class _UValsSeq, _static_U __u_sentinal,
            class _IdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _static_U, _UValsSeq, __u_sentinal, _IdxsSeq> const
          &__rhs) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __rhs.__next()
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  //--------------------------------------------------------------------------

  // See https://godbolt.org/z/_KSDNX for a summary-by-example of why this is
  // necessary. We're using inheritance here instead of an alias template
  // because we have to deduce __values_or_sentinals in several places, and
  // alias templates don't permit that in this context.
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __standard_layout_psa const &__enable_psa_conversion() const
      noexcept {
    return *this;
  }

  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __next().template __get_n<_I>();
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __value;
  }
  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    __next().__set_value(__rhs);
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &) noexcept {
    // Don't assert here because that would break constexpr. This better
    // not change anything, though
  }
  template <size_t _I, enable_if_t<_I == _Idx, _static_t> = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _static_t __get_static_n() noexcept {
    return __value;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _static_t> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _static_t __get_static_n() noexcept {
    return __next_t::template __get_static_n<_I, __default>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value * (_T(_Idx == __n)) + __next().__get(__n);
  }

  //--------------------------------------------------------------------------
};

//==============================================================================

// Dynamic case, __next_t may or may not be empty
template <class _Tag, class _T, class _static_t, _static_t __sentinal, _static_t... __values_or_sentinals,
          size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _Tag, _T, _static_t, integer_sequence<_static_t, __sentinal, __values_or_sentinals...>,
    __sentinal, integer_sequence<size_t, _Idx, _Idxs...>> {
  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_Tag, _T, _static_t,
                            integer_sequence<_static_t, __values_or_sentinals...>,
                            __sentinal, integer_sequence<size_t, _Idxs...>>;

  using __value_pair_t = __compressed_pair<_T, __next_t>;
  __value_pair_t __value_pair;
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 __next_t &__next() noexcept {
    return __value_pair.__second();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __next_t const &__next() const noexcept {
    return __value_pair.__second();
  }

  static constexpr auto __size = sizeof...(_Idxs) + 1;
  static constexpr auto __size_dynamic = 1 + __next_t::__size_dynamic;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa const &) noexcept =
      default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__standard_layout_psa() noexcept = default;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION
  constexpr __standard_layout_psa(
      __construct_psa_from_all_exts_values_tag_t, _T const &__val,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
      : __value_pair(__val,
                     __next_t(__construct_psa_from_all_exts_values_tag,
                              __vals...)) {}

  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_psa_from_dynamic_exts_values_tag_t, _T const &__val,
      _Ts const &... __vals) noexcept
      : __value_pair(__val,
                     __next_t(__construct_psa_from_dynamic_exts_values_tag,
                              __vals...)) {}

  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_U, _N> const &__vals) noexcept
      : __value_pair(::std::get<_Idx>(__vals), __vals) {}

  template <class _U, size_t _NStatic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_all_exts_array_tag_t __tag,
      array<_U, _NStatic> const &__vals) noexcept
      : __value_pair(
            ::std::get<_Idx>(__vals),
            __next_t(__tag,
                     __vals)) {}

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_exts_array_tag_t<_IDynamic>,
      array<_U, _NDynamic> const &__vals) noexcept
      : __value_pair(
            ::std::get<_IDynamic>(__vals),
            __next_t(__construct_psa_from_dynamic_exts_array_tag_t<_IDynamic + 1>{},
                     __vals)) {}

#ifdef __cpp_lib_span
  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      span<_U, _N> const &__vals) noexcept
      : __value_pair(__vals[_Idx], __vals) {}

  template <class _U, size_t _NStatic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_all_exts_array_tag_t __tag,
      span<_U, _NStatic> const &__vals) noexcept
      : __value_pair(
            __vals[_Idx],
            __next_t(__tag,
                     __vals)) {}

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_exts_array_tag_t<_IDynamic>,
      span<_U, _NDynamic> const &__vals) noexcept
      : __value_pair(
            __vals[_IDynamic],
            __next_t(__construct_psa_from_dynamic_exts_array_tag_t<_IDynamic + 1>{},
                     __vals)) {}
#endif

  template <class _UTag, class _U, class _static_U, class _UValsSeq, _static_U __u_sentinal,
            class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _static_U, _UValsSeq, __u_sentinal, _UIdxsSeq> const
          &__rhs) noexcept
      : __value_pair(__rhs.template __get_n<_Idx>(), __rhs.__next()) {}

  //--------------------------------------------------------------------------

  // See comment in the previous partial specialization for why this is
  // necessary.  Or just trust me that it's messy.
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __standard_layout_psa const &__enable_psa_conversion() const
      noexcept {
    return *this;
  }

  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __next().template __get_n<_I>();
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return __value_pair.__first();
  }
  template <size_t _I, enable_if_t<_I != _Idx, int> = 0>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    __next().__set_value(__rhs);
  }
  template <size_t _I, enable_if_t<_I == _Idx, int> = 1>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void
  __set_n(_T const &__rhs) noexcept {
    __value_pair.__first() = __rhs;
  }
  template <size_t _I, enable_if_t<_I == _Idx, _static_t> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _static_t __get_static_n() noexcept {
    return __default;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _static_t> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _static_t __get_static_n() noexcept {
    return __next_t::template __get_static_n<_I, __default>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value_pair.__first() * (_T(_Idx == __n)) + __next().__get(__n);
  }

  //--------------------------------------------------------------------------
};

// empty/terminal case
template <class _Tag, class _T, class _static_t, _static_t __sentinal>
struct __standard_layout_psa<_Tag, _T, _static_t, integer_sequence<_static_t>, __sentinal,
                             integer_sequence<size_t>> {
  //--------------------------------------------------------------------------

  static constexpr auto __size = 0;
  static constexpr auto __size_dynamic = 0;

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa() noexcept
#if defined(__clang__) || defined(_MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND)
  // As far as I can tell, there appears to be a bug in clang that's causing
  // this to be non-constexpr when it's defaulted.
  { }
#else
   = default;
#endif
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa const &) noexcept =
      default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __standard_layout_psa(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __standard_layout_psa &
  operator=(__standard_layout_psa &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__standard_layout_psa() noexcept = default;

  MDSPAN_INLINE_FUNCTION
  constexpr __standard_layout_psa(
      __construct_psa_from_all_exts_values_tag_t) noexcept {}

  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_psa_from_dynamic_exts_values_tag_t) noexcept {}

  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_U, _N> const &) noexcept {}

  template <class _U, size_t _NStatic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_all_exts_array_tag_t,
      array<_U, _NStatic> const &) noexcept {}

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_exts_array_tag_t<_IDynamic>,
      array<_U, _NDynamic> const &) noexcept {}

#ifdef __cpp_lib_span
  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      span<_U, _N> const &) noexcept {}

  template <class _U, size_t _NStatic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_all_exts_array_tag_t,
      span<_U, _NStatic> const &) noexcept {}

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_exts_array_tag_t<_IDynamic>,
      span<_U, _NDynamic> const &) noexcept {}
#endif

  template <class _UTag, class _U, class _static_U, class _UValsSeq, _static_U __u_sentinal,
            class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _static_U, _UValsSeq, __u_sentinal, _UIdxsSeq> const&) noexcept {}

  // See comment in the previous partial specialization for why this is
  // necessary.  Or just trust me that it's messy.
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __standard_layout_psa const &__enable_psa_conversion() const
      noexcept {
    return *this;
  }

  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t /*n*/) const noexcept {
    return 0;
  }
};

// Same thing, but with a disambiguator so that same-base issues doesn't cause
// a loss of standard-layout-ness.
template <class _Tag, class T, class _static_t, _static_t... __values_or_sentinals>
struct __partially_static_sizes_tagged
    : __standard_layout_psa<
          _Tag, T, _static_t,
          integer_sequence<_static_t, __values_or_sentinals...>> {
  using __tag_t = _Tag;
  using __psa_impl_t = __standard_layout_psa<
      _Tag, T, _static_t, integer_sequence<_static_t, __values_or_sentinals...>>;
  using __psa_impl_t::__psa_impl_t;
#ifdef _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND
  MDSPAN_INLINE_FUNCTION
#endif
  constexpr __partially_static_sizes_tagged() noexcept
#ifdef _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND
    : __psa_impl_t() { }
#else
    = default;
#endif
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __partially_static_sizes_tagged(
      __partially_static_sizes_tagged const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __partially_static_sizes_tagged(
      __partially_static_sizes_tagged &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __partially_static_sizes_tagged &
  operator=(__partially_static_sizes_tagged const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __partially_static_sizes_tagged &
  operator=(__partially_static_sizes_tagged &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__partially_static_sizes_tagged() noexcept = default;

  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr explicit __partially_static_sizes_tagged(
    __partially_static_sizes_tagged<_UTag, T, _static_t, __values_or_sentinals...> const& __vals
  ) noexcept : __psa_impl_t(__vals.__enable_psa_conversion()) { }
};

struct __no_tag {};
template <class T, class _static_t, _static_t... __values_or_sentinals>
struct __partially_static_sizes
    : __partially_static_sizes_tagged<__no_tag, T, _static_t, __values_or_sentinals...> {
private:
  using __base_t =
      __partially_static_sizes_tagged<__no_tag, T, _static_t, __values_or_sentinals...>;
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes(
    __partially_static_sizes_tagged<_UTag, T, _static_t, __values_or_sentinals...>&& __vals
  ) noexcept : __base_t(::std::move(__vals)) { }
public:
  using __base_t::__base_t;

#ifdef _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND
  MDSPAN_INLINE_FUNCTION
  constexpr __partially_static_sizes() noexcept : __base_t() { }
#endif
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes_tagged<
      _UTag, T, _static_t, __values_or_sentinals...>
  __with_tag() const noexcept {
    return __partially_static_sizes_tagged<_UTag, T, _static_t, __values_or_sentinals...>(*this);
  }
};

#endif // _MDSPAN_PRESERVE_STATIC_LAYOUT

} // end namespace detail
} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/standard_layout_static_array.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/type_list.hpp
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



namespace std {
namespace experimental {

//==============================================================================

namespace detail {

template <class... _Ts> struct __type_list { static constexpr auto __size = sizeof...(_Ts); };

// Implementation of type_list at() that's heavily optimized for small typelists
template <size_t, class> struct __type_at;
template <size_t, class _Seq, class=make_index_sequence<_Seq::__size>> struct __type_at_large_impl;

template <size_t _I, size_t _Idx, class _T>
struct __type_at_entry { };

template <class _Result>
struct __type_at_assign_op_ignore_rest {
  template <class _T>
  __type_at_assign_op_ignore_rest<_Result> operator=(_T&&);
  using type = _Result;
};

struct __type_at_assign_op_impl {
  template <size_t _I, size_t _Idx, class _T>
  __type_at_assign_op_impl operator=(__type_at_entry<_I, _Idx, _T>&&);
  template <size_t _I, class _T>
  __type_at_assign_op_ignore_rest<_T> operator=(__type_at_entry<_I, _I, _T>&&);
};

template <size_t _I, class... _Ts, size_t... _Idxs>
struct __type_at_large_impl<_I, __type_list<_Ts...>, integer_sequence<size_t, _Idxs...>>
  : decltype(
      _MDSPAN_FOLD_ASSIGN_LEFT(__type_at_assign_op_impl{}, /* = ... = */ __type_at_entry<_I, _Idxs, _Ts>{})
    )
{ };

template <size_t _I, class... _Ts>
struct __type_at<_I, __type_list<_Ts...>>
    : __type_at_large_impl<_I, __type_list<_Ts...>>
{ };

template <class _T0, class... _Ts>
struct __type_at<0, __type_list<_T0, _Ts...>> {
  using type = _T0;
};

template <class _T0, class _T1, class... _Ts>
struct __type_at<1, __type_list<_T0, _T1, _Ts...>> {
  using type = _T1;
};

template <class _T0, class _T1, class _T2, class... _Ts>
struct __type_at<2, __type_list<_T0, _T1, _T2, _Ts...>> {
  using type = _T2;
};

template <class _T0, class _T1, class _T2, class _T3, class... _Ts>
struct __type_at<3, __type_list<_T0, _T1, _T2, _T3, _Ts...>> {
  using type = _T3;
};


} // namespace detail

//==============================================================================

} // end namespace experimental
} // end namespace std

//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/type_list.hpp

// Needs to be after the includes above to work with the single header generator
#if !_MDSPAN_PRESERVE_STANDARD_LAYOUT

namespace std {
namespace experimental {
namespace detail {

//==============================================================================

template <class _T, _T _Val, bool _Mask> struct __mask_element {};

template <class _T, _T... _Result>
struct __mask_sequence_assign_op {
  template <_T _V>
  __mask_sequence_assign_op<_T, _Result..., _V>
  operator=(__mask_element<_T, _V, true>&&);
  template <_T _V>
  __mask_sequence_assign_op<_T, _Result...>
  operator=(__mask_element<_T, _V, false>&&);
  using __result = integer_sequence<_T, _Result...>;
};

template <class _Seq, class _Mask>
struct __mask_sequence;

template <class _T, _T... _Vals, bool... _Masks>
struct __mask_sequence<integer_sequence<_T, _Vals...>, integer_sequence<bool, _Masks...>>
{
  using type = typename decltype(
    _MDSPAN_FOLD_ASSIGN_LEFT(
      __mask_sequence_assign_op<_T>{}, /* = ... = */ __mask_element<_T, _Vals, _Masks>{}
    )
  )::__result;
};

//==============================================================================

template <class _T, class _static_t, class _Vals, _static_t __sentinal,
          class _Idxs, class _IdxsDynamic, class _IdxsDynamicIdxs>
class __partially_static_array_impl;

template <
  class _T, class _static_t,
  _static_t... __values_or_sentinals, _static_t __sentinal,
  size_t... _Idxs,
  size_t... _IdxsDynamic,
  size_t... _IdxsDynamicIdxs
>
class __partially_static_array_impl<
  _T,
  _static_t,
  integer_sequence<_static_t, __values_or_sentinals...>,
  __sentinal,
  integer_sequence<size_t, _Idxs...>,
  integer_sequence<size_t, _IdxsDynamic...>,
  integer_sequence<size_t, _IdxsDynamicIdxs...>
>
    : private __maybe_static_value<_T, _static_t, __values_or_sentinals, __sentinal,
                                   _Idxs>... {
private:

  template <size_t _N>
  using __base_n = typename __type_at<_N,
    __type_list<__maybe_static_value<_T, _static_t, __values_or_sentinals, __sentinal, _Idxs>...>
  >::type;

public:

  static constexpr auto __size = sizeof...(_Idxs);
  static constexpr auto __size_dynamic =
    _MDSPAN_FOLD_PLUS_RIGHT(static_cast<int>((__values_or_sentinals == __sentinal)), /* + ... + */ 0);

  //--------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __partially_static_array_impl() = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __partially_static_array_impl(
      __partially_static_array_impl const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr __partially_static_array_impl(
      __partially_static_array_impl &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __partially_static_array_impl &
  operator=(__partially_static_array_impl const &) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  _MDSPAN_CONSTEXPR_14_DEFAULTED __partially_static_array_impl &
  operator=(__partially_static_array_impl &&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~__partially_static_array_impl() noexcept = default;

  MDSPAN_INLINE_FUNCTION
  constexpr __partially_static_array_impl(
      __construct_psa_from_all_exts_values_tag_t,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
      : __base_n<_Idxs>(__base_n<_Idxs>{{__vals}})... {}

  MDSPAN_INLINE_FUNCTION
  constexpr __partially_static_array_impl(
      __construct_psa_from_dynamic_exts_values_tag_t,
      __repeated_with_idxs<_IdxsDynamicIdxs, _T> const &... __vals) noexcept
      : __base_n<_IdxsDynamic>(__base_n<_IdxsDynamic>{{__vals}})... {}

  MDSPAN_INLINE_FUNCTION constexpr explicit __partially_static_array_impl(
    array<_T, sizeof...(_Idxs)> const& __vals) noexcept
    : __partially_static_array_impl(
        __construct_psa_from_all_exts_values_tag,
        ::std::get<_Idxs>(__vals)...) {}

  // clang-format off
  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr explicit),
    __partially_static_array_impl,
    (array<_T, __size_dynamic> const &__vals), noexcept,
    /* requires */
      (sizeof...(_Idxs) != __size_dynamic)
  ): __partially_static_array_impl(
       __construct_psa_from_dynamic_exts_values_tag,
       ::std::get<_IdxsDynamicIdxs>(__vals)...) {}
  // clang-format on

  template <class _U, class _static_u, class _UValsSeq, _static_u __u_sentinal, class _UIdxsSeq,
            class _UIdxsDynamicSeq, class _UIdxsDynamicIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __partially_static_array_impl(
    __partially_static_array_impl<
      _U, _static_u, _UValsSeq, __u_sentinal, _UIdxsSeq,
     _UIdxsDynamicSeq, _UIdxsDynamicIdxsSeq> const &__rhs) noexcept
    : __partially_static_array_impl(
        __construct_psa_from_all_exts_values_tag,
        __rhs.template __get_n<_Idxs>()...) {}

  //--------------------------------------------------------------------------

  // See comment in the previous partial specialization for why this is
  // necessary.  Or just trust me that it's messy.
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __partially_static_array_impl const &__enable_psa_conversion() const
  noexcept {
      return *this;
  }

  template <size_t _I>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get_n() const noexcept {
    return static_cast<__base_n<_I> const*>(this)->__value();
  }

  template <class _U, size_t _I>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 void __set_n(_U&& __rhs) noexcept {
    static_cast<__base_n<_I>*>(this)->__set_value((_U&&)__rhs);
  }

  template <size_t _I, _static_t __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _static_t
  __get_static_n() noexcept {
    return __base_n<_I>::__static_value == __sentinal ?
      __default : __base_n<_I>::__static_value;
  }

  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T
  __get(size_t __n) const noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT(
      (_T(_Idxs == __n) * __get_n<_Idxs>()), /* + ... + */ _T(0)
    );
  }

};

//==============================================================================

template <class _T, class _static_t, class _ValSeq, _static_t __sentinal, class _Idxs = make_index_sequence<_ValSeq::size()>>
struct __partially_static_array_impl_maker;

template <
  class _T, class _static_t,  _static_t... _Vals, _static_t __sentinal, size_t... _Idxs
>
struct __partially_static_array_impl_maker<
  _T, _static_t, integer_sequence<_static_t, _Vals...>, __sentinal, integer_sequence<size_t, _Idxs...>
>
{
  using __dynamic_idxs = typename __mask_sequence<
    integer_sequence<size_t, _Idxs...>,
    integer_sequence<bool, (_Vals == __sentinal)...>
  >::type;
  using __impl_base =
    __partially_static_array_impl<_T, _static_t,
      integer_sequence<_static_t, _Vals...>,
      __sentinal, integer_sequence<size_t, _Idxs...>,
      __dynamic_idxs,
      make_index_sequence<__dynamic_idxs::size()>
    >;
};

template <class _T, class _static_t, class _ValsSeq, _static_t __sentinal = dynamic_extent>
class __partially_static_array_with_sentinal
  : public __partially_static_array_impl_maker<_T, _static_t, _ValsSeq, __sentinal>::__impl_base
{
private:
  using __base_t = typename __partially_static_array_impl_maker<_T, _static_t, _ValsSeq, __sentinal>::__impl_base;
public:
  using __base_t::__base_t;
};

//==============================================================================

template <class T, class _static_t, _static_t... __values_or_sentinals>
struct __partially_static_sizes :
  __partially_static_array_with_sentinal<
    T, _static_t, ::std::integer_sequence<_static_t, __values_or_sentinals...>>
{
private:
  using __base_t = __partially_static_array_with_sentinal<
    T, _static_t, ::std::integer_sequence<_static_t, __values_or_sentinals...>>;
public:
  using __base_t::__base_t;
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes<T, _static_t, __values_or_sentinals...>
  __with_tag() const noexcept {
    return *this;
  }
};

// Tags are needed for the standard layout version, but not here
template <class T, class _static_t, _static_t... __values_or_sentinals>
using __partially_static_sizes_tagged = __partially_static_sizes<T, _static_t, __values_or_sentinals...>;

} // end namespace detail
} // end namespace experimental
} // end namespace std

#endif // !_MDSPAN_PRESERVE_STANDARD_LAYOUT
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/static_array.hpp

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#endif


namespace std {
namespace experimental {

namespace detail {

template<size_t ... Extents>
struct _count_dynamic_extents;

template<size_t E, size_t ... Extents>
struct _count_dynamic_extents<E,Extents...> {
  static constexpr size_t val = (E==dynamic_extent?1:0) + _count_dynamic_extents<Extents...>::val;
};

template<>
struct _count_dynamic_extents<> {
  static constexpr size_t val = 0;
};

template <size_t... Extents, size_t... OtherExtents>
static constexpr std::false_type _check_compatible_extents(
  std::false_type, std::integer_sequence<size_t, Extents...>, std::integer_sequence<size_t, OtherExtents...>
) noexcept { return { }; }

template <size_t... Extents, size_t... OtherExtents>
static std::integral_constant<
  bool,
  _MDSPAN_FOLD_AND(
    (
      Extents == dynamic_extent
        || OtherExtents == dynamic_extent
        || Extents == OtherExtents
    ) /* && ... */
  )
>
_check_compatible_extents(
  std::true_type, std::integer_sequence<size_t, Extents...>, std::integer_sequence<size_t, OtherExtents...>
) noexcept { return { }; }

struct __extents_tag { };

} // end namespace detail

template <class ThisIndexType, size_t... Extents>
class extents
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  : private detail::__no_unique_address_emulation<
      detail::__partially_static_sizes_tagged<detail::__extents_tag, ThisIndexType , size_t, Extents...>>
#endif
{
public:

  using rank_type = size_t;
  using index_type = ThisIndexType;
  static_assert(std::is_integral<index_type>::value && !std::is_same<index_type, bool>::value,
                "std::extents requires a signed or unsigned integer as index_type parameter");
  using size_type = make_unsigned_t<index_type>;

// internal typedefs which for technical reasons are public
  using __storage_t = detail::__partially_static_sizes_tagged<detail::__extents_tag, index_type, size_t, Extents...>;

#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS __storage_t __storage_;
#else
  using __base_t = detail::__no_unique_address_emulation<__storage_t>;
#endif

// private members dealing with the way we internally store dynamic extents
 private:

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __storage_t& __storage() noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __storage_;
#else
    return this->__base_t::__ref();
#endif
  }
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr __storage_t const& __storage() const noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __storage_;
#else
    return this->__base_t::__ref();
#endif
  }

  template <size_t... Idxs>
  MDSPAN_FORCE_INLINE_FUNCTION
  static constexpr
  std::size_t _static_extent_impl(size_t n, std::integer_sequence<size_t, Idxs...>) noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT(((Idxs == n) ? Extents : 0), /* + ... + */ 0);
  }

  template <class, size_t...>
  friend class extents;

  template <class OtherIndexType, size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(std::experimental::extents<OtherIndexType, OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return false; }
  template <class OtherIndexType, size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(
    std::experimental::extents<OtherIndexType, OtherExtents...> other,
    true_type, index_sequence<Idxs...>
  ) const noexcept {
    return _MDSPAN_FOLD_AND(
      (__storage().template __get_n<Idxs>() == other.__storage().template __get_n<Idxs>()) /* && ... */
    );
  }

  template <class OtherIndexType, size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(std::experimental::extents<OtherIndexType, OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return true; }
  template <class OtherIndexType, size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(
    std::experimental::extents<OtherIndexType, OtherExtents...> other,
    true_type, index_sequence<Idxs...>
  ) const noexcept {
    return _MDSPAN_FOLD_OR(
      (__storage().template __get_n<Idxs>() != other.__storage().template __get_n<Idxs>()) /* || ... */
    );
  }

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  MDSPAN_INLINE_FUNCTION constexpr explicit
  extents(__base_t&& __b) noexcept
    : __base_t(::std::move(__b))
  { }
#endif


// public interface:
public:
  /* Defined above for use in the private code
  using rank_type = size_t;
  using index_type = ThisIndexType;
  */

  MDSPAN_INLINE_FUNCTION
  static constexpr rank_type rank() noexcept { return sizeof...(Extents); }
  MDSPAN_INLINE_FUNCTION
  static constexpr rank_type rank_dynamic() noexcept { return _MDSPAN_FOLD_PLUS_RIGHT((rank_type(Extents == dynamic_extent)), /* + ... + */ 0); }

  //--------------------------------------------------------------------------------
  // Constructors, Destructors, and Assignment

  // Default constructor
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents() noexcept = default;

  // Converting constructor
  MDSPAN_TEMPLATE_REQUIRES(
    class OtherIndexType, size_t... OtherExtents,
    /* requires */ (
      /* multi-stage check to protect from invalid pack expansion when sizes don't match? */
      decltype(detail::_check_compatible_extents(
        std::integral_constant<bool, sizeof...(Extents) == sizeof...(OtherExtents)>{},
        std::integer_sequence<size_t, Extents...>{},
        std::integer_sequence<size_t, OtherExtents...>{}
      ))::value
    )
  )
  MDSPAN_INLINE_FUNCTION
  MDSPAN_CONDITIONAL_EXPLICIT(
    (((Extents != dynamic_extent) && (OtherExtents == dynamic_extent)) || ...) ||
    (std::numeric_limits<index_type>::max() < std::numeric_limits<OtherIndexType>::max()))
  constexpr extents(const extents<OtherIndexType, OtherExtents...>& __other)
    noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __storage_{
#else
    : __base_t(__base_t{__storage_t{
#endif
        __other.__storage().__enable_psa_conversion()
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      }})
#endif
  {
    /* TODO: precondition check
     * other.extent(r) equals Er for each r for which Er is a static extent, and
     * either
     *   - sizeof...(OtherExtents) is zero, or
     *   - other.extent(r) is a representable value of type index_type for all rank index r of other
     */
  }

#ifdef __NVCC__
    MDSPAN_TEMPLATE_REQUIRES(
    class... Integral,
    /* requires */ (
      // TODO: check whether the other version works with newest NVCC, doesn't with 11.4
      // NVCC seems to pick up rank_dynamic from the wrong extents type???
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, Integral, index_type) /* && ... */) &&
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_nothrow_constructible, index_type, Integral) /* && ... */) &&
      // NVCC chokes on the fold thingy here so wrote the workaround
      ((sizeof...(Integral) == detail::_count_dynamic_extents<Extents...>::val) ||
       (sizeof...(Integral) == sizeof...(Extents)))
      )
    )
#else
    MDSPAN_TEMPLATE_REQUIRES(
    class... Integral,
    /* requires */ (
       _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, Integral, index_type) /* && ... */) &&
       _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_nothrow_constructible, index_type, Integral) /* && ... */) &&
       ((sizeof...(Integral) == rank_dynamic()) || (sizeof...(Integral) == rank()))
      )
    )
#endif
  MDSPAN_INLINE_FUNCTION
  explicit constexpr extents(Integral... exts) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __storage_{
#else
    : __base_t(__base_t{typename __base_t::__stored_type{
#endif
      std::conditional_t<sizeof...(Integral)==rank_dynamic(),
        detail::__construct_psa_from_dynamic_exts_values_tag_t,
        detail::__construct_psa_from_all_exts_values_tag_t>(),
        static_cast<index_type>(exts)...
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      }})
#endif
  {
    /* TODO: precondition check
     * If sizeof...(IndexTypes) != rank_dynamic() is true, exts_arr[r] equals Er for each r for which Er is a static extent, and
     * either
     *   - sizeof...(exts) == 0 is true, or
     *   - each element of exts is nonnegative and is a representable value of type index_type.
     */
  }

    // TODO: check whether this works with newest NVCC, doesn't with 11.4
#ifdef __NVCC__
  // NVCC seems to pick up rank_dynamic from the wrong extents type???
  // NVCC chokes on the fold thingy here so wrote the workaround
  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, IndexType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, IndexType) &&
      ((N == detail::_count_dynamic_extents<Extents...>::val) ||
       (N == sizeof...(Extents)))
    )
  )
#else
    MDSPAN_TEMPLATE_REQUIRES(
        class IndexType, size_t N,
        /* requires */ (
          _MDSPAN_TRAIT(is_convertible, IndexType, index_type) &&
          _MDSPAN_TRAIT(is_nothrow_constructible, index_type, IndexType) &&
          (N == rank() || N == rank_dynamic())
    )
  )
#endif
  MDSPAN_CONDITIONAL_EXPLICIT(N != rank_dynamic())
  MDSPAN_INLINE_FUNCTION
  constexpr
  extents(std::array<IndexType, N> const& exts) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __storage_{
#else
    : __base_t(__base_t{typename __base_t::__stored_type{
#endif
      std::conditional_t<N==rank_dynamic(),
        detail::__construct_psa_from_dynamic_exts_array_tag_t<0>,
        detail::__construct_psa_from_all_exts_array_tag_t>(),
      std::array<IndexType,N>{exts}
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      }})
#endif
  {
    /* TODO: precondition check
     * If N != rank_dynamic() is true, exts[r] equals Er for each r for which Er is a static extent, and
     * either
     *   - N is zero, or
     *   - exts[r] is nonnegative and is a representable value of type index_type for all rank index r
     */
  }

#ifdef __cpp_lib_span
  // TODO: check whether the below works with newest NVCC, doesn't with 11.4
#ifdef __NVCC__
  // NVCC seems to pick up rank_dynamic from the wrong extents type???
  // NVCC chokes on the fold thingy here so wrote the workaround
  MDSPAN_TEMPLATE_REQUIRES(
    class IndexType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, IndexType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, IndexType) &&
      ((N == detail::_count_dynamic_extents<Extents...>::val) ||
       (N == sizeof...(Extents)))
    )
  )
#else
    MDSPAN_TEMPLATE_REQUIRES(
        class IndexType, size_t N,
        /* requires */ (
          _MDSPAN_TRAIT(is_convertible, IndexType, index_type) &&
          _MDSPAN_TRAIT(is_nothrow_constructible, index_type, IndexType) &&
          (N == rank() || N == rank_dynamic())
    )
  )
#endif
  MDSPAN_CONDITIONAL_EXPLICIT(N != rank_dynamic())
  MDSPAN_INLINE_FUNCTION
  constexpr
  extents(std::span<IndexType, N> exts) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __storage_{
#else
    : __base_t(__base_t{typename __base_t::__stored_type{
#endif
      std::conditional_t<N==rank_dynamic(),
        detail::__construct_psa_from_dynamic_exts_array_tag_t<0>,
        detail::__construct_psa_from_all_exts_array_tag_t>(),
      exts
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      }})
#endif
  {
    /* TODO: precondition check
     * If N != rank_dynamic() is true, exts[r] equals Er for each r for which Er is a static extent, and
     * either
     *   - N is zero, or
     *   - exts[r] is nonnegative and is a representable value of type index_type for all rank index r
     */
  }
#endif

  // Need this constructor for some submdspan implementation stuff
  // for the layout_stride case where I use an extents object for strides
  MDSPAN_INLINE_FUNCTION
  constexpr explicit
  extents(__storage_t const& sto ) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __storage_{
#else
    : __base_t(__base_t{
#endif
        sto
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      })
#endif
  { }

  //--------------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION
  static constexpr
  size_t static_extent(size_t n) noexcept {
    // Can't do assert here since that breaks true constexpr ness
    // assert(n<rank());
    return _static_extent_impl(n, std::make_integer_sequence<size_t, sizeof...(Extents)>{});
  }

  MDSPAN_INLINE_FUNCTION
  constexpr
  index_type extent(size_t n) const noexcept {
    // Can't do assert here since that breaks true constexpr ness
    // assert(n<rank());
    return __storage().__get(n);
  }

  //--------------------------------------------------------------------------------

  template<class OtherIndexType, size_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator==(extents const& lhs, extents<OtherIndexType, RHS...> const& rhs) noexcept {
    return lhs._eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(RHS) == rank())>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }

#if !(MDSPAN_HAS_CXX_20)
  template<class OtherIndexType, size_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator!=(extents const& lhs, extents<OtherIndexType, RHS...> const& rhs) noexcept {
    return lhs._not_eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(RHS) == rank())>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }
#endif

  // End of public interface

public:  // (but not really)

  MDSPAN_INLINE_FUNCTION static constexpr
  extents __make_extents_impl(detail::__partially_static_sizes<index_type, size_t,Extents...>&& __bs) noexcept {
    // This effectively amounts to a sideways cast that can be done in a constexpr
    // context, but we have to do it to handle the case where the extents and the
    // strides could accidentally end up with the same types in their hierarchies
    // somehow (which would cause layout_stride::mapping to not be standard_layout)
    return extents(
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      __base_t{
#endif
        ::std::move(__bs.template __with_tag<detail::__extents_tag>())
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#endif
    );
  }

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr
  index_type __extent() const noexcept {
    return __storage().template __get_n<N>();
  }

  template <size_t N, size_t Default=dynamic_extent>
  MDSPAN_INLINE_FUNCTION
  static constexpr
  index_type __static_extent() noexcept {
    return __storage_t::template __get_static_n<N, Default>();
  }

};

namespace detail {

template <class IndexType, size_t Rank, class Extents = ::std::experimental::extents<IndexType>>
struct __make_dextents;

template <class IndexType, size_t Rank, size_t... ExtentsPack>
struct __make_dextents<IndexType, Rank, ::std::experimental::extents<IndexType, ExtentsPack...>> {
  using type = typename __make_dextents<IndexType, Rank - 1,
    ::std::experimental::extents<IndexType, ::std::experimental::dynamic_extent, ExtentsPack...>>::type;
};

template <class IndexType, size_t... ExtentsPack>
struct __make_dextents<IndexType, 0, ::std::experimental::extents<IndexType, ExtentsPack...>> {
  using type = ::std::experimental::extents<IndexType, ExtentsPack...>;
};

} // end namespace detail

template <class IndexType, size_t Rank>
using dextents = typename detail::__make_dextents<IndexType, Rank>::type;

#if defined(_MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION)
template <class... IndexTypes>
extents(IndexTypes...)
  -> extents<size_t, size_t((IndexTypes(), ::std::experimental::dynamic_extent))...>;
#endif

namespace detail {

template <class T>
struct __is_extents : ::std::false_type {};

template <class IndexType, size_t... ExtentsPack>
struct __is_extents<::std::experimental::extents<IndexType, ExtentsPack...>> : ::std::true_type {};

template <class T>
static constexpr bool __is_extents_v = __is_extents<T>::value;


template <typename Extents>
struct __extents_to_partially_static_sizes;

template <class IndexType, size_t... ExtentsPack>
struct __extents_to_partially_static_sizes<::std::experimental::extents<IndexType, ExtentsPack...>> {
  using type = detail::__partially_static_sizes<
          typename ::std::experimental::extents<IndexType, ExtentsPack...>::index_type, size_t, 
          ExtentsPack...>;
};

template <typename Extents>
using __extents_to_partially_static_sizes_t = typename __extents_to_partially_static_sizes<Extents>::type;

} // end namespace detail
} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/extents.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_stride.hpp
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



#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#endif

#ifdef __cpp_lib_span
#endif
#if defined(_MDSPAN_USE_CONCEPTS) && MDSPAN_HAS_CXX_20
#endif

namespace std {
namespace experimental {

struct layout_left {
  template<class Extents>
    class mapping;
};
struct layout_right {
  template<class Extents>
    class mapping;
};

namespace detail {
  template<class Layout, class Mapping>
  constexpr bool __is_mapping_of =
    is_same<typename Layout::template mapping<typename Mapping::extents_type>, Mapping>::value;

#if defined(_MDSPAN_USE_CONCEPTS) && MDSPAN_HAS_CXX_20
  template<class M>
  concept __layout_mapping_alike = requires {
    requires __is_extents<typename M::extents_type>::value;
    { M::is_always_strided() } -> same_as<bool>;
    { M::is_always_exhaustive() } -> same_as<bool>;
    { M::is_always_unique() } -> same_as<bool>;
    bool_constant<M::is_always_strided()>::value;
    bool_constant<M::is_always_exhaustive()>::value;
    bool_constant<M::is_always_unique()>::value;
  };
#endif
} // namespace detail

struct layout_stride {
  template <class Extents>
  class mapping
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : private detail::__no_unique_address_emulation<
        detail::__compressed_pair<
          Extents,
          std::array<typename Extents::index_type, Extents::rank()>
        >
      >
#endif
  {
  public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_stride;

    // This could be a `requires`, but I think it's better and clearer as a `static_assert`.
    static_assert(detail::__is_extents_v<Extents>, "std::experimental::layout_stride::mapping must be instantiated with a specialization of std::experimental::extents.");


  private:

    //----------------------------------------------------------------------------

    using __strides_storage_t = array<index_type, extents_type::rank()>;//::std::experimental::dextents<index_type, extents_type::rank()>;
    using __member_pair_t = detail::__compressed_pair<extents_type, __strides_storage_t>;

#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    _MDSPAN_NO_UNIQUE_ADDRESS __member_pair_t __members;
#else
    using __base_t = detail::__no_unique_address_emulation<__member_pair_t>;
#endif

    MDSPAN_FORCE_INLINE_FUNCTION constexpr __strides_storage_t const&
    __strides_storage() const noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      return __members.__second();
#else
      return this->__base_t::__ref().__second();
#endif
    }
    MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 __strides_storage_t&
    __strides_storage() noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      return __members.__second();
#else
      return this->__base_t::__ref().__second();
#endif
    }

    //----------------------------------------------------------------------------

    template <class>
    friend class mapping;

    //----------------------------------------------------------------------------

    // Workaround for non-deducibility of the index sequence template parameter if it's given at the top level
    template <class>
    struct __deduction_workaround;

    template <size_t... Idxs>
    struct __deduction_workaround<index_sequence<Idxs...>>
    {
      template <class OtherExtents>
      MDSPAN_INLINE_FUNCTION
      static constexpr bool _eq_impl(mapping const& self, mapping<OtherExtents> const& other) noexcept {
        return _MDSPAN_FOLD_AND((self.stride(Idxs) == other.stride(Idxs)) /* && ... */);
      }
      template <class OtherExtents>
      MDSPAN_INLINE_FUNCTION
      static constexpr bool _not_eq_impl(mapping const& self, mapping<OtherExtents> const& other) noexcept {
        return _MDSPAN_FOLD_OR((self.stride(Idxs) != other.stride(Idxs)) /* || ... */);
      }

      template <class... Integral>
      MDSPAN_FORCE_INLINE_FUNCTION
      static constexpr size_t _call_op_impl(mapping const& self, Integral... idxs) noexcept {
        return _MDSPAN_FOLD_PLUS_RIGHT((idxs * self.stride(Idxs)), /* + ... + */ 0);
      }

      MDSPAN_INLINE_FUNCTION
      static constexpr size_t _req_span_size_impl(mapping const& self) noexcept {
        // assumes no negative strides; not sure if I'm allowed to assume that or not
        return __impl::_call_op_impl(self, (self.extents().template __extent<Idxs>() - 1)...) + 1;
      }

      template<class OtherMapping>
      MDSPAN_INLINE_FUNCTION
      static constexpr const __strides_storage_t fill_strides(const OtherMapping& map) {
        return __strides_storage_t{static_cast<index_type>(map.stride(Idxs))...};
      }

      MDSPAN_INLINE_FUNCTION
      static constexpr const __strides_storage_t& fill_strides(const __strides_storage_t& s) {
        return s;
      }

      template<class IntegralType>
      MDSPAN_INLINE_FUNCTION
      static constexpr const __strides_storage_t fill_strides(const array<IntegralType,extents_type::rank()>& s) {
        return __strides_storage_t{static_cast<index_type>(s[Idxs])...};
      }

#ifdef __cpp_lib_span
      template<class IntegralType>
      MDSPAN_INLINE_FUNCTION
      static constexpr const __strides_storage_t fill_strides(const span<IntegralType,extents_type::rank()>& s) {
        return __strides_storage_t{static_cast<index_type>(s[Idxs])...};
      }
#endif

      MDSPAN_INLINE_FUNCTION
      static constexpr const __strides_storage_t fill_strides(
        detail::__extents_to_partially_static_sizes_t<
          ::std::experimental::dextents<index_type, extents_type::rank()>>&& s) {
        return __strides_storage_t{static_cast<index_type>(s.template __get_n<Idxs>())...};
      }

      template<size_t K>
      MDSPAN_INLINE_FUNCTION
      static constexpr size_t __return_zero() { return 0; }

      template<class Mapping>
      MDSPAN_INLINE_FUNCTION
      static constexpr typename Mapping::index_type
        __OFFSET(const Mapping& m) { return m(__return_zero<Idxs>()...); }
    };

    // Can't use defaulted parameter in the __deduction_workaround template because of a bug in MSVC warning C4348.
    using __impl = __deduction_workaround<make_index_sequence<Extents::rank()>>;


    //----------------------------------------------------------------------------

#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    MDSPAN_INLINE_FUNCTION constexpr explicit
    mapping(__member_pair_t&& __m) : __members(::std::move(__m)) {}
#else
    MDSPAN_INLINE_FUNCTION constexpr explicit
    mapping(__base_t&& __b) : __base_t(::std::move(__b)) {}
#endif

  public: // but not really
    MDSPAN_INLINE_FUNCTION
    static constexpr mapping
    __make_mapping(
      detail::__extents_to_partially_static_sizes_t<Extents>&& __exts,
      detail::__extents_to_partially_static_sizes_t<
        ::std::experimental::dextents<index_type, Extents::rank()>>&& __strs
    ) noexcept {
      // call the private constructor we created for this purpose
      return mapping(
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        __base_t{
#endif
          __member_pair_t(
            extents_type::__make_extents_impl(::std::move(__exts)),
            __strides_storage_t{__impl::fill_strides(::std::move(__strs))}
          )
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#endif
      );
    }
    //----------------------------------------------------------------------------


  public:

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping const&) noexcept = default;

    MDSPAN_TEMPLATE_REQUIRES(
      class IntegralTypes,
      /* requires */ (
        // MSVC 19.32 does not like using index_type here, requires the typename Extents::index_type
        // error C2641: cannot deduce template arguments for 'std::experimental::layout_stride::mapping'
        _MDSPAN_TRAIT(is_convertible, const remove_const_t<IntegralTypes>&, typename Extents::index_type) &&
        _MDSPAN_TRAIT(is_nothrow_constructible, typename Extents::index_type, const remove_const_t<IntegralTypes>&)
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr
    mapping(
      extents_type const& e,
      array<IntegralTypes, extents_type::rank()> const& s
    ) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __members{
#else
      : __base_t(__base_t{__member_pair_t(
#endif
          e, __strides_storage_t(__impl::fill_strides(s))
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
    {
      /*
       * TODO: check preconditions
       * - s[i] > 0 is true for all i in the range [0, rank_ ).
       * - REQUIRED-SPAN-SIZE(e, s) is a representable value of type index_type ([basic.fundamental]).
       * - If rank_ is greater than 0, then there exists a permutation P of the integers in the
       *   range [0, rank_), such that s[ pi ] >= s[ pi − 1 ] * e.extent( pi − 1 ) is true for
       *   all i in the range [1, rank_ ), where pi is the ith element of P.
       */
    }

#ifdef __cpp_lib_span
    MDSPAN_TEMPLATE_REQUIRES(
      class IntegralTypes,
      /* requires */ (
        // MSVC 19.32 does not like using index_type here, requires the typename Extents::index_type
        // error C2641: cannot deduce template arguments for 'std::experimental::layout_stride::mapping'
        _MDSPAN_TRAIT(is_convertible, const remove_const_t<IntegralTypes>&, typename Extents::index_type) &&
        _MDSPAN_TRAIT(is_nothrow_constructible, typename Extents::index_type, const remove_const_t<IntegralTypes>&)
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr
    mapping(
      extents_type const& e,
      span<IntegralTypes, extents_type::rank()> const& s
    ) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __members{
#else
      : __base_t(__base_t{__member_pair_t(
#endif
          e, __strides_storage_t(__impl::fill_strides(s))
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
    {
      /*
       * TODO: check preconditions
       * - s[i] > 0 is true for all i in the range [0, rank_ ).
       * - REQUIRED-SPAN-SIZE(e, s) is a representable value of type index_type ([basic.fundamental]).
       * - If rank_ is greater than 0, then there exists a permutation P of the integers in the
       *   range [0, rank_), such that s[ pi ] >= s[ pi − 1 ] * e.extent( pi − 1 ) is true for
       *   all i in the range [1, rank_ ), where pi is the ith element of P.
       */
    }
#endif // __cpp_lib_span

#if !(defined(_MDSPAN_USE_CONCEPTS) && MDSPAN_HAS_CXX_20)
    MDSPAN_TEMPLATE_REQUIRES(
      class StridedLayoutMapping,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, extents_type, typename StridedLayoutMapping::extents_type) &&
        detail::__is_mapping_of<typename StridedLayoutMapping::layout_type, StridedLayoutMapping> &&
        StridedLayoutMapping::is_always_unique() &&
        StridedLayoutMapping::is_always_strided()
      )
    )
#else
    template<class StridedLayoutMapping>
    requires(
         detail::__layout_mapping_alike<StridedLayoutMapping> &&
         _MDSPAN_TRAIT(is_constructible, extents_type, typename StridedLayoutMapping::extents_type) &&
         StridedLayoutMapping::is_always_unique() &&
         StridedLayoutMapping::is_always_strided()
    )
#endif
    MDSPAN_CONDITIONAL_EXPLICIT(
      (!is_convertible<typename StridedLayoutMapping::extents_type, extents_type>::value) &&
      (detail::__is_mapping_of<layout_left, StridedLayoutMapping> ||
       detail::__is_mapping_of<layout_right, StridedLayoutMapping> ||
       detail::__is_mapping_of<layout_stride, StridedLayoutMapping>)
    ) // needs two () due to comma
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(StridedLayoutMapping const& other) noexcept // NOLINT(google-explicit-constructor)
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __members{
#else
      : __base_t(__base_t{__member_pair_t(
#endif
          other.extents(), __strides_storage_t(__impl::fill_strides(other))
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
    {
      /*
       * TODO: check preconditions
       * - other.stride(i) > 0 is true for all i in the range [0, rank_ ).
       * - other.required_span_size() is a representable value of type index_type ([basic.fundamental]).
       * - OFFSET(other) == 0
       */
    }

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED
    mapping& operator=(mapping const&) noexcept = default;

    MDSPAN_INLINE_FUNCTION constexpr const extents_type& extents() const noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      return __members.__first();
#else
      return this->__base_t::__ref().__first();
#endif
    };

    MDSPAN_INLINE_FUNCTION
    constexpr array< index_type, extents_type::rank() > strides() const noexcept {
      return __strides_storage();
    }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type required_span_size() const noexcept {
      index_type span_size = 1;
      for(unsigned r = 0; r < extents_type::rank(); r++) {
        // Return early if any of the extents are zero
        if(extents().extent(r)==0) return 0;
        span_size = std::max(span_size, static_cast<index_type>(extents().extent(r) * __strides_storage()[r]));
      }
      return span_size;
    }


    MDSPAN_TEMPLATE_REQUIRES(
      class... Indices,
      /* requires */ (
        sizeof...(Indices) == Extents::rank() &&
        _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, Indices, index_type) /*&& ...*/ ) &&
        _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_nothrow_constructible, index_type, Indices) /*&& ...*/)
      )
    )
    MDSPAN_FORCE_INLINE_FUNCTION
    constexpr size_t operator()(Indices... idxs) const noexcept {
      return __impl::_call_op_impl(*this, static_cast<index_type>(idxs)...);
    }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept {
      return false;
    }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 bool is_exhaustive() const noexcept {
// TODO @testing test layout_stride is_exhaustive()
// FIXME CUDA
#ifdef __CUDA_ARCH__
      return false;
#else
      auto rem = array<size_t, Extents::rank()>{ };
      std::iota(rem.begin(), rem.end(), size_t(0));
      auto next_idx_iter = std::find_if(
        rem.begin(), rem.end(),
        [&](size_t i) { return this->stride(i) == 1;  }
      );
      if(next_idx_iter != rem.end()) {
        size_t prev_stride_times_prev_extent =
          this->extents().extent(*next_idx_iter) * this->stride(*next_idx_iter);
        // "remove" the index
        constexpr auto removed_index_sentinel = static_cast<size_t>(-1);
        *next_idx_iter = removed_index_sentinel;
        size_t found_count = 1;
        while (found_count != Extents::rank()) {
          next_idx_iter = std::find_if(
            rem.begin(), rem.end(),
            [&](size_t i) {
              return i != removed_index_sentinel
                && static_cast<size_t>(this->extents().extent(i)) == prev_stride_times_prev_extent;
            }
          );
          if (next_idx_iter != rem.end()) {
            // "remove" the index
            *next_idx_iter = removed_index_sentinel;
            ++found_count;
            prev_stride_times_prev_extent = stride(*next_idx_iter) * this->extents().extent(*next_idx_iter);
          } else { break; }
        }
        return found_count == Extents::rank();
      }
      return false;
#endif
    }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_strided() noexcept { return true; }


    MDSPAN_INLINE_FUNCTION
    constexpr index_type stride(rank_type r) const noexcept {
      return __strides_storage()[r];
    }

#if !(defined(_MDSPAN_USE_CONCEPTS) && MDSPAN_HAS_CXX_20)
    MDSPAN_TEMPLATE_REQUIRES(
      class StridedLayoutMapping,
      /* requires */ (
        detail::__is_mapping_of<typename StridedLayoutMapping::layout_type, StridedLayoutMapping> &&
        (extents_type::rank() == StridedLayoutMapping::extents_type::rank()) &&
        StridedLayoutMapping::is_always_strided()
      )
    )
#else
    template<class StridedLayoutMapping>
    requires(
         detail::__layout_mapping_alike<StridedLayoutMapping> &&
         (extents_type::rank() == StridedLayoutMapping::extents_type::rank()) &&
         StridedLayoutMapping::is_always_strided()
    )
#endif
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(const mapping& x, const StridedLayoutMapping& y) noexcept {
      bool strides_match = true;
      for(rank_type r = 0; r < extents_type::rank(); r++)
        strides_match = strides_match && (x.stride(r) == y.stride(r));
      return (x.extents() == y.extents()) &&
             (__impl::__OFFSET(y)== static_cast<typename StridedLayoutMapping::index_type>(0)) &&
             strides_match;
    }

    // This one is not technically part of the proposal. Just here to make implementation a bit more optimal hopefully
    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        (extents_type::rank() == OtherExtents::rank())
      )
    )
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return __impl::_eq_impl(lhs, rhs);
    }

#if !MDSPAN_HAS_CXX_20
    MDSPAN_TEMPLATE_REQUIRES(
      class StridedLayoutMapping,
      /* requires */ (
        detail::__is_mapping_of<typename StridedLayoutMapping::layout_type, StridedLayoutMapping> &&
        (extents_type::rank() == StridedLayoutMapping::extents_type::rank()) &&
        StridedLayoutMapping::is_always_strided()
      )
    )
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(const mapping& x, const StridedLayoutMapping& y) noexcept {
      return not (x == y);
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        (extents_type::rank() == OtherExtents::rank())
      )
    )
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return __impl::_not_eq_impl(lhs, rhs);
    }
#endif

  };
};

} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_stride.hpp

namespace std {
namespace experimental {

//==============================================================================
template <class Extents>
class layout_right::mapping {
  public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_right;
  private:

    static_assert(detail::__is_extents_v<extents_type>, "std::experimental::layout_right::mapping must be instantiated with a specialization of std::experimental::extents.");

    template <class>
    friend class mapping;

    // i0+(i1 + E(1)*(i2 + E(2)*i3))
    template <size_t r, size_t Rank>
    struct __rank_count {};

    template <size_t r, size_t Rank, class I, class... Indices>
    _MDSPAN_HOST_DEVICE
    constexpr index_type __compute_offset(
      index_type offset, __rank_count<r,Rank>, const I& i, Indices... idx) const {
      return __compute_offset(offset * __extents.template __extent<r>() + i,__rank_count<r+1,Rank>(),  idx...);
    }

    template<class I, class ... Indices>
    _MDSPAN_HOST_DEVICE
    constexpr index_type __compute_offset(
      __rank_count<0,extents_type::rank()>, const I& i, Indices... idx) const {
      return __compute_offset(i,__rank_count<1,extents_type::rank()>(),idx...);
    }

    _MDSPAN_HOST_DEVICE
    constexpr index_type __compute_offset(size_t offset, __rank_count<extents_type::rank(), extents_type::rank()>) const {
      return static_cast<index_type>(offset);
    }

    _MDSPAN_HOST_DEVICE
    constexpr index_type __compute_offset(__rank_count<0,0>) const { return 0; }

  public:

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping const&) noexcept = default;

    _MDSPAN_HOST_DEVICE
    constexpr mapping(extents_type const& __exts) noexcept
      :__extents(__exts)
    { }

    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, extents_type, OtherExtents)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((!is_convertible<OtherExtents, extents_type>::value)) // needs two () due to comma
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(mapping<OtherExtents> const& other) noexcept // NOLINT(google-explicit-constructor)
      :__extents(other.extents())
    {
       /*
        * TODO: check precondition
        * other.required_span_size() is a representable value of type index_type
        */
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, extents_type, OtherExtents) &&
        (extents_type::rank() <= 1)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((!is_convertible<OtherExtents, extents_type>::value)) // needs two () due to comma
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(layout_left::mapping<OtherExtents> const& other) noexcept // NOLINT(google-explicit-constructor)
      :__extents(other.extents())
    {
       /*
        * TODO: check precondition
        * other.required_span_size() is a representable value of type index_type
        */
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, extents_type, OtherExtents)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((extents_type::rank() > 0))
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(layout_stride::mapping<OtherExtents> const& other) // NOLINT(google-explicit-constructor)
      :__extents(other.extents())
    {
       /*
        * TODO: check precondition
        * other.required_span_size() is a representable value of type index_type
        */
       #ifndef __CUDA_ARCH__
       size_t stride = 1;
       for(rank_type r=__extents.rank(); r>0; r--) {
         if(stride != other.stride(r-1))
           throw std::runtime_error("Assigning layout_stride to layout_right with invalid strides.");
         stride *= __extents.extent(r-1);
       }
       #endif
    }

    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping const&) noexcept = default;

    MDSPAN_INLINE_FUNCTION
    constexpr const extents_type& extents() const noexcept {
      return __extents;
    }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type required_span_size() const noexcept {
      index_type value = 1;
      for(rank_type r=0; r != extents_type::rank(); ++r) value*=__extents.extent(r);
      return value;
    }

    //--------------------------------------------------------------------------------

    MDSPAN_TEMPLATE_REQUIRES(
      class... Indices,
      /* requires */ (
        (sizeof...(Indices) == extents_type::rank()) &&
        _MDSPAN_FOLD_AND(
           (_MDSPAN_TRAIT(is_convertible, Indices, index_type) &&
            _MDSPAN_TRAIT(is_nothrow_constructible, index_type, Indices))
        )
      )
    )
    _MDSPAN_HOST_DEVICE
    constexpr index_type operator()(Indices... idxs) const noexcept {
      return __compute_offset(__rank_count<0, extents_type::rank()>(), idxs...);
    }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
    MDSPAN_INLINE_FUNCTION constexpr bool is_exhaustive() const noexcept { return true; }
    MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type stride(rank_type i) const noexcept {
      index_type value = 1;
      for(rank_type r=extents_type::rank()-1; r>i; r--) value*=__extents.extent(r);
      return value;
    }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() == rhs.extents();
    }

    // In C++ 20 the not equal exists if equal is found
#if MDSPAN_HAS_CXX_20
    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() != rhs.extents();
    }
#endif

    // Not really public, but currently needed to implement fully constexpr useable submdspan:
    template<size_t N, class SizeType, size_t ... E, size_t ... Idx>
    constexpr index_type __get_stride(std::experimental::extents<SizeType, E...>,integer_sequence<size_t, Idx...>) const {
      return _MDSPAN_FOLD_TIMES_RIGHT((Idx>N? __extents.template __extent<Idx>():1),1);
    }
    template<size_t N>
    constexpr index_type __stride() const noexcept {
      return __get_stride<N>(__extents, make_index_sequence<extents_type::rank()>());
    }

private:
   _MDSPAN_NO_UNIQUE_ADDRESS extents_type __extents{};

};

} // end namespace experimental
} // end namespace std

//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_right.hpp

namespace std {
namespace experimental {

template <
  class ElementType,
  class Extents,
  class LayoutPolicy = layout_right,
  class AccessorPolicy = default_accessor<ElementType>
>
class mdspan
{
private:
  static_assert(detail::__is_extents_v<Extents>, "std::experimental::mdspan's Extents template parameter must be a specialization of std::experimental::extents.");

  // Workaround for non-deducibility of the index sequence template parameter if it's given at the top level
  template <class>
  struct __deduction_workaround;

  template <size_t... Idxs>
  struct __deduction_workaround<index_sequence<Idxs...>>
  {
    MDSPAN_FORCE_INLINE_FUNCTION static constexpr
    size_t __size(mdspan const& __self) noexcept {
      return _MDSPAN_FOLD_TIMES_RIGHT((__self.__mapping_ref().extents().template __extent<Idxs>()), /* * ... * */ size_t(1));
    }
    MDSPAN_FORCE_INLINE_FUNCTION static constexpr
    bool __empty(mdspan const& __self) noexcept {
      return (__self.rank()>0) && _MDSPAN_FOLD_OR((__self.__mapping_ref().extents().template __extent<Idxs>()==index_type(0)));
    }
    template <class ReferenceType, class SizeType, size_t N>
    MDSPAN_FORCE_INLINE_FUNCTION static constexpr
    ReferenceType __callop(mdspan const& __self, const array<SizeType, N>& indices) noexcept {
      return __self.__accessor_ref().access(__self.__ptr_ref(), __self.__mapping_ref()(indices[Idxs]...));
    }
  };

public:

  //--------------------------------------------------------------------------------
  // Domain and codomain types

  using extents_type = Extents;
  using layout_type = LayoutPolicy;
  using accessor_type = AccessorPolicy;
  using mapping_type = typename layout_type::template mapping<extents_type>;
  using element_type = ElementType;
  using value_type = remove_cv_t<element_type>;
  using index_type = typename extents_type::index_type;
  using size_type = typename extents_type::size_type;
  using rank_type = typename extents_type::rank_type;
  using data_handle_type = typename accessor_type::data_handle_type;
  using reference = typename accessor_type::reference;

  MDSPAN_INLINE_FUNCTION static constexpr size_t rank() noexcept { return extents_type::rank(); }
  MDSPAN_INLINE_FUNCTION static constexpr size_t rank_dynamic() noexcept { return extents_type::rank_dynamic(); }
  MDSPAN_INLINE_FUNCTION static constexpr size_t static_extent(size_t r) noexcept { return extents_type::static_extent(r); }
  MDSPAN_INLINE_FUNCTION constexpr index_type extent(size_t r) const noexcept { return __mapping_ref().extents().extent(r); };

private:

  // Can't use defaulted parameter in the __deduction_workaround template because of a bug in MSVC warning C4348.
  using __impl = __deduction_workaround<make_index_sequence<extents_type::rank()>>;

  using __map_acc_pair_t = detail::__compressed_pair<mapping_type, accessor_type>;

public:

  //--------------------------------------------------------------------------------
  // [mdspan.basic.cons], mdspan constructors, assignment, and destructor

#if !MDSPAN_HAS_CXX_20
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdspan() = default;
#else
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdspan()
    requires(
       (rank_dynamic() > 0) &&
       _MDSPAN_TRAIT(is_default_constructible, data_handle_type) &&
       _MDSPAN_TRAIT(is_default_constructible, mapping_type) &&
       _MDSPAN_TRAIT(is_default_constructible, accessor_type)
     ) = default;
#endif
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdspan(const mdspan&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdspan(mdspan&&) = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeTypes) /* && ... */) &&
      ((sizeof...(SizeTypes) == rank()) || (sizeof...(SizeTypes) == rank_dynamic())) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr mdspan(data_handle_type p, SizeTypes... dynamic_extents)
    // TODO @proposal-bug shouldn't I be allowed to do `move(p)` here?
    : __members(std::move(p), __map_acc_pair_t(mapping_type(extents_type(static_cast<index_type>(std::move(dynamic_extents))...)), accessor_type()))
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeType) &&
      ((N == rank()) || (N == rank_dynamic())) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_CONDITIONAL_EXPLICIT(N != rank_dynamic())
  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(data_handle_type p, const array<SizeType, N>& dynamic_extents)
    : __members(std::move(p), __map_acc_pair_t(mapping_type(extents_type(dynamic_extents)), accessor_type()))
  { }

#ifdef __cpp_lib_span
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeType) &&
      ((N == rank()) || (N == rank_dynamic())) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_CONDITIONAL_EXPLICIT(N != rank_dynamic())
  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(data_handle_type p, span<SizeType, N> dynamic_extents)
    : __members(std::move(p), __map_acc_pair_t(mapping_type(extents_type(as_const(dynamic_extents))), accessor_type()))
  { }
#endif

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdspan, (data_handle_type p, const extents_type& exts), ,
    /* requires */ (_MDSPAN_TRAIT(is_default_constructible, accessor_type) &&
                    _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type))
  ) : __members(std::move(p), __map_acc_pair_t(mapping_type(exts), accessor_type()))
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdspan, (data_handle_type p, const mapping_type& m), ,
    /* requires */ (_MDSPAN_TRAIT(is_default_constructible, accessor_type))
  ) : __members(std::move(p), __map_acc_pair_t(m, accessor_type()))
  { }

  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(data_handle_type p, const mapping_type& m, const accessor_type& a)
    : __members(std::move(p), __map_acc_pair_t(m, a))
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherAccessor,
    /* requires */ (
      _MDSPAN_TRAIT(is_constructible, mapping_type, typename OtherLayoutPolicy::template mapping<OtherExtents>) &&
      _MDSPAN_TRAIT(is_constructible, accessor_type, OtherAccessor)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(const mdspan<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>& other)
    : __members(other.__ptr_ref(), __map_acc_pair_t(other.__mapping_ref(), other.__accessor_ref()))
  {
      static_assert(_MDSPAN_TRAIT(is_constructible, data_handle_type, typename OtherAccessor::data_handle_type),"Incompatible data_handle_type for mdspan construction");
      static_assert(_MDSPAN_TRAIT(is_constructible, extents_type, OtherExtents),"Incompatible extents for mdspan construction");
      /*
       * TODO: Check precondition
       * For each rank index r of extents_type, static_extent(r) == dynamic_extent || static_extent(r) == other.extent(r) is true.
       */
  }

  /* Might need this on NVIDIA?
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~mdspan() = default;
  */

  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mdspan& operator=(const mdspan&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mdspan& operator=(mdspan&&) = default;


  //--------------------------------------------------------------------------------
  // [mdspan.basic.mapping], mdspan mapping domain multidimensional index to access codomain element

  #if MDSPAN_USE_BRACKET_OPERATOR
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeTypes) /* && ... */) &&
      (rank() == sizeof...(SizeTypes))
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](SizeTypes... indices) const
  {
    return __accessor_ref().access(__ptr_ref(), __mapping_ref()(static_cast<index_type>(std::move(indices))...));
  }
  #endif

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeType)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](const array<SizeType, rank()>& indices) const
  {
    return __impl::template __callop<reference>(*this, indices);
  }

  #ifdef __cpp_lib_span
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeType)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](span<SizeType, rank()> indices) const
  {
    return __impl::template __callop<reference>(*this, indices);
  }
  #endif // __cpp_lib_span

  #if !MDSPAN_USE_BRACKET_OPERATOR
  MDSPAN_TEMPLATE_REQUIRES(
    class Index,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, Index, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, Index) &&
      extents_type::rank() == 1
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](Index idx) const
  {
    return __accessor_ref().access(__ptr_ref(), __mapping_ref()(static_cast<index_type>(std::move(idx))));
  }
  #endif

  #if MDSPAN_USE_PAREN_OPERATOR
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeTypes) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(SizeTypes... indices) const
  {
    return __accessor_ref().access(__ptr_ref(), __mapping_ref()(static_cast<index_type>(std::move(indices))...));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeType)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(const array<SizeType, rank()>& indices) const
  {
    return __impl::template __callop<reference>(*this, indices);
  }

  #ifdef __cpp_lib_span
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, SizeType)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(span<SizeType, rank()> indices) const
  {
    return __impl::template __callop<reference>(*this, indices);
  }
  #endif // __cpp_lib_span
  #endif // MDSPAN_USE_PAREN_OPERATOR

  MDSPAN_INLINE_FUNCTION constexpr size_t size() const noexcept {
    return __impl::__size(*this);
  };

  MDSPAN_INLINE_FUNCTION constexpr bool empty() const noexcept {
    return __impl::__empty(*this);
  };

  MDSPAN_INLINE_FUNCTION
  friend constexpr void swap(mdspan& x, mdspan& y) noexcept {
    swap(x.__ptr_ref(), y.__ptr_ref());
    swap(x.__mapping_ref(), y.__mapping_ref());
    swap(x.__accessor_ref(), y.__accessor_ref());
  }

  //--------------------------------------------------------------------------------
  // [mdspan.basic.domobs], mdspan observers of the domain multidimensional index space


  MDSPAN_INLINE_FUNCTION constexpr const extents_type& extents() const noexcept { return __mapping_ref().extents(); };
  MDSPAN_INLINE_FUNCTION constexpr const data_handle_type& data_handle() const noexcept { return __ptr_ref(); };
  MDSPAN_INLINE_FUNCTION constexpr const mapping_type& mapping() const noexcept { return __mapping_ref(); };
  MDSPAN_INLINE_FUNCTION constexpr const accessor_type& accessor() const noexcept { return __accessor_ref(); };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.obs], mdspan observers of the mapping

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept { return mapping_type::is_always_exhaustive(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return mapping_type::is_always_strided(); };

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return __mapping_ref().is_unique(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_exhaustive() const noexcept { return __mapping_ref().is_exhaustive(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return __mapping_ref().is_strided(); };
  MDSPAN_INLINE_FUNCTION constexpr index_type stride(size_t r) const { return __mapping_ref().stride(r); };

private:

  detail::__compressed_pair<data_handle_type, __map_acc_pair_t> __members{};

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 data_handle_type& __ptr_ref() noexcept { return __members.__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr data_handle_type const& __ptr_ref() const noexcept { return __members.__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 mapping_type& __mapping_ref() noexcept { return __members.__second().__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr mapping_type const& __mapping_ref() const noexcept { return __members.__second().__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 accessor_type& __accessor_ref() noexcept { return __members.__second().__second(); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr accessor_type const& __accessor_ref() const noexcept { return __members.__second().__second(); }

  template <class, class, class, class>
  friend class mdspan;

};

#if defined(_MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION)
MDSPAN_TEMPLATE_REQUIRES(
  class ElementType, class... SizeTypes,
  /* requires */ _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_integral, SizeTypes) /* && ... */) &&
  (sizeof...(SizeTypes) > 0)
)
explicit mdspan(ElementType*, SizeTypes...)
  -> mdspan<ElementType, ::std::experimental::dextents<size_t, sizeof...(SizeTypes)>>;

MDSPAN_TEMPLATE_REQUIRES(
  class Pointer,
  (_MDSPAN_TRAIT(is_pointer, std::remove_reference_t<Pointer>))
)
mdspan(Pointer&&) -> mdspan<std::remove_pointer_t<std::remove_reference_t<Pointer>>, extents<size_t>>;

MDSPAN_TEMPLATE_REQUIRES(
  class CArray,
  (_MDSPAN_TRAIT(is_array, CArray) && (rank_v<CArray> == 1))
)
mdspan(CArray&) -> mdspan<std::remove_all_extents_t<CArray>, extents<size_t, ::std::extent_v<CArray,0>>>;

template <class ElementType, class SizeType, size_t N>
mdspan(ElementType*, const ::std::array<SizeType, N>&)
  -> mdspan<ElementType, ::std::experimental::dextents<size_t, N>>;

#ifdef __cpp_lib_span
template <class ElementType, class SizeType, size_t N>
mdspan(ElementType*, ::std::span<SizeType, N>)
  -> mdspan<ElementType, ::std::experimental::dextents<size_t, N>>;
#endif

// This one is necessary because all the constructors take `data_handle_type`s, not
// `ElementType*`s, and `data_handle_type` is taken from `accessor_type::data_handle_type`, which
// seems to throw off automatic deduction guides.
template <class ElementType, class SizeType, size_t... ExtentsPack>
mdspan(ElementType*, const extents<SizeType, ExtentsPack...>&)
  -> mdspan<ElementType, ::std::experimental::extents<SizeType, ExtentsPack...>>;

template <class ElementType, class MappingType>
mdspan(ElementType*, const MappingType&)
  -> mdspan<ElementType, typename MappingType::extents_type, typename MappingType::layout_type>;

template <class MappingType, class AccessorType>
mdspan(const typename AccessorType::data_handle_type, const MappingType&, const AccessorType&)
  -> mdspan<typename AccessorType::element_type, typename MappingType::extents_type, typename MappingType::layout_type, AccessorType>;
#endif



} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/mdspan.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_left.hpp
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



namespace std {
namespace experimental {

//==============================================================================

template <class Extents>
class layout_left::mapping {
  public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_left;
  private:

    static_assert(detail::__is_extents_v<extents_type>, "std::experimental::layout_left::mapping must be instantiated with a specialization of std::experimental::extents.");

    template <class>
    friend class mapping;

    // i0+(i1 + E(1)*(i2 + E(2)*i3))
    template <size_t r, size_t Rank>
    struct __rank_count {};

    template <size_t r, size_t Rank, class I, class... Indices>
    _MDSPAN_HOST_DEVICE
    constexpr index_type __compute_offset(
      __rank_count<r,Rank>, const I& i, Indices... idx) const {
      return __compute_offset(__rank_count<r+1,Rank>(), idx...) *
                 __extents.template __extent<r>() + i;
    }

    template<class I>
    _MDSPAN_HOST_DEVICE
    constexpr index_type __compute_offset(
      __rank_count<extents_type::rank()-1,extents_type::rank()>, const I& i) const {
      return i;
    }

    _MDSPAN_HOST_DEVICE
    constexpr index_type __compute_offset(__rank_count<0,0>) const { return 0; }

  public:

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping const&) noexcept = default;

    _MDSPAN_HOST_DEVICE
    constexpr mapping(extents_type const& __exts) noexcept
      :__extents(__exts)
    { }

    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, extents_type, OtherExtents)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((!is_convertible<OtherExtents, extents_type>::value)) // needs two () due to comma
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(mapping<OtherExtents> const& other) noexcept // NOLINT(google-explicit-constructor)
      :__extents(other.extents())
    {
       /*
        * TODO: check precondition
        * other.required_span_size() is a representable value of type index_type
        */
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, extents_type, OtherExtents) &&
        (extents_type::rank() <= 1)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((!is_convertible<OtherExtents, extents_type>::value)) // needs two () due to comma
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(layout_right::mapping<OtherExtents> const& other) noexcept // NOLINT(google-explicit-constructor)
      :__extents(other.extents())
    {
       /*
        * TODO: check precondition
        * other.required_span_size() is a representable value of type index_type
        */
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, extents_type, OtherExtents)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((extents_type::rank() > 0))
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(layout_stride::mapping<OtherExtents> const& other) // NOLINT(google-explicit-constructor)
      :__extents(other.extents())
    {
       /*
        * TODO: check precondition
        * other.required_span_size() is a representable value of type index_type
        */
       #ifndef __CUDA_ARCH__
       size_t stride = 1;
       for(rank_type r=0; r<__extents.rank(); r++) {
         if(stride != other.stride(r))
           throw std::runtime_error("Assigning layout_stride to layout_left with invalid strides.");
         stride *= __extents.extent(r);
       }
       #endif
    }

    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping const&) noexcept = default;

    MDSPAN_INLINE_FUNCTION
    constexpr const extents_type& extents() const noexcept {
      return __extents;
    }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type required_span_size() const noexcept {
      index_type value = 1;
      for(rank_type r=0; r<extents_type::rank(); r++) value*=__extents.extent(r);
      return value;
    }

    //--------------------------------------------------------------------------------

    MDSPAN_TEMPLATE_REQUIRES(
      class... Indices,
      /* requires */ (
        (sizeof...(Indices) == extents_type::rank()) &&
        _MDSPAN_FOLD_AND(
           (_MDSPAN_TRAIT(is_convertible, Indices, index_type) &&
            _MDSPAN_TRAIT(is_nothrow_constructible, index_type, Indices))
        )
      )
    )
    _MDSPAN_HOST_DEVICE
    constexpr index_type operator()(Indices... idxs) const noexcept {
      return __compute_offset(__rank_count<0, extents_type::rank()>(), idxs...);
    }



    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
    MDSPAN_INLINE_FUNCTION constexpr bool is_exhaustive() const noexcept { return true; }
    MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

    MDSPAN_INLINE_FUNCTION
    constexpr index_type stride(rank_type i) const noexcept {
      index_type value = 1;
      for(rank_type r=0; r<i; r++) value*=__extents.extent(r);
      return value;
    }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() == rhs.extents();
    }

    // In C++ 20 the not equal exists if equal is found
#if MDSPAN_HAS_CXX_20
    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() != rhs.extents();
    }
#endif

    // Not really public, but currently needed to implement fully constexpr useable submdspan:
    template<size_t N, class SizeType, size_t ... E, size_t ... Idx>
    constexpr index_type __get_stride(std::experimental::extents<SizeType, E...>,integer_sequence<size_t, Idx...>) const {
      return _MDSPAN_FOLD_TIMES_RIGHT((Idx<N? __extents.template __extent<Idx>():1),1);
    }
    template<size_t N>
    constexpr index_type __stride() const noexcept {
      return __get_stride<N>(__extents, make_index_sequence<extents_type::rank()>());
    }

private:
   _MDSPAN_NO_UNIQUE_ADDRESS extents_type __extents{};

};


} // end namespace experimental
} // end namespace std

//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_left.hpp
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/submdspan.hpp
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





namespace std {
namespace experimental {

namespace detail {

template <size_t OldExtent, size_t OldStaticStride, class T>
struct __slice_wrap {
  T slice;
  size_t old_extent;
  size_t old_stride;
};

//--------------------------------------------------------------------------------

template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
__slice_wrap<OldExtent, OldStaticStride, size_t>
__wrap_slice(size_t val, size_t ext, size_t stride) { return { val, ext, stride }; }

template <size_t OldExtent, size_t OldStaticStride, class IntegerType, IntegerType Value0>
MDSPAN_INLINE_FUNCTION constexpr
__slice_wrap<OldExtent, OldStaticStride, std::integral_constant<IntegerType, Value0>>
__wrap_slice(size_t val, size_t ext, std::integral_constant<IntegerType, Value0> stride)
{
#if MDSPAN_HAS_CXX_17
  if constexpr (std::is_signed_v<IntegerType>) {
    static_assert(Value0 >= IntegerType(0), "Invalid slice specifier");
  }
#endif // MDSPAN_HAS_CXX_17

  return { val, ext, stride };
}

template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
__slice_wrap<OldExtent, OldStaticStride, full_extent_t>
__wrap_slice(full_extent_t val, size_t ext, size_t stride) { return { val, ext, stride }; }

// TODO generalize this to anything that works with std::get<0> and std::get<1>
template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
__slice_wrap<OldExtent, OldStaticStride, std::tuple<size_t, size_t>>
__wrap_slice(std::tuple<size_t, size_t> const& val, size_t ext, size_t stride)
{
  return { val, ext, stride };
}

template <size_t OldExtent, size_t OldStaticStride,
	  class IntegerType0, IntegerType0 Value0,
	  class IntegerType1, IntegerType1 Value1>
MDSPAN_INLINE_FUNCTION constexpr
  __slice_wrap<OldExtent, OldStaticStride,
               std::tuple<std::integral_constant<IntegerType0, Value0>,
                          std::integral_constant<IntegerType1, Value1>>>
__wrap_slice(std::tuple<std::integral_constant<IntegerType0, Value0>, std::integral_constant<IntegerType1, Value1>> const& val, size_t ext, size_t stride)
{
  static_assert(Value1 >= Value0, "Invalid slice tuple");
  return { val, ext, stride };
}

//--------------------------------------------------------------------------------


// a layout right remains a layout right if it is indexed by 0 or more scalars,
// then optionally a pair and finally 0 or more all
template <
  // what we encountered until now preserves the layout right
  bool result=true,
  // we only encountered 0 or more scalars, no pair or all
  bool encountered_only_scalar=true
>
struct preserve_layout_right_analysis : integral_constant<bool, result> {
  using layout_type_if_preserved = layout_right;
  using encounter_pair = preserve_layout_right_analysis<
    // if we encounter a pair, the layout remains a layout right only if it was one before
    // and that only scalars were encountered until now
    result && encountered_only_scalar,
    // if we encounter a pair, we didn't encounter scalars only
    false
  >;
  using encounter_all = preserve_layout_right_analysis<
    // if we encounter a all, the layout remains a layout right if it was one before
    result,
    // if we encounter a all, we didn't encounter scalars only
    false
  >;
  using encounter_scalar = preserve_layout_right_analysis<
    // if we encounter a scalar, the layout remains a layout right only if it was one before
    // and that only scalars were encountered until now
    result && encountered_only_scalar,
    // if we encounter a scalar, the fact that we encountered scalars only doesn't change
    encountered_only_scalar
  >;
};

// a layout left remains a layout left if it is indexed by 0 or more all,
// then optionally a pair and finally 0 or more scalars
template <
  bool result=true,
  bool encountered_only_all=true
>
struct preserve_layout_left_analysis : integral_constant<bool, result> {
  using layout_type_if_preserved = layout_left;
  using encounter_pair = preserve_layout_left_analysis<
    // if we encounter a pair, the layout remains a layout left only if it was one before
    // and that only all were encountered until now
    result && encountered_only_all,
    // if we encounter a pair, we didn't encounter all only
    false
  >;
  using encounter_all = preserve_layout_left_analysis<
    // if we encounter a all, the layout remains a layout left only if it was one before
    // and that only all were encountered until now
    result && encountered_only_all,
    // if we encounter a all, the fact that we encountered scalars all doesn't change
    encountered_only_all
  >;
  using encounter_scalar = preserve_layout_left_analysis<
    // if we encounter a scalar, the layout remains a layout left if it was one before
    result,
    // if we encounter a scalar, we didn't encounter scalars only
    false
  >;
};

struct ignore_layout_preservation : std::integral_constant<bool, false> {
  using layout_type_if_preserved = void;
  using encounter_pair = ignore_layout_preservation;
  using encounter_all = ignore_layout_preservation;
  using encounter_scalar = ignore_layout_preservation;
};

template <class Layout>
struct preserve_layout_analysis
  : ignore_layout_preservation { };
template <>
struct preserve_layout_analysis<layout_right>
  : preserve_layout_right_analysis<> { };
template <>
struct preserve_layout_analysis<layout_left>
  : preserve_layout_left_analysis<> { };

//--------------------------------------------------------------------------------

template <
  class _IndexT,
  class _PreserveLayoutAnalysis,
  class _OffsetsArray=__partially_static_sizes<_IndexT, size_t>,
  class _ExtsArray=__partially_static_sizes<_IndexT, size_t>,
  class _StridesArray=__partially_static_sizes<_IndexT, size_t>,
  class = make_index_sequence<_OffsetsArray::__size>,
  class = make_index_sequence<_ExtsArray::__size>,
  class = make_index_sequence<_StridesArray::__size>
>
struct __assign_op_slice_handler;

/* clang-format: off */
template <
  class _IndexT,
  class _PreserveLayoutAnalysis,
  size_t... _Offsets,
  size_t... _Exts,
  size_t... _Strides,
  size_t... _OffsetIdxs,
  size_t... _ExtIdxs,
  size_t... _StrideIdxs>
struct __assign_op_slice_handler<
  _IndexT,
  _PreserveLayoutAnalysis,
  __partially_static_sizes<_IndexT, size_t, _Offsets...>,
  __partially_static_sizes<_IndexT, size_t, _Exts...>,
  __partially_static_sizes<_IndexT, size_t, _Strides...>,
  integer_sequence<size_t, _OffsetIdxs...>,
  integer_sequence<size_t, _ExtIdxs...>,
  integer_sequence<size_t, _StrideIdxs...>>
{
  // TODO remove this for better compiler performance
  static_assert(
    _MDSPAN_FOLD_AND((_Strides == dynamic_extent || _Strides > 0) /* && ... */),
    " "
  );
  static_assert(
    _MDSPAN_FOLD_AND((_Offsets == dynamic_extent || _Offsets >= 0) /* && ... */),
    " "
  );

  using __offsets_storage_t = __partially_static_sizes<_IndexT, size_t, _Offsets...>;
  using __extents_storage_t = __partially_static_sizes<_IndexT, size_t, _Exts...>;
  using __strides_storage_t = __partially_static_sizes<_IndexT, size_t, _Strides...>;
  __offsets_storage_t __offsets;
  __extents_storage_t __exts;
  __strides_storage_t __strides;

#ifdef __INTEL_COMPILER
#if __INTEL_COMPILER <= 1800
  MDSPAN_INLINE_FUNCTION constexpr __assign_op_slice_handler(__assign_op_slice_handler&& __other) noexcept
    : __offsets(::std::move(__other.__offsets)), __exts(::std::move(__other.__exts)), __strides(::std::move(__other.__strides))
  { }
  MDSPAN_INLINE_FUNCTION constexpr __assign_op_slice_handler(
    __offsets_storage_t&& __o,
    __extents_storage_t&& __e,
    __strides_storage_t&& __s
  ) noexcept
    : __offsets(::std::move(__o)), __exts(::std::move(__e)), __strides(::std::move(__s))
  { }
#endif
#endif

// Don't define this unless we need it; they have a cost to compile
#ifndef _MDSPAN_USE_RETURN_TYPE_DEDUCTION
  using __extents_type = ::std::experimental::extents<_IndexT, _Exts...>;
#endif

  // For size_t slice, skip the extent and stride, but add an offset corresponding to the value
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(__slice_wrap<_OldStaticExtent, _OldStaticStride, size_t>&& __slice) noexcept
    -> __assign_op_slice_handler<
         _IndexT,
         typename _PreserveLayoutAnalysis::encounter_scalar,
         __partially_static_sizes<_IndexT, size_t, _Offsets..., dynamic_extent>,
         __partially_static_sizes<_IndexT, size_t, _Exts...>,
         __partially_static_sizes<_IndexT, size_t, _Strides...>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_IndexT, size_t, _Offsets..., dynamic_extent>(
        __construct_psa_from_all_exts_values_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., __slice.slice),
      ::std::move(__exts),
      ::std::move(__strides)
    };
  }

  // Treat integral_constant slice like size_t slice, but with a compile-time offset.
  // The result's extents_type can't take advantage of that,
  // but it might help for specialized layouts.
  template <size_t _OldStaticExtent, size_t _OldStaticStride, class IntegerType, IntegerType Value0>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(__slice_wrap<_OldStaticExtent, _OldStaticStride, std::integral_constant<IntegerType, Value0>>&&) noexcept
    -> __assign_op_slice_handler<
         _IndexT,
         typename _PreserveLayoutAnalysis::encounter_scalar,
         __partially_static_sizes<_IndexT, size_t, _Offsets..., Value0>,
         __partially_static_sizes<_IndexT, size_t, _Exts...>,
         __partially_static_sizes<_IndexT, size_t, _Strides...>/* intentional space here to work around ICC bug*/> {
#if MDSPAN_HAS_CXX_17
    if constexpr (std::is_signed_v<IntegerType>) {
      static_assert(Value0 >= IntegerType(0), "Invalid slice specifier");
    }
#endif // MDSPAN_HAS_CXX_17
    return {
      __partially_static_sizes<_IndexT, size_t, _Offsets..., Value0>(
        __construct_psa_from_all_exts_values_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., size_t(Value0)),
      ::std::move(__exts),
      ::std::move(__strides)
    };
  }

  // For a std::full_extent, offset 0 and old extent
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(__slice_wrap<_OldStaticExtent, _OldStaticStride, full_extent_t>&& __slice) noexcept
    -> __assign_op_slice_handler<
         _IndexT,
         typename _PreserveLayoutAnalysis::encounter_all,
         __partially_static_sizes<_IndexT, size_t, _Offsets..., 0>,
         __partially_static_sizes<_IndexT, size_t, _Exts..., _OldStaticExtent>,
         __partially_static_sizes<_IndexT, size_t, _Strides..., _OldStaticStride>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_IndexT, size_t, _Offsets..., 0>(
        __construct_psa_from_all_exts_values_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., size_t(0)),
      __partially_static_sizes<_IndexT, size_t, _Exts..., _OldStaticExtent>(
        __construct_psa_from_all_exts_values_tag,
        __exts.template __get_n<_ExtIdxs>()..., __slice.old_extent),
      __partially_static_sizes<_IndexT, size_t, _Strides..., _OldStaticStride>(
        __construct_psa_from_all_exts_values_tag,
        __strides.template __get_n<_StrideIdxs>()..., __slice.old_stride)
    };
  }

  // For a std::tuple, add an offset and add a new dynamic extent (strides still preserved)
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(__slice_wrap<_OldStaticExtent, _OldStaticStride, tuple<size_t, size_t>>&& __slice) noexcept
    -> __assign_op_slice_handler<
         _IndexT,
         typename _PreserveLayoutAnalysis::encounter_pair,
         __partially_static_sizes<_IndexT, size_t, _Offsets..., dynamic_extent>,
         __partially_static_sizes<_IndexT, size_t, _Exts..., dynamic_extent>,
         __partially_static_sizes<_IndexT, size_t, _Strides..., _OldStaticStride>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_IndexT, size_t, _Offsets..., dynamic_extent>(
        __construct_psa_from_all_exts_values_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., ::std::get<0>(__slice.slice)),
      __partially_static_sizes<_IndexT, size_t, _Exts..., dynamic_extent>(
        __construct_psa_from_all_exts_values_tag,
        __exts.template __get_n<_ExtIdxs>()..., ::std::get<1>(__slice.slice) - ::std::get<0>(__slice.slice)),
      __partially_static_sizes<_IndexT, size_t, _Strides..., _OldStaticStride>(
        __construct_psa_from_all_exts_values_tag,
        __strides.template __get_n<_StrideIdxs>()..., __slice.old_stride)
    };
  }

  // For a std::tuple of two std::integral_constant, do something like
  // we did above for a tuple of two size_t, but make sure the
  // result's extents type make the values compile-time constants.
  template <size_t _OldStaticExtent, size_t _OldStaticStride,
	    class IntegerType0, IntegerType0 Value0,
	    class IntegerType1, IntegerType1 Value1>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(__slice_wrap<_OldStaticExtent, _OldStaticStride, tuple<std::integral_constant<IntegerType0, Value0>, std::integral_constant<IntegerType1, Value1>>>&& __slice) noexcept
    -> __assign_op_slice_handler<
         _IndexT,
         typename _PreserveLayoutAnalysis::encounter_pair,
         __partially_static_sizes<_IndexT, size_t, _Offsets..., size_t(Value0)>,
         __partially_static_sizes<_IndexT, size_t, _Exts..., size_t(Value1 - Value0)>,
         __partially_static_sizes<_IndexT, size_t, _Strides..., _OldStaticStride>/* intentional space here to work around ICC bug*/> {
    static_assert(Value1 >= Value0, "Invalid slice specifier");
    return {
      // We're still turning the template parameters Value0 and Value1
      // into (constexpr) run-time values here.
      __partially_static_sizes<_IndexT, size_t, _Offsets..., size_t(Value0) > (
        __construct_psa_from_all_exts_values_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., Value0),
      __partially_static_sizes<_IndexT, size_t, _Exts..., size_t(Value1 - Value0) > (
        __construct_psa_from_all_exts_values_tag,
        __exts.template __get_n<_ExtIdxs>()..., Value1 - Value0),
      __partially_static_sizes<_IndexT, size_t, _Strides..., _OldStaticStride>(
        __construct_psa_from_all_exts_values_tag,
        __strides.template __get_n<_StrideIdxs>()..., __slice.old_stride)
    };
  }

   // TODO defer instantiation of this?
  using layout_type = typename conditional<
    _PreserveLayoutAnalysis::value,
    typename _PreserveLayoutAnalysis::layout_type_if_preserved,
    layout_stride
  >::type;

  // TODO noexcept specification
  template <class NewLayout>
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      _MDSPAN_CONSTEXPR_14 /* auto */
      _make_layout_mapping_impl(NewLayout) noexcept
    ),
    (
      /* not layout stride, so don't pass dynamic_strides */
      /* return */ typename NewLayout::template mapping<::std::experimental::extents<_IndexT, _Exts...>>(
        experimental::extents<_IndexT, _Exts...>::__make_extents_impl(::std::move(__exts))
      ) /* ; */
    )
  )

  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      _MDSPAN_CONSTEXPR_14 /* auto */
      _make_layout_mapping_impl(layout_stride) noexcept
    ),
    (
      /* return */ layout_stride::template mapping<::std::experimental::extents<_IndexT, _Exts...>>
        ::__make_mapping(::std::move(__exts), ::std::move(__strides)) /* ; */
    )
  )

  template <class OldLayoutMapping> // mostly for deferred instantiation, but maybe we'll use this in the future
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
    (
      _MDSPAN_CONSTEXPR_14 /* auto */
      make_layout_mapping(OldLayoutMapping const&) noexcept
    ),
    (
      /* return */ this->_make_layout_mapping_impl(layout_type{}) /* ; */
    )
  )
};

//==============================================================================

#if _MDSPAN_USE_RETURN_TYPE_DEDUCTION
// Forking this because the C++11 version will be *completely* unreadable
template <class ET, class ST, size_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
MDSPAN_INLINE_FUNCTION
constexpr auto _submdspan_impl(
  integer_sequence<size_t, Idxs...>,
  mdspan<ET, std::experimental::extents<ST, Exts...>, LP, AP> const& src,
  SliceSpecs&&... slices
) noexcept
{
  using _IndexT = ST;
  auto _handled =
    _MDSPAN_FOLD_ASSIGN_LEFT(
      (
        detail::__assign_op_slice_handler<
          _IndexT,
          detail::preserve_layout_analysis<LP>
        >{
          __partially_static_sizes<_IndexT, size_t>{},
          __partially_static_sizes<_IndexT, size_t>{},
          __partially_static_sizes<_IndexT, size_t>{}
        }
      ),
        /* = ... = */
      detail::__wrap_slice<
        Exts, dynamic_extent
      >(
        slices, src.extents().template __extent<Idxs>(),
        src.mapping().stride(Idxs)
      )
    );

  size_t offset_size = src.mapping()(_handled.__offsets.template __get_n<Idxs>()...);
  auto offset_ptr = src.accessor().offset(src.data_handle(), offset_size);
  auto map = _handled.make_layout_mapping(src.mapping());
  auto acc_pol = typename AP::offset_policy(src.accessor());
  return mdspan<
    ET, remove_const_t<remove_reference_t<decltype(map.extents())>>,
        typename decltype(_handled)::layout_type, remove_const_t<remove_reference_t<decltype(acc_pol)>>
  >(
    std::move(offset_ptr), std::move(map), std::move(acc_pol)
  );
}
#else

template <class ET, class AP, class Src, class Handled, size_t... Idxs>
auto _submdspan_impl_helper(Src&& src, Handled&& h, std::integer_sequence<size_t, Idxs...>)
  -> mdspan<
       ET, typename Handled::__extents_type, typename Handled::layout_type, typename AP::offset_policy
     >
{
  return {
    src.accessor().offset(src.data_handle(), src.mapping()(h.__offsets.template __get_n<Idxs>()...)),
    h.make_layout_mapping(src.mapping()),
    typename AP::offset_policy(src.accessor())
  };
}

template <class ET, class ST, size_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
MDSPAN_INLINE_FUNCTION
_MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
  (
    constexpr /* auto */ _submdspan_impl(
      std::integer_sequence<size_t, Idxs...> seq,
      mdspan<ET, std::experimental::extents<ST, Exts...>, LP, AP> const& src,
      SliceSpecs&&... slices
    ) noexcept
  ),
  (
    /* return */ _submdspan_impl_helper<ET, AP>(
      src,
      _MDSPAN_FOLD_ASSIGN_LEFT(
        (
          detail::__assign_op_slice_handler<
            size_t,
            detail::preserve_layout_analysis<LP>
          >{
            __partially_static_sizes<ST, size_t>{},
            __partially_static_sizes<ST, size_t>{},
            __partially_static_sizes<ST, size_t>{}
          }
        ),
        /* = ... = */
        detail::__wrap_slice<
          Exts, dynamic_extent
        >(
          slices, src.extents().template __extent<Idxs>(), src.mapping().stride(Idxs)
        )
      ),
      seq
    ) /* ; */
  )
)

#endif

template <class T> struct _is_layout_stride : std::false_type { };
template<>
struct _is_layout_stride<
  layout_stride
> : std::true_type
{ };

} // namespace detail

//==============================================================================

MDSPAN_TEMPLATE_REQUIRES(
  class ET, class EXT, class LP, class AP, class... SliceSpecs,
  /* requires */ (
    (
      _MDSPAN_TRAIT(is_same, LP, layout_left)
        || _MDSPAN_TRAIT(is_same, LP, layout_right)
        || detail::_is_layout_stride<LP>::value
    ) &&
    _MDSPAN_FOLD_AND((
      _MDSPAN_TRAIT(is_convertible, SliceSpecs, size_t)
        || _MDSPAN_TRAIT(is_convertible, SliceSpecs, tuple<size_t, size_t>)
        || _MDSPAN_TRAIT(is_convertible, SliceSpecs, full_extent_t)
    ) /* && ... */) &&
    sizeof...(SliceSpecs) == EXT::rank()
  )
)
MDSPAN_INLINE_FUNCTION
_MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
  (
    constexpr submdspan(
      mdspan<ET, EXT, LP, AP> const& src, SliceSpecs... slices
    ) noexcept
  ),
  (
    /* return */
      detail::_submdspan_impl(std::make_index_sequence<sizeof...(SliceSpecs)>{}, src, slices...) /*;*/
  )
)
/* clang-format: on */

} // end namespace experimental
} // namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/submdspan.hpp
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/mdspan
//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p1684_bits/mdarray.hpp
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



//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p1684_bits/../mdspan
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


//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p1684_bits/../mdspan

namespace std {
namespace experimental {

namespace {
  template<class Extents>
  struct size_of_extents;

  template<class IndexType, size_t ... Extents>
  struct size_of_extents<extents<IndexType, Extents...>> {
    constexpr static size_t value() {
      size_t size = 1;
      for(size_t r=0; r<extents<IndexType, Extents...>::rank(); r++)
        size *= extents<IndexType, Extents...>::static_extent(r);
      return size;
    }
  };
}

namespace {
  template<class C>
  struct container_is_array : false_type {
    template<class M>
    static constexpr C construct(const M& m) { return C(m.required_span_size()); }
  };
  template<class T, size_t N>
  struct container_is_array<array<T,N>> : true_type {
    template<class M>
    static constexpr array<T,N> construct(const M&) { return array<T,N>(); }
  };
}

template <
  class ElementType,
  class Extents,
  class LayoutPolicy = layout_right,
  class Container = vector<ElementType>
>
class mdarray {
private:
  static_assert(detail::__is_extents_v<Extents>, "std::experimental::mdspan's Extents template parameter must be a specialization of std::experimental::extents.");


public:

  //--------------------------------------------------------------------------------
  // Domain and codomain types

  using extents_type = Extents;
  using layout_type = LayoutPolicy;
  using container_type = Container;
  using mapping_type = typename layout_type::template mapping<extents_type>;
  using element_type = ElementType;
  using value_type = remove_cv_t<element_type>;
  using index_type = typename Extents::index_type;
  using size_type = typename Extents::size_type;
  using rank_type = typename Extents::rank_type;
  using pointer = typename container_type::pointer;
  using reference = typename container_type::reference;
  using const_pointer = typename container_type::const_pointer;
  using const_reference = typename container_type::const_reference;

public:

  //--------------------------------------------------------------------------------
  // [mdspan.basic.cons], mdspan constructors, assignment, and destructor

#if !(MDSPAN_HAS_CXX_20)
  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr),
    mdarray, (), ,
    /* requires */ (extents_type::rank_dynamic()!=0)) {}
#else
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray() requires(extents_type::rank_dynamic()!=0) = default;
#endif
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray(const mdarray&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray(mdarray&&) = default;

  // Constructors for container types constructible from a size
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      _MDSPAN_TRAIT(is_constructible, extents_type, SizeTypes...) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      (_MDSPAN_TRAIT(is_constructible, container_type, size_t) ||
       container_is_array<container_type>::value) &&
      (extents_type::rank()>0 || extents_type::rank_dynamic()==0)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr mdarray(SizeTypes... dynamic_extents)
    : map_(extents_type(dynamic_extents...)), ctr_(container_is_array<container_type>::construct(map_))
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (const extents_type& exts), ,
    /* requires */ ((_MDSPAN_TRAIT(is_constructible, container_type, size_t) ||
                     container_is_array<container_type>::value) &&
                    _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type))
  ) : map_(exts), ctr_(container_is_array<container_type>::construct(map_))
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (const mapping_type& m), ,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, container_type, size_t) ||
                    container_is_array<container_type>::value)
  ) : map_(m), ctr_(container_is_array<container_type>::construct(map_))
  { }

  // Constructors from container
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      _MDSPAN_TRAIT(is_constructible, extents_type, SizeTypes...) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr mdarray(const container_type& ctr, SizeTypes... dynamic_extents)
    : map_(extents_type(dynamic_extents...)), ctr_(ctr)
  { assert(ctr.size() >= static_cast<size_t>(map_.required_span_size())); }


  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (const container_type& ctr, const extents_type& exts), ,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, mapping_type, extents_type))
  ) : map_(exts), ctr_(ctr)
  { assert(ctr.size() >= static_cast<size_t>(map_.required_span_size())); }

  constexpr mdarray(const container_type& ctr, const mapping_type& m)
    : map_(m), ctr_(ctr)
  { assert(ctr.size() >= static_cast<size_t>(map_.required_span_size())); }


  // Constructors from container
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      _MDSPAN_TRAIT(is_constructible, extents_type, SizeTypes...) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr mdarray(container_type&& ctr, SizeTypes... dynamic_extents)
    : map_(extents_type(dynamic_extents...)), ctr_(std::move(ctr))
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }


  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdarray, (container_type&& ctr, const extents_type& exts), ,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, mapping_type, extents_type))
  ) : map_(exts), ctr_(std::move(ctr))
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  constexpr mdarray(container_type&& ctr, const mapping_type& m)
    : map_(m), ctr_(std::move(ctr))
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }



  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherContainer,
    /* requires */ (
      _MDSPAN_TRAIT(is_constructible, mapping_type, typename OtherLayoutPolicy::template mapping<OtherExtents>) &&
      _MDSPAN_TRAIT(is_constructible, container_type, OtherContainer)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mdarray<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherContainer>& other)
    : map_(other.mapping()), ctr_(other.container())
  {
    static_assert(is_constructible<extents_type, OtherExtents>::value, "");
  }

  // Constructors for container types constructible from a size and allocator
  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, container_type, size_t, Alloc) &&
                    _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const extents_type& exts, const Alloc& a)
    : map_(exts), ctr_(map_.required_span_size(), a)
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, container_type, size_t, Alloc))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mapping_type& map, const Alloc& a)
    : map_(map), ctr_(map_.required_span_size(), a)
  { }

  // Constructors for container types constructible from a container and allocator
  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, container_type, container_type, Alloc) &&
                    _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const container_type& ctr, const extents_type& exts, const Alloc& a)
    : map_(exts), ctr_(ctr, a)
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, container_type, size_t, Alloc))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const container_type& ctr, const mapping_type& map, const Alloc& a)
    : map_(map), ctr_(ctr, a)
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, container_type, container_type, Alloc) &&
                    _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(container_type&& ctr, const extents_type& exts, const Alloc& a)
    : map_(exts), ctr_(std::move(ctr), a)
  { assert(ctr_.size() >= static_cast<size_t>(map_.required_span_size())); }

  MDSPAN_TEMPLATE_REQUIRES(
    class Alloc,
    /* requires */ (_MDSPAN_TRAIT(is_constructible, container_type, size_t, Alloc))
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(container_type&& ctr, const mapping_type& map, const Alloc& a)
    : map_(map), ctr_(std::move(ctr), a)
  { assert(ctr_.size() >= map_.required_span_size()); }

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherContainer, class Alloc,
    /* requires */ (
      _MDSPAN_TRAIT(is_constructible, mapping_type, typename OtherLayoutPolicy::template mapping<OtherExtents>) &&
      _MDSPAN_TRAIT(is_constructible, container_type, OtherContainer, Alloc)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdarray(const mdarray<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherContainer>& other, const Alloc& a)
    : map_(other.mapping()), ctr_(other.container(), a)
  {
    static_assert(is_constructible<extents_type, OtherExtents>::value, "");
  }

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray& operator= (const mdarray&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdarray& operator= (mdarray&&) = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~mdarray() = default;

  //--------------------------------------------------------------------------------
  // [mdspan.basic.mapping], mdspan mapping domain multidimensional index to access codomain element

  #if MDSPAN_USE_BRACKET_OPERATOR
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator[](SizeTypes... indices) const noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](SizeTypes... indices) noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }
  #endif

#if 0
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator[](const array<SizeType, N>& indices) const noexcept
  {
    return __impl::template __callop<reference>(*this, indices);
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](const array<SizeType, N>& indices) noexcept
  {
    return __impl::template __callop<reference>(*this, indices);
  }
#endif


  #if MDSPAN_USE_PAREN_OPERATOR
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator()(SizeTypes... indices) const noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }
  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, index_type) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(SizeTypes... indices) noexcept
  {
    return ctr_[map_(static_cast<index_type>(std::move(indices))...)];
  }

#if 0
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr const_reference operator()(const array<SizeType, N>& indices) const noexcept
  {
    return __impl::template __callop<reference>(*this, indices);
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, index_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(const array<SizeType, N>& indices) noexcept
  {
    return __impl::template __callop<reference>(*this, indices);
  }
#endif
  #endif

  MDSPAN_INLINE_FUNCTION constexpr pointer data() noexcept { return ctr_.data(); };
  MDSPAN_INLINE_FUNCTION constexpr const_pointer data() const noexcept { return ctr_.data(); };
  MDSPAN_INLINE_FUNCTION constexpr container_type& container() noexcept { return ctr_; };
  MDSPAN_INLINE_FUNCTION constexpr const container_type& container() const noexcept { return ctr_; };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.domobs], mdspan observers of the domain multidimensional index space

  MDSPAN_INLINE_FUNCTION static constexpr rank_type rank() noexcept { return extents_type::rank(); }
  MDSPAN_INLINE_FUNCTION static constexpr rank_type rank_dynamic() noexcept { return extents_type::rank_dynamic(); }
  MDSPAN_INLINE_FUNCTION static constexpr size_t static_extent(size_t r) noexcept { return extents_type::static_extent(r); }

  MDSPAN_INLINE_FUNCTION constexpr extents_type extents() const noexcept { return map_.extents(); };
  MDSPAN_INLINE_FUNCTION constexpr index_type extent(size_t r) const noexcept { return map_.extents().extent(r); };
  MDSPAN_INLINE_FUNCTION constexpr index_type size() const noexcept {
//    return __impl::__size(*this);
    return ctr_.size();
  };


  //--------------------------------------------------------------------------------
  // [mdspan.basic.obs], mdspan observers of the mapping

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_exhaustive() noexcept { return mapping_type::is_always_exhaustive(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return mapping_type::is_always_strided(); };

  MDSPAN_INLINE_FUNCTION constexpr mapping_type mapping() const noexcept { return map_; };
  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return map_.is_unique(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_exhaustive() const noexcept { return map_.is_exhaustive(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return map_.is_strided(); };
  MDSPAN_INLINE_FUNCTION constexpr index_type stride(size_t r) const { return map_.stride(r); };

private:
  mapping_type map_;
  container_type ctr_;

  template <class, class, class, class>
  friend class mdarray;
};


} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p1684_bits/mdarray.hpp

//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/mdarray
#endif // _MDSPAN_SINGLE_HEADER_INCLUDE_GUARD_

