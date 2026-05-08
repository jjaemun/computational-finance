#pragma once


#include <cassert>
#include "ffc/core/types.hpp"
#include "ffc/core/ptr/uptr.hpp"


namespace ffc::core::mem::alignment {
    /// Returns whether `align` is a power of two.
    ///
    /// `is_power_of_two()` is the basic precondition for valid
    /// alignments. It must be **non**-zero.
    ///
    /// ```c++
    /// using namespace ffc::core::mem::alignment;
    ///
    /// // non-powers.
    /// static_assert(!is_power_of_two(0uz));
    /// static_assert(!is_power_of_two(3uz));
    ///
    /// // powers.
    /// static_assert(is_power_of_two(2uz));
    /// static_assert(is_power_of_two(8uz));
    /// ```
    [[nodiscard]]
    constexpr bool is_power_of_two(usize align) noexcept {
        return (align != 0uz) && ((align & (align - 1uz)) == 0uz);
    }

    /// Returns the bitmask for some alignment `align`.
    ///
    /// `align_mask()` computes `~(align - 1)` in `ptr::uptr` 
    /// representation space.
    /// 
    /// Expects a valid alignment.
    ///
    /// ```c++
    /// using namespace ffc::core::mem;
    ///
    /// constexpr auto mask = alignment::align_mask(8uz);
    /// static_assert(mask.to_usize() == ~7uz);
    /// ```
    [[nodiscard]]
    constexpr ptr::uptr align_mask(usize align) noexcept {
        assert(is_power_of_two(align));

        return ptr::uptr::from_usize(align - 1uz)
            .bit_not();
    }

    /// Returns the smallest aligned address not below `addr`.
    ///
    /// `align_up()` rounds `addr` upward to the next address
    /// satisfying the power-of-two alignment `align`. 
    ///
    /// It is a non-decreasing transform, in the sense that `addr`
    /// is returned unchanged if it is already aligned.
    ///
    /// Expects a valid alignment.
    ///
    /// ```c++
    /// using namespace ffc::core;
    ///
    /// constexpr auto addr = ptr::uptr::from_usize(13uz);
    /// constexpr auto aligned = mem::alignment::align_up(addr, 8uz);
    ///
    /// static_assert(aligned.to_usize() == 16uz);
    /// ```
    [[nodiscard]]
    constexpr ptr::uptr align_up(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        return addr
            .byte_add(align - 1uz)
            .mask(align_mask(align));
    }

    /// Returns the greatest aligned address not above `addr`.
    ///
    /// `align_down()` rounds `addr` downward to the previous
    /// address satisfying the power-of-two alignment `align`.
    ///
    /// It is a non-increasing transform. `addr` is returned unchanged 
    /// if it is already aligned.
    ///
    /// Expects a valid alignment.
    ///
    /// ```c++
    /// using namespace ffc::core;
    ///
    /// constexpr auto addr = ptr::uptr::from_usize(13uz);
    /// constexpr auto aligned = mem::alignment::align_down(addr, 8uz);
    ///
    /// static_assert(aligned.to_usize() == 8uz);
    /// ```
    [[nodiscard]]
    constexpr ptr::uptr align_down(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        return addr
            .mask(align_mask(align));
    }

    /// Returns whether `addr` is aligned to `align`.
    ///
    /// `is_aligned()` checks whether the low bits of `addr`
    /// permitted by `align` are zero.
    ///
    /// Expects a valid alignment.
    ///
    /// ```c++
    /// using namespace ffc::core;
    ///
    /// constexpr auto ALIGNMENT{8uz};
    ///
    /// {
    ///     constexpr auto addr = ptr::uptr::from_usize(16uz);
    ///     static_assert(mem::alignment::is_aligned(addr, ALIGNMENT));
    /// }
    /// {
    ///     constexpr auto addr = ptr::uptr::from_usize(9uz);
    ///     static_assert(!mem::alignment::is_aligned(addr, ALIGNMENT));
    /// }
    /// ```
    [[nodiscard]]
    constexpr bool is_aligned(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        const auto masked = addr
            .mask(ptr::uptr::from_usize(align - 1uz));

        return (masked.to_usize() == 0uz);
    }

    /// Returns the result of aligning pointer `ptr` upward.
    ///
    /// `align_up<T>()` is a typed pointer convenience that delegates
    /// to its `uptr` counterpart.
    template <typename T>
    [[nodiscard]]
    inline T *align_up(T *ptr, usize align) noexcept {
        return align_up(ptr::uptr::from_ptr(ptr), align)
            .as_ptr<T>();
    }

    /// Returns the result of aligning pointer `ptr` downward.
    ///
    /// `align_down<T>()` is a typed pointer convenience that delegates
    /// to its `uptr` counterpart.
    template <typename T>
    [[nodiscard]]
    inline T *align_down(T *ptr, usize align) noexcept {
        return align_down(ptr::uptr::from_ptr(ptr), align)
            .as_ptr<T>();
    }

    /// Returns the result of aligning const pointer `ptr` upward.
    ///
    /// This is a const typed pointer convenience overload delegating
    /// to `align_up(ptr::uptr, usize)`.
    template <typename T>
    [[nodiscard]]
    inline const T *align_up(const T *ptr, usize align) noexcept {
        return align_up(ptr::uptr::from_const_ptr(ptr), align)
            .as_const_ptr<T>();
    }

    /// Returns the result of aligning const pointer `ptr` downward.
    ///
    /// This is a const typed pointer convenience overload delegating
    /// to `align_down(ptr::uptr, usize)`.
    template <typename T>
    [[nodiscard]]
    inline const T *align_down(const T *ptr, usize align) noexcept {
        return align_down(ptr::uptr::from_const_ptr(ptr), align)
            .as_const_ptr<T>();
    }

    /// Returns the alignment requirement of `T`.
    ///
    /// `of<T>()` is a convenience wrapper over `alignof(T)`.
    ///
    /// ```c++
    /// using namespace ffc::core::mem;
    ///
    /// static_assert(alignment::of<f64>() == alignof(f64));
    /// ```
    template <typename T>
    [[nodiscard]]
    constexpr usize of() noexcept {
        return alignof(T);
    }

    /// Returns the alignment requirement of `T`.
    ///
    /// This value-based overload is equivalent to `of<T>()`.
    template <typename T>
    [[nodiscard]]
    constexpr usize of([[maybe_unused]] const T &_) noexcept {
        return alignof(T);
    }

    /// Returns the forward byte distance from `addr` to its aligned successor.
    ///
    /// `offset_to_alignment()` is zero exactly when `addr` is already aligned
    /// to `align`.
    ///
    /// Expects a valid alignment.
    ///
    /// ```c++
    /// using namespace ffc::core;
    ///
    /// constexpr auto addr = ptr::uptr::from_usize(13uz);
    /// static_assert(alignment::offset_to_alignment(addr, 8uz) == 3uz);
    /// ```
    [[nodiscard]]
    constexpr usize offset_to_alignment(ptr::uptr addr, usize align) noexcept {
        assert(is_power_of_two(align));

        return align_up(addr, align)
            .byte_offset_from(addr);
    }
} // namespace ffc::core::mem::alignment
