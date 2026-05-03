// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Write an efficient algorithm that searches for a value target in an m x n
integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool Binarys(vector<int>& row, int target) {
        int l = 0, r = row.size();
        while (l < r) {
            int const mid = l + (r - l) / 2;
            if (row[mid] == target) return true;
            if (row[mid] > target) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return false;
    }

    bool SearchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0;
        int j = static_cast<int>(matrix.at(0).size()) - 1;

        while (j >= 0 && i < static_cast<int>(matrix.size())) {
            if (matrix.at(i).at(j) == target) {
                return true;
            }

            if (matrix.at(i).at(j) > target) {
                j--;
            }

            else {
                i++;
            }
        }

        return false;
    }
};

TEST(SearchA2dMatrixIi, t1) {
    vector<vector<int>> matrix = {{1, 4, 7, 11, 15},
                                  {2, 5, 8, 12, 19},
                                  {3, 6, 9, 16, 22},
                                  {10, 13, 14, 17, 24},
                                  {18, 21, 23, 26, 30}};
    int const target = 5;
    bool const output = true;

    Solution sl;
    bool const ret = sl.SearchMatrix(matrix, target);
    EXPECT_EQ(ret, output);
}

TEST(SearchA2dMatrixIi, t2) {
    vector<vector<int>> matrix = {{1, 4, 7, 11, 15},
                                  {2, 5, 8, 12, 19},
                                  {3, 6, 9, 16, 22},
                                  {10, 13, 14, 17, 24},
                                  {18, 21, 23, 26, 30}};
    int const target = 20;
    bool const output = false;

    Solution sl;
    bool const ret = sl.SearchMatrix(matrix, target);
    EXPECT_EQ(ret, output);
}
}  // namespace
