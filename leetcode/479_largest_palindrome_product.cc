// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given an integer n, return the largest palindromic integer that can be
represented as the product of two n-digits integers. Since the answer can be
very large, return it modulo 1337.

*/
#include <string>

class Solution {
   public:
    bool IsPalindrome(unsigned long val) {
        if ((val % 10) != 9) return false;
        std::string s = std::to_string(val);
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }
    int LargestPalindrome(int n) {
        if (n == 1) return 9;
        unsigned long n_digits = 1;
        while (n--) n_digits *= 10;
        unsigned long candidate = 0, max_offset = 0;
        long i, j;
        for (i = 1; i < (int)n_digits; i += 2) {
            // int cnt = 0;
            if (!((n_digits - i) % 11)) {
                unsigned long start;
                for (j = 1, start = (n_digits - i) * (n_digits - j); j <= i;
                     j += 2) {
                    // cnt++;
                    unsigned long val = start;  //(n_digits-i)*(n_digits-j);
                    if (IsPalindrome(val)) {
                        candidate = val;
                        max_offset = n_digits - val / (n_digits - 1);
                        break;
                    }
                    start -= ((n_digits - i) << 1);
                }
            } else {
                unsigned long start;
                j = n_digits - n_digits / 11 * 11;
                if (!(j & 1)) j += 11;
                start = (n_digits - i) * (n_digits - j);
                int step = (n_digits - i) * 22;
                for (; j <= i + 11; j += 22) {
                    // cnt++;
                    unsigned long val = start;  //(n_digits-i)*(n_digits-j);
                    start -= step;
                    if (IsPalindrome(val)) {
                        candidate = val;
                        max_offset = n_digits - val / (n_digits - 1);
                        break;
                    }
                }
            }

            if (candidate) break;
        }
        for (; i <= (int)max_offset; i += 2) {
            for (j = 1; j <= i; j += 2) {
                unsigned long val = (n_digits - i) * (n_digits - j);
                if (val <= candidate) break;
                if (IsPalindrome(val)) {
                    candidate = val;
                    max_offset = n_digits - val / (n_digits - 1);
                    break;
                }
            }
        }
        return candidate % 1337;
    }
    bool IsPalindrome(const std::string s) {
        int n = s.size();

        int left = 0;
        int right = 0;
        if (n % 2 == 0) {
            left = n / 2 - 1;
            right = n / 2;
        } else {
            left = n / 2 - 1;
            right = n / 2 + 1;
        }

        while (left >= 0) {
            if (s[left] == s[right]) {
                left--;
                right++;

            } else {
                return false;
            }
        }
        if (left < 0) {
            return true;
        }
        return false;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t, t1) {
    // Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
    Solution s;
    bool ret = s.IsPalindrome("9009");
    EXPECT_EQ(ret, true);
}

TEST(t, t2) {
    // Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
    Solution s;
    bool ret = s.IsPalindrome("000");
    EXPECT_EQ(ret, true);
}

TEST(t0, t1) {
    int n = 2;
    int expected = 987;
    // Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
    Solution s;
    int ret = s.LargestPalindrome(n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    int n = 1;
    int expected = 9;
    Solution s;
    int ret = s.LargestPalindrome(n);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
