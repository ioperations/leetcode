// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

The Hamming distance between two integers is the number of positions at which
the corresponding bits are different.

Given two integers x and y, return the Hamming distance between them.

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

namespace {
class Solution {
   public:
    int HammingDistance(int x, int y) {
        std::string x_str = ErJinZhi(x);
        std::string y_str = ErJinZhi(y);

        int count = 0;
        for (int i = 0; i < 32; i++) {
            if (x_str[i] != y_str[i]) {
                count++;
            }
        }
        return count;
    }

    std::string ErJinZhi(int x) {
        std::string ret = "00000000000000000000000000000000";

        int i = 0;
        while (x) {
            int cur = x % 2;
            ret[31 - i] = '0' + cur;
            x /= 2;
            i++;
        }
        // std::reverse(ret.begin(), ret.end());
        return ret;
    }
    int HammingWeight(int n) {
        int sum = 0;
        while (n > 0) {
            n = (n & (n - 1));
            sum++;
        }
        return sum;
    }
    int HammingDistanceV2(int x, int y) { return HammingWeight(x ^ y); }
};



TEST(hamming_distance, t1) {
    int x = 1, y = 4;
    int output = 2;
    // Explanation:
    // 1   (0 0 0 1)
    // 4   (0 1 0 0)
    //        ↑   ↑
    // The above arrows point to positions where the corresponding bits are
    // different.
    Solution s;
    int ret = s.HammingDistance(x, y);
    EXPECT_EQ(ret, output);

    ret = s.HammingDistanceV2(x, y);
    EXPECT_EQ(ret, output);
}

TEST(hamming_distance, t2) {
    int x = 3, y = 1;
    int output = 1;
    // Explanation:
    // 1   (0 0 0 1)
    // 4   (0 1 0 0)
    // ↑   ↑
    // The above arrows point to positions where the corresponding bits are
    // different.
    Solution s;
    int ret = s.HammingDistance(x, y);
    EXPECT_EQ(ret, output);

    ret = s.HammingDistanceV2(x, y);
    EXPECT_EQ(ret, output);
}

} // namespace
