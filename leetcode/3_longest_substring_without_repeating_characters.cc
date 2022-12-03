#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
   public:
    int LengthOfLongestSubstring(string s) {
        int n = s.size();
        int ans = numeric_limits<int>::min(), i = 0, j = 0;
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

#if defined(TEST_ADQ)

#include <gtest/gtest.h>

#include <iostream>
TEST(t2, t2) {
    std::string s("bbbbb");
    Solution sss;
    int ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(1, ret);
}
TEST(t1, t2) {
    std::string s("abcabcbb");
    Solution sss;
    int ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(3, ret);
}
TEST(t1, t2ss) {
    std::string s("");
    Solution sss;
    int ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(0, ret);
}
TEST(t1sss, t2ss) {
    std::string s("pwwkew");
    Solution sss;
    int ret = sss.LengthOfLongestSubstring(s);
    EXPECT_EQ(3, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
