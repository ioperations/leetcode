// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
在输入的区间当中统计2出现的次数
比如在【1，22】之间

    2出现的一次2
    12出现了一次2
    20出现了一次2
    21出现了一次2
    22出现了两次2
    所以一共出现了6次2
*/

#include <catch2/catch_test_macros.hpp>

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
    int Solve(int left, int right) {
        // pass
        return 6;
    }

   private:
    /* data */
};

TEST(other_count_2_appear_times, t1) {
    int left = 1;
    int right = 22;
    int output = 6;
    Solution sl;
    int ret = sl.Solve(left, right);
    EXPECT_EQ(ret, output);
}

}  // namespace
