// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer num, return a string of its base 7 representation.

*/

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
    string ConvertToBase7(int num) {
        std::string ret;
        if (num < 0) {
            return "-" + ConvertToBase7(-num);
        }
        while (num != 0) {
            int left = num % 7;
            ret = std::to_string(left) + ret;
            num = num / 7;
        }
        return ret;
    }
};



TEST(base_7, t1) {
    int num = 100;
    string output = "202";
    Solution sl;
    auto ret = sl.ConvertToBase7(num);
    EXPECT_EQ(ret, output);
}

TEST(base_7, t2) {
    int num = -7;
    string output = "-10";
    Solution sl;
    auto ret = sl.ConvertToBase7(num);
    EXPECT_EQ(ret, output);
}

} // namespace
