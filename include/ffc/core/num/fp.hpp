#pragma once


#include <limits>
#include "ffc/core/num/traits.hpp"


namespace ffc::core::num {
    using f32 = float;
    using f64 = double;

    namespace fp {
        using f32 = FpTraits<::ffc::core::num::f32>; 
        using f64 = FpTraits<::ffc::core::num::f64>; 
    } // namespace fp

    static_assert(sizeof(f32) == 4uz);
    static_assert(sizeof(f64) == 8uz);
    
    static_assert(std::numeric_limits<f32>::is_iec559);
    static_assert(std::numeric_limits<f64>::is_iec559);
} // namespace ffc::core::num
