#include <gtest/gtest.h>


#include <array>
#include <cmath>
#include <ranges>
#include <vector>


#include "ffc/types.hpp"
#include "ffc/core/num/num.hpp"
#include "ffc/core/specfun/norminv.hpp"


#define INF ffc::core::num::FpTraits<ffc::f64>::INF 
#define NEG_INF ffc::core::num::FpTraits<ffc::f64>::NEG_INF


namespace {
    namespace core = ffc::core;
   
    constexpr std::array<ffc::f64, 34> probabilities{
        0.0,
     // ----+ lower limit value.
    
        1e-12,
        1e-11,
        1e-10,
        1e-9,
        1e-8,
        1e-7,
        1e-6,
        1e-5,
        1e-4,
        1e-3,
        1e-2,
        1e-1,
     // ----+ extreme left tail.

        2e-1,
        3e-1,
        4e-1,
        5e-1,
        6e-1,
        7e-1,
        8e-1,
        9e-1,
     // ----+ central region.

        1.0 - 1e-1,
        1.0 - 1e-2,
        1.0 - 1e-3,
        1.0 - 1e-4,
        1.0 - 1e-5,
        1.0 - 1e-6,
        1.0 - 1e-7,
        1.0 - 1e-8,
        1.0 - 1e-9,
        1.0 - 1e-10,
        1.0 - 1e-11,
        1.0 - 1e-12,
     // -----------+ extreme right tail.

        1.0
     // ----+ upper limit value.
    };

    TEST(norminv_specfuntest, BoundaryBehaviour) {
        using ffc::core::specfun::norminv;

        EXPECT_EQ(norminv(probabilities.front()), NEG_INF);
        EXPECT_EQ(norminv(probabilities.back()), INF);
    }

    TEST(norminv_specfuntest, Monotone) {
        using ffc::core::specfun::norminv;
        
        # if defined(__cpp_lib_ranges_zip)
        for (const auto [prev, curr] : probabilities | std::views::pairwise) 
            EXPECT_LE(norminv(prev), norminv(curr);
        #endif
    }

    TEST(norminv_specfuntest, Symmetric) {
        using ffc::core::specfun::norminv;

        for (const auto probability : probabilities) {
            const auto quantile = norminv(1.0 - probability);
            const auto mirrored = -norminv(probability);

            EXPECT_NEAR(quantile, mirrored, 1e-5);
        }
    }

   TEST(norminv_specfuntest, CriticalProbabilities) {
        using ffc::core::specfun::norminv;
        
        EXPECT_NEAR(norminv(0.8413447460685429), 1.0, 1e-12);
        EXPECT_NEAR(norminv(0.1586552539314571), -1.0, 1e-12);

        EXPECT_NEAR(norminv(0.9772498680518208), 2.0, 1e-12);
        EXPECT_NEAR(norminv(0.0227501319481792), -2.0, 1e-12);

        EXPECT_NEAR(norminv(0.9986501019683699), 3.0, 1e-11);
        EXPECT_NEAR(norminv(0.0013498980316301), -3.0, 1e-11);
    }
}


#undef INF
#undef NEG_INF
