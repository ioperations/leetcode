// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard
such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You
may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens'
placement, where 'Q' and '.' both indicate a queen and an empty space,
respectively.

*/
#include <iterator>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<string>>
        m_sols;  // 2D vector of strings to store the solutions
    ~Solution() { m_sols.clear(); }
    vector<vector<string>> SolveNQueens(int n) {
        vector<string> board(n, string(n, '.'));  // creating an empty board
        Solve(board, 0);  // calling the recursive function
        return m_sols;
    }
    bool IsSafe(vector<string>& board, int row, int col) {
      int const n = size(board);
      for (int i = 0; i < n; i++) {
        // checking if there is a queen in the same column
        if (board[i][col] == 'Q') return false;
        // checking if there is a queen in the same diagonal (left to right)
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == 'Q')
          return false;
        if (row - i >= 0 && col + i < n && board[row - i][col + i] == 'Q')
          return false;
        if (row + i < n && col - i >= 0 && board[row + i][col - i] == 'Q')
          return false;
        if (row + i < n && col + i < n && board[row + i][col + i] == 'Q')
          return false;
        }
        return true;
    }
    // Recursive Function (solve) - It basically tries all possible placement of
    // queen for the current row & recurses for it's next row
    void Solve(vector<string>& board, int row) {
        // Base condition.
        // We reached the last row, so we have a solution so we add it to the
        // solution vector
        if (row == (int)size(board)) {
          m_sols.push_back(board);
          return;
        }
        // Try placing a queen on each column for a given row.
        // Explore next row by placing Q at each valid column for the current
        // row
        for (int col = 0; col < (int)size(board); col++) {
            if (IsSafe(board, row, col)) {
                board[row][col] = 'Q';  // Queen placed on a valid cell
                Solve(board, row + 1);  // Exploring next row
                board[row][col] =
                    '.';  // Backtracking to get all possible solutions
            }
        }
    }
};

#include <set>

using namespace std;

TEST(n_queue, t1) {
    // pass
    int const n = 4;
    vector<vector<string>> output = {{".Q..", "...Q", "Q...", "..Q."},
                                     {"..Q.", "Q...", "...Q", ".Q.."}};
    Solution sl;
    auto ret = sl.SolveNQueens(n);
    std::set<vector<string>> const output_set(output.begin(), output.end());

    std::set<vector<string>> const ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
    // Explanation: There exist two distinct solutions to the 4-queens puzzle as
    // shown above
}

TEST(n_queue, t2) {
    // pass
    int const n = 1;
    vector<vector<string>> output = {{"Q"}};
    Solution sl;
    auto ret = sl.SolveNQueens(n);
    std::set<vector<string>> const output_set(output.begin(), output.end());

    std::set<vector<string>> const ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
    // Explanation: There exist two distinct solutions to the 4-queens puzzle as
    // shown above
}
}  // namespace
