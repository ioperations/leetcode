// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given an n x n matrix where each of the rows and columns is sorted in ascending
order, return the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth
distinct element.

You must find a solution with a memory complexity better than O(n2).

*/

#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int KthSmallest(const vector<vector<int>>& matrix, int k) {
        // pass
        // n == matrix.length == matrix[i].length
        // 1 <= n <= 300

        // int i = 0, j = 0;
        int const n = matrix.size();

        std::set<std::pair<int, int>> visited;
        visited.emplace(0, 0);

        struct Tt {
            bool operator()(pair<int, int> a, pair<int, int> b) {
                return a.first + a.second > b.first + b.second;
            }
        };
        std::function<bool(pair<int, int>, pair<int, int>)> const mycompaire =
            [&matrix](pair<int, int> a, pair<int, int> b) -> bool {
            return matrix[a.first][a.second] > matrix[b.first][b.second];
        };

        std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, Tt> q;

        if (n > 1) {
            q.emplace(0, 1);
            q.emplace(1, 0);
            visited.emplace(0, 1);
            visited.emplace(1, 0);
        }

        // std::function<int()> geMinAndAdvance = [&]() -> int { return 0; };
        int ret = matrix[0][0];

        for (int i = 1; i < k; i++) {
            // ret = getMinAndAdvance();
            auto [a, b] = q.top();
            q.pop();
            ret = matrix[a][b];
            if (a < (n - 1)) {
                if (!visited.count(make_pair(a + 1, b))) {
                    q.emplace(a + 1, b);
                    visited.emplace(a + 1, b);
                }
            }
            if (b < (n - 1)) {
                if (!visited.count(make_pair(a, b + 1))) {
                    q.emplace(a, b + 1);
                    visited.emplace(a, b + 1);
                }
            }
        }

        return ret;
    }

    int KthSmallestV2(vector<vector<int>>& matrix, int k) {
        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>, greater<>>
            pq;
        int const n = matrix.size();
        int cnt = 0;
        for (int i = 0; i < n; i++) pq.push({matrix[i][0], {i, 0}});
        while (pq.size() != 0) {
            auto t = pq.top();
            pq.pop();
            int val = t.first, i = t.second.first, j = t.second.second;
            if (++cnt == k) return val;
            if (j + 1 < n) pq.push({matrix[i][j + 1], {i, j + 1}});
        }
        return -1;
    }

    /**
     * @brief O(n2) 解法
     * @return
     */
    int KthSmallestOn2(vector<vector<int>>& matrix, int k) {
        // pass

        vector<int> z(matrix.size() * matrix.size(), 0);
        for (int i = 0; i < (int)matrix.size(); i++) {
            for (int j = 0; j < (int)matrix.size(); j++) {
                z[i + j] = matrix[i][j];
            }
        }

        sort(z.begin(), z.end());
        return z[k - 1];
        return 0;
    }
};

TEST(Kth_smallest_elements_in_a_sorted_matrix, t1) {
    vector<vector<int>> const matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    int const k = 8;
    int const expected = 13;
    // Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15],
    // and the 8th smallest number is 13
    Solution sl;
    int const ret = sl.KthSmallest(matrix, k);
    EXPECT_EQ(ret, expected);
}

TEST(Kth_smallest_elements_in_a_sorted_matrix_v2, t1) {
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    int const k = 8;
    int const expected = 13;
    // Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15],
    // and the 8th smallest number is 13
    Solution sl;
    int const ret = sl.KthSmallestOn2(matrix, k);
    EXPECT_EQ(ret, expected);
}

TEST(Kth_smallest_elements_in_a_sorted_matrix_v3, t1) {
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    int const k = 8;
    int const expected = 13;
    // Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15],
    // and the 8th smallest number is 13
    Solution sl;
    int const ret = sl.KthSmallestV2(matrix, k);
    EXPECT_EQ(ret, expected);
}

TEST(Kth_smallest_elements_in_a_sorted_matrix, t2) {
    vector<vector<int>> const matrix = {{-5}};
    int const k = 1;
    int const expected = -5;
    // Explanation: The elements in the matrix are [-5]
    // and the 1th smallest number is -5
    Solution sl;
    int const ret = sl.KthSmallest(matrix, k);
    EXPECT_EQ(ret, expected);
}

TEST(Kth_smallest_elements_in_a_sorted_matrix_v2, t2) {
    vector<vector<int>> matrix = {{-5}};
    int const k = 1;
    int const expected = -5;
    // Explanation: The elements in the matrix are [-5]
    // and the 1th smallest number is -5
    Solution sl;
    int const ret = sl.KthSmallestOn2(matrix, k);
    EXPECT_EQ(ret, expected);
}
TEST(Kth_smallest_elements_in_a_sorted_matrix_v3, t2) {
    vector<vector<int>> matrix = {{-5}};
    int const k = 1;
    int const expected = -5;
    // Explanation: The elements in the matrix are [-5]
    // and the 1th smallest number is -5
    Solution sl;
    int const ret = sl.KthSmallestV2(matrix, k);
    EXPECT_EQ(ret, expected);
}
}  // namespace
