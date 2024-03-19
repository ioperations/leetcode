// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown
pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k],
nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For
example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become
[4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return
the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

*/
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
    class Solution {
    public:
        /**
          * In this question, we can solve it step by step:
          *
          * think about the method to solve this question. Since we need to search a value's
          * index at a sorted array, the best way is to use binary search. In this question,
          * there are some parts are rotated we can still use binary search to solve it with
          * some special conditions. instead of consider the mid value and target first, we
          * can consider left value and mid value. after that we need to consider an extra
          * case that whether target < nums[left] is true. If yes, it mean target value is
          * rotated, we can only find it at the part that next to the mid value. If not,
          * then let right = mid - 1 if found the answer, just return the index of mid,
          * otherwise return -1 That is my idea about this question.
          */
        int Search(vector<int> &nums, int target) {
            int left = 0;
            int right = nums.size() - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (nums[mid] == target) return mid;

                // instead of comparing target and nums[mid]
                // we need to compare nums[left] and nums[mid]
                if (nums[left] <= nums[mid]) {
                    // In addition to first condition, we also need to consider
                    // target < nums [left]
                    if (nums[mid] < target || target < nums[left]) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                } else {
                    if (nums[mid] > target || target > nums[right])
                        right = mid - 1;
                    else
                        left = mid + 1;
                }
            }
            return -1;
        }
    };


    TEST(search_in_rotated_sorted_array, t1) {
        std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
        int target = 0;
        int output = 4;
        Solution s;
        int ret = s.Search(nums, target);
        EXPECT_EQ(ret, output);
    }

    TEST(search_in_rotated_sorted_array, t2) {
        std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
        int target = 3;
        int output = -1;
        Solution s;
        int ret = s.Search(nums, target);
        EXPECT_EQ(ret, output);
    }

    TEST(search_in_rotated_sorted_array, t3) {
        std::vector<int> nums = {1};
        int target = 0;
        int output = -1;
        Solution s;
        int ret = s.Search(nums, target);
        EXPECT_EQ(ret, output);
    }
} // namespace
