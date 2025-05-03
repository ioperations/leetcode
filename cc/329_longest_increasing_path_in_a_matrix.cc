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

#include <algorithm>
#include <cstring>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    int m_n{}, m_m{};
    int m_dp[201][201]{};
    vector<vector<int>> m_a;
    int Recur(int i, int j) {
        if (m_dp[i][j] != -1) return m_dp[i][j];
        int val = 0;
        if (i - 1 != -1 && m_a[i - 1][j] > m_a[i][j]) {
            val = max(val, Recur(i - 1, j) + 1);
        }
        if (j - 1 != -1 && m_a[i][j - 1] > m_a[i][j]) {
            val = max(val, Recur(i, j - 1) + 1);
        }
        if (i + 1 != m_n && m_a[i + 1][j] > m_a[i][j]) {
            val = max(val, Recur(i + 1, j) + 1);
        }
        if (j + 1 != m_m && m_a[i][j + 1] > m_a[i][j]) {
            val = max(val, Recur(i, j + 1) + 1);
        }
        return m_dp[i][j] = val;
    }
    int LongestIncreasingPath(vector<vector<int>>& matrix) {
        this->m_a = matrix;
        m_n = matrix.size();
        m_m = matrix[0].size();
        int ans = 0;
        memset(m_dp, -1, sizeof(m_dp));
        for (int i = 0; i < m_n; i++) {
            for (int j = 0; j < m_m; j++) {
                ans = max(ans, Recur(i, j));
            }
        }
        return ans + 1;
    }
};

TEST(longest_increasing_path_in_a_matrix, t1) {
    vector<vector<int>> matrix = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
    int const output = 4;

    Solution sl;
    int const ret = sl.LongestIncreasingPath(matrix);
    EXPECT_EQ(ret, output);
    // Explanation: The longest increasing path is [1, 2, 6, 9].
}
TEST(longest_increasing_path_in_a_matrix, t2) {
    vector<vector<int>> matrix = {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}};
    int const output = 4;

    // Explanation: The longest increasing path is [3, 4, 5, 6]. Moving
    // diagonally is not allowed.

    Solution sl;
    int const ret = sl.LongestIncreasingPath(matrix);
    EXPECT_EQ(ret, output);
    // Explanation: The longest increasing path is [1, 2, 6, 9].
}

}  // namespace
