// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s, find the first non-repeating character in it and return its
 * index. If it does not exist, return -1.*/
#include <algorithm>
#include <unordered_map>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

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

TEST(first_unique_character_in_a_string, t1) {
    string s = "leetcode";
    Solution sl;
    int ret = sl.FirstUniqChar(s);
    EXPECT_EQ(ret, 0);
}

TEST(first_unique_character_in_a_string, t2) {
    string s = "loveleetcode";
    Solution sl;
    int ret = sl.FirstUniqChar(s);
    EXPECT_EQ(ret, 2);
}

TEST(first_unique_character_in_a_string, t3) {
    string s = "aabb";
    Solution sl;
    int ret = sl.FirstUniqChar(s);
    EXPECT_EQ(ret, -1);
}

}  // namespace
