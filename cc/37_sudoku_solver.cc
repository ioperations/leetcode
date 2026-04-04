// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// leetcode 数独游戏

#include <set>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    bool SolveSudoku(vector<vector<char>>& board);

   private:
    bool Valid(vector<vector<char>>& board);
    /// **get candidate using the position**
    /// * NOTE: this function do have sequence dependency cause it use global
    /// state
    /// * to determine thoes candiadate's size is 0 indicating the previous
    /// * arrangement is wrong
    vector<char> GetPositionCandidate(int i, int j);
    bool SolveSudokuHelper(vector<vector<char>>& board);
    vector<vector<char>> board;
};

/// 横着没有重复 竖着没有重复 九宫格内没有重复
bool Solution::Valid(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        std::set<char> rows, cols, box;
        for (int j = 0; j < 9; j++) {
            char c = board[i][j];
            if (c != '.') {
                if (rows.count(c)) return false;
                rows.insert(c);
            }
            c = board[j][i];
            if (c != '.') {
                if (cols.count(c)) return false;
                cols.insert(c);
            }
            c = board[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3];
            if (c != '.') {
                if (box.count(c)) return false;
                box.insert(c);
            }
        }
    }
    return true;
}

/// 将数独棋盘填充完整
/// 暴力破解
vector<char> Solution::GetPositionCandidate(int i, int j) {
    vector<char> candidates;
    std::set<char> used;
    for (int col = 0; col < 9; col++) {
        if (board[i][col] != '.') used.insert(board[i][col]);
    }
    for (int row = 0; row < 9; row++) {
        if (board[row][j] != '.') used.insert(board[row][j]);
    }
    int boxRow = 3 * (i / 3);
    int boxCol = 3 * (j / 3);
    for (int r = boxRow; r < boxRow + 3; r++) {
        for (int c = boxCol; c < boxCol + 3; c++) {
            if (board[r][c] != '.') used.insert(board[r][c]);
        }
    }
    for (char d = '1'; d <= '9'; d++) {
        if (used.find(d) == used.end()) candidates.push_back(d);
    }
    return candidates;
}
bool Solution::SolveSudokuHelper(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                auto candidates = GetPositionCandidate(i, j);
                for (char c : candidates) {
                    board[i][j] = c;
                    if (SolveSudokuHelper(board)) return true;
                    board[i][j] = '.';
                }
                return false;
            }
        }
    }
    return true;
}
bool Solution::SolveSudoku(vector<vector<char>>& board) {
    this->board = board;
    bool ret = SolveSudokuHelper(this->board);
    board = this->board;
    return ret;
}

TEST(sudoku_solver, t1) {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    Solution sl;
    auto ret = sl.SolveSudoku(board);
    EXPECT_TRUE(ret);
}

}  // namespace
