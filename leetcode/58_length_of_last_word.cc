// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <string>
using namespace std;
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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::string s = "Hello World";
    int output = 5;

    Solution sl;
    int ret = sl.LengthOfLastWord(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::string s = "   fly me   to   the moon  ";
    int output = 4;
    Solution sl;
    int ret = sl.LengthOfLastWord(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    std::string s = "luffy is still joyboy";
    int output = 6;
    Solution sl;
    int ret = sl.LengthOfLastWord(s);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
