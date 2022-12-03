
/*

Given an m x n board of characters and a list of strings words, return all words
on the board.

Each word must be constructed from letters of sequentially adjacent cells, where
adjacent cells are horizontally or vertically neighboring. The same letter cell
may not be used more than once in a word.

*/

#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<string> FindWords(vector<vector<char>>& board,
                             vector<string>& words) {
        return words;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<vector<char>> board = {{'o', 'a', 'a', 'n'},
                                       {'e', 't', 'a', 'e'},
                                       {'i', 'h', 'k', 'r'},
                                       {'i', 'f', 'l', 'v'}};
    std::vector<string> words = {"oath", "pea", "eat", "rain"};

    /*
     ___ ___ ___ ___
    | o | a | a | n |
    |___|___|___|___|
    | e | t | a | e |
    |___|___|___|___|
    | i | h | k | r |
    |___|___|___|___|
    | i | f | l | v |
    |___|___|___|___|
    */

    Solution s;
    auto ret = s.FindWords(board, words);

    std::vector<std::string> expected = {"eat", "oath"};

    std::set<std::string> ret_set(ret.begin(), ret.end());
    std::set<std::string> expected_set(expected.begin(), expected.end());

    EXPECT_EQ(ret_set, expected_set);
}

TEST(t0, t2) {
    std::vector<vector<char>> board = {{'a', 'b'}, {'c', 'd'}};
    std::vector<string> words = {"abcb"};
    /*
         ___ ___
        | a | b |
        |___|___|
        | c | d |
        |___|___|
    */
    Solution s;
    auto ret = s.FindWords(board, words);

    std::vector<std::string> expected = {};

    std::set<std::string> ret_set(ret.begin(), ret.end());
    std::set<std::string> expected_set(expected.begin(), expected.end());

    EXPECT_EQ(ret_set, expected_set);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

