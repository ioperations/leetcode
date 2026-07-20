/*
 * Given a 2D grid of size m x n and an integer k. You need to shift the grid k
 * times.
 *
 * In one shift operation:
 *
 * Element at grid[i][j] moves to grid[i][j + 1].
 * Element at grid[i][n - 1] moves to grid[i + 1][0].
 * Element at grid[m - 1][n - 1] moves to grid[0][0].
 * Return the 2D grid after applying shift operation k times.
 *
 * m == grid.length
 * n == grid[i].length
 * 1 <= m <= 50
 * 1 <= n <= 50
 * -1000 <= grid[i][j] <= 1000
 * 0 <= k <= 100
 **/
#include <list>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    vector<vector<int>> ShiftGrid(vector<vector<int>>& grid, int k) {
        vector<int> ret;
        int m = grid.size();
        int n = grid[0].size();
        ret.resize(m * n + k, 0);
        int i = 0;
        for (auto& vec : grid) {
            for (auto& p : vec) {
                ret[k + i] = p;
                i++;
            }
        }

        for (int i = 0; i < k; i++) {
            ret[k - 1 - i] = ret[k + m * n - 1 - i];
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                grid[i][j] = ret[i * n + j];
            }
        }
        return grid;
    }
};
}  // namespace
   //

#include <gtest/gtest.h>

TEST(shiftGrid, t0) {
    vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int k = 1;
    std::vector<std::vector<int>> output = {{9, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    Solution sl;
    auto ret = sl.ShiftGrid(grid, k);
    EXPECT_EQ(output, ret);
}

TEST(shiftGrid, t1) {
    vector<vector<int>> grid = {
        {3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}, {12, 0, 21, 13}};
    int k = 4;
    std::vector<std::vector<int>> output = {
        {12, 0, 21, 13}, {3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}};
    Solution sl;
    auto ret = sl.ShiftGrid(grid, k);
    EXPECT_EQ(output, ret);
}

TEST(shiftGrid, t2) {
    vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int k = 9;
    std::vector<std::vector<int>> output = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Solution sl;
    auto ret = sl.ShiftGrid(grid, k);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
