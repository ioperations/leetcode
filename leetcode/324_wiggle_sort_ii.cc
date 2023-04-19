// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums, reorder it such that
nums[0] < nums[1] > nums[2] < nums[3]....

You may assume the input array always has a valid answer.*/

#include <algorithm>
#include <vector>

using namespace std;
class Solution {
   public:
    void WiggleSort(vector<int> &nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> sorted(n);

        int end = n - 1;
        int start = end / 2;

        int i = 0;
        while (i < n) {
            sorted[i++] = nums[start--];
            if (i < n) {
                sorted[i++] = nums[end--];
            }
        }

        nums = sorted;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> nums = {1, 5, 1, 1, 6, 4};
    std::vector<int> output = {1, 6, 1, 5, 1, 4};
    std::vector<int> output1 = {1, 4, 1, 5, 1, 6};

    Solution sl;
    sl.WiggleSort(nums);

    EXPECT_TRUE(nums == output1 || nums == output);
}
TEST(t0, t2) {
    std::vector<int> nums = {1, 3, 2, 2, 3, 1};
    std::vector<int> output = {2, 3, 1, 3, 1, 2};

    Solution sl;
    sl.WiggleSort(nums);

    EXPECT_EQ(nums, output);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
