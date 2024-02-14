// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s, find the first non-repeating character in it and return its
 * index. If it does not exist, return -1.*/
#include <string>
#include <unordered_map>
using namespace std;

#include <gtest/gtest.h>
namespace {
class Solution {
   public:
    int FirstUniqChar(string s) {
        unordered_map<char, pair<int, int>> m;
        int idx = s.size();
        for (int i = 0; i < (int)s.size(); i++) {
            m[s[i]].first++;
            m[s[i]].second = i;
        }
        for (const auto &[c, p] : m) {
            if (p.first == 1) {
                idx = min(idx, p.second);
            }
        }
        return idx == (int)s.size() ? -1 : idx;
        return 0;
    }
};

TEST(t0, t1) {
    string s = "leetcode";
    Solution sl;
    int ret = sl.FirstUniqChar(s);
    EXPECT_EQ(ret, 0);
}

TEST(t0, t2) {
    string s = "loveleetcode";
    Solution sl;
    int ret = sl.FirstUniqChar(s);
    EXPECT_EQ(ret, 2);
}

TEST(t0, t3) {
    string s = "aabb";
    Solution sl;
    int ret = sl.FirstUniqChar(s);
    EXPECT_EQ(ret, -1);
}

}  // namespace
