/*
DDetermine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without
repetition. Note:

A Sudoku board (partially filled) could be valid but is not necessarily
solvable. Only the filled cells need to be validated according to the mentioned
rules. etermine if a 9 x 9 Sudoku board is valid. Only the filled cells need to
be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without
repetition. Note:

A Sudoku board (partially filled) could be valid but is not necessarily
solvable. Only the filled cells need to be validated according to the mentioned
rules.

*/
#include <array>
#include <vector>
using namespace std;
class Solution {
   public:
    bool IsValidSudoku(vector<vector<char>> &board) {
        array<int, 9> rows = {};
        array<int, 9> cols = {};
        array<int, 9> boxes = {};
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == '.') continue;
                const int mask = 1 << (board[r][c] & 0xf);
                // row
                if (rows[r] & mask) return false;
                rows[r] |= mask;
                // col
                if (cols[c] & mask) return false;
                cols[c] |= mask;
                // box
                const int box = (r / 3) * 3 + (c / 3);
                if (boxes[box] & mask) return false;
                boxes[box] |= mask;
            }
        }
        return true;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
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

    bool output = true;
    Solution sl;
    bool const ret = sl.IsValidSudoku(board);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<char>> board = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    bool output = false;
    Solution sl;
    bool const ret = sl.IsValidSudoku(board);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
