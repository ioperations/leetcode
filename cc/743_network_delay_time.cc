// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You are given a network of n nodes, labeled from 1 to n. You are also given
    times, a list of travel times as directed edges times[i] = (ui, vi, wi),
   where ui is the source node, vi is the target node, and wi is the time it
   takes for a signal to travel from source to target.

    We will send a signal from a given node k. Return the time it takes for all
   the n nodes to receive the signal. If it is impossible for all the n nodes to
    receive the signal, return -1.
*/

#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int NetworkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& it : times) {
            adj[it[0]].emplace_back(it[1], it[2]);
        }

        vector<int> dist(n + 1, 1e9);
        dist[0] = dist[k] = 0;

        queue<pair<int, int>> q;
        q.emplace(k, 0);
        while (q.size()) {
            int sz = q.size();
            while (sz--) {
                auto [node, prev] = q.front();
                q.pop();
                for (auto& it : adj[node]) {
                    int const curr_time = prev + it.second;
                    if (dist[it.first] > curr_time) {
                        dist[it.first] = curr_time;
                        q.emplace(it.first, curr_time);
                    }
                }
            }
        }

        int ans = 0;
        for (auto it : dist) {
            if (it == 1e9) return -1;
            ans = max(ans, it);
        }
        return ans;
    }

   public:
    const int m_max_time = 1e8;
    using pa = pair<int, int>;

    int NetworkDelayTimeV1(vector<vector<int>>& times, int n, int k) {
        vector<vector<pa>> graph(n + 1);
        vector<int> visited(n + 1);
        vector<int> dist(n + 1, m_max_time);
        dist[k] = 0;

        for (auto& edge : times) {
            int u = edge[0], v = edge[1], time = edge[2];
            graph[u].emplace_back(time, v);
        }

        priority_queue<pa, vector<pa>, greater<>> pq;
        pq.emplace(0, k);
        while (!pq.empty()) {
            auto [current_time, current_node] = pq.top();
            pq.pop();

            if (visited[current_node]) continue;

            for (auto& [time, adj_current_node] : graph[current_node]) {
                if (current_time + time < dist[adj_current_node]) {
                    dist[adj_current_node] = current_time + time;
                    pq.emplace(dist[adj_current_node], adj_current_node);
                }
            }

            visited[current_node] = true;
        }

        int ans = 0;
        for (int node = 1; node <= n; node++) {
            if (dist[node] == m_max_time) return -1;
            ans = max(ans, dist[node]);
        }

        return ans;
    }
};

TEST(network_delay_time, t1) {
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4, k = 2;
    int const output = 2;

    Solution sl;
    int ret = sl.NetworkDelayTime(times, n, k);
    EXPECT_EQ(ret, output);

    ret = sl.NetworkDelayTimeV1(times, n, k);
    EXPECT_EQ(ret, output);
}

TEST(network_delay_time, t2) {
    vector<vector<int>> times = {{1, 2, 1}};
    int n = 2, k = 1;
    int const output = 1;

    Solution sl;
    int ret = sl.NetworkDelayTime(times, n, k);
    EXPECT_EQ(ret, output);
    ret = sl.NetworkDelayTimeV1(times, n, k);
    EXPECT_EQ(ret, output);
}

TEST(network_delay_time, t3) {
    vector<vector<int>> times = {{1, 2, 1}};
    int n = 2, k = 2;
    int const output = -1;

    Solution sl;
    int ret = sl.NetworkDelayTime(times, n, k);
    EXPECT_EQ(ret, output);

    ret = sl.NetworkDelayTimeV1(times, n, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
