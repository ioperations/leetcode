// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given an array of distinct integers candidates and a target integer target,
return a list of all unique combinations of candidates where the chosen numbers
sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two
combinations are unique if the frequency of at least one of the chosen numbers
is different.

It is guaranteed that the number of unique combinations that sum up to target is
less than 150 combinations for the given input.

*/

#include <algorithm>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    void Sum(vector<int> &candidates, int target, vector<vector<int>> &res,
             vector<int> &r, int i) {
        if (target == 0) {
            // if we get exact answer
            res.push_back(r);
            return;
        }

        while (i < (int)candidates.size() && target - candidates[i] >= 0) {
            // Till every element in the array starting
            // from i which can contribute to the target
            r.push_back(candidates[i]);  // add them to vector

            // recur for next numbers
            Sum(candidates, target - candidates[i], res, r, i);
            ++i;

            // Remove number from vector (backtracking)
            r.pop_back();
        }
    }

    vector<vector<int>> CombinationSum(vector<int> &candidates, int target) {
        /*
            1. Sort the vector(non-decreasing).
            2. First remove all the duplicates from vector.
            3. Then use recursion and backtracking to solve
               the problem.
               (A) If at any time sub-problem sum == 0 then
                   add that vector to the result (vector of
                   vectors).
               (B) Else if sum is negative then ignore that
                   sub-problem.
               (C) Else insert the present index in that
                   vector to the current vector and call
                   the function with sum = sum-ar[index] and
                   index = index, then pop that element from
                   current index (backtrack) and call the
                   function with sum = sum and index = index+1
        */
        sort(candidates.begin(), candidates.end());  // sort candidates array

        // remove duplicates
        candidates.erase(unique(candidates.begin(), candidates.end()),
                         candidates.end());

        vector<int> r;
        vector<vector<int>> res;

        Sum(candidates, target, res, r, 0);

        return res;
    }
};



TEST(combination_sum, t1) {
    std::vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    Solution s;
    auto ret = s.CombinationSum(candidates, target);

    EXPECT_EQ(ret, (std::vector<std::vector<int>>{{2, 2, 3}, {7}}));
}

TEST(combination_sum, t2) {
    std::vector<int> candidates = {2, 3, 5};
    int target = 8;

    Solution s;
    auto ret = s.CombinationSum(candidates, target);

    EXPECT_EQ(
        ret,
        (std::vector<std::vector<int>>{{{2, 2, 2, 2}, {2, 3, 3}, {3, 5}}}));
}

TEST(combination_sum, t3) {
    std::vector<int> candidates = {2};

    int target = 1;

    Solution s;
    auto ret = s.CombinationSum(candidates, target);

    EXPECT_EQ(ret, (std::vector<std::vector<int>>{}));
}

}
