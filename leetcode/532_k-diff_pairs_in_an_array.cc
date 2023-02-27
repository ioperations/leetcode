/*
Given an array of integers nums and an integer k, return the number of unique
k-diff pairs in the array.

A k-diff pair is an integer pair (nums[i], nums[j]), where the following are
true:

0 <= i, j < nums.length
i != j
nums[i] - nums[j] == k
Notice that |val| denotes the absolute value of val
*/

#include <limits.h>

#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
   public:
    int FindPairs(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end());
        int ret = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            if (binary_search(nums.begin() + i + 1, nums.end(), k + nums[i])) {
                ret++;
            }
            while (i + 1 < (int)nums.size() && nums[i + 1] == nums[i]) {
                i++;
            }
        }
        return ret;
    }

    int FindPairsV1(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end());
        int prev = INT_MIN, ret = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            auto &v = nums[i];
            if (v != prev) {
                if (binary_search(nums.begin() + i + 1, nums.end(), v + k)) {
                    ret++;
                }
                prev = v;
            }
        }
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {3, 1, 4, 1, 5};
    int k = 2;
    int output = 2;
    // Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
    // Although we have two 1s in the input, we should only return the number of
    // unique pairs.

    Solution sl;
    int ret = sl.FindPairs(nums, k);
    EXPECT_EQ(ret, output);

    ret = sl.FindPairsV1(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 1;
    int output = 4;
    // There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4,
    // 5).

    Solution sl;
    int ret = sl.FindPairs(nums, k);

    EXPECT_EQ(ret, output);

    ret = sl.FindPairsV1(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<int> nums = {1, 3, 1, 5, 4};
    int k = 0;
    int output = 1;
    // There is one 0-diff pair in the array, (1, 1).

    Solution sl;
    int ret = sl.FindPairs(nums, k);
    EXPECT_EQ(ret, output);

    ret = sl.FindPairsV1(nums, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
