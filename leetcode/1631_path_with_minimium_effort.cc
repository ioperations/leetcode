
/*
You are a hiker preparing for an upcoming hike. You are given heights, a 2D
array of size rows x columns, where heights[row][col] represents the height of
cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to
travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can
move up, down, left, or right, and you wish to find a route that requires the
minimum effort.

A route's effort is the maximum absolute difference in heights between two
consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the
bottom-right cell.
*/

#include <algorithm>
#include <cstdint>
#include <functional>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class Solution {
   public:
    int MinimumEffortPath(vector<vector<int>>& heights) {
        // pass
        /*
            rows == heights.length
            columns == heights[i].length
            1 <= rows, columns <= 100
            1 <= heights[i][j] <= 106
        */
        int m = heights.size();
        int n = heights[0].size();

        // int direction[]{-2, -1, 0, 1, 2};  // 左　下　初始化　上　右

        std::map<std::pair<int, int>, int> cache;

        std::set<std::pair<int, int>> visiting;
        cache[make_pair(m - 1, n - 1)] = 0;
        std::function<int(int, int, int)> fun = [&](int i, int j,
                                                    int direction_t) -> int {
            if (cache.count(make_pair(i, j))) {
                return cache[make_pair(i, j)];
            }
            if (visiting.count(make_pair(i, j)))
                return std::numeric_limits<int>::max();

            visiting.emplace(make_pair(i, j));

            int candidate1 = std::numeric_limits<int>::max();
            int candidate2 = std::numeric_limits<int>::max();
            int candidate3 = std::numeric_limits<int>::max();
            int candidate4 = std::numeric_limits<int>::max();

            if (i < (m - 1)) {
                // 向下走
                if (direction_t != 1) {
                    int z = fun(i + 1, j, -1);
                    if (z != candidate1) {
                        candidate1 =
                            std::max(abs(heights[i + 1][j] - heights[i][j]), z);
                    }
                }
            }
            if (i > 1) {
                // 向上走
                if (direction_t != -1) {
                    int z = fun(i - 1, j, 1);
                    if (z != candidate2) {
                        candidate2 =
                            std::max(abs(heights[i - 1][j] - heights[i][j]), z);
                    }
                }
            }
            if (j < (n - 1)) {
                // 向右走
                if (direction_t != -2) {
                    int z = fun(i, j + 1, 2);
                    if (z != candidate3) {
                        candidate3 =
                            std::max(abs(heights[i][j + 1] - heights[i][j]),
                                     fun(i, j + 1, 2));
                    }
                }
            }
            if (j > 1) {
                // 向左走
                if (direction_t != 2) {
                    int z = fun(i, j - 1, -2);
                    if (z != candidate4) {
                        candidate4 =
                            std::max(abs(heights[i][j - 1] - heights[i][j]), z);
                    }
                }
            }

            int ret =
                std::min({candidate1, candidate2, candidate3, candidate4});

            cache[make_pair(i, j)] = ret;
            return ret;
        };
        int ret = fun(0, 0, 0);
        return ret;
    }

   public:
    bool OutBound(int x, int y, int m, int n) {
        return x < 0 || y < 0 || x >= m || y >= n;
    }

    int MinimumEffortPathV2(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // int dp[m + 1][n + 1];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = std::numeric_limits<int>::max();
            }
        }
        dp[0][0] = 0;

        queue<pair<int, int>> q;
        q.push({0, 0});
        int x[4] = {0, -1, 0, 1};
        int y[4] = {-1, 0, 1, 0};
        pair<int, int> temp;
        int px, py;

        while (!q.empty()) {
            temp = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                px = temp.first + x[k];
                py = temp.second + y[k];
                if (OutBound(px, py, m, n)) {
                    continue;
                }
                if (dp[px][py] <= dp[temp.first][temp.second]) {
                    continue;
                }

                dp[px][py] =
                    min(dp[px][py], max(dp[temp.first][temp.second],
                                        abs(heights[temp.first][temp.second] -
                                            heights[px][py])));
                q.push({px, py});
            }
        }

        return dp[m - 1][n - 1];
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    /*
         ___ ___ ___
        | 1 | 2 | 2 |
        |___|___|___|
        | 3 | 8 | 2 |
        |___|___|___|
        | 5 | 3 | 5 |
        |___|___|___|
    */
    vector<vector<int>> heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    int output = 2;
    // Explanation: The route of [1,3,5,3,5] has a maximum absolute difference
    // of 2 in consecutive cells.
    // This is better than the route of [1,2,2,2,5], where the maximum absolute
    // difference is 3.

    Solution s;
    int ret = s.MinimumEffortPath(heights);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<int>> heights = {{1, 2, 3}, {3, 8, 4}, {5, 3, 5}};
    int output = 1;
    /*
        ___ ___ ___
       | 1 | 2 | 3 |
       |___|___|___|
       | 3 | 8 | 4 |
       |___|___|___|
       | 5 | 3 | 5 |
       |___|___|___|
    */

    // Explanation: The route of [1,3,5,3,5] has a maximum absolute difference
    // of 2 in consecutive cells.
    // This is better than the route of [1,2,2,2,5], where the maximum absolute
    // difference is 3.

    Solution s;
    int ret = s.MinimumEffortPath(heights);
    EXPECT_EQ(ret, output);
}
TEST(t0, t3) {
    vector<vector<int>> heights = {{1, 2, 1, 1, 1},
                                   {1, 2, 1, 2, 1},
                                   {1, 2, 1, 2, 1},
                                   {1, 2, 1, 2, 1},
                                   {1, 1, 1, 2, 1}};

    /*
     ___ ___ ___ ___ ___
    | 1 | 2 | 1 | 1 | 1 |
    |___|___|___|___|___|
    | 1 | 2 | 1 | 2 | 1 |
    |___|___|___|___|___|
    | 1 | 2 | 1 | 2 | 1 |
    |___|___|___|___|___|
    | 1 | 2 | 1 | 2 | 1 |
    |___|___|___|___|___|
    | 1 | 1 | 1 | 2 | 1 |
    |___|___|___|___|___|
    */
    int output = 0;

    Solution s;
    int ret = s.MinimumEffortPathV2(heights);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
