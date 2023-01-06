#include <tuple>
namespace std {
namespace experimental {

//******************************************
// Return type of submdspan_mapping overloads
//******************************************
template <class Mapping> struct mapping_offset {
  Mapping mapping;
  size_t offset;
};

namespace detail {
// constructs sub strides
template <class SrcMapping, class... slice_strides, size_t... InvMapIdxs>
constexpr auto
construct_sub_strides(const SrcMapping &src_mapping,
                      index_sequence<InvMapIdxs...>,
                      const tuple<slice_strides...> &slices_stride_factor) {
  using index_type = typename SrcMapping::index_type;
  return array<typename SrcMapping::index_type, sizeof...(InvMapIdxs)>{
      (static_cast<index_type>(src_mapping.stride(InvMapIdxs)) *
       static_cast<index_type>(get<InvMapIdxs>(slices_stride_factor)))...};
}
} // namespace detail

//**********************************
// layout_left submdspan_mapping
//*********************************
namespace detail {

// Figure out whether to preserve layout_left
template <class IndexSequence, size_t SubRank, class... SliceSpecifiers>
struct preserve_layout_left_mapping;

template <class... SliceSpecifiers, size_t... Idx, size_t SubRank>
struct preserve_layout_left_mapping<index_sequence<Idx...>, SubRank,
                                    SliceSpecifiers...> {
  constexpr static bool value =
      // Preserve layout for rank 0
      (SubRank == 0) ||
      (
          // Slice specifiers up to subrank need to be full_extent_t - except
          // for the last one which could also be tuple but not a strided index
          // range slice specifiers after subrank are integrals
          ((Idx > SubRank - 1) || // these are only integral slice specifiers
           (is_same_v<SliceSpecifiers, full_extent_t>) ||
           ((Idx == SubRank - 1) &&
            is_convertible_v<SliceSpecifiers, tuple<size_t, size_t>>)) &&
          ...);
};
} // namespace detail

// Actual submdspan mapping call
template <class Extents, class... SliceSpecifiers>
constexpr auto
submdspan_mapping(const layout_left::mapping<Extents> &src_mapping,
                  SliceSpecifiers... slices) {

  // compute sub extents
  using src_ext_t = Extents;
  auto dst_ext = submdspan_extents(src_mapping.extents(), slices...);
  using dst_ext_t = decltype(dst_ext);

  // figure out sub layout type
  constexpr bool preserve_layout = detail::preserve_layout_left_mapping<
      decltype(make_index_sequence<src_ext_t::rank()>()), dst_ext_t::rank(),
      SliceSpecifiers...>::value;
  using dst_layout_t =
      conditional_t<preserve_layout, layout_left, layout_stride>;
  using dst_mapping_t = typename dst_layout_t::template mapping<dst_ext_t>;

  if constexpr (is_same_v<dst_layout_t, layout_left>) {
    // layout_left case
    return mapping_offset<dst_mapping_t>{
        dst_mapping_t(dst_ext),
        static_cast<size_t>(src_mapping(detail::first_of(slices)...))};
  } else {
    // layout_stride case
    #if MDSPAN_HAS_CXX_20
    using inv_map_t = typename detail::inv_map_rank<0, index_sequence<>,
                                                    SliceSpecifiers...>::type;
    #else
    using inv_map_t = decltype(detail::inv_map_rank(
      integral_constant<size_t,0>(),
      index_sequence<>(),
      (declval<SliceSpecifiers>())...));
    #endif
    return mapping_offset<dst_mapping_t>{
        dst_mapping_t(dst_ext, detail::construct_sub_strides(
                                   src_mapping, inv_map_t(),
                                   tuple{detail::stride_of(slices)...})),
        static_cast<size_t>(src_mapping(detail::first_of(slices)...))};
  }
}

//**********************************
// layout_right submdspan_mapping
//*********************************
namespace detail {

// Figure out whether to preserve layout_left
template <class IndexSequence, size_t SubRank, class... SliceSpecifiers>
struct preserve_layout_right_mapping;

template <class... SliceSpecifiers, size_t... Idx, size_t SubRank>
struct preserve_layout_right_mapping<index_sequence<Idx...>, SubRank,
                                     SliceSpecifiers...> {
  constexpr static size_t SrcRank = sizeof...(SliceSpecifiers);
  constexpr static bool value =
      // Preserve layout for rank 0
      (SubRank == 0) ||
      (
          // The last subrank slice specifiers need to be full_extent_t - except
          // for the srcrank-subrank one which could also be tuple but not a
          // strided index range slice specifiers before srcrank-subrank are
          // integrals
          ((Idx <
            SrcRank - SubRank) || // these are only integral slice specifiers
           (is_same_v<SliceSpecifiers, full_extent_t>) ||
           ((Idx == SrcRank - SubRank) &&
            is_convertible_v<SliceSpecifiers, tuple<size_t, size_t>>)) &&
          ...);
};
} // namespace detail

template <class Extents, class... SliceSpecifiers>
constexpr auto
submdspan_mapping(const layout_right::mapping<Extents> &src_mapping,
                  SliceSpecifiers... slices) {

  // get sub extents
  using src_ext_t = Extents;
  auto dst_ext = submdspan_extents(src_mapping.extents(), slices...);
  using dst_ext_t = decltype(dst_ext);

  // determine new layout type
  constexpr bool preserve_layout = detail::preserve_layout_right_mapping<
      decltype(make_index_sequence<src_ext_t::rank()>()), dst_ext_t::rank(),
      SliceSpecifiers...>::value;
  using dst_layout_t =
      conditional_t<preserve_layout, layout_right, layout_stride>;
  using dst_mapping_t = typename dst_layout_t::template mapping<dst_ext_t>;

  if constexpr (is_same_v<dst_layout_t, layout_right>) {
    // layout_right case
    return mapping_offset<dst_mapping_t>{
        dst_mapping_t(dst_ext),
        static_cast<size_t>(src_mapping(detail::first_of(slices)...))};
  } else {
    // layout_stride case
    #if MDSPAN_HAS_CXX_20
    using inv_map_t = typename detail::inv_map_rank<0, index_sequence<>,
                                                    SliceSpecifiers...>::type;
    #else
    using inv_map_t = decltype(detail::inv_map_rank(
      integral_constant<size_t,0>(),
      index_sequence<>(),
      (declval<SliceSpecifiers>())...));
    #endif
    return mapping_offset<dst_mapping_t>{
        dst_mapping_t(dst_ext, detail::construct_sub_strides(
                                   src_mapping, inv_map_t(),
                                   tuple{detail::stride_of(slices)...})),
        static_cast<size_t>(src_mapping(detail::first_of(slices)...))};
  }
}

//**********************************
// layout_stride submdspan_mapping
//*********************************
template <class Extents, class... SliceSpecifiers>
constexpr auto
submdspan_mapping(const layout_stride::mapping<Extents> &src_mapping,
                  SliceSpecifiers... slices) {
  auto dst_ext = submdspan_extents(src_mapping.extents(), slices...);
  using dst_ext_t = decltype(dst_ext);
  #if MDSPAN_HAS_CXX_20
  using inv_map_t = typename detail::inv_map_rank<0, index_sequence<>,
                                                  SliceSpecifiers...>::type;
  #else
  using inv_map_t = decltype(detail::inv_map_rank(
      integral_constant<size_t,0>(),
      index_sequence<>(),
      (declval<SliceSpecifiers>())...));
  #endif
  using dst_mapping_t = typename layout_stride::template mapping<dst_ext_t>;
  return mapping_offset<dst_mapping_t>{
      dst_mapping_t(dst_ext, detail::construct_sub_strides(
                                 src_mapping, inv_map_t(),
                                 tuple{detail::stride_of(slices)...})),
      static_cast<size_t>(src_mapping(detail::first_of(slices)...))};
}
} // namespace experimental
} // namespace std
