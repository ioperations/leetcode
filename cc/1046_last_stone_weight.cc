// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

// You are given an array of integers stones where stones[i] is the weight of
// the ith stone.

// We are playing a game with the stones. On each turn, we choose the heaviest
// two stones and smash them together. Suppose the heaviest two stones have
// weights x and y with x <= y. The result of this smash is:

// If x == y, both stones are destroyed, and
// If x != y, the stone of weight x is destroyed, and the stone of weight y has
// new weight y - x. At the end of the game, there is at most one stone left.

#include <stdlib.h>
#include <queue>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    int LastStoneWeight(vector<int> &stones) {
        std::priority_queue<int> q;
        for (auto &ptr : stones) {
            q.push(ptr);
        }

        while (!(q.size() == 1 || q.size() == 0)) {
            int v1 = q.top();
            q.pop();
            int v2 = q.top();
            q.pop();
            if (v1 == v2) {
                continue;
            }
            q.push(abs(v2 - v1));
        }
        if (q.size()) {
            return q.top();
        }
        return 0;
    }
};


TEST(t0, t1) {
    // Input:
    // stones = [ 2, 7, 4, 1, 8, 1 ] Output : 1 Explanation
    // : We combine 7 and
    // 8 to get 1 so the array converts to[2, 4, 1, 1, 1] then,
    // we combine 2 and 4 to get 2 so the array converts to[2, 1, 1, 1] then,
    // we combine 2 and 1 to get 1 so the array converts to[1, 1, 1] then,
    // we combine 1 and 1 to get 0 so the array converts to[1] then that's the
    // value of the last stone.

    std::vector<int> stones{2, 7, 4, 1, 8, 1};
    Solution s;
    int ret = s.LastStoneWeight(stones);
    EXPECT_EQ(ret, 1);
}

TEST(t0, t2) {
    std::vector<int> stones{1};
    Solution s;
    int ret = s.LastStoneWeight(stones);
    EXPECT_EQ(ret, 1);
}
}
