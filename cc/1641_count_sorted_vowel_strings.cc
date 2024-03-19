// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer n, return the number of strings of length n that consist only
of vowels (a, e, i, o, u) and are lexicographically sorted.

A string s is lexicographically sorted if for all valid i, s[i] is the same as
or comes before s[i+1] in the alphabet.
*/

/*
So you can think of this as follows suppose you wish to find the number of ways
of doing this problem for some n.

You can think of this as making "walls" between which you put one of the five
vowels. For example suppose n=5. Let O be a place where you put a letter and let
| be a wall. You can construct all your answers as follows:

O|O|O|O|O

this represents AEIOU

Or you can have:

OOO|||OO

this represents AAAUU

Or you can have:

OOO||O||O

this represents AAAOU

one more for example:

|||O|OOOO

this is OUUUU

Ok so this is the pattern. For a word of size n now you have n+4 placeholders
and we need to CHOOSE four on which to place walls.

This number from couning theory is n+4 CHOOSE 4

Explicitly n+4 CHOOSE 4 is (n+4)(n+3)(n+2)(n+1)/(4 * 3 * 2 * 1);

Effectively this is your answer. All you have to do is return this number.

The Code is Below: Thank You!!! =]
*/
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int Choose4(int n) {
        long int ret;
        ret = n * (n - 1) * (n - 2) * (n - 3);
        ret = ret / 24;

        return (ret);
    }

    int CountVowelStrings(int n) { return (Choose4(n + 4)); }

    int CountVowelStringsV2(int n) {
        vector<int> dp(5, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < 5; j++) {
                dp[j] = dp[j - 1] + dp[j];
            }
        }
        return dp[4];
    }
};

TEST(count_sorted_vowel_strings, t1) {
    const int n = 1;
    const int output = 5;
    // Explanation: The 5 sorted strings that consist of vowels only are
    // ["a","e","i","o","u"].

    Solution sl;
    int ret = sl.CountVowelStrings(n);
    EXPECT_EQ(ret, output);

    ret = sl.CountVowelStringsV2(n);
    EXPECT_EQ(ret, output);
}

TEST(count_sorted_vowel_strings, t2) {
    const int n = 2;
    const int output = 15;

    // Explanation: The 15 sorted strings that consist of vowels only are
    // ["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
    // Note that "ea" is not a valid string since 'e' comes after 'a' in the
    // alphabet.

    Solution sl;
    int ret = sl.CountVowelStrings(n);
    EXPECT_EQ(ret, output);

    ret = sl.CountVowelStringsV2(n);
    EXPECT_EQ(ret, output);
}

TEST(count_sorted_vowel_strings, t3) {
    const int n = 33;
    const int output = 66045;

    Solution sl;
    int ret = sl.CountVowelStrings(n);
    EXPECT_EQ(ret, output);

    ret = sl.CountVowelStringsV2(n);
    EXPECT_EQ(ret, output);
}

}  // namespace
