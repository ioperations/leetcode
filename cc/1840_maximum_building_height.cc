/**
 * @file 1840_maximum_building_height.cc
 * @brief
 * @version 0.1
 * @date 2026-06-20
 *
 * @copyright Copyright (c) 2026
 *
 * You want to build n new buildings in a city. The new buildings will be built
 * in a line and are labeled from 1 to n.
 *
 * However, there are city restrictions on the heights of the new buildings:
 *
 * The height of each building must be a non-negative integer.
 * The height of the first building must be 0.
 * The height difference between any two adjacent buildings cannot exceed 1.
 * Additionally, there are city restrictions on the maximum height of specific
 * buildings. These restrictions are given as a 2D integer array restrictions
 * where restrictions[i] = [idi, maxHeighti] indicates that building idi must
 * have a height less than or equal to maxHeighti.
 *
 * It is guaranteed that each building will appear at most once in restrictions,
 * and building 1 will not be in restrictions.
 *
 * Return the maximum possible height of the tallest building.
 *
 * 2 <= n <= 109
 * 0 <= restrictions.length <= min(n - 1, 105)
 * 2 <= idi <= n
 * idi is unique.
 * 0 <= maxHeighti <= 109
 */

#include <algorithm>
#include <vector>

namespace {

class Solution {
    // 左边有限制的楼 最高能建多高
    // 右边有限制的楼 最高能建多高
    // 取右边有限制的楼， 最高值， 看左边的楼能不能满足右边的楼的要求
    void PropagateLeftToRight(
        std::vector<std::vector<int>>& restrictions) const {
        for (int i = 0; i + 1 < (int)restrictions.size(); i++) {
            const auto& now = restrictions[i];
            int now_index = now[0];
            int now_max_height = now[1];

            auto& right_restri = restrictions[i + 1];
            int right_index = right_restri[0];
            int& right_max_height = right_restri[1];

            int length = right_index - now_index;
            if (right_max_height > now_max_height) {
                if (now_max_height + length < right_max_height) {
                    right_max_height = now_max_height + length;
                }
            }
        }
    }

    // 取左边有限制的楼， 假设设置为左高值，
    // 看右边的楼能不能满足右边的楼的要求
    void PropagateRightToLeft(
        std::vector<std::vector<int>>& restrictions) const {
        for (int i = (int)restrictions.size() - 1; i > 0; i--) {
            const auto& now = restrictions[i];
            int now_index = now[0];
            int now_max_height = now[1];

            auto& left_restri = restrictions[i - 1];
            int left_index = left_restri[0];
            int& left_max_height = left_restri[1];

            int length = now_index - left_index;
            if (left_max_height > now_max_height) {
                if (now_max_height + length < left_max_height) {
                    left_max_height = now_max_height + length;
                }
            }
        }
    }

    int ComputeMaxHeight(int n,
                         std::vector<std::vector<int>>& restrictions) const {
        if (restrictions.empty()) return n - 1;

        int max = std::max(restrictions[0][1], restrictions.back()[1]);
        for (int i = 0; i + 1 < (int)restrictions.size(); i++) {
            const auto& now = restrictions[i];
            int now_index = now[0];
            int now_max_height = now[1];

            auto& right_restri = restrictions[i + 1];
            int right_index = right_restri[0];
            int& right_max_height = right_restri[1];

            int length = right_index - now_index;
            int best = (length + right_max_height + now_max_height) / 2;
            max = std::max(max, best);
        }
        return max;
    }

    void BuildAndSort(int n, std::vector<std::vector<int>>& restrictions) {
        restrictions.insert(restrictions.begin(), std::vector<int>{1, 0});
        auto it = std::find_if(
            restrictions.begin(), restrictions.end(),
            [n](const std::vector<int>& p) { return p[0] == n - 1; });
        if (it == restrictions.end()) {
            restrictions.insert(restrictions.end(), std::vector<int>{n, n});
        }
        std::sort(restrictions.begin(), restrictions.end(),
                  [](const auto& l, const auto& r) { return l[0] < r[0]; });
    }

   public:
    int MaxBuilding(int n, std::vector<std::vector<int>>& restrictions) {
        BuildAndSort(n, restrictions);

        PropagateLeftToRight(restrictions);
        PropagateRightToLeft(restrictions);
        return ComputeMaxHeight(n, restrictions);
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(maxBuilding, t1) {
    int n = 5;
    std::vector<std::vector<int>> restrictions = {{2, 1}, {4, 1}};
    int output = 2;
    Solution sl;
    int ret = sl.MaxBuilding(n, restrictions);
    EXPECT_EQ(output, ret);
    // The green area in the image indicates the maximum allowed
    // height for each building. We can build the buildings with heights
    // [0,1,2,1,2], and the tallest building has a height of 2.
}

TEST(maxBuilding, t2) {
    int n = 6;
    std::vector<std::vector<int>> restrictions = {};
    int output = 5;
    Solution sl;
    int ret = sl.MaxBuilding(n, restrictions);
    EXPECT_EQ(output, ret);
    // The green area in the image indicates the maximum allowed height for
    // each building.
    // We can build the buildings with heights [0,1,2,3,4,5], and the tallest
    // building has a height of 5.
}

TEST(maxBuilding, t3) {
    int n = 10;
    std::vector<std::vector<int>> restrictions = {
        {5, 3}, {2, 5}, {7, 4}, {10, 3}};
    int output = 5;
    Solution sl;
    int ret = sl.MaxBuilding(n, restrictions);
    EXPECT_EQ(output, ret);
    // The green area in the image indicates the maximum allowed height for each
    // building.
    // We can build the buildings with heights [0,1,2,3,3,4,4,5,4,3], and the
    // tallest building has a height of 5.
}

TEST(maxBuilding, t4) {
    int n = 10;
    std::vector<std::vector<int>> restrictions = {{6, 0}, {5, 2}, {7, 0},
                                                  {9, 1}, {2, 4}, {3, 4},
                                                  {4, 0}, {8, 2}, {10, 0}};
    int output = 1;
    Solution sl;
    int ret = sl.MaxBuilding(n, restrictions);
    EXPECT_EQ(output, ret);
    // The green area in the image indicates the maximum allowed height for each
    // building.
    // We can build the buildings with heights [0,1,2,3,3,4,4,5,4,3], and the
    // tallest building has a height of 5.
}
