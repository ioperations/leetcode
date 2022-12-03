/*
A password is considered strong if the below conditions are all met:

It has at least 6 characters and at most 20 characters.
It contains at least one lowercase letter, at least one uppercase letter, and at
least one digit. It does not contain three repeating characters in a row (i.e.,
"...aaa..." is weak, but "...aa...a..." is strong, assuming other conditions are
met). Given a string password, return the minimum number of steps required to
make password strong. if password is already strong, return 0.

In one step, you can:

Insert one character to password,
Delete one character from password, or
Replace one character of password with another character.*/

#include <string>
using namespace std;

class Solution {
   public:
    int StrongPasswordChecker(string password) {
        // pass

        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string password = "a";
    Solution sl;
    int ret = sl.StrongPasswordChecker(password);
    EXPECT_EQ(ret, 5);
}

TEST(t0, t2) {
    string password = "aA1";
    Solution sl;
    int ret = sl.StrongPasswordChecker(password);
    EXPECT_EQ(ret, 3);
}

TEST(t0, t3) {
    string password = "1337C0d3";
    Solution sl;
    int ret = sl.StrongPasswordChecker(password);
    EXPECT_EQ(ret, 0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
