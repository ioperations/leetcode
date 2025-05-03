/*You are given an integer array nums. The absolute sum of a subarray [numsl,
numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.

Note that abs(x) is defined as follows:

If x is a negative integer, then abs(x) = -x.
If x is a non-negative integer, then abs(x) = x.
*/
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
   public:
    template <typename M>
    int Calculate(vector<int>& nums, M&& m) {
      /*
       * Kadane’s algorithm is to traverse over the array from left to right
       * and for each element, find the maximum sum among all subarrays ending
       * at that element. The result will be the maximum of all these values.
       * 以某一个元素结尾的子数组 总和最大值 是前一个
       *  .......................................... 的 最大值 加上本元素的值
       *  或者
       *      就是本元素的值
       *
       *      取决于前一个.......................... 最大值 是正输还是负数
       */
      int res = nums[0];
      int max_ending = nums[0];

      for (auto i = 1; i < nums.size(); ++i) {
        max_ending = m(max_ending + nums[i], nums[i]);
        res = m(res, max_ending);
      }
      return res;
    }

    int MaxAbsoluteSum(vector<int>& nums) {
      int const ma =
          Calculate(nums, [](int a, int b) { return std::max(a, b); });
      int const mi =
          Calculate(nums, [](int a, int b) { return std::min(a, b); });
      return max(abs(ma), abs(mi));
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums = {1, -3, 2, 3, -4};
    int const output = 5;
    // Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
    Solution sl;
    auto ret = sl.MaxAbsoluteSum(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {2, -5, 1, -4, 3, -2};
    int const output = 8;
    //  The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.
    Solution sl;
    auto ret = sl.MaxAbsoluteSum(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
