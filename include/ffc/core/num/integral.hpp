#pragma once


#include <cstdint>
#include <cstddef>

#include "ffc/core/num/traits.hpp"


namespace ffc::core::num {
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

    namespace integral {
        using usize = IntTraits<::ffc::core::num::usize>;
        using isize = IntTraits<::ffc::core::num::isize>;

        using u8 = IntTraits<::ffc::core::num::u8>;
        using u16 = IntTraits<::ffc::core::num::u16>;
        using u32 = IntTraits<::ffc::core::num::u32>;
        using u64 = IntTraits<::ffc::core::num::u64>;

        using i8 = IntTraits<::ffc::core::num::i8>;
        using i16 = IntTraits<::ffc::core::num::i16>;
        using i32 = IntTraits<::ffc::core::num::i32>;
        using i64 = IntTraits<::ffc::core::num::i64>;
    } // namespace integral
} // namespace ffc::core::num
