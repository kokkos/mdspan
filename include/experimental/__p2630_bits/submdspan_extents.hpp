namespace std {
namespace experimental {

// Slice Specifier allowing for strides and compile time extent
template <class OffsetType, class ExtentType, class StrideType>
struct strided_index_range {
  using offset_type = OffsetType;
  using extent_type = ExtentType;
  using stride_type = StrideType;

  OffsetType offset;
  ExtentType extent;
  StrideType stride;
};

namespace detail {

// Mapping from submapping ranks to srcmapping ranks
// InvMapRank is gonna be a index_sequence, which we build recursively
// to contain the mapped indicies.
template <size_t Counter, class InvMapRank, class... SliceSpecifiers>
struct inv_map_rank;

// specialization reducing rank by one (i.e. integral slice specifier)
template <size_t Counter, class Slice, class... SliceSpecifiers,
          size_t... MapIdxs>
requires(is_convertible_v<Slice, size_t>) struct inv_map_rank<
    Counter, index_sequence<MapIdxs...>, Slice, SliceSpecifiers...> {
  using type = typename inv_map_rank<Counter + 1, index_sequence<MapIdxs...>,
                                     SliceSpecifiers...>::type;
};

// specialization for slice specifiers expressing some form of range
template <size_t Counter, class Slice, class... SliceSpecifiers,
          size_t... MapIdxs>
requires(!is_convertible_v<Slice, size_t>) struct inv_map_rank<
    Counter, index_sequence<MapIdxs...>, Slice, SliceSpecifiers...> {
  using type =
      typename inv_map_rank<Counter + 1, index_sequence<MapIdxs..., Counter>,
                            SliceSpecifiers...>::type;
};

// final specialziation containing the final index_sequence
template <size_t Counter, size_t... MapIdxs>
struct inv_map_rank<Counter, index_sequence<MapIdxs...>> {
  using type = index_sequence<MapIdxs...>;
};

// Helper for identifying strided_index_range
template <class T> struct is_strided_index_range : false_type {};

template <class OffsetType, class ExtentType, class StrideType>
struct is_strided_index_range<
    strided_index_range<OffsetType, ExtentType, StrideType>> : true_type {};

// first_of(slice): getting begin of slice specifier range
template <class Integral>
requires(is_convertible_v<Integral, size_t>) constexpr Integral
    first_of(const Integral &i) {
  return i;
}

constexpr integral_constant<size_t, 0>
first_of(const experimental::full_extent_t &) {
  return integral_constant<size_t, 0>();
}

template <class Slice>
requires(
    is_convertible_v<
        Slice, tuple<size_t, size_t>>) constexpr auto first_of(const Slice &i) {
  return get<0>(i);
}

template <class OffsetType, class ExtentType, class StrideType>
constexpr OffsetType
first_of(const strided_index_range<OffsetType, ExtentType, StrideType> &r) {
  return r.offset;
}

// last_of(slice): getting end of slice sepcifier range
template <size_t k, class Extents, class Integral>
requires(is_convertible_v<Integral, size_t>) constexpr Integral
    last_of(integral_constant<size_t, k>, const Extents &, const Integral &i) {
  return i;
}

template <size_t k, class Extents, class Slice>
requires(is_convertible_v<Slice, tuple<size_t, size_t>>) constexpr auto last_of(
    integral_constant<size_t, k>, const Extents &, const Slice &i) {
  return get<1>(i);
}

template <size_t k, class Extents>
constexpr auto last_of(integral_constant<size_t, k>, const Extents &ext,
                       experimental::full_extent_t) {
  if constexpr (Extents::static_extent(k) == dynamic_extent) {
    return ext.extent(k);
  } else {
    return integral_constant<size_t, Extents::static_extent(k)>();
  }
}

template <size_t k, class Extents, class OffsetType, class ExtentType,
          class StrideType>
constexpr OffsetType
last_of(integral_constant<size_t, k>, const Extents &,
        const strided_index_range<OffsetType, ExtentType, StrideType> &r) {
  return r.extent;
}

// get stride of slices
template <class T> constexpr auto stride_of(const T &) {
  return integral_constant<size_t, 1>();
}

template <class OffsetType, class ExtentType, class StrideType>
constexpr auto
stride_of(const strided_index_range<OffsetType, ExtentType, StrideType> &r) {
  return r.stride;
}

// divide which can deal with integral constant preservation
template <class IndexT, class T0, class T1>
constexpr auto divide(const T0 &v0, const T1 &v1) {
  return IndexT(v0) / IndexT(v1);
}

template <class IndexT, class T0, T0 v0, class T1, T1 v1>
constexpr auto divide(const integral_constant<T0, v0> &,
                      const integral_constant<T1, v1> &) {
  return integral_constant<IndexT, v0 / v1>();
}

// multiply which can deal with integral constant preservation
template <class IndexT, class T0, class T1>
constexpr auto multiply(const T0 &v0, const T1 &v1) {
  return IndexT(v0) * IndexT(v1);
}

template <class IndexT, class T0, T0 v0, class T1, T1 v1>
constexpr auto multiply(const integral_constant<T0, v0> &,
                        const integral_constant<T1, v1> &) {
  return integral_constant<IndexT, v0 * v1>();
}

// compute new static extent from range, preserving static knowledge
template <class Arg0, class Arg1> struct StaticExtent {
  constexpr static size_t value = std::dynamic_extent;
};

template <class Integral0, Integral0 val0, class Integral1, Integral1 val1>
struct StaticExtent<std::integral_constant<Integral0, val0>,
                    std::integral_constant<Integral1, val1>> {
  constexpr static size_t value = val1 - val0;
};

// creates new extents through recursive calls to next_extent member function
// next_extent has different overloads for different types of stride specifiers
template <size_t K, class Extents, size_t... NewExtents>
struct extents_constructor {
  template <class Slice, class... SliceSpecifiers>
  requires(
      !is_convertible_v<Slice, size_t> &&
      !is_strided_index_range<Slice>::
          value) constexpr static auto next_extent(const Extents &ext,
                                                   const Slice &sl,
                                                   SliceSpecifiers... slices) {
    constexpr size_t new_static_extent =
        StaticExtent<decltype(first_of(std::declval<Slice>())),
                     decltype(last_of(
                         integral_constant<size_t, Extents::rank() - K>(),
                         std::declval<Extents>(),
                         std::declval<Slice>()))>::value;

    using next_t =
        extents_constructor<K - 1, Extents, NewExtents..., new_static_extent>;
    using index_t = typename Extents::index_type;
    return next_t::next_extent(
        ext, slices...,
        index_t(last_of(integral_constant<size_t, Extents::rank() - K>(), ext,
                        sl)) -
            index_t(first_of(sl)));
  }
  template <class Slice, class... SliceSpecifiers>
  requires(is_convertible_v<Slice, size_t>) constexpr static auto next_extent(
      const Extents &ext, const Slice &, SliceSpecifiers... slices) {
    using next_t = extents_constructor<K - 1, Extents, NewExtents...>;
    return next_t::next_extent(ext, slices...);
  }
  template <class OffsetType, class ExtentType, class StrideType,
            class... SliceSpecifiers>
  constexpr static auto
  next_extent(const Extents &ext,
              const strided_index_range<OffsetType, ExtentType, StrideType> &r,
              SliceSpecifiers... slices) {
    using index_t = typename Extents::index_type;
    if constexpr (StaticExtent<ExtentType, StrideType>::value ==
                  dynamic_extent) {
      using next_t =
          extents_constructor<K - 1, Extents, NewExtents..., dynamic_extent>;
      return next_t::next_extent(ext, slices...,
                                 divide<index_t>(r.extent, r.stride));
    } else {
      constexpr size_t new_static_extent =
          divide<size_t>(ExtentType(), StrideType());
      using next_t =
          extents_constructor<K - 1, Extents, NewExtents..., new_static_extent>;
      return next_t::next_extent(
          ext, slices..., index_t(divide<index_t>(ExtentType(), StrideType())));
    }
  }
};

template <class Extents, size_t... NewStaticExtents>
struct extents_constructor<0, Extents, NewStaticExtents...> {

  template <class... NewExtents>
  constexpr static auto next_extent(const Extents &, NewExtents... new_exts) {
    return extents<typename Extents::index_type, NewStaticExtents...>(
        new_exts...);
  }
};

} // namespace detail

// submdspan_extents creates new extents given src extents and submdspan slice
// specifiers
template <class IndexType, size_t... Extents, class... SliceSpecifiers>
constexpr auto submdspan_extents(const extents<IndexType, Extents...> &src_exts,
                                 SliceSpecifiers... slices) {

  using ext_t = extents<IndexType, Extents...>;
  return detail::extents_constructor<ext_t::rank(), ext_t>::next_extent(
      src_exts, slices...);
}
} // namespace experimental
} // namespace std
