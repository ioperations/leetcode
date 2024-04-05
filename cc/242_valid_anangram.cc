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

#include "gtest/gtest.h"

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
