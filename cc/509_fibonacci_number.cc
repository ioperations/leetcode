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

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
    std::map<int, int> cache;

   public:
    int Fib(int n) {
        // pass
        if (n == 0) return 0;
        if (n == 1) return 1;
        if (cache.count(n)) {
            return cache[n];
        }
        int ret = Fib(n - 1) + Fib(n - 2);
        cache[n] = ret;
        return ret;
    }
};

TEST(fibonacci_number, t1) {
    int n = 2;
    int out = 1;
    Solution sl;
    int ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

TEST(fibonacci_number, t2) {
    int n = 3;
    int out = 2;
    Solution sl;
    int ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

TEST(fibonacci_number, t3) {
    int n = 4;
    int out = 3;
    Solution sl;
    int ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

}  // namespace
