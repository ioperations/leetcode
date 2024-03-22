// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <catch2/catch_test_macros.hpp>
#include <climits>
#include <string>
#include <unordered_map>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int LengthOfLongestSubstring(string s) {
        int n = s.size();
        int ans = INT_MIN, i = 0, j = 0;
        unordered_map<char, int> m;
        if (n == 0) return 0;
        for (j = 0; j < n; j++) {
            m[s[j]]++;
            if ((int)m.size() == j - i + 1) {
                ans = max(ans, j - i + 1);
            } else if ((int)m.size() < j - i + 1) {
                while ((int)m.size() < j - i + 1) {
                    m[s[i]]--;
                    if (m[s[i]] == 0) m.erase(s[i]);
                    i++;
                }
            }
        }
        return ans;
    }
};

TEST(leetcode3_2_v2, t2) {
    std::string in("abcabcbb");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 3);
}
TEST(leetcode3_2_v2, t3) {
    std::string in("bbbbbb");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 1);
}
TEST(leetcode3_2_v2, t4) {
    std::string in("pwwwkew");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 3);
}
TEST(leetcode3_2_v2, t5) {
    std::string in("");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 0);
}
TEST(leetcode3_2_v2, t2) {
    std::string in("aab");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 2);
}
}  // namespace
