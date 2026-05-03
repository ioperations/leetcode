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

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool CanReach(string s, int min_jump, int max_jump) {
        // pass
        if (s.at(s.size() - 1) != '0') return false;
        vector<int> list;
        for (int i = 0; i < static_cast<int>(s.size()); i++) {
            if (s.at(i) == '0') list.push_back(i);
        }
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        for (int i = 0; i < static_cast<int>(list.size()); i++) {
            if (q.empty()) return false;
            if (list.at(i) >= q.front().first && list.at(i) <= q.front().second) {
                if (list.at(i) == static_cast<int>(s.size()) - 1) return true;
                q.emplace(list.at(i) + min_jump, list.at(i) + max_jump);
            } else {
                if (list.at(i) > q.front().second) {
                    q.pop();
                    i--;
                }
            }
        }
        return false;
    }
};

TEST(JumpGameVii, t1) {
    string const s = "011010";
    int min_jump = 2, max_jump = 3;
    bool const output = true;
    // In the first step, move from index 0 to index 3. In the second step, move
    // from index 3 to index 5.
    Solution sl;
    bool const ret = sl.CanReach(s, min_jump, max_jump);
    EXPECT_EQ(ret, output);
}

TEST(JumpGameVii, t2) {
    string const s = "01101110";
    int min_jump = 2, max_jump = 3;
    bool const output = false;
    // In the first step, move from index 0 to index 3. In the second step, move
    // from index 3 to index 5.
    Solution sl;
    bool const ret = sl.CanReach(s, min_jump, max_jump);
    EXPECT_EQ(ret, output);
}

}  // namespace
