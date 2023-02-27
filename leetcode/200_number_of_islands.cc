/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and
'0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands
horizontally or vertically. You may assume all four edges of the grid are all
surrounded by water.
*/

#include <vector>
/*
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'.
*/
#include <queue>

using namespace std;

class Solution {
   public:
    // BFS
    int NumIslands(vector<vector<char>> &grid) {
        int rows = grid.size();                // rows
        int cols = rows ? grid[0].size() : 0;  // cols
        int islands = 0;
        vector<int> offsets{0, 1, 0, -1, 0};
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // cout << "checking: " << i << "," << j << "\n";
                if (grid[i][j] == '1') {
                    ++islands;
                    // cout << "visited top: " << i << "," << j << "\n";
                    //  mark loc as visited
                    grid[i][j] = '0';
                    // cout << "visited top: " << i << "," << j << "\n";
                    queue<pair<int, int>> neighbors;  // queue for neighbors
                    neighbors.push({i, j});           // push loc
                    while (!neighbors.empty()) {
                        // get
                        pair<int, int> p = neighbors.front();
                        neighbors.pop();
                        // iterate thru offsets
                        for (size_t k = 0; k < offsets.size() - 1; k++) {
                            int r = p.first + offsets[k];
                            int c = p.second + offsets[k + 1];
                            if (r >= 0 && r < rows && c >= 0 && c < cols &&
                                grid[r][c] == '1') {
                                // cout << "visited within: " << r << "," << c
                                // << "\n";
                                //  mark as visited
                                grid[r][c] = '0';
                                neighbors.push({r, c});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }

    // DFS
    int NumIslandsDFS(vector<vector<char>> &grid) {
        auto rows = grid.size();
        auto cols = grid[0].size();

        int islands = 0;

        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++islands;
                    Dfs(grid, r, c);
                }
            }
        }
        return islands;
    }
    void Dfs(vector<vector<char>> &grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // mark 1st loc 0
        grid[r][c] = '0';
        for (auto off : offsets) {
            int r_x = r + off[0];
            int c_x = c + off[1];
            // cout << "r_: " << r_ << "\n";
            // cout << "c_: " << c_ << "\n";
            if (r_x >= 0 && r_x < rows && c_x >= 0 && c_x < cols &&
                grid[r_x][c_x] == '1') {
                Dfs(grid, r_x, c_x);
            }
        }
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<std::vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                           {'1', '1', '0', '1', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '0', '0', '0'}};
    int expected = 1;

    Solution s;
    int ret = s.NumIslands(grid);
    EXPECT_EQ(ret, expected);
}

TEST(t1, t1) {
    std::vector<std::vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                           {'1', '1', '0', '1', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '0', '0', '0'}};
    int expected = 1;

    Solution s;
    int ret = s.NumIslandsDFS(grid);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::vector<std::vector<char>> grid = {{'1', '1', '0', '0', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '1', '0', '0'},
                                           {'0', '0', '0', '1', '1'}};
    int expected = 3;

    Solution s;
    int ret = s.NumIslands(grid);
    EXPECT_EQ(ret, expected);
}

TEST(t1, t2) {
    std::vector<std::vector<char>> grid = {{'1', '1', '0', '0', '0'},
                                           {'1', '1', '0', '0', '0'},
                                           {'0', '0', '1', '0', '0'},
                                           {'0', '0', '0', '1', '1'}};
    int expected = 3;

    Solution s;
    int ret = s.NumIslandsDFS(grid);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
