#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_run_context.hpp>

#undef OE_DEBUG
#undef OE_ENABLE_ASSERTS

#include "core/data/maths/matrix.h"
#include "core/data/maths/vector.h"

using namespace ObsidianEdge;

struct LoggerFixture {
    LoggerFixture() {
        // Init for testing
        REQUIRE_NOTHROW(ObsidianEdge::Log::init());

        // ------------- IGNORE SIGTRAP ------------- //

        /**
         * * For testing purposes, sigtrap actions
         * * triggered from logging will be ignore
         */

        struct sigaction sa{};
        sa.sa_handler = SIG_IGN;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        sigaction(SIGTRAP, &sa, nullptr);
        // ------------- IGNORE SIGTRAP ------------- //
    }

    ~LoggerFixture() {
        Log::yeet();
    }
};

TEST_CASE_PERSISTENT_FIXTURE(LoggerFixture) {
    SECTION("vector and matrix initializer") {
        auto init = []() {
            VectorBase<short, 2> V_INIT_SHORT_2 = {};
            VectorBase<short, 3> V_INIT_SHORT_3 = {};
            VectorBase<short, 4> V_INIT_SHORT_4 = {};

            VectorBase<unsigned short, 2> V_INIT_U_SHORT_2 = {};
            VectorBase<unsigned short, 3> V_INIT_U_SHORT_3 = {};
            VectorBase<unsigned short, 4> V_INIT_U_SHORT_4 = {};

            VectorBase<int, 2> V_INIT_INT_2 = {};
            VectorBase<int, 3> V_INIT_INT_3 = {};
            VectorBase<int, 4> V_INIT_INT_4 = {};

            VectorBase<unsigned int, 2> V_INIT_U_INT_2 = {};
            VectorBase<unsigned int, 3> V_INIT_U_INT_3 = {};
            VectorBase<unsigned int, 4> V_INIT_U_INT_4 = {};

            VectorBase<long, 2> V_INIT_LONG_2 = {};
            VectorBase<long, 3> V_INIT_LONG_3 = {};
            VectorBase<long, 4> V_INIT_LONG_4 = {};

            VectorBase<unsigned long, 2> V_INIT_U_LONG_2 = {};
            VectorBase<unsigned long, 3> V_INIT_U_LONG_3 = {};
            VectorBase<unsigned long, 4> V_INIT_U_LONG_4 = {};

            VectorBase<float, 2> V_INIT_FLOAT_2 = {};
            VectorBase<float, 3> V_INIT_FLOAT_3 = {};
            VectorBase<float, 4> V_INIT_FLOAT_4 = {};

            VectorBase<double, 2> V_INIT_DOUBLE_2 = {};
            VectorBase<double, 3> V_INIT_DOUBLE_3 = {};
            VectorBase<double, 4> V_INIT_DOUBLE_4 = {};

            MatrixBase<short, 2, 2> M_INIT_SHORT_2 = {};
            MatrixBase<short, 3, 2> M_INIT_SHORT_3 = {};
            MatrixBase<short, 4, 2> M_INIT_SHORT_4 = {};

            MatrixBase<unsigned short, 2, 2> M_INIT_U_SHORT_2_2 = {};
            MatrixBase<unsigned short, 3, 2> M_INIT_U_SHORT_3_2 = {};
            MatrixBase<unsigned short, 4, 2> M_INIT_U_SHORT_4_2 = {};

            MatrixBase<int, 2, 2> M_INIT_INT_2_2 = {};
            MatrixBase<int, 3, 2> M_INIT_INT_3_2 = {};
            MatrixBase<int, 4, 2> M_INIT_INT_4_2 = {};

            MatrixBase<unsigned int, 2, 2> M_INIT_U_INT_2_2 = {};
            MatrixBase<unsigned int, 3, 2> M_INIT_U_INT_3_2 = {};
            MatrixBase<unsigned int, 4, 2> M_INIT_U_INT_4_2 = {};

            MatrixBase<long, 2, 2> M_INIT_LONG_2_2 = {};
            MatrixBase<long, 3, 2> M_INIT_LONG_3_2 = {};
            MatrixBase<long, 4, 2> M_INIT_LONG_4_2 = {};

            MatrixBase<unsigned long, 2, 2> M_INIT_U_LONG_2_2 = {};
            MatrixBase<unsigned long, 3, 2> M_INIT_U_LONG_3_2 = {};
            MatrixBase<unsigned long, 4, 2> M_INIT_U_LONG_4_2 = {};

            MatrixBase<float, 2, 2> M_INIT_FLOAT_2_2 = {};
            MatrixBase<float, 3, 2> M_INIT_FLOAT_3_2 = {};
            MatrixBase<float, 4, 2> M_INIT_FLOAT_4_2 = {};

            MatrixBase<double, 2, 2> M_INIT_DOUBLE_2_2 = {};
            MatrixBase<double, 3, 2> M_INIT_DOUBLE_3_2 = {};
            MatrixBase<double, 4, 2> M_INIT_DOUBLE_4_2 = {};

            MatrixBase<unsigned short, 2, 3> M_INIT_U_SHORT_2_3 = {};
            MatrixBase<unsigned short, 3, 3> M_INIT_U_SHORT_3_3 = {};
            MatrixBase<unsigned short, 4, 3> M_INIT_U_SHORT_4_3 = {};

            MatrixBase<int, 2, 3> M_INIT_INT_2_3 = {};
            MatrixBase<int, 3, 3> M_INIT_INT_3_3 = {};
            MatrixBase<int, 4, 3> M_INIT_INT_4_3 = {};

            MatrixBase<unsigned int, 2, 3> M_INIT_U_INT_2_3 = {};
            MatrixBase<unsigned int, 3, 3> M_INIT_U_INT_3_3 = {};
            MatrixBase<unsigned int, 4, 3> M_INIT_U_INT_4_3 = {};

            MatrixBase<long, 2, 3> M_INIT_LONG_2_3 = {};
            MatrixBase<long, 3, 3> M_INIT_LONG_3_3 = {};
            MatrixBase<long, 4, 3> M_INIT_LONG_4_3 = {};

            MatrixBase<unsigned long, 2, 3> M_INIT_U_LONG_2_3 = {};
            MatrixBase<unsigned long, 3, 3> M_INIT_U_LONG_3_3 = {};
            MatrixBase<unsigned long, 4, 3> M_INIT_U_LONG_4_3 = {};

            MatrixBase<float, 2, 3> M_INIT_FLOAT_2_3 = {};
            MatrixBase<float, 3, 3> M_INIT_FLOAT_3_3 = {};
            MatrixBase<float, 4, 3> M_INIT_FLOAT_4_3 = {};

            MatrixBase<double, 2, 3> M_INIT_DOUBLE_2_3 = {};
            MatrixBase<double, 3, 3> M_INIT_DOUBLE_3_3 = {};
            MatrixBase<double, 4, 3> M_INIT_DOUBLE_4_3 = {};

            MatrixBase<unsigned short, 2, 4> M_INIT_U_SHORT_2_4 = {};
            MatrixBase<unsigned short, 3, 4> M_INIT_U_SHORT_3_4 = {};
            MatrixBase<unsigned short, 4, 4> M_INIT_U_SHORT_4_4 = {};

            MatrixBase<int, 2, 4> M_INIT_INT_2_4 = {};
            MatrixBase<int, 3, 4> M_INIT_INT_3_4 = {};
            MatrixBase<int, 4, 4> M_INIT_INT_4_4 = {};

            MatrixBase<unsigned int, 2, 4> M_INIT_U_INT_2_4 = {};
            MatrixBase<unsigned int, 3, 4> M_INIT_U_INT_3_4 = {};
            MatrixBase<unsigned int, 4, 4> M_INIT_U_INT_4_4 = {};

            MatrixBase<long, 2, 4> M_INIT_LONG_2_4 = {};
            MatrixBase<long, 3, 4> M_INIT_LONG_3_4 = {};
            MatrixBase<long, 4, 4> M_INIT_LONG_4_4 = {};

            MatrixBase<unsigned long, 2, 4> M_INIT_U_LONG_2_4 = {};
            MatrixBase<unsigned long, 3, 4> M_INIT_U_LONG_3_4 = {};
            MatrixBase<unsigned long, 4, 4> M_INIT_U_LONG_4_4 = {};

            MatrixBase<float, 2, 4> M_INIT_FLOAT_2_4 = {};
            MatrixBase<float, 3, 4> M_INIT_FLOAT_3_4 = {};
            MatrixBase<float, 4, 4> M_INIT_FLOAT_4_4 = {};

            MatrixBase<double, 2, 4> M_INIT_DOUBLE_2_4 = {};
            MatrixBase<double, 3, 4> M_INIT_DOUBLE_3_4 = {};
            MatrixBase<double, 4, 4> M_INIT_DOUBLE_4_4 = {};
        };

        REQUIRE_NOTHROW(init());
    }

    SECTION("vector boiler plates") {
        // constexpr VectorBase(t scalar)
        REQUIRE_NOTHROW(Vector2{8});
        REQUIRE_NOTHROW(Vector3{8});
        REQUIRE_NOTHROW(Vector4{8});

        Vector2 vec2 = {2};

        // constexpr VectorBase(const VectorBase<t, n - 1>& minor)
        CHECK_NOTHROW(Vector4{Vector3{vec2}});

        // static constexpr auto zero() -> VectorBase
        CHECK_NOTHROW(Vector4::zero());

        // constexpr auto operator==(const VectorBase& other) const->bool
        REQUIRE_NOTHROW(Vector4{1.0F} == Vector4{2.0F});
        CHECK(Vector4{1.0F} == Vector4{1.0F});

        // constexpr auto operator!=(const VectorBase& other) const->bool
        REQUIRE_NOTHROW(Vector4{1.0F} != Vector4{2.0F});
        CHECK(Vector4{1.0F} != Vector4{2.0F});

        // constexpr auto operator*(t scalar)const ->
        CHECK_NOTHROW(Vector4{1.0F} * 5.0F);

        // constexpr auto operator*=(t scalar) -> VectorBase&
        CHECK_NOTHROW(Vector4{1.0F} *= 5.0F);

        // constexpr auto operator/(t scalar)const -> VectorBase
        CHECK_NOTHROW(Vector4{1.0F} / 5.0F);
        CHECK_THROWS(Vector4{1.0F} /= 0.0F);

        // constexpr auto operator/=(t scalar) -> VectorBase&
        CHECK_NOTHROW(Vector4{1.0F} / 5.0F);
        CHECK_THROWS(Vector4{1.0F} /= 0.0F);

        // constexpr auto operator+(const VectorBase& other)const->VectorBase
        REQUIRE_NOTHROW((Vector4{1.0F} + Vector4{1.0F}) == Vector4{2.0F});
        CHECK((Vector4{1.0F} + Vector4{1.0F}) == Vector4{2.0F});

        // constexpr auto operator+=(const VectorBase& other)->VectorBase&
        REQUIRE_NOTHROW((Vector4{1.0F} += Vector4{1.0F}) == Vector4{2.0F});
        CHECK((Vector4{1.0F} += Vector4{1.0F}) == Vector4{2.0F});

        // constexpr auto operator-(const VectorBase& other)const->VectorBase
        REQUIRE_NOTHROW((Vector4{1.0F} - Vector4{1.0F}) == Vector4{0.0F});
        CHECK((Vector4{1.0F} - Vector4{1.0F}) == Vector4{0.0F});

        // constexpr auto operator-=(const VectorBase& other)->VectorBase&
        REQUIRE_NOTHROW((Vector4{1.0F} -= Vector4{1.0F}) == Vector4{0.0F});
        CHECK((Vector4{1.0F} -= Vector4{1.0F}) == Vector4{0.0F});

        // constexpr auto operator-() const->VectorBase
        REQUIRE_NOTHROW(-Vector4{1.0F});
        CHECK(-Vector4{1.0F} == Vector4{-1.0F});

        // constexpr auto at(unsigned int index) const -> const t&
        REQUIRE_NOTHROW(Vector4{1.0F}.at(0) + Vector4{1.0F}.at(1) + Vector4{1.0F}.at(2) + Vector4{1.0F}.at(3));
        REQUIRE_THROWS(Vector4{1.0F}.at(4));

        // constexpr auto operator[](unsigned int index) const->const t&
        REQUIRE_NOTHROW(Vector4{1.0F}[0] + Vector4{1.0F}[1] + Vector4{1.0F}[2] + Vector4{1.0F}[3]);
        REQUIRE_THROWS(Vector4{1.0F}[4]);
    }

    SECTION("vector utils") {
        REQUIRE(isHexDigit('0'));
        REQUIRE(isHexDigit('1'));
        REQUIRE(isHexDigit('2'));
        REQUIRE(isHexDigit('3'));
        REQUIRE(isHexDigit('4'));
        REQUIRE(isHexDigit('5'));
        REQUIRE(isHexDigit('6'));
        REQUIRE(isHexDigit('7'));
        REQUIRE(isHexDigit('8'));
        REQUIRE(isHexDigit('9'));
        REQUIRE(isHexDigit('A'));
        REQUIRE(isHexDigit('a'));
        REQUIRE(isHexDigit('B'));
        REQUIRE(isHexDigit('b'));
        REQUIRE(isHexDigit('C'));
        REQUIRE(isHexDigit('c'));
        REQUIRE(isHexDigit('D'));
        REQUIRE(isHexDigit('d'));
        REQUIRE(isHexDigit('E'));
        REQUIRE(isHexDigit('e'));
        REQUIRE(isHexDigit('F'));
        REQUIRE(isHexDigit('f'));

        REQUIRE(hexValue('0') == 0x0);
        REQUIRE(hexValue('1') == 0x1);
        REQUIRE(hexValue('2') == 0x2);
        REQUIRE(hexValue('3') == 0x3);
        REQUIRE(hexValue('4') == 0x4);
        REQUIRE(hexValue('5') == 0x5);
        REQUIRE(hexValue('6') == 0x6);
        REQUIRE(hexValue('7') == 0x7);
        REQUIRE(hexValue('8') == 0x8);
        REQUIRE(hexValue('9') == 0x9);
        REQUIRE(hexValue('A') == 0xA);
        REQUIRE(hexValue('a') == 0xA);
        REQUIRE(hexValue('B') == 0xB);
        REQUIRE(hexValue('b') == 0xB);
        REQUIRE(hexValue('C') == 0xC);
        REQUIRE(hexValue('c') == 0xC);
        REQUIRE(hexValue('D') == 0xD);
        REQUIRE(hexValue('d') == 0xD);
        REQUIRE(hexValue('E') == 0xE);
        REQUIRE(hexValue('e') == 0xE);
        REQUIRE(hexValue('F') == 0xF);
        REQUIRE(hexValue('f') == 0xF);

        // ! No test for hexToDec yet...
    }

    SECTION("vector hexStr resolver") {
        REQUIRE_NOTHROW(Vector4{"#89dada"});
        REQUIRE_NOTHROW(Vector4{"#000000"});
        REQUIRE_NOTHROW(Vector4{"#FFFFFF"});
        REQUIRE_NOTHROW(Vector4{"#FFFFFFff"});
        REQUIRE_NOTHROW(Vector4{"#FaFcFf"});
        REQUIRE_NOTHROW(Vector4{"#9ca938ee"});

        REQUIRE_THROWS(Vector4{"#gfffffff"});
        REQUIRE_THROWS(Vector4{"#hfffffff"});
        REQUIRE_THROWS(Vector4{"#ifffffff"});
        REQUIRE_THROWS(Vector4{"#jfffffff"});
        REQUIRE_THROWS(Vector4{"#kfffffff"});
        REQUIRE_THROWS(Vector4{"#lfffffff"});
        REQUIRE_THROWS(Vector4{"#mfffffff"});
        REQUIRE_THROWS(Vector4{"#nfffffff"});
        REQUIRE_THROWS(Vector4{"#offfffff"});
        REQUIRE_THROWS(Vector4{"#qfffffff"});
        REQUIRE_THROWS(Vector4{"#rfffffff"});
        REQUIRE_THROWS(Vector4{"#sfffffff"});
        REQUIRE_THROWS(Vector4{"#wfffffff"});
        REQUIRE_THROWS(Vector4{"#vfffffff"});
    }
}