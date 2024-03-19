// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an array of integers nums sorted in non-decreasing order, find the
starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.*/

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
    vector<int> SearchRange(vector<int> &nums, int target) {
        vector<int> ans(2, -1);
        if (nums.size() == 0) return ans;  // base case
        auto it = lower_bound(nums.begin(), nums.end(), target);
        if (it == nums.end() || *it != target)
            return ans;  // ensures that there isnt any element equal to target
        auto i = upper_bound(
            nums.begin(), nums.end(),
            target);  // gets the smallest element greater than target
        i--;          // reduced by 1 to get to the target
        if (*it == *i) {
            ans[0] = it - nums.begin();
            ans[1] = i - nums.begin();
            return ans;
        }
        return ans;
    }
};

TEST(find_first_and_last_position_of_element_in_sorted_array, t1) {
    vector<int> elements{5, 7, 7, 8, 8, 10};
    Solution sl;
    auto ret = sl.SearchRange(elements, 8);
    vector<int> output{3, 4};
    EXPECT_EQ(ret, output);
}

TEST(find_first_and_last_position_of_element_in_sorted_array, t2) {
    vector<int> elements{5, 7, 7, 8, 8, 10};
    Solution sl;
    auto ret = sl.SearchRange(elements, 6);
    vector<int> output{-1, -1};
    EXPECT_EQ(ret, output);
}

TEST(find_first_and_last_position_of_element_in_sorted_array, t3) {
    vector<int> elements{};
    Solution sl;
    auto ret = sl.SearchRange(elements, 0);
    vector<int> output{-1, -1};
    EXPECT_EQ(ret, output);
}

}  // namespace
