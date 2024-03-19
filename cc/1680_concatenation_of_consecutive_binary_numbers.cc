// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer n, return the decimal value of the binary string formed by
 * concatenating the binary representations of 1 to n in order, modulo 109
 * + 7.*/

#include <cmath>
#include <string>

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
   public:
    inline std::string DemicalToBinary(int i) {
        std::string ret;
        while (i) {
            ret = std::to_string(i % 2) + ret;
            i /= 2;
        }
        return ret;
    }

    inline void AppendToStringv1(int i, std::string &str) {
        std::string ret = DemicalToBinary(i);
        str += ret;
    }
    void AppendToString(int n, std::string &str) {
        for (int i = 1; i < (n + 1); ++i) {
            AppendToStringv1(i, str);
        }
    }

   public:
    int ConcatenatedBinary(int n) {
        int next = 1;  //  length = 1;
        long max_n = pow(10, 9) + 7, result = 0;
        for (int i = 0; i <= n; i++) {
            if (i == next) {
                next *= 2;
                // length++;
            }

            result = (result * next + i) % max_n;
        }
        return result;
    }
};

TEST(concatenation_of_consecutive_binary_numbers_v2, t0) {
    int const n = 10;
    Solution sl;
    std::string const ret = sl.DemicalToBinary(n);
    // "1" in binary corresponds to the decimal value 1.
    EXPECT_EQ(ret, std::string("1010"));
}

TEST(concatenation_of_consecutive_binary_numbers, t1) {
    int const n = 1;
    int const output = 1;
    Solution sl;
    int const ret = sl.ConcatenatedBinary(n);
    std::string expected_str = "1";
    // "1" in binary corresponds to the decimal value 1.
    std::string str;
    sl.AppendToString(n, str);
    EXPECT_EQ(str, expected_str);
    EXPECT_EQ(ret, output);
}

TEST(concatenation_of_consecutive_binary_numbers, t2) {
    int const n = 3;
    int const output = 27;
    Solution sl;
    int const ret = sl.ConcatenatedBinary(n);
    std::string expected_str = "11011";
    /*
        In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
        After concatenating them, we have "11011", which corresponds to the
       decimal value 27.
    */

    std::string str;
    sl.AppendToString(n, str);
    EXPECT_EQ(str, expected_str);
    EXPECT_EQ(ret, output);
}

TEST(concatenation_of_consecutive_binary_numbers, t3) {
    int const n = 12;
    int const output = 505379714;
    std::string expected_str = "1101110010111011110001001101010111100";
    /*
        Explanation: The concatenation results in
        "1101110010111011110001001101010111100". The decimal value of that is
        118505380540. After modulo 109 + 7, the result is 505379714.
    */
    Solution sl;
    int const ret = sl.ConcatenatedBinary(n);
    std::string str;
    sl.AppendToString(n, str);
    EXPECT_EQ(str, expected_str);
    EXPECT_EQ(ret, output);
}

}  // namespace
