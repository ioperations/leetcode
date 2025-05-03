// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/* Given a collection of candidate numbers (candidates) and a target number
(target), find all unique combinations in candidates where the candidate numbers
sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.
*/

#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    void Find(int i, vector<vector<int>>& ans, vector<int>& v, vector<int>& arr,
              int target) {
        if (target == 0) {
            ans.push_back(v);
            return;
        }

        for (int j = i; j < (int)arr.size(); j++) {
            if (j > i && arr[j] == arr[j - 1]) continue;
            if (arr[j] > target) break;
            v.push_back(arr[j]);
            Find(j + 1, ans, v, arr, target - arr[j]);
            v.pop_back();
        }
    }
    vector<vector<int>> CombinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        sort(candidates.begin(), candidates.end());
        vector<int> v;
        Find(0, ans, v, candidates, target);
        return ans;
    }
};

TEST(combination_sum_ii, t1) {
    std::vector<int> candidates{10, 1, 2, 7, 6, 1, 5};
    int target = 8;
    Solution sl;
    std::vector<vector<int>> output{{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}};
    set<vector<int>> out_set(output.begin(), output.end());
    auto ret = sl.CombinationSum2(candidates, target);
    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

TEST(combination_sum_ii, t2) {
    std::vector<int> candidates{2, 5, 2, 1, 2};
    int target = 5;
    Solution sl;
    std::vector<vector<int>> output{{1, 2, 2}, {5}};
    set<vector<int>> out_set(output.begin(), output.end());
    auto ret = sl.CombinationSum2(candidates, target);
    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

}  // namespace
