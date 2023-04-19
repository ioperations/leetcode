// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
 */

#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    /*
Time Complexity: O( (m+n) * log(d)), where m and n are number of rows and
columns in the matrix and d is the difference of the maximum element of the
matrix and the minimum element of the matrix.

Space Complexity: O(1), constant space.


    */

    int KthSmallest(vector<vector<int>> &matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        int low = matrix[0][0], high = matrix[m - 1][n - 1];
        int ans = -1;

        // do binary search
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (CountLessOrEqual(matrix, mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else
                low = mid + 1;
        }

        return ans;
    }

    int CountLessOrEqual(vector<vector<int>> &mat, int x) {
        int m = mat.size();
        int n = mat[0].size();
        int cnt = 0;
        int c = n - 1;

        for (int i = 0; i < m; i++) {
            while (c >= 0 && mat[i][c] > x) c--;
            cnt += c + 1;
        }

        return cnt;
    }
    int KthSmallestV2(vector<vector<int>> &matrix, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < (int)matrix.size(); i++) {
            for (int j = 0; j < (int)matrix.size(); j++) {
                pq.push(matrix[i][j]);
            }
        }
        while (k > 1) {
            pq.pop();
            k--;
        }
        return pq.top();
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    int k = 8;
    int output = 13;
    // Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15],
    // and the 8th smallest number is 13
    Solution sl;
    int ret = sl.KthSmallest(matrix, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<int>> matrix = {{-5}};
    int k = 1;
    int output = -5;
    Solution sl;
    int ret = sl.KthSmallest(matrix, k);
    EXPECT_EQ(ret, output);
}

TEST(t1, t1) {
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    int k = 8;
    int output = 13;
    // Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15],
    // and the 8th smallest number is 13
    Solution sl;
    int ret = sl.KthSmallestV2(matrix, k);
    EXPECT_EQ(ret, output);
}

TEST(t1, t2) {
    vector<vector<int>> matrix = {{-5}};
    int k = 1;
    int output = -5;
    Solution sl;
    int ret = sl.KthSmallestV2(matrix, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
