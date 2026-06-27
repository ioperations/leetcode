/**
 * You are given an array of positive integers nums.
 *
 * You need to select a subset of nums which satisfies the following condition:
 *
 * You can place the selected elements in a 0-indexed array such that it follows
 * the pattern: [x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] (Note that k
 * can be be any non-negative power of 2). For example, [2, 4, 16, 4, 2] and [3,
 * 9, 3] follow the pattern while [2, 4, 8, 4, 2] does not. Return the maximum
 * number of elements in a subset that satisfies these conditions.
 * 2 <= nums.length <= 105
 * 1 <= nums[i] <= 109
 */

#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;
namespace {

class Solution {
   public:
    int MaximumLength(vector<int>& nums) {
        for (auto& p : nums) {
            map[p]++;
        }
        for (auto p : nums) {
            Check(p, 0);
        }

        int count1 = map[1];
        return std::max(m_max, (count1 - 1) / 2 * 2 + 1);
    }
    void Check(int currnum, int max) {
        if (map[currnum] == 1) {
            m_max = std::max(m_max, max + 1);
            return;
        }
        if (inmax / currnum > currnum && map[currnum] >= 2 && currnum != 1) {
            return Check(currnum * currnum, max + 2);
        } else if (map[currnum] >= 1 && currnum != -1) {
            m_max = std::max(m_max, max + 1);
            return;
        }
        m_max = std::max(m_max, max - 1);
    }

    int m_max = 1;
    std::unordered_map<int, int> map;
    static constexpr int inmax = std::numeric_limits<int>::max();
};
}  // namespace

#include <gtest/gtest.h>

TEST(maximumLength, t0) {
    vector<int> nums = {5, 4, 1, 2, 2};
    int output = 3;
    Solution sl;
    int ret = sl.MaximumLength(nums);
    EXPECT_EQ(output, ret);
    // We can select the subset {1}, which can be placed in the array as [1]
    // which follows the pattern. Hence the answer is 1. Note that we could have
    // also selected the subsets {2}, {3}, or {4}, there may be multiple subsets
    // which provide the same answer.
}

TEST(maximumLength, t1) {
    vector<int> nums = {1, 3, 2, 4};
    int output = 1;
    Solution sl;
    int ret = sl.MaximumLength(nums);
    EXPECT_EQ(output, ret);
    // Explanation: We can select the subset {4,2,2}, which can be placed in the
    // array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer
    // is 3.
}

TEST(maximumLength, t2) {
    vector<int> nums = {1, 1};
    int output = 1;
    Solution sl;
    int ret = sl.MaximumLength(nums);
    EXPECT_EQ(output, ret);
    // Explanation: We can select the subset {4,2,2}, which can be placed in the
    // array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer
    // is 3.
}

TEST(maximumLength, t3) {
    vector<int> nums = {15, 15, 225, 225, 50625, 50625};
    int output = 5;
    Solution sl;
    int ret = sl.MaximumLength(nums);
    EXPECT_EQ(output, ret);
    // Explanation: We can select the subset {4,2,2}, which can be placed in the
    // array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer
    // is 3.
}
TEST(maximumLength, t4) {
    vector<int> nums = {1, 1, 1, 1,  1,  1,  1,   1,   1,   1,
                        2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int output = 9;
    Solution sl;
    int ret = sl.MaximumLength(nums);
    EXPECT_EQ(output, ret);
    // Explanation: We can select the subset {4,2,2}, which can be placed in the
    // array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer
    // is 3.
}
