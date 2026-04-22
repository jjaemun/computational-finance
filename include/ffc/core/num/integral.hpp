#pragma once


#include <limits>
#include "ffc/core/num/concepts.hpp"


namespace ffc::core::num::integral {
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
} // namespace ffc::core::num::integral.
