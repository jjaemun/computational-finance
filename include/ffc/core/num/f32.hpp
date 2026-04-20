#pragma once


#include <limits>


namespace ffc::core::num {
    using f32 = float;
    static_assert(sizeof(f32) == 4uz);

    namespace fp::f32 {
        constexpr auto MAX{std::numeric_limits<f32>::max()};
        constexpr auto MIN{std::numeric_limits<f32>::lowest()};
        constexpr auto MIN_POSITIVE{std::numeric_limits<f32>::min()}; 
        constexpr auto INF{std::numeric_limits<f32>::infinity()};
        constexpr auto NEG_INF{-std::numeric_limits<f32>::infinity()};
        constexpr auto RADIX{std::numeric_limits<f32>::radix};
        constexpr auto DIGITS10{std::numeric_limits<f32>::digits10};
        constexpr auto QUIET_NAN{std::numeric_limits<f32>::quiet_NaN()};
        constexpr auto EPSILON{std::numeric_limits<f32>::epsilon()};
        constexpr auto BYTES{sizeof(f32)};
        constexpr auto BITS{sizeof(f32) * 8uz};
        constexpr auto SIGN_MASK{0x8000'0000ULL};
        constexpr auto EXP_MASK{0x7f80'0000ULL};
        constexpr auto MANTISSA_MASK{0x007f'ffffULL};
    }
} // namespace ffc::core::num;
