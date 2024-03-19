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

#include <stddef.h>

#include <string>
#include <unordered_set>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
    // pass
    // we need to create a structure
   private:
    struct TrieNode {
        int ends_here;
        TrieNode *child[26];
    };

    // creates a node with character and returns it
    TrieNode *GetNode() {
        // index is 0-25 representing characters of alphabets
        TrieNode *new_node = new TrieNode;
        new_node->ends_here = 0;
        // initialize every child node ptr to NULL
        for (int i = 0; i < 26; i++) new_node->child[i] = NULL;
        return new_node;
    }

    void DeleteNode(TrieNode *root) {
        if (root == nullptr) return;
        for (int i = 0; i < 26; i++) {
            DeleteNode(root->child[i]);
        }
        delete root;
    }

   public:
    TrieNode *root;

    Solution() { root = GetNode(); }
    ~Solution() { DeleteNode(root); }

    int MinimumLengthEncoding(vector<string> &words) {
        // use set to avoid repetetion for duplicate words
        unordered_set<string> s;

        int count = 0;  // the number of words in the reference string
        // the number of words =  number of # to add in result string
        int res = 0;  // the total length of the result string
        for (int i = 0; i < (int)words.size(); i++) {
            if (s.count(words[i])) continue;
            s.insert(words[i]);
            Insert(words[i], count, res);
        }
        return res + count;
    }

    void Insert(string word, int &count, int &res) {
        TrieNode *curr = root;
        int len = word.length();
        bool flag = true;
        for (int i = len - 1; i >= 0; i--) {
            int ind = word[i] - 'a';
            if (curr->child[ind] == NULL) {
                flag = false;
                // if no word has created yet
                curr->child[ind] = GetNode();
            }
            // a word ends here previously
            // so donot consider it in the result
            if (curr->ends_here) {
                curr->ends_here = 0;
                count--;
                res -= (len - i - 1);
            }
            curr = curr->child[ind];
        }
        // flag will be true if some word previously has created all the
        // nodes ex- ["time","me"] for "me" the flag will be true so we dont
        // calculate the result
        if (!flag) {
            curr->ends_here = 1;
            count++;
            res += len;
        }
    }
};

TEST(short_encoding_of_words, t1) {
    vector<string> words = {"time", "me", "bell"};
    int output = 10;
    Solution sl;
    int ret = sl.MinimumLengthEncoding(words);
    /*A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
words[0] = "time", the substring of s starting from indices[0] = 0 to the next
'#' is underlined in "time#bell#" words[1] = "me", the substring of s starting
from indices[1] = 2 to the next '#' is underlined in "time#bell#" words[2] =
"bell", the substring of s starting from indices[2] = 5 to the next '#' is
underlined in "time#bell#"
    */
    EXPECT_EQ(ret, output);
}

TEST(short_encoding_of_words, t2) {
    vector<string> words = {"t"};
    int output = 2;
    Solution sl;
    int ret = sl.MinimumLengthEncoding(words);
    // A valid encoding would be s = "t#" and indices = [0].
    EXPECT_EQ(ret, output);
}

}  // namespace
