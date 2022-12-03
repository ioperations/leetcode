/*You are playing the Bulls and Cows game with your friend.

You write down a secret number and ask your friend to guess what the number is.
When your friend makes a guess, you provide a hint with the following info:

The number of "bulls", which are digits in the guess that are in the correct
position. The number of "cows", which are digits in the guess that are in your
secret number but are located in the wrong position. Specifically, the non-bull
digits in the guess that could be rearranged such that they become bulls. Given
the secret number secret and your friend's guess guess, return the hint for your
friend's guess.

The hint should be formatted as "xAyB", where x is the number of bulls and y is
the number of cows. Note that both secret and guess may contain duplicate
digits.

 */

#include <string>
using namespace std;

class Solution {
   public:
    string GetHint(string secret, string guess) {
        string ret;
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string secret = "1807", guess = "7810";

    string out = "1A3B";
    // Bulls are connected with a '|' and cows are underlined:
    // "1807"
    //   |
    // "7810"

    Solution sl;
    auto ret = sl.GetHint(secret, guess);
    EXPECT_EQ(ret, out);
}

TEST(t0, t2) {
    string secret = "1123", guess = "0111";
    string out = "1A1B";
    /*
        Bulls are connected with a '|' and cows are underlined:
        "1123"        "1123"
          |      or     |
        "0111"        "0111"
        Note that only one of the two unmatched 1s is counted as a cow since
        the non-bull digits can only be rearranged to allow one 1 to be a bull.
    */

    Solution sl;
    auto ret = sl.GetHint(secret, guess);
    EXPECT_EQ(ret, out);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
