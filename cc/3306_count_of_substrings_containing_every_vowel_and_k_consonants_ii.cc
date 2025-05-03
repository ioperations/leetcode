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
    int m_n{};
    char m_vow[26] = {0};  //  vowels & consonants mapped to 0~5
    void SetType() {
        // Initialize all characters as consonants 5
        memset(m_vow, 5, sizeof(m_vow));
        m_vow[0] = 0, m_vow['e' - 'a'] = 1, m_vow['i' - 'a'] = 2,
        m_vow['o' - 'a'] = 3,
        m_vow['u' - 'a'] = 4;  // type for vowels
    }

    // Function computes the number at most k consonants
    inline long long LessEq(string& word, int k) {
        int last_pos[5] = {-1};  // last position of each vowel
        int freq[6] = {0};       // 0-4 for vowl 5 for consonants)
        long long ans = 0;       // count of valid substrings

        int cnt_vow = 0;  // count different vowels in the current window
        for (int l = 0, r = 0; r < m_n; r++) {
            int type = m_vow[word[r] - 'a'];  // Get the type

            if (type < 5) {
                last_pos[type] = r;  // last position of the vowel
                if (freq[type] == 0) cnt_vow++;
            }

            freq[type]++;  // Increase the freq

            // Shrink the window if the number of consonants exceeds k
            while (freq[5] > k) {  // freq[5] tracks consonants
                type = m_vow[word[l] - 'a'];
                freq[type]--;
                if (type < 5 && freq[type] == 0) cnt_vow--;
                l++;  // Move left pointer
            }
            int const min_pos = *min_element(last_pos, last_pos + 5);
            //    cout << freq[5] << endl;
            // count the number of valid substrings
            if (cnt_vow == 5)
                ans += (min_pos - l + 1);  // valid substrings ending at r
        }
        return ans;
    }

    // Main function to count the substrings based on the given k value
    long long CountOfSubstrings(string& word, int k) {
        SetType();

        m_n = word.size();  // Store the length of the word

        // Return the number of substrings with at most k consonants minus
        // those with at most k-1 consonants
        return k == 0 ? LessEq(word, 0) : LessEq(word, k) - LessEq(word, k - 1);
    }
};

static auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();

#include <gtest/gtest.h>

TEST(t0, t1) {
    string word = "aeioqq";
    int const k = 1;
    int const output = 0;
    Solution sl;
    int const ret = sl.CountOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string word = "aeiou";
    int const k = 0;
    int const output = 1;
    Solution sl;
    int const ret = sl.CountOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
    // The only substring with every vowel and zero consonants is
    // word[0..4], which is "aeiou".
}

TEST(t0, t3) {
    string word = "ieaouqqieaouqq";
    int const k = 1;
    int const output = 3;
    // Explanation :
    //
    // The substrings with every vowel and one consonant are :
    //
    // word[0..5],
    // which is "ieaouq".word[6..11],
    // which is "qieaou".word[7..12],
    // which is "ieaouq".int output = 1;
    Solution sl;
    int const ret = sl.CountOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
