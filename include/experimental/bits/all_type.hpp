

#pragma once

#include "macros.hpp"

namespace std {

struct all_type { };

_MDSPAN_INLINE_VARIABLE constexpr auto all = all_type{ };
        
} // namespace std
