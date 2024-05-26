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
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<int>> ThreeSum(vector<int> &nums) {
        std::vector<std::vector<int>> ret;

        for (size_t i = 0; i < nums.size(); i++) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                std::vector<int> ret1 = TwoSum(nums, j, 0 - nums[i]);
                if (ret1.size() == 2) {
                    ret1.push_back(nums[i]);
                    if (!HasElements(ret, ret1)) {
                        ret.push_back(ret1);
                    }
                }
            }
        }
        return ret;
    }

    vector<vector<int>> ThreeSumV2(vector<int> &nums) {
        size_t n = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        for (size_t i = 0; i < n; i++) {
            size_t target = 0 - nums[i];

            size_t front = i + 1;
            size_t back = n - 1;

            while (front < back) {
                int sum = nums[front] + nums[back];

                if (sum < target)
                    front++;
                else if (sum > target)
                    back--;
                else {
                    vector<int> temp = {nums[i], nums[front], nums[back]};
                    res.push_back(temp);

                    while (front < back && nums[front] == temp[1]) front++;
                    while (front < back && nums[back] == temp[2]) back--;
                }
            }

            while (i < n - 1 && nums[i] == nums[i + 1]) i++;
        }

        return res;
    }

    bool HasElements(const std::vector<std::vector<int>> &nums,
                     const std::vector<int> &elements) noexcept {
        for (auto &ptr : nums) {
            if (Equal(ptr, elements)) return true;
        }

        return false;
    }

    // first.size() ==3 && second.size() ==3
    // first[0] + first[1]  + first[2]  =0
    // second[0] + second[1]  + second[2]  =0
    bool Equal(const std::vector<int> &first, const std::vector<int> &second) {
        // assert(first.size() == second.size() == 3);
        if (first[0] == second[0]) {
            if (first[1] == second[1] || first[1] == second[2]) {
                return true;
            }
        }
        if (first[0] == second[1]) {
            if (first[1] == second[0] || first[1] == second[2]) {
                return true;
            }
        }
        if (first[0] == second[2]) {
            if (first[2] == second[0] || first[2] == second[1]) {
                return true;
            }
        }

        return false;
    }

    std::vector<int> TwoSum(vector<int> &nums, size_t left, int target) {
        std::vector<int> ret;
        for (size_t i = left; i < nums.size(); ++i) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return std::vector<int>{nums[i], nums[j]};
                }
            }
        }

        return ret;
    }
};


TEST(sum, t1) {
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    const std::vector<std::vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
    const std::vector<std::vector<int>> expected1 = {{-1, 0, 1}, {-1, -1, 2}};
    Solution s;
    const auto ret = s.ThreeSum(nums);
    // EXPECT_TRUE(ret == expected || ret == expected1);
}

TEST(sum, t2) {
    std::vector<int> nums = {};
    const std::vector<std::vector<int>> expected = {};
    Solution s;
    const auto ret = s.ThreeSum(nums);
    // EXPECT_EQ(ret, expected);
}

TEST(sum, t3) {
    std::vector<int> nums = {0};
    const std::vector<std::vector<int>> expected = {};
    Solution s;
    const auto ret = s.ThreeSum(nums);
    EXPECT_EQ(ret, expected);
}

} // namespace
