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
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<string> TopKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> umap;
        for (string const& s : words) umap[s]++;
        priority_queue<pair<int, string>> pq;
        for (auto it : umap) {
            // minus sign used to build min heap
            pq.emplace(-it.second, it.first);
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

TEST(top_k_frequent_words, t1) {
    std::vector<string> words = {"i", "love", "leetcode",
                                 "i", "love", "coding"};
    int const k = 2;
    std::vector<string> const output = {"i", "love"};
    /*
        "i" and "love" are the two most frequent words.
        Note that "i" comes before "love" due to a lower alphabetical order.
    */

    Solution sl;
    auto ret = sl.TopKFrequent(words, k);
    EXPECT_EQ(ret, output);
}

TEST(top_k_frequent_words, t2) {
    std::vector<string> words = {"the", "day", "is",    "sunny", "the",
                                 "the", "the", "sunny", "is",    "is"};
    int const k = 4;
    std::vector<string> const output = {"the", "is", "sunny", "day"};
    // Explanation: "the", "is", "sunny" and "day" are the four most frequent
    // words, with the number of occurrence being 4, 3, 2 and 1 respectively.

    Solution sl;
    auto ret = sl.TopKFrequent(words, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
