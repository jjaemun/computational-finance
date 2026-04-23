#pragma once 


#include <cstdint>


namespace ffc::core::ptr::repr {
    #if !(defined(UINTPTR_MAX))
    #error "error! repr::uptr requires std::uintptr_t." 
    #endif 
    
    /// Raw unsigned integer representation type for object pointer values.
    ///     
    /// `repr::uptr` aliases `std::uintptr_t`, which is an *optional*, implementation
    /// defined unsigned integer capable of holding pointer values.
    ///
    /// It is only a raw representation type for pointer-address arithmetic. In 
    /// `ffc::core::ptr` it provides an explicit unsigned integer type for pointers, 
    /// and some elementary operations around them. 
    ///
    /// ```c++
    ///  using namespace ffc::core::ptr;
    ///     
    /// const repr::uptr ALIGNMASK{63u};
    ///
    /// struct Foo { 
    ///     int bar; 
    /// };
    ///
    /// Foo *foo = new Foo{};
    /// repr::uptr addr = reinterpret_cast<repr::uptr>(foo);
    /// 
    /// // align ptr to 64 bytes
    /// repr::uptr aligned = (addr + ALIGNMASK) & ~ALIGNMASK;
    /// ```
    ///
    /// `repr::uptr` does not hold any implications about ownership, lifetime, validity,
    /// dereferenceability, or provenance. It should not be taken as a portable
    /// physical address format, but rather a low-level primitive for pointer machinery.
    /// 
    /// A numeric value alone is *not* sufficient to establish that a converted
    /// pointer may be safely dereferenced.
    using uptr = std::uintptr_t;

    #if !(defined(INTPTR_MAX))
    #error "error! repr::iptr requires std::intptr_t." 
    #endif 

    /// Raw signed integer representation type for object pointer values.
    ///     
    /// `repr::iptr` aliases `std::intptr_t`, which is an *optional*, implementation
    /// defined signed integer capable of holding pointer values.
    ///
    /// It is only a raw representation type for signed pointer arithmetic. In 
    /// `ffc::core::ptr` it provides an explicit signed integer type for e.g., pointer
    /// displacement operations, whenever unrelated to sizes, counts, or indices.
    ///
    /// ```c++
    ///  using namespace ffc::core::ptr;
    ///     
    /// const repr::iptr BIT64CACHELINE{64};
    ///
    /// struct Foo { 
    ///     int bar; 
    /// };
    ///
    /// Foo *foo = new Foo{};
    /// repr::iptr addr = reinterpret_cast<repr::iptr>(foo);
    /// 
    /// // move integer repr by one signed cacheline offset
    /// repr::iptr preceding = addr - CACHELINE64BIT;
    /// ```
    ///
    /// `repr::uptr` does not hold any implications about ownership, lifetime, validity,
    /// dereferenceability, or provenance. It should not be taken as a portable
    /// physical address format, but rather a low-level primitive for pointer machinery.
    /// 
    /// A numeric value alone is *not* sufficient to establish that a converted
    /// pointer may be safely dereferenced.
    using iptr = std::intptr_t;
} // namespace ffc::core::ptr::repr
