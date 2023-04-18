#include <iostream>
#include <iterator>
#include <set>
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

#if defined(TEST_ADQ)
#include <gtest/gtest.h>

#include <iostream>

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
    Solution slu ;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 0);
}
TEST(r2, t2) {
    std::string in("aab");
    Solution slu ;
    int ret = slu.LengthOfLongestSubstring(in);
    EXPECT_EQ(ret, 2);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
#endif
