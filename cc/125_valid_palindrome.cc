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
    bool IsPalindrome(string s) {
        s = RemoveAllUNreleated(s);
        return IsPalindrome(s, 0, s.size() - 1);
        return false;
    }

    string RemoveAllUNreleated(std::string& ss) {
        std::string ret;
        for (char s : ss) {
            if ('A' <= s && s <= 'Z') {
                ret += s - 'A' + 'a';
            } else if ('a' <= s && s <= 'z') {
                ret += s;
            } else if ('0' <= s && s <= '9') {
                ret += s;
            }
        }
        return ret;
    }

    bool IsPalindrome(string& s, int i, int j) {
        while (i < j) {
            if (s[i] == s[j]) {
                i++;
                j--;
            } else {
                return false;
            }
        }
        return true;
    }
};

TEST(valid_palindrome, t1) {
    string const s = "A man, a plan, a canal: Panama";
    bool const output = true;
    // Explanation: "amanaplanacanalpanama" is a palindrome.

    Solution sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
TEST(valid_palindrome, t2) {
    string const s = "race a car";
    bool const output = false;
    //  "raceacar" is not a palindrome.

    Solution sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}

TEST(valid_palindrome, t3) {
    string const s = " ";
    bool const output = true;
    // Explanation: s is an empty string "" after removing non-alphanumeric
    // characters. Since an empty string reads the same forward and backward, it
    // is a palindrome. bool output = false;
    //  Explanation: "amanaplanacanalpanama" is a palindrome.

    Solution sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}

TEST(valid_palindrome, t4) {
    string const s = "0P";
    bool const output = false;

    Solution sl;
    bool const ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
}  // namespace
