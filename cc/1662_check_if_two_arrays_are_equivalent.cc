// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given two string arrays word1 and word2, return true if the two arrays represent
the same string, and false otherwise.

A string is represented by an array if the array elements concatenated in order
forms the string.

*/

#include <string>
#include <vector>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    bool ArrayStringsAreEqual(vector<string> &word1, vector<string> &word2) {
        int i = 0, j = 0;  // word pointers
        int m = 0, n = 0;  // char pointers

        while (i < (int)word1.size() and j < (int)word2.size()) {
            if (word1[i][m++] != word2[j][n++]) return false;

            if (m >= (int)word1[i].size()) i++, m = 0;

            if (n >= (int)word2[j].size()) j++, n = 0;
        }

        return i == (int)word1.size() and j == (int)word2.size();
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<string> word1 = {"ab", "c"}, word2 = {"a", "bc"};
    bool output = true;
    /*
    Explanation:
    word1 represents string "ab" + "c" -> "abc"
    word2 represents string "a" + "bc" -> "abc"
    The strings are the same, so return true.
    */
    Solution sl;
    bool ret = sl.ArrayStringsAreEqual(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<string> word1 = {"a", "cb"}, word2 = {"ab", "c"};
    bool output = false;
    Solution sl;
    bool ret = sl.ArrayStringsAreEqual(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<string> word1 = {"abc", "d", "defg"}, word2 = {"abcddefg"};
    bool output = true;
    Solution sl;
    bool ret = sl.ArrayStringsAreEqual(word1, word2);
    EXPECT_EQ(ret, output);
}

}
