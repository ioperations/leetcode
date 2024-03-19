// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums, reorder it such that
nums[0] < nums[1] > nums[2] < nums[3]....

You may assume the input array always has a valid answer.*/

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

#define TEST(a, b) TEST_CASE(#a, #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
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

TEST(wiggle_sort_ii, t1) {
    std::vector<int> nums = {1, 5, 1, 1, 6, 4};
    std::vector<int> output = {1, 6, 1, 5, 1, 4};
    std::vector<int> output1 = {1, 4, 1, 5, 1, 6};

    Solution sl;
    sl.WiggleSort(nums);

    if (nums == output1 || nums == output) {
        REQUIRE(true);
    } else {
        REQUIRE(false);
    }
}
TEST(wiggle_sort_ii, t2) {
    std::vector<int> nums = {1, 3, 2, 2, 3, 1};
    std::vector<int> output = {2, 3, 1, 3, 1, 2};

    Solution sl;
    sl.WiggleSort(nums);

    REQUIRE(nums == output);
}
}  // namespace
