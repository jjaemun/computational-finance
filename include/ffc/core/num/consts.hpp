#pragma once


#include <concepts>
#include <numbers>


#include "ffc/core/num/f32.hpp"
#include "ffc/core/num/f64.hpp"


namespace ffc::core::num::consts {
    template <std::floating_point T>
    constexpr T E = std::numbers::e_v<T>;

    template <std::floating_point T>
    constexpr T LOG2_E = std::numbers::log2e_v<T>;

    template <std::floating_point T>
    constexpr T LOG10_E = std::numbers::log10e_v<T>;

    template <std::floating_point T>
    constexpr T PI = std::numbers::pi_v<T>;

    template <std::floating_point T>
    constexpr T INV_PI = std::numbers::inv_pi_v<T>;

    template <std::floating_point T>
    constexpr T INV_SQRT_PI = std::numbers::inv_sqrtpi_v<T>;

    template <std::floating_point T>
    constexpr T LN_2 = std::numbers::ln2_v<T>;

    template <std::floating_point T>
    constexpr T LN_10 = std::numbers::ln10_v<T>;

    template <std::floating_point T>
    constexpr T SQRT_2 = std::numbers::sqrt2_v<T>;

    template <std::floating_point T>
    constexpr T SQRT_3 = std::numbers::sqrt3_v<T>;

    template <std::floating_point T>
    constexpr T INV_SQRT_3 = std::numbers::inv_sqrt3_v<T>;

    template <std::floating_point T>
    constexpr T EGAMMA = std::numbers::egamma_v<T>;

    template <std::floating_point T>
    constexpr T PHI = std::numbers::phi_v<T>;
} // namespace ffc::core::num::consts.
