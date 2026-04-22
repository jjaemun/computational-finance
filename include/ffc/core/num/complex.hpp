#pragma once


#include <complex>

#include "ffc/core/num/fp.hpp"
#include "ffc/core/num/traits.hpp"


namespace ffc::core::num {
    using c64 = std::complex<f32>;
    using c128 = std::complex<f64>;

    namespace complex {
        using c64 = ComplexTraits<::ffc::core::num::c64>;
        using c128 = ComplexTraits<::ffc::core::num::c128>;
    } // namespace complex

    static_assert(sizeof(c64) == 8uz);
    static_assert(sizeof(c128) == 16uz);
} // namespace ffc::core::num
