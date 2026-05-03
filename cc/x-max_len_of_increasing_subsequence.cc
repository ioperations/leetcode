// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <array>

#include "gtest/gtest.h"

namespace {

int MaxLengthOfdijizixulie(const int* nums, int length) {
    std::array<int, 100> dp{};
    dp.fill(1);

    for (int i = 0; i < length; ++i) {
        dp[i] = 1;
    }

    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < i; j++) {
            if (nums[i] < nums[j]) {
                dp[i] = std::max({dp[i], dp[j] + 1});
            }
        }
    }

    return dp[length - 1];
}

int MaxLengthOf(const int* nums, int length) {
    std::array<int, 100> dp{};
    dp.fill(1);

    for (int i = 0; i < length; ++i) {
        dp[i] = 1;
    }

    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max({dp[i], dp[j] + 1});
            }
        }
    }

    return dp[length - 1];
}

TEST(XMaxLenOfIncreasingSubsequenceV2, t2) {
    constexpr std::array<int, 7> z = {1, 2, 3, 4, 5, 6, 7};
    int const ret = MaxLengthOf(z.data(), static_cast<int>(z.size()));
    EXPECT_EQ(ret, 7);
    EXPECT_EQ(MaxLengthOfdijizixulie(z.data(), static_cast<int>(z.size())), 1);
}

TEST(XMaxLenOfIncreasingSubsequenceV2, t3) {
    constexpr std::array<int, 7> z = {1, 9, 3, 4, 5, 6, 7};
    int const ret = MaxLengthOf(z.data(), static_cast<int>(z.size()));
    EXPECT_EQ(ret, 6);
    EXPECT_EQ(MaxLengthOfdijizixulie(z.data(), static_cast<int>(z.size())), 2);
}

TEST(XMaxLenOfIncreasingSubsequenceV2, t4) {
    constexpr std::array<int, 7> z = {9, 9, 3, 4, 5, 6, 7};
    int const ret = MaxLengthOf(z.data(), static_cast<int>(z.size()));
    EXPECT_EQ(ret, 5);
    EXPECT_EQ(MaxLengthOfdijizixulie(z.data(), static_cast<int>(z.size())), 2);
}

TEST(XMaxLenOfIncreasingSubsequenceV3, t4) {
    constexpr std::array<int, 7> z = {-1, 9, 3, 4, 5, 6, 7};
    int const ret = MaxLengthOf(z.data(), static_cast<int>(z.size()));
    EXPECT_EQ(ret, 6);
    EXPECT_EQ(MaxLengthOfdijizixulie(z.data(), static_cast<int>(z.size())), 2);
}

}  // namespace
