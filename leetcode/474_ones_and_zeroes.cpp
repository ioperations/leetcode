/*
You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's
and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.
*/

#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<vector<int>>> mem;
    vector<int> one_cnt, zero_cnt;
    int Solve(int index, int m, int n) {
        int size = one_cnt.size();
        if (index >= size) {
            return 0;
        }
        if (m < 0 or n < 0) {
            return 0;
        }
        if (mem[index][m][n] != -1) {
            return mem[index][m][n];
        }
        int ans1 = Solve(index + 1, m, n);
        if (one_cnt[index] > n or zero_cnt[index] > m) {
            return mem[index][m][n] = ans1;
        }
        int ans2 =
            1 + Solve(index + 1, m - zero_cnt[index], n - one_cnt[index]);
        return mem[index][m][n] = max(ans1, ans2);
    }

   public:
    int FindMaxForm(vector<string>& strs, int m, int n) {
        int size = strs.size();
        mem = vector<vector<vector<int>>>(
            size, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        one_cnt = vector<int>(size, 0);
        zero_cnt = vector<int>(size, 0);
        for (int i = 0; i < strs.size(); i++) {
            for (int j = 0; j < strs[i].size(); j++) {
                if (strs[i][j] == '0') {
                    zero_cnt[i]++;
                } else {
                    one_cnt[i]++;
                }
            }
        }
        return Solve(0, m, n);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<string> v{"10", "0001", "111001", "1", "0"};
    int m = 5;
    int n = 3;
    int expected = 4;
    /*
       The largest subset with at most 5 0's and 3 1's is {"10", "0001",
       "1", "0"}, so the answer is 4. Other valid but smaller subsets include
       {"0001", "1"} and {"10", "1", "0"}. {"111001"} is an invalid subset
       because it contains 4 1's, greater than the maximum of 3.
    */
    Solution sl;
    int ret = sl.FindMaxForm(v, m, n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    vector<string> v{"10", "0", "1"};
    int m = 1;
    int n = 1;
    int expected = 2;
    /*
        The largest subset is {"0", "1"}, so the answer is 2.
    */
    Solution sl;

    int ret = sl.FindMaxForm(v, m, n);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

