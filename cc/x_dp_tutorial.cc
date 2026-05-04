// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// 给你两个字符串， s1 s2
/// 让你把s1换成s2
///
/// s1     "rad"
/// s2     "apple"
#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <string_view>

#include "gtest/gtest.h"

// 每一个步骤  只有删除 添加 改变
namespace {

int FindMinPath(std::string_view s1, std::string_view s2) {
    /// 从右向左走

    /// - 主要思路
    /// - 基础情况
    /// - 转换方程
    /// - 1 递归解法
    /// - 2 迭代解法
    ///
    /// 定义 dp_fun 是 s1[0..i] 和 s2[0..j] 之间的最小编辑距离
    std::array<std::array<int, 100>, 100> hash{};
    hash.fill({});
    for (auto& row : hash) {
        row.fill(-1);
    }
    std::function<int(int, int)> dp_fun = [&hash, s1, s2, &dp_fun](
                                              int i, int j) -> int {
        /// base case
        if (i == -1) {  // s1走到尽头
            return j + 1;
        }
        if (j == -1) {  // s2走到尽头
            return i + 1;
        }

        if (hash.at(i).at(j) != -1) {
            return hash.at(i).at(j);
        }

        if (s1.at(static_cast<std::size_t>(i)) == s2.at(static_cast<std::size_t>(j))) {
            hash.at(i).at(j) = dp_fun(i - 1, j - 1);
        } else {
            hash.at(i).at(j) = std::min({
                dp_fun(i - 1, j - 1) + 1,
                dp_fun(i, j - 1) + 1,
                dp_fun(i - 1, j) + 1,
            });
        }
        return hash.at(i).at(j);
    };
    /// transfer function
    return dp_fun(static_cast<int>(s1.size()) - 1, static_cast<int>(s2.size()) - 1);
}

TEST(XDpTutorialV2, r2) {
    int const expected = 5;

    std::string_view const s1 = "rad";
    std::string_view const s2 = "apple";
    int const ret = FindMinPath(s1, s2);

    EXPECT_EQ(ret, expected);
    EXPECT_EQ(FindMinPath("appled", "apple"), 1);
    std::string_view const s1_1 = "appl7777777777777777777777777";
    std::string_view const s2_1 = "appl7777777777777777777777776";
    EXPECT_EQ(FindMinPath(s1_1, s2_1), 1);
}

}  // namespace
