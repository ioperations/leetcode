// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <climits>
#include <string>
#include <unordered_map>

using namespace std;

namespace {
class Solution {
   public:
    int LengthOfLongestSubstring(string s) {
        int const n = s.size();
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

}  // namespace

#include "gtest/gtest.h"

TEST(longest_substring, t1) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("abcabcbb");
    EXPECT_EQ(ret, 3);
}

TEST(longest_substring, t2) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("bbbbb");
    EXPECT_EQ(ret, 1);
}

TEST(longest_substring, t3) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("pwwkew");
    EXPECT_EQ(ret, 3);
}

TEST(longest_substring, t4) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("");
    EXPECT_EQ(ret, 0);
}

TEST(longest_substring, t5) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("au");
    EXPECT_EQ(ret, 2);
}
