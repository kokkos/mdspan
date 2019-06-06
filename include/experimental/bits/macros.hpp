

#pragma once

#define MDSPAN_FORCE_INLINE_FUNCTION __attribute__((always_inline))
#define MDSPAN_INLINE_FUNCTION inline

#if __cpp_concepts >= 201507
#  define MDSPAN_USE_CONCEPTS 1
#else
#  undef MDSPAN_USE_CONCEPTS
#endif


// These compatibility macros don't help with partial ordering, but they should do the trick
// for what we need to do with concepts in mdspan
#ifdef MDSPAN_USE_CONCEPTS
#  define MDSPAN_REQUIRES(...) requires __VA_ARGS__
#  define MDSPAN_NOEXCEPT_REQUIRES(...) noexcept requires __VA_ARGS__
#else
#  define MDSPAN_REQUIRES(...) noexcept(noexcept(std::enable_if_t<__VA_ARGS__, int>(0)) && false)
#  define MDSPAN_NOEXCEPT_REQUIRES(...) noexcept(noexcept(std::enable_if_t<__VA_ARGS__, int>(0)) || true)
#  define MDSPAN_CONDITIONAL_NOEXCEPT_REQUIRES(condition, ...) noexcept(condition && noexcept(std::enable_if_t<__VA_ARGS__, int>(0)))
#endif