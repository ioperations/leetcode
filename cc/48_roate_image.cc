// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <stddef.h>

#include <algorithm>
#include <vector>

/*

You are given an n x n 2D matrix representing an image, rotate the image by 90
degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input
2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
*/
using namespace std;
#include <cassert>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    /**
     * @brief 90顺时针旋转整个table
     * @param @matrix 二维表
     * @return
     */
    void Rotate(vector<vector<int>>& matrix) {
        /*
             ___ ___ ___      ___ ___ ___
            | 1 | 2 | 3 |    | 7 | 4 | 1 |
            |___|___|___|    |___|___|___|
            | 4 | 5 | 6 | => | 8 | 5 | 2 |
            |___|___|___|    |___|___|___|
            | 7 | 8 | 9 |    | 9 | 6 | 3 |
            |___|___|___|    |___|___|___|
        */

        const bool __attribute__((unused)) ok =
            matrix.size() ? matrix.size() == matrix[0].size() : true;
        assert(ok && "should be ok");

        const int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                const int t = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = t;
            }
        }
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
        return;
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix.size(); j++) {
                /*
                    (0,0) => (0,2)
                    (0,1) => (1,2)
                    (0,2) => (2,2)
                    (1,0) => (0,1)
                    (1,1) => (1,1)
                    (1,2) => (2,1)
                    (2,0) => (0,0)
                    (2,1) => (1,0)
                    (2,2) => (2,0)
                */
            }
        }
    }
};

TEST(roate_image, t1) {
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const std::vector<std::vector<int>> expected = {
        {7, 4, 1}, {8, 5, 2}, {9, 6, 3}};

    Solution s;
    s.Rotate(matrix);

    EXPECT_EQ(matrix, expected);
}

TEST(roate_image, t2) {
    std::vector<std::vector<int>> matrix = {
        {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
    const std::vector<std::vector<int>> expected = {
        {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};

    Solution s;
    s.Rotate(matrix);

    EXPECT_EQ(matrix, expected);
}
}  // namespace
