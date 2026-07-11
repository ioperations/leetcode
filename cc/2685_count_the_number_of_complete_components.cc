/*
 *
 * You are given an integer n. There is an undirected graph with n vertices,
 * numbered from 0 to n - 1. You are given a 2D integer array edges where
 * edges[i] = [ai, bi] denotes that there exists an undirected edge connecting
 * vertices ai and bi.
 *
 * Return the number of complete connected components of the graph.
 *
 * A connected component is a subgraph of a graph in which there exists a path
 * between any two vertices, and no vertex of the subgraph shares an edge with a
 * vertex outside of the subgraph.
 *
 * A connected component is said to be complete if there exists an edge between
 * every pair of its vertices.
 *
 * 1 <= n <= 50
 * 0 <= edges.length <= n * (n - 1) / 2
 * edges[i].length == 2
 * 0 <= ai, bi <= n - 1
 * ai != bi
 * There are no repeated edges.
 * */
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace {

class Solution {
   public:
    int CountCompleteComponents(int n, vector<vector<int>>& edges) {
        // pass
        vector<int> visited(n, 0);
        vector<vector<int>> connected;

        for (auto& edge : edges) {
            int p = edge[0];
            int q = edge[1];
            m_matrix[p].emplace(q);
            m_matrix[q].emplace(p);
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                Bfs(visited, i, connected);
            }
        }

        int ret = 0;

        for (auto& graph : connected) {
            ret += Count(graph);
        }
        return ret;
    }

    int Count(vector<int>& graph) {
        int size = static_cast<int>(graph.size());
        if (size == 1) {
            return 1;
        }
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (m_matrix[graph[i]].count(graph[j]) == 0) {
                    return 0;
                }
            }
        }
        return 1;
    }

    void Bfs(vector<int>& visited, int i, vector<vector<int>>& connected) {
        queue<int> q;
        q.emplace(i);
        visited[i] = true;
        vector<int> ret{i};

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto& next : m_matrix[node]) {
                if (!visited[next]) {
                    ret.emplace_back(next);
                    visited[next] = true;
                    q.emplace(next);
                }
            }
        }
        connected.push_back(ret);
    }

   private:
    unordered_map<int, unordered_set<int>> m_matrix;
};
}  // namespace

#include <gtest/gtest.h>

TEST(countCompleteComponents, t0) {
    int n = 6;
    std::vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 4}};
    int output = 3;
    // Explanation: From the picture above, one can see that all of the
    // components of this graph are complete.

    Solution sl;
    int ret = sl.CountCompleteComponents(n, edges);
    EXPECT_EQ(output, ret);
}

TEST(countCompleteComponents, t1) {
    int n = 6;
    std::vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}};
    int output = 1;
    // The component containing vertices 0, 1, and 2 is complete since there is
    // an edge between every pair of two vertices. On the other hand, the
    // component containing vertices 3, 4, and 5 is not complete since there is
    // no edge between vertices 4 and 5. Thus, the number of complete components
    // in this graph is 1.

    Solution sl;
    int ret = sl.CountCompleteComponents(n, edges);
    EXPECT_EQ(output, ret);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
