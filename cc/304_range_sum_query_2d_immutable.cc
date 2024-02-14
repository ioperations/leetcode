// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a 2D matrix matrix, handle multiple queries of the following type:

Calculate the sum of the elements of matrix inside the rectangle defined by its
upper left corner (row1, col1) and lower right corner (row2, col2). Implement
the NumMatrix class:

NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the
elements of matrix inside the rectangle defined by its upper left corner (row1,
col1) and lower right corner (row2, col2).
 */

#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

#include <gtest/gtest.h>

namespace {
class NumMatrix {
   public:
    NumMatrix(vector<vector<int>> &matrix) {
        // pass
        m_matrix = matrix;
    }

    int SumRegion(int row1, int col1, int row2, int col2) {
        // pass

        int sum = 0;
        for (int i = row1; i <= row2; i++) {
            for (int j = col1; j <= col2; j++) {
                sum += m_matrix[i][j];
            }
        }

        return sum;
    }

   private:
    vector<vector<int>> m_matrix;
};
class NumMatrixV1 {
    vector<vector<int>> sum;

   public:
    NumMatrixV1(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        sum = vector<vector<int>>(
            m + 1, vector<int>(n + 1));  // sum[i][j] is sum of all elements
                                         // inside the rectangle [0,0,i,j]
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] +
                            matrix[i - 1][j - 1];
            }
        }
    }
    int SumRegion(int r1, int c1, int r2, int c2) {
        // Since our `sum` starts by 1 so we need to increase r1, c1, r2, c2 by
        // 1
        r1++;
        c1++;
        r2++;
        c2++;
        return sum[r2][c2] - sum[r2][c1 - 1] - sum[r1 - 1][c2] +
               sum[r1 - 1][c1 - 1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */



TEST(t0, t1) {
    // ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
    vector<vector<int>> input = {{3, 0, 1, 4, 2},
                                 {5, 6, 3, 2, 1},
                                 {1, 2, 0, 1, 5},
                                 {4, 1, 0, 1, 7},
                                 {1, 0, 3, 0, 5}};
    NumMatrix *obj = new NumMatrix(input);

    int ret = obj->SumRegion(2, 1, 4, 3);
    EXPECT_EQ(ret, 8);

    ret = obj->SumRegion(1, 1, 2, 2);
    EXPECT_EQ(ret, 11);

    ret = obj->SumRegion(1, 2, 2, 4);
    EXPECT_EQ(ret, 12);
    delete obj;

    // /*NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1],
    // [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
    // numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red
    // rectangle)
    // numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green
    // rectangle) numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the
    // blue rectangle)
}

TEST(t0, t2) {
    // ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
    vector<vector<int>> input = {{3, 0, 1, 4, 2},
                                 {5, 6, 3, 2, 1},
                                 {1, 2, 0, 1, 5},
                                 {4, 1, 0, 1, 7},
                                 {1, 0, 3, 0, 5}};
    NumMatrixV1 *obj = new NumMatrixV1(input);

    int ret = obj->SumRegion(2, 1, 4, 3);
    EXPECT_EQ(ret, 8);

    ret = obj->SumRegion(1, 1, 2, 2);
    EXPECT_EQ(ret, 11);

    ret = obj->SumRegion(1, 2, 2, 4);
    EXPECT_EQ(ret, 12);
    delete obj;

    // /*NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1],
    // [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
    // numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red
    // rectangle)
    // numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green
    // rectangle) numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the
    // blue rectangle)
}

}  // namespace
