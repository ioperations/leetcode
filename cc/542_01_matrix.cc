/*
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for
each cell.

The distance between two adjacent cells is 1.
*/

#include <array>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    std::array<int, 4> m_dx = {0, 0, 1, -1};
    std::array<int, 4> m_dy = {1, -1, 0, 0};
    struct Node {
        int m_x;
        int m_y;
        int m_step;
        Node(int x, int y, int step) : m_x(x), m_y(y), m_step(step) {}
    };

    vector<vector<int>> UpdateMatrix(vector<vector<int>>& mat) {
        int const m = static_cast<int>(mat.size());
        int const n = static_cast<int>(mat.at(0).size());
        vector<vector<int>> ans(m, vector<int>(n, 0));
        queue<Node> q;
        vector<vector<int>> vis(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat.at(i).at(j) == 0) {
                    q.emplace(i, j, 0);
                    vis.at(i).at(j) = 1;
                }
            }
        }
        while (!q.empty()) {
            Node const cur = q.front();
            q.pop();
            ans.at(cur.m_x).at(cur.m_y) = cur.m_step;

            for (int i = 0; i < 4; i++) {
                int const nx = cur.m_x + m_dx.at(i);
                int const ny = cur.m_y + m_dy.at(i);
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis.at(nx).at(ny)) {
                    continue;
                }
                vis.at(nx).at(ny) = 1;
                q.emplace(nx, ny, cur.m_step + 1);
            }
        }
        return ans;
    }
};

TEST(V, t1) {
    std::vector<std::vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    std::vector<std::vector<int>> const output = {
        {0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    Solution sl;
    auto ret = sl.UpdateMatrix(mat);
    EXPECT_EQ(output, ret);
}

TEST(V, t2) {
    std::vector<std::vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};

    std::vector<std::vector<int>> const output = {
        {0, 0, 0}, {0, 1, 0}, {1, 2, 1}};
    Solution sl;
    auto ret = sl.UpdateMatrix(mat);
    EXPECT_EQ(output, ret);
}

}  // namespace
