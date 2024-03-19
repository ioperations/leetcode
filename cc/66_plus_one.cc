// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given a large integer represented as an integer array digits, where
each digits[i] is the ith digit of the integer. The digits are ordered from most
significant to least significant in left-to-right order. The large integer does
not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.
*/

#include <vector>

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
    vector<int> PlusOne(vector<int> &digits) {
        // pass
        int carry = 1;

        for (auto it = digits.rbegin(); it != digits.rend(); it++) {
            *it += carry;
            carry = *it / 10;
            *it = *it % 10;
        }
        if (carry) {
            digits.insert(digits.begin(), 1, carry);
        }
        return digits;
    }
};

TEST(plus_one, t1) {
    std::vector<int> digits = {1, 2, 3};

    Solution s;
    auto ret = s.PlusOne(digits);
    EXPECT_EQ(ret, (std::vector<int>{1, 2, 4}));
}

TEST(plus_one, t2) {
    std::vector<int> digits = {4, 3, 2, 1};

    Solution s;
    auto ret = s.PlusOne(digits);
    EXPECT_EQ(ret, (std::vector<int>{4, 3, 2, 2}));
}

TEST(plus_one, t3) {
    std::vector<int> digits = {9};

    Solution s;
    auto ret = s.PlusOne(digits);
    EXPECT_EQ(ret, (std::vector<int>{1, 0}));
}

}  // namespace
