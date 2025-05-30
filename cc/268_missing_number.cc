// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array nums containing n distinct numbers in the range [0, n], return
 * the only number in the range that is missing from the array.*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int MissingNumber(vector<int>& nums) {
        int sum = 0;

        int max = 0;
        for (auto& ptr : nums) {
            sum += ptr;
            max = std::max(max, ptr);
        }
        int const ret = nums.size() * (nums.size() + 1) / 2 - sum;
        return ret;
    }
};

TEST(missing_number, t0) {
    std::vector<int> nums = {1};
    int const output = 0;
    // Explanation: n = 3 since there are 3 numbers, so all numbers are in the
    // range [0,3]. 2 is the missing number in the range since it does not
    // appear in nums.

    Solution sl;
    int const ret = sl.MissingNumber(nums);
    EXPECT_EQ(ret, output);
}

TEST(missing_number, t1) {
    std::vector<int> nums = {3, 0, 1};
    int const output = 2;
    // Explanation: n = 3 since there are 3 numbers, so all numbers are in the
    // range [0,3]. 2 is the missing number in the range since it does not
    // appear in nums.

    Solution sl;
    int const ret = sl.MissingNumber(nums);
    EXPECT_EQ(ret, output);
}

TEST(missing_number, t2) {
    std::vector<int> nums = {0, 1};
    int const output = 2;

    // n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2
    // is the missing number in the range since it does not appear in nums.

    Solution sl;
    int const ret = sl.MissingNumber(nums);
    EXPECT_EQ(ret, output);
}

TEST(missing_number, t3) {
    std::vector<int> nums = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    int const output = 8;

    // n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8
    // is the missing number in the range since it does not appear in nums.

    Solution sl;
    int const ret = sl.MissingNumber(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
