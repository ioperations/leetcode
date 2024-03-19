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

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    string BreakPalindrome(string palindrome) {
        string &ret = palindrome;
        int const original_size = palindrome.size();
        int const size = palindrome.size() / 2;
        for (int i = 0; i < size; i++) {
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

TEST(brak_a_palindrome, t1) {
    string const palindrome = "abccba";
    string const output = "aaccba";
    // Explanation: There are many ways to make "abccba" not a palindrome, such
    // as "zbccba", "aaccba", and "abacba". Of all the ways, "aaccba" is the
    // lexicographically smallest.
    Solution sl;
    auto const ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(ret, output);
}

TEST(brak_a_palindrome, t2) {
    string const palindrome = "a";
    string const output = "";
    // There is no way to replace a single character to make "a" not a
    // palindrome, so return an empty string.
    Solution sl;
    auto const ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(ret, output);
}

TEST(brak_a_palindrome, t3) {
    string const palindrome = "aa";
    string const output = "ab";
    // There is no way to replace a single character to make "a" not a
    // palindrome, so return an empty string.
    Solution sl;
    auto const ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(ret, output);
}
}  // namespace
