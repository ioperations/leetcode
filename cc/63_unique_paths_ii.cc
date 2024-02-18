// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an m x n integer array grid. There is a robot initially located
at the top-left corner (i.e., grid[0][0]). The robot tries to move to the
bottom-right corner (i.e., grid[m-1][n-1]). The robot can only move either down
or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the
robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the
bottom-right corner.

The testcases are generated so that the answer will be less than or equal to 2 *
109.

 */

#include <queue>
#include <vector>
#include <string>
#include <utility>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    int UniquePathsWithObstacles(vector<vector<int>> &obstacle_grid) {
        int m = obstacle_grid.size(), n = obstacle_grid[0].size();
        if (obstacle_grid[0][0] == 1) return 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int i = 1; i < m; i++)
            dp[i][0] = obstacle_grid[i][0] == 0 && dp[i - 1][0] == 1 ? 1 : 0;
        for (int i = 1; i < n; i++)
            dp[0][i] = obstacle_grid[0][i] == 0 && dp[0][i - 1] == 1 ? 1 : 0;

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacle_grid[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    int UniquePathsWithObstaclesV1(vector<vector<int>> &obstacle_grid) {
        int m = obstacle_grid.size(), n = obstacle_grid[0].size();
        vector<vector<int>> grid(m, vector<int>(n, 0));
        queue<pair<int, int>> q;
        vector<pair<int, int>> dirs = {make_pair(0, 1), make_pair(1, 0)};
        grid[0][0] = obstacle_grid[0][0] == 0 ? 1 : 0;
        q.push(make_pair(0, 0));
        while (q.size() > 0) {
            pair<int, int> cell = q.front();
            q.pop();
            int next_value = grid[cell.first][cell.second];
            for (auto &p : dirs) {
                if ((p.second + cell.second) > n - 1 ||
                    (p.first + cell.first) > m - 1 ||
                    (obstacle_grid[p.first + cell.first]
                                  [p.second + cell.second] == 1))
                    continue;
                pair<int, int> next_cell =
                    make_pair(p.first + cell.first, p.second + cell.second);
                if (grid[next_cell.first][next_cell.second] == 0)
                    q.push(next_cell);
                grid[next_cell.first][next_cell.second] += next_value;
            }
        }
        return grid[m - 1][n - 1];
    }
};



TEST(unique_paths_ii, t1) {
    vector<vector<int>> obstacle_grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    int output = 2;
    // Explanation: There is one obstacle in the middle of the 3x3 grid above.
    // There are two ways to reach the bottom-right corner:
    // 1. Right -> Right -> Down -> Down
    // 2. Down -> Down -> Right -> Right
    Solution sl;
    int ret = sl.UniquePathsWithObstacles(obstacle_grid);
    EXPECT_EQ(ret, output);
}

TEST(unique_paths_ii, t2) {
    vector<vector<int>> obstacle_grid = {{0, 1}, {0, 0}};
    int output = 1;
    // Explanation: There is one obstacle in the middle of the 3x3 grid above.
    // There are two ways to reach the bottom-right corner:
    // 1. Right -> Right -> Down -> Down
    // 2. Down -> Down -> Right -> Right
    Solution sl;
    int ret = sl.UniquePathsWithObstacles(obstacle_grid);
    EXPECT_EQ(ret, output);
}

TEST(t1, t1) {
    vector<vector<int>> obstacle_grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    int output = 2;
    // Explanation: There is one obstacle in the middle of the 3x3 grid above.
    // There are two ways to reach the bottom-right corner:
    // 1. Right -> Right -> Down -> Down
    // 2. Down -> Down -> Right -> Right
    Solution sl;
    int ret = sl.UniquePathsWithObstaclesV1(obstacle_grid);
    EXPECT_EQ(ret, output);
}

TEST(t1, t2) {
    vector<vector<int>> obstacle_grid = {{0, 1}, {0, 0}};
    int output = 1;
    // Explanation: There is one obstacle in the middle of the 3x3 grid above.
    // There are two ways to reach the bottom-right corner:
    // 1. Right -> Right -> Down -> Down
    // 2. Down -> Down -> Right -> Right
    Solution sl;
    int ret = sl.UniquePathsWithObstaclesV1(obstacle_grid);
    EXPECT_EQ(ret, output);
}

}
