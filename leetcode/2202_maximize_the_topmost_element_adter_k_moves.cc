/*You are given a 0-indexed integer array nums representing the contents of a
pile, where nums[0] is the topmost element of the pile.

In one move, you can perform either of the following:

If the pile is not empty, remove the topmost element of the pile.
If there are one or more removed elements, add any one of them back onto the
pile. This element becomes the new topmost element. You are also given an
integer k, which denotes the total number of moves to be made.

Return the maximum value of the topmost element of the pile possible after
exactly k moves. In case it is not possible to obtain a non-empty pile after k
moves, return -1.*/

#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
   public:
    int MaximumTop(vector<int> &nums, int k) {
        // sloution v1
        int z_max = -1;
        if (nums.size() == 1 && k % 2 == 1) return -1;
        if (k == 1 || k == 0) return nums[k];
        for (int i = 0; i < (int)nums.size(); i++) {
            if (nums[i] > z_max) z_max = nums[i];
            k--;
            if (k <= 1) {
                if (nums[i + 2] > z_max) return nums[i + 2];
                break;
            }
        }
        return z_max;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> nums{5, 2, 2, 4, 0, 6};
    int k = 4;
    int output = 5;
    Solution sl;
    int ret = sl.MaximumTop(nums, k);
    /*One of the ways we can end with 5 at the top of the pile after 4 moves is
    as follows:
    - Step 1: Remove the topmost element = 5. The pile becomes [2,2,4,0,6].
    - Step 2: Remove the topmost element = 2. The pile becomes [2,4,0,6].
    - Step 3: Remove the topmost element = 2. The pile becomes [4,0,6].
    - Step 4: Add 5 back onto the pile. The pile becomes [5,4,0,6].
    Note that this is not the only way to end with 5 at the top of the pile. It
    can be shown that 5 is the largest answer possible after 4 moves.
    */
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<int> nums{2};
    int k = 1;
    int output = -1;
    Solution sl;
    int ret = sl.MaximumTop(nums, k);
    /* In the first move, our only option is to pop the topmost element of the
    pile. Since it is not possible to obtain a non-empty pile after one move, we
    return -1.*/
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    std::vector<int> nums{99, 95, 68, 24, 18};
    int k = 69;
    int output = 99;
    Solution sl;
    int ret = sl.MaximumTop(nums, k);
    /* In the first move, our only option is to pop the topmost element of the
    pile. Since it is not possible to obtain a non-empty pile after one move, we
    return -1.*/
    EXPECT_EQ(ret, output);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
