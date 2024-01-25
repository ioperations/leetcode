// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a 2D integer array matrix, return the transpose of matrix.

The transpose of a matrix is the matrix flipped over its main diagonal,
switching the matrix's row and column indices.*/

#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<int>> Transpose(vector<vector<int>> &matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> res(m, vector<int>(n, 0));  // matrix creation
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[j][i] =
                    matrix[i][j];  // filling the matrix in transpose form
            }
        }
        return res;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> output = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    Solution sl;
    auto ret = sl.Transpose(matrix);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}};
    vector<vector<int>> output = {{1, 4}, {2, 5}, {3, 6}};
    Solution sl;
    auto ret = sl.Transpose(matrix);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
