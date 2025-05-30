// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A permutation of an array of integers is an arrangement of its members into a
sequence or linear order.

For example, for arr = [1,2,3], the following are considered permutations of
arr: [1,2,3], [1,3,2], [3,1,2], [2,3,1]. The next permutation of an array of
integers is the next lexicographically greater permutation of its integer. More
formally, if all the permutations of the array are sorted in one container
according to their lexicographical order, then the next permutation of that
array is the permutation that follows it in the sorted container. If such
arrangement is not possible, the array must be rearranged as the lowest possible
order (i.e., sorted in ascending order).

For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not
have a lexicographical larger rearrangement. Given an array of integers nums,
find the next permutation of nums.

The replacement must be in place and use only constant extra memory.
*/

#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    void NextPermutation(vector<int>& nums) {
        bool flag = false;

        for (int i = nums.size() - 1; i > 0; i--) {
            if (nums[i] > nums[i - 1]) {
                flag = true;
                int j = nums.size() - 1;
                while (nums[j] <= nums[i - 1]) {
                    j--;
                }
                swap(nums[i - 1], nums[j]);
                reverse(nums.begin() + i, nums.end());
                break;
            }
        }
        if (flag == false) {
            reverse(nums.begin(), nums.end());
        }
    }
};

TEST(next_permutation, t1) {
    vector<int> nums = {1, 2, 3};
    vector<int> const output = {1, 3, 2};
    Solution sl;
    sl.NextPermutation(nums);
    EXPECT_EQ(nums, output);
}

TEST(next_permutation, t2) {
    vector<int> nums = {3, 2, 1};
    vector<int> const output = {1, 2, 3};
    Solution sl;
    sl.NextPermutation(nums);
    EXPECT_EQ(nums, output);
}

TEST(next_permutation, t3) {
    vector<int> nums = {1, 1, 5};
    vector<int> const output = {1, 5, 1};
    Solution sl;
    sl.NextPermutation(nums);
    EXPECT_EQ(nums, output);
}

}  // namespace
