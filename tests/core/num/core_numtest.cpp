#include <gtest/gtest.h>

#include "ffc/num/types.hpp"
#include "ffc/core/num/num.hpp"


namespace {
    namespace core = ffc::core::num;
    
    template <typename...Types>
        requires
            ((core::IntType<Types>) && ...)
    constexpr bool integrals = true;

    template <typename... Types>
        requires
            ((!core::IntType<Types>) && ...)
    constexpr bool nonintegrals = true;
            
    TEST(numtest, IntTypeConcept) {
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
            ((core::UnsignedIntType<Types>) && ...)
    constexpr bool unsignedints = true;   

    template <typename...Types>
        requires
            ((core::SignedIntType<Types>) && ...)
    constexpr bool signedints = true;

    TEST(numtest, IntTypeSignednessConcept) {
        static_assert(
            signedints<
                ffc::isize,
                
                ffc::i8,
                ffc::i16,
                ffc::i32,
                ffc::i64
            >
        );
            
        static_assert(
            unsignedints<
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
            ((core::FpType<Types>) && ...)
    constexpr bool fps = true;

    template <typename... Types>
        requires
            ((!core::FpType<Types>) && ...)
    constexpr bool nonfps = true;
            
    TEST(numtest, FpTypeConcept) {
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
            ((core::ComplexType<Types>) && ...)
    constexpr bool complex = true;

    template <typename... Types>
        requires
            ((!core::ComplexType<Types>) && ...)
    constexpr bool noncomplex = true;
            
    TEST(numtest, ComplexTypeConcept) {
        static_assert(
            complex<
                ffc::c64,
                ffc::c128
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

                ffc::f32,
                ffc::f64
            >
        );

        EXPECT_TRUE(true);
    }

    template <typename T, ffc::usize N>
    struct bytes final {
        using U = T;
        static constexpr auto M = N;
    };

    template <typename... Types>
    constexpr bool cmpeq = ((sizeof(typename Types::U) == Types::M) && ...);
    
    TEST(numtest, TypeByteSize) {
        static_assert(
            cmpeq<
                bytes<ffc::u8, 1>,
                bytes<ffc::u16, 2>,
                bytes<ffc::u32, 4>,
                bytes<ffc::u64, 8>,
        
                bytes<ffc::i8, 1>,
                bytes<ffc::i16, 2>,
                bytes<ffc::i32, 4>,
                bytes<ffc::i64, 8>,

                bytes<ffc::f32, 4>,
                bytes<ffc::f64, 8>,

                bytes<ffc::c64, 8>,
                bytes<ffc::c128, 16>
            >
        );

        EXPECT_TRUE(true);
    }
}
