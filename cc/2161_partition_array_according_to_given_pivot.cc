/*
 * You are given a 0-indexed integer array nums and an integer pivot. Rearrange
nums such that the following conditions are satisfied:

Every element less than pivot appears before every element greater than pivot.
Every element equal to pivot appears in between the elements less than and
greater than pivot. The relative order of the elements less than pivot and the
elements greater than pivot is maintained. More formally, consider every pi, pj
where pi is the new position of the ith element and pj is the new position of
the jth element. If i < j and both elements are smaller (or larger) than pivot,
then pi < pj. Return nums after the rearrangement.

*/

#include <queue>
#include <utility>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> pivotArray(vector<int> &nums, int pivot) {
        vector<int> left;
        vector<int> middle;
        vector<int> right;
        for (auto &n : nums) {
            if (n < pivot) {
                left.push_back(n);
            } else if (n == pivot) {
                middle.push_back(n);
            } else {
                right.push_back(n);
            }
        }
        for (auto &q : middle) {
            left.push_back(q);
        }

        for (auto &q : right) {
            left.push_back(q);
        }

        return left;
    }

    vector<int> pivotArrayV2(vector<int> &nums, int pivot) {
        vector<int> result(nums.size(), 0);
        int left = 0, right = nums.size() - 1;

        for (int i = 0, j = nums.size() - 1; i < nums.size(); ++i, --j) {
            if (nums[i] < pivot) {
                result[left] = nums[i];
                left++;
            }

            if (nums[j] > pivot) {
                result[right] = nums[j];
                right--;
            }
        }

        while (left <= right) {
            result[left] = pivot;
            left++;
        }

        return result;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums = {9, 12, 5, 10, 14, 3, 10};
    int pivot = 10;
    vector<int> output = {9, 5, 3, 10, 10, 12, 14};
    Solution sl;
    auto ret = sl.pivotArray(nums, pivot);
    EXPECT_EQ(ret, output);

    ret = sl.pivotArrayV2(nums, pivot);
    EXPECT_EQ(ret, output);
    // Explanation:
    // The elements 9, 5, and 3 are less than the pivot so they are on the left
    // side of the array. The elements 12 and 14 are greater than the pivot so
    // they are on the right side of the array. The relative ordering of the
    // elements less than and greater than pivot is also maintained. [9, 5, 3]
    // and [12, 14] are the respective orderings.
    //
}

TEST(t0, t2) {
    vector<int> nums = {-3, 4, 3, 2};
    int pivot = 2;
    vector<int> output = {-3, 2, 4, 3};
    Solution sl;
    auto ret = sl.pivotArray(nums, pivot);
    EXPECT_EQ(ret, output);

    ret = sl.pivotArrayV2(nums, pivot);
    EXPECT_EQ(ret, output);
    // Explanation:
    // The element -3 is less than the pivot so it is on the left side of the
    // array.
    // The elements 4 and 3 are greater than the pivot so they are on the right
    // side of the array. The relative ordering of the elements less than and
    // greater than pivot is also maintained. [-3] and [4, 3] are the respective
    // orderings.
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
