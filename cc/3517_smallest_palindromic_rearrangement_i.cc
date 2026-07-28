/*
 * You are given a palindromic string s.
 * Return the lexicographically smallest palindromic permutation of s.
 * 1 <= s.length <= 105
 * s consists of lowercase English letters.
 * s is guaranteed to be palindromic.k
 * */
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

namespace {
class Solution {
   public:
    string SmallestPalindrome(const string& s) {
        auto size = s.size();
        auto half = size / 2;
        string p = s.substr(0, half);
        sort(p.begin(), p.end());
        auto q = p;
        sort(q.begin(), q.end(), std::greater<>());

        if (size % 2 == 0) {
            return p + q;
        }
        return p + s[size / 2] + q;
    }
};
}  // namespace
#include <gtest/gtest.h>

TEST(smallestPalindrome, t0) {
    string s = "z";
    Solution sl;
    string output = "z";
    auto ret = sl.SmallestPalindrome(s);
    EXPECT_EQ(output, ret);
    /*
     * A string of only one character is already the lexicographically
     * smallest palindrome.
     */
}

TEST(smallestPalindrome, t1) {
    string s = "babab";
    Solution sl;
    string output = "abbba";
    auto ret = sl.SmallestPalindrome(s);
    EXPECT_EQ(output, ret);
    /*
     * Rearranging "babab" → "abbba" gives the smallest lexicographic
     * palindrome. smallest palindrome.
     */
}

TEST(smallestPalindrome, t2) {
    string s = "daccad";
    Solution sl;
    string output = "acddca";
    auto ret = sl.SmallestPalindrome(s);
    EXPECT_EQ(output, ret);
    /*
     * Rearranging "daccad" → "acddca" gives the smallest
     * lexicographic palindrome.
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
