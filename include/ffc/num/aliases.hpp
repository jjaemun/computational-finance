#pragma once


#include <complex>
#include <cstdint>
#include <cstddef>


#include "ffc/core/num/num.hpp"


namespace ffc {
    using usize = std::size_t;
    using isize = std::ptrdiff_t;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using f32 = float;
    using f64 = double;

    using c64 = std::complex<f32>;
    using c128 = std::complex<f64>;
} // namespace ffc
