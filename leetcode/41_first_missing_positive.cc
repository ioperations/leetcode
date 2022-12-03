/*

Given an unsorted integer array nums, return the smallest missing positive
integer.

You must implement an algorithm that runs in O(n) time and uses constant extra
space.

*/
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;
class Solution {
   public:
    int FirstMissingPositive(std::vector<int>& nums) {
        // 1 <= nums.length <= 5 * 10^5
        // -2^31 <= nums[i] <= 2^31 - 1
        map<int, int> m;
        for (auto i : nums) m[i]++;

        for (size_t i = 1; i <= nums.size(); i++)
            if (m[i] == 0) return i;

        return nums.size() + 1;

        return 0;
    }
    int FirstMissingPositiveV2(std::vector<int>& nums) {
        int n = nums.size();
        // making all negative to zero as they are useless
        for (int i = 0; i < n; i++) {
            if (nums[i] < 0) nums[i] = 0;
        }

        // maarking -ve for present
        for (int i = 0; i < n; i++) {
            int val = abs(nums[i]);
            if (val >= 1 && val <= n) {
                int idx = val - 1;
                if (nums[idx] == 0) {
                    nums[idx] = -(n + 1);
                } else if (nums[idx] > 0) {
                    nums[idx] *= -1;
                }
            }
        }

        // check first missing positive number
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0) return (i + 1);
        }

        return (n + 1);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> nums = {1, 2, 0};
    Solution s;
    int ret = s.FirstMissingPositive(nums);
    EXPECT_EQ(ret, 3);
}

TEST(t0, t2) {
    std::vector<int> nums = {3, 4, -1, 1};
    Solution s;
    int ret = s.FirstMissingPositive(nums);
    EXPECT_EQ(ret, 2);
}

TEST(t0, t3) {
    std::vector<int> nums = {7, 8, 9, 11, 12};
    Solution s;
    int ret = s.FirstMissingPositive(nums);
    EXPECT_EQ(ret, 1);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
