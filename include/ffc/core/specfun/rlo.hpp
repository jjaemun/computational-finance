#pragma once

#include <cmath>


#include "ffc/core/types.hpp"
#include "ffc/core/approx/horner.hpp"
#include "ffc/core/num/traits.hpp"


namespace ffc::core::specfun {
    [[nodiscard]]
    #if defined(_MSC_VER)

        // If available, forcing inline improves performance, but
        // is generally superfluous.

    __forceinline
    #elif defined(__GNUC__) || defined(__clang__)
    __attribute__((hot, always_inline))
    #endif
    inline f64 rlog1(const f64 u) noexcept {

        // ALGO. 708 TOMS (Didonato & Morris, 1992) VOL. 18, NO.3. 

        // open set boundaries.
        static constexpr auto leftbound = (f64)-0.39;
        static constexpr auto rightbound = (f64)0.57;

        // symmetrization boundary.
        static constexpr auto symmbound = (f64)0.18;

        // correction shifts.
        static constexpr auto leftshift = (f64)0.566749439387324e-1;
        static constexpr auto rightshift = (f64)0.456512608815524e-1;


        static constexpr approx::Horner p{
            (f64)0.333333333333333  ,
            (f64)-0.224696413112536 ,
            (f64)0.00620886815375787,
        };

        static constexpr approx::Horner q{
            (f64)1.0              ,
            (f64)-1.27408923933623,
            (f64)0.354508718369557,
        };

        if (u <= (f64)-1.0)
            return num::FpTraits<f64>::QUIET_NAN;

        // direct evaluation. 
        if (u < leftbound || rightbound < u)
            return u - std::log((f64)1.0 + u);

        f64 coordinate{}; 
        f64 correction{}; 
   
        // left region.
        if (u < -symmbound) {
            coordinate = (u + (f64)0.3) / 
                (f64)0.7;
            correction = leftshift - coordinate * 
                (f64)0.3;
        }

        // right region.
        else if (u > symmbound) {
            coordinate = (f64)0.75 * u - 
                (f64)0.25;
            correction = rightshift + coordinate / 
                (f64)3.0; 
        }

        // central region.
        else {
            coordinate = u;
            correction = (f64)0.0;
        }

        // transform to symmetrized domain.
        const auto mobius = u / (u + (f64)2.0);
        const auto even = mobius * mobius;
        const auto rational = p(even) / q(even);

        return even * (f64)2.0 * 
            ((f64)1.0 / ((f64)1 - mobius) - mobius * 
                rational) + correction;
        }
} // namespace ffc::core::specfun
