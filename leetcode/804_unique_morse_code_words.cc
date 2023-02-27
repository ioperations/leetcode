/*International Morse Code defines a standard encoding where each letter is
mapped to a series of dots and dashes, as follows:

'a' maps to ".-",
'b' maps to "-...",
'c' maps to "-.-.", and so on.
For convenience, the full table for the 26 letters of the English alphabet is
given below:

[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
Given an array of strings words where each word can be written as a
concatenation of the Morse code of each letter.

For example, "cab" can be written as "-.-..--...", which is the concatenation of
"-.-.", ".-", and "-...". We will call such a concatenation the transformation
of a word. Return the number of different transformations among all words we
have.*/
#include <set>
#include <string>
#include <vector>

using namespace std;

const char *table[] = {".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",
                       "....", "..",   ".---", "-.-",  ".-..", "--",   "-.",
                       "---",  ".--.", "--.-", ".-.",  "...",  "-",    "..-",
                       "...-", ".--",  "-..-", "-.--", "--.."};
class Solution {
    std::string Convert(std::string &s) {
        string ret;
        for (auto chars : s) {
            ret += table[chars - 'a'];
        }

        return ret;
    }

   public:
    int UniqueMorseRepresentations(vector<string> &words) {
        // pass
        std::set<string> set;
        for (auto &ptr : words) {
            set.insert(Convert(ptr));
        }

        return set.size();
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<string> words = {"gin", "zen", "gig", "msg"};
    int output = 2;
    /*
    Explanation: The transformation of each word is:
    "gin" -> "--...-."
    "zen" -> "--...-."
    "gig" -> "--...--."
    "msg" -> "--...--."
    There are 2 different transformations: "--...-." and "--...--.".
    */
    Solution sl;

    int ret = sl.UniqueMorseRepresentations(words);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<string> words = {"a"};
    int output = 1;
    Solution sl;

    int ret = sl.UniqueMorseRepresentations(words);
    EXPECT_EQ(ret, output);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
