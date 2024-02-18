// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*There is an integer array nums sorted in non-decreasing order (not necessarily
with distinct values).

Before being passed to your function, nums is rotated at an unknown pivot index
k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1],
..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example,
[0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become
[4,5,6,6,7,0,1,2,4,4].

Given the array nums after the rotation and an integer target, return true if
target is in nums, or false if it is not in nums.

You must decrease the overall operation steps as much as possible.

*/
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    bool Search(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (target == nums[mid]) return true;
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
            } else if (nums[left] <= nums[mid]) {
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            } else {
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return false;
    }
};



TEST(search_in_rotated_sorted_array_ii, t1) {
    vector<int> nums = {2, 5, 6, 0, 0, 1, 2};
    int target = 0;
    bool output = true;
    Solution sl;
    bool ret = sl.Search(nums, target);
    EXPECT_EQ(ret, output);
}

TEST(search_in_rotated_sorted_array_ii, t2) {
    vector<int> nums = {2, 5, 6, 0, 0, 1, 2};
    int target = 3;
    bool output = false;
    Solution sl;
    bool ret = sl.Search(nums, target);
    EXPECT_EQ(ret, output);
}

}
