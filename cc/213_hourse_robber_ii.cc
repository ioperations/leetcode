/// you are a professional robber planning to rob houses along a street.
/// Each house has a certain amount of money stashed. All houses at this place
/// are arranged in a circle. That means the first house is the neighbor of the
/// last one. Meanwhile, adjacent houses have a security system connected, and
/// it will automatically contact the police if two adjacent houses were broken
/// into on the same night. Given an integer array nums representing the amount
/// of money of each house, return the maximum amount of money you can rob
/// tonight without alerting the police.
///
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    int Rob(vector<int> &nums) {
        // pass
        int v1 = Rob(nums, true, 1, false) + nums[0];
        int v2 = Rob(nums, false, 1, true);
        return max(v1, v2);
    }

    int Rob(vector<int> &nums, bool previous_robd, int current_index,
            bool last_can_be_robbed) {
        if (current_index >= nums.size()) {
            return 0;
        }
        if (current_index == nums.size() - 1 && !last_can_be_robbed) {
            return 0;
        }

        auto tuple =
            make_tuple(previous_robd, current_index, last_can_be_robbed);
        if (previous_robd) {
            cache[tuple] =
                Rob(nums, false, current_index + 1, last_can_be_robbed);
            return cache[tuple];
        }

        // 偷这个
        int v1 = Rob(nums, true, current_index + 1, last_can_be_robbed) +
                 nums[current_index];
        // 不偷这个家
        int v2 = Rob(nums, false, current_index + 1, last_can_be_robbed);

        cache[tuple] = max(v1, v2);
        return cache[tuple];
    }

    map<tuple<int, int, int>, int> cache;
};

TEST(hourse_robber_ii, t1) {
    vector<int> nums = {2, 3, 2};
    int output = 3;
    // Explanation : You cannot rob house 1(money = 2) and
    //      then rob house 3(money = 2),
    // because they are adjacent houses.
    Solution sl;
    int ret = sl.Rob(nums);
    EXPECT_EQ(output, ret);
}

TEST(hourse_robber_ii, t2) {
    vector<int> nums = {1, 2, 3, 1};
    int output = 4;
    // Rob house 1 (money = 1) and then rob house 3 (money = 3).
    // Total amount you can rob = 1 + 3 = 4.

    Solution sl;
    int ret = sl.Rob(nums);
    EXPECT_EQ(output, ret);
}

TEST(hourse_robber_ii, t3) {
    vector<int> nums = {
        1,
        2,
        3,
    };
    int output = 3;
    // Rob house 1 (money = 1) and then rob house 3 (money = 3).
    // Total amount you can rob = 1 + 3 = 4.

    Solution sl;
    int ret = sl.Rob(nums);
    EXPECT_EQ(output, ret);
}

}  // namespace
