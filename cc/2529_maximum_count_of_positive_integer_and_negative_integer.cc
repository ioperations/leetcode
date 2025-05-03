/*
 * Given an array nums sorted in non-decreasing order, return the maximum
between the number of positive integers and the number of negative integers.

In other words, if the number of positive integers in nums is pos and the number
of negative integers is neg, then return the maximum of pos and neg. Note that 0
is neither positive nor negative.

*/

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    int MaximumCount(vector<int>& nums) {
        /*
         * 1 <= nums.length <= 2000
         * -2000 <= nums[i] <= 2000
         * nums is sorted in a non-decreasing order.
         */
        auto it = lower_bound(nums.begin(), nums.end(), 0);

        auto n = it - nums.begin();
        it = upper_bound(nums.begin(), nums.end(), 0);

        return std::max(nums.end() - it, n);
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    std::vector<int> nums{-2, -1, -1, 1, 2, 3};
    int const output = 3;
    Solution sl;
    int const ret = sl.MaximumCount(nums);
    EXPECT_EQ(ret, output);
    // There are 3 positive integers and 3 negative integers. The maximum count
    // among them is 3.
}

TEST(t0, t2) {
    std::vector<int> nums{-3, -2, -1, 0, 0, 1, 2};
    int const output = 3;
    Solution sl;
    int const ret = sl.MaximumCount(nums);
    EXPECT_EQ(ret, output);
    // There are 2 positive integers and 3 negative integers. The maximum count
    // among them is 3.
}

TEST(t0, t3) {
    std::vector<int> nums{5, 20, 66, 1314};
    int const output = 4;
    Solution sl;
    int const ret = sl.MaximumCount(nums);
    // There are 4 positive integers and 0 negative integers. The maximum count
    // among them is 4.
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
