// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You are given an integer array nums of length n.

    Assume arrk to be an array obtained by rotating nums by k positions
   clock-wise. We define the rotation function F on nums as follow:

    F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1].
    Return the maximum value of F(0), F(1), ..., F(n-1).

    The test cases are generated so that the answer fits in a 32-bit integer.
*/

#include <limits.h>
#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    int MaxRotateFunction(vector<int> &nums) {
        int size = nums.size();

        int tmp = std::numeric_limits<int>::min();
        for (int i = 0; i < size; i++) {
            int tmp_sum = 0;
            for (int j = 0; j < size; j++) {
                tmp_sum += j * nums[j];
            }
            tmp = max(tmp_sum, tmp);
            int z = nums.back();
            nums.pop_back();
            nums.insert(nums.begin(), z);
        }
        // return tmp;

        int n = nums.size();

        // sum of all element in nums except the first one because it will be
        // multiplied by 0
        int sum = accumulate(nums.begin(), nums.end(), 0) - nums.front();

        // pushing same vector at the end of same vector
        nums.insert(nums.end(), nums.begin(), nums.end());

        int rolling = 0, ans = INT_MIN;

        // taking initial numbers in rolling
        for (int i = 0; i < n; i++) rolling += (i * nums[i]);

        ans = max(ans, rolling);

        // now roll the sliding window to find max in whole vector we created
        // above
        for (int j = 1, i = n; i < (n * 2) - 1; i++, j++) {
            rolling -= sum;
            sum -= nums[j];
            sum += nums[i];
            rolling += ((n - 1) * nums[i]);
            ans = max(ans, rolling);
        }

        return ans;
    }
};



TEST(t0, t1) {
    std::vector<int> nums{4, 3, 2, 6};
    int output = 26;

    Solution sl;
    int ret = sl.MaxRotateFunction(nums);
    /*
    F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
    F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
    F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
    F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
    So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.
    */
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<int> nums{100};
    int output = 0;

    Solution sl;
    int ret = sl.MaxRotateFunction(nums);
    EXPECT_EQ(ret, output);
}

}
