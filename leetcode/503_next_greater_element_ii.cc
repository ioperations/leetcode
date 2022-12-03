/*
    Given a circular integer array nums (i.e., the next element of
   nums[nums.length
    - 1] is nums[0]), return the next greater number for every element in nums.

    The next greater number of a number x is the first greater number to its
    traversing-order next in the array, which means you could search circularly
   to find its next greater number. If it doesn't exist, return -1 for this
   number.


*/

#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> NextGreaterElements(vector<int>& nums) {
        // pass
        int size = nums.size();
        vector<int> ret(size, -1);
        vector<int> copy(nums.begin(), nums.end());

        nums.insert(nums.end(), copy.begin(), copy.end());

        for (int i = 0; i < size; i++) {
            for (int j = 1; j < size; j++) {
                if (nums[i + j] > nums[i]) {
                    ret[i] = nums[i + j];
                    break;
                }
            }
        }
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {1, 2, 1};
    vector<int> output = {2, -1, 2};
    Solution sl;
    auto ret = sl.NextGreaterElements(nums);
    EXPECT_EQ(ret, output);
    // Explanation: The first 1's next greater number is 2;
    // The number 2 can't find next greater number.
    // The second 1's next greater number needs to search circularly, which is
    // also 2.
}

TEST(t0, t2) {
    vector<int> nums = {1, 2, 3, 4, 3};
    vector<int> output = {2, 3, 4, -1, 4};
    Solution sl;
    auto ret = sl.NextGreaterElements(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
