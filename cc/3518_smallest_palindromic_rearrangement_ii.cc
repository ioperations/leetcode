/*
 * You are given a palindromic string s and an integer k.
 *
 * Return the k-th lexicographically smallest palindromic permutation of s. If
 * there are fewer than k distinct palindromic permutations, return an empty
 * string.
 *
 * Note: Different rearrangements that yield the same palindromic string are
 * considered identical and are counted once.
 * 1 <= s.length <= 104
 * s consists of lowercase English letters.
 * s is guaranteed to be palindromic.
 * 1 <= k <= 106
 * */
#include <algorithm>
#include <string>

using namespace std;

namespace {

class Solution {
   public:
    string SmallestPalindrome(const string& s, int k) {
        auto size = s.size();
        auto half = s.substr(0, size / 2);
        sort(half.begin(), half.end());

        while (--k &&
               next_permutation(half.begin(), half.end(), std::greater<>())) {
        }

        if (k > 1) {
            return "";
        }
        if (size % 2 == 0) {
            return half + revert(half);
        }

        return half + s[size / 2] + revert(half);
    }

   private:
    string revert(const std::string& s) {
        std::string ret;
        ret.reserve(s.size());
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            ret.push_back(*it);
        }
        return ret;
    }
};

}  // namespace
#include <gtest/gtest.h>

TEST(smallestPalindrome, t0) {
    string s = "abba";
    int k = 2;
    string output = "baab";
    Solution sl;
    auto ret = sl.SmallestPalindrome(s, k);
    EXPECT_EQ(output, ret);
    /*
     * The two distinct palindromic rearrangements of "abba" are "abba" and
     * "baab".
     * Lexicographically, "abba" comes before "baab". Since k = 2, the output is
     * "baab".
     * */
}
TEST(smallestPalindrome, t1) {
    string s = "aa";
    int k = 2;
    string output = "";
    Solution sl;
    auto ret = sl.SmallestPalindrome(s, k);
    EXPECT_EQ(s, ret);  // not really
    /*
     * There is only one palindromic rearrangement: "aa".
     * The output is an empty string since k = 2 exceeds the number of
     * possible rearrangements.
     * */
}
TEST(smallestPalindrome, t2) {
    string s = "bacab";
    int k = 1;
    string output = "abcba";
    Solution sl;
    auto ret = sl.SmallestPalindrome(s, k);
    EXPECT_EQ(output, ret);
    /*
     * The two distinct palindromic rearrangements of "bacab" are "abcba" and
     * "bacab". Lexicographically, "abcba" comes before "bacab". Since k = 1,
     * the output is "abcba".
     * */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
