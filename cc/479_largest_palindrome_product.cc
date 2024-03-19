// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given an integer n, return the largest palindromic integer that can be
represented as the product of two n-digits integers. Since the answer can be
very large, return it modulo 1337.

*/
#include <catch2/catch_test_macros.hpp>
#include <string>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
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
                    const unsigned long val =
                        start;  //(n_digits-i)*(n_digits-j);
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
                const int step = (n_digits - i) * 22;
                for (; j <= i + 11; j += 22) {
                    // cnt++;
                    const unsigned long val =
                        start;  //(n_digits-i)*(n_digits-j);
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
                const unsigned long val = (n_digits - i) * (n_digits - j);
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
        const int n = s.size();

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

TEST(largest_palindrome_product, t1) {
    // Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
    Solution s;
    const bool ret = s.IsPalindrome("9009");
    EXPECT_EQ(ret, true);
}

TEST(largest_palindrome_product, t2) {
    // Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
    Solution s;
    const bool ret = s.IsPalindrome("000");
    EXPECT_EQ(ret, true);
}

TEST(largest_palindrome_product_v2, t2) {
    const int n = 2;
    const int expected = 987;
    // Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
    Solution s;
    const int ret = s.LargestPalindrome(n);
    EXPECT_EQ(ret, expected);
}

TEST(largest_palindrome_product_v2, t3) {
    const int n = 1;
    const int expected = 9;
    Solution s;
    const int ret = s.LargestPalindrome(n);
    EXPECT_EQ(ret, expected);
}

}  // namespace
