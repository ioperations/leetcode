// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A decimal number is called deci-binary if each of its digits is either 0 or 1
without any leading zeros. For example, 101 and 1100 are deci-binary, while 112
and 3001 are not.

Given a string n that represents a positive decimal integer, return the minimum
number of positive deci-binary numbers needed so that they sum up to n.


*/
#include <algorithm>
#include <string>
using namespace std;

class Solution {
   public:
    int MinPartitions(string n) {
        /*
        A binary number may only contain 0 or 1 so to obtain a perticular digit
        of decimal we need only that number of 1s. For example for making 7 we
        need 7 1s so in turn we need minimum 7 binary numbers. So we can see for
        making up a number we need minimum binary numbers to make the largest
        digit of the number. For other digits we may add 0 after they are
        reached. So just return the max digit of the string (number) which is
        the required answer. Implementation :

        we just need to find the max element by *max_element(n.begin(), n.end())
        Here as the digit returned will be in char format so we substract '0'
        from it to make it int.
        */
        return *max_element(n.begin(), n.end()) - '0';
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string n = "32";
    int output = 3;
    Solution sl;
    int ret = sl.MinPartitions(n);
    EXPECT_EQ(ret, output);
    // Explanation: 10 + 11 + 11 = 32;
}

TEST(t0, t2) {
    string n = "38273";
    int output = 8;
    Solution sl;
    int ret = sl.MinPartitions(n);
    EXPECT_EQ(ret, output);
    // Explanation: 10 + 11 + 11 = 32;
}

TEST(t0, t3) {
    string n = "27346209830709182346";
    int output = 9;
    Solution sl;
    int ret = sl.MinPartitions(n);
    EXPECT_EQ(ret, output);
    // Explanation: 10 + 11 + 11 = 32;
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
