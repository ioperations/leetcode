// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A phrase is a palindrome if, after converting all uppercase letters into
lowercase letters and removing all non-alphanumeric characters, it reads the
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.*/

#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    [[nodiscard]] bool IsPalindrome(string s) const {
        s = RemoveAllUNreleated(s);
        return IsPalindrome(s, 0, static_cast<int>(s.size()) - 1);
        return false;
    }

    [[nodiscard]] string RemoveAllUNreleated(std::string& ss) const {
        int const n = static_cast<int>(ss.size());
        std::string ret;
        ret.reserve(n);
        for (int i = 0; i < n; ++i) {
            char const ch = ss.at(i);
            if ('A' <= ch && ch <= 'Z') {
                ret += static_cast<char>(ch - 'A' + 'a');
            } else if ('a' <= ch && ch <= 'z') {
                ret += ch;
            } else if ('0' <= ch && ch <= '9') {
                ret += ch;
            }
        }
        return ret;
    }

    bool IsPalindrome(string& s, int i, int j) const {
        while (i < j) {
            if (s.at(i) == s.at(j)) {
                i++;
                j--;
            } else {
                return false;
            }
        }
        return true;
    }
};

TEST(validV, t1) {
    string const s = "A man, a plan, a canal: Panama";
    bool const output = true;
    // Explanation: "amanaplanacanalpanama" is a palindrome.

    Solution const sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
TEST(validV, t2) {
    string const s = "race a car";
    bool const output = false;
    //  "raceacar" is not a palindrome.

    Solution const sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}

TEST(validV, t3) {
    string const s = " ";
    bool const output = true;
    // Explanation: s is an empty string "" after removing non-alphanumeric
    // characters. Since an empty string reads the same forward and backward, it
    // is a palindrome. bool output = false;
    //  Explanation: "amanaplanacanalpanama" is a palindrome.

    Solution const sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}

TEST(validV, t4) {
    string const s = "0P";
    bool const output = false;

    Solution const sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
}  // namespace
