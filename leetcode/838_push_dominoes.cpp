/*There are n dominoes in a line, and we place each domino vertically upright.
In the beginning, we simultaneously push some of the dominoes either to the left
or to the right.

After each second, each domino that is falling to the left pushes the adjacent
domino on the left. Similarly, the dominoes falling to the right push their
adjacent dominoes standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays
still due to the balance of the forces.

For the purposes of this question, we will consider that a falling domino
expends no additional force to a falling or already fallen domino.

You are given a string dominoes representing the initial state where:

dominoes[i] = 'L', if the ith domino has been pushed to the left,
dominoes[i] = 'R', if the ith domino has been pushed to the right, and
dominoes[i] = '.', if the ith domino has not been pushed.
Return a string representing the final state.*/
#include <string>

using namespace std;

class Solution {
   public:
    string PushDominoes(string dominoes) {
        std::string ret;
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::string const dominoes = "RR.L";
    std::string const output = "RR.L";
    // Explanation: The first domino expends no additional force on the second
    // domino.
    Solution sl;
    std::string const ret = sl.PushDominoes(dominoes);
    EXPECT_EQ(output, ret);
}

TEST(t0, t2) {
    std::string const dominoes = ".L.R...LR..L..";
    std::string const output = "LL.RR.LLRRLL..";
    // Explanation: The first domino expends no additional force on the second
    // domino.
    Solution sl;
    std::string const ret = sl.PushDominoes(dominoes);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
