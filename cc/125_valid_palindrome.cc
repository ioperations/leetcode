// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A phrase is a palindrome if, after converting all uppercase letters into
lowercase letters and removing all non-alphanumeric characters, it reads the
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.*/

#include <string>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

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

TEST(valid_palindrome, t1) {
    string s = "A man, a plan, a canal: Panama";
    bool output = true;
    // Explanation: "amanaplanacanalpanama" is a palindrome.

    Solution sl;
    bool ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
TEST(valid_palindrome, t2) {
    string s = "race a car";
    bool output = false;
    //  "raceacar" is not a palindrome.

    Solution sl;
    bool ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}

TEST(valid_palindrome, t3) {
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

TEST(valid_palindrome, t4) {
    string s = "0P";
    bool output = false;

    Solution sl;
    bool ret = sl.IsPalindrome(s);
    EXPECT_EQ(ret, output);
}
}  // namespace
