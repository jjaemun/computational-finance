#pragma once


#include "ffc/core/types.hpp"
#include "ffc/core/ptr/repr.hpp"


namespace ffc::core::ptr {
    /// Strong unsigned integer representation of a pointer value.
    ///
    /// `uptr` wraps `ffc::core::ptr::repr::uptr` to provide an explicit type
    /// for byte-oriented pointer-representation arithmetic.
    ///
    /// `uptr` is the internal means for:
    /// - Explicit pointer-to-integer repr conversion
    /// - Byte offsets
    /// - Typed offsets
    /// - Bit masks
    ///
    /// `uptr` is **not** a pointer. Additionally, it has no implications about ownership,
    /// validity, lifetime, dereferenceability, or provenance of any represented address.
    ///
    /// ```c++
    /// #include <cassert>
    /// using namespace ffc::core::ptr;
    ///     
    /// constexpr isize OFFSET{8};
    ///
    /// struct Foo {
    ///     i32 bar;
    /// };
    ///
    /// Foo *foo = new Foo{};
    ///
    /// // explicit integer repr of pointer value.
    /// uptr addr = uptr::from_ptr(foo);
    /// // byte displacement.
    /// uptr displaced = addr.offset_bytes(OFFSET);
    ///
    /// assert(OFFSET == addr.byte_offset_from(displaced));
    ///```
    ///
    /// Operations are on integer representations of pointer values and therefore
    /// do not establish that any converted pointer can be safely dereferenced.
    class uptr final {
    private:
        repr::uptr value{};
            
    public:
        /// Default-constructs a zero-valued pointer representation.
        ///
        /// The underlying member `value` uses its in-class value-initializer,
        /// preventing an unspecified raw representation, i.e., garbage bit values.
        /// 
        /// ```c++
        /// using namespace ffc::core::ptr;
        /// 
        /// { uptr foo; }
        /// { uptr foo{}; }
        /// uptr(); 
        /// uptr{};
        ///```
        ///
        /// `uptr` is both `default` and `nothrow` default-constructible.
        constexpr uptr() noexcept = default;
       
        /// Constructs `uptr` from raw `repr::uptr` unsigned pointer representation.
        ///
        /// It is marked `explicit` so that raw integer representations are not
        /// implicitly cast as address-style values.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        /// 
        /// const auto raw = reinterpret_cast<repr::uptr>(ptr);
        ///
        /// // compiles.
        /// {  uptr addr{raw}; }
        ///
        /// // fails.
        /// {  uptr addr = raw; }
        /// //      ^~~~   ~~~ illegal implicit cast!
        /// ```
        constexpr explicit uptr(repr::uptr value_) noexcept 
            : value{value_} {} 

        
        /// Constructs `uptr` from a `usize`.
        ///
        /// `uptr::from_usize()` is a convenience named-constructor whenever the source
        /// is already expressed in the framework's unsigned size/count type.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        /// 
        /// usize addr{0xff};
        /// auto faddr = uptr::from_usize(addr);
        /// ```
        /// 
        /// Conversion is only in terms of representation. It does not preserve a valid
        /// pointer state or safe dereferenceability.
        [[nodiscard]]
        static constexpr uptr from_usize(usize addr) noexcept {
            return uptr{static_cast<repr::uptr>(addr)};
        }
        
        /// Constructs `uptr` from an object pointer.
        ///
        /// `uptr::from_ptr()` is the preferred named-constructor whenever the source
        /// is an actual object pointer. The resulting `uptr` models the source `ptr`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        /// 
        /// i64 foo{};
        /// auto faddr = uptr::from_ptr(&foo);
        /// ```
        /// 
        /// Conversion is only in terms of representation. It does not preserve a valid
        /// pointer state or safe dereferenceability.
        template <typename T>
        [[nodiscard]]
        static uptr from_ptr(T *ptr) noexcept {
            return uptr{reinterpret_cast<repr::uptr>(ptr)};
        }

        /// Constructs `uptr` from a const object pointer.
        ///
        /// `uptr::from_const_ptr()` is the preferred named-constructor whenever the source
        /// is an actual const object pointer. The resulting `uptr` models the source `ptr`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        /// 
        /// const i64 foo{};
        /// auto faddr = uptr::from_const_ptr(&foo);
        /// ```
        /// 
        /// Conversion is only in terms of representation. It does not preserve a valid
        /// pointer state or safe dereferenceability.
        template <typename T>
        [[nodiscard]]
        static uptr from_const_ptr(const T *ptr) noexcept {
            return uptr{reinterpret_cast<repr::uptr>(ptr)};
        }
       
        /// Constructs zero-valued `uptr` unsigned pointer representation.
        ///
        /// `uptr::zero()` is equivalent to default construction, but can be
        /// clearer at call site when an explicit zero representation is intended.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// auto nullish = uptr::zero();
        /// ```
        [[nodiscard]]
        static constexpr uptr zero() noexcept {
            return uptr{};
        }

        /// Converts the stored `repr::uptr` unsigned representation to `T*`.
        ///
        /// If the address modelled by `uptr` is not valid, out of bounds, or unsafe to 
        /// dereference, using the resulting pointer can result in UB.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        ///
        /// i64 *fptr = addr.as_ptr<i64>();
        /// ```
        template <typename T>
        [[nodiscard]]
        T *as_ptr() const noexcept {
            return reinterpret_cast<T*>(value);
        }

        /// Converts the stored `repr::uptr` unsigned representation to `const T*`.
        ///
        /// If the address modelled by `uptr` is not valid, out of bounds or unsafe to 
        /// dereference, using the resulting pointer can result in UB.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const i64 foo{};
        /// uptr addr = uptr::from_const_ptr(&foo);
        ///
        /// const i64 *fptr = addr.as_const_ptr<i64>();
        /// ```
        template <typename T>
        [[nodiscard]]
        const T *as_const_ptr() const noexcept {
            return reinterpret_cast<const T*>(value);
        }
        
        /// Returns the underlying raw `repr::uptr`.
        ///
        /// It is the value-returning accessor for the stored unsigned representation.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        ///
        /// repr::uptr raw = addr.to_unsigned();
        /// ```
        [[nodiscard]]
        constexpr repr::uptr to_unsigned() const noexcept {
            return value;
        }

        /// Returns an immutable reference to the underlying raw `repr::uptr`.
        ///
        /// This accessor should be preferred only when direct immutable access
        /// to the stored representation is required. Because `repr::uptr` is
        /// trivially copyable, `to_unsigned()` is generally the clearer default.
        [[nodiscard]]
        constexpr repr::uptr const &as_unsigned() const noexcept {
            return value;
        }

        /// Returns a mutable reference to the underlying raw `repr::uptr`.
        ///
        /// **Unsafe**. It is the caller's responsibility to preserve `uptr` assumptions downstream. 
        [[nodiscard]]
        constexpr repr::uptr &as_mut_unsigned() noexcept {
            return value;
        }

        /// Returns the stored unsigned pointer representation as `usize`.
        [[nodiscard]]
        constexpr usize to_usize() const noexcept {
            return static_cast<usize>(value);
        }

        /// Returns a new `uptr` advanced by `count` bytes.
        ///
        /// Adds an unsigned byte offset to a pointer representation.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr advanced = addr.byte_add(16uz);
        /// ```
        ///
        /// This is a pure representation-space operation. It does not imply
        /// that the resulting representation corresponds to a valid pointer.
        [[nodiscard]]
        constexpr uptr byte_add(usize count) const noexcept {
            return uptr{value + static_cast<repr::uptr>(count)};
        }
        
        /// Returns a new `uptr` advanced by `count` elements of `T`.
        ///
        /// Adds an unsigned typed offset to a pointer representation. It is
        /// equivalent to advancing the underlying representation by
        /// `count * sizeof(T)` bytes.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr advanced = addr.add<i64>(2uz);
        /// ```
        ///
        /// This operation is unchecked. If the offset, when computed in bytes, overflows
        /// `usize`, the value wraps, invoking specified but undesired behaviour.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const usize count = (2uz << 64uz) - 1uz;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr _ = addr.add<i64>(count);
        /// //            ^~~~~~~~~~~~~~~ wraps by unsigned integer overflow.
        /// //   
        /// //   Equivalently (e.g., in an LP-64 system):
        /// //   
        /// //   /    usize bytes = count * sizeof(T);
        /// //   |                  ----------------- overflows 64 bits and wraps to min \
        /// //   |                                    min value.
        /// //   | 
        /// //   |    uptr RET = addr.byte_add(bytes);
        /// //   |         ^~~   ~~~~~~~~~~~~~~~~~~~~ now binds the wrapped byte offset  \
        /// //   |                                    and no longer models the intended  \
        /// //   |                                    displacement.
        /// //   |___ 
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr uptr add(usize count) const noexcept {
            return byte_add(count * sizeof(T));
        }

        /// Returns a new `uptr` moved backward by `count` bytes.
        ///
        /// Subtracts an unsigned byte offset from a pointer representation.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr regressed = addr.byte_sub(16uz);
        /// ```
        ///
        /// This is a pure representation-space operation. It does not imply
        /// that the resulting representation corresponds to a valid pointer.
        [[nodiscard]]
        constexpr uptr byte_sub(usize count) const noexcept {
            return uptr{value - static_cast<repr::uptr>(count)};
        }

        /// Returns a new `uptr` moved backward by `count` elements of `T`.
        ///
        /// Subtracts an unsigned typed offset from a pointer representation. It is equivalent
        /// to regressing the underlying representation by `count * sizeof(T)` bytes.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr regressed = addr.sub<i64>(2uz);
        /// ```
        ///
        /// This operation is unchecked. If the offset, when computed in bytes, overflows
        /// `usize`, the value wraps, invoking specified but undesired behaviour.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const usize count = (2uz << 64uz) - 1uz;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr _ = addr.sub<i64>(count);
        /// //            ^~~~~~~~~~~~~~~ wraps by unsigned integer overflow.
        /// //
        /// //   Equivalently (e.g., in an LP-64 system):
        /// //
        /// //   /    usize bytes = count * sizeof(T);
        /// //   |                  ----------------- overflows 64 bits and wraps to min \
        /// //   |                                    value.
        /// //   |
        /// //   |    uptr RET = addr.byte_sub(bytes);
        /// //   |         ^~~   ~~~~~~~~~~~~~~~~~~~~ now binds the wrapped byte offset  \
        /// //   |                                    and no longer models the intended  \
        /// //   |                                    displacement.
        /// //   |___ 
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr uptr sub(usize count) const noexcept {
            return byte_sub(count * sizeof(T));
        }
        
        /// Returns a new `uptr` displaced by signed byte offset.
        ///
        /// Delegates to `byte_add()` and `byte_sub()` for advancing and regressing representations.
        ///
        /// ```c++
        /// #include <cassert>
        /// using namespace ffc::core::ptr;
        /// 
        /// uptr nullish = uptr::zero();
        /// uptr advance = nullish.offset_bytes(64);
        /// uptr regress = advance.offset_bytes(-8);
        /// ```
        ///
        /// This operation is branched to prevent negative offsets being directly cast as 
        /// unsigned representations. In the negative case, the pattern 
        ///
        /// ```c++
        /// 
        /// auto _ = static_cast<usize>(-(neg + 1u)) + 1u);
        /// ```
        ///
        /// follows from the fact that negating the most negative signed value directly in
        /// a same-width signed integer is UB.
        [[nodiscard]]
        constexpr uptr offset_bytes(isize bytes) const noexcept {
            if (bytes >= 0)
                return byte_add(static_cast<usize>(bytes));

            return byte_sub(static_cast<usize>(-(bytes + 1u)) + 1u);
        }

        /// Returns a new `uptr` displaced by signed offset expressed, given by
        /// `count` units of `T`.
        ///
        /// Positive values advance the representation by `count * sizeof(T)`
        /// bytes, while negative values move it backward by the same rule.
        template <typename T>
        [[nodiscard]]
        constexpr uptr offset(isize count) const noexcept {
            return offset_bytes(count * static_cast<isize>(sizeof(T)));
        }

        /// Returns signed byte displacement from the current representation
        /// to `origin`.
        ///
        /// The operation is branched explicitly because subtraction occurs in unsigned 
        /// representation space, while the result is a signed displacement.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// u8 foo{};
        /// u8 bar{};
        ///
        /// uptr fptr = uptr::from_ptr(&foo);
        /// uptr bptr = uptr::from_ptr(&bar);
        ///
        /// isize displacement = fptr.byte_offset_from(bptr);
        /// ```
        [[nodiscard]]
        constexpr isize byte_offset_from(uptr origin) const noexcept {
            if (origin.to_unsigned() >= value)
                return static_cast<isize>(origin.to_unsigned() - value);

            return -static_cast<isize>(value - origin.as_unsigned());
        }

        /// Returns signed byte displacement from the current representation
        /// to pointer `origin`.
        ///
        /// It is a convenience wrapper that delegates to `byte_offset_from()`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// u8 buffer[0xff];
        /// uptr addr = uptr::from_ptr(&buffer[0xf]);
        ///
        /// isize displacement = addr.byte_offset_from_ptr(&buffer[0]);
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr isize byte_offset_from_ptr(T *origin) const noexcept {
            return byte_offset_from(uptr::from_ptr(origin));
        }

        /// Returns signed byte displacement from the current representation
        /// to const pointer `origin`.
        ///
        /// It is a convenience wrapper that delegates to `byte_offset_from()`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const u64 buffer[0xff];
        /// uptr addr = uptr::from_const_ptr(&buffer[0xf]);
        ///
        /// isize displacement = addr.byte_offset_from_const_ptr(&buffer[0]);
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr isize byte_offset_from_const_ptr(T const *origin) const noexcept {
            return byte_offset_from(uptr::from_const_ptr(origin));
        }

        /// Returns signed displacement from the current representation to
        /// `origin` expressed in units of `sizeof(T)`.
        ///
        /// It is equivalent to `byte_offset_from(origin) / sizeof(T)`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const u8 buffer[0xff];
        /// uptr origin = uptr::from_ptr(&buffer[0]);
        /// uptr addr = uptr::from_ptr(&buffer[0xf]);
        ///
        /// isize displacement = addr.offset_from<u8>(origin);
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr isize offset_from(uptr origin) const noexcept {
            return byte_offset_from(origin) / static_cast<isize>(sizeof(T));
        }

        /// Returns signed displacement from the current representation to
        /// pointer `origin` expressed in units of `sizeof(T)`.
        ///
        /// This is a convenience wrapper over `offset_from<T>(uptr)`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// u8 buffer[0xff];
        /// uptr addr = uptr::from_ptr(&buffer[0xf]);
        ///
        /// isize displacement = addr.offset_from_ptr(&buffer[0]);
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr isize offset_from_ptr(T *origin) const noexcept {
            return offset_from<T>(uptr::from_ptr(origin));
        }

        /// Returns signed displacement from the current representation to
        /// const pointer `origin` expressed in units of `sizeof(T)`.
        ///
        /// This is a convenience wrapper over `offset_from<T>(uptr)`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const u8 buffer[0xff];
        /// uptr addr = uptr::from_const_ptr(&buffer[0xf]);
        ///
        /// isize displacement = addr.offset_from_const_ptr(&buffer[0]);
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr isize offset_from_const_ptr(T const *origin) const noexcept {
            return offset_from<T>(uptr::from_const_ptr(origin));
        }

        /// Returns a new `uptr` produced by bitwise-AND with `other`.
        ///
        /// `bit_and()` is useful for explicit masking and alignment-style
        /// address-representation manipulation.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// uptr addr = uptr::from_usize(0xffuz);
        /// uptr mask = uptr::from_usize(0x0fuz);
        ///
        /// uptr masked = addr.bit_and(mask);
        /// ```
        [[nodiscard]]
        constexpr uptr bit_and(uptr other) const noexcept {
            return uptr{ value & other.value };
        }

        /// Returns a new `uptr` produced by bitwise-OR with `other`.
        ///
        /// `bit_or()` is useful whenever address representations carry
        /// flag bits or are intentionally combined at the bit level.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// uptr lhs = uptr::from_usize(0xf0uz);
        /// uptr rhs = uptr::from_usize(0x0fuz);
        ///
        /// uptr combined = lhs.bit_or(rhs);
        /// ```
        [[nodiscard]]
        constexpr uptr bit_or(uptr other) const noexcept {
            return uptr{ value | other.value };
        }

        /// Returns a new `uptr` produced by bitwise-XOR with `other`.
        ///
        /// `bit_xor()` is useful when explicitly toggling or comparing
        /// differing bit regions of address representations.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// uptr lhs = uptr::from_usize(0xf0uz);
        /// uptr rhs = uptr::from_usize(0x0fuz);
        ///
        /// uptr toggled = lhs.bit_xor(rhs);
        /// ```
        [[nodiscard]]
        constexpr uptr bit_xor(uptr other) const noexcept {
            return uptr{ value ^ other.value };
        }

        /// Returns a new `uptr` produced by bitwise-NOT.
        ///
        /// `bit_not()` complements the full stored unsigned pointer
        /// representation bit pattern.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// uptr addr = uptr::from_usize(0x0fuz);
        /// auto compl = addr.bit_not();
        /// ```
        [[nodiscard]]
        constexpr uptr bit_not() const noexcept {
            return uptr{ ~value };
        }

        /// Returns a new `uptr` masked by `bitmask`.
        ///
        /// Applies a bitwise-AND between the current pointer representation and the
        /// representation stored in `bitmask`.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// uptr addr = uptr::from_usize(0xff);
        /// uptr mask = uptr::from_usize(0x0f);
        ///
        /// uptr masked = addr.mask(mask);
        /// ```
        ///
        /// This is a pure representation-space operation. It does not imply
        /// that the resulting representation corresponds to a valid pointer.
        [[nodiscard]]
        constexpr uptr mask(uptr bitmask) const noexcept {
            return bit_and(bitmask);
        }
   };
} // namespace ffc::core::ptr
