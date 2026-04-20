#pragma once


#include <complex>
#include <limits>

#include "ffc/core/num/f32.hpp"


namespace ffc::core::num {
    using c64 = std::complex<f32>;
    static_assert(sizeof(c64) == 8uz);

    namespace complex::c64 {
        constexpr auto MAX{std::numeric_limits<f32>::max()};
        constexpr auto MIN{std::numeric_limits<f32>::lowest()};
        constexpr auto MIN_POSITIVE{std::numeric_limits<f32>::min()}; 
        constexpr auto INF{std::numeric_limits<f32>::infinity()};
        constexpr auto NEG_INF{-std::numeric_limits<f32>::infinity()};
        constexpr auto RADIX{std::numeric_limits<f32>::radix};
        constexpr auto DIGITS10{std::numeric_limits<f32>::digits10};
        constexpr auto QUIET_NAN{std::numeric_limits<f32>::quiet_NaN()};
        constexpr auto EPSILON{std::numeric_limits<f32>::epsilon()};
        constexpr auto BYTES{sizeof(c64)};
        constexpr auto BITS{sizeof(c64) * 8uz};
    }
} // namespace ffc::core::num;
