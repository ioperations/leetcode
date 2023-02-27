/*
    Given an integer array nums of unique elements, return all possible subsets
(the power set).

The solution set must not contain duplicate subsets. Return the solution in any
order.
*/

#include <vector>
using namespace std;
class Solution {
   public:
    void Solve(vector<vector<int>> &ans, vector<int> temp, int ind,
               vector<int> &nums) {
        int n = nums.size();

        if (ind >= n) {
            ans.push_back(temp);
            return;
        }

        // not pick
        Solve(ans, temp, ind + 1, nums);
        // pick
        int ele = nums[ind];
        temp.push_back(ele);
        Solve(ans, temp, ind + 1, nums);
        temp.pop_back();  // backtracking to reverse in original manner
    }
    vector<vector<int>> Subsets(vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> temp;
        Solve(ans, temp, 0, nums);
        return ans;
    }
};

class SolutionV1 {
   public:
    void Solve(vector<vector<int>> &ans, vector<int> temp, int ind,
               vector<int> &nums) {
        int n = nums.size();

        if (ind >= n) {
            ans.push_back(temp);
            return;
        }

        // not pick
        Solve(ans, temp, ind + 1, nums);
        // pick
        int ele = nums[ind];
        temp.push_back(ele);
        Solve(ans, temp, ind + 1, nums);
    }
    vector<vector<int>> Subsets(vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> temp;
        Solve(ans, temp, 0, nums);
        return ans;
    }
};
#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> input{1, 2, 3};
    std::vector<vector<int>> out{{},  {1},    {2},    {1, 2},
                                 {3}, {1, 3}, {2, 3}, {1, 2, 3}};

    Solution sl;
    auto ret = sl.Subsets(input);
    set<vector<int>> out_set(out.begin(), out.end());
    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(out_set, ret_set);
}

TEST(t0, t2) {
    std::vector<int> input{0};
    std::vector<vector<int>> out{{}, {0}};

    Solution sl;
    auto ret = sl.Subsets(input);
    set<vector<int>> out_set(out.begin(), out.end());
    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(out_set, ret_set);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
