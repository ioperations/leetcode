// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    A transformation sequence from word beginWord to word endWord using a
   dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk
   such that:

    Every adjacent pair of words differs by a single letter.
    Every si for 1 <= i <= k is in wordList. Note that beginWord does not need
   to be in wordList. sk == endWord Given two words, beginWord and endWord, and
   a dictionary wordList, return the number of words in the shortest
   transformation sequence from beginWord to endWord, or 0 if no such sequence
   exists.
*/

#include <string>
using namespace std;
#include <queue>
#include <set>
#include <vector>
class Solution {
   public:
    int LadderLength(string begin_word, string end_word,
                     vector<string> &word_list) {
        // pass
        set<string> words;
        bool has_end = false;
        for (string word : word_list) {
            words.insert(word);
            if (word == end_word) has_end = true;
        }

        if (!has_end) return 0;

        queue<string> q;
        q.push(begin_word);
        int depth = 0;
        while (!q.empty()) {
            depth += 1;
            int qsize = q.size();
            // traverse all nodes of current level
            // bcz we are not going to use depth array
            while (qsize--) {
                string curr = q.front();
                q.pop();
                for (int i = 0; i < (int)curr.length(); i++) {
                    string tmp = curr;
                    // changing char at i, check all posibilities
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        tmp[i] = ch;
                        if (tmp == curr) continue;
                        if (tmp == end_word) return depth + 1;
                        if (words.count(tmp)) {
                            q.push(tmp);
                            words.erase(tmp);
                        }
                    }
                }
            }
        }

        // 26 * (length^2) * N

        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string begin_word = "hit", end_word = "cog";
    std::vector<string> word_list = {"hot", "dot", "dog", "lot", "log", "cog"};
    int output = 5;
    // Explanation: One shortest transformation sequence is "hit" -> "hot" ->
    // "dot" -> "dog" -> cog", which is 5 words long.

    Solution sl;
    int ret = sl.LadderLength(begin_word, end_word, word_list);
    EXPECT_EQ(ret, output);
}
TEST(t0, t2) {
    string begin_word = "hit", end_word = "cog";
    std::vector<string> word_list = {"hot", "dot", "dog", "lot", "log"};
    int output = 0;
    // Explanation: The endWord "cog" is not in wordList, therefore there is no
    // valid transformation sequence.

    Solution sl;
    int ret = sl.LadderLength(begin_word, end_word, word_list);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
