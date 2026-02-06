#pragma once

#include <type_traits>

namespace MDSPAN_IMPL_STANDARD_NAMESPACE {
  namespace detail { 

#if (__cplusplus >= 202002L)
    using std::remove_cvref_t;
#else
    template<class T>
    struct remove_cvref {
      using type = typename std::remove_cv_t<std::remove_reference_t<T>>;
    };
    template<class T>
    using remove_cvref_t = typename remove_cvref<T>::type;
#endif // __cplusplus >= 202002L

  } // namespace detail
} // namespace MDSPAN_IMPL_STANDARD_NAMESPACE
