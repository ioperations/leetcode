/*
 * You are given a string word and a non-negative integer k.
 *
 * Return the total number of substrings of word that contain every vowel ('a',
 * 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

#include <gtest/gtest.h>

using namespace std;

namespace {
class Solution {
   public:
    int m_n{};
    std::array<char, 26> m_vow{};
    void SetType() {
        m_vow.fill(5);
        m_vow.at(0) = 0, m_vow.at('e' - 'a') = 1, m_vow.at('i' - 'a') = 2,
        m_vow.at('o' - 'a') = 3,
        m_vow.at('u' - 'a') = 4;
    }

    inline long long LessEq(std::string& word, int k) {
        std::array<int, 5> last_pos{};
        last_pos.fill(-1);
        std::array<int, 6> freq{};
        long long ans = 0;

        int cnt_vow = 0;
        for (int l = 0, r = 0; r < m_n; r++) {
            int type = m_vow.at(word.at(r) - 'a');

            if (type < 5) {
                last_pos.at(type) = r;
                if (freq.at(type) == 0) cnt_vow++;
            }

            freq.at(type)++;

            while (freq.at(5) > k) {
                type = m_vow.at(word.at(l) - 'a');
                freq.at(type)--;
                if (type < 5 && freq.at(type) == 0) cnt_vow--;
                l++;
            }
            int const min_pos =
                *std::min_element(last_pos.begin(), last_pos.end());
            if (cnt_vow == 5) {
                ans += (min_pos - l + 1);
            }
        }
        return ans;
    }

    long long CountOfSubstrings(string& word, int k) {
        SetType();

        m_n = static_cast<int>(word.size());

        return k == 0 ? LessEq(word, 0) : LessEq(word, k) - LessEq(word, k - 1);
    }
};
}  // namespace

namespace {
struct Init {
    Init() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
    }
};
Init const init;
}  // namespace

TEST(T0, t1) {
    string word = "aeioqq";
    int const k = 1;
    int const output = 0;
    Solution sl;
    long long const ret = sl.CountOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
}

TEST(T0, t2) {
    string word = "aeiou";
    int const k = 0;
    int const output = 1;
    Solution sl;
    long long const ret = sl.CountOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
}

TEST(T0, t3) {
    string word = "ieaouqqieaouqq";
    int const k = 1;
    int const output = 3;
    Solution sl;
    long long const ret = sl.CountOfSubstrings(word, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}