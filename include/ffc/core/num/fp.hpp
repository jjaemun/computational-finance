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
    /// auto max64f = fp::FpTraits<f64>::MAX;
    /// // macheps for f32.
    /// auto eps32f = fp::FpTraits<f32>::EPSILON;
    ///
    /// (...) // are all contained.
    /// ```
    ///
    /// The primary template is undefined so that instantiating `FpTraits<T>`
    /// for a non-`FpType<T>` is a hard compile error. 
    ///
    ///```c++
    /// namespace fp = ffc::core::num::fp;
    ///
    /// // compiles.
    /// auto max32f = fp::FpTraits<f32>::MAX;
    ///
    /// // fails.
    /// auto max8i = fp::FpTraits<i8>::MAX;
    /// ```
    template <typename T>
        requires
            (FpType<T>)
    struct FpTraits final {
        /// Largest finite value that can be represented by `FpType<T>`.
        /// 
        /// `FpTraits<T>::MAX` is useful for overflow bound checking or
        /// sentinel values in running minimum computations.
        ///
        ///```c++
        /// namespace fp = ffc::core::num::fp;
        ///
        /// // running min.
        /// f64 min = fp::FpTraits<f64>::MAX;
        /// for (auto val : values)
        ///     min = std::min(min, val);
        ///
        /// (...)
        /// ```
        constexpr auto MAX{std::numeric_limits<T>::max()};

        /// Smallest positive (normal) value representable as `FpType<T>`.
        ///
        /// `FpTraits<T>::MIN_POSITIVE` is the normal value closest to zero 
        ///  therefore it is the safe threshold for fp absolute comparisons near it.
        ///
        ///```c++
        /// namespace fp = ffc::core::num::fp;
        ///
        /// template <typename T>
        ///     requires FpType<T>
        /// inline bool near_zero(T fp) noexcept {
        ///     return std::abs(fp) <= fp::FpTraits<T>::MIN_POSITIVE;
        /// }
        /// ```
        constexpr auto MIN_POSITIVE{std::numeric_limits<T>::min()}; 

        /// Smallest finite value that can be represented by `FpType<T>`.
        /// 
        /// `FpTraits<T>::MAX` is useful for underflow bound checking or
        /// sentinel values in running maximum computations.
        ///
        ///```c++
        /// namespace fp = ffc::core::num::fp;
        ///
        /// // running max.
        /// f64 max = fp::FpTraits<f64>::MIN;
        /// for (auto val : values)
        ///     max = std::max(min, val);
        ///
        /// (...)
        ///```
        constexpr auto MIN{std::numeric_limits<T>::lowest()};

        /// Positive Infinity.
        ///
        /// `FpTraits<T>::INFINITY` follows ieee754 conventions, in the 
        /// sense that `INFINITY + var = INFINITY` for any `FpType<T>` `var`.
        constexpr auto INFINITY{std::numeric_limits<T>::infinity()};

        /// Negative infinity.
        ///
        /// `FpTraits<T>::NEG_INFINITY` is the additive inverse of INFINITY, 
        /// and follows the same ieee754 conventions.
        constexpr auto NEG_INFINITY{-std::numeric_limits<T>::infinity()};

        /// Radix (base) of the fp number internal representation.
        ///
        /// ieee754 fp numbers should have binary (2) radix. For tracing
        /// purposes only, to check whether the bit masks below are valid.
        ///
        ///```c++
        /// #include <cassert>
        ///
        /// namespace fp = ffc::core::num::fp;
        /// 
        /// // strong enforcement of ieee754.
        /// assert(fp::FpTraits<T>::RADIX == 2);
        ///```
        constexpr auto RADIX{std::numeric_limits<T>::radix};

        /// Number of base-10 significant digits. 
        ///
        /// A round-trip `f64` -> decimal -> `f64` conversion is lossless
        /// with at most `FpTraits<T>::DIGITS` significant digits. 
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
        constexpr auto DIGITS{std::numeric_limits<T>::digits10};

        /// Quiet iee754 (i.e., non-signaling) NAN representation.
        constexpr auto QUIET_NAN{std::numeric_limits<T>::quiet_NaN()};
        
        /// Machine epsilon for `FpType<T>`.
        ///
        /// Represents the distance between `1.0` and the next larger fp
        /// `FpType<T>`. Used as a relative error tolerance in numerical
        /// comparisons. 
        ///
        /// ** Use MIN_POSITIVE instead for absolute comparisons near zero **
        ///
        ///```c++
        /// namespace fp = ffc::core::num::fp;
        ///
        /// template <typename T>
        ///     requires FpType<T>
        /// inline bool cmp_approx_eq(T lhs, T rhs) noexcept {
        ///     return (std::abs(lhs - rhs) <= fp::FpTraits<T>::EPSILON * std::abs(lhs);
        /// }
        ///```
        constexpr auto EPSILON{std::numeric_limits<T>::epsilon()};

        /// Size of `FpType<T>` expressed in bytes.
        ///
        /// Often required for low-level memory (allocation etc.) 
        /// applications or in SIMD contexts (register packing etc.).
        ///
        /// ```c++
        /// namespace fp = ffc::core::num::fp;
        /// 
        /// template <typename T>
        ///     requires FpType<T>
        /// constexpr auto lanes = 32uz / fp::FpTraits<T>::BYTES;
        constexpr auto BYTES{sizeof(T)};

        /// Size of `FpType<T>` expressed in bits.
        constexpr auto BITS{sizeof(T) * 8uz};
} // namespace ffc::core::num;
