// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s, check if it can be constructed by taking a substring of it
   and appending multiple copies of the substring together.

*/

#include <cstddef>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    [[nodiscard]]
    bool PrefixFunction(string const& p) {
#define ll long long
        ll const n = static_cast<ll>(p.length());
        vector<ll> prefix(static_cast<size_t>(n), 0);
        for (ll i = 1; i < n; i++) {
            ll j = prefix.at(static_cast<size_t>(i) - 1);
            while (j > 0 and p.at(static_cast<size_t>(i)) != p.at(static_cast<size_t>(j))) j = prefix.at(static_cast<size_t>(j) - 1);
            if (p.at(static_cast<size_t>(i)) == p.at(static_cast<size_t>(j))) j++;
            prefix.at(static_cast<size_t>(i)) = j;
        }
        if (prefix.at(static_cast<size_t>(n) - 1) == 0) return false;
        return prefix.at(static_cast<size_t>(n) - 1) % (n - prefix.at(static_cast<size_t>(n) - 1)) == 0;
    }
    [[nodiscard]]
    bool RepeatedSubstringPattern(string const& s) { return PrefixFunction(s); }
};

TEST(RepeatedSubstringPattern, t1) {
    string const s = "abab";
    bool const output = true;
    Solution sl;
    bool const ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "ab" twice.
    EXPECT_EQ(ret, output);
}

TEST(RepeatedSubstringPattern, t2) {
    string const s = "aba";
    bool const output = false;
    Solution sl;
    bool const ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "ab" twice.
    EXPECT_EQ(ret, output);
}

TEST(RepeatedSubstringPattern, t3) {
    string const s = "abcabcabcabc";
    bool const output = true;
    Solution sl;
    bool const ret = sl.RepeatedSubstringPattern(s);
    // It is the substring "abc" four times or the substring "abcabc" twice.
    EXPECT_EQ(ret, output);
}

}  // namespace
