/*
Given an array nums of distinct integers,
return all the possible permutations.
You can return the answer in any order.
*/

#include <vector>
using namespace std;
class Solution {
   public:
    vector<vector<int>> Permute(vector<int>& nums) {
        vector<vector<int>> ret;
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <set>

TEST(t0, t1) {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> output = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                  {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
    Solution sl;
    auto ret = sl.Permute(nums);
    set<vector<int>> out_set(output.begin(), output.end());
    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(out_set, ret_set);
}

TEST(t0, t2) {
    vector<int> nums = {0, 1};
    vector<vector<int>> output = {{0, 1}, {1, 0}};
    Solution sl;
    auto ret = sl.Permute(nums);
    set<vector<int>> out_set(output.begin(), output.end());
    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(out_set, ret_set);
}

TEST(t0, t3) {
    vector<int> nums = {1};
    vector<vector<int>> output = {{1}};
    Solution sl;
    auto ret = sl.Permute(nums);
    set<vector<int>> out_set(output.begin(), output.end());
    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(out_set, ret_set);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
