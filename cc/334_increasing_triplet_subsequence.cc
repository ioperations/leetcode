// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums, return true if there exists a triple of indices
   (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such
   indices exists, return false.

*/

#include <algorithm>
#include <climits>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool IncreasingTriplet(vector<int>& nums) {
        int const n = static_cast<int>(nums.size());
        if (n < 3) {
            return false;
        }
        stack<int> st;
        st.push(nums.at(static_cast<size_t>(n) - 1));
        //  st.push(nums[n-2]);
        int second{INT_MIN};
        int third{INT_MIN};
        for (int i = n - 2; i >= 0; i--) {
            if (nums.at(static_cast<size_t>(i)) < second) {
                return true;
            }

            while (!st.empty() && st.top() > nums.at(static_cast<size_t>(i))) {
                second = max(second, nums.at(static_cast<size_t>(i)));
                int const k = st.top();
                st.pop();
                third = max(third, k);
            }

            if ((nums.at(static_cast<size_t>(i)) > second) && (nums.at(static_cast<size_t>(i)) < third)) {
                second = nums.at(static_cast<size_t>(i));
            }

            st.push(nums.at(static_cast<size_t>(i)));
        }

        return false;
    }
};

TEST(IncreasingTripletSubsequence, t1) {
    vector<int> nums = {1, 2, 3, 4, 5};
    bool const output = true;
    // Explanation: Any triplet where i < j < k is valid.
    Solution sl;
    bool const ret = sl.IncreasingTriplet(nums);
    EXPECT_EQ(ret, output);
}

TEST(IncreasingTripletSubsequence, t2) {
    vector<int> nums = {5, 4, 3, 2, 1};
    bool const output = false;
    // No triplet exists.
    Solution sl;
    bool const ret = sl.IncreasingTriplet(nums);
    EXPECT_EQ(ret, output);
}

TEST(IncreasingTripletSubsequence, t3) {
    vector<int> nums = {2, 1, 5, 0, 4, 6};
    bool const output = true;
    // The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 <
    // nums[5] == 6
    Solution sl;
    bool const ret = sl.IncreasingTriplet(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
