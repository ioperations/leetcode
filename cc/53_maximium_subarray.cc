// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given an integer array nums, find the contiguous subarray (containing at least
one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

*/

#include <algorithm>
#include <cstddef>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    // ReSharper disable once CppMemberFunctionMayBeStatic
    [[nodiscard]] int MaxSubArray(const vector<int>& nums) const {
        // pass
        std::size_t const size = nums.size();
        if (size == 0) {
            return 0;
        }
        int max_sum = nums.at(0);
        int cur = max_sum;
        for (std::size_t i = 1; i < size; i++) {
            if (cur + nums.at(i) > nums.at(i)) {
                cur += nums.at(i);
            } else {
                cur = nums.at(i);
            }
            max_sum = max(max_sum, cur);
        }
        return max_sum;
    }
};

TEST(maximiumV, t1) {
    const std::vector<int> v{-2, 1, -3, 4, -1, 2, 1, -5, 4};

    constexpr int o = 6;
    Solution const sl;
    int const ret = sl.MaxSubArray(v);
    EXPECT_EQ(ret, o);
}

TEST(maximiumV, t2) {
    const std::vector<int> v{1};

    constexpr int o = 1;
    Solution const sl;
    int const ret = sl.MaxSubArray(v);
    EXPECT_EQ(ret, o);
}

TEST(maximiumV, t3) {
    const std::vector<int> v{5, 4, -1, 7, 8};

    constexpr int o = 23;
    Solution const sl;
    int const ret = sl.MaxSubArray(v);
    EXPECT_EQ(ret, o);
}

}  // namespace
