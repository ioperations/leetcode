// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer n, your task is to count how many strings of length n can be
formed under the following rules:

Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
Each vowel 'a' may only be followed by an 'e'.
Each vowel 'e' may only be followed by an 'a' or an 'i'.
Each vowel 'i' may not be followed by another 'i'.
Each vowel 'o' may only be followed by an 'i' or a 'u'.
Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int CountVowelPermutation(int n) {
        int const mod = 1e9 + 7;
        vector<vector<int>> dp(n, vector<int>(5, 0));
        int ans = 0;
        for (int i = 0; i < 5; i++) {
            dp.at(0).at(i) = 1;
        }
        for (int i = 1; i < n; i++) {
            dp.at(i).at(0) = (dp.at(i - 1).at(1)) % mod;
            dp.at(i).at(1) = (dp.at(i - 1).at(0) + dp.at(i - 1).at(2)) % mod;
            dp.at(i).at(2) =
                (dp.at(i - 1).at(0) + dp.at(i - 1).at(1) + dp.at(i - 1).at(3) + dp.at(i - 1).at(4)) %
                mod;
            dp.at(i).at(3) = (dp.at(i - 1).at(2) + dp.at(i - 1).at(4)) % mod;
            dp.at(i).at(4) = (dp.at(i - 1).at(0)) % mod;
        }
        for (auto num : dp.at(n - 1)) {
            ans = (ans + num) % mod;
        }
        return ans;
    }
};

TEST(CountVowelsPermutation, t1) {
    int const n = 1;
    int const output = 5;

    // Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
    Solution sl;
    int const ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}

TEST(CountVowelsPermutation, t2) {
    int const n = 2;
    int const output = 10;

    // All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi",
    // "ou" and "ua".
    Solution sl;
    int const ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}

TEST(CountVowelsPermutation, t3) {
    int const n = 5;
    int const output = 68;

    Solution sl;
    int const ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}
}  // namespace
