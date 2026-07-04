/*
 * You are given a positive integer n representing n cities numbered from 1 to
 * n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei]
 * indicates that there is a bidirectional road between cities ai and bi with a
 * distance equal to distancei. The cities graph is not necessarily connected.
 *
 * The score of a path between two cities is defined as the minimum distance of
 * a road in this path.
 *
 * Return the minimum possible score of a path between cities 1 and n.
 *
 * Note:
 *
 * A path is a sequence of roads between two cities.
 * It is allowed for a path to contain the same road multiple times, and you can
 * visit cities 1 and n multiple times along the path. The test cases are
 * generated such that there is at least one path between 1 and n.
 *
 *
 * 2 <= n <= 105
 * 1 <= roads.length <= 105
 * roads[i].length == 3
 * 1 <= ai, bi <= n
 * ai != bi
 * 1 <= distancei <= 104
 * There are no repeated edges.
 * There is at least one path between 1 and n.k
 */
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace {

class Solution {
   public:
    int MinScore(int n, vector<vector<int>>& roads) {
        vector<int> visited(n + 1, 0);
        auto roads_matrix = BuildRoads(roads);
        visited[1] = 1;
        Bfs(visited, roads_matrix);

        int min = std::numeric_limits<int>::max();
        for (auto& p : roads) {
            if (visited[p[0]] == 1 && visited[p[1]] == 1) {
                min = std::min(min, p[2]);
            }
        }
        return min;
    }

    void Bfs(vector<int>& visited,
             unordered_map<int, unordered_set<int>>& roads_matrix) {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int id = q.front();
            visited[id] = true;
            q.pop();
            for (auto& next : roads_matrix[id]) {
                if (visited[next] == 0) {
                    q.push(next);
                }
            }
        }
    }

    unordered_map<int, unordered_set<int>> BuildRoads(
        vector<vector<int>>& roads) {
        unordered_map<int, unordered_set<int>> ret;
        for (auto& p : roads) {
            ret[p[0]].emplace(p[1]);
            ret[p[1]].emplace(p[0]);
        }
        return ret;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(minScore, t0) {
    int n = 4;
    vector<vector<int>> roads = {{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}};
    int output = 5;
    Solution sl;
    // Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2
    // -> 4. The score of this path is min(9,5) = 5. It can be shown that no
    // other path has less score.}

    int ret = sl.MinScore(n, roads);
    EXPECT_EQ(output, ret);
}

TEST(minScore, t1) {
    int n = 4;
    vector<vector<int>> roads = {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}};
    int output = 2;
    Solution sl;
    // The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3
    // -> 4. The score of this path is min(2,2,4,7) = 2

    int ret = sl.MinScore(n, roads);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
