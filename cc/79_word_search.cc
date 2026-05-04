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

#include <array>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool ExistV(vector<vector<char>>& board, const string& word) {
        /*
            m == board.length
            n = board[i].length
            1 <= m, n <= 6
            1 <= word.length <= 15
        */
        for (int i = 0; i < static_cast<int>(board.size()); i++) {
            for (int j = 0; j < static_cast<int>(board.at(0).size()); j++) {
                if (ExistV(board, i, j, word)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool ExistV(vector<vector<char>>& board, int x, int y, const string& word) {
        std::stack<std::pair<int, int>> stack;
        // std::set<std::pair<int, int>> seen;

        // 这个点的 下一个点 已经走过的位置
        std::map<std::pair<int, int>, std::set<std::pair<int, int>>> next;
        // 这个点已经被走过了
        vector<vector<bool>> route(board.size(),
                                   vector<bool>(board.at(0).size(), false));
        const int m = static_cast<int>(board.size());
        const int n = static_cast<int>(board.at(0).size());

        if (board.at(x).at(y) == word.at(0)) {
            stack.emplace(x, y);
            route.at(x).at(y) = true;
        } else {
            return false;
        }

        int word_it = 1;
        while (stack.size() && word_it < static_cast<int>(word.size())) {
          // navigate to next
          bool set = false;

          auto [x, y] = stack.top();

          int readllyx = 0;
          int readllyy = 0;
          if (route.at(x).at(y) == false) {
            if (x > 1) {
              if (next[make_pair(x, y)].count(make_pair(x - 1, y)) == 0 &&
                  board.at(x - 1).at(y) == word.at(word_it)) {
                stack.emplace(x - 1, y);
                set = true;
                word_it++;
                readllyx = x - 1;
                readllyy = y;
              }
            }
            if (x < m - 1) {
              if (next[make_pair(x, y)].count(make_pair(x + 1, y)) == 0 &&
                  board.at(x + 1).at(y) == word.at(word_it)) {
                // next[make_pair(x, y)].emplace(make_pair(x + 1, y));
                stack.emplace(x + 1, y);
                set = true;

                readllyx = x + 1;
                readllyy = y;
              }
            }
            if (y > 1) {
              if (next[make_pair(x, y)].count(make_pair(x, y - 1)) == 0 &&
                  board.at(x).at(y - 1) == word.at(word_it)) {
                // next[make_pair(x, y)].emplace(make_pair(x, y - 1));
                stack.emplace(x, y - 1);
                set = true;

                readllyx = x;
                readllyy = y - 1;
              }
            }
            if (y < n - 1) {
              if (next[make_pair(x, y)].count(make_pair(x, y + 1)) == 0 &&
                  board.at(x).at(y + 1) == word.at(word_it)) {
                // next[make_pair(x, y)].emplace(make_pair(x, y + 1));
                stack.emplace(x, y + 1);
                set = true;

                readllyx = x;
                readllyy = y + 1;
              }
            }
          }
          if (!set) {
            stack.pop();
            route.at(x).at(y) = true;
            word_it--;
          } else {
            next[make_pair(x, y)].emplace(readllyx, readllyy);
            word_it++;
          }
        }

        if (word_it == static_cast<int>(word.size())) {
            return true;
        }
        return false;
    }

   private:
    vector<char> m_s;
    int m_expect_size = 0;
    int m_row{}, m_col{}, m_index = 0;
    std::array<int, 5> m_dir = {1, 0, -1, 0, 1};
    bool m_decision = false;

   public:
    bool IsSafe(int i, int j) {
        return (i >= 0 && j >= 0 && i < m_row && j < m_col) ? true : false;
    }

    void Backtrack(int i, int j, vector<vector<char>>& board,
                   const string& word) {
      if (m_index >= static_cast<int>(word.size())) return;  // base-case
      if (word.at(m_index) != board.at(i).at(j)) return;              // search pruning

      m_s.at(m_index) = board.at(i).at(j);  // make move
      board.at(i).at(j) = '?';
      m_index++;

      if (m_index == m_expect_size &&
          std::string_view(m_s.data(), m_index) == word) {
        m_decision = true;  // record solution
      }

        for (int k = 0; k < 4; k++) {
            if (IsSafe(i + m_dir.at(k), j + m_dir.at(k + 1))) {
                Backtrack(i + m_dir.at(k), j + m_dir.at(k + 1), board, word);
            }
        }

        board.at(i).at(j) = m_s.at(m_index - 1);  // undo move
        // m_s.pop_back();
        m_index--;
    }

    bool Exist(vector<vector<char>>& board, const string& word) {
        // apply dfs from all starting characters in board
        m_expect_size = static_cast<int>(word.size());
        m_s.resize(m_expect_size);
        m_row = static_cast<int>(board.size()), m_col = static_cast<int>(board.at(0).size());
        for (int i = 0; i < m_row; i++) {
            for (int j = 0; j < m_col; j++) {
                if (board.at(i).at(j) == word.at(0)) {
                    Backtrack(i, j, board, word);
                }
            }
        }
        return m_decision;
    }
};

class SolutionV2 {
   public:
    bool Exist(vector<vector<char>>& board, const string& word) {
        const int m = static_cast<int>(board.size());
        if (m == 0) return false;
        const int n = static_cast<int>(board.at(0).size());

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (Dfs(i, j, board, visited, word)) return true;
            }
        }
        return false;
    }

    bool Dfs(int i, int j, vector<vector<char>>& board,
             vector<vector<bool>>& visited, const string& word) {
        // int step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        stack<std::array<int, 4>> st;
        st.push({i, j, 0, 0});

        while (!st.empty()) {
            const auto& top = st.top();
            const int i = top.at(0);
            const int j = top.at(1);
            const int pos = top.at(2);
            const int dir = top.at(3);
            visited.at(i).at(j) = true;
            st.pop();
            st.push({i, j, pos, dir + 1});

            if (pos == static_cast<int>(word.size()) - 1 && word.at(pos) == board.at(i).at(j)) {
                return true;
            }

            if (word.at(pos) != board.at(i).at(j)) {
                st.pop();
                visited.at(i).at(j) = false;
                continue;
            }

            if (dir == 0) {
              if (i - 1 >= 0 && !visited.at(i - 1).at(j)) {
                st.push({i - 1, j, pos + 1, 0});
              }
            } else if (dir == 1) {
              if (j - 1 >= 0 && !visited.at(i).at(j - 1)) {
                st.push({i, j - 1, pos + 1, 0});
              }
            } else if (dir == 2) {
              if (i + 1 < static_cast<int>(board.size()) &&
                  !visited.at(i + 1).at(j)) {
                st.push({i + 1, j, pos + 1, 0});
              }
            } else if (dir == 3) {
              if (j + 1 < static_cast<int>(board.at(0).size()) &&
                  !visited.at(i).at(j + 1)) {
                st.push({i, j + 1, pos + 1, 0});
              }
            } else {
                st.pop();
                visited.at(i).at(j) = false;
            }
        }

        return false;
    }
};

class SolutionV3 {
   public:
    bool Exist(vector<vector<char>>& board, const string& word) {
        if (board.empty() || word.empty()) return false;
        m_m = static_cast<int>(board.size());
        m_n = static_cast<int>(board.at(0).size());
        if (static_cast<int>(word.size()) > m_m * m_n) return false;

        for (int i = 0; i < m_m; i++) {
          for (int j = 0; j < m_n; j++) {
            if (board.at(i).at(j) == word.at(0)) {
              vector<vector<bool>> visited(m_m, vector<bool>(m_n, false));
              if (Dfs(i, j, 0, board, visited, word)) return true;
            }
          }
        }
        return false;
    }

   private:
    int m_m{}, m_n{};
    std::array<int, 5> m_dirs = {0, 1, 0, -1, 0};

    bool Dfs(int i, int j, int pos, vector<vector<char>>& board,
             vector<vector<bool>>& visited, const string& word) {
      if (pos == static_cast<int>(word.size())) return true;
      if (i < 0 || j < 0 || i >= m_m || j >= m_n) return false;
      if (visited.at(i).at(j) || board.at(i).at(j) != word.at(pos)) return false;

      visited.at(i).at(j) = true;
      for (int k = 0; k < 4; k++) {
        if (Dfs(i + m_dirs.at(k), j + m_dirs.at(k + 1), pos + 1, board, visited,
                word)) {
          return true;
        }
        }
        visited.at(i).at(j) = false;
        return false;
    }
};

TEST(wordV, t1) {
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

TEST(wordsearchV2, t1) {
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

TEST(wordV, t2) {
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

TEST(wordsearchV2, t2) {
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
TEST(wordV, t3) {
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
TEST(wordsearchV2, t3) {
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

TEST(wordV, t4) {
    std::vector<vector<char>> board =

        {{'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
         {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
         {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
    const std::string word = "AAAAAAAAAAAAAAB";
    Solution s;
    const bool ret = s.Exist(board, word);
    EXPECT_EQ(ret, false);
}
TEST(wordsearchV2, t4) {
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

#ifdef TEST_ADQ
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

#include <benchmark/benchmark.h>

namespace {
static void BenchMarkSolution(benchmark::State& state) {
  std::vector<std::vector<char>> board = {
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
  const std::string word = "AAAAAAAAAAAAAAB";
  for (auto&& _ : state) {
    Solution s;
    s.Exist(board, word);
  }
}
BENCHMARK(BenchMarkSolution);

static void BenchMarkSolutionV2(benchmark::State& state) {
  std::vector<std::vector<char>> board = {
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
  const std::string word = "AAAAAAAAAAAAAAB";
  for (auto&& _ : state) {
    SolutionV2 s;
    s.Exist(board, word);
  }
}
BENCHMARK(BenchMarkSolutionV2);

static void BenchMarkSolutionV3(benchmark::State& state) {
  std::vector<std::vector<char>> board = {
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
  const std::string word = "AAAAAAAAAAAAAAB";
  for (auto&& _ : state) {
    SolutionV3 s;
    s.Exist(board, word);
  }
}
BENCHMARK(BenchMarkSolutionV3);
}  // namespace

BENCHMARK_MAIN();
