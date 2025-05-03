// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s, check if it can be constructed by taking a substring of it
   and appending multiple copies of the substring together.

*/

#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool PrefixFunction(string p) {
#define ll long long
        ll const n = p.length();
        vector<ll> prefix(n, 0);
        for (ll i = 1; i < n; i++) {
            ll j = prefix[i - 1];
            while (j > 0 and p[i] != p[j]) j = prefix[j - 1];
            if (p[i] == p[j]) j++;
            prefix[i] = j;
        }
        if (prefix[n - 1] == 0) return false;
        return prefix[n - 1] % (n - prefix[n - 1]) == 0;
    }
    bool RepeatedSubstringPattern(string s) { return PrefixFunction(s); }
};

TEST(repeated_substring_pattern, t1) {
    string const s = "abab";
    bool const output = true;
    Solution sl;
    bool const ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "ab" twice.
    EXPECT_EQ(ret, output);
}

TEST(repeated_substring_pattern, t2) {
    string const s = "aba";
    bool const output = false;
    Solution sl;
    bool const ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "ab" twice.
    EXPECT_EQ(ret, output);
}

TEST(repeated_substring_pattern, t3) {
    string const s = "abcabcabcabc";
    bool const output = true;
    Solution sl;
    bool const ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "abc" four times or the substring "abcabc" twice.
    EXPECT_EQ(ret, output);
}

}  // namespace
