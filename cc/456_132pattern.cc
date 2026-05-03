// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an array of n integers nums, a 132 pattern is a subsequence of three
integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k]
< nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.
*/

#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    bool Find132pattern(vector<int>& nums) {
        int const n = static_cast<int>(nums.size());
        vector<int> minval(static_cast<size_t>(n));
        minval.at(0) = nums.at(0);
        for (int i = 1; i < n; i++) {
            minval.at(i) = min(nums.at(i), minval.at(static_cast<size_t>(i) - 1));
        }
        stack<int> st;
        for (int j = n - 1; j >= 0; j--) {
            while (!st.empty() && st.top() <= minval.at(static_cast<size_t>(j))) st.pop();
            if (!st.empty() && st.top() < nums.at(static_cast<size_t>(j))) {
                return true;
            }
            st.push(nums.at(static_cast<size_t>(j)));
        }
        return false;
    }
};

TEST(Pattern, t1) {
    std::vector<int> v{1, 2, 3, 4};
    bool const expected = false;
    Solution sl;
    bool const ret = sl.Find132pattern(v);
    EXPECT_EQ(ret, expected);
}

TEST(Pattern, t2) {
    std::vector<int> v{3, 1, 4, 2};
    bool const expected = true;
    Solution sl;
    bool const ret = sl.Find132pattern(v);
    EXPECT_EQ(ret, expected);
}

TEST(Pattern, t3) {
    std::vector<int> v{-1, 3, 2, 0};
    bool const expected = true;
    Solution sl;
    bool const ret = sl.Find132pattern(v);
    EXPECT_EQ(ret, expected);
}

}  // namespace
