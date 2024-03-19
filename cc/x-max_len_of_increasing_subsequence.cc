// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <cstring>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {

int MaxLengthOfdijizixulie(int nums[], int length) {
    /// 最长递增子序列的长度

    int dp[100];
    memset(dp, 1, sizeof(dp));

    for (int i = 0; i < length; ++i) {
        dp[i] = 1;
    }

    // dp[i] 表示 以 num[i] 为结尾的最长递增子序列的长度

    /// 那么 dp[i] =
    ///     for i in [0..length ]
    ///          for j in [0 .. i]
    ///             max( dp[i] , dp[j] + 1) if num[j] > num[i]

    /// 也就是说在前面的 0..i-1 中找到一个结尾比 num[i]  值要小的
    ///    在这条子序列上再加上 num[i] 保证序列是递增的

    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < i; j++) {
            if (nums[i] < nums[j]) {
                dp[i] = std::max({dp[i], dp[j] + 1});
            }
        }
    }

    return *(dp + length - 1);
}
int MaxLengthOf(int nums[], int length) {
    /// 最长递增子序列的长度

    int dp[100];
    memset(dp, 1, sizeof(dp));

    for (int i = 0; i < length; ++i) {
        dp[i] = 1;
    }

    // dp[i] 表示 以 num[i] 为结尾的最长递增子序列的长度

    /// 那么 dp[i] =
    ///     for i in [0..length ]
    ///          for j in [0 .. i]
    ///             max( dp[i] , dp[j] + 1) if num[j] > num[i]

    /// 也就是说在前面的 0..i-1 中找到一个结尾比 num[i]  值要小的
    ///    在这条子序列上再加上 num[i] 保证序列是递增的

    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max({dp[i], dp[j] + 1});
            }
        }
    }

    return *(dp + length - 1);
}

TEST(x_max_len_of_increasing_subsequence_v2, t2) {
    int z[] = {1, 2, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 7);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 1);
}

TEST(x_max_len_of_increasing_subsequence_v2, t3) {
    int z[] = {1, 9, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 6);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 2);
}

TEST(x_max_len_of_increasing_subsequence_v2, t4) {
    int z[] = {9, 9, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 5);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 2);
}

TEST(x_max_len_of_increasing_subsequence_v3, t4) {
    int z[] = {-1, 9, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 6);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 2);
}

}  // namespace
