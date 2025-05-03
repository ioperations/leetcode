/**
 * You are given a 0-indexed array nums consisting of positive integers. You can
 * choose two indices i and j, such that i != j, and the sum of digits of the
 * number nums[i] is equal to that of nums[j].
 *
 * Return the maximum value of nums[i] + nums[j] that you can obtain over all
 * possible indices i and j that satisfy the conditions.
 */

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int MaximumSum(vector<int>& nums) {
      // 1 <= nums.length <= 105
      // 1 <= nums[i] <= 109
      unordered_map<int, priority_queue<int>> map;

      for (auto& ptr : nums) {
        map[GetDigitSum(ptr)].emplace(ptr);
      }

      int ret = -1;
      for (auto& it : map) {
        auto& n = it.second;
        if (n.size() > 1) {
          int v = n.top();
          n.pop();
          v += n.top();

          ret = std::max(ret, v);
        }
      }
      return ret;
    }
    int GetDigitSum(int n) {
      int ret = 0;
      for (; n > 0;) {
        ret += n % 10;
        n = n / 10;
      }
      return ret;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums{18, 43, 36, 13, 7};
    int const output = 54;
    Solution sl;
    int const ret = sl.MaximumSum(nums);
    EXPECT_EQ(ret, output);
    // Explanation: The pairs (i, j) that satisfy the conditions are:
    // - (0, 2), both numbers have a sum of digits equal to 9, and their sum is
    // 18 + 36 = 54.
    // - (1, 4), both numbers have a sum of digits equal to 7, and their sum is
    // 43 + 7 = 50. So the maximum sum that we can obtain is 54.
}

TEST(t0, t2) {
    vector<int> nums{10, 12, 19, 14};
    int const output = -1;
    Solution sl;
    int const ret = sl.MaximumSum(nums);
    EXPECT_EQ(ret, output);
    // Explanation:
    // There are no two numbers that satisfy the conditions, so we return -1.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
