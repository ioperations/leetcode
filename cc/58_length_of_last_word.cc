// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    int LengthOfLastWord(string s) {
        int size = 0;
        for (auto it = s.rbegin(); it < s.rend(); it++) {
            if (*it == ' ') {
                if (size) {
                    break;
                }
                continue;
            }

            size++;
        }

        return size;
    }
};

TEST(length_of_last_word, t1) {
    std::string s = "Hello World";
    int output = 5;

    Solution sl;
    int ret = sl.LengthOfLastWord(s);
    EXPECT_EQ(ret, output);
}

TEST(length_of_last_word, t2) {
    std::string s = "   fly me   to   the moon  ";
    int output = 4;
    Solution sl;
    int ret = sl.LengthOfLastWord(s);
    EXPECT_EQ(ret, output);
}

TEST(length_of_last_word, t3) {
    std::string s = "luffy is still joyboy";
    int output = 6;
    Solution sl;
    int ret = sl.LengthOfLastWord(s);
    EXPECT_EQ(ret, output);
}

}  // namespace
