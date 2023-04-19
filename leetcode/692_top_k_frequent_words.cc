// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an array of strings words and an integer k, return the k most frequent
strings.

Return the answer sorted by the frequency from highest to lowest. Sort the words
with the same frequency by their lexicographical order.
*/
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<string> TopKFrequent(vector<string> &words, int k) {
        unordered_map<string, int> umap;
        for (string s : words) umap[s]++;
        priority_queue<pair<int, string>> pq;
        for (auto it : umap) {
            // minus sign used to build min heap
            pq.push({-it.second, it.first});
            if ((int)pq.size() > k) pq.pop();
        }
        vector<string> res;
        while (k--) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<string> words = {"i", "love", "leetcode",
                                 "i", "love", "coding"};
    int k = 2;
    std::vector<string> output = {"i", "love"};
    /*
        "i" and "love" are the two most frequent words.
        Note that "i" comes before "love" due to a lower alphabetical order.
    */

    Solution sl;
    auto ret = sl.TopKFrequent(words, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<string> words = {"the", "day", "is",    "sunny", "the",
                                 "the", "the", "sunny", "is",    "is"};
    int k = 4;
    std::vector<string> output = {"the", "is", "sunny", "day"};
    // Explanation: "the", "is", "sunny" and "day" are the four most frequent
    // words, with the number of occurrence being 4, 3, 2 and 1 respectively.

    Solution sl;
    auto ret = sl.TopKFrequent(words, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
