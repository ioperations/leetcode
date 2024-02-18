// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

You are given an integer array nums and an integer x. In one operation, you can
either remove the leftmost or the rightmost element from the array nums and
subtract its value from x. Note that this modifies the array for future
operations.

Return the minimum number of operations to reduce x to exactly 0 if it is
possible, otherwise, return -1.

*/

#include <algorithm>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    int MinOperations(vector<int> &nums, int x) {
        int sum = 0;
        int n = nums.size();
        int len = 0;

        //         calculate the sum of array
        for (int i : nums) {
            sum += i;
        }
        //         if total sum is equal to x then return size of array
        if (sum == x) return n;

        //         here we use sliding window algorithm
        int i = 0, j = 0;
        int pre_sum = 0;
        while (j < n) {
            pre_sum += nums[j];
            //             here (sum-preSum) represent sum of end points
            // if (sum-preSum) i.e. the sum of end points is greater than x we
            // have to increase the size of window
            if ((sum - pre_sum) > x) {
                j++;
            }
            //             if we found sum of end points is equal to x then
            //             store this and check further if better solution is
            //             present or not
            else if ((sum - pre_sum) == x) {
                len = max((j - i + 1), len);
                j++;
            }
            //             if sum of end points less than x we have to shrink
            //             the window
            else {
                while (i < j && (sum - pre_sum) < x) {
                    pre_sum -= nums[i];
                    i++;
                }
                if ((sum - pre_sum) == x) len = max((j - i + 1), len);
                j++;
            }
        }

        //         if len is not updated then answer is not possible
        if (len == 0) {
            return -1;
        }
        return n - len;
    }
};



TEST(minimium_operations_to_reduce_x_to_zero, t1) {
    vector<int> nums = {1, 1, 4, 2, 3};
    int x = 5;
    int output = 2;
    // Explanation: The optimal solution is to remove the last two elements to
    // reduce x to zero.
    Solution sl;
    int ret = sl.MinOperations(nums, x);
    EXPECT_EQ(ret, output);
}

TEST(minimium_operations_to_reduce_x_to_zero, t2) {
    vector<int> nums = {5, 6, 7, 8, 9};
    int x = 4;
    int output = -1;
    // Explanation: The optimal solution is to remove the last two elements to
    // reduce x to zero.
    Solution sl;
    int ret = sl.MinOperations(nums, x);
    EXPECT_EQ(ret, output);
}

TEST(minimium_operations_to_reduce_x_to_zero, t3) {
    vector<int> nums = {3, 2, 20, 1, 1, 3};
    int x = 10;
    int output = 5;

    // The optimal solution is to remove the last three elements and the first
    // two elements (5 operations in total) to reduce x to zero.

    Solution sl;

    int ret = sl.MinOperations(nums, x);
    EXPECT_EQ(ret, output);
}
}
