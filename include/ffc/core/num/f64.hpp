#pragma once


#include <numbers>
#include <limits>


namespace ffc::core::num {
    using f64 = double;
    static_assert(sizeof(f64) == 8uz);

    namespace fp::f64 {
        constexpr auto MAX{std::numeric_limits<f64>::max()};
        constexpr auto MIN{std::numeric_limits<f64>::lowest()};
        constexpr auto MIN_POSITIVE{std::numeric_limits<f64>::min()}; 
        constexpr auto INF{std::numeric_limits<f64>::infinity()};
        constexpr auto NEG_INF{-std::numeric_limits<f64>::infinity()};
        constexpr auto RADIX{std::numeric_limits<f64>::radix};
        constexpr auto DIGITS10{std::numeric_limits<f64>::digits10};
        constexpr auto NAN{std::numeric_limits<f64>::quiet_NaN()};
        constexpr auto EPSILON{std::numeric_limits<f64>::epsilon()};
        constexpr auto BYTES{sizeof(f64)};
        constexpr auto BITS{sizeof(f64) * 8uz};
        constexpr auto SIGN_MASK{0x8000'0000'0000'0000ULL};
        constexpr auto EXP_MASK{0x7ff0'0000'0000'0000ULL};
        constexpr auto MANTISSA_MASK{0x000f'ffff'ffff'ffffULL};
    } // namespace fp::f64;
} // namespace ffc::core::num;
