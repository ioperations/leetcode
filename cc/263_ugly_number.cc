// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*An ugly number is a positive integer whose prime factors are limited to 2, 3,
and 5. Given an integer n, return true if n is an ugly number.*/

#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
    std::unordered_map<int, bool> cache;

   public:
    bool IsUgly(int n) {
        if (n == 0) return false;
        if (n == 1) return true;
        if (cache.count(n)) return cache[n];

        int t2 = n / 2;
        int t_2 = n % 2;
        if (t_2 == 0 && IsUgly(t2)) {
            cache[n] = true;
            return true;
        }
        int t3 = n / 3;
        int t_3 = n % 3;
        if (t_3 == 0 && IsUgly(t3)) {
            cache[n] = true;
            return true;
        }

        int t4 = n / 5;
        int t_4 = n % 5;
        if (t_4 == 0 && IsUgly(t4)) {
            cache[n] = true;
            return true;
        }

        cache[n] = false;
        return false;
    }
};

TEST(ugly_number, t1) {
    int n = 6;
    bool output = true;
    // Explanation: 6 = 2 × 3
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(ugly_number, t2) {
    int n = 1;
    bool output = true;
    // 1 has no prime factors, therefore all of its prime factors are limited to
    // 2, 3, and 5.
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(ugly_number, t3) {
    int n = 14;
    bool output = false;
    // 14 is not ugly since it includes the prime factor 7.
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(ugly_number, t4) {
    int n = 0;
    bool output = false;
    // 14 is not ugly since it includes the prime factor 7.
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

}  // namespace
