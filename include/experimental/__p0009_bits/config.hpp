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

#ifndef _MDSPAN_INCLUDE_EXPERIMENTAL_BITS_CONFIG_HPP_
#define _MDSPAN_INCLUDE_EXPERIMENTAL_BITS_CONFIG_HPP_

#ifndef __has_include
#  define __has_include(x) 0
#endif

#if __has_include(<version>)
#  include <version>
#else
#  include <type_traits>
#  include <utility>
#endif

#ifdef _MSVC_LANG
#define _MDSPAN_CPLUSPLUS _MSVC_LANG
#else
#define _MDSPAN_CPLUSPLUS __cplusplus
#endif

static_assert(_MDSPAN_CPLUSPLUS >= 201102L, "MDSpan requires C++11 or later.");

#define MDSPAN_CXX_STD_14 201402L
#define MDSPAN_CXX_STD_17 201703L

#define MDSPAN_HAS_CXX_14 (_MDSPAN_CPLUSPLUS >= MDSPAN_CXX_STD_14)
#define MDSPAN_HAS_CXX_17 (_MDSPAN_CPLUSPLUS >= MDSPAN_CXX_STD_17)

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

#ifndef __has_cpp_attribute
#  define __has_cpp_attribute(x) 0
#endif

#ifndef _MDSPAN_PRESERVE_STANDARD_LAYOUT
// Preserve standard layout by default, but we're not removing the old version
// that turns this off until we're sure this doesn't have an unreasonable cost
// to the compiler or optimizer.
#  define _MDSPAN_PRESERVE_STANDARD_LAYOUT 1
#endif

#ifndef _MDSPAN_NO_UNIQUE_ADDRESS
#  if __has_cpp_attribute(no_unique_address) >= 201803L
#    define _MDSPAN_NO_UNIQUE_ADDRESS [[no_unique_address]]
#  else
#    define _MDSPAN_NO_UNIQUE_ADDRESS
#  endif
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
#  if (defined(__cpp_variable_templates) && __cpp_variable_templates >= 201304) \
        || (!defined(__cpp_variable_templates) && MDSPAN_HAS_CXX_14)
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
#  ifdef _MDSPAN_COMPILER_MSVC
#    if (defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304) && MDSPAN_HAS_CXX_14
#      define _MDSPAN_USE_RETURN_TYPE_DEDUCTION 1
#    endif
#  endif
#endif
#ifndef _MDSPAN_USE_RETURN_TYPE_DEDUCTION
#  if (defined(__cpp_return_type_deduction) && __cpp_return_type_deduction >= 201304) \
          || (!defined(__cpp_return_type_deduction) && MDSPAN_HAS_CXX_14)
#    define _MDSPAN_USE_RETURN_TYPE_DEDUCTION 1
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

#endif // _MDSPAN_INCLUDE_EXPERIMENTAL_BITS_CONFIG_HPP_
