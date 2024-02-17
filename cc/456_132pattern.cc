// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an array of n integers nums, a 132 pattern is a subsequence of three
integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k]
< nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.
*/

#include <stack>
#include <vector>
#include <algorithm>
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace { 
class Solution {
   public:
    bool Find132pattern(vector<int> &nums) {
        int n = nums.size();
        vector<int> minval(n);
        minval[0] = nums[0];
        for (int i = 1; i < n; i++) {
            minval[i] = min(nums[i], minval[i - 1]);
        }
        stack<int> st;
        for (int j = n - 1; j >= 0; j--) {
            while (!st.empty() && st.top() <= minval[j]) st.pop();
            if (!st.empty() && st.top() < nums[j]) {
                return true;
            }
            st.push(nums[j]);
        }
        return false;
    }
};



TEST(t0, t1) {
    std::vector<int> v{1, 2, 3, 4};
    bool expected = false;
    Solution sl;
    bool ret = sl.Find132pattern(v);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::vector<int> v{3, 1, 4, 2};
    bool expected = true;
    Solution sl;
    bool ret = sl.Find132pattern(v);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t3) {
    std::vector<int> v{-1, 3, 2, 0};
    bool expected = true;
    Solution sl;
    bool ret = sl.Find132pattern(v);
    EXPECT_EQ(ret, expected);
}

}
