// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
There are n servers numbered from 0 to n - 1 connected by undirected
server-to-server connections forming a network where connections[i] = [ai, bi]
represents a connection between servers ai and bi. Any server can reach other
servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers
unable to reach some other server.

Return all critical connections in the network in any order.
*/

#include <functional>
#include <vector>

using namespace std;

class Solution {
   public:
    // You can search "find bridges graph" in youtube or google to understand
    // algorithm, that is easiest way.
    vector<vector<int>> CriticalConnections(int n,
                                            vector<vector<int>> &connections) {
        vector<vector<int>> adj(n);
        for (const auto &c : connections) {
            adj[c[0]].push_back(c[1]);
            adj[c[1]].push_back(c[0]);
        }

        vector<vector<int>> result;
        vector<int> vis(n, -1);
        function<int(int, int, int)> dfs = [&](int u, int p, int rank) -> int {
            if (vis[u] != -1) return vis[u];
            vis[u] = rank;

            int min_rank = rank;
            for (int v : adj[u]) {
                if (v == p) continue;
                int returned_rank = dfs(v, u, rank + 1);
                if (returned_rank == rank + 1) result.push_back({u, v});
                min_rank = min(min_rank, returned_rank);
            }

            return min_rank;
        };

        dfs(0, -1, 0);

        return result;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <set>

TEST(t0, t1) {
    int n = 4;
    std::vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    std::vector<vector<int>> output = {{1, 3}};

    Solution sl;
    auto ret = sl.CriticalConnections(n, connections);

    EXPECT_EQ(output, ret);

    // Explanation : [[ 3, 1 ]] is also accepted.
}
TEST(t0, t2) {
    int n = 2;
    std::vector<vector<int>> connections = {{0, 1}};
    std::vector<vector<int>> output = {{0, 1}};

    Solution sl;
    auto ret = sl.CriticalConnections(n, connections);

    // const set<vector<int>> ret_set(ret.begin(), ret.end());

    EXPECT_EQ(output, ret);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
