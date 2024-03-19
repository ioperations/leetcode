// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Write a function that reverses a string. The input string is given as an array
of characters s.

You must do this by modifying the input array in-place with O(1) extra memory.

*/

#include <algorithm>
#include <stack>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    void ReverseString(std::vector<char> &s) {
        // pass
        std::reverse(s.begin(), s.end());
    }

    void ReverseStringV2(std::vector<char> &s) {
        std::stack<char> sk;
        for (auto &ptr : s) {
            sk.push(ptr);
        }

        int i = 0;
        while (sk.size()) {
            s[i] = sk.top();
            sk.pop();
            i++;
        }
    }
};

TEST(reverse_string, t1) {
    std::vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    std::vector<char> output = {'o', 'l', 'l', 'e', 'h'

    };
    Solution sl;
    sl.ReverseString(s);

    EXPECT_EQ(s, output);

    sl.ReverseString(s);

    sl.ReverseStringV2(s);
    EXPECT_EQ(s, output);
}
TEST(reverse_string, t2) {
    std::vector<char> s = {'H', 'a', 'n', 'n', 'a', 'h'};
    std::vector<char> output = {'h', 'a', 'n', 'n', 'a', 'H'};
    Solution sl;
    sl.ReverseString(s);

    EXPECT_EQ(s, output);
}
}  // namespace
