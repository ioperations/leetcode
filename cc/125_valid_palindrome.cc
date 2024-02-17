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

    string RemoveAllUNreleated(std::string &ss) {
        std::string ret;
        for (int i = 0; i < (int)ss.size(); i++) {
            if ('A' <= ss[i] && ss[i] <= 'Z') {
                ret += ss[i] - 'A' + 'a';
            } else if ('a' <= ss[i] && ss[i] <= 'z') {
                ret += ss[i];
            } else if ('0' <= ss[i] && ss[i] <= '9') {
                ret += ss[i];
            }
        }
        return ret;
    }

    bool IsPalindrome(string &s, int i, int j) {
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


TEST(t0, t1) {
    string s = "A man, a plan, a canal: Panama";
    bool output = true;
    // Explanation: "amanaplanacanalpanama" is a palindrome.

    Solution sl;
    bool ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
TEST(t0, t2) {
    string s = "race a car";
    bool output = false;
    //  "raceacar" is not a palindrome.

    Solution sl;
    bool ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string s = " ";
    bool output = true;
    // Explanation: s is an empty string "" after removing non-alphanumeric
    // characters. Since an empty string reads the same forward and backward, it
    // is a palindrome. bool output = false;
    //  Explanation: "amanaplanacanalpanama" is a palindrome.

    Solution sl;
    bool ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t4) {
    string s = "0P";
    bool output = false;

    Solution sl;
    bool ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
}
