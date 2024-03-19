// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
There is an undirected graph with n nodes, where each node is numbered between 0
and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes
that node u is adjacent to. More formally, for each v in graph[u], there is an
undirected edge between node u and node v. The graph has the following
properties:

There are no self-edges (graph[u] does not contain u).
There are no parallel edges (graph[u] does not contain duplicate values).
If v is in graph[u], then u is in graph[v] (the graph is undirected).
The graph may not be connected, meaning there may be two nodes u and v such that
there is no path between them. A graph is bipartite if the nodes can be
partitioned into two independent sets A and B such that every edge in the graph
connects a node in set A and a node in set B.

Return true if and only if it is bipartite.
*/
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    vector<int> vis, col;
    bool Dfs(int v, int c, vector<vector<int>> &graph) {
        vis[v] = 1;
        col[v] = c;
        for (int child : graph[v]) {
            if (vis[child] == 0) {
                // here c^1 is for flipping 1 by 0 or 0 by 1, that is flip the
                // current color
                if (Dfs(child, c ^ 1, graph) == false) return false;
            } else {
                if (col[v] == col[child]) return false;
            }
        }
        return true;
    }

    bool IsBipartite(vector<vector<int>> &graph) {
        /*
            A. Traverse each node of the graph and try to assign a color to them
           such that alternating nodes are of same color. B. If at any step, the
           child node color matches with the parent node color, then the graph
           is not bipartite. C. If no B found, then the graph is bipartite. So,
           return true at the end. D. Here, the two colors are represented by 0
           and 1.

           TIME COMPLEXITY
           O(n) [Since each node of the graph is traversed exactly once]
           SPACE COMPLEXITY
           O(n+n) [vis and col vectors are of size n each]
        */
        int n = graph.size();
        vis.resize(n);
        col.resize(n);

        for (int i = 0; i < n; ++i) {
            if (vis[i] == 0 && Dfs(i, 0, graph) == false) {
                return false;
            }
        }

        return true;
    }
};

TEST(is_graph_bipartite, t1) {
    /*
         ___         ___
        | 0 |_______| 1 |
        |___|       |___|
          |  \_       |
          |    \_     |
          |      \_   |
         _|_       \ _|_
        | 3 |_______| 2 |
        |___|       |___|
    */

    vector<vector<int>> graph = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
    bool expected = false;
    // There is no way to partition the nodes into two independent sets such
    // that every edge connects a node in one and a node in the other.
    Solution s;
    bool ret = s.IsBipartite(graph);
    EXPECT_EQ(ret, expected);
}

TEST(is_graph_bipartite, t2) {
    /*
         ___         ___
        | 0 |_______| 1 |
        |___|       |___|
          |           |
          |           |
          |           |
         _|_         _|_
        | 3 |_______| 2 |
        |___|       |___|
    */

    vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    bool expected = true;
    // We can partition the nodes into two sets: {0, 2} and {1, 3}.
    Solution s;
    bool ret = s.IsBipartite(graph);
    EXPECT_EQ(ret, expected);
}

}  // namespace
