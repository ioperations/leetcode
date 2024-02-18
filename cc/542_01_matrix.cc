/*
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for
each cell.

The distance between two adjacent cells is 1.
*/

#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    struct Node {
        int x;
        int y;
        int step;
        Node(int x, int y, int step) : x(x), y(y), step(step) {}
    };

    vector<vector<int>> UpdateMatrix(vector<vector<int>> &mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        queue<Node> q;
        vector<vector<int>> vis(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    q.push(Node(i, j, 0));
                    vis[i][j] = 1;
                }
            }
        }
        while (!q.empty()) {
            Node cur = q.front();
            q.pop();
            ans[cur.x][cur.y] = cur.step;

            for (int i = 0; i < 4; i++) {
                int nx = cur.x + dx[i];
                int ny = cur.y + dy[i];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny])
                    continue;
                vis[nx][ny] = 1;
                q.push(Node(nx, ny, cur.step + 1));
            }
        }
        return ans;
    }
};

TEST(_matrix, t1) {
    std::vector<std::vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    std::vector<std::vector<int>> output = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    Solution sl;
    auto ret = sl.UpdateMatrix(mat);
    EXPECT_EQ(output, ret);
}

TEST(_matrix, t2) {
    std::vector<std::vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};

    std::vector<std::vector<int>> output = {{0, 0, 0}, {0, 1, 0}, {1, 2, 1}};
    Solution sl;
    auto ret = sl.UpdateMatrix(mat);
    EXPECT_EQ(output, ret);
}

}  // namespace
