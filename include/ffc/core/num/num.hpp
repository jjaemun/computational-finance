#pragma once


#include "ffc/core/num/concepts.hpp"
#include "ffc/core/num/consts.hpp"
#include "ffc/core/num/traits.hpp"
#include "ffc/core/num/integral.hpp"
#include "ffc/core/num/fp.hpp"
#include "ffc/core/num/complex.hpp"

namespace ffc {
    using core::num::IntType;
    using core::num::SignedIntType;
    using core::num::UnsignedIntType;
    using core::num::FpType;
    using core::num::ComplexType;
    using core::num::FpComplexType;

    using core::num::IntTraits;
    using core::num::FpTraits;
    using core::num::ComplexTraits;

    using core::num::E;
    using core::num::LOG2_E;
    using core::num::LOG10_E;
    using core::num::PI;
    using core::num::INV_PI;
    using core::num::INV_SQRT_PI;
    using core::num::LN_2;
    using core::num::LN_10;
    using core::num::SQRT_2;
    using core::num::SQRT_3;
    using core::num::INV_SQRT_3;
    using core::num::EGAMMA;
    using core::num::PHI;

    using core::num::usize;
    using core::num::isize;

    using core::num::u8;
    using core::num::u16;
    using core::num::u32;
    using core::num::u64;

    using core::num::i8;
    using core::num::i16;
    using core::num::i32;
    using core::num::i64;

    using core::num::f32;
    using core::num::f64;

    using core::num::c64;
    using core::num::c128;

    namespace fp = core::num::fp;
    namespace integral = core::num::integral;
    namespace complex = core::num::complex;
} // namespace ffc
