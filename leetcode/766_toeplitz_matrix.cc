// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise,
return false.

A matrix is Toeplitz if every diagonal from top-left to bottom-right has the
same elements.

*/
#include <vector>
using namespace std;

namespace { 
class Solution {
   public:
    bool IsToeplitzMatrix(vector<vector<int>> &matrix) {
        int const rows = matrix.size();
        int const cols = matrix[0].size();
        for (int r = 1; r < rows; ++r)
            for (int c = 1; c < cols; ++c)
                if (matrix[r][c] != matrix[r - 1][c - 1]) return false;

        return true;
    }
};
} 

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 1, 2, 3}, {9, 5, 1, 2}};
    bool const output = true;
    /*
    Explanation:
    In the above grid, the diagonals are:
    "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
    In each diagonal all elements are the same, so the answer is True.
    */
    Solution sl;
    bool const ret = sl.IsToeplitzMatrix(matrix);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<int>> matrix = {{1, 2}, {2, 2}};
    bool const output = false;
    /*
    Explanation:
    The diagonal "[1, 2]" has different elements.
    */
    Solution sl;
    bool const ret = sl.IsToeplitzMatrix(matrix);
    EXPECT_EQ(ret, output);
}

}
