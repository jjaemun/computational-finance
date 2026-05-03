#include <gtest/gtest.h>

#include "ffc/types.hpp"
#include "ffc/core/ptr/uptr.hpp"


namespace {
    namespace core = ffc::core::ptr;

    TEST(uptrtest, DefaultInitIsNullish) {
        static_assert(
            core::uptr{}.to_unsigned() == core::uptr::zero().to_unsigned()
        );

        EXPECT_TRUE(true);
    }

    TEST(uptrtest, UsizeRoundTrip) {
        static_assert(
            core::uptr::from_usize(0xffuz).to_usize() == (0xffuz)
        );

        EXPECT_TRUE(true);
    }

    TEST(uptrtest, PtrRoundTrip) {
        ffc::u8 foo{0xff};
        const auto faddr = core::uptr::from_ptr(&foo);
        const auto recov = faddr.as_ptr<decltype(foo)>();

        EXPECT_EQ(recov, &foo);
        EXPECT_EQ(*recov, 0xff);
    }

    TEST(uptrtest, ConstPointerRoundTripBehavior) {
        const ffc::u8 foo{0xff};
        const auto faddr = core::uptr::from_const_ptr(&foo);
        const auto recov = faddr.as_const_ptr<decltype(foo)>();

        EXPECT_EQ(recov, &foo);
        EXPECT_EQ(*recov, 0xff);
    }

    TEST(uptrtest, ByteArithmeticOps) {
        constexpr auto addr = core::uptr::from_usize(8uz);

        // unsigned bytes.
        constexpr ffc::usize uoffset{8};
        constexpr auto addbytes = addr.byte_add(uoffset);
        constexpr auto subbytes = addr.byte_sub(uoffset);
        
        static_assert(addbytes.to_usize() == 16uz);
        static_assert(subbytes.to_usize() == 0uz);

        // signed bytes.
        constexpr ffc::isize soffset{8};
        constexpr auto posbytes = addr.offset_bytes(soffset);
        constexpr auto negbytes = addr.offset_bytes(-soffset);

        static_assert(posbytes.to_usize() == 16uz);
        static_assert(negbytes.to_usize() == 0uz);

        EXPECT_TRUE(true);
    }

    TEST(uptrtest, TypedArithmeticOps) {
        constexpr auto addr = core::uptr::from_usize(8uz);

        // unsigned typed.
        constexpr ffc::usize uoffset{1};
        constexpr auto addtyped = addr.add<ffc::i64>(uoffset);
        constexpr auto subtyped = addr.sub<ffc::i64>(uoffset);

        static_assert(addtyped.to_usize() == 16uz);
        static_assert(subtyped.to_usize() == 0uz);

        
        // signed typed.
        constexpr ffc::isize soffset{1};
        constexpr auto postyped = addr.offset<ffc::i64>(soffset);
        constexpr auto negtyped = addr.offset<ffc::i64>(-soffset);

        static_assert(postyped.to_usize() == 16uz);
        static_assert(negtyped.to_usize() == 0uz);

        EXPECT_TRUE(true);
    }

    TEST(uptrtest, ByteOffsetFrom) {
        constexpr auto lhs = core::uptr::zero();
        constexpr auto rhs = core::uptr::from_usize(0xffuz);

        static_assert(lhs.byte_offset_from(rhs) == 0xff);
        static_assert(rhs.byte_offset_from(lhs) == -0xff);

        EXPECT_TRUE(true);
    }

    TEST(uptrtest, PtrOffsetFrom) {
        ffc::u8 buffer[16];
        const auto addr = core::uptr::from_ptr(&buffer[8]);

        EXPECT_EQ(addr.byte_offset_from_ptr(&buffer[0]), -8);
    }

    TEST(uptrtest, TypedOffsetBehavior) {
        constexpr auto lhs = core::uptr::zero();
        constexpr auto rhs = core::uptr::from_usize(16uz);

        static_assert(lhs.offset_from<ffc::i64>(rhs) == 2);
        static_assert(rhs.offset_from<ffc::i64>(lhs) == -2);

        EXPECT_TRUE(true);
    }

    TEST(uptrtest, BitwiseOps) {
        constexpr auto lhs = core::uptr::from_usize(0xf0uz);
        constexpr auto rhs = core::uptr::from_usize(0x0fuz);

        constexpr auto and_ = lhs.bit_and(rhs);
        constexpr auto not_ = lhs.bit_not();
        constexpr auto or_ = lhs.bit_or(rhs);
        constexpr auto xor_ = lhs.bit_xor(rhs);
        constexpr auto mask_ = lhs.mask(rhs);

        static_assert(and_.to_usize() == 0x00uz);
        static_assert(not_.to_unsigned() == ~lhs.to_unsigned());
        static_assert(or_.to_usize() == 0xffuz);
        static_assert(xor_.to_usize() == 0xffuz);
        static_assert(mask_.to_usize() == 0x00uz);

        EXPECT_TRUE(true);
    }
}
