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

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
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

TEST(target_sum, t1) {
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

TEST(target_sum, t2) {
    std::vector<int> nums = {1};
    int target = 1;

    Solution sl;
    int ret = sl.FindTargetSumWays(nums, target);
    EXPECT_EQ(ret, 1);
}

}  // namespace
