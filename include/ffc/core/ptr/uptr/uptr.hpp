#pragma once


#include "ffc/core/num/num.hpp"
#include "ffc/core/ptr/repr.hpp"


namespace ffc::core::ptr {
    /// Strong unsigned integer representation of a pointer value.
    ///
    /// `uptr` wraps `ffc::core::ptr::repr::uptr` to provide an explicit type
    /// for byte pointer-representation arithmetic. 
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
    /// constexpr isize OFFSET{32};
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
    /// do not establish that any converted pointer can be safely to dereferenced.
    class uptr final {
    private:
        repr::uptr value{};
            
    public:
        /// Default-constructs of a zero-valued pointer representation.
        ///
        /// The underlying member `value` uses its in-class value-initializer preventing
        /// an unspecified raw representation, i.e., garbage bit values.
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
        /// `uptr` is therefore both `default` and `nothrow` default-constructible. 
        constexpr uptr() noexcept = default;
       
        /// Constructs `uptr` from raw `repr::uptr` unsigned pointer representation.
        ///
        /// It enforces that raw integers are not implicitly cast as address
        /// values. 
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

        /// Constructs zero-valued `uptr` unsigned pointer representation.
        ///
        /// `uptr::zero()` is equivalent to the default construcutor, only 
        /// more explicit, and clearer.
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
            return reinterpret_cast<T const*>(value);
        }
        
        /// Returns the underlying raw underlying `repr::uptr`.
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
        /// Should be preferred only for direct immutable access to the underlying
        /// representation is required without copying. Because `repr::uptr` is trivially
        /// copyable, it should be used sparsely and intently instead of `to_unsigned()`.
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
        /// Adds an unsigned typed offset to a pointer representation. It is equivalent 
        /// to advancing underlying representation by `count * sizeof(T)` bytes.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr advanced = addr.add<i64>(2uz);
        /// ```
        ///
        /// This operation is unchecked. If the offset when computed as bytes overflows a 
        /// `usize`, the value wraps, invoking specified but undesired behaviour.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const usize count = (2uz << 59uz) + 1uz;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr _ = addr.add<i64>(count);
        /// //            ^~~~~~~~~~~~~~~ wraps by unsigned integer overflow.
        /// //   
        /// //   Equivalently (e.g., in an LP-64 system):
        /// //   
        /// //   /    usize bytes = count * sizeof(T);
        /// //   |                  ----------------- ((2^64) + 1) overflows 64-bits \
        /// //   |                                    and wraps to min value.
        /// //   | 
        /// //   |    uptr RET = addr.byte_add(bytes);
        /// //   |         ^~~ now binds to wrapped value and no longer models the \
        /// //   |             intended address. 
        /// //   |___ 
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr uptr add(usize count) const noexcept {
            return byte_add(count * sizeof(T));
        }

        /// Returns a new `uptr` regressed by `count` bytes.
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
        /// Subtracts an unsigned typed offset from a pointer representation. It is
        /// equivalent to regressing underlying representation by
        /// `count * sizeof(T)` bytes.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr regressed = addr.sub<i64>(2uz);
        /// ```
        ///
        /// This operation is unchecked. If the offset when computed as bytes overflows a
        /// `usize`, the value wraps, invoking specified but undesired behaviour.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// const usize count = (2uz << 59uz) + 1uz;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        /// uptr _ = addr.sub<i64>(count);
        /// //            ^~~~~~~~~~~~~~~ wraps by unsigned integer overflow.
        /// //
        /// //   Equivalently (e.g., in an LP-64 system):
        /// //
        /// //   /    usize bytes = count * sizeof(T);
        /// //   |                  ----------------- ((2^64) + 1) overflows 64 bits \
        /// //   |                                    and wraps to min value.
        /// //   |
        /// //   |    uptr RET = addr.byte_sub(bytes);
        /// //   |         ^~~ now binds to wrapped value and no longer models the \
        /// //   |             intended address.
        /// //   |___
        /// ```
        template <typename T>
        [[nodiscard]]
        constexpr uptr sub(usize count) const noexcept {
            return byte_sub(count * sizeof(T));
        }

        /// Returns a new `uptr` displaced by signed byte offset.
        ///
        /// Positive values advance the representation, while negative values
        /// move it backward.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 foo{};
        /// uptr addr = uptr::from_ptr(&foo);
        ///
        /// uptr fore = addr.offset_bytes(32);
        /// uptr back = addr.offset_bytes(-16);
        /// ```
        ///
        template <typename T>
        [[nodiscard]]
        constexpr uptr offset(isize count) const noexcept {
            return offset_bytes(count * static_cast<isize>(sizeof(T)));
        }

        [[nodiscard]]
        constexpr uptr offset_bytes(isize bytes) const noexcept {
            if (bytes >= 0)
                return byte_add(static_cast<usize>(bytes));

            return byte_sub(static_cast<usize>(-(bytes + 1u)) + 1u);
        }

        /// Returns a new `uptr` displaced by signed offset expressed in
        /// units of `sizeof(T)`.
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
        /// The result is computed as `origin - current`, expressed in bytes.
        /// The operation is branched explicitly because subtraction occurs on
        /// the unsigned representation layer, while the result is a signed
        /// displacement.
        ///
        /// ```c++
        /// using namespace ffc::core::ptr;
        ///
        /// i64 lhs{};
        /// i64 rhs{};
        ///
        /// uptr a = uptr::from_ptr(&lhs);
        /// uptr b = uptr::from_ptr(&rhs);
        ///
        /// isize disp = a.byte_offset_from(b);
        /// ```
        [[nodiscard]]
        constexpr isize byte_offset_from(uptr origin) const noexcept {
            if (origin.to_unsigned() >= value)
                return static_cast<isize>(origin.to_unsigned() - value);

            return -static_cast<isize>(value - origin.as_unsigned());
        }

        /// Returns signed byte displacement from the current representation
        /// to `origin`.
        template <typename T>
        [[nodiscard]]
        constexpr isize byte_offset_from_ptr(T *origin) const noexcept {
            return byte_offset_from(uptr::from_ptr(origin));
        }

        /// Returns signed byte displacement from the current representation
        /// to `origin`.
        template <typename T>
        [[nodiscard]]
        constexpr isize byte_offset_from_const_ptr(T const *origin) const noexcept {
            return byte_offset_from(uptr::from_const_ptr(origin));
        }

        /// Returns signed displacement from the current representation to
        /// `origin` expressed in units of `sizeof(T)`.
        ///
        /// This is equivalent to `byte_offset_from(origin) / sizeof(T)`.
        template<typename T>
        [[nodiscard]]
        constexpr isize offset_from(uptr origin) const noexcept {
            return byte_offset_from(origin) / sizeof(T);
        }

        /// Returns signed displacement from the current representation to
        /// `origin` expressed in units of `sizeof(T)`.
        template <typename T>
        [[nodiscard]]
        constexpr isize offset_from_ptr(T *origin) const noexcept {
            return offset_from<T>(uptr::from_ptr(origin));
        }

        /// Returns signed displacement from the current representation to
        /// `origin` expressed in units of `sizeof(T)`.
        template <typename T>
        [[nodiscard]]
        constexpr isize offset_from_const_ptr(T const *origin) const noexcept {
            return offset_from<T>(uptr::from_const_ptr(origin));
        }
   };
} // namespace ffc::core::ptr
