// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an array of integers nums sorted in non-decreasing order, find the
starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    vector<int> SearchRange(vector<int>& nums, int target) {
        vector<int> ans(2, -1);
        if (nums.empty()) {
            return ans;
        }
        auto it = std::lower_bound(nums.begin(), nums.end(), target);
        if (it == nums.end() || *it != target) {
            return ans;
        }
        auto i = std::upper_bound(nums.begin(), nums.end(), target);
        --i;
        if (*it == *i) {
            ans.at(0) = static_cast<int>(it - nums.begin());
            ans.at(1) = static_cast<int>(i - nums.begin());
            return ans;
        }
        return ans;
    }
};

TEST(FindFirstAndLastPositionOfElementInSortedArray, t1) {
    vector<int> elements{5, 7, 7, 8, 8, 10};
    Solution sl;
    auto ret = sl.SearchRange(elements, 8);
    vector<int> const output{3, 4};
    EXPECT_EQ(ret, output);
}

TEST(FindFirstAndLastPositionOfElementInSortedArray, t2) {
    vector<int> elements{5, 7, 7, 8, 8, 10};
    Solution sl;
    auto ret = sl.SearchRange(elements, 6);
    vector<int> const output{-1, -1};
    EXPECT_EQ(ret, output);
}

TEST(FindFirstAndLastPositionOfElementInSortedArray, t3) {
    vector<int> elements{};
    Solution sl;
    auto ret = sl.SearchRange(elements, 0);
    vector<int> const output{-1, -1};
    EXPECT_EQ(ret, output);
}

}  // namespace
