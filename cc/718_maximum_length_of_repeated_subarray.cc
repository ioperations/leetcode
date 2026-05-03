// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two integer arrays nums1 and nums2, return the maximum length of a
   subarray that appears in both arrays.
*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int FindLength(vector<int>& nums1, vector<int>& nums2) {
        // DP Approach - Similar to 1143. Longest Common Subsequence
        int const n = static_cast<int>(nums1.size());
        int const m = static_cast<int>(nums2.size());
        int ans = 0;
        // dp[i][j] means the length of repeated subarray of nums1[:i] and
        // nums2[:j] initially the first row (i = 0) and the first col (j = 0)
        // would be zero dp[i][0] = 0 for all i and dp[0][j] = 0 for all j if
        // you use int dp[n + 1][m + 1], then you need to take care of this part
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // if both character is same
                if (nums1.at(i - 1) == nums2.at(j - 1)) {
                    dp.at(i).at(j) = dp.at(i - 1).at(j - 1) + 1;
                    ans = max(ans, dp.at(i).at(j));
                } else {
                    // if you are looking for longest common sequence,
                    // then you put dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    // here however, this problem is looking for subarray, since
                    // both character is not equal, which means we need to break
                    // it here hence, set dp[i][j] to 0 since we use
                    // vector<vector<int>> dp instead of int dp[n + 1][m + 1]
                    // this part can be skipped as it is already 0
                }
            }
        }
        return ans;
    }
};

TEST(MaximumLengthOfRepeatedSubarray, t1) {
    vector<int> nums1 = {1, 2, 3, 2, 1}, nums2 = {3, 2, 1, 4, 7};

    int const output = 3;
    /*The repeated subarray with maximum length is [3,2,1].*/
    Solution sl;
    int const ret = sl.FindLength(nums1, nums2);
    EXPECT_EQ(ret, output);
}

TEST(MaximumLengthOfRepeatedSubarray, t2) {
    vector<int> nums1 = {0, 0, 0, 0, 0}, nums2 = {0, 0, 0, 0, 0};

    int const output = 5;
    Solution sl;
    int const ret = sl.FindLength(nums1, nums2);
    EXPECT_EQ(ret, output);
}

}  // namespace
