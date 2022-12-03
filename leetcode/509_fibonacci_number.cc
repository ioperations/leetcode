/*The Fibonacci numbers, commonly denoted F(n) form a sequence, called the
Fibonacci sequence, such that each number is the sum of the two preceding ones,
starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.

Given n, calculate F(n).*/

#include <map>
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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 2;
    int out = 1;
    Solution sl;
    int ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

TEST(t0, t2) {
    int n = 3;
    int out = 2;
    Solution sl;
    int ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

TEST(t0, t3) {
    int n = 4;
    int out = 3;
    Solution sl;
    int ret = sl.Fib(n);
    EXPECT_EQ(ret, out);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
