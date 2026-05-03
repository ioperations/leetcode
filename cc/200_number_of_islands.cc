// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and
'0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands
horizontally or vertically. You may assume all four edges of the grid are all
surrounded by water.
*/

#include <cstddef>
#include <vector>
/*
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'.
*/
#include <queue>
#include <stack>
#include <utility>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int NumIslands(vector<vector<char>>& grid) {
        int const rows = static_cast<int>(grid.size());                // rows
        int const cols = rows ? static_cast<int>(grid.at(0).size()) : 0;  // cols
        int islands = 0;
        vector<int> offsets{0, 1, 0, -1, 0};
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // cout << "checking: " << i << "," << j << "\n";
                if (grid.at(i).at(j) == '1') {
                    ++islands;
                    // cout << "visited top: " << i << "," << j << "\n";
                    //  mark loc as visited
                    grid[i][j] = '0';
                    // cout << "visited top: " << i << "," << j << "\n";
                    queue<pair<int, int>> neighbors;  // queue for neighbors
                    neighbors.emplace(i, j);          // push loc
                    while (!neighbors.empty()) {
                        // get
                        pair<int, int> const p = neighbors.front();
                        neighbors.pop();
                        // iterate thru offsets
                        for (size_t k = 0; k < offsets.size() - 1; k++) {
                            int const r = p.first + offsets.at(k);
                            int const c = p.second + offsets.at(k + 1);
                            if (r >= 0 && r < rows && c >= 0 && c < cols &&
                                grid.at(r).at(c) == '1') {
                                // cout << "visited within: " << r << "," << c
                                // << "\n";
                                //  mark as visited
                                grid[r][c] = '0';
                                neighbors.emplace(r, c);
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }

    // DFS
    int NumIslandsDFS(vector<vector<char>>& grid) {
        auto rows = static_cast<int>(grid.size());
        auto cols = static_cast<int>(grid.at(0).size());

        int islands = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid.at(r).at(c) == '1') {
                    ++islands;
                    Dfs(grid, r, c);
                }
            }
        }
        return islands;
    }
    void Dfs(vector<vector<char>>& grid, int r, int c) {
        int const rows = static_cast<int>(grid.size());
        int const cols = static_cast<int>(grid.at(0).size());
        vector<vector<int>> const offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // mark 1st loc 0
        grid[r][c] = '0';
        for (auto off : offsets) {
            int const r_x = r + off.at(0);
            int const c_x = c + off.at(1);
            // cout << "r_: " << r_ << "\n";
            // cout << "c_: " << c_ << "\n";
            if (r_x >= 0 && r_x < rows && c_x >= 0 && c_x < cols &&
                grid.at(r_x).at(c_x) == '1') {
                Dfs(grid, r_x, c_x);
            }
        }
    }

    void DfsUsingStack(const vector<vector<char>>& grid,
                       vector<vector<bool>>& visit, int i, int j) {
        stack<pair<int, int>> st;
        st.emplace(i, j);
        while (st.size()) {
            auto [i, j] = st.top();
            st.pop();
            if (i < 0 || j < 0 || i >= static_cast<int>(grid.size()) || j >= static_cast<int>(grid.at(0).size())) {
                continue;
            }

            if (visit[i][j] || grid[i][j] == '0') {
                continue;
            }
            visit[i][j] = true;
            st.emplace(i + 1, j);
            st.emplace(i - 1, j);
            st.emplace(i, j + 1);
            st.emplace(i, j - 1);
        }
    }

    void BfsUsingQueue(const vector<vector<char>>& grid,
                       vector<vector<bool>>& visit, int i, int j) {
        queue<pair<int, int>> q;
        q.emplace(i, j);
        while (q.size()) {
            auto [i, j] = q.front();
            q.pop();
            if (i < 0 || j < 0 || i >= static_cast<int>(grid.size()) || j >= static_cast<int>(grid.at(0).size())) {
                continue;
            }

            if (visit[i][j] || grid[i][j] == '0') {
                continue;
            }
            visit[i][j] = true;
            q.emplace(i + 1, j);
            q.emplace(i - 1, j);
            q.emplace(i, j + 1);
            q.emplace(i, j - 1);
        }
    }
};

TEST(NumberOfIslands, t1) {
    std::vector<std::vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                           {'1', '1', '0', '1', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '0', '0', '0'}};
    int const expected = 1;

    Solution s;
    int const ret = s.NumIslands(grid);
    EXPECT_EQ(ret, expected);
}

TEST(NumberOfIslandsV2, t1) {
    std::vector<std::vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                           {'1', '1', '0', '1', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '0', '0', '0'}};
    int const expected = 1;

    Solution s;
    int const ret = s.NumIslandsDFS(grid);
    EXPECT_EQ(ret, expected);
}

TEST(NumberOfIslands, t2) {
    std::vector<std::vector<char>> grid = {{'1', '1', '0', '0', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '1', '0', '0'},
                                           {'0', '0', '0', '1', '1'}};
    int const expected = 3;

    Solution s;
    int const ret = s.NumIslands(grid);
    EXPECT_EQ(ret, expected);
}

TEST(NumberOfIslandsV2, t2) {
    std::vector<std::vector<char>> grid = {{'1', '1', '0', '0', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '1', '0', '0'},
                                           {'0', '0', '0', '1', '1'}};
    int const expected = 3;

    Solution s;
    int const ret = s.NumIslandsDFS(grid);
    EXPECT_EQ(ret, expected);
}

}  // namespace
