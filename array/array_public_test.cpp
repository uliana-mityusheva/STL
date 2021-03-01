#include <gtest/gtest.h>

#include <public_tests/util/comparision_check.h>
#include <public_tests/util/equal_range_check.h>

#include "array.h"

TEST(Array, Public) {
    Array<int, 5> arr{1, 2, 3};  // agregate initialization
    Array<int, 5> other{3, 2, 1};

    ASSERT_EQ(sizeof(arr), sizeof(int) * 5);  // no dynamic arrays

    ASSERT_EQ(arr.Size(), (size_t) 5);  // Size

    ASSERT_FALSE(arr.Empty());  // Empty

    arr[1] = -2;  // []

    ASSERT_EQ(arr[1], -2);  // []

    arr.At(2) = -3;  // At

    ASSERT_EQ(arr.At(2), -3);  // At

    ASSERT_THROW(arr.At(5), ArrayOutOfRange);  // NOLINT throws out of range

    ASSERT_EQ(arr.Front(), 1);  // Front

    arr.Front() = -1;

    ASSERT_EQ(arr.Back(), 0);  // Back

    arr.Back() = 11;

    ASSERT_EQ(arr.Data(), &arr[0]);  // Data

    arr.Fill(-1);  // Fill

    arr.Swap(other);  // Swap

    std::swap(arr, other);  // std::swap

    ASSERT_TRUE(arr < other);  // operator<

    ASSERT_FALSE(arr == other);  // operator==
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
