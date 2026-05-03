// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two strings s and t of lengths m and n respectively, return the minimum
window substring of s such that every character in t (including duplicates) is
included in the window. If there is no such substring, return the empty string
"".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

*/

#include <climits>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    string MinWindow(string s, string t) {
        // This result variable will store the string which we will return
        string result;

        // It will check if any of the two string is empty and return empty
        // string result
        if (s.empty() || t.empty()) {
            return result;
        }

        // These 2 unorders maps will store frequency of characters in t string
        // and windows
        unordered_map<char, int> map;
        unordered_map<char, int> window;

        // It will update the frequency of each charater of string t int map;
        for (int i = 0; i < static_cast<int>(t.length()); i++) {
            map[t.at(i)]++;
        }

        // variable to store minimum length of result string
        int min_length = INT_MAX;

        // counter
        int letter_counter = 0;

        for (int slow = 0, fast = 0; fast < static_cast<int>(s.length()); fast++) {
            char const c = s.at(fast);

            if (map.find(c) != map.end()) {
                window[c]++;
                if (window.at(c) <= map.at(c)) {
                    letter_counter++;
                }
            }

            if (letter_counter >= static_cast<int>(t.length())) {
                while (map.find(s.at(slow)) == map.end() ||
                       window.at(s.at(slow)) > map.at(s.at(slow))) {
                    window[s.at(slow)]--;

                    slow++;
                }

                if (fast - slow + 1 < min_length) {
                    min_length = fast - slow + 1;
                    result = s.substr(slow, min_length);
                }
            }
        }
        return result;
    }
};

TEST(MinimiumWindowSubstring, t1) {
    string const s = "ADOBECODEBANC";
    string const t = "ABC";
    string const output = "BANC";

    // Explanation: The minimum window substring "BANC" includes 'A', 'B', and
    // 'C' from string t.
    Solution sl;
    auto ret = sl.MinWindow(s, t);
    EXPECT_EQ(ret, output);
}

TEST(MinimiumWindowSubstring, t2) {
    string const s = "a";
    string const t = "a";
    string const output = "a";

    // The entire string s is the minimum window.
    // 'C' from string t.
    Solution sl;
    auto ret = sl.MinWindow(s, t);
    EXPECT_EQ(ret, output);
}

TEST(MinimiumWindowSubstring, t3) {
    string const s = "a";
    string const t = "aa";
    string const output = "";

    // Both 'a's from t must be included in the window.
    // Since the largest window of s only has one 'a', return empty string.

    Solution sl;
    auto ret = sl.MinWindow(s, t);
    EXPECT_EQ(ret, output);
}
}  // namespace
