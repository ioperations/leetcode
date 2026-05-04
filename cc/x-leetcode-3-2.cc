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
    int LengthOfLongestSubstring(string const& s) {
        int const n = static_cast<int>(s.size());
        int ans = INT_MIN, i = 0, j = 0;
        unordered_map<char, int> m;
        if (n == 0) return 0;
        for (j = 0; j < n; j++) {
            m[s.at(j)]++;
            if (static_cast<int>(m.size()) == j - i + 1) {
                ans = max(ans, j - i + 1);
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

}  // namespace

#include "gtest/gtest.h"

TEST(longestV, t1) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("abcabcbb");
    EXPECT_EQ(ret, 3);
}

TEST(longestV, t2) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("bbbbb");
    EXPECT_EQ(ret, 1);
}

TEST(longestV, t3) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("pwwkew");
    EXPECT_EQ(ret, 3);
}

TEST(longestV, t4) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("");
    EXPECT_EQ(ret, 0);
}

TEST(longestV, t5) {
    Solution sl;
    int const ret = sl.LengthOfLongestSubstring("au");
    EXPECT_EQ(ret, 2);
}
