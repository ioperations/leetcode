// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer array nums,
    return all the triplets[nums[i], nums[j], nums[k]] such that i != j, i != k,
    and j != k,
    and nums[i] + nums[j] + nums[k] ==
        0.

        Notice that the solution set must not contain duplicate triplets.
*/

#include <algorithm>
#include <cstddef>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<int>> ThreeSum(vector<int>& nums) {
        std::vector<std::vector<int>> ret;

        for (size_t i = 0; i < nums.size(); i++) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                std::vector<int> ret1 = TwoSum(nums, j, 0 - nums.at(i));
                if (ret1.size() == 2) {
                    ret1.push_back(nums.at(i));
                    if (!HasElements(ret, ret1)) {
                        ret.push_back(ret1);
                    }
                }
            }
        }
        return ret;
    }

    vector<vector<int>> ThreeSumV2(vector<int>& nums) {
        size_t const n = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        for (size_t i = 0; i < n; i++) {
            size_t const target = 0 - nums.at(i);

            size_t front = i + 1;
            size_t back = n - 1;

            while (front < back) {
                int const sum = nums.at(front) + nums.at(back);

                if (sum < target) {
                    front++;
                } else if (sum > target) {
                    back--;
                } else {
                    vector<int> temp = {nums.at(i), nums.at(front), nums.at(back)};
                    res.push_back(temp);

                    while (front < back && nums.at(front) == temp.at(1)) front++;
                    while (front < back && nums.at(back) == temp.at(2)) back--;
                }
            }

            while (i < n - 1 && nums.at(i) == nums.at(i + 1)) i++;
        }

        return res;
    }

    bool HasElements(const std::vector<std::vector<int>>& nums,
                     const std::vector<int>& elements) noexcept {
        for (auto& ptr : nums) {
            if (Equal(ptr, elements)) return true;
        }

        return false;
    }

    // first.size() ==3 && second.size() ==3
    // first[0] + first[1]  + first[2]  =0
    // second[0] + second[1]  + second[2]  =0
    bool Equal(const std::vector<int>& first, const std::vector<int>& second) {
        // assert(first.size() == second.size() == 3);
        if (first.at(0) == second.at(0)) {
            if (first.at(1) == second.at(1) || first.at(1) == second.at(2)) {
                return true;
            }
        }
        if (first.at(0) == second.at(1)) {
            if (first.at(1) == second.at(0) || first.at(1) == second.at(2)) {
                return true;
            }
        }
        if (first.at(0) == second.at(2)) {
            if (first.at(2) == second.at(0) || first.at(2) == second.at(1)) {
                return true;
            }
        }

        return false;
    }

    std::vector<int> TwoSum(vector<int>& nums, size_t left, int target) {
        std::vector<int> ret;
        for (size_t i = left; i < nums.size(); ++i) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums.at(i) + nums.at(j) == target) {
                    return {nums.at(i), nums.at(j)};
                }
            }
        }

        return ret;
    }
};

TEST(Sum, t1) {
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    const std::vector<std::vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
    const std::vector<std::vector<int>> expected1 = {{-1, 0, 1}, {-1, -1, 2}};
    Solution s;
    const auto ret = s.ThreeSum(nums);
    // EXPECT_TRUE(ret == expected || ret == expected1);
}

TEST(Sum, t2) {
    std::vector<int> nums = {};
    const std::vector<std::vector<int>> expected = {};
    Solution s;
    const auto ret = s.ThreeSum(nums);
    // EXPECT_EQ(ret, expected);
}

TEST(Sum, t3) {
    std::vector<int> nums = {0};
    const std::vector<std::vector<int>> expected = {};
    Solution s;
    const auto ret = s.ThreeSum(nums);
    EXPECT_EQ(ret, expected);
}

}  // namespace
