#pragma once 


#include <array>
#include <cmath>
#include <utility>
#include <type_traits>

#include "ffc/core/utils.hpp"
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
        #if defined(__GNUC__) || defined(__clang__)
            
            // If available, forcing inline improves performance, but is
            // generally superfluous.
        
        __attribute__((always_inline))
        #endif
        constexpr type<Coeffs...> operator()(const type<Coeffs...> u) const noexcept {
            
            // std::fma is chosen to reduce rounding errors. The performance hit 
            // of using stl machinery, e.g., std::views::reverse, is considerable 
            // since it prevents aggresive unrolling, therefore it is avoided.
            
            auto ret = (type<Coeffs...>)0.0;
            for (auto it = coeffs.rbegin(); it != coeffs.rend(); ++it)
                ret = std::fma(ret, u, *it);

            return ret;
        }

    private:
        std::array<type<Coeffs...>, sizeof...(Coeffs)> coeffs;
    };
} // namespace ffc::core::approx
