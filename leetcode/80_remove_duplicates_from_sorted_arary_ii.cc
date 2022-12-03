/*
Given an integer array nums sorted in non-decreasing order, remove some
duplicates in-place such that each unique element appears at most twice. The
relative order of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages, you
must instead have the result be placed in the first part of the array nums. More
formally, if there are k elements after removing the duplicates, then the first
k elements of nums should hold the final result. It does not matter what you
leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array. You must do this by modifying the
input array in-place with O(1) extra memory.
*/

#include <vector>

using namespace std;
class Solution {
   public:
    int RemoveDuplicates(vector<int>& nums) {
        int idx = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (idx < 2 || nums[idx - 2] != nums[i]) {
                nums[idx++] = nums[i];
            }
        }

        return idx;
    }

    void MakeVectorBack(vector<int>& nums, int from, int end) {
        for (int i = from; i < end - 1; i++) {
            nums[i] = nums[i + 1];
        }
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int output = 5;
    vector<int> ret_expected = {1, 1, 2, 2, 3};

    // Explanation:
    // Your function should return k = 5, with the first five elements of nums
    // being 1, 1, 2, 2 and 3 respectively .It does not matter what you leave
    // beyond the returned k(hence they are underscores)
    // .

    Solution sl;
    int ret = sl.RemoveDuplicates(nums);

    EXPECT_EQ(ret, output);

    for (int i = 0; i < ret; i++) {
        EXPECT_EQ(ret_expected[i], nums[i]);
    }
}

TEST(t0, t2) {
    vector<int> nums = {0, 0, 1, 1, 1, 1, 2, 3, 3};
    int output = 7;
    vector<int> ret_expected = {0, 0, 1, 1, 2, 3, 3};

    // Your function should return k = 7, with the first seven elements of nums
    // being 0, 0, 1, 1, 2, 3 and 3 respectively.
    // It does not matter what you leave beyond the returned k (hence they are
    // underscores).

    Solution sl;
    int ret = sl.RemoveDuplicates(nums);

    EXPECT_EQ(ret, output);

    for (int i = 0; i < ret; i++) {
        EXPECT_EQ(ret_expected[i], nums[i]);
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
