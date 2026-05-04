// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <iterator>
#include <set>
#include <string>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int LengthOfLongestSubstring(std::string s) {
        std::set<char> visited{};
        int max = 0;
        int continued = 0;
        int j = 0;
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            j = i;
            auto z = visited.find(s.at(j));
            for (; z == std::end(visited) && j < static_cast<int>(s.size());) {
                // 没有找到
                visited.emplace(s.at(j));
                continued++;
                max = std::max(max, continued);
                j++;
                if (j < static_cast<int>(s.size())) {
                    z = visited.find(s.at(j));
                }
            }
            continued = 0;
            visited.erase(visited.begin(), visited.end());
        }
        return max;
    }
};

TEST(R1, t2) {
    std::string const in("abcabcbb");
    Solution slu;
    int const ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 3);
}
TEST(R1, t3) {
    std::string const in("bbbbbb");
    Solution slu;
    int const ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 1);
}
TEST(R1, t4) {
    std::string const in("pwwwkew");
    Solution slu;
    int const ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 3);
}
TEST(R1, t5) {
    std::string const in("");
    Solution slu;
    int const ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 0);
}
TEST(R2, t2) {
    std::string const in("aab");
    Solution slu;
    int const ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 2);
}

}  // namespace
