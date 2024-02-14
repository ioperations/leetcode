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

#include "gtest/gtest.h"

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

TEST(t0, t1) {
    std::vector<std::string> strs = {"flower", "flow", "flight"};
    std::string output = "fl";

    Solution s;
    auto ret = s.LongestCommonPrefix(strs);

    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<std::string> strs = {"dog", "racecar", "car"};
    std::string output = "";

    Solution s;
    auto ret = s.LongestCommonPrefix(strs);

    EXPECT_EQ(ret, output);
}

}  // namespace
