/*
 * Given two strings str1 and str2, return the shortest string that has both
 * str1 and str2 as subsequences. If there are multiple valid strings, return
 * any of them.
 *
 * A string s is a subsequence of string t if deleting some number of characters
 * from t (possibly 0) results in the string s.
 */

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    string ShortestCommonSupersequence(string str1, string str2) {
        /*
         * 1 <= str1.length, str2.length <= 1000
         * str1 and str2 consist of lowercase English letters.
         */

        size_t const m = str1.length();
        size_t const n = str2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Fill the dp table
        for (int i = 1; i <= static_cast<int>(m); i++) {
            for (int j = 1; j <= static_cast<int>(n); j++) {
                if (str1.at(i - 1) == str2.at(j - 1)) {
                    dp.at(i).at(j) = 1 + dp.at(i - 1).at(j - 1);
                } else {
                    dp.at(i).at(j) = max(dp.at(i - 1).at(j), dp.at(i).at(j - 1));
                }
            }
        }

        // Step 2: Construct the shortest common supersequence
        // Start from the bottom right of the dp table
        std::size_t i = m, j = n;
        string result = "";

        while (i > 0 && j > 0) {
            if (str1.at(i - 1) == str2.at(j - 1)) {
                // If the characters are the same, add it once
                result.push_back(str1.at(i - 1));
                i--;
                j--;
            } else if (dp.at(i - 1).at(j) > dp.at(i).at(j - 1)) {
                // If coming from top has higher value, take character from str1
                result.push_back(str1.at(i - 1));
                i--;
            } else {
                // Otherwise, take character from str2
                result.push_back(str2.at(j - 1));
                j--;
            }
        }

        // Add remaining characters from str1 (if any)
        while (i > 0) {
            result.push_back(str1.at(i - 1));
            i--;
        }

        // Add remaining characters from str2 (if any)
        while (j > 0) {
            result.push_back(str2.at(j - 1));
            j--;
        }

        // Reverse the result to get the final supersequence
        reverse(result.begin(), result.end());

        return result;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(T0, t1) {
    string const str1 = "abac";
    string const str2 = "cab";
    string const output = "cabac";
    /*
        str1 = "abac" is a subsequence of "cabac" because we can delete the
    first "c". str2 = "cab" is a subsequence of "cabac" because we can delete
    the last "ac". The answer provided is the shortest such string that
    satisfies these properties.
        */

    Solution sl;
    auto ret = sl.ShortestCommonSupersequence(str1, str2);
    EXPECT_EQ(ret, output);
}

TEST(T0, t2) {
    string const str1 = "aaaaaaaa";
    string const& str2 = str1;
    string const& output = str1;
    /*
        str1 = "abac" is a subsequence of "cabac" because we can delete the
    first "c". str2 = "cab" is a subsequence of "cabac" because we can delete
    the last "ac". The answer provided is the shortest such string that
    satisfies these properties.
        */

    Solution sl;
    auto ret = sl.ShortestCommonSupersequence(str1, str2);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
