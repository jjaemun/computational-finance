#pragma once


#include <limits>
#include "ffc/core/num/concepts.hpp"


namespace ffc::core::num {
    /// Constants and properties of integral types.
    ///
    /// `IntTraits<T>` represents the canonical source of truth for known 
    /// properties of an integral type. 
    ///
    ///```c++
    /// namespace integral = ffc::core::num::integral;
    /// 
    /// // largest representable i64.
    /// auto max64i = integral::IntTraits<i64>::MAX;
    /// // bits for u32.
    /// auto bits32u = integral::IntTraits<u32>::BITS;
    ///
    /// (...) // are all contained.
    /// ```
    ///
    /// The template is restricted so that instantiating `IntTraits<T>`
    /// for a non-`IntType<T>` is a hard compile error. 
    ///
    ///```c++
    /// namespace integral = ffc::core::num::integral;
    ///
    /// // compiles.
    /// auto max8i = integral::IntTraits<i8>::MAX;
    /// // fails.
    /// auto max32f = integral::IntTraits<f32>::MAX;
    /// ```
    template <typename T>
        requires
            (IntType<T>)
    struct IntTraits final {
        /// Largest value that can be represented by `IntType<T>`.
        /// 
        /// `IntTraits<T>::MAX` is useful for upper bound checking or
        /// sentinel values in running minimum computations.
        ///
        ///```c++
        /// namespace integral = ffc::core::num::integral;
        ///
        /// // running min.
        /// i64 min = integral::IntTraits<i64>::MAX;
        /// for (auto value : values)
        ///     min = std::min(min, value);
        ///
        /// (...)
        /// ```
        static constexpr auto MAX{std::numeric_limits<T>::max()};

        /// Smallest value that can be represented by `IntType<T>`.
        /// 
        /// `IntTraits<T>::MIN` is useful for lower bound checking or
        /// sentinel values in running maximum computations.
        ///
        ///```c++
        /// namespace integral = ffc::core::num::integral;
        ///
        /// // running max.
        /// i64 max = integral::IntTraits<i64>::MIN;
        /// for (auto value : values)
        ///     max = std::max(max, value);
        ///
        /// (...)
        ///```
        static constexpr auto MIN{std::numeric_limits<T>::lowest()};

        /// Size of `IntType<T>` expressed in bytes.
        ///
        /// Often required for low-level memory (allocation etc.) 
        /// applications or in SIMD contexts (register packing etc.).
        ///
        /// ```c++
        /// namespace integral = ffc::core::num::integral;
        ///
        /// template <typename T>
        ///     requires 
        ///         (IntType<T>)
        /// constexpr auto avx2_int_lanes = 32uz / integral::IntTraits<T>::BYTES;
        ///```
        static constexpr auto BYTES{sizeof(T)};

        /// Size of `IntType<T>` expressed in bits.
        static constexpr auto BITS{sizeof(T) * 8uz};
    };

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
    /// // machine epsilon for f32.
    /// auto eps32f = fp::FpTraits<f32>::EPSILON;
    ///
    /// (...) // are all contained.
    /// ```
    ///
    /// The template is restricted so that instantiating `FpTraits<T>`
    /// for a non-`FpType<T>` is a hard compile error. 
    ///
    ///```c++
    /// namespace fp = ffc::core::num::fp;
    ///
    /// // compiles.
    /// auto max32f = fp::FpTraits<f32>::MAX;
    /// // fails.
    /// auto max8i = fp::FpTraits<i8>::MAX;
    /// ```
    template <typename T>
        requires
            (FpType<T>)
    struct FpTraits final {
        /// Largest finite value that can be represented by `FpType<T>`.
        /// 
        /// `FpTraits<T>::MAX` is useful for upper finite bound checking or
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
        static constexpr auto MAX{std::numeric_limits<T>::max()};

        /// Smallest positive normal value representable as `FpType<T>`.
        ///
        /// `FpTraits<T>::MIN_POSITIVE` is the *normal* value closest to zero. 
        ///  Can be used as a threshold for fp absolute comparisons near it.
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
        static constexpr auto MIN_POSITIVE{std::numeric_limits<T>::min()}; 

        /// Smallest finite value that can be represented by `FpType<T>`.
        /// 
        /// `FpTraits<T>::MIN` is useful for lower finite bound checking or
        /// sentinel values in running maximum computations.
        ///
        ///```c++
        /// namespace fp = ffc::core::num::fp;
        ///
        /// // running max.
        /// f64 max = fp::FpTraits<f64>::MIN;
        /// for (auto val : values)
        ///     max = std::max(max, val);
        ///
        /// (...)
        ///```
        static constexpr auto MIN{std::numeric_limits<T>::lowest()};

        /// Positive Infinity.
        ///
        /// `FpTraits<T>::INF` follows ieee754 conventions, in the 
        /// sense that `INF + var = INF` for any `FpType<T>` `var`.
        static constexpr auto INF{std::numeric_limits<T>::infinity()};

        /// Negative infinity.
        ///
        /// It is the additive inverse of `FpTraits<T>::INF`, and follows
        /// the same ieee754 conventions.
        static constexpr auto NEG_INF{-std::numeric_limits<T>::infinity()};

        /// Radix (base) of the fp number internal representation.
        ///
        /// ieee754 fp numbers should have binary (2) radix. For tracing
        /// purposes mostly.
        ///
        ///```c++
        /// #include <cassert>
        ///
        /// namespace fp = ffc::core::num::fp;
        /// 
        /// // strong enforcement of ieee754.
        /// assert(fp::FpTraits<T>::RADIX == 2);
        ///```
        static constexpr auto RADIX{std::numeric_limits<T>::radix};

        /// Number of base-10 significant digits that can be represented 
        /// without change. 
        ///
        /// `FpTraits<T>::DIGITS` is a conservative measure of decimal 
        /// precision. Additional decimals may not be preserved exactly.
        static constexpr auto DIGITS{std::numeric_limits<T>::digits10};

        /// Number of base-10 significant digits required to preserve 
        /// identity. 
        ///
        /// The following are equivalent:
        /// - `FpType<T>` satisfy uniqueness up to MAX_DIGITS significant 
        ///    digits.
        /// - Round-trip `FpType<T>` -> decimal -> `FpType<T>` conversions 
        ///   are lossless iff `FpType<T>` holds MAX_DIGITS.
        ///
        /// ```c++
        /// #include <cassert>
        /// #include <sstream>
        /// #include <iomanip>
        ///
        /// namespace fp = ffc::core::num::fp;
        ///
        /// const f64 value = 1.0 / 10.0;
        /// std::ostringstream output;
        /// output << std::setprecision(fp::FpTraits<f64>::MAX_DIGITS) << value;
        ///
        /// std::istringstream input{output.str()};
        /// f64 recovered{};
        /// input >> recovered;
        ///
        /// assert(value == recovered);
        /// ```
        static constexpr auto MAX_DIGITS{std::numeric_limits<T>::max_digits10};

        /// Quiet ieee754 (i.e., non-signaling) NAN representation.
        static constexpr auto QUIET_NAN{std::numeric_limits<T>::quiet_NaN()};
        
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
        ///     requires 
        ///         (FpType<T>)
        /// inline bool cmp_approx_eq(T lhs, T rhs) noexcept {
        ///     return std::abs(lhs - rhs) <= fp::FpTraits<T>::EPSILON * std::abs(lhs);
        /// }
        ///```
        static constexpr auto EPSILON{std::numeric_limits<T>::epsilon()};

        /// Size of `FpType<T>` expressed in bytes.
        ///
        /// Often required for low-level memory (allocation etc.) 
        /// applications or in SIMD contexts (register packing etc.).
        ///
        /// ```c++
        /// namespace fp = ffc::core::num::fp;
        ///
        /// template <typename T>
        ///     requires 
        ///         (FpType<T>)
        /// constexpr auto avx2_fp_lanes = 32uz / fp::FpTraits<T>::BYTES;
        ///```
        static constexpr auto BYTES{sizeof(T)};

        /// Size of `FpType<T>` expressed in bits.
        static constexpr auto BITS{sizeof(T) * 8uz};
    };

    /// Constants and properties of complex types.
    ///
    /// `ComplexTraits<T>` represents the canonical source of truth for
    /// known properties of any complex type. 
    ///
    ///```c++
    /// namespace complex = ffc::core::num::complex;
    /// 
    /// // bits for c64.
    /// auto bits64c = complex::ComplexTraits<c64>::BITS;
    /// // bytes for a c128.
    /// auto bytes128c = complex::ComplexTraits<c128>::BYTES;
    ///
    /// (...) // are all contained.
    /// ```
    ///
    /// `std::complex` is templated on an underlying scalar type. 
    /// `ComplexTraits<T>` therefore exposes properties derived from it
    /// and from the layout of the complex type itself. 
    /// 
    /// The template is restricted so that instantiating `ComplexTraits<T>`
    /// for a non-`ComplexType<T>` is a hard compile error. 
    ///
    ///```c++
    /// namespace complex = ffc::core::num::complex;
    ///
    /// // compiles.
    /// auto bytes64c = complex::ComplexTraits<c64>::BYTES;
    /// // fails.
    /// auto bits32f = complex::ComplexTraits<f32>::BITS;
    /// ```
    template <typename T>
        requires
            (ComplexType<T>)
    struct ComplexTraits {
        /// `ComplexType<T>` type alias.
        using Type = T;
        
        /// Scalar component type of `ComplexType<T>`.
        using ScalarType = typename T::value_type;
    
        /// Size of `ComplexType<T>` expressed in bytes.
        ///
        /// Often required for low-level memory (allocation etc.) 
        /// applications or fixed-width storage assumptions.
        ///
        /// ```c++
        /// namespace complex = ffc::core::num::complex;
        ///
        /// // byte offset needed to advance n `ComplexType<T>` elements.
        /// template <typename T>
        ///     requires 
        ///         (ComplexType<T>)
        /// constexpr auto offset_as_bytes(T n) noexcept {
        ///     return complex::ComplexTraits<T>::BYTES * n;
        /// }
        ///```
        static constexpr auto BYTES{sizeof(T)};

        /// Size of `ComplexType<T>` expressed in bits.
        static constexpr auto BITS{sizeof(T) * 8uz};
    };
} // namespace ffc::core::num
