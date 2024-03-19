// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <iterator>
#include <set>
#include <string>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    int LengthOfLongestSubstring(std::string s) {
        std::set<char> visited{};
        int max = 0;
        int continued = 0;
        int j;
        for (int i = 0; i < (int)s.size(); ++i) {
            j = i;
            auto z = visited.find(s[j]);
            for (; z == std::end(visited) && j < (int)s.size();) {
                // 没有找到
                visited.emplace(s[j]);
                continued++;
                max = std::max(max, continued);
                j++;
                z = visited.find(s[j]);
            }
            continued = 0;
            visited.erase(visited.begin(), visited.end());
        }
        return max;
    }
};

TEST(r1, t2) {
    std::string in("abcabcbb");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 3);
}
TEST(r1, t3) {
    std::string in("bbbbbb");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 1);
}
TEST(r1, t4) {
    std::string in("pwwwkew");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 3);
}
TEST(r1, t5) {
    std::string in("");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 0);
}
TEST(r2, t2) {
    std::string in("aab");
    Solution slu;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 2);
}

}  // namespace
