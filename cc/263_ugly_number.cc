// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*An ugly number is a positive integer whose prime factors are limited to 2, 3,
and 5. Given an integer n, return true if n is an ugly number.*/

#include <unordered_map>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
    std::unordered_map<int, bool> m_cache;

   public:
    bool IsUgly(int n) {
        if (n == 0) return false;
        if (n == 1) return true;
        if (m_cache.count(n)) return m_cache[n];

        int const t2 = n / 2;
        int const t_2 = n % 2;
        if (t_2 == 0 && IsUgly(t2)) {
            m_cache[n] = true;
            return true;
        }
        int const t3 = n / 3;
        int const t_3 = n % 3;
        if (t_3 == 0 && IsUgly(t3)) {
            m_cache[n] = true;
            return true;
        }

        int const t4 = n / 5;
        int const t_4 = n % 5;
        if (t_4 == 0 && IsUgly(t4)) {
            m_cache[n] = true;
            return true;
        }

        m_cache[n] = false;
        return false;
    }
};

TEST(ugly_number, t1) {
    int const n = 6;
    bool const output = true;
    // Explanation: 6 = 2 × 3
    Solution sl;
    bool const ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(ugly_number, t2) {
    int const n = 1;
    bool const output = true;
    // 1 has no prime factors, therefore all of its prime factors are limited to
    // 2, 3, and 5.
    Solution sl;
    bool const ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(ugly_number, t3) {
    int const n = 14;
    bool const output = false;
    // 14 is not ugly since it includes the prime factor 7.
    Solution sl;
    bool const ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(ugly_number, t4) {
    int const n = 0;
    bool const output = false;
    // 14 is not ugly since it includes the prime factor 7.
    Solution sl;
    bool const ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

}  // namespace
