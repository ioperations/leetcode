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

#include "gtest/gtest.h"

using namespace std;

namespace {
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

TEST(partitioning_into_minimum_number_of_deci_binary_numbers, t1) {
    string const n = "32";
    int const output = 3;
    Solution sl;
    int const ret = sl.MinPartitions(n);
    EXPECT_EQ(ret, output);
    // Explanation: 10 + 11 + 11 = 32;
}

TEST(partitioning_into_minimum_number_of_deci_binary_numbers, t2) {
    string const n = "38273";
    int const output = 8;
    Solution sl;
    int const ret = sl.MinPartitions(n);
    EXPECT_EQ(ret, output);
    // Explanation: 10 + 11 + 11 = 32;
}

TEST(partitioning_into_minimum_number_of_deci_binary_numbers, t3) {
    string const n = "27346209830709182346";
    int const output = 9;
    Solution sl;
    int const ret = sl.MinPartitions(n);
    EXPECT_EQ(ret, output);
    // Explanation: 10 + 11 + 11 = 32;
}
}  // namespace
