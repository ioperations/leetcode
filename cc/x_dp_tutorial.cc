// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// 给你两个字符串， s1 s2
/// 让你把s1换成s2
///
/// s1     "rad"
/// s2     "apple"
#include <algorithm>
#include <cstring>
#include <functional>

#include "gtest/gtest.h"

// 每一个步骤  只有删除 添加 改变
namespace {

int FindMinPath(const char *s1, const int s1_length, const char *s2,
                const int s2_length) {
    /// 从右向左走

    /// - 主要思路
    /// - 基础情况
    /// - 转换方程
    /// - 1 递归解法
    /// - 2 迭代解法
    ///
    /// 定义 dp_fun 是 s1[0..i] 和 s2[0..j] 之间的最小编辑距离
    int hash[100][100];
    memset(hash, -1, sizeof(hash));
    std::function<int(int, int)> dp_fun = [&hash, s1, s2, &dp_fun](
                                              int i, int j) -> int {
        /// base case
        if (i == -1) {  // s1走到尽头
            return j + 1;
        }
        if (j == -1) {  // s2走到尽头
            return i + 1;
        }

        if (hash[i][j] != -1) {
            return hash[i][j];
        }

        if (*(s1 + i) == *(s2 + j)) {
            hash[i][j] = dp_fun(i - 1, j - 1);
        } else {
            hash[i][j] = std::min({
                dp_fun(i - 1, j - 1) + 1,
                dp_fun(i, j - 1) + 1,
                dp_fun(i - 1, j) + 1,
            });
        }
        return hash[i][j];
    };
    /// transfer function
    return dp_fun(s1_length - 1, s2_length - 1);
}

TEST(t1, r2) {
    int expected = 5;

    const char *s1 = "rad";
    const char *s2 = "apple";
    int ret = FindMinPath(s1, 3, s2, 5);

    EXPECT_EQ(ret, expected);
    EXPECT_EQ(FindMinPath("appled", 6, "apple", 5), 1);
    const char *s1_1 = "appl7777777777777777777777777";
    const char *s2_1 = "appl7777777777777777777777776";
    EXPECT_EQ(FindMinPath(s1_1, strlen(s1_1), s2_1, strlen(s2_1)), 1);
}

}  // namespace
