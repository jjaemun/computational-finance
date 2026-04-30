#include <gtest/gtest.h>


#include <ranges>
#include <vector>


#include "ffc/types.hpp"
#include "ffc/core/num/traits.hpp"
#include "ffc/core/specfun/norminv.hpp"


namespace {
    namespace core = ffc::core;

    TEST(norminv_specfuntest, EdgeBehavior) {
        auto lb = f64{0.0}; 
        EXPECT_EQ(core::specfun::norminv(lb), 
                  core::num::FpTraits<ffc::f64>::NEG_INF);

        auto median = f64{0.5};
        EXPECT_DOUBLE_EQ(core::norminv(median), f64{0.0});
        
        auto ub = f64{1.0}; 
        EXPECT_EQ(core::specfun::norminv(ub), 
                  core::num::FpTraits<ffc::f64>::INF);
    }


    inline auto linspaced(f64 from, f64 to, usize count) noexcept {
    
        // Constructs a uniform partition, i.e., linspaced, of the 
        // interval [from, to]. Expects from < to.
        
        const auto delta = (to - from) /
            static_cast<f64>(count);

        std::vector<f64> grid(count + 1);
        for (auto i : std::views::iota((usize)0, count + 1))
            grid[i] = from + (i * delta);
    
        return grid;
    }

    TEST(norminv_specfuntest, MonotoneBehavior) {
        const auto grid = linspaced(f64{1e-6}, f64{1.0 - 1e-6}, 128uz);

        for (const auto [prev, curr] : grid | std::views::pairwise) 
            EXPECT_LT(core::norminv(prev), core::norminv(curr));
    }

    TEST(norminv_specfuntest, SymmetryBehavior) {
        constexpr std::array<f64, 5> probs{
            1e-8, 1e-6,
            1e-5, 1e-4,
            1e-2, 1e-1
        };

        for (const auto p : probs) {
            const auto quantile = core::norminv(f64{1.0} - p);
            const auto mirrored = -core::norminv(p);

            EXPECT_NEAR(quantile, mirrored, 1e-10);
        }
    }
}
