// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s, check if it can be constructed by taking a substring of it
   and appending multiple copies of the substring together.

*/

#include <string>
#include <vector>

using namespace std;

namespace { 
class Solution {
   public:
    bool PrefixFunction(string p) {
#define ll long long
        ll n = p.length();
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
} 
#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    string s = "abab";
    bool output = true;
    Solution sl;
    bool ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "ab" twice.
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = "aba";
    bool output = false;
    Solution sl;
    bool ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "ab" twice.
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string s = "abcabcabcabc";
    bool output = true;
    Solution sl;
    bool ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "abc" four times or the substring "abcabc" twice.
    EXPECT_EQ(ret, output);
}

}
