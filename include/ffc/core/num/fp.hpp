#pragma once


#include <limits>
#include "ffc/core/num/traits.hpp"


namespace ffc::core::num::fp {
    /// Constants and properties of floating-point types.
    ///
    /// `FpTraits<T>` represents the canonical source of truth for known 
    /// properties of a fp type. 
    ///
    ///```c++
    /// namespace fp = ffc::core::num::fp;
    /// 
    /// // largest finite f64.
    /// fp::f64::MAX
    /// // macheps for f32.
    /// fp::f32::EPSILON
    /// // ... are all contained.
    /// ```
    ///
    /// The primary template is undefined so that instantiating `FpTraits<T>`
    /// for a non-`FpType<T>` is a hard compile error. 
    ///
    ///```c++
    ///
    /// // compiles.
    /// auto max32f = FpTraits<f32>::MAX;
    ///
    /// // fails.
    /// auto max8i = FpTraits<i8>::MAX;
    /// ```
    template <typename T>
    requires(FpType<T>)
    struct FpTraits final {
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
        /// # Examples
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
        /// comparisons. 
        ///
        /// ** Use MIN_POSITIVE instead for absolute comparisons near zero **
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
} // namespace ffc::core::num;
