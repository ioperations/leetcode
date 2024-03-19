// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    Given an integer array nums of size n, return the minimum number of moves
    required to make all array elements equal.
    In one move, you can increment or decrement an element of the array by 1.
    Test cases are designed so that the answer will fit in a 32-bit integer.
*/

#include <stdlib.h>

#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
class Solution {
   public:
    int MinMoves2(vector<int> &nums) {
        // pass
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int mid = 0;
        if (n % 2 != 0) {
            mid = nums[n / 2];
        } else {
            mid = nums[(n + 1) / 2];
        }

        int move = 0;
        for (int x : nums) {
            move += abs(x - mid);
        }
        return move;
    }
};

TEST(minimum_moves_to_equal_array_elements_ii, t1) {
    vector<int> nums{1, 2, 3};
    int output = 2;
    Solution sl;
    int ret = sl.MinMoves2(nums);
    // Only two moves are needed (remember each move increments or decrements
    // one element): [1,2,3]  =>  [2,2,3]  =>  [2,2,2]
    EXPECT_EQ(ret, output);
}

TEST(minimum_moves_to_equal_array_elements_ii, t2) {
    vector<int> nums{1, 10, 2, 9};
    int output = 16;
    Solution sl;
    int ret = sl.MinMoves2(nums);
    EXPECT_EQ(ret, output);
}
}  // namespace
