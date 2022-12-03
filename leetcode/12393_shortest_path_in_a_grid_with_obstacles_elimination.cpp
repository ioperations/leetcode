/*You are given an m x n integer matrix grid where each cell is either 0 (empty)
or 1 (obstacle). You can move up, down, left, or right from and to an empty cell
in one step.

Return the minimum number of steps to walk from the upper left corner (0, 0) to
the lower right corner (m - 1, n - 1) given that you can eliminate at most k
obstacles. If it is not possible to find such walk return -1.*/

#include <vector>
using namespace std;

class Solution {
   public:
    int ShortestPath(vector<vector<int>>& grid, int k) {
        // pass
        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<vector<int>> grid = {
        {0, 0, 0}, {1, 1, 0}, {0, 0, 0}, {0, 1, 1}, {0, 0, 0}};
    int k = 1;
    int output = 6;
    /*
    Explanation:
    The shortest path without eliminating any obstacle is 10.
    The shortest path with one obstacle elimination at position (3,2) is 6. Such
    path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
    */
    Solution sl;
    int ert = sl.ShortestPath(grid, k);
    EXPECT_EQ(ert, output);
}

TEST(t0, t2) {
    vector<vector<int>> grid = {{0, 1, 1}, {1, 1, 1}, {1, 0, 0}};
    int k = 1;
    int output = -1;
    /*
    Explanation: We need to eliminate at least two obstacles to find such a
    walk.
    */
    Solution sl;
    int ert = sl.ShortestPath(grid, k);
    EXPECT_EQ(ert, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

