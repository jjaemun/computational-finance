#pragma once


#include <limits>


namespace ffc::core::num {
    using f64 = double;
    static_assert(sizeof(f64) == 8uz);

    namespace fp::f64 {
        /// Largest finite value that can be represented by `f64`.
        constexpr auto MAX{std::numeric_limits<f64>::max()};

        /// Smallest finite positive value representable by `f64`.
        constexpr auto MIN_POSITIVE{std::numeric_limits<f64>::min()}; 

        /// Smallest finite value that can be represented by `f64`.
        constexpr auto MIN{std::numeric_limits<f64>::lowest()};

        /// Infinity.
        constexpr auto INFINITY{std::numeric_limits<f64>::infinity()};

        /// Negative infinity.
        constexpr auto NEG_INFINITY{-std::numeric_limits<f64>::infinity()};

        /// The base of the internal representation for an iee754 64-bit
        /// floating point number, i.e., the radix.
        constexpr auto RADIX{std::numeric_limits<f64>::radix};

        /// Number of base-10 significant digits. 
        ///
        /// Denotes the largest base-10 quantity for which a round trip
        /// conversion `f64` -> decimal -> `f64` is lossless.
        ///
        /// ```c++
        ///
        /// // safe! 
        /// const f64 safe = 1.2345678912345;
        /// // 15 signigicant digits preserved.
        /// assert(safe == 1.2345678912345);
        ///
        /// // unsafe!
        /// const f64 unsafe = 1.23456789123456;
        /// // 16th signigicant digit might be lost.
        /// ```
        constexpr auto DIGITS{std::numeric_limits<f64>::digits10};

        /// Quiet iee754 (i.e., non-signaling) nan representation.
        constexpr auto QUIET_NAN{std::numeric_limits<f64>::quiet_NaN()};
        
        /// Machine epsilon for `f64`.
        ///
        /// Represents the distance between 1.0 and the next larger floating 
        /// point number. Used as a relative error tolerance in numerical
        /// comparisons. Do **not** use for absolute comparisons near zero, 
        /// use MIN_POSITIVE instead.
        constexpr auto EPSILON{std::numeric_limits<f64>::epsilon()};

        /// Size of `f64` expressed in bytes.
        constexpr auto BYTES{sizeof(f64)};

        /// Size of `f64` expressed in bits.
        constexpr auto BITS{sizeof(f64) * 8uz};

        /// Sign bit mask for `f64`.
        constexpr auto SIGN_MASK{0x8000'0000'0000'0000ULL};

        /// Exponent mask for `f64`.
        constexpr auto EXP_MASK{0x7ff0'0000'0000'0000ULL};

        /// Mantissa mask for `f64`.
        constexpr auto MANTISSA_MASK{0x000f'ffff'ffff'ffffULL};
    } // namespace fp::f64;
} // namespace ffc::core::num;
