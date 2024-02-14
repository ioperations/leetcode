// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums, return true if there exists a triple of indices
   (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such
   indices exists, return false.

*/

#include <climits>
#include <stack>
#include <vector>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    bool IncreasingTriplet(vector<int> &nums) {
        int const n = nums.size();
        if (n < 3) {
            return 0;
        }
        stack<int> st;
        st.push(nums[n - 1]);
        //  st.push(nums[n-2]);
        int second = INT_MIN;
        int third = INT_MIN;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < second) {
                return true;
            }

            while (!st.empty() && st.top() > nums[i]) {
                second = max(second, nums[i]);
                int const k = st.top();
                st.pop();
                third = max(third, k);
            }

            if ((nums[i] > second) && (nums[i] < third)) {
                second = nums[i];
            }

            st.push(nums[i]);
        }

        return false;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {1, 2, 3, 4, 5};
    bool const output = true;
    // Explanation: Any triplet where i < j < k is valid.
    Solution sl;
    bool const ret = sl.IncreasingTriplet(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {5, 4, 3, 2, 1};
    bool const output = false;
    // No triplet exists.
    Solution sl;
    bool const ret = sl.IncreasingTriplet(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<int> nums = {2, 1, 5, 0, 4, 6};
    bool const output = true;
    // The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 <
    // nums[5] == 6
    Solution sl;
    bool const ret = sl.IncreasingTriplet(nums);
    EXPECT_EQ(ret, output);
}

}
