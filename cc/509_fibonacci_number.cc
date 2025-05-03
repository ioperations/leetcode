// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*The Fibonacci numbers, commonly denoted F(n) form a sequence, called the
Fibonacci sequence, such that each number is the sum of the two preceding ones,
starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.

Given n, calculate F(n).*/

#include <map>

#include "gtest/gtest.h"

namespace {
class Solution {
    std::map<int, int> m_cache;

   public:
    int Fib(int n) {
        // pass
        if (n == 0) return 0;
        if (n == 1) return 1;
        if (m_cache.count(n)) {
            return m_cache[n];
        }
        int const ret = Fib(n - 1) + Fib(n - 2);
        m_cache[n] = ret;
        return ret;
    }
};

TEST(fibonacci_number, t1) {
    int const n = 2;
    int const out = 1;
    Solution sl;
    int const ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

TEST(fibonacci_number, t2) {
    int const n = 3;
    int const out = 2;
    Solution sl;
    int const ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

TEST(fibonacci_number, t3) {
    int const n = 4;
    int const out = 3;
    Solution sl;
    int const ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

}  // namespace
