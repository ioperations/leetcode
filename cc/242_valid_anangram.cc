// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given two strings s and t, return true if t is an anagram of s, and false
otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.

*/
#include <algorithm>
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
    bool IsAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

TEST(valid_anangram, t1) {
    string s = "anagram", t = "nagaram";
    bool output = true;
    Solution sl;
    bool ret = sl.IsAnagram(s, t);
    EXPECT_EQ(ret, output);
}

TEST(valid_anangram, t2) {
    string s = "rat", t = "car";
    bool output = false;
    Solution sl;
    bool ret = sl.IsAnagram(s, t);
    EXPECT_EQ(ret, output);
}

}  // namespace
