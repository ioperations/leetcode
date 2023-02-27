#include <gtest/gtest.h>

#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>

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

TEST(t1, t2) {
    int z[] = {1, 2, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 7);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 1);
}

TEST(t1, t3) {
    int z[] = {1, 9, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 6);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 2);
}

TEST(t1, t4) {
    int z[] = {9, 9, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 5);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 2);
}

TEST(t2, t4) {
    int z[] = {-1, 9, 3, 4, 5, 6, 7};
    int ret = MaxLengthOf(z, sizeof(z) / sizeof(int));
    EXPECT_EQ(ret, 6);
    EXPECT_EQ(MaxLengthOfdijizixulie(z, sizeof(z) / sizeof(int)), 2);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
