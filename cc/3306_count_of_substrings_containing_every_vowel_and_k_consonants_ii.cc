/*
 * You are given a string word and a non-negative integer k.
 *
 * Return the total number of substrings of word that contain every vowel ('a',
 * 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
 */

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class Solution {
   public:
    /*
     * 5 <= word.length <= 2 * 105
     * word consists only of lowercase English letters.
     * 0 <= k <= word.length - 5
     */
    int n;
    char vow[26] = {0};  //  vowels & consonants mapped to 0~5
    void set_type() {
        // Initialize all characters as consonants 5
        memset(vow, 5, sizeof(vow));
        vow[0] = 0, vow['e' - 'a'] = 1, vow['i' - 'a'] = 2, vow['o' - 'a'] = 3,
        vow['u' - 'a'] = 4;  // type for vowels
    }

    // Function computes the number at most k consonants
    inline long long lessEq(string& word, int k) {
        int lastPos[5] = {-1};  // last position of each vowel
        int freq[6] = {0};      // 0-4 for vowl 5 for consonants)
        long long ans = 0;      // count of valid substrings

        int cntVow = 0;  // count different vowels in the current window
        for (int l = 0, r = 0; r < n; r++) {
            int type = vow[word[r] - 'a'];  // Get the type

            if (type < 5) {
                lastPos[type] = r;  // last position of the vowel
                if (freq[type] == 0) cntVow++;
            }

            freq[type]++;  // Increase the freq

            // Shrink the window if the number of consonants exceeds k
            while (freq[5] > k) {  // freq[5] tracks consonants
                type = vow[word[l] - 'a'];
                freq[type]--;
                if (type < 5 && freq[type] == 0) cntVow--;
                l++;  // Move left pointer
            }
            int minPos = *min_element(lastPos, lastPos + 5);
            //    cout << freq[5] << endl;
            // count the number of valid substrings
            if (cntVow == 5)
                ans += (minPos - l + 1);  // valid substrings ending at r
        }
        return ans;
    }

    // Main function to count the substrings based on the given k value
    long long countOfSubstrings(string& word, int k) {
        set_type();

        n = word.size();  // Store the length of the word

        // Return the number of substrings with at most k consonants minus
        // those with at most k-1 consonants
        return k == 0 ? lessEq(word, 0) : lessEq(word, k) - lessEq(word, k - 1);
    }
};

auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();

#include <gtest/gtest.h>

TEST(t0, t1) {
    string word = "aeioqq";
    int k = 1;
    int output = 0;
    Solution sl;
    int ret = sl.countOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string word = "aeiou";
    int k = 0;
    int output = 1;
    Solution sl;
    int ret = sl.countOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
    // The only substring with every vowel and zero consonants is
    // word[0..4], which is "aeiou".
}

TEST(t0, t3) {
    string word = "ieaouqqieaouqq";
    int k = 1;
    int output = 3;
    // Explanation :
    //
    // The substrings with every vowel and one consonant are :
    //
    // word[0..5],
    // which is "ieaouq".word[6..11],
    // which is "qieaou".word[7..12],
    // which is "ieaouq".int output = 1;
    Solution sl;
    int ret = sl.countOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
