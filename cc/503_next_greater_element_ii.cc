// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
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

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
class Solution {
   public:
    vector<int> NextGreaterElements(vector<int> &nums) {
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

TEST(next_greater_element_ii, t1) {
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

TEST(next_greater_element_ii, t2) {
    vector<int> nums = {1, 2, 3, 4, 3};
    vector<int> output = {2, 3, 4, -1, 4};
    Solution sl;
    auto ret = sl.NextGreaterElements(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
