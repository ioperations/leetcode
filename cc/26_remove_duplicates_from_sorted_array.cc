// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer array nums sorted in non-decreasing order, remove the
duplicates in-place such that each unique element appears only once. The
relative order of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages, you
must instead have the result be placed in the first part of the array nums. More
formally, if there are k elements after removing the duplicates, then the first
k elements of nums should hold the final result. It does not matter what you
leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array. You must do this by modifying the
input array in-place with O(1) extra memory.

Custom Judge:

The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
If all assertions pass, then your solution will be accepted.



Example 1:
*/

#include <functional>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int RemoveDuplicates(vector<int>& nums) {
        priority_queue<int, vector<int>, std::greater<>> q;
        int last = 0;
        bool last_set = false;
        for (auto& ptr : nums) {
            if (last_set) {
                if (ptr != last) {
                    last = ptr;
                    q.push(ptr);
                }
            } else {
                last = ptr;
                last_set = true;
                q.push(ptr);
            }
        }

        int i = 0;
        while (q.size()) {
            nums[i] = q.top();
            q.pop();
            i++;
        }
        return i;
    }
};

TEST(remove_duplicates_from_sorted_array, t1) {
    std::vector<int> nums = {1, 1, 2};
    int const output = 2;
    std::vector<int> nums_expected = {1, 2};
    Solution sl;
    int const k = sl.RemoveDuplicates(nums);
    EXPECT_EQ(k, output);
    for (int i = 0; i < output; i++) {
        EXPECT_EQ(nums[i], nums_expected[i]);
    }
}
TEST(remove_duplicates_from_sorted_array, t2) {
    std::vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int const output = 5;
    std::vector<int> nums_expected = {0, 1, 2, 3, 4};
    Solution sl;
    int const k = sl.RemoveDuplicates(nums);
    EXPECT_EQ(k, output);
    for (int i = 0; i < output; i++) {
        EXPECT_EQ(nums[i], nums_expected[i]);
    }
}

}  // namespace
