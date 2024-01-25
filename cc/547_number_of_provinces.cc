// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
There are n cities. Some of them are connected, while some are not. If city a is
connected directly with city b, and city b is connected directly with city c,
then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other
cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith
city and the jth city are directly connected, and isConnected[i][j] = 0
otherwise.

Return the total number of provinces.
*/

#include <vector>
using namespace std;

class Solution {
   public:
    int FindCircleNum(vector<vector<int>> &is_connected) {
        if ((int)is_connected.size() == 1) return 1;

        int is_connected_size = is_connected.size();
        vector<vector<int>> visited(is_connected.size());
        int provinces = 0;
        for (int i = 0; i < is_connected_size; i++) {
            vector<int> row_size(is_connected_size);
            visited[i] = row_size;
        }

        for (int i = 0; i < (int)is_connected.size(); i++) {
            if (visited[i][0]) continue;
            if (!visited[i][0]) {
                visited[i][0] = 1;
                DfSprovince(is_connected, visited, i, 0);
                provinces++;
            }
        }
        return provinces;
    }

   public:
    void DfSprovince(vector<vector<int>> &is_connected,
                     vector<vector<int>> &is_visited, int i, int j) {
        if (j == (int)is_connected.size()) return;
        is_visited[i][j] = 1;
        // isVisited[i][j] = 1;
        if (is_connected[i][j] == 1 && i != j && is_visited[j][0] == 0) {
            is_visited[j][0] = 1;
            DfSprovince(is_connected, is_visited, j, 0);
        }

        DfSprovince(is_connected, is_visited, i, j + 1);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<vector<int>> v{{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    /*
     ___     ___
    | 1 |___| 2 |
    |___|   |___|

         ___
        | 3 |
        |___|
    */
    Solution sl;
    int ret = sl.FindCircleNum(v);
    EXPECT_EQ(ret, 2);
}

TEST(t0, t2) {
    std::vector<vector<int>> v{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    /*
     ___     ___
    | 1 |   | 2 |
    |___|   |___|

         ___
        | 3 |
        |___|
    */

    Solution sl;
    int ret = sl.FindCircleNum(v);
    EXPECT_EQ(ret, 3);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
