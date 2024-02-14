// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an array of words where each word consists of lowercase English
letters.

wordA is a predecessor of wordB if and only if we can insert exactly one letter
anywhere in wordA without changing the order of the other characters to make it
equal to wordB.

For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor
of "bcad". A word chain is a sequence of words [word1, word2, ..., wordk] with k
>= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3,
and so on. A single word is trivially a word chain with k == 1.

Return the length of the longest possible word chain with words chosen from the
given list of words.*/

#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    bool Check(const string &a, const string &b) {
        int cnt = 0, idx = 0;
        for (int i = 0; i < (int)a.size() && idx < (int)b.size(); i++, idx++) {
            if (a[i] != b[idx]) {
                cnt++;
                i--;
            }
            if (cnt > 1) {
                return false;
            }
        }
        return cnt <= 1;
    }
    int LongestStrChain(vector<string> &words) {
        int ans = 1;
        vector<int> dp(words.size(), 1);
        sort(words.begin(), words.end(),
             [](const string &s1, const string &s2) {
                 return s1.length() < s2.length();
             });
        for (int i = 0; i < (int)words.size(); i++) {
            for (int j = i - 1;
                 j >= 0 && words[j].size() + 1 >= words[i].size(); j--) {
                if (words[j].size() == words[i].size() - 1) {
                    if (Check(words[j], words[i])) {
                        dp[i] = max(dp[j] + 1, dp[i]);
                    }
                }
            }
        }

        ans = *max_element(dp.begin(), dp.end());
        return ans;
    }
};


TEST(t0, t1) {
    vector<string> words = {"a", "b", "ba", "bca", "bda", "bdca"};
    int output = 4;
    // Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
    Solution sl;
    int ret = sl.LongestStrChain(words);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<string> words = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
    int output = 5;
    // All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc",
    // "pcxbcf"].
    Solution sl;
    int ret = sl.LongestStrChain(words);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<string> words = {"abcd", "dbqca"};
    int output = 1;
    // The trivial word chain ["abcd"] is one of the longest word chains.
    // ["abcd","dbqca"] is not a valid word chain because the ordering of the
    // letters is changed.
    Solution sl;
    int ret = sl.LongestStrChain(words);
    EXPECT_EQ(ret, output);
}
}
