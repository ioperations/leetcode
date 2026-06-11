/*
 * There is an undirected tree with n nodes labeled from 1 to n, rooted at
 * node 1. The tree is represented by a 2D integer array edges of length n - 1,
 * where edges[i] = [ui, vi] indicates that there is an edge between nodes ui
 * and vi.
 *
 * Initially, all edges have a weight of 0. You must assign each edge a weight
 * of either 1 or 2.
 *
 * The cost of a path between any two nodes u and v is the total weight of all
 * edges in the path connecting them.
 *
 * Select any one node x at the maximum depth. Return the number of ways to
 * assign edge weights in the path from node 1 to x such that its total cost is
 * odd.
 *
 * Since the answer may be large, return it modulo 109 + 7.
 *
 * Note: Ignore all edges not in the path from node 1 to x.
 *
 * 2 <= n <= 105
 * edges.length == n - 1
 * edges[i] == [ui, vi]
 * 1 <= ui, vi <= n
 * edges represents a valid tree.
 */

#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    int AssignEdgeWeights(vector<vector<int>>& edges) {
        BuildDepth(edges);

        int z = 1;
        int depth = 0;
        set<int> visited{z};
        Dfs(z, depth, visited);

        return Qpow(2, m_max - 1);
    }

   private:
    static constexpr int mod = 1e9 + 7;
    int Qpow(long long x, int y) {
        int res = 1;
        for (; y; y >>= 1) {
            if (y & 1) {
                res = res * x % mod;
            }
            x = x * x % mod;
        }
        return res;
    }

    void BuildDepth(vector<vector<int>>& edges) {
        for (const auto& pair : edges) {
            auto p = pair[0];
            auto q = pair[1];

            m_nodes.emplace(p);
            m_nodes.emplace(q);

            m_graph[p].emplace(q);
            m_graph[q].emplace(p);
        }
    }
    void Dfs(int start, int& depth, set<int>& visited) {
        for (auto& v : m_graph[start]) {
            if (!visited.count(v)) {
                visited.emplace(v);
                depth++;
                if (depth > m_max) {
                    m_max = depth;
                }
                Dfs(v, depth, visited);
                depth--;
                visited.erase(v);
            }
        }
    }

   private:
    int m_max = 0;

    std::set<int> m_nodes;
    std::unordered_map<int, set<int>> m_graph;
};
}  // namespace

#include <gtest/gtest.h>

TEST(assignEdgeWeights, t1) {
    vector<vector<int>> edges = {{1, 2}};

    int output = 1;
    Solution sl;
    int ret = sl.AssignEdgeWeights(edges);
    EXPECT_EQ(output, ret);
    /*
    Explanation:

    The path from Node 1 to Node 2 consists of one edge (1 → 2).
    Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the
    number of valid assignments is 1.
    */
}

TEST(assignEdgeWeights, t2) {
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {3, 4}, {3, 5}};

    int output = 2;
    Solution sl;
    int ret = sl.AssignEdgeWeights(edges);
    EXPECT_EQ(output, ret);
    /*
    Explanation:
    The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node
    can be selected for processing. For example, the path from Node 1 to Node 4
    consists of two edges (1 → 3 and 3 → 4). Assigning weights (1,2) or (2,1)
    results in an odd cost. Thus, the number of valid assignments is 2.
    */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
