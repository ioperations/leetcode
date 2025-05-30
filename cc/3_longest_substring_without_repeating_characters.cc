// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <limits>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace {

class Solution {
   public:
    int LengthOfLongestSubstring(std::string s) {
        int const n = s.size();
        int ans = std::numeric_limits<int>::min(), i = 0, j = 0;
        std::unordered_map<char, int> m;
        if (n == 0) return 0;
        for (j = 0; j < n; j++) {
            m[s[j]]++;
            if ((int)m.size() == j - i + 1) {
                ans = std::max(ans, j - i + 1);
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

TEST(longest_substring_without_repeating_characters_v3, t2) {
    std::string const s("bbbbb");
    Solution sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(1, ret);
}

TEST(longest_substring_without_repeating_characters_v2, t2) {
    std::string const s("abcabcbb");
    Solution sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(3, ret);
}

TEST(longest_substring_without_repeating_characters_v2, t2ss) {
    std::string const s("");
    Solution sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(0, ret);
}

TEST(t1sss, t2ss) {
    std::string const s("pwwkew");
    Solution sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(3, ret);
}

}  // namespace
