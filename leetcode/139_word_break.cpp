/*
Given a string s and a dictionary of strings wordDict, return true if s can be
segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the
segmentation.
*/

#include <string>
#include <vector>
using namespace std;
#include <unordered_set>

class Solution {
   public:
    bool WordBreak(string& s, int n, int i, unordered_set<string>& words,
                   vector<int>& dp) {
        if (i == n) return 1;

        int j = i;
        if (dp[j] == -1) {
            string t = "";
            for (; i < n; i++) {
                t += s[i];
                if (words.find(t) != words.end()) {
                    if (WordBreak(s, n, i + 1, words, dp)) {
                        dp[j] = 1;
                        return 1;
                    }
                }
            }
            dp[j] = 0;
        }

        return dp[j] == 1;
    }

    bool WordBreak(string s, vector<string>& word_dict) {
        unordered_set<string> words(word_dict.begin(), word_dict.end());

        int n = s.length();
        vector<int> dp(n + 1, -1);

        return WordBreak(s, n, 0, words, dp);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string s = "leetcode";
    vector<string> word_dict = {"leet", "code"};
    bool expected = true;
    // Explanation: Return true because "leetcode"
    // can be segmented as "leet code".

    Solution sl;
    bool ret = sl.WordBreak(s, word_dict);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    string s = "applepenapple";
    vector<string> word_dict = {"apple", "pen"};
    bool expected = true;

    /*
        Return true because "applepenapple" can be segmented as
        "apple pen apple".Note that you are
        allowed to reuse a dictionary word.
    */

    Solution sl;
    bool ret = sl.WordBreak(s, word_dict);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t3) {
    string s = "catsandog";
    vector<string> word_dict = {"cats", "dog", "sand", "and", "cat"};
    bool expected = false;

    /*
        Return true because "applepenapple" can be segmented as
        "apple pen apple".Note that you are
        allowed to reuse a dictionary word.
    */

    Solution sl;
    bool ret = sl.WordBreak(s, word_dict);
    EXPECT_EQ(ret, expected);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

