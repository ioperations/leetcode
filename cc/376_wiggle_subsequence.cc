// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    A wiggle sequence is a sequence where the differences between successive
    numbers strictly alternate between positive and negative. The first
   difference (if one exists) may be either positive or negative. A sequence
   with one element and a sequence with two non-equal elements are trivially
   wiggle sequences.

    For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences
   (6, -3, 5, -7, 3) alternate between positive and negative. In contrast, [1,
   4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences. The first is not
   because its first two differences are positive, and the second is not because
   its last difference is zero. A subsequence is obtained by deleting some
   elements (possibly zero) from the original sequence, leaving the remaining
   elements in their original order.

    Given an integer array nums, return the length of the longest wiggle
   subsequence of nums.
*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int WiggleMaxLength(vector<int>& nums) {
        int const n = nums.size();
        int peak = 1, valley = 1;

        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1])
                peak = valley + 1;
            else if (nums[i] < nums[i - 1])
                valley = peak + 1;
        }
        return max(peak, valley);
    }
};

TEST(wiggle_subsequence, t1) {
    // pass
    vector<int> nums = {1, 7, 4, 9, 2, 5};
    int const output = 6;
    // Explanation: The entire sequence is a wiggle sequence with differences(6,
    // -3, 5, -7, 3)
    Solution sl;
    int const ret = sl.WiggleMaxLength(nums);
    EXPECT_EQ(ret, output);
}

TEST(wiggle_subsequence, t2) {
    // pass
    vector<int> nums = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
    int const output = 7;
    // There are several subsequences that achieve this length.
    // One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6,
    // -8).
    Solution sl;
    int const ret = sl.WiggleMaxLength(nums);
    EXPECT_EQ(ret, output);
}

TEST(wiggle_subsequence, t3) {
    // pass
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int const output = 2;
    Solution sl;
    int const ret = sl.WiggleMaxLength(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
