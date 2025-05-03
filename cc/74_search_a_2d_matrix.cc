// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

write an efficient algorithm that searches for a value target in an m x n
integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous
row.
*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool SearchMatrix(vector<vector<int>>& matrix, int target) {
        //  在matrix的头从小到大的搜索　，找到最小的点所在的节点
        //  在这个节点对应的vector当中二分搜索，搜索到了就返回成功

        int low = 0;
        int high = matrix.size();
        while (low < high) {
            int const mid = low + (high - low) / 2;

            if (matrix[mid].size()) {
                if (matrix[low][0] == target) {
                    return true;
                }
                (matrix[mid][0] > target) ? (high = mid) : (low = mid + 1);
            } else {
                high--;
            }
        }

        int first_dimension = low - 1;
        if (first_dimension < 0) {
            first_dimension = 0;
        }

        low = 0;
        high = matrix[first_dimension].size();

        while (low < high) {
            int const mid = low + (high - low) / 2;
            if (matrix[first_dimension][mid] == target) {
                return true;
            }
            (matrix[first_dimension][mid] > target) ? (high = mid)
                                                    : (low = mid + 1);
        }

        return false;
    }

    // https://leetcode.com/problems/search-a-2d-matrix/discuss/1895837/C%2B%2B-BINARY-SEARCH-TREE-(**)-Explained-with-IMG
    bool SearchMatrixV2(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size(), cols = matrix[0].size(), row = 0,
            col = cols - 1;

        while (row < rows && col > -1) {
            int const cur = matrix[row][col];
            if (cur == target) return true;
            if (target > cur)
                row++;
            else
                col--;
        }

        return false;
    }
};

TEST(search_a_2d_matrix_v2, t0) {
    // Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
    // Output: true

    std::vector<std::vector<int>> nums{
        {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};

    Solution s;
    bool ret = s.SearchMatrix(nums, 3);
    EXPECT_EQ(ret, true);

    ret = s.SearchMatrixV2(nums, 3);
    EXPECT_EQ(ret, true);
}

TEST(search_a_2d_matrix_v2, t1) {
    // matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
    // Output: false

    std::vector<std::vector<int>> nums{
        {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};

    Solution s;
    bool ret = s.SearchMatrix(nums, 13);
    EXPECT_EQ(ret, false);

    ret = s.SearchMatrixV2(nums, 13);
    EXPECT_EQ(ret, false);
}

TEST(search_a_2d_matrix_v2, t2) {
    // [[1]]
    // 0
    std::vector<std::vector<int>> nums{{1}};

    Solution s;
    bool ret = s.SearchMatrix(nums, 0);
    EXPECT_EQ(ret, false);

    ret = s.SearchMatrixV2(nums, 0);
    EXPECT_EQ(ret, false);
}

TEST(search_a_2d_matrix_v2, t3) {
    // [[1]]
    // 0
    std::vector<std::vector<int>> nums{{1}};

    Solution s;
    bool ret = s.SearchMatrix(nums, 1);
    EXPECT_EQ(ret, true);
    ret = s.SearchMatrixV2(nums, 1);
    EXPECT_EQ(ret, true);
}

}  // namespace
