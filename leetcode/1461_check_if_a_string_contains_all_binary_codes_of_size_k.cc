// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given a binary string s and an integer k, return true if every binary code of
length k is a substring of s. Otherwise, return false.


*/

#include <cmath>
#include <string>

using namespace std;

#include <unordered_set>

class Solution {
   public:
    bool HasAllCodes(string s, int k) {
        // 1 <= s.length <= 5 * 105
        // s[i] is either '0' or '1'.
        // 1 <= k <= 20

        if ((int)s.size() < k) return false;
        unordered_set<string> st;
        for (int i = 0; i <= (int)s.size() - k; i++) st.insert(s.substr(i, k));
        return st.size() == pow(2, k);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string s = "00110110";
    int k = 2;
    bool output = true;

    Solution sl;
    bool ret = sl.HasAllCodes(s, k);
    // The binary codes of length 2 are "00", "01", "10" and "11". They can be
    // all found as substrings at indices 0, 1, 3 and 2 respectively.
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = "0110";
    int k = 1;
    bool output = true;
    // The binary codes of length 1 are "0" and "1", it is clear that both exist
    // as a substring.
    Solution sl;
    bool ret = sl.HasAllCodes(s, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string s = "0110";
    int k = 2;
    bool output = false;

    //  The binary code "00" is of length 2 and does not exist in the array.
    Solution sl;
    bool ret = sl.HasAllCodes(s, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
