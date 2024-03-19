// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Write a function to find the longest common prefix string amongst an array of
strings.

If there is no common prefix, return an empty string "".


    */

#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    string LongestCommonPrefix(vector<string> &strs) {
        std::string ret = "";

        size_t i = 0;
        int continue_run = true;
        while (continue_run) {
            char this_bit = ' ';
            bool set = false;
            for (auto &ptr : strs) {
                if (i < ptr.size()) {
                    if (set) {
                        if (this_bit == ptr[i]) {
                            continue;
                        }
                        continue_run = false;
                        break;
                    }

                    this_bit = ptr[i];
                    set = true;

                } else {
                    continue_run = false;
                    break;
                }
            }
            if (continue_run) {
                ret += this_bit;
            }
            i++;
        }
        return ret;
    }
};

TEST(longest_common_prefix, t1) {
    std::vector<std::string> strs = {"flower", "flow", "flight"};
    const std::string output = "fl";

    Solution s;
    const auto ret = s.LongestCommonPrefix(strs);

    EXPECT_EQ(ret, output);
}

TEST(longest_common_prefix, t2) {
    std::vector<std::string> strs = {"dog", "racecar", "car"};
    const std::string output = "";

    Solution s;
    const auto ret = s.LongestCommonPrefix(strs);

    EXPECT_EQ(ret, output);
}

}  // namespace
