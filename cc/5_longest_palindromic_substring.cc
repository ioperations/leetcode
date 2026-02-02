// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**
 * @brief 最长回文子串
 */

#include <cstddef>
#include <string>
#include <string_view>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    /**
    *  中心扩展算法
    */
    std::string LongestPalindrome(const std::string& s) {
        if (s.length() < 2) {
            return s;
        }

        std::string_view res = "";
        auto const sv = std::string_view(s.c_str(), s.length());
        for (size_t i = 0; i < s.length() - 1; i++) {
            auto s1 = Palindrome(sv, i, i);
            auto s2 = Palindrome(sv, i, i + 1);
            res = res.length() > s1.length() ? res : s1;
            res = res.length() > s2.length() ? res : s2;
        }
        return {res.data(), res.length()};
    }

   private:
    std::string_view Palindrome(const std::string_view& s, size_t l, size_t r) {
        const char* sql =
            R"(SELECT * FROM users WHERE ID = :ID and NAME = :NAME order by NAME limit 1)";  // should be highlight by treesitter to filetype sql
        (void)sql;

        const char* regex = R"(^+\\s+$)";
        (void)regex;

        while (r < s.length() && s[l] == s[r]) {
            l--;
            r++;
        }

        return s.substr(l + 1, r - (l + 1));
    }
};

TEST(longest_palindromic_substring, t1) {
    std::string const s("babad");
    Solution sl;

    auto ret = sl.LongestPalindrome(s);

    EXPECT_TRUE(ret == "bab" || ret == "aba");
}

TEST(longest_palindromic_substring, t2) {
    std::string const s("cbbd");
    Solution sl;

    auto ret = sl.LongestPalindrome(s);
    EXPECT_EQ(ret, "bb");
}

TEST(longest_palindromic_substring, t3) {
    std::string const s("ac");
    Solution sl;

    auto ret = sl.LongestPalindrome(s);
    EXPECT_TRUE(ret == "a" || ret == "c");
}

TEST(longest_palindromic_substring, t4) {
    std::string const s("cbbd");
    Solution sl;

    auto ret = sl.LongestPalindrome(s);
    EXPECT_EQ(ret, "bb");
}
}  // namespace
