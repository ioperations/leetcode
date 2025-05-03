/*
 * You are given a positive integer n representing the number of nodes in an
 * undirected graph. The nodes are labeled from 1 to n.
 *
 * You are also given a 2D integer array edges, where edges[i] = [ai, bi]
 * indicates that there is a bidirectional edge between nodes ai and bi. Notice
 * that the given graph may be disconnected.
 *
 * Divide the nodes of the graph into m groups (1-indexed) such that:
 *
 * Each node in the graph belongs to exactly one group.
 * For every pair of nodes in the graph that are connected by an edge [ai, bi],
 * if ai belongs to the group with index x, and bi belongs to the group with
 * index y, then |y - x| = 1. Return the maximum number of groups (i.e., maximum
 * m) into which you can divide the nodes. Return -1 if it is impossible to
 * group the nodes with the given conditions.
 */

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0] - 1].push_back(e[1] - 1);
            adj[e[1] - 1].push_back(e[0] - 1);
        }
        vector<int> color(n, -1);
        vector<vector<int>> components;
        for (int i = {0}; i < n; ++i) {
            if (color[i] == -1) {
                components.emplace_back();
                if (!dfs(i, 0, adj, color, components.back())) return -1;
            }
        }
        int maxGroups = {0};
        for (const auto& comp : components) {
            maxGroups += bfsMaxDepth(comp, adj);
        }
        return maxGroups;
    }

   private:
    bool dfs(int node, int col, const vector<vector<int>>& adj,
             vector<int>& color, vector<int>& comp) {
        color[node] = col;
        comp.push_back(node);
        for (int neighbor : adj[node]) {
            if (color[neighbor] == col) return false;
            if (color[neighbor] == -1 &&
                !dfs(neighbor, 1 - col, adj, color, comp))
                return false;
        }
        return true;
    }
    int bfsMaxDepth(const vector<int>& comp, const vector<vector<int>>& adj) {
        int maxDepth = {0};
        for (int start : comp) {
            vector<int> depth(adj.size(), -1);
            vector<int> queue = {start};
            depth[start] = {0};
            for (size_t i = {0}; i < queue.size(); ++i) {
                int node = queue[i];
                for (int neighbor : adj[node]) {
                    if (depth[neighbor] == -1) {
                        depth[neighbor] = depth[node] + 1;
                        queue.push_back(neighbor);
                    }
                }
            }
            maxDepth = max(maxDepth, *max_element(depth.begin(), depth.end()));
        }
        return maxDepth + 1;
    }
};

#include "gtest/gtest.h"

TEST(t0, t1) {
    /**
     * Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
     * Output: 4
     * Explanation: As shown in the image we:
     * - Add node 5 to the first group.
     * - Add node 1 to the second group.
     * - Add nodes 2 and 4 to the third group.
     * - Add nodes 3 and 6 to the fourth group.
     * We can see that every edge is satisfied.
     * It can be shown that that if we create a fifth group and move any node
     * from the third or fourth group to it, at least on of the edges will not
     * be satisfied.
     */
    int n = 6;
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {4, 5}, {5, 6}};
    Solution sl;
    int ret = sl.magnificentSets(n, edges);
    EXPECT_EQ(ret, 6);
}

TEST(t0, t2) {
    int n = 3;
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {1, 3}};
    Solution sl;
    int ret = sl.magnificentSets(n, edges);
    EXPECT_EQ(ret, -1);
}
