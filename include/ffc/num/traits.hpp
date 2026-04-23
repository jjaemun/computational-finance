#pragma once


#include "ffc/num/aliases.hpp"
#include "ffc/core/num/num.hpp"


namespace ffc::num {
    using usize = ffc::core::num::IntTraits<ffc::usize>;
    using isize = ffc::core::num::IntTraits<ffc::isize>;

    using u8 = ffc::core::num::IntTraits<ffc::u8>;
    using u8 = ffc::core::num::IntTraits<ffc::u8>;
    
    using f32 = ffc::core::num::FpTraits<ffc::f32>;
    using f64 = ffc::core::num::FpTraits<ffc::f64>;

    using c64 = ffc::core::num::ComplexTraits<ffc::c64>;
    using c128 = ffc::core::num::ComplexTraits<ffc::c128>;
} // namespace ffc::num
