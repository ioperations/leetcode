/*

Given an integer array nums, move all the even integers at the beginning of the
array followed by all the odd integers.

Return any array that satisfies this condition.

*/

#include <functional>
#include <queue>
#include <set>
#include <vector>
using namespace std;

class Solution {
    struct Fun {
        bool operator()(int a, int b) {
            if (a % 2 == 0 && b % 2 == 0) {
                return false;
            }
            if (a % 2 == 0 && b % 2 != 0) {
                return false;
            }
            if (a % 2 != 0 && b % 2 == 0) {
                return true;
            }
            if (a % 2 != 0 && b % 2 != 0) {
                return false;
            }
            return false;
        }
    };

   public:
    vector<int> SortArrayByParity(vector<int> &nums) {
        priority_queue<int, std::vector<int>, Fun> q;

        for (auto &ptr : nums) {
            q.push(ptr);
        }

        int i = 0;
        while (q.size()) {
            nums[i] = q.top();
            i++;
            q.pop();
        }

        return nums;
    }
};

class SolutionV2 {
   public:
    vector<int> SortArrayByParity(vector<int> &nums) {
        // pass
        int n = nums.size();

        int last_odd_index = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 0 and last_odd_index != -1) {
                swap(nums[last_odd_index], nums[i]);
                last_odd_index++;
            }

            if (nums[i] % 2 != 0 and last_odd_index == -1) {
                last_odd_index = i;
            }
        }

        return nums;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> nums = {3, 1, 2, 4};
    std::set<std::vector<int>> output = {
        {4, 2, 3, 1}, {2, 4, 1, 3}, {4, 2, 1, 3}, {2, 4, 3, 1}};
    Solution sl;
    auto ret = sl.SortArrayByParity(nums);

    EXPECT_TRUE(output.count(ret) == true);
}

TEST(t1, t1) {
    std::vector<int> nums = {3, 1, 2, 4};
    std::set<std::vector<int>> output = {
        {4, 2, 3, 1}, {2, 4, 1, 3}, {4, 2, 1, 3}, {2, 4, 3, 1}};
    SolutionV2 sl;
    auto ret = sl.SortArrayByParity(nums);

    EXPECT_TRUE(output.count(ret) == true);
}

TEST(t0, t2) {
    std::vector<int> nums = {0};
    std::vector<int> output = {0};
    Solution sl;
    auto ret = sl.SortArrayByParity(nums);

    EXPECT_EQ(ret, output);
}

TEST(t1, t2) {
    std::vector<int> nums = {0};
    std::vector<int> output = {0};
    SolutionV2 sl;
    auto ret = sl.SortArrayByParity(nums);

    EXPECT_EQ(ret, output);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
