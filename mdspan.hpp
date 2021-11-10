#ifndef _MDSPAN_SINGLE_HEADER_INCLUDE_GUARD_
#define _MDSPAN_SINGLE_HEADER_INCLUDE_GUARD_
#  include <version>
#  include <type_traits>
#  include <utility>
#include <type_traits> // std::is_void
#include <cstddef> // size_t
#include <cstddef>  // size_t
#include <limits>   // numeric_limits
#include <type_traits>
#include <utility> // integer_sequence
#include <array>
#include <utility> // integer_sequence
#include <cstddef>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <array>
#include <cstddef>
#include <cstddef>
#include <array>
#include <algorithm>
#include <numeric>
#include <array>
#include <tuple> // std::apply
#include <utility> // std::pair

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

#ifndef __has_cpp_attribute
#  define __has_cpp_attribute(x) 0
#endif

#ifndef _MDSPAN_PRESERVE_STANDARD_LAYOUT
// Preserve standard layout by default, but we're not removing the old version
// that turns this off until we're sure this doesn't have an unreasonable cost
// to the compiler or optimizer.
#  define _MDSPAN_PRESERVE_STANDARD_LAYOUT 1
#endif

#ifndef _MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS
#  if __has_cpp_attribute(no_unique_address) >= 201803L
#    define _MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS 1
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
#  if (defined(MDSPAN_HAS_CXX_20))
#    define MDSPAN_CONDITIONAL_EXPLICIT(COND) explicit(COND)
#  else
#    define MDSPAN_CONDITIONAL_EXPLICIT(COND)
#  endif
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

#if defined(_MDSPAN_COMPILER_MSVC) // Microsoft compilers

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

#else // Non-Microsoft compilers

# define MDSPAN_PP_COUNT(...) \
   _MDSPAN_PP_INTERNAL_COUNT_PRIVATE( \
     0, ## __VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61,  \
     60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, \
     45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, \
     30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, \
     15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) \
     /**/
# define _MDSPAN_PP_INTERNAL_COUNT_PRIVATE( \
    _0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, \
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
    _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, \
    _70, count, ...) count \
    /**/

#endif

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
  using pointer = ElementType*;

  MDSPAN_INLINE_FUNCTION
  constexpr default_accessor() noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, typename default_accessor<OtherElementType>::pointer, pointer)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr default_accessor(default_accessor<OtherElementType>) noexcept {}

  MDSPAN_INLINE_FUNCTION
  constexpr pointer
  offset(pointer p, size_t i) const noexcept {
    return p + i;
  }

  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference access(pointer p, size_t i) const noexcept {
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


//BEGIN_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/fixed_layout_impl.hpp
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

namespace detail {

template <class>
constexpr auto __make_dynamic_extent() {
  return dynamic_extent;
}

template <size_t>
constexpr auto __make_dynamic_extent_integral() {
  return dynamic_extent;
}

} // end namespace detail

} // end namespace experimental
} // namespace std

//==============================================================================================================
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/dynamic_extent.hpp
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
template <class _T, _T __v,
          _T __is_dynamic_sentinal = dynamic_extent,
          size_t __array_entry_index = 0>
struct __maybe_static_value {
  static constexpr _T __static_value = __v;
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __value() const noexcept {
    return __v;
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
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
  constexpr explicit __maybe_static_value(_T const&) noexcept {
    // Should we assert that the value matches the static value here?
  }

  //--------------------------------------------------------------------------

};

// dynamic case
template <class _T, _T __is_dynamic_sentinal, size_t __array_entry_index>
struct __maybe_static_value<_T, __is_dynamic_sentinal, __is_dynamic_sentinal,
                            __array_entry_index>
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __no_unique_address_emulation<_T>
#endif
{
  static constexpr _T __static_value = __is_dynamic_sentinal;
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS _T __v = {};
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __value() const noexcept {
    return __v;
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__ref() noexcept {
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
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __value() const noexcept {
    return this->__no_unique_address_emulation<_T>::__ref();
  }
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 _T &__ref() noexcept {
    return this->__no_unique_address_emulation<_T>::__ref();
  }
  template <class _U>
  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  __mdspan_enable_fold_comma
  __set_value(_U&& __rhs) noexcept {
    this->__no_unique_address_emulation<_T>::__ref() = (_U &&)__rhs;
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
    : private __no_unique_address_emulation<_T, 0>,
      private __no_unique_address_emulation<_U, 1>
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


namespace std {
namespace experimental {
namespace detail {

//==============================================================================

_MDSPAN_INLINE_VARIABLE constexpr struct
    __construct_partially_static_array_from_sizes_tag_t {
} __construct_partially_static_array_from_sizes_tag = {};

template <size_t _N = 0> struct __construct_psa_from_dynamic_values_tag_t {};

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
template <class _Tag, class _T, class _ValsSeq, _T __sentinal = dynamic_extent,
          class _IdxsSeq = make_index_sequence<_ValsSeq::size()>>
struct __standard_layout_psa;

//==============================================================================
// Static case
template <class _Tag, class _T, _T __value, _T... __values_or_sentinals,
          _T __sentinal, size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _Tag, _T, integer_sequence<_T, __value, __values_or_sentinals...>,
    __sentinal, integer_sequence<size_t, _Idx, _Idxs...>>
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : private __no_unique_address_emulation<__standard_layout_psa<
          _Tag, _T, integer_sequence<_T, __values_or_sentinals...>, __sentinal,
          integer_sequence<size_t, _Idxs...>>>
#endif
{

  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_Tag, _T,
                            integer_sequence<_T, __values_or_sentinals...>,
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
#ifdef _MDSPAN_COMPILER_MSVC
  // MSVC doesn't like the fact that __next_t happens to be a base
  // class that's private, even though __size_synamic is public in
  // it's definition.
  struct __msvc_workaround_tag {};
  using __msvc_workaround_next_t = __standard_layout_psa<
      __msvc_workaround_tag, _T,
      integer_sequence<_T, __values_or_sentinals...>, __sentinal,
      integer_sequence<size_t, _Idxs...>>;
  static constexpr auto __size_dynamic =
      __msvc_workaround_next_t::__size_dynamic;
#else
  static constexpr auto __size_dynamic = __next_t::__size_dynamic;
#endif

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
      __construct_partially_static_array_from_sizes_tag_t, _T const & /*__val*/,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __construct_partially_static_array_from_sizes_tag, __vals...
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
  { }

  // Dynamic idxs only given version, which is probably going to not need to
  // supported by the time mdspan is merged into the standard, but is currently
  // the way this is specified.  Use a repeated tag for the old semantics
  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t,
      _Ts const &... __vals) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __next_{
#else
      : __base_t(__base_t{__next_t(
#endif
          __construct_partially_static_array_from_sizes_tag,
          __construct_partially_static_array_from_sizes_tag, __vals...
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

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
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

  template <class _UTag, class _U, class _UValsSeq, _U __u_sentinal,
            class _IdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _UValsSeq, __u_sentinal, _IdxsSeq> const
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
  __set_n(_T const &__rhs) noexcept {
    // Don't assert here because that would break constexpr. This better
    // not change anything, though
  }
  template <size_t _I, enable_if_t<_I == _Idx, _T> = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __value;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __next_t::template __get_static_n<_I, __default>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value * (_T(_Idx == __n)) + __next().__get(__n);
  }

  //--------------------------------------------------------------------------
};

//==============================================================================

// Dynamic case, __next_t may or may not be empty
template <class _Tag, class _T, _T __sentinal, _T... __values_or_sentinals,
          size_t _Idx, size_t... _Idxs>
struct __standard_layout_psa<
    _Tag, _T, integer_sequence<_T, __sentinal, __values_or_sentinals...>,
    __sentinal, integer_sequence<size_t, _Idx, _Idxs...>> {
  //--------------------------------------------------------------------------

  using __next_t =
      __standard_layout_psa<_Tag, _T,
                            integer_sequence<_T, __values_or_sentinals...>,
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
      __construct_partially_static_array_from_sizes_tag_t, _T const &__val,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
      : __value_pair(__val,
                     __next_t(__construct_partially_static_array_from_sizes_tag,
                              __vals...)) {}

  // Dynamic idxs only given version, which is probably going to not need to
  // supported by the time mdspan is merged into the standard, but is currently
  // the way this is specified.  Use a repeated tag for the old semantics
  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t, _T const &__val,
      _Ts const &... __vals) noexcept
      : __value_pair(__val,
                     __next_t(__construct_partially_static_array_from_sizes_tag,
                              __construct_partially_static_array_from_sizes_tag,
                              __vals...)) {}

  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_U, _N> const &__vals) noexcept
      : __value_pair(::std::get<_Idx>(__vals), __vals) {}

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
      array<_U, _NDynamic> const &__vals) noexcept
      : __value_pair(
            ::std::get<_IDynamic>(__vals),
            __next_t(__construct_psa_from_dynamic_values_tag_t<_IDynamic + 1>{},
                     __vals)) {}

  template <class _UTag, class _U, class _UValsSeq, _U __u_sentinal,
            class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _UValsSeq, __u_sentinal, _UIdxsSeq> const
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
  template <size_t _I, enable_if_t<_I == _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __default;
  }
  template <size_t _I, enable_if_t<_I != _Idx, _T> __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T __get_static_n() noexcept {
    return __next_t::template __get_static_n<_I, __default>();
  }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr _T __get(size_t __n) const noexcept {
    return __value_pair.__first() * (_T(_Idx == __n)) + __next().__get(__n);
  }

  //--------------------------------------------------------------------------
};

// empty/terminal case
template <class _Tag, class _T, _T __sentinal>
struct __standard_layout_psa<_Tag, _T, integer_sequence<_T>, __sentinal,
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
      __construct_partially_static_array_from_sizes_tag_t) noexcept {}

  template <class... _Ts>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t) noexcept {}

  template <class _U, size_t _N>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      array<_U, _N> const &) noexcept {}

  template <class _U, size_t _IDynamic, size_t _NDynamic>
  MDSPAN_INLINE_FUNCTION constexpr explicit __standard_layout_psa(
      __construct_psa_from_dynamic_values_tag_t<_IDynamic> __tag,
      array<_U, _NDynamic> const &) noexcept {}

  template <class _UTag, class _U, class _UValsSeq, _U __u_sentinal,
            class _UIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __standard_layout_psa(
      __standard_layout_psa<_UTag, _U, _UValsSeq, __u_sentinal, _UIdxsSeq> const&) noexcept {}

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
template <class _Tag, size_t... __values_or_sentinals>
struct __partially_static_sizes_tagged
    : __standard_layout_psa<
          _Tag, size_t,
          integer_sequence<size_t, __values_or_sentinals...>> {
  using __tag_t = _Tag;
  using __psa_impl_t = __standard_layout_psa<
      _Tag, size_t, integer_sequence<size_t, __values_or_sentinals...>>;
  using __psa_impl_t::__psa_impl_t;
  MDSPAN_INLINE_FUNCTION
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
    __partially_static_sizes_tagged<_UTag, __values_or_sentinals...> const& __vals
  ) noexcept : __psa_impl_t(__vals.__enable_psa_conversion()) { }
};

struct __no_tag {};
template <size_t... __values_or_sentinals>
struct __partially_static_sizes
    : __partially_static_sizes_tagged<__no_tag, __values_or_sentinals...> {
private:
  using __base_t =
      __partially_static_sizes_tagged<__no_tag, __values_or_sentinals...>;
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes(
    __partially_static_sizes_tagged<_UTag, __values_or_sentinals...>&& __vals
  ) noexcept : __base_t(::std::move(__vals)) { }
public:
  using __base_t::__base_t;

#ifdef _MDSPAN_DEFAULTED_CONSTRUCTORS_INHERITANCE_WORKAROUND
  MDSPAN_INLINE_FUNCTION
  constexpr __partially_static_sizes() noexcept : __base_t() { }
#endif
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes_tagged<
      _UTag, __values_or_sentinals...>
  __with_tag() const noexcept {
    return __partially_static_sizes_tagged<_UTag, __values_or_sentinals...>(*this);
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

template <class _T, class _Vals, _T __sentinal,
          class _Idxs, class _IdxsDynamic, class _IdxsDynamicIdxs>
class __partially_static_array_impl;

template <
  class _T, _T... __values_or_sentinals, _T __sentinal,
  size_t... _Idxs,
  size_t... _IdxsDynamic,
  size_t... _IdxsDynamicIdxs
>
class __partially_static_array_impl<
  _T,
  integer_sequence<_T, __values_or_sentinals...>,
  __sentinal,
  integer_sequence<size_t, _Idxs...>,
  integer_sequence<size_t, _IdxsDynamic...>,
  integer_sequence<size_t, _IdxsDynamicIdxs...>
>
    : private __maybe_static_value<_T, __values_or_sentinals, __sentinal,
                                   _Idxs>... {
private:

  template <size_t _N>
  using __base_n = typename __type_at<_N,
    __type_list<__maybe_static_value<_T, __values_or_sentinals, __sentinal, _Idxs>...>
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
      __construct_partially_static_array_from_sizes_tag_t,
      __repeated_with_idxs<_Idxs, _T> const &... __vals) noexcept
      : __base_n<_Idxs>(__base_n<_Idxs>{{__vals}})... {}

  // Dynamic idxs only given version, which is probably going to not need to
  // supported by the time mdspan is merged into the standard, but is currently the
  // way this is specified.  Use a repeated tag for the old semantics
  MDSPAN_INLINE_FUNCTION
  constexpr __partially_static_array_impl(
      __construct_partially_static_array_from_sizes_tag_t,
      __construct_partially_static_array_from_sizes_tag_t,
      __repeated_with_idxs<_IdxsDynamicIdxs, _T> const &... __vals) noexcept
      : __base_n<_IdxsDynamic>(__base_n<_IdxsDynamic>{{__vals}})... {}

  MDSPAN_INLINE_FUNCTION constexpr explicit __partially_static_array_impl(
    array<_T, sizeof...(_Idxs)> const& __vals) noexcept
    : __partially_static_array_impl(
        __construct_partially_static_array_from_sizes_tag,
        ::std::get<_Idxs>(__vals)...) {}

  // clang-format off
  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr explicit),
    __partially_static_array_impl,
    (array<_T, __size_dynamic> const &__vals), noexcept,
    /* requires */
      (sizeof...(_Idxs) != __size_dynamic)
  ): __partially_static_array_impl(
       __construct_partially_static_array_from_sizes_tag,
       __construct_partially_static_array_from_sizes_tag,
       ::std::get<_IdxsDynamicIdxs>(__vals)...) {}
  // clang-format on

  template <class _U, class _UValsSeq, _U __u_sentinal, class _UIdxsSeq,
            class _UIdxsDynamicSeq, class _UIdxsDynamicIdxsSeq>
  MDSPAN_INLINE_FUNCTION constexpr __partially_static_array_impl(
    __partially_static_array_impl<
      _U, _UValsSeq, __u_sentinal, _UIdxsSeq,
     _UIdxsDynamicSeq, _UIdxsDynamicIdxsSeq> const &__rhs) noexcept
    : __partially_static_array_impl(
        __construct_partially_static_array_from_sizes_tag,
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

  template <size_t _I, _T __default = __sentinal>
  MDSPAN_FORCE_INLINE_FUNCTION static constexpr _T
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

template <class _T, class _ValSeq, _T __sentinal, class _Idxs = make_index_sequence<_ValSeq::size()>>
struct __partially_static_array_impl_maker;

template <
  class _T, _T... _Vals, _T __sentinal, size_t... _Idxs
>
struct __partially_static_array_impl_maker<
  _T, integer_sequence<_T, _Vals...>, __sentinal, integer_sequence<size_t, _Idxs...>
>
{
  using __dynamic_idxs = typename __mask_sequence<
    integer_sequence<size_t, _Idxs...>,
    integer_sequence<bool, (_Vals == __sentinal)...>
  >::type;
  using __impl_base =
    __partially_static_array_impl<_T,
      integer_sequence<_T, _Vals...>,
      __sentinal, integer_sequence<size_t, _Idxs...>,
      __dynamic_idxs,
      make_index_sequence<__dynamic_idxs::size()>
    >;
};

template <class _T, class _ValsSeq, _T __sentinal = dynamic_extent>
class __partially_static_array_with_sentinal
  : public __partially_static_array_impl_maker<_T, _ValsSeq, __sentinal>::__impl_base
{
private:
  using __base_t = typename __partially_static_array_impl_maker<_T, _ValsSeq, __sentinal>::__impl_base;
public:
  using __base_t::__base_t;
};

//==============================================================================

template <size_t... __values_or_sentinals>
struct __partially_static_sizes :
  __partially_static_array_with_sentinal<
    size_t, ::std::integer_sequence<size_t, __values_or_sentinals...>>
{
private:
  using __base_t = __partially_static_array_with_sentinal<
    size_t, ::std::integer_sequence<size_t, __values_or_sentinals...>>;
public:
  using __base_t::__base_t;
  template <class _UTag>
  MDSPAN_FORCE_INLINE_FUNCTION constexpr __partially_static_sizes<__values_or_sentinals...>
  __with_tag() const noexcept {
    return *this;
  }
};

// Tags are needed for the standard layout version, but not here
template <class, size_t... __values_or_sentinals>
using __partially_static_sizes_tagged = __partially_static_sizes<__values_or_sentinals...>;

} // end namespace detail
} // end namespace experimental
} // end namespace std

#endif // !_MDSPAN_PRESERVE_STANDARD_LAYOUT
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/static_array.hpp
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



#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#endif


namespace std {
namespace experimental {

namespace detail {

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

template <size_t... Extents>
class extents
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  : private detail::__no_unique_address_emulation<
      detail::__partially_static_sizes_tagged<detail::__extents_tag, Extents...>>
#endif
{
public:

  using size_type = size_t;

  using __storage_t = detail::__partially_static_sizes_tagged<detail::__extents_tag, Extents...>;

#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS __storage_t __storage_;
#else
  using __base_t = detail::__no_unique_address_emulation<__storage_t>;
#endif

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
  size_type _static_extent_impl(size_t n, std::integer_sequence<size_t, Idxs...>) noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT(((Idxs == n) ? Extents : 0), /* + ... + */ 0);
  }

  template <size_t...>
  friend class extents;

  template <size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(std::experimental::extents<OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return false; }
  template <size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _eq_impl(
    std::experimental::extents<OtherExtents...> other,
    true_type, index_sequence<Idxs...>
  ) const noexcept {
    return _MDSPAN_FOLD_AND(
      (__storage().template __get_n<Idxs>() == other.__storage().template __get_n<Idxs>()) /* && ... */
    );
  }

  template <size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(std::experimental::extents<OtherExtents...>, false_type, index_sequence<Idxs...>) const noexcept { return true; }
  template <size_t... OtherExtents, size_t... Idxs>
  MDSPAN_INLINE_FUNCTION
  constexpr bool _not_eq_impl(
    std::experimental::extents<OtherExtents...> other,
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

public:

  MDSPAN_INLINE_FUNCTION
  static constexpr size_t rank() noexcept { return sizeof...(Extents); }
  MDSPAN_INLINE_FUNCTION
  static constexpr size_t rank_dynamic() noexcept { return _MDSPAN_FOLD_PLUS_RIGHT((int(Extents == dynamic_extent)), /* + ... + */ 0); }

  //--------------------------------------------------------------------------------
  // Constructors, Destructors, and Assignment

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr extents(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED extents& operator=(extents const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED extents& operator=(extents&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~extents() noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    size_t... OtherExtents,
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
  MDSPAN_CONDITIONAL_EXPLICIT((((Extents != dynamic_extent) && (OtherExtents == dynamic_extent)) || ...))
  constexpr extents(const extents<OtherExtents...>& __other)
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
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class... Integral,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, Integral, size_type) /* && ... */)
        && sizeof...(Integral) == rank_dynamic()
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr extents(Integral... dyn) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __storage_{
#else
    : __base_t(__base_t{typename __base_t::__stored_type{
#endif
        detail::__construct_partially_static_array_from_sizes_tag,
        detail::__construct_partially_static_array_from_sizes_tag, static_cast<size_t>(dyn)...
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      }})
#endif
  { }


  // TODO @proposal-bug this constructor should be explicit
  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, size_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr
  extents(std::array<SizeType, rank_dynamic()> const& dyn) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __storage_{
#else
    : __base_t(__base_t{typename __base_t::__stored_type{
#endif
        detail::__construct_psa_from_dynamic_values_tag_t<>{}, dyn
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      }})
#endif
  { }

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

  MDSPAN_TEMPLATE_REQUIRES(
    size_t... OtherExtents,
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
  _MDSPAN_CONSTEXPR_14 extents& operator=(const extents<OtherExtents...>& other) noexcept
  {
    __storage() = other.__storage().__enable_psa_conversion();
    return *this;
  }

  //--------------------------------------------------------------------------------

  MDSPAN_INLINE_FUNCTION
  static constexpr
  size_type static_extent(size_t n) noexcept {
    return _static_extent_impl(n, std::make_integer_sequence<size_t, sizeof...(Extents)>{});
  }

  MDSPAN_INLINE_FUNCTION
  constexpr
  size_type extent(size_t n) const noexcept {
    return __storage().__get(n);
  }

  //--------------------------------------------------------------------------------

  template<size_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator==(extents const& lhs, extents<RHS...> const& rhs) noexcept {
    return lhs._eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(RHS) == rank())>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }

  template<size_t... RHS>
  MDSPAN_INLINE_FUNCTION
  friend constexpr bool operator!=(extents const& lhs, extents<RHS...> const& rhs) noexcept {
    return lhs._not_eq_impl(
      rhs, std::integral_constant<bool, (sizeof...(RHS) == rank())>{},
      make_index_sequence<sizeof...(RHS)>{}
    );
  }

public:  // (but not really)

  MDSPAN_INLINE_FUNCTION static constexpr
  extents __make_extents_impl(detail::__partially_static_sizes<Extents...>&& __bs) noexcept {
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
  size_type __extent() const noexcept {
    return __storage().template __get_n<N>();
  }

  template <size_t N, size_t Default=dynamic_extent>
  MDSPAN_INLINE_FUNCTION
  static constexpr
  size_type __static_extent() noexcept {
    return __storage_t::template __get_static_n<N, Default>();
  }

};

namespace detail {

template <size_t Rank, class Extents = ::std::experimental::extents<>>
struct __make_dextents;

template <size_t Rank, size_t... ExtentsPack>
struct __make_dextents<Rank, ::std::experimental::extents<ExtentsPack...>> {
  using type = typename __make_dextents<Rank - 1,
    ::std::experimental::extents<::std::experimental::dynamic_extent, ExtentsPack...>>::type;
};

template <size_t... ExtentsPack>
struct __make_dextents<0, ::std::experimental::extents<ExtentsPack...>> {
  using type = ::std::experimental::extents<ExtentsPack...>;
};

} // end namespace detail

template <size_t Rank>
using dextents = typename detail::__make_dextents<Rank>::type;

#if defined(_MDSPAN_USE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION)
template <class... SizeTypes>
extents(SizeTypes...)
  -> extents<detail::__make_dynamic_extent<SizeTypes>()...>;
#endif

namespace detail {

template <class T>
struct __is_extents : ::std::false_type {};

template <size_t... ExtentsPack>
struct __is_extents<::std::experimental::extents<ExtentsPack...>> : ::std::true_type {};

template <class T>
static constexpr bool __is_extents_v = __is_extents<T>::value;


template <typename Extents>
struct __extents_to_partially_static_sizes;

template <size_t... ExtentsPack>
struct __extents_to_partially_static_sizes<::std::experimental::extents<ExtentsPack...>> {
  using type = detail::__partially_static_sizes<ExtentsPack...>;
};

template <typename Extents>
using __extents_to_partially_static_sizes_t = typename __extents_to_partially_static_sizes<Extents>::type;

} // end namespace detail
} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/extents.hpp

#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
#endif


//==============================================================================================================

namespace std {
namespace experimental {
namespace detail {

//==============================================================================================================

template <class, class, class> struct __extents_storage_impl;

template <size_t... Exts, size_t... Idxs, class IdxConditional>
struct __extents_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  : __no_unique_address_emulation<experimental::extents<Exts...>>
#endif
{
protected:

#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
  _MDSPAN_NO_UNIQUE_ADDRESS experimental::extents<Exts...> __extents_;
#else
  using __base_t = __no_unique_address_emulation<experimental::extents<Exts...>>;
#endif

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
  experimental::extents<Exts...>& __extents() noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __extents_;
#else
    return this->__base_t::__ref();
#endif
  }
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr experimental::extents<Exts...> const& __extents() const noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    return __extents_;
#else
    return this->__base_t::__ref();
#endif
  }

public:

  using extents_type = experimental::extents<Exts...>;

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __extents_storage_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __extents_storage_impl(__extents_storage_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr __extents_storage_impl(__extents_storage_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED __extents_storage_impl& operator=(__extents_storage_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED __extents_storage_impl& operator=(__extents_storage_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~__extents_storage_impl() noexcept = default;

  // The layouts need to be implicitly convertible from extents (as currently specified),
  // which means we need to make this not explicit here
  // TODO @proposal-bug make this explicit?
  MDSPAN_INLINE_FUNCTION
  constexpr /* implicit */ __extents_storage_impl(extents_type const& __exts) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __extents_{
#else
    : __base_t(__base_t{
#endif
        __exts
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      })
#endif
  { }
  template<std::size_t ... OtherExts>
  MDSPAN_INLINE_FUNCTION
  constexpr /* implicit */ __extents_storage_impl(experimental::extents<OtherExts...> const& __exts) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : __extents_{
#else
    : __base_t(__base_t{
#endif
    // Need to convert extents here potentially explicit
        extents_type(__exts)
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      }
#else
      })
#endif
  { }

  // The layouts need to be implicitly convertible from extents (as currently specified),
  // which means we need to make this not explicit here
  // TODO @proposal-bug this one isn't in the proposal?
//  MDSPAN_INLINE_FUNCTION
//  constexpr /* implicit */ __extents_storage_impl(extents_type&& __exts) noexcept
//#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
//    : __extents_{
//#else
//    : __base_t(__base_t{
//#endif
//        std::move(__exts)
//#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
//      }
//#else
//      })
//#endif
//  { }

  template <size_t N>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr size_t get_stride() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, N) ? __extents().template __extent<Idxs>() : 1),
        /* * ... * */ 1
    );
  }

  MDSPAN_INLINE_FUNCTION
  constexpr size_t get_stride(size_t n) const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, n) ? __extents().template __extent<Idxs>() : 1),
        /* * ... * */ 1
    );
  }

};

//==============================================================================================================

template <class, class, class>
class fixed_layout_common_impl;

// TODO: We can probably make `__extents_storage_impl` a [[no_unique_address]]
// member instead of a base class.
template <size_t... Exts, size_t... Idxs, class IdxConditional>
class fixed_layout_common_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
  : protected __extents_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>
{
private:

  using base_t = __extents_storage_impl<std::experimental::extents<Exts...>, integer_sequence<size_t, Idxs...>, IdxConditional>;

public:

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl(fixed_layout_common_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr fixed_layout_common_impl(fixed_layout_common_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED fixed_layout_common_impl& operator=(fixed_layout_common_impl const&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED fixed_layout_common_impl& operator=(fixed_layout_common_impl&&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED ~fixed_layout_common_impl() noexcept = default;

  using base_t::base_t;

  MDSPAN_INLINE_FUNCTION constexpr typename base_t::extents_type extents() const noexcept {
    return typename base_t::extents_type(this->base_t::__extents());
  };

  template <class... Integral>
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr size_t operator()(Integral... idxs) const noexcept {
    return _MDSPAN_FOLD_PLUS_RIGHT((idxs * this->base_t::template get_stride<Idxs>()), /* + ... + */ 0);
  }

  MDSPAN_INLINE_FUNCTION
  constexpr size_t required_span_size() const noexcept {
    return _MDSPAN_FOLD_TIMES_RIGHT((base_t::__extents().template __extent<Idxs>()), /* * ... * */ 1);
  }

  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return true; }
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

  MDSPAN_INLINE_FUNCTION
  constexpr size_t stride(size_t r) const noexcept {
    return this->base_t::get_stride(r);
  }

  //--------------------------------------------------------------------------------

public:  // (but not really)

  template <size_t R>
  MDSPAN_INLINE_FUNCTION
  constexpr size_t __stride() const noexcept {
    return this->base_t::template get_stride<R>();
  }

  template <size_t N>
  struct __static_stride_workaround {
    static constexpr size_t __result = _MDSPAN_FOLD_TIMES_RIGHT(
      (IdxConditional{}(Idxs, N) ?
        base_t::__stored_type::template __static_extent<Idxs, 0>() : 1
      ), /* * ... * */ 1
    );
    static constexpr size_t value = __result == 0 ? dynamic_extent : __result;
  };

  template <size_t N>
  MDSPAN_INLINE_FUNCTION
  static constexpr size_t __static_stride() noexcept
  {
    return __static_stride_workaround<N>::value;
  }

};

//==============================================================================================================

} // namespace detail

} // end namespace experimental
} // namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/fixed_layout_impl.hpp

namespace std {
namespace experimental {

//==============================================================================

namespace detail {

struct layout_right_idx_conditional {
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr layout_right_idx_conditional() noexcept = default;
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr bool operator()(size_t Idx, size_t N) const noexcept {
    return Idx > N;
  };
};

} // end namespace detail

struct layout_right {
  template <class Extents>
  class mapping
    : public detail::fixed_layout_common_impl<Extents, make_index_sequence<Extents::rank()>, detail::layout_right_idx_conditional>
  {
  private:

    static_assert(detail::__is_extents_v<Extents>, "std::experimental::layout_left::mapping must be instantiated with a specialization of std::experimental::extents.");

    using base_t = detail::fixed_layout_common_impl<Extents, make_index_sequence<Extents::rank()>, detail::layout_right_idx_conditional>;

    template <class>
    friend class mapping;

  public:

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED ~mapping() noexcept = default;

    using base_t::base_t;

    // TODO @proposal-bug This isn't a requirement of layouts in the proposal,
    // but we need it for `mdspan`'s deduction guides for its mapping
    // constructors.
    using layout = layout_right;

    // TODO @proposal-bug This isn't a requirement in the proposal.
    using typename base_t::extents_type;

    // This has to be here for CTAD; just inheriting the base class constructor
    // isn't sufficient.
    constexpr mapping(Extents const& __exts) noexcept
      : base_t(__exts)
    { }

    // TODO noexcept specification
    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, OtherExtents, Extents)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((!is_convertible<OtherExtents, Extents>::value)) // needs to () due to ,
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(mapping<OtherExtents> const& other) // NOLINT(google-explicit-constructor)
      : base_t(other.extents())
    { }

    // TODO noexcept specification
    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
        /* requires */ (
        _MDSPAN_TRAIT(is_assignable, OtherExtents, Extents)
      )
    )
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping& operator=(mapping<OtherExtents> const& other)
    {
      this->base_t::__extents() = other.extents();
      return *this;
    }
    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    // TODO @proposal-bug these (and other analogous operators) should be non-member functions
    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() == rhs.extents();
    }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() != rhs.extents();
    }

  };
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
      return _MDSPAN_FOLD_TIMES_RIGHT((__self.__mapping_ref().extents().template __extent<Idxs>()), /* * ... * */ 1);
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
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = typename accessor_type::pointer;
  using reference = typename accessor_type::reference;

private:

  // Can't use defaulted parameter in the __deduction_workaround template because of a bug in MSVC warning C4348.
  using __impl = __deduction_workaround<make_index_sequence<extents_type::rank()>>;

  using __map_acc_pair_t = detail::__compressed_pair<mapping_type, accessor_type>;

public:

  //--------------------------------------------------------------------------------
  // [mdspan.basic.cons], mdspan constructors, assignment, and destructor

  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdspan() noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdspan(const mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mdspan(mdspan&&) noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, size_type) /* && ... */) &&
      (sizeof...(SizeTypes) == extents_type::rank_dynamic()) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  explicit constexpr mdspan(pointer p, SizeTypes... dynamic_extents)
    noexcept
    // TODO @proposal-bug shouldn't I be allowed to do `move(p)` here?
    : __members(p, __map_acc_pair_t(mapping_type(extents_type(dynamic_extents...)), accessor_type()))
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, size_type) &&
      (N == extents_type::rank_dynamic()) &&
      _MDSPAN_TRAIT(is_constructible, mapping_type, extents_type) &&
      _MDSPAN_TRAIT(is_default_constructible, accessor_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(pointer p, const array<SizeType, N>& dynamic_extents)
    noexcept
    : __members(p, __map_acc_pair_t(mapping_type(extents_type(dynamic_extents)), accessor_type()))
  { }

  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(pointer p, const extents_type& exts)
    noexcept
    : __members(p, __map_acc_pair_t(mapping_type(exts), accessor_type()))
  { }

  MDSPAN_FUNCTION_REQUIRES(
    (MDSPAN_INLINE_FUNCTION constexpr),
    mdspan, (pointer p, const mapping_type& m), noexcept,
    /* requires */ (_MDSPAN_TRAIT(is_default_constructible, accessor_type))
  ) : __members(p, __map_acc_pair_t(m, accessor_type()))
  { }

  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(pointer p, const mapping_type& m, const accessor_type& a) noexcept
    : __members(p, __map_acc_pair_t(m, a))
  { }

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherAccessor,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, typename OtherLayoutPolicy::template mapping<OtherExtents>, mapping_type) &&
      _MDSPAN_TRAIT(is_convertible, OtherAccessor, accessor_type) &&
      _MDSPAN_TRAIT(is_convertible, typename OtherAccessor::pointer, pointer) &&
      // TODO @proposal-bug there is a redundant constraint in the proposal; the convertibility of the extents is effectively stated twice
      _MDSPAN_TRAIT(is_convertible, OtherExtents, extents_type)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr mdspan(const mdspan<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>& other)
    : __members(other.__ptr_ref(), __map_acc_pair_t(other.__mapping_ref(), other.__accessor_ref()))
  { }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  ~mdspan() noexcept = default;

  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mdspan& operator=(const mdspan&) noexcept = default;
  MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mdspan& operator=(mdspan&&) noexcept = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherElementType, size_t... OtherExtents, class OtherLayoutPolicy, class OtherAccessorPolicy,
    /* requires */ (
      _MDSPAN_TRAIT(is_assignable, mapping_type, typename OtherLayoutPolicy::template mapping<std::experimental::extents<OtherExtents...>>) &&
      _MDSPAN_TRAIT(is_assignable, accessor_type, OtherAccessorPolicy) &&
      _MDSPAN_TRAIT(is_assignable, pointer, typename OtherAccessorPolicy::pointer) &&
      sizeof...(OtherExtents) == extents_type::rank() &&
      // "For all r in the range [0, rank()), if other.static_extent(r) != dynamic_extent
      //   && static_extent(r) != dynamic_extent is true, then
      //   other.static_extent(r) == static_extent(r) is true."
      // (this is just the convertiblity constraint on extents...)
      _MDSPAN_TRAIT(is_convertible, extents_type, std::experimental::extents<OtherExtents...>)
    )
  )
  MDSPAN_INLINE_FUNCTION
  _MDSPAN_CONSTEXPR_14 mdspan& operator=(
    const mdspan<OtherElementType, std::experimental::extents<OtherExtents...>, OtherLayoutPolicy, OtherAccessorPolicy>& other
  ) noexcept(/* TODO noexcept specification */ true)
  {
    __ptr_ref() = other.__ptr_ref();
    __mapping_ref() = other.__mapping_ref();
    __accessor_ref() = other.__accessor_ref();
    return *this;
  }

  //--------------------------------------------------------------------------------
  // [mdspan.basic.mapping], mdspan mapping domain multidimensional index to access codomain element

  MDSPAN_TEMPLATE_REQUIRES(
    class Index,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, Index, size_type) &&
      extents_type::rank() == 1
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator[](Index idx) const noexcept
  {
    return __accessor_ref().access(__ptr_ref(), __mapping_ref()(size_type(idx)));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class... SizeTypes,
    /* requires */ (
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, SizeTypes, size_type) /* && ... */) &&
      extents_type::rank() == sizeof...(SizeTypes)
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(SizeTypes... indices) const noexcept
  {
    return __accessor_ref().access(__ptr_ref(), __mapping_ref()(size_type(indices)...));
  }

  MDSPAN_TEMPLATE_REQUIRES(
    class SizeType, size_t N,
    /* requires */ (
      _MDSPAN_TRAIT(is_convertible, SizeType, size_type) &&
      N == extents_type::rank()
    )
  )
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference operator()(const array<SizeType, N>& indices) const noexcept
  {
    return __impl::template __callop<reference>(*this, indices);
  }

  // TODO @proposal-bug The proposal is missing constexpr here
  MDSPAN_INLINE_FUNCTION constexpr
  accessor_type accessor() const { return __accessor_ref(); };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.domobs], mdspan observers of the domain multidimensional index space

  MDSPAN_INLINE_FUNCTION static constexpr int rank() noexcept { return extents_type::rank(); }
  MDSPAN_INLINE_FUNCTION static constexpr int rank_dynamic() noexcept { return extents_type::rank_dynamic(); }
  MDSPAN_INLINE_FUNCTION static constexpr size_type static_extent(size_t r) noexcept { return extents_type::static_extent(r); }

  MDSPAN_INLINE_FUNCTION constexpr extents_type extents() const noexcept { return __mapping_ref().extents(); };
  MDSPAN_INLINE_FUNCTION constexpr size_type extent(size_t r) const noexcept { return __mapping_ref().extents().extent(r); };
  MDSPAN_INLINE_FUNCTION constexpr size_type size() const noexcept {
    return __impl::__size(*this);
  };

  // TODO @proposal-bug for non-unique, non-contiguous mappings this is unimplementable
  MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 size_type unique_size() const noexcept {
    if(__mapping_ref().is_unique()) {
      return size();
    }
    else if(__mapping_ref().is_contiguous()) {
      return __mapping_ref().required_span_size();
    }
    else {
      // ??? guess, for now, until this gets fixed in the proposal ???
      return __mapping_ref().required_span_size();
    }
  }

  // [mdspan.basic.codomain], mdspan observers of the codomain
  // TODO span (or just `codomain` function, as discussed)
  // constexpr span<element_type> span() const noexcept;

  MDSPAN_INLINE_FUNCTION constexpr pointer data() const noexcept { return __ptr_ref(); };

  //--------------------------------------------------------------------------------
  // [mdspan.basic.obs], mdspan observers of the mapping

  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return mapping_type::is_always_unique(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return mapping_type::is_always_contiguous(); };
  MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return mapping_type::is_always_strided(); };

  MDSPAN_INLINE_FUNCTION constexpr mapping_type mapping() const noexcept { return __mapping_ref(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return __mapping_ref().is_unique(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_contiguous() const noexcept { return __mapping_ref().is_contiguous(); };
  MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return __mapping_ref().is_strided(); };
  MDSPAN_INLINE_FUNCTION constexpr size_type stride(size_t r) const { return __mapping_ref().stride(r); };

private:

  detail::__compressed_pair<pointer, __map_acc_pair_t> __members{};

  MDSPAN_FORCE_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 pointer& __ptr_ref() noexcept { return __members.__first(); }
  MDSPAN_FORCE_INLINE_FUNCTION constexpr pointer const& __ptr_ref() const noexcept { return __members.__first(); }
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
  /* requires */ _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_integral, SizeTypes) /* && ... */)
)
explicit mdspan(ElementType*, SizeTypes...)
  -> mdspan<ElementType, ::std::experimental::dextents<sizeof...(SizeTypes)>>;

template <class ElementType, class SizeType, size_t N>
explicit mdspan(ElementType*, const ::std::array<SizeType, N>&)
  -> mdspan<ElementType, ::std::experimental::dextents<N>>;

// This one is necessary because all the constructors take `pointer`s, not
// `ElementType*`s, and `pointer` is taken from `accessor_type::pointer`, which
// seems to throw off automatic deduction guides.
template <class ElementType, size_t... ExtentsPack>
explicit mdspan(ElementType*, const extents<ExtentsPack...>&)
  -> mdspan<ElementType, ::std::experimental::extents<ExtentsPack...>>;

// TODO @proposal-bug Layout mappings in the proposal are not required to have `extents_type`.
template <class ElementType, class MappingType>
mdspan(ElementType*, const MappingType&)
  -> mdspan<ElementType, typename MappingType::extents_type, typename MappingType::layout>;

// TODO @proposal-bug Layout mappings in the proposal are not required to have `extents_type`.
template <class ElementType, class MappingType, class AccessorType>
mdspan(ElementType*, const MappingType&, const AccessorType&)
  -> mdspan<ElementType, typename MappingType::extents_type, typename MappingType::layout, AccessorType>;
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

namespace detail {

struct layout_left_idx_conditional {
  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr layout_left_idx_conditional() noexcept = default;
  MDSPAN_FORCE_INLINE_FUNCTION
  constexpr bool operator()(size_t Idx, size_t N) const noexcept {
    return Idx < N;
  };
};

} // end namespace detail

struct layout_left {
  template <class Extents>
  class mapping
    : public detail::fixed_layout_common_impl<Extents, make_index_sequence<Extents::rank()>, detail::layout_left_idx_conditional>
  {
  private:

    static_assert(detail::__is_extents_v<Extents>, "std::experimental::layout_left::mapping must be instantiated with a specialization of std::experimental::extents.");

    using base_t = detail::fixed_layout_common_impl<Extents, make_index_sequence<Extents::rank()>, detail::layout_left_idx_conditional>;

    template <class>
    friend class mapping;

  public:

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED mapping& operator=(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED ~mapping() noexcept = default;

    using base_t::base_t;

    // TODO @proposal-bug This isn't a requirement of layouts in the proposal,
    // but we need it for `mdspan`'s deduction guides for its mapping
    // constructors.
    using layout = layout_left;

    // TODO @proposal-bug This isn't a requirement in the proposal.
    using typename base_t::extents_type;

    // This has to be here for CTAD; just inheriting the base class constructor
    // isn't sufficient.
    constexpr mapping(Extents const& __exts) noexcept
      : base_t(__exts)
    { }

    // TODO noexcept specification
    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_constructible, OtherExtents, Extents)
      )
    )
    MDSPAN_CONDITIONAL_EXPLICIT((!is_convertible<OtherExtents, Extents>::value)) // needs two () due to comma
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping(mapping<OtherExtents> const& other) // NOLINT(google-explicit-constructor)
      : base_t(other.extents())
    { }

    // TODO noexcept specification
    MDSPAN_TEMPLATE_REQUIRES(
      class OtherExtents,
      /* requires */ (
        _MDSPAN_TRAIT(is_assignable, OtherExtents, Extents)
      )
    )
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14
    mapping& operator=(mapping<OtherExtents> const& other)
    {
      this->base_t::__extents() = other.extents();
      return *this;
    }
    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() == rhs.extents();
    }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return lhs.extents() != rhs.extents();
    }

  };
};

} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_left.hpp
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


namespace std {
namespace experimental {

struct layout_stride {
  template <class Extents>
  class mapping
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
    : private detail::__no_unique_address_emulation<
        detail::__compressed_pair<
          Extents,
          ::std::experimental::dextents<Extents::rank()>
        >
      >
#endif
  {
  public:
    // This could be a `requires`, but I think it's better and clearer as a `static_assert`.
    static_assert(detail::__is_extents_v<Extents>, "std::experimental::layout_stride::mapping must be instantiated with a specialization of std::experimental::extents.");

    using size_type = typename Extents::size_type;
    using extents_type = Extents;

    // TODO @proposal-bug This isn't a requirement of layouts in the proposal,
    // but we need it for `mdspan`'s deduction guides for its mapping
    // constructors.
    using layout = layout_stride;

  private:

    //----------------------------------------------------------------------------

    using __strides_storage_t = ::std::experimental::dextents<Extents::rank()>;
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
        return _MDSPAN_FOLD_AND((self.template __stride<Idxs>() == other.template __stride<Idxs>()) /* && ... */);
      }
      template <class OtherExtents>
      MDSPAN_INLINE_FUNCTION
      static constexpr bool _not_eq_impl(mapping const& self, mapping<OtherExtents> const& other) noexcept {
        return _MDSPAN_FOLD_OR((self.template __stride<Idxs>() != other.template __stride<Idxs>()) /* || ... */);
      }

      template <class... Integral>
      MDSPAN_FORCE_INLINE_FUNCTION
      static constexpr size_t _call_op_impl(mapping const& self, Integral... idxs) noexcept {
        return _MDSPAN_FOLD_PLUS_RIGHT((idxs * self.template __stride<Idxs>()), /* + ... + */ 0);
      }

      MDSPAN_INLINE_FUNCTION
      static constexpr size_t _req_span_size_impl(mapping const& self) noexcept {
        // assumes no negative strides; not sure if I'm allowed to assume that or not
        return __impl::_call_op_impl(self, (self.extents().template __extent<Idxs>() - 1)...) + 1;
      }
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

    //----------------------------------------------------------------------------

  public: // (but not really)

    template <size_t R>
    MDSPAN_INLINE_FUNCTION
    constexpr size_t __stride() const noexcept {
      return __strides_storage().extent(R);
    }

    template <size_t... Idxs>
    MDSPAN_INLINE_FUNCTION
    constexpr array< size_t, Extents::rank() > __strides(std::index_sequence<Idxs...>) const noexcept {
      return {__strides_storage().template __extent<Idxs>()...};
    }

    MDSPAN_INLINE_FUNCTION
    static constexpr mapping
    __make_mapping(
      detail::__extents_to_partially_static_sizes_t<Extents>&& __exts,
      detail::__extents_to_partially_static_sizes_t<
        ::std::experimental::dextents<Extents::rank()>>&& __strs
    ) noexcept {
      // call the private constructor we created for this purpose
      return mapping(
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        __base_t{
#endif
          __member_pair_t(
            extents_type::__make_extents_impl(::std::move(__exts)),
            __strides_storage_t{::std::move(__strs)}
          )
#if !defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#endif
      );
    }

  public:

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping() noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED constexpr mapping(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED
    mapping& operator=(mapping const&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED _MDSPAN_CONSTEXPR_14_DEFAULTED
    mapping& operator=(mapping&&) noexcept = default;
    MDSPAN_INLINE_FUNCTION_DEFAULTED ~mapping() noexcept = default;

    template<class IntegralType>
    MDSPAN_INLINE_FUNCTION
    constexpr
    mapping(
      Extents const& e,
      ::std::array<IntegralType, Extents::rank()> const& strides
    ) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __members{
#else
      : __base_t(__base_t{__member_pair_t(
#endif
          e, __strides_storage_t{strides}
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
    { }

    template<class OtherExtents>
    MDSPAN_CONDITIONAL_EXPLICIT((!is_convertible<OtherExtents, Extents>::value)) // needs two () due to comma
    MDSPAN_INLINE_FUNCTION
    constexpr
    mapping(
      const mapping<OtherExtents>& rhs
    ) noexcept
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      : __members{
#else
      : __base_t(__base_t{__member_pair_t(
#endif
          rhs.extents(), __strides_storage_t{rhs.__strides_storage()}
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
        }
#else
        )})
#endif
    { }

    //--------------------------------------------------------------------------------

    MDSPAN_INLINE_FUNCTION constexpr extents_type extents() const noexcept {
#if defined(_MDSPAN_USE_ATTRIBUTE_NO_UNIQUE_ADDRESS)
      return __members.__first();
#else
      return this->__base_t::__ref().__first();
#endif
    };

    MDSPAN_INLINE_FUNCTION constexpr bool is_unique() const noexcept { return true; }
    // TODO @proposal-bug this wording for this is (at least slightly) broken (should at least be "... stride(p[0]) == 1...")
    MDSPAN_INLINE_FUNCTION _MDSPAN_CONSTEXPR_14 bool is_contiguous() const noexcept {
      // TODO @testing test layout_stride is_contiguous()
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
        constexpr size_t removed_index_sentinel = -1;
        *next_idx_iter = removed_index_sentinel;
        int found_count = 1;
        while (found_count != Extents::rank()) {
          next_idx_iter = std::find_if(
            rem.begin(), rem.end(),
            [&](size_t i) {
              return i != removed_index_sentinel
                && this->stride(i) * this->extents().extent(i) == prev_stride_times_prev_extent;
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
    }
    MDSPAN_INLINE_FUNCTION constexpr bool is_strided() const noexcept { return true; }

    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_unique() noexcept { return true; }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_contiguous() noexcept {
      return false;
    }
    MDSPAN_INLINE_FUNCTION static constexpr bool is_always_strided() noexcept { return true; }

    MDSPAN_TEMPLATE_REQUIRES(
      class... Indices,
      /* requires */ (
        sizeof...(Indices) == Extents::rank() &&
        _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_constructible, Indices, size_t) /*&& ...*/)
      )
    )
    MDSPAN_FORCE_INLINE_FUNCTION
    constexpr size_t operator()(Indices... idxs) const noexcept {
      return __impl::_call_op_impl(*this, idxs...);
    }

    MDSPAN_INLINE_FUNCTION
    constexpr size_t stride(size_t r) const noexcept {
      return __strides_storage().extent(r);
    }

    MDSPAN_INLINE_FUNCTION
    constexpr array< size_t, Extents::rank() > strides() const noexcept {
      return __strides(std::make_index_sequence<Extents::rank()>());
    }

    MDSPAN_INLINE_FUNCTION
    constexpr size_t required_span_size() const noexcept {
      size_t span_size = 1;
      for(unsigned r = 0; r < Extents::rank(); r++) {
        // Return early if any of the extents are zero
        if(extents().extent(r)==0) return 0;
        span_size = std::max(span_size, extents().extent(r) * __strides_storage().extent(r));
      }
      return span_size;
    }

    // TODO @proposal-bug these (and other analogous operators) should be non-member functions
    // TODO @proposal-bug these should do more than just compare extents!

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return __impl::_eq_impl(lhs, rhs);
    }

    template<class OtherExtents>
    MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator!=(mapping const& lhs, mapping<OtherExtents> const& rhs) noexcept {
      return __impl::_not_eq_impl(lhs, rhs);
    }

  };
};

} // end namespace experimental
} // end namespace std
//END_FILE_INCLUDE: /home/runner/work/mdspan/mdspan/include/experimental/__p0009_bits/layout_stride.hpp
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

template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
__slice_wrap<OldExtent, OldStaticStride, full_extent_t>
__wrap_slice(full_extent_t val, size_t ext, size_t stride) { return { val, ext, stride }; }

// TODO generalize this to anything that works with std::get<0> and std::get<1>
template <size_t OldExtent, size_t OldStaticStride>
MDSPAN_INLINE_FUNCTION constexpr
__slice_wrap<OldExtent, OldStaticStride, std::pair<size_t, size_t>>
__wrap_slice(std::pair<size_t, size_t> const& val, size_t ext, size_t stride)
{
  return { val, ext, stride };
}

//--------------------------------------------------------------------------------


template <
  bool result=true,
  bool encountered_first_all=false,
  bool encountered_first_pair=false
>
struct preserve_layout_right_analysis : integral_constant<bool, result> {
  using layout_type_if_preserved = layout_right;
  using encounter_pair = preserve_layout_right_analysis<
    // If the pair isn't the right-most slice (i.e., if there was a previous pair),
    // we can't preserve any contiguous layout.  Nothing else should matter
    (encountered_first_pair ? false : result),
    // Whether or not we've encountered the first all doesn't change, though it
    // doesn't really matter, since anything to the right of this leads to a false
    // result
    encountered_first_all,
    // This is a pair, so we've encountered at least one
    true
  >;
  using encounter_all = preserve_layout_right_analysis<
    // encountering an all changes nothing unless we've already encountered a pair
    (encountered_first_pair ? false : result),
    // This is an all, so we've encountered at least one
    true,
    // nothing changes about this last one
    encountered_first_pair
  >;
  using encounter_scalar = preserve_layout_right_analysis<
    // if there's a scalar to the right of any non-scalar slice, we can't preserve
    // any contiguous layout:
    (encountered_first_all || encountered_first_pair) ? false : result,
    // nothing else changes (though if they're true, it doesn't matter)
    encountered_first_all,
    encountered_first_pair
  >;
};

template <
  bool result=true,
  bool encountered_first_scalar=false,
  bool encountered_first_all=false,
  bool encountered_first_pair=false
>
struct preserve_layout_left_analysis : integral_constant<bool, result> {
  using layout_type_if_preserved = layout_left;
  using encounter_pair = preserve_layout_left_analysis<
    // Only the left-most slice can be a pair.  If we've encountered anything else,
    // we can't preserve any contiguous layout
    (encountered_first_scalar || encountered_first_all || encountered_first_pair) ? false : result,
    // These change in the expected ways
    encountered_first_scalar,
    encountered_first_all,
    true
  >;
  using encounter_all = preserve_layout_left_analysis<
    // If there's a scalar to the left of us, we can't preserve contiguous
    encountered_first_scalar ? false : result,
    // These change in the expected ways
    encountered_first_scalar,
    true,
    encountered_first_pair
  >;
  using encounter_scalar = preserve_layout_left_analysis<
    // If there's a scalar to the left of us, we can't preserve contiguous
    result,
    // These change in the expected ways
    true,
    encountered_first_all,
    encountered_first_pair
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
  class _PreserveLayoutAnalysis,
  class _OffsetsArray=__partially_static_sizes<>,
  class _ExtsArray=__partially_static_sizes<>,
  class _StridesArray=__partially_static_sizes<>,
  class=make_index_sequence<_OffsetsArray::__size>,
  class=make_index_sequence<_ExtsArray::__size>,
  class=make_index_sequence<_StridesArray::__size>
>
struct __assign_op_slice_handler;

/* clang-format: off */
template <
  class _PreserveLayoutAnalysis,
  size_t... _Offsets,
  size_t... _Exts,
  size_t... _Strides,
  size_t... _OffsetIdxs,
  size_t... _ExtIdxs,
  size_t... _StrideIdxs>
struct __assign_op_slice_handler<
  _PreserveLayoutAnalysis,
  __partially_static_sizes<_Offsets...>,
  __partially_static_sizes<_Exts...>,
  __partially_static_sizes<_Strides...>,
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

  using __offsets_storage_t = __partially_static_sizes<_Offsets...>;
  using __extents_storage_t = __partially_static_sizes<_Exts...>;
  using __strides_storage_t = __partially_static_sizes<_Strides...>;
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
  using __extents_type = ::std::experimental::extents<_Exts...>;
#endif

  // For size_t slice, skip the extent and stride, but add an offset corresponding to the value
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(__slice_wrap<_OldStaticExtent, _OldStaticStride, size_t>&& __slice) noexcept
    -> __assign_op_slice_handler<
         typename _PreserveLayoutAnalysis::encounter_scalar,
         __partially_static_sizes<_Offsets..., dynamic_extent>,
         __partially_static_sizes<_Exts...>,
         __partially_static_sizes<_Strides...>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_Offsets..., dynamic_extent>(
        __construct_partially_static_array_from_sizes_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., __slice.slice),
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
         typename _PreserveLayoutAnalysis::encounter_all,
         __partially_static_sizes<_Offsets..., 0>,
         __partially_static_sizes<_Exts..., _OldStaticExtent>,
         __partially_static_sizes<_Strides..., _OldStaticStride>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_Offsets..., 0>(
        __construct_partially_static_array_from_sizes_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., size_t(0)),
      __partially_static_sizes<_Exts..., _OldStaticExtent>(
        __construct_partially_static_array_from_sizes_tag,
        __exts.template __get_n<_ExtIdxs>()..., __slice.old_extent),
      __partially_static_sizes<_Strides..., _OldStaticStride>(
        __construct_partially_static_array_from_sizes_tag,
        __strides.template __get_n<_StrideIdxs>()..., __slice.old_stride)
    };
  }

  // For a std::pair, add an offset and add a new dynamic extent (strides still preserved)
  template <size_t _OldStaticExtent, size_t _OldStaticStride>
  MDSPAN_FORCE_INLINE_FUNCTION // NOLINT (misc-unconventional-assign-operator)
  _MDSPAN_CONSTEXPR_14 auto
  operator=(__slice_wrap<_OldStaticExtent, _OldStaticStride, pair<size_t, size_t>>&& __slice) noexcept
    -> __assign_op_slice_handler<
         typename _PreserveLayoutAnalysis::encounter_pair,
         __partially_static_sizes<_Offsets..., dynamic_extent>,
         __partially_static_sizes<_Exts..., dynamic_extent>,
         __partially_static_sizes<_Strides..., _OldStaticStride>/* intentional space here to work around ICC bug*/> {
    return {
      __partially_static_sizes<_Offsets..., dynamic_extent>(
        __construct_partially_static_array_from_sizes_tag,
        __offsets.template __get_n<_OffsetIdxs>()..., ::std::get<0>(__slice.slice)),
      __partially_static_sizes<_Exts..., dynamic_extent>(
        __construct_partially_static_array_from_sizes_tag,
        __exts.template __get_n<_ExtIdxs>()..., ::std::get<1>(__slice.slice) - ::std::get<0>(__slice.slice)),
      __partially_static_sizes<_Strides..., _OldStaticStride>(
        __construct_partially_static_array_from_sizes_tag,
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
      /* return */ typename NewLayout::template mapping<::std::experimental::extents<_Exts...>>(
        experimental::extents<_Exts...>::__make_extents_impl(::std::move(__exts))
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
      /* return */ layout_stride::template mapping<::std::experimental::extents<_Exts...>>
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
template <class ET, size_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
MDSPAN_INLINE_FUNCTION
constexpr auto _submdspan_impl(
  integer_sequence<size_t, Idxs...>,
  mdspan<ET, std::experimental::extents<Exts...>, LP, AP> const& src,
  SliceSpecs&&... slices
) noexcept
{
  auto _handled =
    _MDSPAN_FOLD_ASSIGN_LEFT(
      (
        detail::__assign_op_slice_handler<
          detail::preserve_layout_analysis<LP>
        >{
          __partially_static_sizes<>{},
          __partially_static_sizes<>{},
          __partially_static_sizes<>{}
        }
      ),
        /* = ... = */
      detail::__wrap_slice<
        Exts, dynamic_extent
      >(
        slices, src.extents().template __extent<Idxs>(),
        src.mapping().template __stride<Idxs>()
      )
    );

  size_t offset_size = src.mapping()(_handled.__offsets.template __get_n<Idxs>()...);
  auto offset_ptr = src.accessor().offset(src.data(), offset_size);
  auto map = _handled.make_layout_mapping(src.mapping());
  auto acc_pol = typename AP::offset_policy(src.accessor());
  return mdspan<
    ET, decltype(map.extents()), typename decltype(_handled)::layout_type, decltype(acc_pol)
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
    src.accessor().offset(src.data(), src.mapping()(h.__offsets.template __get_n<Idxs>()...)),
    h.make_layout_mapping(src.mapping()),
    typename AP::offset_policy(src.accessor())
  };
}

template <class ET, size_t... Exts, class LP, class AP, class... SliceSpecs, size_t... Idxs>
MDSPAN_INLINE_FUNCTION
_MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
  (
    constexpr /* auto */ _submdspan_impl(
      std::integer_sequence<size_t, Idxs...> seq,
      mdspan<ET, std::experimental::extents<Exts...>, LP, AP> const& src,
      SliceSpecs&&... slices
    ) noexcept
  ),
  (
    /* return */ _submdspan_impl_helper<ET, AP>(
      src,
      _MDSPAN_FOLD_ASSIGN_LEFT(
        (
          detail::__assign_op_slice_handler<
            detail::preserve_layout_analysis<LP>
          >{
            __partially_static_sizes<>{},
            __partially_static_sizes<>{},
            __partially_static_sizes<>{}
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

// TODO @proposal-bug sizeof...(SliceSpecs) == sizeof...(Exts) should be a constraint, not a requirement
MDSPAN_TEMPLATE_REQUIRES(
  class ET, size_t... Exts, class LP, class AP, class... SliceSpecs,
  /* requires */ (
    (
      _MDSPAN_TRAIT(is_same, LP, layout_left)
        || _MDSPAN_TRAIT(is_same, LP, layout_right)
        || detail::_is_layout_stride<LP>::value
    ) &&
    _MDSPAN_FOLD_AND((
      _MDSPAN_TRAIT(is_convertible, SliceSpecs, size_t)
        || _MDSPAN_TRAIT(is_convertible, SliceSpecs, pair<size_t, size_t>)
        || _MDSPAN_TRAIT(is_convertible, SliceSpecs, full_extent_t)
    ) /* && ... */) &&
    sizeof...(SliceSpecs) == sizeof...(Exts)
  )
)
MDSPAN_INLINE_FUNCTION
_MDSPAN_DEDUCE_RETURN_TYPE_SINGLE_LINE(
  (
    constexpr submdspan(
      mdspan<ET, std::experimental::extents<Exts...>, LP, AP> const& src, SliceSpecs... slices
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
#endif // _MDSPAN_SINGLE_HEADER_INCLUDE_GUARD_

