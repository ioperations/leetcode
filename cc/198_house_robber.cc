// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*You are a professional robber planning to rob houses along a street. Each
house has a certain amount of money stashed, the only constraint stopping you
from robbing each of them is that adjacent houses have security systems
connected and it will automatically contact the police if two adjacent houses
were broken into on the same night.

Given an integer array nums representing the amount of money of each house,
return the maximum amount of money you can rob tonight without alerting the
police.*/
#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int Rob(vector<int> &nums) {
        int size = nums.size();

        if (size == 1) {
            return nums[0];
        }
        if (size == 2) {
            return max(nums[0], nums[1]);
        }
        std::map<int, int> cache;

        function<int(int)> fun = [&](int index) -> int {
            if (index == size - 1) return nums[index];
            if (cache.count(index)) return cache[index];
            int m1 = fun(index + 1);
            if (index + 2 < size) {
                int m2 = nums[index] + fun(index + 2);
                int tmp = max(m1, m2);

                cache[index] = tmp;
                return tmp;
            }
            int tmp = std::max(m1, nums[index]);
            cache[index] = tmp;
            return tmp;
        };
        int t1 = fun(0);
        int t2 = fun(1);
        return max(t1, t2);
    }
};

TEST(house_robber, t1) {
    std::vector<int> nums{1, 2, 3, 1};
    int output = 4;
    Solution sl;
    int ret = sl.Rob(nums);
    /*Rob house 1 (money = 1) and then rob house 3 (money = 3).
    Total amount you can rob = 1 + 3 = 4.
    */
    EXPECT_EQ(ret, output);
}

TEST(house_robber, t2) {
    std::vector<int> nums{2, 7, 9, 3, 1};
    int output = 12;
    Solution sl;
    int ret = sl.Rob(nums);
    /*Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money =
    1). Total amount you can rob = 2 + 9 + 1 = 12.*/
    EXPECT_EQ(ret, output);
}

TEST(house_robber, t3) {
    std::vector<int> nums{1, 1, 1};
    int output = 2;
    Solution sl;
    int ret = sl.Rob(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
