/*
    Given an integer array nums of size n, return the minimum number of moves
    required to make all array elements equal.
    In one move, you can increment or decrement an element of the array by 1.
    Test cases are designed so that the answer will fit in a 32-bit integer.
*/

#include <algorithm>
#include <vector>

using namespace std;
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

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums{1, 2, 3};
    int output = 2;
    Solution sl;
    int ret = sl.MinMoves2(nums);
    // Only two moves are needed (remember each move increments or decrements
    // one element): [1,2,3]  =>  [2,2,3]  =>  [2,2,2]
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums{1, 10, 2, 9};
    int output = 16;
    Solution sl;
    int ret = sl.MinMoves2(nums);
    EXPECT_EQ(ret, output);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
