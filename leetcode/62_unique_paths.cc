/*There is a robot on an m x n grid. The robot is initially located at the
top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right
corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right
at any point in time.

Given the two integers m and n, return the number of possible unique paths that
the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to 2
* 109.*/

#include <functional>
#include <vector>

using namespace std;

class Solution {
   public:
    int UniquePaths(int m, int n) {
        // pass

        std::vector<std::vector<int>> v(m, std::vector<int>(n, 0));
        // int v[120][120] = {{0}};

        std::function<int(int, int)> fun = [&](int i, int j) -> int {
            if (i == m - 1) return 1;
            if (j == n - 1) return 1;

            if (v[i][j] != 0) {
                return v[i][j];
            }

            v[i][j] = fun(i + 1, j) + fun(i, j + 1);

            return v[i][j];
        };

        return fun(0, 0);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int m = 3, n = 7;
    int output = 28;
    Solution sl;
    int ret = sl.UniquePaths(m, n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int m = 3, n = 2;
    int output = 3;
    Solution sl;
    /*
        From the top-left corner, there are a total of 3 ways to reach the
        bottom-right corner:
        1. Right -> Down -> Down
        2. Down -> Down -> Right
        3. Down -> Right -> Down
    */
    int ret = sl.UniquePaths(m, n);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
