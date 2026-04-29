#pragma once 


#include <array>
#include <cmath>
#include <utility>
#include <type_traits>

#include "ffc/core/num/num.hpp"


namespace ffc::core::approx {
    /// Compile-time Horner polynomial evaluation object for 
    /// floating point coefficients.
    ///
    /// `Horner` is a zero cost abstraction enabling possibly compile-time
    /// polynomial evaluations. It is a building block for numerical kernels.
    ///
    /// ```c++
    /// using namespace ffc::core::approx;
    ///
    /// static constexpr Horner polynomial{
    ///     1.0, 2.0, 
    ///     3.0, 4.0,
    /// };
    ///
    /// auto eval = polynomial(0.5);
    ///```
    template <typename... Coeffs>
        requires
            ((core::num::FpType<Coeffs>) && ...)
    class Horner final {

        template <typename... Types>
        using type = std::common_type_t<Types...>;

    public:
        constexpr Horner(Coeffs&&... coeffs_) noexcept
            : coeffs{ std::forward<Coeffs>(coeffs_)... } {}

        [[nodiscard]]
        #if defined(__GNUC__) || defined(__clang__)
        __attribute__((always_inline))
        #elif defined(_MSC_VER)
        [[msvc::forceinline]]
        #endif
        constexpr type<Coeffs...> operator()(const type<Coeffs...> u) const noexcept {
            auto ret = (type<Coeffs...>)0.0;
            for (auto it = coeffs.rbegin(); it != coeffs.rend(); ++it)
                ret = std::fma(ret, u, *it);

            return ret;
        }

    private:
        std::array<type<Coeffs...>, sizeof...(Coeffs)> coeffs;
    };
} // namespace ffc::core::approx
