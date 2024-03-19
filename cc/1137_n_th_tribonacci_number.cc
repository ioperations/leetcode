// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*The Tribonacci sequence Tn is defined as follows:

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.*/

#include <map>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
    std::map<int, int> cache;

   public:
    int Tribonacci(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        if (n == 2) return 1;
        if (cache.count(n)) {
            return cache[n];
        }
        int ret = Tribonacci(n - 3) + Tribonacci(n - 2) + Tribonacci(n - 1);
        cache[n] = ret;

        return ret;
    }
};

TEST(n_th_tribonacci_number, t1) {
    int n = 4;
    int out = 4;
    Solution sl;
    int ret = sl.Tribonacci(n);
    /*
        T_3 = 0 + 1 + 1 = 2
        T_4 = 1 + 1 + 2 = 4
    */
    EXPECT_EQ(ret, out);
}

TEST(n_th_tribonacci_number, t2) {
    int n = 25;
    int out = 1389537;
    Solution sl;
    int ret = sl.Tribonacci(n);
    EXPECT_EQ(ret, out);
}

}  // namespace
