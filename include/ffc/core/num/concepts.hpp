#pragma once


#include <complex>
#include <concepts>
#include <type_traits>


namespace ffc::core::num {
    /// Satistfied by signed integral types.
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
    concept SignedIntType = std::integral<T> 
        && std::signed_integral<T>;

    /// Satistfied by unsigned integral types.
    /// 
    /// `UnsignedIntType<T>` holds iff `T` models `std::integral<T>`
    /// and but *not* `std::signed_integral<T>`.
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
    concept UnsignedIntType = std::integral<T> 
        && !std::signed_integral<T>;

    /// Satistfied by floating point scalar types.
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

    /// Satistfied by `std::complex<U>` specializations.
    /// 
    /// `ComplexType<T>` holds iff `T` models `std::complex<U>`
    /// for some valid scalar type `U`.
    template <typename T>
    concept ComplexType = requires { 
            typename std::remove_cvref_t<T>::value_type; 
        } &&  std::same_as<
                std::remove_cvref_t<T>, 
                std::complex<typename std::remove_cvref_t<T>::value_type>>;

    /// Satistfied by `std::complex<U>` specializations whose scalar
    /// type is floating-point.
    /// 
    /// `FpComplexType<T>` holds iff `T` models `std::complex<U>`for some
    /// scalar type `U` verifying `FpType<U>`.
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
    concept FpComplexType =  FpType<typename T::value_type> 
        && ComplexType<T>;
} // namespace ffc::core::num.


