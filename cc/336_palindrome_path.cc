// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given a list of unique words, return all the pairs of the distinct indices (i,
j) in the given list, so that the concatenation of the two words words[i] +
words[j] is a palindrome.

*/

#include <algorithm>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    vector<vector<int>> PalindromePairs(vector<string> &words) {
        vector<vector<int>> ret;

        for (int i = 0; i < (int)words.size() - 1; i++) {
            for (int j = i + 1; j < (int)words.size(); j++) {
                if (IsPalindromePairs(words, i, j)) {
                    ret.push_back({i, j});
                }
                if (IsPalindromePairs(words, j, i)) {
                    ret.push_back({j, i});
                }
            }
        }

        return ret;
    }
    bool IsPalindromePairs(vector<string> &words, int i, int j) {
        // pass

        string tmp = words[i] + words[j];

        int begin = 0;
        int end = tmp.size() - 1;

        while (begin < end) {
            if (tmp[begin] == tmp[end]) {
                begin++;
                end--;
            } else {
                return false;
            }
        }

        return true;
    }

   private:
    vector<vector<int>> res;
    struct TrieNode {
        TrieNode() : word_index(-1), children(26, nullptr) {}
        int word_index;
        vector<TrieNode *> children;
        ~TrieNode() {
            for (auto &ptr : children) {
                delete ptr;
            }
        }
    };

    void Insert(TrieNode *root, string &word, int word_index) {
        for (auto c : word) {
            const int index = c - 'a';
            if (root->children[index] == nullptr) {
                root->children[index] = new TrieNode();
            }
            root = root->children[index];
        }

        root->word_index = word_index;
    }

    bool IsPalindrome(const string &s) {
        int i = 0;
        int j = s.size() - 1;

        while (i < j) {
            if (s[i] != s[j]) {
                return false;
            }
            ++i;
            --j;
        }

        return true;
    }

    void Dfs(TrieNode *root, vector<int> &long_word_indices, string &str) {
        if (root == nullptr) {
            return;
        }

        // palindrome + reverse_word
        if (root->word_index != -1 && !str.empty() && IsPalindrome(str)) {
            long_word_indices.push_back(root->word_index);
        }

        for (int i = 0; i < 26; ++i) {
            str.push_back('a' + i);
            Dfs(root->children[i], long_word_indices, str);
            str.pop_back();
        }
    }

    void Find(TrieNode *root, string &word, int word_index) {
        // word is longer than its corresponding word.
        int index = 0;
        while (index < (int)word.length() && root != nullptr) {
            root = root->children[word[index++] - 'a'];
            if (root != nullptr && root->word_index != -1) {
                if (root->word_index != word_index &&
                    IsPalindrome(word.substr(index))) {
                    res.push_back({word_index, root->word_index});
                }
            }
        }

        // word is shorter than its corresponding word.
        if (index == (int)word.length()) {
            string str;
            vector<int> long_word_indices;
            Dfs(root, long_word_indices, str);
            for (const int i : long_word_indices) {
                res.push_back({word_index, i});
            }
        }
    }

   public:
    vector<vector<int>> PalindromePairsV1(vector<string> &words) {
        TrieNode *root = new TrieNode();

        // Create Trie with reversed words
        for (int i = 0; i < (int)words.size(); ++i) {
            string reversed_word = words[i];
            reverse(reversed_word.begin(), reversed_word.end());
            Insert(root, reversed_word, i);
        }

        for (int i = 0; i < (int)words.size(); ++i) {
            string &word = words[i];
            // word is palindrome
            if (root->word_index != -1 && !word.empty() && IsPalindrome(word)) {
                res.push_back({i, root->word_index});
            }
            Find(root, word, i);
        }

        delete root;
        return res;
    }

   private:
    bool CheckPalindrome(string &s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }

   public:
    vector<vector<int>> PalindromePairsV2(vector<string> &words) {
        unordered_map<string, int> rev;
        string temp;

        const int n = words.size();

        for (int i = 0; i < n; i++) {
            temp = words[i];
            reverse(temp.begin(), temp.end());

            rev[temp] = i;
        }

        vector<vector<int>> ans;

        if (rev.find("") != rev.end()) {
            for (int i = 0; i < n; i++) {
                if (rev[""] == i) {
                    continue;
                }

                if (CheckPalindrome(words[i])) {
                    ans.push_back({i, rev[""]});
                }
            }
        }

        string left, right, word;

        for (int i = 0; i < n; i++) {
            word = words[i];

            left = "";
            right = word;

            const int sz = word.size();

            for (int j = 0; j < sz; j++) {
                left.push_back(word[j]);
                right.erase(0, 1);

                if (rev.find(left) != rev.end() && rev[left] != i &&
                    CheckPalindrome(right)) {
                    ans.push_back({i, rev[left]});
                }

                if (rev.find(right) != rev.end() && rev[right] != i &&
                    CheckPalindrome(left)) {
                    ans.push_back({rev[right], i});
                }
            }
        }

        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<string> words = {"abcd", "dcba", "lls", "s", "sssll"};
    vector<vector<int>> output = {{0, 1}, {1, 0}, {3, 2}, {2, 4}};
    // Explanation: The palindromes are
    // ["dcbaabcd","abcddcba","slls","llssssll"]

    const set<vector<int>> output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PalindromePairs(words);

    const set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
    ret = sl.PalindromePairsV1(words);

    const set<vector<int>> ret_set1(ret.begin(), ret.end());
    EXPECT_EQ(ret_set1, output_set);
    ret = sl.PalindromePairsV1(words);

    const set<vector<int>> ret_set2(ret.begin(), ret.end());
    EXPECT_EQ(ret_set2, output_set);
}

TEST(t0, t2) {
    vector<string> words = {"bat", "tab", "cat"};
    vector<vector<int>> output = {{0, 1}, {1, 0}};
    // Explanation: The palindromes are
    // The palindromes are ["battab","tabbat"]

    const set<vector<int>> output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PalindromePairs(words);

    const set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
    ret = sl.PalindromePairsV1(words);

    const set<vector<int>> ret_set1(ret.begin(), ret.end());
    EXPECT_EQ(ret_set1, output_set);
    ret = sl.PalindromePairsV1(words);

    const set<vector<int>> ret_set2(ret.begin(), ret.end());
    EXPECT_EQ(ret_set2, output_set);
}

}
