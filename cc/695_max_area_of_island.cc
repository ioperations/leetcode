// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an m x n binary matrix grid. An island is a group of 1's
(representing land) connected 4-directionally (horizontal or vertical.) You may
assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.

Return the maximum area of an island in grid. If there is no island, return 0.*/

#include <algorithm>
#include <cassert>
#include <set>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
    set<pair<int, int>> m_visited;

   public:
    Solution() = default;
    int MaxAreaOfIslandV1(vector<vector<int>>& grid) {
        // 行
        const int column = grid.size();
        assert(column > 0 && "the pre condition");
        // 列
        const int row = grid[0].size();

        const int ret = 0;
        const vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < column; i++) {
            for (int j = 0; j < row; j++) {
                auto pair = make_pair(i, j);

                if (m_visited.count(pair)) {
                    // pass
                }
                m_visited.emplace(pair);
            }
        }
        return ret;
    }

    int m_m{}, m_n{};
    void Dfs(int i, int j, vector<vector<int>>& grid, int& count) {
        if (i < 0 || j < 0 || i >= m_m || j >= m_n || grid[i][j] == 0 ||
            grid[i][j] == 2)
            return;
        grid[i][j] = 2;
        count++;  // sare direction me jao jiske just me 1 ho .. utna hi baar
                  // count bhi increase kro jeetne milenge aur 1 aaspass ke sare
                  // 1 ko 2 bna do jis se agli baar yeh nai mile
        Dfs(i - 1, j, grid, count);
        Dfs(i + 1, j, grid, count);
        Dfs(i, j + 1, grid, count);
        Dfs(i, j - 1, grid, count);
    }
    int MaxAreaOfIslandV2(vector<vector<int>>& grid) {
        m_m = grid.size();
        m_n = grid[0].size();

        int count = 0;
        int ans = 0;
        for (int i = 0; i < m_m; i++)
            for (int j = 0; j < m_n; j++) {
                if (grid[i][j] == 1) {
                    Dfs(i, j, grid, count);
                    ans = max(ans, count);
                    count = 0;
                }
            }
        return ans;
    }
    int Mark(vector<vector<int>>& grid, int x, int y, int m, int n) {
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1) return 0;
        grid[x][y] = 2;
        const int a = Mark(grid, x + 1, y, m, n);
        const int b = Mark(grid, x, y + 1, m, n);
        const int c = Mark(grid, x - 1, y, m, n);
        const int d = Mark(grid, x, y - 1, m, n);
        return 1 + a + b + c + d;
    }
    int MaxAreaOfIsland(vector<vector<int>>& grid) {
        const int m = grid.size(), n = grid[0].size();
        int max_area = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    const int area = Mark(grid, i, j, m, n);
                    max_area = max(max_area, area);
                }
            }
        }
        return max_area;
    }
};

TEST(max_area_of_island, t1) {
    std::vector<std::vector<int>> grid = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

    Solution sl;
    const int ret = sl.MaxAreaOfIsland(grid);
    EXPECT_EQ(ret, 6);
}

TEST(max_area_of_island, t2) {
    std::vector<std::vector<int>> grid = {{0, 0, 0, 0, 0, 0, 0, 0}};

    Solution sl;
    const int ret = sl.MaxAreaOfIsland(grid);
    EXPECT_EQ(ret, 0);
}

}  // namespace
