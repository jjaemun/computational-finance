#pragma once


#include "ffc/num/types.hpp"
#include "ffc/core/num/traits.hpp"


namespace ffc::num {
    using usize = core::num::IntTraits<ffc::usize>;
    using isize = core::num::IntTraits<ffc::isize>;

    using u8 = core::num::IntTraits<ffc::u8>;
    using u16 = core::num::IntTraits<ffc::u16>;
    using u32 = core::num::IntTraits<ffc::u32>;
    using u64 = core::num::IntTraits<ffc::u64>;

    using i8 = core::num::IntTraits<ffc::i8>;
    using i16 = core::num::IntTraits<ffc::i16>;
    using i32 = core::num::IntTraits<ffc::i32>;
    using i64 = core::num::IntTraits<ffc::i64>;

    using f32 = core::num::FpTraits<ffc::f32>;
    using f64 = core::num::FpTraits<ffc::f64>;

    using c64 = core::num::ComplexTraits<ffc::c64>; 
    using c128 = core::num::ComplexTraits<ffc::c128>;
} // namespace ffc::num
