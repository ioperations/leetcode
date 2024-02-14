// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an m x n grid of characters board and a string word, return true if word
exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where
adjacent cells are horizontally or vertically neighboring. The same letter cell
may not be used more than once.
*/

#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

#include <gtest/gtest.h>
#include <stddef.h>

namespace {
class Solution {
   public:
    bool ExistV(vector<vector<char>> &board, string word) {
        /*
            m == board.length
            n = board[i].length
            1 <= m, n <= 6
            1 <= word.length <= 15
        */
        for (size_t i = 0; i < board.size(); i++) {
            for (size_t j = 0; j < board[0].size(); j++) {
                if (ExistV(board, i, j, word)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool ExistV(vector<vector<char>> &board, int x, int y, string word) {
        std::stack<std::pair<int, int>> stack;
        // std::set<std::pair<int, int>> seen;

        // 这个点的 下一个点 已经走过的位置
        std::map<std::pair<int, int>, std::set<std::pair<int, int>>> next;
        // 这个点已经被走过了
        vector<vector<bool>> route(board.size(),
                                   vector<bool>(board[0].size(), false));
        const int m = board.size();
        const int n = board[0].size();

        if (board[x][y] == word[0]) {
            stack.push(make_pair(x, y));
            // seen.emplace(std::make_pair(x, y));
            route[x][y] = true;
        } else {
            return false;
        }

        int word_it = 1;
        while (stack.size() && word_it < (int)word.size()) {
            // navigate to next
            bool set = false;

            auto [x, y] = stack.top();

            int readllyx = 0;
            int readllyy = 0;
            if (route[x][y] == false) {
                if (x > 1) {
                    if (next[make_pair(x, y)].count(make_pair(x - 1, y)) == 0 &&
                        board[x - 1][y] == word[word_it]) {
                        // next[make_pair(x, y)].emplace(make_pair(x - 1, y));
                        stack.push(make_pair(x - 1, y));
                        set = true;
                        word_it++;
                        readllyx = x - 1;
                        readllyy = y;
                    }
                }
                if (x < m - 1) {
                    if (next[make_pair(x, y)].count(make_pair(x + 1, y)) == 0 &&
                        board[x + 1][y] == word[word_it]) {
                        // next[make_pair(x, y)].emplace(make_pair(x + 1, y));
                        stack.push(make_pair(x + 1, y));
                        set = true;

                        readllyx = x + 1;
                        readllyy = y;
                    }
                }
                if (y > 1) {
                    if (next[make_pair(x, y)].count(make_pair(x, y - 1)) == 0 &&
                        board[x][y - 1] == word[word_it]) {
                        // next[make_pair(x, y)].emplace(make_pair(x, y - 1));
                        stack.push(make_pair(x, y - 1));
                        set = true;

                        readllyx = x;
                        readllyy = y - 1;
                    }
                }
                if (y < n - 1) {
                    if (next[make_pair(x, y)].count(make_pair(x, y + 1)) == 0 &&
                        board[x][y + 1] == word[word_it]) {
                        // next[make_pair(x, y)].emplace(make_pair(x, y + 1));
                        stack.push(make_pair(x, y + 1));
                        set = true;

                        readllyx = x;
                        readllyy = y + 1;
                    }
                }
            }
            if (!set) {
                stack.pop();
                route[x][y] = true;
                word_it--;
            } else {
                next[make_pair(x, y)].emplace(make_pair(readllyx, readllyy));
                // route[readllyx][readllyy] = true;
                word_it++;
            }
        }

        if (word_it == (int)word.size()) {
            return true;
        }
        return false;
    }

   private:
    string s;
    int row, col, index = 0, dir[5] = {1, 0, -1, 0, 1};
    bool decision = false;

   public:
    bool IsSafe(int i, int j) {
        return (i >= 0 && j >= 0 && i < row && j < col) ? true : false;
    }

    void Backtrack(int i, int j, vector<vector<char>> &board, string &word) {
        if (index >= (int)word.size()) return;   // base-case
        if (word[index] != board[i][j]) return;  // search pruning

        s.push_back(board[i][j]);  // make move
        board[i][j] = '?';
        index++;

        if (s == word) decision = true;  // record solution

        for (int k = 0; k < 4; k++)  // backtrack
            if (IsSafe(i + dir[k], j + dir[k + 1]))
                Backtrack(i + dir[k], j + dir[k + 1], board, word);

        board[i][j] = s.back();  // undo move
        s.pop_back();
        index--;
    }

    bool Exist(vector<vector<char>> &board, string word) {
        // apply dfs from all starting characters in board
        row = board.size(), col = board[0].size();
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                if (board[i][j] == word[0]) {
                    Backtrack(i, j, board, word);
                }

        return decision;
    }
};

class SolutionV2 {
   public:
    bool Exist(vector<vector<char>> &board, string word) {
        const int m = board.size();
        if (m == 0) return false;
        const int n = board[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (Dfs(i, j, board, visited, word)) return true;
            }
        }
        return false;
    }

    bool Dfs(int i, int j, vector<vector<char>> &board,
             vector<vector<bool>> &visited, string word) {
        // int step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        stack<vector<int>> stack;
        stack.push({i, j, 0, 0});

        while (!stack.empty()) {
            auto top = stack.top();
            const int i = top[0];
            const int j = top[1];
            const int pos = top[2];
            const int dir = top[3];
            visited[i][j] = true;
            stack.pop();
            stack.push({i, j, pos, dir + 1});

            if (pos == (int)word.size() - 1 && word[pos] == board[i][j])
                return true;

            if (word[pos] != board[i][j]) {
                stack.pop();
                visited[i][j] = false;
                continue;
            }

            if (dir == 0) {
                if (i - 1 >= 0 && !visited[i - 1][j])
                    stack.push({i - 1, j, pos + 1, 0});
            } else if (dir == 1) {
                if (j - 1 >= 0 && !visited[i][j - 1])
                    stack.push({i, j - 1, pos + 1, 0});
            } else if (dir == 2) {
                if (i + 1 < (int)board.size() && !visited[i + 1][j])
                    stack.push({i + 1, j, pos + 1, 0});
            } else if (dir == 3) {
                if (j + 1 < (int)board[0].size() && !visited[i][j + 1])
                    stack.push({i, j + 1, pos + 1, 0});
            } else {
                stack.pop();
                visited[i][j] = false;
            }
        }

        return false;
    }
};



TEST(t0, t1) {
    /*
         ___ ___ ___ ___
        | A | B | C | E |
        |_-_|_-_|_-_|___|
        | S | F | C | S |
        |___|___|_-_|___|
        | A | D | E | E |
        |___|_-_|_-_|___|
    */
    std::vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    const std::string word = "ABCCED";
    Solution s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, true);
}

TEST(t1, t1) {
    /*
         ___ ___ ___ ___
        | A | B | C | E |
        |_-_|_-_|_-_|___|
        | S | F | C | S |
        |___|___|_-_|___|
        | A | D | E | E |
        |___|_-_|_-_|___|
    */
    std::vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    const std::string word = "ABCCED";
    SolutionV2 s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, true);
}

TEST(t0, t2) {
    /*
         ___ ___ ___ ___
        | A | B | C | E |
        |___|___|___|___|
        | S | F | C | S |
        |___|___|___|_-_|
        | A | F | D | E |
        |___|___|_-_|_-_|
    */

    std::vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    const std::string word = "SEE";
    Solution s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, true);
}

TEST(t1, t2) {
    /*
         ___ ___ ___ ___
        | A | B | C | E |
        |___|___|___|___|
        | S | F | C | S |
        |___|___|___|_-_|
        | A | F | D | E |
        |___|___|_-_|_-_|
    */

    std::vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    const std::string word = "SEE";
    SolutionV2 s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, true);
}
TEST(t0, t3) {
    /*
         ___ ___ ___ ___
        | A | B | C | E |
        |___|___|___|___|
        | S | F | C | S |
        |___|___|___|___|
        | A | F | D | E |
        |___|___|___|___|
    */

    std::vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    const std::string word = "ABCB";
    Solution s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, false);
}
TEST(t1, t3) {
    /*
         ___ ___ ___ ___
        | A | B | C | E |
        |___|___|___|___|
        | S | F | C | S |
        |___|___|___|___|
        | A | F | D | E |
        |___|___|___|___|
    */

    std::vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    const std::string word = "ABCB";
    SolutionV2 s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, false);
}

TEST(t0, t4) {
    std::vector<vector<char>> board =

        {{'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
         {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
         {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
    const std::string word = "AAAAAAAAAAAAAAB";
    Solution s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, false);
}
TEST(t1, t4) {
    std::vector<vector<char>> board =

        {{'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
         {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
         {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
    const std::string word = "AAAAAAAAAAAAAAB";
    SolutionV2 s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, false);
}

}  // namespace
