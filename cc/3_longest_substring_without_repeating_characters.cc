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
    [[nodiscard]] int LengthOfLongestSubstring(std::string s) const {
        int const n = static_cast<int>(s.size());
        int ans = std::numeric_limits<int>::min(), i = 0, j = 0;
        std::unordered_map<char, int> m;
        if (n == 0) return 0;
        for (j = 0; j < n; j++) {
            m[s.at(j)]++;
            if (static_cast<int>(m.size()) == j - i + 1) {
              ans = std::max(ans, j - i + 1);
            } else if (static_cast<int>(m.size()) < j - i + 1) {
              while (static_cast<int>(m.size()) < j - i + 1) {
                m[s.at(i)]--;
                if (m[s.at(i)] == 0) m.erase(s.at(i));
                i++;
              }
            }
        }
        return ans;
    }
};

TEST(LongestSubstringWithoutRepeatingCharactersV3, t2) {
    std::string const s("bbbbb");
    Solution const sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(1, ret);
}

TEST(LongestSubstringWithoutRepeatingCharactersV2, t2) {
    std::string const s("abcabcbb");
    Solution const sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(3, ret);
}

TEST(LongestSubstringWithoutRepeatingCharactersV2, t2ss) {
    std::string const s("");
    Solution const sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(0, ret);
}

TEST(T1sss, t2ss) {
    std::string const s("pwwkew");
    Solution const sss;
    int const ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(3, ret);
}

}  // namespace
