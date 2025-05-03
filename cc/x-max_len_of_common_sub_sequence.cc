// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// given two string
/// find the max length of the substring containing same characters

#include <algorithm>
#include <cstring>
#include <functional>

#include "gtest/gtest.h"

namespace {

int MaxSubStringLengthOfTwoString(const char* s1, int s1_len, const char* s2,
                                  int s2_len) {
    int dp[100][100];
    memset(dp, -1, sizeof(dp));
    /// fp_fun(i,j) 是 s1[0..i] s2[0..j] 之间的最长子序列的长度
    std::function<int(int, int)> dp_fun = [&dp_fun, &dp, s1, s2](int i,
                                                                 int j) -> int {
        if (i == -1) {
            return 0;
        }
        if (j == -1) {
            return 0;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        if (*(s1 + i) == *(s2 + j)) {
            dp[i][j] = dp_fun(i - 1, j - 1) + 1;
        } else {
            dp[i][j] = std::max({dp_fun(i - 1, j), dp_fun(i, j - 1)});
        }
        return dp[i][j];
    };
    return dp_fun(s1_len - 1, s2_len - 1);
}

TEST(t1j, t2) {
    const char* s1 = "hello";
    const char* s2 = "hell";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, strlen(s1), s2, strlen(s2));
    EXPECT_EQ(ret, 4);
}

TEST(t1j, t3) {
    const char* s1 = "hllo";
    const char* s2 = "hell";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, strlen(s1), s2, strlen(s2));
    EXPECT_EQ(ret, 3);
}

TEST(t1j, t4) {
    const char* s1 = "abcd";
    const char* s2 = "defg";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, strlen(s1), s2, strlen(s2));
    EXPECT_EQ(ret, 1);
}

TEST(t1j, t5) {
    const char* s1 = "abch";
    const char* s2 = "defg";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, strlen(s1), s2, strlen(s2));
    EXPECT_EQ(ret, 0);
}

}  // namespace
