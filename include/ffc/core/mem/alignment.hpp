#pragma once


#include <cassert>
#include "ffc/core/types.hpp"
#include "ffc/core/ptr/uptr.hpp"


namespace ffc::core::mem {
    [[nodiscard]]
    constexpr bool is_power_of_two(usize align) noexcept {
        return (align != 0uz) && ((align & (align - 1uz)) == 0uz);
    }

    [[nodiscard]]
    constexpr ptr::uptr align_mask(usize align) noexcept {
        assert(is_power_of_two(align));

        return ptr::uptr::from_usize(align - 1uz)
            .bit_not();
    }

    [[nodiscard]]
    constexpr ptr::uptr align_up(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        return addr
            .byte_add(align - 1uz)
            .mask(align_mask(align));
    }

    [[nodiscard]]
    constexpr ptr::uptr align_down(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        return addr
            .mask(align_mask(align));
    }

    [[nodiscard]]
    constexpr bool is_aligned(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        const auto masked = addr
            .mask(ptr::uptr::from_usize(align - 1uz));

        return (masked.to_usize() == 0uz);
    }

    template <typename T>
    [[nodiscard]]
    inline T *align_up(T *ptr, usize align) noexcept {
        return align_up(ptr::uptr::from_ptr(ptr), align)
            .as_ptr<T>();
    }

    template <typename T>
    [[nodiscard]]
    inline T *align_down(T *ptr, usize align) noexcept {
        return align_down(ptr::uptr::from_ptr(ptr), align)
            .as_ptr<T>();
    }

    template <typename T>
    [[nodiscard]]
    inline const T *align_up(const T *ptr, usize align) noexcept {
        return align_up(ptr::uptr::from_const_ptr(ptr), align)
            .as_const_ptr<T>();
    }

    template <typename T>
    [[nodiscard]]
    inline const T *align_down(const T *ptr, usize align) noexcept {
        return align_down(ptr::uptr::from_const_ptr(ptr), align)
            .as_const_ptr<T>();
    }

    template <typename T>
    [[nodiscard]]
    constexpr usize of() noexcept {
        return alignof(T);
    }

    template <typename T>
    [[nodiscard]]
    constexpr usize of([[maybe_unused]] const T &_) noexcept {
        return alignof(T);
    }

    [[nodiscard]]
    constexpr usize offset_to_alignment(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        return align_up(addr, align)
            .byte_offset_from(addr);
    }
} // namespace ffc::core::mem
