// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
According to Wikipedia's article: "The Game of Life, also known simply as Life,
is a cellular automaton devised by the British mathematician John Horton Conway
in 1970."

The board is made up of an m x n grid of cells, where each cell has an initial
state: live (represented by a 1) or dead (represented by a 0). Each cell
interacts with its eight neighbors (horizontal, vertical, diagonal) using the
following four rules (taken from the above Wikipedia article):

    1. Any live cell with fewer than two live neighbors dies as if caused by
under-population.
    2. Any live cell with two or three live neighbors lives on to the
next generation.
    3. Any live cell with more than three live neighbors dies, as if
by over-population.
    4. Any dead cell with exactly three live neighbors becomes a
live cell, as if by reproduction.

    The next state is created by applying the above rules simultaneously to
every cell in the current state, where births and deaths occur simultaneously.
Given the current state of the m x n grid board, return the next state.

@FOLLOW_UP:

Could you solve it in-place? Remember that the board needs to be updated
simultaneously: You cannot update some cells first and then use their updated
values to update other cells. In this question, we represent the board using a
2D array. In principle, the board is infinite, which would cause problems when
the active area encroaches upon the border of the array (i.e., live cells reach
the border). How would you address these problems?
*/
#include <array>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    void GameOfLife(vector<vector<int>>& board) {
        auto z = board;
        int const m = static_cast<int>(board.size());
        int const n = static_cast<int>(board.at(0).size());

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                z.at(i).at(j) = 0;
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0 && j > 0) {  // 左上
                    z.at(i - 1).at(j - 1) += board.at(i).at(j);
                }
                if (i > 0) {  // 上
                    z.at(i - 1).at(j) += board.at(i).at(j);
                }
                if (i > 0 && j < n - 1) {  // 右上
                    z.at(i - 1).at(j + 1) += board.at(i).at(j);
                }
                if (j > 0) {  // 左边
                    z.at(i).at(j - 1) += board.at(i).at(j);
                }
                if (j < n - 1) {  // 右边
                    z.at(i).at(j + 1) += board.at(i).at(j);
                }

                if (i < m - 1 && j > 0) {  // 左下
                    z.at(i + 1).at(j - 1) += board.at(i).at(j);
                }
                if (i < m - 1) {  // 下
                    z.at(i + 1).at(j) += board.at(i).at(j);
                }
                if (i < m - 1 && j < n - 1) {  // 右下
                    z.at(i + 1).at(j + 1) += board.at(i).at(j);
                }
            }
        }

        std::array<int, 9> const live_next = {0, 0, 1, 1, 0, 0, 0, 0, 0};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board.at(i).at(j) =
                    board.at(i).at(j) ? (live_next.at(z.at(i).at(j))) : (z.at(i).at(j) == 3 ? 1 : 0);
            }
        }
    }
};

TEST(GameOfLife, t1) {
    // pass
    std::vector<std::vector<int>> board = {
        {0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
    std::vector<std::vector<int>> const expected = {
        {0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 1, 0}};

    Solution s;
    s.GameOfLife(board);
    EXPECT_EQ(board, expected);
}

TEST(GameOfLife, t2) {
    // pass
    std::vector<std::vector<int>> board = {{1, 1}, {1, 0}};
    std::vector<std::vector<int>> const expected = {{1, 1}, {1, 1}};

    Solution s;
    s.GameOfLife(board);
    EXPECT_EQ(board, expected);
}

}  // namespace
