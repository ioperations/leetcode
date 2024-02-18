// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Return all non-negative integers of length n such that the absolute difference
between every two consecutive digits is k.

Note that every number in the answer must not have leading zeros. For example,
01 has one leading zero and is invalid.

You may return the answer in any order.*/
#include <cstdlib>
#include <vector>

using namespace std;
#include <functional>
#include <set>
#include <string>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    vector<int> NumsSameConsecDiff(int n, int k) {
        std::set<int> ret;
        if (n <= 1) return vector<int>(ret.begin(), ret.end());

        // @tmp 当前已经构造的数值
        std::function<void(std::string, int)> fun = [&](std::string tmp,
                                                        int cur_count) -> void {
            if (cur_count == n) {
                ret.emplace(atoi(tmp.c_str()));
                return;
            }
            if (tmp.back() + k <= '9') {
                tmp += tmp.back() + k;
                fun(tmp, cur_count + 1);
                tmp.pop_back();
            }
            if (tmp.back() - k >= '0') {
                tmp += tmp.back() - k;
                fun(tmp, cur_count + 1);
                tmp.pop_back();
            }
        };
        for (int i = 1; i < 10; i++) {
            fun(std::to_string(i), 1);
        }
        return std::vector<int>(ret.begin(), ret.end());
    }
};

TEST(numbers_with_same_consecutive_differences, t1) {
    int n = 3, k = 7;
    vector<int> output = {181, 292, 707, 818, 929};
    // Explanation: Note that 070 is not a valid number, because it has leading
    // zeroes.
    set<int> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.NumsSameConsecDiff(n, k);
    std::set<int> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

TEST(numbers_with_same_consecutive_differences, t2) {
    int n = 2, k = 1;
    vector<int> output = {10, 12, 21, 23, 32, 34, 43, 45, 54,
                          56, 65, 67, 76, 78, 87, 89, 98};
    set<int> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.NumsSameConsecDiff(n, k);
    std::set<int> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

TEST(numbers_with_same_consecutive_differences, t3) {
    int n = 2, k = 0;
    vector<int> output = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    set<int> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.NumsSameConsecDiff(n, k);
    std::set<int> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}
}  // namespace
