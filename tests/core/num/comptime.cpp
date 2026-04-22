#include <gtest/gtest.h>
#include "ffc/core/num/num.hpp"


namespace {
    template <typename...Types>
        requires
            ((ffc::IntType<Types>) && ...)
    constexpr bool integrals = true;

    template <typename... Types>
        requires
            ((!ffc::IntType<Types>) && ...)
    constexpr bool nonintegrals = true;
            
    TEST(comptime, IntTypeConcept) {
        static_assert(
            integrals<
                ffc::usize,
                ffc::isize,
                
                ffc::u8,
                ffc::u16,
                ffc::u32,
                ffc::u64,
        
                ffc::i8,
                ffc::i16,
                ffc::i32,
                ffc::i64
            >
        );
            
        static_assert(
            nonintegrals<
                ffc::f32,
                ffc::f64,
        
                ffc::c64,
                ffc::c128
            >
        );

        EXPECT_TRUE(true);
    }
     
    template <typename... Types>
        requires
            ((ffc::UnsignedIntType<Types>) && ...)
    constexpr bool unsignedints = true;   

    template <typename...Types>
        requires
            ((ffc::SignedIntType<Types>) && ...)
    constexpr bool signedints = true;

    TEST(comptime, IntTypeSignednessConcept) {
        static_assert(
            signedints <
                ffc::isize,
                
                ffc::i8,
                ffc::i16,
                ffc::i32,
                ffc::i64
            >
        );
            
        static_assert(
            unsignedints <
                ffc::usize,
                
                ffc::u8,
                ffc::u16,
                ffc::u32,
                ffc::u64
            >
        );

        EXPECT_TRUE(true);
    }

    template <typename...Types>
        requires
            ((ffc::FpType<Types>) && ...)
    constexpr bool fps = true;

    template <typename... Types>
        requires
            ((!ffc::FpType<Types>) && ...)
    constexpr bool nonfps = true;
            
    TEST(comptime, FpTypeConcept) {
        static_assert(
            fps<
                ffc::f32,
                ffc::f64
            >
        );

        static_assert(
            nonfps<
                ffc::usize,
                ffc::isize,
                
                ffc::u8,
                ffc::u16,
                ffc::u32,
                ffc::u64,
        
                ffc::i8,
                ffc::i16,
                ffc::i32,
                ffc::i64,

                ffc::c64,
                ffc::c128
            >
        );

        EXPECT_TRUE(true);
    }

    template <typename...Types>
        requires
            ((ffc::ComplexType<Types>) && ...)
    constexpr bool complex = true;

    template <typename... Types>
        requires
            ((!ffc::ComplexType<Types>) && ...)
    constexpr bool noncomplex = true;
            
    TEST(comptime, ComplexTypeConcept) {
        static_assert(
            complex<
                ffc::c64,
                ffc::c128,
            >
        );

        static_assert(
            noncomplex<
                ffc::usize,
                ffc::isize,
                
                ffc::u8,
                ffc::u16,
                ffc::u32,
                ffc::u64,
        
                ffc::i8,
                ffc::i16,
                ffc::i32,
                ffc::i64,

                ffc::32,
                ffc::f64
            >
        );

        EXPECT_TRUE(true);
    }
}
