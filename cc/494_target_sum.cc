// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and
'-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and
concatenate them to build the expression "+2-1". Return the number of different
expressions that you can build, which evaluates to target.
*/

#include <vector>
using namespace std;

class Solution {
   public:
    int FindTargetSumWaysV2(vector<int> &nums, int target) {
        /*
            1<= nums.length <= 20
            0 <= nums[i] <= 1000
            0 <= sum(nums[i]) <= 1000
            -1000 <= target <= 1000
        */
        return 0;
    }
    int FindTargetSumWays(vector<int> &nums, int target) {
        int count = 0;
        int sum = 0;
        Backtrack(nums, target, 0, count, sum);
        return count;
    }

    void Backtrack(vector<int> &nums, int target, int index, int &count,
                   int &sum) {
        if (index == (int)nums.size()) {
            if (target == sum) count++;
        } else {
            int temp_add = sum + nums[index];
            int temp_minus = sum - nums[index];
            Backtrack(nums, target, index + 1, count, temp_add);
            Backtrack(nums, target, index + 1, count, temp_minus);
        }
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;

    Solution sl;
    /*
        There are 5 ways to assign symbols to make the sum of nums be target 3.
        -1 + 1 + 1 + 1 + 1 = 3
        +1 - 1 + 1 + 1 + 1 = 3
        +1 + 1 - 1 + 1 + 1 = 3
        +1 + 1 + 1 - 1 + 1 = 3
        +1 + 1 + 1 + 1 - 1 = 3
    */
    int ret = sl.FindTargetSumWays(nums, target);
    EXPECT_EQ(ret, 5);
}

TEST(t0, t2) {
    std::vector<int> nums = {1};
    int target = 1;

    Solution sl;
    int ret = sl.FindTargetSumWays(nums, target);
    EXPECT_EQ(ret, 1);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
