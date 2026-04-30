#include <gtest/gtest.h>


#include <array>
#include <cmath>
#include <ranges>


#include "ffc/types.hpp"
#include "ffc/core/approx/horner.hpp"


namespace {
    namespace core = ffc::core::approx;


    template <typename T, const ffc::usize N>
    inline T expected(const std::array<T, N> &coeffs, T arg) noexcept {
        
        // Naive horner polynommial evaluation.
        
        auto RET = (T)0.0;
        for (const auto &coeff : coeffs | std::views::reverse)
    //                                    ^~~~~~~~~~~~~~~~~~~ notice that Horner requires that
    //                                                        that the coefficients be traversed in reverse.
            RET = std::fma(RET, arg, coeff);
    //      ^~~   ~~~~~~~~~~~~~~~~~~~~~~~~~ similarly, std::fma is used to check that we 
    //                                      achieve the same results.
        return RET;
    }



    TEST(horner_approxtest, TrivialExecTest) {
        std::array<ffc::f64, 8uz> coeffs{
            1.0, 2.0,
            3.0, 4.0,
            5.0, 6.0,
            7.0, 8.0
        };

        core::Horner horner{
            coeffs[0], coeffs[1],
            coeffs[2], coeffs[3],
            coeffs[4], coeffs[5],
            coeffs[6], coeffs[7]
        };

        ffc::f64 arg{1.0};

        EXPECT_DOUBLE_EQ(horner(arg), expected(coeffs, arg));
    }
}
