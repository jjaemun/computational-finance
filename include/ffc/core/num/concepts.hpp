#pragma once


#include <complex>
#include <concepts>
#include <type_traits>


namespace ffc::core::num {
    /// Satisfied by integral scalar types.
    /// 
    /// `IntType<T>` holds iff `T` models `std::integral<T>`.
    ///
    ///```c++
    ///
    /// // compiles.
    /// static_assert(IntType<i32>);
    ///
    /// // fails.
    /// static_assert(IntType<f64>);
    /// ```
    template <typename T>
    concept IntType = std::integral<T>;

    /// Satisfied by signed integral types.
    /// 
    /// `SignedIntType<T>` holds iff `T` models both `std::integral<T>`
    /// and `std::signed_integral<T>`.
    ///
    ///```c++
    ///
    /// // compiles.
    /// static_assert(SignedIntType<i32>);
    ///
    /// // fails.
    /// static_assert(SignedIntType<u32>);
    /// ```
    template <typename T>
    concept SignedIntType = IntType<T> 
        && std::signed_integral<T>;

    /// Satisfied by unsigned integral types.
    /// 
    /// `UnsignedIntType<T>` holds iff `T` models `std::integral<T>`
    /// but *not* `std::signed_integral<T>`.
    ///
    ///```c++
    ///
    /// // compiles.
    /// static_assert(UnsignedIntType<u32>);
    ///
    /// // fails.
    /// static_assert(UnsignedIntType<i32>);
    /// ```
    template <typename T>
    concept UnsignedIntType = IntType<T> 
        && !std::signed_integral<T>;

    /// Satisfied by floating point scalar types.
    /// 
    /// `FpType<T>` holds iff `T` models `std::floating_point<T>`
    ///
    ///```c++
    ///
    /// // compiles.
    /// static_assert(FpType<f32>);
    ///
    /// // fails.
    /// static_assert(FpType<i64>);
    /// ```
    template <typename T>
    concept FpType = std::floating_point<T>;

    /// Satisfied by `std::complex<U>` specializations.
    /// 
    /// `ComplexType<T>` holds iff `T` models `std::complex<U>`
    /// for some valid scalar type `U`.
    template <typename T>
    concept ComplexType = requires {
            typename std::remove_cvref_t<T>::value_type; 
        } &&  std::same_as<
                std::remove_cvref_t<T>, 
                std::complex<typename std::remove_cvref_t<T>::value_type>>;

    /// Satisfied by `std::complex<U>` specializations whose scalar
    /// type is floating-point.
    /// 
    /// `FpComplexType<T>` holds iff `T` models `std::complex<U>` for some
    /// scalar type `U` such that `FpType<U>` holds.
    ///  
    ///```c++
    ///
    /// // compiles.
    /// static_assert(FpComplexType<c64>);
    ///
    /// // fails.
    /// static_assert(FpComplexType<f64>);
    /// ```
    template <typename T>
    concept FpComplexType = ComplexType<T> 
        && FpType<typename std::remove_cvref_t<T>::value_type>;
} // namespace ffc::core::num.


