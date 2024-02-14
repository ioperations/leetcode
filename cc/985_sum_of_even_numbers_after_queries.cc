// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an integer array nums and an array queries where queries[i] =
[vali, indexi].

For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print
the sum of the even values of nums.

Return an integer array answer where answer[i] is the answer to the ith query.*/

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    vector<int> SumEvenAfterQueries(vector<int> &nums,
                                    vector<vector<int>> &queries) {
        int sum = accumulate(begin(nums), end(nums), 0, [](int sum, int x) {
            return IsEven(x) ? sum + x : sum;
        });

        vector<int> ans;
        ans.reserve(size(queries));
        for (const vector<int> &query : queries) {
            const int val = query[0];
            const int index = query[1];

            int &num = nums[index];

            if (IsEven(num)) sum -= num;
            num += val;
            if (IsEven(num)) sum += num;

            ans.push_back(sum);
        }
        return ans;
    }

    static bool IsEven(int x) { return !(x & 1); }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {1, 2, 3, 4};

    vector<vector<int>> queries = {{1, 0}, {-3, 1}, {-4, 0}, {2, 3}};
    vector<int> const output = {8, 6, 2, 4};
    Solution sl;
    auto ret = sl.SumEvenAfterQueries(nums, queries);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {1};
    vector<vector<int>> queries = {{4, 0}};
    vector<int> const output = {0};
    Solution sl;
    auto ret = sl.SumEvenAfterQueries(nums, queries);
    EXPECT_EQ(ret, output);
}

}
