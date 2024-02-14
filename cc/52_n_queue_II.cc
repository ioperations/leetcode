// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*The n-queens puzzle is the problem of placing n queens on an n x n chessboard
such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens
puzzle.

*/

#include <vector>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    int TotalNQueens(int n) {
        vector<bool> col(n), diag(2 * n - 1), anti_diag(2 * n - 1);
        return Solve(col, diag, anti_diag, 0);
    }

    int Solve(vector<bool> &col, vector<bool> &diag, vector<bool> &anti_diag,
              int row) {
        int n = size(col), count = 0;
        if (row == n) return 1;
        for (int column = 0; column < n; column++)
            if (!col[column] && !diag[row + column] &&
                !anti_diag[row - column + n - 1]) {
                col[column] = diag[row + column] =
                    anti_diag[row - column + n - 1] = true;
                count += Solve(col, diag, anti_diag, row + 1);
                col[column] = diag[row + column] =
                    anti_diag[row - column + n - 1] = false;
            }
        return count;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 4;
    int ret = 2;
    Solution sl;
    int out = sl.TotalNQueens(n);
    // here are two distinct solutions to the 4-queens puzzle as shown.
    EXPECT_EQ(ret, out);
}

TEST(t0, t2) {
    int n = 1;
    int ret = 1;
    Solution sl;
    int out = sl.TotalNQueens(n);
    EXPECT_EQ(ret, out);
}

}
