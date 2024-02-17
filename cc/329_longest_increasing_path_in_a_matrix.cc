// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an m x n integers matrix, return the length of the longest increasing path
in matrix.

From each cell, you can either move in four directions: left, right, up, or
down. You may not move diagonally or move outside the boundary (i.e.,
wrap-around is not allowed).

*/

#include <cstring>
#include <vector>
#include <algorithm>
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace { 
class Solution {
   public:
    int n, m;
    int dp[201][201];
    vector<vector<int>> a;
    int Recur(int i, int j) {
        if (dp[i][j] != -1) return dp[i][j];
        int val = 0;
        if (i - 1 != -1 && a[i - 1][j] > a[i][j]) {
            val = max(val, Recur(i - 1, j) + 1);
        }
        if (j - 1 != -1 && a[i][j - 1] > a[i][j]) {
            val = max(val, Recur(i, j - 1) + 1);
        }
        if (i + 1 != n && a[i + 1][j] > a[i][j]) {
            val = max(val, Recur(i + 1, j) + 1);
        }
        if (j + 1 != m && a[i][j + 1] > a[i][j]) {
            val = max(val, Recur(i, j + 1) + 1);
        }
        return dp[i][j] = val;
    }
    int LongestIncreasingPath(vector<vector<int>> &matrix) {
        this->a = matrix;
        n = matrix.size();
        m = matrix[0].size();
        int ans = 0;
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans = max(ans, Recur(i, j));
            }
        }
        return ans + 1;
    }
};



TEST(t0, t1) {
    vector<vector<int>> matrix = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
    int output = 4;

    Solution sl;
    int ret = sl.LongestIncreasingPath(matrix);
    EXPECT_EQ(ret, output);
    // Explanation: The longest increasing path is [1, 2, 6, 9].
}
TEST(t0, t2) {
    vector<vector<int>> matrix = {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}};
    int output = 4;

    // Explanation: The longest increasing path is [3, 4, 5, 6]. Moving
    // diagonally is not allowed.

    Solution sl;
    int ret = sl.LongestIncreasingPath(matrix);
    EXPECT_EQ(ret, output);
    // Explanation: The longest increasing path is [1, 2, 6, 9].
}

}
