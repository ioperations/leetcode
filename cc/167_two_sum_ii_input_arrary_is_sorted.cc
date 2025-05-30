// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given a 1-indexed array of integers numbers that is already sorted in
non-decreasing order, find two numbers such that they add up to a specific
target number. Let these two numbers be numbers[index1] and numbers[index2]
where 1 <= index1 < index2 <= numbers.length.

Return the indices of the two numbers, index1 and index2, added by one as an
integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not use
the same element twice.

Your solution must use only constant extra space.

*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<int> TwoSum(vector<int>& numbers, int target) {
        vector<int> ret;

        int const size = numbers.size();
        for (int i = 0; i < size; i++) {
            int j = 0;
            if ((j = FindInArray(numbers, i + 1, size - 1,
                                 target - numbers[i])) != 0) {
                return vector<int>{i + 1, j + 1};
            }
        }
        return ret;
    }

    int FindInArray(const vector<int>& numbers, int left, int right,
                    int target) {
        while (left <= right) {
            int const mid = (left + right) / 2;

            if (numbers[mid] > target) {
                right = mid - 1;

            } else if (numbers[mid] < target) {
                left = mid + 1;

            } else {
                return mid;
            }
        }
        return 0;
    }
};

TEST(two_sum_ii_input_arrary_is_sorted, t1) {
    vector<int> numbers = {2, 7, 11, 15};
    int const target = 9;
    vector<int> const output = {1, 2};
    // Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2.
    // We return [1, 2].
    Solution sl;
    auto ret = sl.TwoSum(numbers, target);
    EXPECT_EQ(ret, output);
}

TEST(two_sum_ii_input_arrary_is_sorted, t2) {
    vector<int> numbers = {2, 3, 4};
    int const target = 6;
    vector<int> const output = {1, 3};
    // Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2.
    // We return [1, 2].
    Solution sl;
    auto ret = sl.TwoSum(numbers, target);
    EXPECT_EQ(ret, output);
}

TEST(two_sum_ii_input_arrary_is_sorted, t3) {
    vector<int> numbers = {-1, 0};
    int const target = -1;
    vector<int> const output = {1, 2};
    // Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2.
    // We return [1, 2].
    Solution sl;
    auto ret = sl.TwoSum(numbers, target);
    EXPECT_EQ(ret, output);
}

TEST(two_sum_ii_input_arrary_is_sorted, t4) {
    vector<int> numbers = {3, 24, 50, 79, 88, 150, 345};
    int const target = 200;
    vector<int> const output = {3, 6};
    // Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2.
    // We return [1, 2].
    Solution sl;
    auto ret = sl.TwoSum(numbers, target);
    EXPECT_EQ(ret, output);
}

}  // namespace