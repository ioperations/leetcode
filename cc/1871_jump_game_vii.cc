// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You are given a 0-indexed binary string s and two integers minJump and
    maxJump. In the beginning, you are standing at index 0, which is equal to
   '0'. You can move from index i to index j if the following conditions are
   fulfilled:

    i + minJump <= j <= min(i + maxJump, s.length - 1), and
    s[j] == '0'.
    Return true if you can reach index s.length - 1 in s, or false otherwise.
*/

#include <queue>
#include <string>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    bool CanReach(string s, int min_jump, int max_jump) {
        // pass
        if (s[s.size() - 1] != '0') return false;
        vector<int> list;
        for (int i = 0; i < (int)s.size(); i++)
            if (s[i] == '0') list.push_back(i);
        queue<pair<int, int>> q;
        q.push({0, 0});
        for (int i = 0; i < (int)list.size(); i++) {
            if (q.empty()) return false;
            if (list[i] >= q.front().first && list[i] <= q.front().second) {
                if (list[i] == (int)s.size() - 1) return true;
                q.push({list[i] + min_jump, list[i] + max_jump});
            } else {
                if (list[i] > q.front().second) q.pop(), i--;
            }
        }
        return false;
    }
};

TEST(jump_game_vii, t1) {
    string s = "011010";
    int min_jump = 2, max_jump = 3;
    bool output = true;
    // In the first step, move from index 0 to index 3. In the second step, move
    // from index 3 to index 5.
    Solution sl;
    bool ret = sl.CanReach(s, min_jump, max_jump);
    EXPECT_EQ(ret, output);
}

TEST(jump_game_vii, t2) {
    string s = "01101110";
    int min_jump = 2, max_jump = 3;
    bool output = false;
    // In the first step, move from index 0 to index 3. In the second step, move
    // from index 3 to index 5.
    Solution sl;
    bool ret = sl.CanReach(s, min_jump, max_jump);
    EXPECT_EQ(ret, output);
}

}  // namespace
