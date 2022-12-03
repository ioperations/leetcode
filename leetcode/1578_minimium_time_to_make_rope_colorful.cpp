/*
Alice has n balloons arranged on a rope. You are given a 0-indexed string
colors where colors[i] is the color of the ith balloon.

Alice wants the rope to be colorful. She does not want two consecutive balloons
to be of the same color, so she asks Bob for help. Bob can remove some balloons
from the rope to make it colorful. You are given a 0-indexed integer array
neededTime where neededTime[i] is the time (in seconds) that Bob needs to remove
the ith balloon from the rope.

Return the minimum time Bob needs to make the rope colorful.*/

#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int MinCost(string colors, vector<int>& needed_time) {
        // pass
        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string const colors = "abaac";
    vector<int> needed_time = {1, 2, 3, 4, 5};
    int const output = 3;
    /*
    Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
    Bob can remove the blue balloon at index 2. This takes 3 seconds.
    There are no longer two consecutive balloons of the same color. Total time
    = 3.
    */

    Solution sl;
    int const ret = sl.MinCost(colors, needed_time);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string const colors = "aba";
    vector<int> needed_time = {1, 2, 3};
    int const output = 0;
    /*
    The rope is already colorful. Bob does not need to remove any balloons from
    the rope.
    */

    Solution sl;
    int const ret = sl.MinCost(colors, needed_time);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string const colors = "aabaa";
    vector<int> needed_time = {1, 2, 3, 4, 1};
    int const output = 2;
    /*
    Bob will remove the ballons at indices 0 and 4. Each ballon takes 1 second
    to remove. There are no longer two consecutive balloons of the same color.
    Total time = 1 + 1 = 2.
    */

    Solution sl;
    int const ret = sl.MinCost(colors, needed_time);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
