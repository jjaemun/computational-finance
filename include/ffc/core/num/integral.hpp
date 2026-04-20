#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace ffc::core::num {
    // platform dependent.
    using usize = std::size_t;
    using isize = std::ptrdiff_t;

    using u8  = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    static_assert(sizeof(u8)  == 1uz);
    static_assert(sizeof(u16) == 2uz);
    static_assert(sizeof(u32) == 4uz);
    static_assert(sizeof(u64) == 8uz);

    using i8  = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    static_assert(sizeof(i8)  == 1uz);
    static_assert(sizeof(i16) == 2uz);
    static_assert(sizeof(i32) == 4uz);
    static_assert(sizeof(i64) == 8uz);

    namespace integral::usize {
        constexpr auto MAX{std::numeric_limits<usize>::max()};
        constexpr auto MIN{std::numeric_limits<usize>::min()};
        constexpr auto BYTES{sizeof(usize)};
        constexpr auto BITS{sizeof(usize) * 8uz};
    } // namespace integral::usize

    namespace integral::isize {
        constexpr auto MAX{std::numeric_limits<isize>::max()};
        constexpr auto MIN{std::numeric_limits<isize>::min()};
        constexpr auto BYTES{sizeof(isize)};
        constexpr auto BITS{sizeof(isize) * 8uz};
    } // namespace integral::isize

    namespace integral::u8 {
        constexpr auto MAX{std::numeric_limits<u8>::max()};
        constexpr auto MIN{std::numeric_limits<u8>::min()};
        constexpr auto BYTES{sizeof(u8)};
        constexpr auto BITS{sizeof(u8) * 8uz};
    } // namespace integral::u8

    namespace integral::u16 {
        constexpr auto MAX{std::numeric_limits<u16>::max()};
        constexpr auto MIN{std::numeric_limits<u16>::min()};
        constexpr auto BYTES{sizeof(u16)};
        constexpr auto BITS{sizeof(u16) * 8uz};
    } // namespace integral::u16

    namespace integral::u32 {
        constexpr auto MAX{std::numeric_limits<u32>::max()};
        constexpr auto MIN{std::numeric_limits<u32>::min()};
        constexpr auto BYTES{sizeof(u32)};
        constexpr auto BITS{sizeof(u32) * 8uz};
    } // namespace integral::u32

    namespace integral::u64 {
        constexpr auto MAX{std::numeric_limits<u64>::max()};
        constexpr auto MIN{std::numeric_limits<u64>::min()};
        constexpr auto BYTES{sizeof(u64)};
        constexpr auto BITS{sizeof(u64) * 8uz};
    } // namespace integral::u64

    namespace integral::i8 {
        constexpr auto MAX{std::numeric_limits<i8>::max()};
        constexpr auto MIN{std::numeric_limits<i8>::min()};
        constexpr auto BYTES{sizeof(i8)};
        constexpr auto BITS{sizeof(i8) * 8uz};
    } // namespace integral::i8

    namespace integral::i16 {
        constexpr auto MAX{std::numeric_limits<i16>::max()};
        constexpr auto MIN{std::numeric_limits<i16>::min()};
        constexpr auto BYTES{sizeof(i16)};
        constexpr auto BITS{sizeof(i16) * 8uz};
    } // namespace integral::i16

    namespace integral::i32 {
        constexpr auto MAX{std::numeric_limits<i32>::max()};
        constexpr auto MIN{std::numeric_limits<i32>::min()};
        constexpr auto BYTES{sizeof(i32)};
        constexpr auto BITS{sizeof(i32) * 8uz};
    } // namespace integral::i32

    namespace integral::i64 {
        constexpr auto MAX{std::numeric_limits<i64>::max()};
        constexpr auto MIN{std::numeric_limits<i64>::min()};
        constexpr auto BYTES{sizeof(i64)};
        constexpr auto BITS{sizeof(i64) * 8uz};
    } // namespace integral::i64
} // namespace ffc::core::num
