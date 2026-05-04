// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A valid encoding of an array of words is any reference string s and array of
indices indices such that:

words.length == indices.length
The reference string s ends with the '#' character.
For each index indices[i], the substring of s starting from indices[i] and up to
(but not including) the next '#' character is equal to words[i]. Given an array
of words, return the length of the shortest reference string s possible of any
valid encoding of words.*/

#include <array>
#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   private:
    struct TrieNode {
        int m_ends_here{0};
        std::array<TrieNode*, 26> m_child{};
        TrieNode() = default;
        ~TrieNode() = default;
        TrieNode(const TrieNode&) = default;
        TrieNode& operator=(const TrieNode&) = default;
        TrieNode(TrieNode&&) = default;
        TrieNode& operator=(TrieNode&&) = default;
    };

    TrieNode* GetNode() {
        auto* new_node = new TrieNode;
        return new_node;
    }

    void DeleteNode(TrieNode* const root) {
        if (root == nullptr) return;
        for (auto& i : root->m_child) {
            DeleteNode(i);
        }
        delete root;
    }

   public:
    TrieNode* m_root;

    Solution() : m_root(GetNode()) {}
    ~Solution() { DeleteNode(m_root); }
    Solution(const Solution&) = default;
    Solution& operator=(const Solution&) = default;
    Solution(Solution&&) = default;
    Solution& operator=(Solution&&) = default;

    int MinimumLengthEncoding(vector<string>& words) {
        // use set to avoid repetetion for duplicate words
        unordered_set<string> s;

        int count = 0;  // the number of words in the reference string
        // the number of words =  number of # to add in result string
        int res = 0;  // the total length of the result string
        for (const auto& word : words) {
            if (s.count(word)) continue;
            s.insert(word);
            Insert(word, count, res);
        }
        return res + count;
    }

    void Insert(string const& word, int& count, int& res) {
        TrieNode* curr = m_root;
        int const len = static_cast<int>(word.length());
        bool flag = true;
        for (int i = len - 1; i >= 0; i--) {
            int const ind = word.at(i) - 'a';
            if (curr->m_child.at(ind) == nullptr) {
                flag = false;
                curr->m_child.at(ind) = GetNode();
            }
            if (curr->m_ends_here) {
                curr->m_ends_here = 0;
                count--;
                res -= (len - i - 1);
            }
            curr = curr->m_child.at(ind);
        }
        // flag will be true if some word previously has created all the
        // nodes ex- ["time","me"] for "me" the flag will be true so we dont
        // calculate the result
        if (!flag) {
            curr->m_ends_here = 1;
            count++;
            res += len;
        }
    }
};

TEST(ShortEncodingOfWords, t1) {
    vector<string> words = {"time", "me", "bell"};
    int const output = 10;
    Solution sl;
    int const ret = sl.MinimumLengthEncoding(words);
    /*A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
words[0] = "time", the substring of s starting from indices[0] = 0 to the next
'#' is underlined in "time#bell#" words[1] = "me", the substring of s starting
from indices[1] = 2 to the next '#' is underlined in "time#bell#" words[2] =
"bell", the substring of s starting from indices[2] = 5 to the next '#' is
underlined in "time#bell#"
    */
    EXPECT_EQ(ret, output);
}

TEST(ShortEncodingOfWords, t2) {
    vector<string> words = {"t"};
    int const output = 2;
    Solution sl;
    int const ret = sl.MinimumLengthEncoding(words);
    // A valid encoding would be s = "t#" and indices = [0].
    EXPECT_EQ(ret, output);
}

}  // namespace
