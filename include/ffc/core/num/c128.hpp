#pragma once


#include <complex>
#include <limits>


#include "ffc/core/num/f64.hpp"


namespace ffc::core::num {
    using c128 = std::complex<f64>;
    static_assert(sizeof(c128) == 16uz);

    namespace complex::c128 {
        constexpr auto MAX{std::numeric_limits<f64>::max()};
        constexpr auto MIN{std::numeric_limits<f64>::lowest()};
        constexpr auto MIN_POSITIVE{std::numeric_limits<f64>::min()}; 
        constexpr auto INF{std::numeric_limits<f64>::infinity()};
        constexpr auto NEG_INF{-std::numeric_limits<f64>::infinity()};
        constexpr auto RADIX{std::numeric_limits<f64>::radix};
        constexpr auto DIGITS10{std::numeric_limits<f64>::digits10};
        constexpr auto QUIET_NAN{std::numeric_limits<f64>::quiet_NaN()};
        constexpr auto EPSILON{std::numeric_limits<f64>::epsilon()};
        constexpr auto BYTES{sizeof(c128)};
        constexpr auto BITS{sizeof(c128) * 8uz};
    }
} // namespace ffc::core::num;
