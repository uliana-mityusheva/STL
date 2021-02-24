#include <gtest/gtest.h>

#include <limits>

#include "sum.h"

TEST(Sum, SignatureIsNotChanged) {
    ASSERT_TRUE((std::is_same_v<decltype(Sum), int64_t(int32_t, int32_t)>));
}

TEST(Sum, PositiveSmall) {
    ASSERT_EQ(Sum(2, 5), 7);
    ASSERT_EQ(Sum(6, 4), 10);
}

TEST(Sum, NegativeSmall) {
    ASSERT_EQ(Sum(-3, -6), -9);
    ASSERT_EQ(Sum(-7, -5), -12);
}

TEST(Sum, MixSmall) {
    ASSERT_EQ(Sum(-4, 5), 1);
    ASSERT_EQ(Sum(4, -6), -2);
    ASSERT_EQ(Sum(-11, 11), 0);
}

TEST(Sum, PositiveLarge) {
    const int32_t max_value = std::numeric_limits<int32_t>::max();
    ASSERT_EQ(Sum(max_value, max_value), int64_t{max_value} + int64_t{max_value});
    ASSERT_EQ(Sum(max_value, max_value / 2), int64_t{max_value / 2} + int64_t{max_value});
    ASSERT_EQ(Sum(5, max_value), int64_t{max_value} + int64_t{5});
}

TEST(Sum, NegativeLarge) {
    const int32_t max_value = std::numeric_limits<int32_t>::max();
    ASSERT_EQ(Sum(-max_value, -max_value), int64_t{-max_value} + int64_t{-max_value});
    ASSERT_EQ(Sum(-max_value / 2, -max_value), int64_t{-max_value / 2} + int64_t{-max_value});
    ASSERT_EQ(Sum(-5, -max_value), int64_t{-max_value} + int64_t{-5});
}

TEST(Sum, MixLarge) {
    const int32_t max_value = std::numeric_limits<int32_t>::max();
    ASSERT_EQ(Sum(-max_value, max_value), int64_t{-max_value} + int64_t{max_value});
    ASSERT_EQ(Sum(-max_value / 2, max_value), int64_t{-max_value / 2} + int64_t{max_value});
    ASSERT_EQ(Sum(-max_value, max_value / 2), int64_t{max_value / 2} + int64_t{-max_value});
    ASSERT_EQ(Sum(5, -max_value), int64_t{-max_value} + int64_t{5});
    ASSERT_EQ(Sum(max_value, -5), int64_t{-5} + int64_t{max_value});
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
