#pragma once 


#include <array>
#include <cmath>
#include <utility>
#include <type_traits>

#include "ffc/core/num/num.hpp"


namespace ffc::core::approx {
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
        #elif defined(_MSC_VER)


            /**
             * If available, forcing inline improves performance, but is
             * generally superfluous.
             */

        __forceinline
        #if defined(__GNUC__) || defined(__clang__)
        __attribute__((always_inline))
        #endif
        constexpr type<Coeffs...> operator()(const type<Coeffs...> u) const noexcept {
   
            /**
             * `std::fma` is chosen to reduce rounding errors.
             */

            auto ret = (type<Coeffs...>)0.0;
            for (auto it = coeffs.rbegin(); it != coeffs.rend(); ++it)
                ret = std::fma(ret, u, *it);

            return ret;
        }

    private:
        std::array<type<Coeffs...>, sizeof...(Coeffs)> coeffs;
    };

    template <typename... Coeffs>
    Horner(Coeffs...) -> Horner<Coeffs...>;
} // namespace ffc::core::approx
