// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a palindromic string of lowercase English letters palindrome, replace
exactly one character with any lowercase English letter so that the resulting
string is not a palindrome and that it is the lexicographically smallest one
possible.

Return the resulting string. If there is no way to replace a character to make
it not a palindrome, return an empty string.

A string a is lexicographically smaller than a string b (of the same length) if
in the first position where a and b differ, a has a character strictly smaller
than the corresponding character in b. For example, "abcc" is lexicographically
smaller than "abcd" because the first position they differ is at the fourth
character, and 'c' is smaller than 'd'.

*/

#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    string BreakPalindrome(string& palindrome) {
        string& ret = palindrome;
        int const original_size = static_cast<int>(palindrome.size());
        int const size = original_size / 2;
        for (size_t i = 0; i < size; i++) {
            if (ret[i] != 'a') {
                ret[i] = 'a';
                return ret;
            }
        }
        if (original_size > 1) {
            for (int i = 0; i < size; i++) {
                if (ret[i] == 'a') {
                    ret[original_size - (i + 1)] = 'b';
                    return ret;
                }
            }
        }
        return "";
    }
};

TEST(BrakAPalindrome, t1) {
    string palindrome = "abccba";
    string const output = "aaccba";
    // Explanation: There are many ways to make "abccba" not a palindrome, such
    // as "zbccba", "aaccba", and "abacba". Of all the ways, "aaccba" is the
    // lexicographically smallest.
    Solution sl;
    const auto& ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(output, ret);
}

TEST(BrakAPalindrome, t2) {
    string palindrome = "a";
    string const output = "";
    // There is no way to replace a single character to make "a" not a
    // palindrome, so return an empty string.
    Solution sl;
    const auto& ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(output, ret);
}

TEST(BrakAPalindrome, t3) {
    string palindrome = "aa";
    string const output = "ab";
    // There is no way to replace a single character to make "a" not a
    // palindrome, so return an empty string.
    Solution sl;
    const auto& ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(output, ret);
}
}  // namespace
