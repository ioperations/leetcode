// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string containing digits from 2-9 inclusive, return all possible letter
combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given
below. Note that 1 does not map to any letters.

*/

#include <set>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    void Solve(vector<vector<char> > &v, vector<string> &ans, string digits,
               int pos, string s) {
        if (pos == (int)digits.size()) {
            if (s != "") ans.push_back(s);
            return;
        }
        int temp = digits[pos] - '0';
        for (int i = 0; i < (int)v[temp].size(); i++) {
            s.push_back(v[temp][i]);
            Solve(v, ans, digits, pos + 1, s);
            s.pop_back();
        }
    }
    // clang-format off
    vector<string> LetterCombinations(string digits) {
        string s;
        // clang-format off
        vector<vector<char> > v{{}, {}, {'a', 'b', 'c'}, {'d', 'e', 'f'},
                                {'g', 'h', 'i'}, {'j', 'k', 'l'},
                                {'m', 'n', 'o'}, {'p', 'q', 'r', 's'},
                                {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'}
                                };
        // clang-format on
        vector<string> ans;
        Solve(v, ans, digits, 0, "");
        return ans;
    }
    // clang-format on
};



TEST(t0, t1) {
    vector<string> expected = {"ad", "ae", "af", "bd", "be",
                               "bf", "cd", "ce", "cf"};

    string digits = "23";

    set<string> expected_set(expected.begin(), expected.end());

    Solution sl;
    auto ret = sl.LetterCombinations(digits);
    set<string> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, expected_set);
}

TEST(t0, t2) {
    vector<string> expected = {};

    string digits = "";

    set<string> expected_set(expected.begin(), expected.end());

    Solution sl;
    auto ret = sl.LetterCombinations(digits);
    set<string> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, expected_set);
}

TEST(t0, t3) {
    vector<string> expected = {"a", "b", "c"};

    string digits = "2";

    set<string> expected_set(expected.begin(), expected.end());

    Solution sl;
    auto ret = sl.LetterCombinations(digits);
    set<string> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, expected_set);
}

}
