/*Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More
formally, if you are on index i on the current row, you may move to either index
i or index i + 1 on the next row.

 */

#include <vector>
using namespace std;

class Solution {
   public:
    int FindMin(int i, int j, int n, vector<vector<int>>& triangle,
                vector<vector<int>>& mem) {
        if (i == n - 1) return triangle[i][j];
        if (mem[i][j] != -1) return mem[i][j];
        int left = triangle[i][j] + FindMin(i + 1, j, n, triangle, mem);
        int right = triangle[i][j] + FindMin(i + 1, j + 1, n, triangle, mem);
        return mem[i][j] = min(left, right);
    }

    int MinimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> mem(triangle.size(),
                                vector<int>(triangle.size(), -1));
        return FindMin(0, 0, triangle.size(), triangle, mem);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<vector<int>> v{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    int out = 11;
    Solution sl;
    int ret = sl.MinimumTotal(v);
    /*
    The triangle looks like:
       2
      3 4
     6 5 7
    4 1 8 3
    The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined
    above).
    */

    EXPECT_EQ(ret, out);
}

TEST(t0, t2) {
    std::vector<vector<int>> v{{-10}};
    int out = -10;
    Solution sl;
    int ret = sl.MinimumTotal(v);
    EXPECT_EQ(ret, out);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
