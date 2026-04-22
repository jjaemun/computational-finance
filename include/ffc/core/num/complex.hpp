#pragma once


#include <limits>
#include "ffc/core/num/concepts.hpp"


namespace ffc::core::num::complex {
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
