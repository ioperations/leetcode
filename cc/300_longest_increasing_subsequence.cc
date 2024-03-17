// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums, return the length of the longest strictly
increasing subsequence.

A subsequence is a sequence that can be derived from an array by deleting some
or no elements without changing the order of the remaining elements. For
example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].*/

#include <algorithm>
#include <functional>
#include <limits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int LengthOfLisV1(vector<int> &nums) {
        int size = nums.size();
        function<int(int, int)> fun = [&](int start_with,
                                          int min_required) -> int {
            // passengers

            if (start_with >= size) return 0;

            if (nums[start_with] > min_required) {
                return max(1 + fun(start_with + 1,
                                   max(min_required, nums[start_with])),
                           fun(start_with + 1, min_required));
            }

            return fun(start_with + 1, min_required);
        };
        return fun(0, std::numeric_limits<int>::min());
    }
    int LengthOfLis(vector<int> &nums) {
        vector<int> ans;
        ans.push_back(nums[0]);
        for (int i = 1; i < (int)nums.size(); i++) {
            int ele = nums[i];
            if (ele > ans.back()) {
                ans.push_back(ele);
                continue;
            }
            int idx = lower_bound(ans.begin(), ans.end(), ele) - ans.begin();
            if (idx == (int)ans.size()) continue;
            ans[idx] = ele;
        }
        return ans.size();
    }
};

TEST(longest_increasing_subsequence, t1) {
    vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
    int output = 4;
    Solution sl;
    int ret = sl.LengthOfLis(nums);
    // The longest increasing subsequence is [2,3,7,101], therefore the length
    // is 4.
    EXPECT_EQ(ret, output);
}
TEST(longest_increasing_subsequence, t2) {
    vector<int> nums{0, 1, 0, 3, 2, 3};
    int output = 4;
    Solution sl;
    int ret = sl.LengthOfLis(nums);
    EXPECT_EQ(ret, output);
}

TEST(longest_increasing_subsequence, t3) {
    vector<int> nums{7, 7, 7, 7, 7, 7, 7};
    int output = 1;
    Solution sl;
    int ret = sl.LengthOfLis(nums);
    EXPECT_EQ(ret, output);
}
}  // namespace
