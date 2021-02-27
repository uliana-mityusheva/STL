#include <gtest/gtest.h>

#include <type_traits>
#include <iostream>

#include <public_tests/util/comparision_check.h>

#include "rational.h"

void RationalEqual(const Rational& rational, int64_t numerator, int64_t denominator) {
    ASSERT_EQ(rational.GetNumerator(), numerator);
    ASSERT_EQ(rational.GetDenominator(), denominator);
}

TEST(Rational, Public) {
Rational a;
Rational b = -1;
Rational c(2, -4);
RationalEqual(c, -1, 2);

a.SetNumerator(6);
a.SetDenominator(21);
ASSERT_EQ(a.GetNumerator(), 2);
ASSERT_EQ(a.GetDenominator(), 7);

a += b;
b -= c;
c *= a;
b /= a;

RationalEqual(+a, -5, 7);
RationalEqual(-b, -7, 10);
RationalEqual(c, 5, 14);

RationalEqual(a + c, -5, 14);
RationalEqual(a - b, -99, 70);
RationalEqual(b * c, 1, 4);
RationalEqual(c / a, -1, 2);

RationalEqual(++b, 17, 10);
RationalEqual(b++, 17, 10);
RationalEqual(b--, 27, 10);
RationalEqual(--b, 7, 10);

ASSERT_TRUE(a < b);
ASSERT_TRUE(b > c);
ASSERT_FALSE(a == c);

std::stringstream is("-7/3 4/6 7");
is >> a >> b >> c;

std::stringstream os;
os << a << ' ' << b << ' ' << c;
ASSERT_EQ(os.str(), "-7/3 2/3 7");

ASSERT_THROW(a / 0, RationalDivisionByZero);  // NOLINT
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

