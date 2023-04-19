// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given an integer array nums, find the contiguous subarray (containing at least
one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

*/

#include <functional>
#include <map>
#include <vector>
using namespace std;

class Solution {
   public:
    int MaxSubArray(vector<int> &nums) {
        // pass
        int max_sum = nums[0];
        int cur = max_sum;
        for (int i = 1; i < (int)nums.size(); i++) {
            if (cur + nums[i] > nums[i]) {
                cur += nums[i];
            } else {
                cur = nums[i];
            }
            max_sum = max(max_sum, cur);
        }
        return max_sum;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> v{-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int o = 6;
    Solution sl;
    int ret = sl.MaxSubArray(v);
    EXPECT_EQ(ret, o);
}

TEST(t0, t2) {
    std::vector<int> v{1};

    int o = 1;
    Solution sl;
    int ret = sl.MaxSubArray(v);
    EXPECT_EQ(ret, o);
}

TEST(t0, t3) {
    std::vector<int> v{5, 4, -1, 7, 8};

    int o = 23;
    Solution sl;
    int ret = sl.MaxSubArray(v);
    EXPECT_EQ(ret, o);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
