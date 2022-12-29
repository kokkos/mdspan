#include "submdspan_extents.hpp"
#include "submdspan_mapping.hpp"

namespace std {
namespace experimental {
template <class ElementType, class Extents, class LayoutPolicy,
          class AccessorPolicy, class... SliceSpecifiers>
constexpr auto
submdspan(const mdspan<ElementType, Extents, LayoutPolicy, AccessorPolicy> &src,
          SliceSpecifiers... slices) {
  const auto sub_map_offset = submdspan_mapping(src.mapping(), slices...);
  return mdspan(src.accessor().offset(src.data_handle(), sub_map_offset.offset),
                sub_map_offset.map,
                typename AccessorPolicy::offset_policy(src.accessor()));
}
} // namespace experimental
} // namespace std
