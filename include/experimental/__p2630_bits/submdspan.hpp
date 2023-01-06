#include "submdspan_extents.hpp"
#include "submdspan_mapping.hpp"

namespace std {
namespace experimental {
template <class ElementType, class Extents, class LayoutPolicy,
          class AccessorPolicy, class... SliceSpecifiers>
constexpr auto
submdspan(const mdspan<ElementType, Extents, LayoutPolicy, AccessorPolicy> &src,
          SliceSpecifiers... slices) {
  const auto sub_mapping_offset = submdspan_mapping(src.mapping(), slices...);
  return mdspan(src.accessor().offset(src.data_handle(), sub_mapping_offset.offset),
                sub_mapping_offset.mapping,
                typename AccessorPolicy::offset_policy(src.accessor()));
}
} // namespace experimental
} // namespace std
