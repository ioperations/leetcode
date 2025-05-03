// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given two integer arrays nums and multipliers of size n and m
respectively, where n >= m. The arrays are 1-indexed.

You begin with a score of 0. You want to perform exactly m operations. On the
ith operation (1-indexed), you will:

Choose one integer x from either the start or the end of the array nums.
Add multipliers[i] * x to your score.
Remove x from the array nums.
Return the maximum score after performing m operations.*/
#include <algorithm>
#include <climits>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int MaximumScoreV1(vector<int>& nums, vector<int>& multipliers) {
      int const n = nums.size();
      int m = multipliers.size();

      function<int(int, int, int, int)> fun = [&](int start, int end, int ith,
                                                  int value) -> int {
        if (ith == m) return value;
        if (start > end) return value;

        int const v1 = fun(start + 1, end, ith + 1,
                           value + nums[start] * multipliers[ith]);
        int const v2 =
            fun(start, end - 1, ith + 1, value + nums[end] * multipliers[ith]);

        return std::max(v1, v2);
      };
      return fun(0, n - 1, 0, 0);
    }

    int Dfs(int i, int j, vector<vector<int>>& dp, vector<int>& nums,
            vector<int>& mul, int m) {
        if (m >= (int)mul.size()) return 0;
        if (dp[i][j] != INT_MIN) return dp[i][j];
        int const idx = nums.size() - j - 1;
        int const l = nums[idx] * mul[m] + Dfs(i, j + 1, dp, nums, mul, m + 1);
        int const r = nums[i] * mul[m] + Dfs(i + 1, j, dp, nums, mul, m + 1);
        return dp[i][j] = max(l, r);
    }

   public:
    int MaximumScore(vector<int>& nums, vector<int>& mul) {
        // int n = nums.size();
        int const m = mul.size();
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, INT_MIN));
        return Dfs(0, 0, dp, nums, mul, 0);
    }
};

TEST(maximum_score_from_performing_multiplication_operations, t1) {
    vector<int> nums = {1, 2, 3}, multipliers = {3, 2, 1};
    int const output = 14;
    Solution sl;
    int const ret = sl.MaximumScore(nums, multipliers);
    /*
    Explanation: An optimal solution is as follows:
    - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
    - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
    - Choose from the end, [1], adding 1 * 1 = 1 to the score.
    The total score is 9 + 4 + 1 = 14.
    */

    EXPECT_EQ(ret, output);
}

TEST(maximum_score_from_performing_multiplication_operations, t2) {
    vector<int> nums = {-5, -3, -3, -2, 7, 1}, multipliers = {-10, -5, 3, 4, 6};
    int const output = 102;
    Solution sl;
    int const ret = sl.MaximumScore(nums, multipliers);
    /*
    An optimal solution is as follows:
    - Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the
    score.
    - Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
    - Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
    - Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
    - Choose from the end, [-2,7], adding 7 * 6 = 42 to the score.
    The total score is 50 + 15 - 9 + 4 + 42 = 102.
    */

    EXPECT_EQ(ret, output);
}
}  // namespace
