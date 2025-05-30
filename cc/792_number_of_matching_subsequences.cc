// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s and an array of strings words, return the number of words[i]
that is a subsequence of s.

A subsequence of a string is a new string generated from the original string
with some characters (can be none) deleted without changing the relative order
of the remaining characters.

For example, "ace" is a subsequence of "abcde".
*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
    unordered_map<string, bool> m_cache;

   public:
    bool IsSubsequence(const string& s1, const string& s2) {
        if (m_cache.count(s1)) return m_cache[s1];
        int n = s1.length(), m = s2.length();
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (s1[i] == s2[j]) i++;
            j++;
        }
        /*If i reaches end of s1,that mean we found all
        characters of s1 in s2,
        so s1 is subsequence of s2, else not*/
        return m_cache[s1] = i == n;
    }
    int NumMatchingSubseqV1(string s, vector<string>& words) {
        // pass
        int sum = 0;
        for (auto& ptr : words) {
            sum += (IsSubsequence(ptr, s) ? 1 : 0);
        }
        return sum;
    }

    int NumMatchingSubseq(string s, vector<string>& words) {
        unordered_map<char, vector<int>>
            ump;  // unordered_map with character as key and its index position
                  // vector generated from string s
        int count = 0;

        int i = 0;
        for (auto c : s) {  // pushing char and its index into unordered_map
            ump[c].push_back(i);
            i++;
        }

        for (auto word : words) {  // for each word
            int prev_index = -1;   // initialize upper_bound to -1
            count++;  // first we will consider it as valid subsequence, then we
                      // prove it is correct or not. If it is not, then don't
                      // worry, we are going to decrement the count later
            for (auto c : word) {  // for each character in the word
                auto it = upper_bound(
                    ump[c].begin(), ump[c].end(),
                    prev_index);  // take upper_bound of prevIndex, this is the
                                  // most important line as we gradually
                                  // traverse through the whole word, it is
                                  // going to stay in increasing order if it is
                                  // valid subsequence
                if (it ==
                    ump[c].end()) {  // if any character is not there in the map
                    count--;         // then reject that word
                    break;           // and move to next word
                }
                prev_index = *it;  // now we got the new upper_bound
            }
        }

        return count;
    }
};

TEST(number_of_matching_subsequences, t1) {
    string const s = "abcde";
    vector<string> words = {"a", "bb", "acd", "ace"};
    int const output = 3;
    // Explanation: There are three strings in words that are a subsequence
    // of s: "a", "acd", "ace".
    Solution sl;
    int const ret = sl.NumMatchingSubseq(s, words);
    EXPECT_EQ(ret, output);
}

TEST(number_of_matching_subsequences, t2) {
    string const s = "dsahjpjauf";
    vector<string> words = {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"};
    int const output = 2;
    Solution sl;
    int const ret = sl.NumMatchingSubseq(s, words);
    EXPECT_EQ(ret, output);
}

}  // namespace
