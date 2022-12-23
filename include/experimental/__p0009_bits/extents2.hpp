#include "dynamic_extent.hpp"

#ifdef __cpp_lib_span
#include "span"
#endif
#include "array"

#define _MDSPAN_NEW_EXTENTS

namespace std::experimental {

// Implementation of Static Array, recursive implementation of get
template<size_t R, class T, T ... Extents>
struct static_array_impl;

template<size_t R, class T, T FirstExt, T ... Extents>
struct static_array_impl<R, T, FirstExt, Extents...> {
  MDSPAN_INLINE_FUNCTION
  constexpr static T value(size_t r) {
    if(r==R) return FirstExt;
    else return static_array_impl<R+1, T, Extents...>::value(r);
  }
  template<size_t r>
  MDSPAN_INLINE_FUNCTION
  constexpr static T get() {
#if MDSPAN_HAS_CXX_17
    if constexpr (r==R) return FirstExt;
    else return static_array_impl<R+1, T, Extents...>::template get<r>();
#else
    if(r==R) return FirstExt;
    else return static_array_impl<R+1, T, Extents...>::value(r);
#endif
  }
};

// End the recursion
template<size_t R, class T, T FirstExt>
struct static_array_impl<R, T, FirstExt> {
  MDSPAN_INLINE_FUNCTION
  constexpr static T value(int) {
    return FirstExt;
  }
  template<size_t>
  MDSPAN_INLINE_FUNCTION
  constexpr static T get() {
    return FirstExt;
  }
};

// Don't start recursion if size 0
template<class T>
struct static_array_impl<0, T> {
  MDSPAN_INLINE_FUNCTION
  constexpr static T value(int) {
    return T();
  }
  template<size_t>
  MDSPAN_INLINE_FUNCTION
  constexpr static T get() {
    return T();
  }
};

// Static array, provides get<r>(), get(r) and operator[r]
template<class T, T ... Values>
struct static_array {
private:
  using impl_t = static_array_impl<0, T, Values...>;
public:
  using value_type = T;

  MDSPAN_INLINE_FUNCTION
  constexpr T operator[](int r) const { return get(r); }
  MDSPAN_INLINE_FUNCTION
  constexpr static T get(int r) { return impl_t::value(r); }
  template<size_t r>
  MDSPAN_INLINE_FUNCTION
  constexpr static T get() { return impl_t::template get<r>(); }
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t size() { return sizeof...(Values); }
};

// index_sequence_scan takes indicies and provides get(r) and get<r>() to get the sum of the first r-1 values
template<size_t R, size_t ... Values>
struct index_sequence_scan_impl;

template<size_t R, size_t FirstVal, size_t ... Values>
struct index_sequence_scan_impl<R, FirstVal, Values...> {
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t get(size_t r) {
    if(r>R) return FirstVal + index_sequence_scan_impl<R+1, Values...>::get(r);
    else return 0;
  }
  template<size_t r>
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t get() { return r>R? FirstVal + index_sequence_scan_impl<R+1, Values...>::get(r):0; }
};

template<size_t R, size_t FirstVal>
struct index_sequence_scan_impl<R, FirstVal> {
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t get(size_t r) { return R>r?FirstVal:0; }
  template<size_t r>
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t get() { return R>r?FirstVal:0; }
};
template<>
struct index_sequence_scan_impl<0> {
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t get(size_t) { return 0; }
  template<size_t>
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t get() { return 0; }
};

// Need this to have fully empty class maybe_static_array with all entries static
// Rather specialize this small helper class on size 0, then the whole thing
template<class T, size_t N>
struct possibly_empty_array {
  T vals[N];
  MDSPAN_INLINE_FUNCTION
  constexpr T& operator[] (size_t r) { return vals[r]; }
  MDSPAN_INLINE_FUNCTION
  constexpr const T& operator[] (size_t r) const { return vals[r]; }
};

template<class T>
struct possibly_empty_array<T,0> {
  MDSPAN_INLINE_FUNCTION
  constexpr T operator[] (size_t) { return T(); }
  MDSPAN_INLINE_FUNCTION
  constexpr const T operator[] (size_t) const { return T(); }
};


// maybe_static_array is an array which has a mix of static and dynamic values
template<class TDynamic, class TStatic, TStatic dyn_tag, TStatic ... Values>
struct maybe_static_array {
  private:
    using static_vals_t = static_array<TStatic, Values...>;
    constexpr static size_t m_size = sizeof...(Values);
    constexpr static size_t m_size_dynamic = _MDSPAN_FOLD_PLUS_RIGHT((Values==dyn_tag), 0);

    _MDSPAN_NO_UNIQUE_ADDRESS possibly_empty_array<TDynamic,m_size_dynamic> m_dyn_vals;
  public:
    using dyn_map_t = index_sequence_scan_impl<0, size_t(Values==dyn_tag)...>;

    using value_type = TDynamic;
    using static_value_type = TStatic;
    constexpr static static_value_type tag_value = dyn_tag;

    constexpr maybe_static_array() = default;

    // constructors from dynamic_extentamic values only
    MDSPAN_TEMPLATE_REQUIRES(
      class ... DynVals,
      /* requires */(
        sizeof...(DynVals)==m_size_dynamic && m_size_dynamic>0
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(DynVals ... vals):
      m_dyn_vals{static_cast<TDynamic>(vals)...} {}

    MDSPAN_TEMPLATE_REQUIRES(
      class ... DynVals,
      /* requires */(
        (m_size_dynamic==0) && (sizeof...(DynVals)>0)
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(DynVals ...):
      m_dyn_vals{} {}

    MDSPAN_TEMPLATE_REQUIRES(
      class T, size_t N,
      /* requires */(
        N==m_size_dynamic && N>0
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(const std::array<T,N>& vals) {
      for(size_t r=0; r<N; r++) m_dyn_vals[r] = static_cast<TDynamic>(vals[r]);
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class T, size_t N,
      /* requires */(
        N==m_size_dynamic && N==0
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(const std::array<T,N>&) {
    }

#ifdef __cpp_lib_span
    MDSPAN_TEMPLATE_REQUIRES(
      class T, size_t N,
      /* requires */(
        N==m_size_dynamic
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(const std::span<T,N>& vals) {
      for(size_t r=0; r<N; r++) m_dyn_vals[r] = static_cast<TDynamic>(vals[r]);
    }
#endif

    // constructors from all values
    MDSPAN_TEMPLATE_REQUIRES(
      class ... DynVals,
      /* requires */(
        sizeof...(DynVals)!=m_size_dynamic && m_size_dynamic>0
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(DynVals ... vals) {
      static_assert((sizeof...(DynVals)==m_size) || (m_size==dynamic_extent));
      TDynamic values[m_size]{static_cast<TDynamic>(vals)...};
      for(size_t r=0; r<m_size; r++) {
        TStatic static_val = static_vals_t::get(r);
        if(static_val == dynamic_extent) {
          m_dyn_vals[dyn_map_t::get(r)] = values[r];
        }
#ifdef _MDSPAN_DEBUG
        else {
          assert(values[r]==static_cast<TDynamic>(static_val));
        }
#endif
      }
    }

    MDSPAN_TEMPLATE_REQUIRES(
      class T, size_t N,
      /* requires */(
        N!=m_size_dynamic && m_size_dynamic>0
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(const std::array<T,N>& vals) {
      static_assert((N==m_size) || (m_size==dynamic_extent));
#ifdef _MDSPAN_DEBUG
      assert(N==m_size);
#endif
      for(size_t r=0; r<m_size; r++) {
        TStatic static_val = static_vals_t::get(r);
        if(static_val == dynamic_extent) {
          m_dyn_vals[dyn_map_t::get(r)] = static_cast<TDynamic>(vals[r]);
        }
#ifdef _MDSPAN_DEBUG
        else {
          assert(static_cast<TDynamic>(vals[r])==static_cast<TDynamic>(static_val));
        }
#endif
      }
    }

#ifdef __cpp_lib_span
    MDSPAN_TEMPLATE_REQUIRES(
      class T, size_t N,
      /* requires */(
        N!=m_size_dynamic && m_size_dynamic>0
      )
    )
    MDSPAN_INLINE_FUNCTION
    constexpr maybe_static_array(const std::span<T,N>& vals) {
      static_assert((N==m_size) || (m_size==dynamic_extent));
#ifdef _MDSPAN_DEBUG
      assert(N==m_size);
#endif
      for(size_t r=0; r<m_size; r++) {
        TStatic static_val = static_vals_t::get(r);
        if(static_val == dynamic_extent) {
          m_dyn_vals[dyn_map_t::get(r)] = static_cast<TDynamic>(vals[r]);
        }
#ifdef _MDSPAN_DEBUG
        else {
          assert(static_cast<TDynamic>(vals[r])==static_cast<TDynamic>(static_val));
        }
#endif
      }
    }
#endif

    // access functions
    MDSPAN_INLINE_FUNCTION
    constexpr static TStatic static_value(int r) { return static_vals_t::get(r); }

    MDSPAN_INLINE_FUNCTION
    constexpr TDynamic value(int r) const {
      TStatic static_val = static_vals_t::get(r);
      return static_val==dynamic_extent?
        m_dyn_vals[dyn_map_t::get(r)] : static_cast<TDynamic>(static_val);
    }
    MDSPAN_INLINE_FUNCTION
    constexpr TDynamic operator[](int r) const {
      return value(r);
    }

    // observers
    MDSPAN_INLINE_FUNCTION
    constexpr static size_t size() { return m_size; }
    MDSPAN_INLINE_FUNCTION
    constexpr static size_t size_dynamic() { return m_size_dynamic; }
};

#if 0
template<class TDynamic, class TStatic, TStatic dyn_tag>
struct maybe_static_array {
  private:
    using static_vals_t = static_array<TStatic, Values...>;
    using dyn_map_t = index_sequence_scan_impl<0, size_t(Values==dyn_tag)...>;
    constexpr static size_t m_size = sizeof...(Values);
    constexpr static size_t m_size_dynamic = ((Values==dyn_tag) + ... + 0);


  public:

    using value_type = TDynamic;
    using static_value_type = TStatic;
    constexpr static static_value_type tag_value = dyn_tag;

    constexpr static size_t size() { return 0; }
    constexpr static size_t size_dynamic() { return 0; }
};
#endif

template<class IndexType, size_t ... Extents>
class extents {
public:
  using rank_type = size_t;
  using index_type = IndexType;
  using size_type = make_unsigned_t<index_type>;
private:
  constexpr static rank_type m_rank = sizeof...(Extents);
  constexpr static rank_type m_rank_dynamic = _MDSPAN_FOLD_PLUS_RIGHT((Extents==dynamic_extent), /* + ... + */ 0);

  using vals_t = maybe_static_array<IndexType, size_t, dynamic_extent, Extents...>;
  _MDSPAN_NO_UNIQUE_ADDRESS vals_t m_vals;
public:
  MDSPAN_INLINE_FUNCTION
  constexpr static rank_type rank() { return m_rank; }
  MDSPAN_INLINE_FUNCTION
  constexpr static rank_type rank_dynamic() { return m_rank_dynamic; }

  MDSPAN_INLINE_FUNCTION_DEFAULTED
  constexpr extents() = default;

  MDSPAN_TEMPLATE_REQUIRES(
    class ... OtherIndexTypes,
    /* requires */(
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_convertible, OtherIndexTypes, index_type) /* && ... */) &&
      _MDSPAN_FOLD_AND(_MDSPAN_TRAIT(is_nothrow_constructible, index_type, OtherIndexTypes) /* && ... */) &&
      (sizeof...(OtherIndexTypes)==m_rank || sizeof...(OtherIndexTypes)==m_rank_dynamic)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(OtherIndexTypes ... dynvals):m_vals(static_cast<index_type>(dynvals)...) {}

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherIndexType, size_t N,
    /* requires */(
      _MDSPAN_TRAIT(is_convertible, OtherIndexType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, OtherIndexType) &&
      (N==m_rank || N==m_rank_dynamic)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(const array<OtherIndexType, N>& exts):m_vals(std::move(exts)) {}

#ifdef __cpp_lib_span
  MDSPAN_TEMPLATE_REQUIRES(
    class OtherIndexType, size_t N,
    /* requires */(
      _MDSPAN_TRAIT(is_convertible, OtherIndexType, index_type) &&
      _MDSPAN_TRAIT(is_nothrow_constructible, index_type, OtherIndexType) &&
      (N==m_rank || N==m_rank_dynamic)
    )
  )
  MDSPAN_INLINE_FUNCTION
  constexpr extents(const span<OtherIndexType, N>& exts):m_vals(std::move(exts)) {}
#endif

  MDSPAN_TEMPLATE_REQUIRES(
    class OtherIndexType, size_t... OtherExtents,
    /* requires */(
      (sizeof...(OtherExtents) == rank()) &&
      _MDSPAN_FOLD_AND((OtherExtents == dynamic_extent ||
        Extents == dynamic_extent ||
        OtherExtents == Extents) /* && ... */)
    )
  )
  MDSPAN_CONDITIONAL_EXPLICIT((((Extents != dynamic_extent) && (OtherExtents == dynamic_extent))
                     || ... ) ||
                     (numeric_limits<index_type>::max() < numeric_limits<OtherIndexType>::max()))
  MDSPAN_INLINE_FUNCTION
  constexpr extents(const extents<OtherIndexType, OtherExtents...>& other) noexcept {
#if MDSPAN_HAS_CXX_17
      if constexpr(m_rank_dynamic>0) {
#else
      if (m_rank_dynamic>0) {
#endif
        std::array<index_type, m_rank_dynamic> vals;
        for(size_type r=0; r<m_rank; r++) {
          if (static_extent(r) == dynamic_extent) {
            vals[vals_t::dyn_map_t::get(r)] = other.extent(r);
          }
        }
        m_vals = vals_t(std::move(vals));
      }
  }

  MDSPAN_INLINE_FUNCTION
  constexpr index_type extent(rank_type r) const {
    return m_vals.value(r);
  }
  MDSPAN_INLINE_FUNCTION
  constexpr static size_t static_extent(rank_type r) {
    return vals_t::static_value(r);
  }

  template<class OtherIndexType, size_t... OtherExtents>
  MDSPAN_INLINE_FUNCTION
    friend constexpr bool operator==(const extents& ext,
                                     const extents<OtherIndexType, OtherExtents...>& ext2) noexcept {
    bool value = true;
    for(size_type r=0; r<m_rank; r++) value &= ext.extent(r) == ext2.extent(r);
    return value;
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

}
}
