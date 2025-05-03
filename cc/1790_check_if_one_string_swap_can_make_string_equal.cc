/*
 * You are given two strings s1 and s2 of equal length. A string swap is
    an operation where you choose two indices in a string (not
   necessarily different) and swap the characters at these indices.

   Return true if it is possible to make both strings equal by
   performing at most one string swap on exactly one of the strings.
   Otherwise, return false.
 */

#include <cstddef>
#include <string>

using namespace std;

class Solution {
   public:
    bool AreAlmostEqual(string s1, string s2) {
        /*
         * 1 <= s1.length, s2.length <= 100
         * s1.length == s2.length
         * s1 and s2 consist of only lowercase English letters.
         */
        auto size = s1.length();

        for (size_t i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                Change(s1, i, j);
                if (s1 == s2) {
                    return true;
                }
                Change(s1, i, j);
            }
        }
        return false;
    }

    void Change(std::string& s, size_t i, size_t j) {
        char const tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
};

class SolutionV2 {
   public:
    bool AreAlmostEqual(string s1, string s2) {
        /*
         * Initialize Variables:
         Use variables i and j to store the indices of characters that differ
         between the two strings. Initialize them to -1. Use a counter cnt to
         count the number of differing positions.

         Iterate Through the Strings:
         Traverse each character of the strings using a loop. If characters at
         the current position differ, increment the counter cnt. Store the index
         of the differing characters in i and j when cnt is 1 and 2
         respectively.

         Check Conditions: If cnt is 0, the strings are already equal, so return
         true. If cnt is 2, check if swapping the characters at positions i and
         j in one string makes it equal to the other string. If both conditions
         are met, return true; otherwise, return false.

         Complexity Time complexity:
         O(n) Space complexity: O(1)
        */
        int i = -1, j = -1;
        int cnt = 0;

        for (int k = 0; k < s1.length(); k++) {
            if (s1[k] != s2[k]) {
                cnt++;
                if (i == -1) {
                    i = k;
                } else if (j == -1) {
                    j = k;
                }
            }
        }

        if (cnt == 0) {
            return true;
        }
        if (cnt == 2 && s1[i] == s2[j] && s1[j] == s2[i]) {
            return true;
        }

        return false;
    }
};
#include <gtest/gtest.h>

TEST(t0, t1) {
    string s1 = "bank", s2 = "kanb";
    bool const output = true;
    // Explanation : For example, swap the first character with the last
    // character of s2 to make "bank"
    Solution sl;
    auto ret = sl.AreAlmostEqual(s1, s2);
    EXPECT_EQ(ret, output);
    SolutionV2 sl2;
    ret = sl2.AreAlmostEqual(s1, s2);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s1 = "attack", s2 = "defend";
    auto output = false;
    // Explanation : It is impossible to make them equal with one string swap
    Solution sl;
    auto ret = sl.AreAlmostEqual(s1, s2);
    EXPECT_EQ(ret, output);
    SolutionV2 sl2;
    ret = sl2.AreAlmostEqual(s1, s2);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string s1 = "kelb", s2 = "kelb";
    bool const output = true;
    // Explanation: The two strings are already equal, so no string swap
    // operation is required.
    Solution sl;
    auto ret = sl.AreAlmostEqual(s1, s2);
    EXPECT_EQ(ret, output);
    SolutionV2 sl2;
    ret = sl2.AreAlmostEqual(s1, s2);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
