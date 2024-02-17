// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A matrix diagonal is a diagonal line of cells starting from some cell in
either the topmost row or leftmost column and going in the bottom-right
direction until reaching the matrix's end. For example, the matrix diagonal
starting from mat[2][0], where mat is a 6 x 3 matrix, includes cells mat[2][0],
mat[3][1], and mat[4][2].

Given an m x n matrix mat of integers, sort each matrix diagonal in ascending
order and return the resulting matrix.

*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<int>> DiagonalSort(vector<vector<int>> &mat) {
        /*
            m == mat.length
            n == mat[i].length
            1 <= m, n <= 100
            1 <= mat[i][j] <= 100
        */

        /*
             ______   ______   ______   ______
            |      | |      | |      | |      |
            |      | |      | |      | |      |
            |______| |______| |______| |______|
             ______   ______   ______   ______
            |      | |      | |      | |      |
            |      | |      | |      | |      |
            |______| |______| |______| |______|
             ______   ______   ______   ______
            |      | |      | |      | |      |
            |      | |      | |      | |      |
            |______| |______| |______| |______|


        */
        auto bubble_sort = [&](vector<void *> &arr, int n) {
            int i, j;
            for (i = 0; i < n - 1; i++)
                for (j = 0; j < n - i - 1; j++)
                    if (*(int *)arr[j] > *(int *)arr[j + 1]) {
                        int tmp = *(int *)arr[j];
                        *(int *)arr[j] = *(int *)arr[j + 1];
                        *(int *)arr[j + 1] = tmp;
                    }
        };

        // 行
        int row = mat.size();
        // 列
        int column = mat[0].size();

        for (int i = row - 1, j = 0; i >= row || j < column;) {
            // pass
            {
                // 在这里对这一条斜线上的数字做排序
                vector<void *> address;
                address.reserve(min(row, column));

                for (int tmp_i = max(i, 0), tmp_j = j;
                     tmp_i < row && tmp_j < column; tmp_i++, tmp_j++) {
                    address.push_back(&mat[tmp_i][tmp_j]);
                }
                bubble_sort(address, address.size());

            }  //
            {
                // loop next
                if (i >= 0)
                    i--;
                else
                    j++;
            }
        }
        return mat;
    }
};

TEST(t0, t1) {
    vector<vector<int>> mat = {{3, 3, 1, 1}, {2, 2, 1, 2}, {1, 1, 1, 2}};
    vector<vector<int>> expected = {{1, 1, 1, 1}, {1, 2, 2, 2}, {1, 2, 3, 3}};
    Solution sl;
    auto ret = sl.DiagonalSort(mat);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    vector<vector<int>> mat = {{11, 25, 66, 1, 69, 7},
                               {23, 55, 17, 45, 15, 52},
                               {75, 31, 36, 44, 58, 8},
                               {22, 27, 33, 25, 68, 4},
                               {84, 28, 14, 11, 5, 50}};
    vector<vector<int>> expected = {{5, 17, 4, 1, 52, 7},
                                    {11, 11, 25, 45, 8, 69},
                                    {14, 23, 25, 44, 58, 15},
                                    {22, 27, 31, 36, 50, 66},
                                    {84, 28, 75, 33, 55, 68}};
    Solution sl;
    auto ret = sl.DiagonalSort(mat);
    EXPECT_EQ(ret, expected);
}

}  // namespace
