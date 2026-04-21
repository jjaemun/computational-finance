#pragma once


#include <limits>
#include "ffc/core/num/fp.hpp"


namespace ffc::core::num {
    /// A 64-bit ieee754-style  floating-point number.
    /// 
    /// `f64` is an alias of `double` which enforces additional 
    /// guarantees at compile-time.
    ///
    /// The standard only guarantees that `double` be at least as
    /// precise as `float`, while binary layout, size and range are
    /// implementation-defined.
    using f64 = double;

    /// Compile time assert that the size of `f64` be 8 bytes, as on
    /// most sane platforms and implementations.
    static_assert(sizeof(f64) == 8uz);

    /// Compile time assert that the size of `f64` behaves 
    /// according to ieee754 semantics.
    ///
    /// Beware this does **not** fully prove ieee754 binary64 
    /// identity.
    ///
    /// Guarantees `f64` has a binary radix, supports (±)infinity,
    /// nan, signed zero, and ieee754 style behaviour for those.
    ///
    /// Does not guarantee `f64` has exact precision, exponent range,
    /// or prevents excess precision in intermediate computations.
    static_assert(std::numeric_limits<f64>::is_iec559);
   
    // Traits.
    using fp::f64 = fp::FpTraits<f64>;
} // namespace ffc::core::num;
