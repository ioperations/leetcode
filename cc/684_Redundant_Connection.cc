
/**
 * In this problem, a tree is an undirected graph that is connected and has no
 * cycles. You are given a graph that started as a tree with n nodes labeled
 * from 1 to n, with one additional edge added. The added edge has two different
 * vertices chosen from 1 to n, and was not an edge that already existed. The
 * graph is represented as an array edges of length n where edges[i] = [ai, bi]
 * indicates that there is an edge between nodes ai and bi in the graph. Return
 * an edge that can be removed so that the resulting graph is a tree of n nodes.
 * If there are multiple answers, return the answer that occurs last in the
 * input.
 */
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> FindRedundantConnection(vector<vector<int>>& edges) {
      /**
      The problem asks us to find a redundant connection in a graph
              formed by edges. A "redundant connection" is the edge that, when
         added, creates a cycle. We are tasked with finding the first such
         edge in the given list. Since the graph initially has no cycles, our
         goal is to detect the first edge that completes a cycle.

      To achieve this, we maintain a representation of the graph using
         an adjacency list. We can then determine if adding a new edge forms a
         cycle by checking if there is already a path between the two nodes of
         that edge. If a path exists, the edge forms a cycle, and we return
         it.

      - Approach
              Graph Representation:
              Use an unordered_map<int, vector<int>> to represent the graph as
         an adjacency list. This data structure allows us to dynamically store
         the connections between nodes and efficiently traverse the graph.

       - Cycle Detection Without DFS/BFS:
              Instead of a standard DFS or BFS, implement a custom iterative
              path-checking mechanism:

              Use a stack to simulate traversal starting from one node.
              Use an unordered_set to track visited nodes during this process.
              If the target node is found during traversal, it indicates that
         adding the current edge would form a cycle. Processing Edges:

      - Iterate through each edge in the input.
              Before adding an edge, check if there is already a path between
         the two nodes using the path-checking function (isConnected). If a
         path exists, return the current edge as it forms the first cycle. If
         no path exists, add the edge to the graph by updating the adjacency
         list. Termination: Once we find the first edge forming a cycle,
         return it. Otherwise, if no cycles are detected (which won't happen
         based on the problem constraints), return an empty result.

      - Complexity
              Time Complexity:

              For each edge, we check if there is a path between two nodes
         using an iterative traversal. In the worst case, this traversal can
         visit all nodes (O(V)), and we repeat this for each edge (O(E)).
         Hence, the overall time complexity is (O(E+ V)), where (E) is the
         number of edges and (V) is the number of nodes. Space Complexity:

              The adjacency list requires (O(V + E)) space.
              The stack and visited set for traversal require (O(V)) space
         during path checking. Therefore, the total space complexity is (O(V +
         E)).
      */
      unordered_map<int, vector<int>> graph;

      auto is_connected = [&](int u, int v) {
        unordered_set<int> visited;
        stack<int> stack;
        stack.push(u);

        while (!stack.empty()) {
          int const node = stack.top();
          stack.pop();

          if (visited.count(node)) continue;
          visited.insert(node);

          if (node == v) return true;

          for (int const neighbor : graph[node]) {
            stack.push(neighbor);
          }
        }
        return false;
      };

      for (const auto& edge : edges) {
        int u = edge[0], v = edge[1];

        if (graph.count(u) && graph.count(v) && is_connected(u, v)) {
          return edge;
        }

        graph[u].push_back(v);
        graph[v].push_back(u);
      }

      return {};
    }
};

#include "gtest/gtest.h"

TEST(t0, t1) {
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> const output = {2, 3};
    Solution sl;
    vector<int> const ret = sl.FindRedundantConnection(edges);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    vector<int> const output = {1, 4};
    Solution sl;
    vector<int> const ret = sl.FindRedundantConnection(edges);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> const output = {2, 3};
    Solution sl;
    vector<int> const ret = sl.FindRedundantConnection(edges);
    EXPECT_EQ(ret, output);
}