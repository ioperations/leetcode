/*
    You are given a 0-indexed binary string s and two integers minJump and
    maxJump. In the beginning, you are standing at index 0, which is equal to
   '0'. You can move from index i to index j if the following conditions are
   fulfilled:

    i + minJump <= j <= min(i + maxJump, s.length - 1), and
    s[j] == '0'.
    Return true if you can reach index s.length - 1 in s, or false otherwise.
*/

#include <functional>
#include <map>
#include <queue>
#include <string>
using namespace std;

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
        int size = s.size();
        std::map<int, bool> cache;
        function<bool(int)> fun = [&](int index) -> bool {
            // pass
            if (index == size - 1) {
                return true;
            }
            if (cache.count(index)) return cache[index];

            for (int i = min_jump; i <= max_jump; i++) {
                if (index + i < size && s[index + i] == '0') {
                    if (fun(index + i)) return cache[index] = true;
                }
            }

            return false;
        };
        return fun(0);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string s = "011010";
    int min_jump = 2, max_jump = 3;
    bool output = true;
    // In the first step, move from index 0 to index 3. In the second step, move
    // from index 3 to index 5.
    Solution sl;
    bool ret = sl.CanReach(s, min_jump, max_jump);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = "01101110";
    int min_jump = 2, max_jump = 3;
    bool output = false;
    // In the first step, move from index 0 to index 3. In the second step, move
    // from index 3 to index 5.
    Solution sl;
    bool ret = sl.CanReach(s, min_jump, max_jump);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
