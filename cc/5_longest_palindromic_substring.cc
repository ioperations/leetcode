// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**
 * @brief 最长回文子串
 */

#include <string>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    std::string LongestPalindrome(const std::string& s) {
        /**
         *  中心扩展算法
         */

        if (s.length() < 2) {
            return s;
        }

        std::string res = "";
        for (size_t i = 0; i < s.length() - 1; i++) {
            std::string s1 = Palindrome(s, i, i);
            std::string s2 = Palindrome(s, i, i + 1);
            res = res.length() > s1.length() ? res : s1;
            res = res.length() > s2.length() ? res : s2;
        }
        return res;
    }

   private:
    std::string Palindrome(const std::string &s, int l, size_t r) {
        while (l >= 0 && r < s.length() && s[l] == s[r]) {
            l--;
            r++;
        }

        return s.substr(l + 1, r - (l + 1));
    }
};

TEST(longest_palindromic_substring, t1) {
    std::string s("babad");
    Solution sl;

    auto ret = sl.LongestPalindrome(s);

    EXPECT_TRUE(ret == "bab" || ret == "aba");
}

TEST(longest_palindromic_substring, t2) {
    std::string s("cbbd");
    Solution sl;

    auto ret = sl.LongestPalindrome(s);
    EXPECT_EQ(ret, "bb");
}
TEST(longest_palindromic_substring, t3) {
    std::string s("ac");
    Solution sl;

    auto ret = sl.LongestPalindrome(s);
    EXPECT_TRUE(ret == "a" || ret == "c");
}

}  // namespace
