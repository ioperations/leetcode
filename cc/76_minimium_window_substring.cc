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
        for (int i = 0; i < (int)t.length(); i++) {
            map[t[i]]++;
        }

        // variable to store minimum length of result string
        int min_length = INT_MAX;

        // counter
        int letter_counter = 0;

        for (int slow = 0, fast = 0; fast < (int)s.length(); fast++) {
            // This c variable will store each character of string s according
            // to the fast pointer movement starting from 0
            char const c = s[fast];

            // If current character of "s" is available in map that consists of
            // string "t" characters
            if (map.find(c) != map.end()) {
                // store that character in current window and increase the
                // counter by 1
                window[c]++;
                // This if condition will execute only if there is need to
                // fulfill required charters from map to window and increase the
                // letter counter
                if (window[c] <= map[c]) {
                    letter_counter++;
                }
            }

            // This condition we have found the result in current window
            if (letter_counter >= (int)t.length()) {
                while (map.find(s[slow]) == map.end() ||
                       window[s[slow]] > map[s[slow]]) {
                    // This will start decreasing frequency of extra character
                    // in window
                    window[s[slow]]--;

                    // and move slow pointer
                    slow++;
                }

                // It will update the minimum required substring
                if (fast - slow + 1 < min_length) {
                    min_length = fast - slow + 1;
                    // It will update the result string
                    result = s.substr(slow, min_length);
                }
            }
        }
        return result;
    }
};

TEST(minimium_window_substring, t1) {
    string const s = "ADOBECODEBANC";
    string const t = "ABC";
    string const output = "BANC";

    // Explanation: The minimum window substring "BANC" includes 'A', 'B', and
    // 'C' from string t.
    Solution sl;
    auto ret = sl.MinWindow(s, t);
    EXPECT_EQ(ret, output);
}

TEST(minimium_window_substring, t2) {
    string const s = "a";
    string const t = "a";
    string const output = "a";

    // The entire string s is the minimum window.
    // 'C' from string t.
    Solution sl;
    auto ret = sl.MinWindow(s, t);
    EXPECT_EQ(ret, output);
}

TEST(minimium_window_substring, t3) {
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
