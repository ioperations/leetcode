// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an n x n binary matrix grid, return the length of the shortest clear
path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0))
to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are
different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.*/

#include <queue>
#include <vector>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   private:
    bool InBoundsAndClear(vector<vector<int>> &grid, int i, int j) {
        return i >= 0 && i < (int)grid.size() && j >= 0 &&
               j < (int)grid.at(i).size() && grid.at(i).at(j) == 0;
    }

   public:
    int ShortestPathBinaryMatrix(vector<vector<int>> &grid) {
        if (grid.at(0).at(0) == 1) return -1;  // path is blocked from the start

        vector<vector<int>> dirs = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                                    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        queue<pair<int, int>> fill_values;
        fill_values.push({0, 0});

        int steps = 0;
        while (!fill_values.empty()) {
            steps++;

            int size = fill_values.size();
            for (int i = 0; i < size; i++) {
                pair<int, int> coord = fill_values.front();
                fill_values.pop();

                int x = coord.first, y = coord.second;

                if (x == (int)grid.size() - 1 &&
                    y == (int)grid.at(x).size() - 1)
                    return steps;

                for (vector<int> &dir : dirs) {
                    int new_x = x + dir.at(0), new_y = y + dir.at(1);

                    if (!InBoundsAndClear(grid, new_x, new_y)) continue;

                    // mark as visited
                    grid.at(new_x).at(new_y) = -1;

                    // push coordinates of clear cell to explore other paths
                    fill_values.push({new_x, new_y});
                }
            }
        }

        return -1;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    std::vector<vector<int>> v{{0, 1}, {1, 0}};
    int expected = 2;

    Solution sl;
    int ret = sl.ShortestPathBinaryMatrix(v);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::vector<vector<int>> v{{0, 0, 0}, {1, 1, 0}, {1, 1, 0}};
    int expected = 4;

    Solution sl;
    int ret = sl.ShortestPathBinaryMatrix(v);
    EXPECT_EQ(ret, expected);
}
TEST(t0, t3) {
    std::vector<vector<int>> v{{1, 0, 0}, {1, 1, 0}, {1, 1, 0}};
    int expected = -1;

    Solution sl;
    int ret = sl.ShortestPathBinaryMatrix(v);
    EXPECT_EQ(ret, expected);
}

}
