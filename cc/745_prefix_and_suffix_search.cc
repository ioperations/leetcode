// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Design a special dictionary with some words that searchs the words in it by a
prefix and a suffix.

Implement the WordFilter class:

WordFilter(string[] words) Initializes the object with the words in the
dictionary. f(string prefix, string suffix) Returns the index of the word in the
dictionary, which has the prefix prefix and the suffix suffix. If there is more
than one valid index, return the largest of them. If there is no such word in
the dictionary, return -1.
*/

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

#include <stddef.h>

namespace {
class Trie {
   public:
    struct Node {
       public:
        Node *child[27];
        int end_idx;

       public:
        bool Contains(char &ch) { return (child[ch - 'a'] != NULL); }

        void PutNode(char &ch, Node *new_node) { child[ch - 'a'] = new_node; }

        Node *GetNext(char &ch) { return child[ch - 'a']; }

        void SetIdx(int &i) { end_idx = i; }

        int GetIdx() { return end_idx; }
    };

    Node *root;
    void DeleteNode(Node *n) {
        if (n == nullptr) return;
        for (int i = 0; i < 27; i++) {
            DeleteNode(n->child[i]);
        }
        delete n;
    }

   public:
    Trie() { root = new Node(); }

    ~Trie() { DeleteNode(root); }

    void Insert(string &word, int &idx) {
        Node *temp = root;

        for (auto &ch : word) {
            if (!temp->Contains(ch)) {
                temp->PutNode(ch, new Node());
            }

            temp = temp->GetNext(ch);
            temp->SetIdx(idx);
        }
    }

    int StartsWith(string &word) {
        Node *temp = root;

        for (auto &ch : word) {
            if (!temp->Contains(ch)) {
                return -1;
            }

            temp = temp->GetNext(ch);
        }

        return temp->GetIdx();
    }
};

class WordFilter {
    Trie trie;

   public:
    WordFilter(vector<string> &words) {
        /*

        We are storing word as suffix + '{' + prefix, index
        why '{' ? you can use any special character, but '{' - 'a' will give
        26th index so, we don't need to take care of special character.

        apple -> suffix + '{' + prefix, i
            apple{apple 0
            pple{apple 0
            ple{apple 0
            le{apple 0
            e{apple 0
            {apple 0


        */
        int len = words.size();
        for (int i = 0; i < len; i++) {
            string str = words[i];
            int n = str.size();

            for (int j = 0; j <= n; j++) {
                string cur = str.substr(j) + '{' + str;

                trie.Insert(cur, i);
            }
        }
    }

    int F(string prefix, string suffix) {
        string cur = suffix + '{' + prefix;

        // just use startswith function and pass suffix + '{' + prefix to find
        // index

        return trie.StartsWith(cur);
    }
};

class WordFilterMy {
    struct Pp {
        string s;
        int index;
    };

    class PrefixTree {
       public:
        std::vector<Pp> n;
        std::map<char, PrefixTree> node;
        PrefixTree() {}
        ~PrefixTree() {
            node.clear();
            n.clear();
        }
    };

    PrefixTree root;

   public:
    WordFilterMy(vector<string> &words) {
        // 应该是先有一个前缀树
        // 指向一个新的前缀树，前缀树中的节点是一个链表,
        // 在真正构建的时候可以覆盖，后面的index覆盖前面的index，
        // 第一个前缀树当中还需要保留链表，
        int size = words.size();
        for (int i = 0; i < size; i++) {
            PrefixTree *z = &root;
            string tmp = words[i];
            reverse(words[i].begin(), words[i].end());

            for (auto &ptr : tmp) {
                z = &z->node[ptr];
                z->n.push_back(Pp{words[i], i});
            }
        }
    }

    int F(string prefix, string suffix) {
        // pass
        PrefixTree *z = &root;
        for (auto &ptr : prefix) {
            if (z->node.find(ptr) != z->node.end()) {
                z = &z->node[ptr];
            } else {
                return -1;
            }
        }
        int max = -1;

        int suffix_size = suffix.size();
        reverse(suffix.begin(), suffix.end());
        for (auto &ptr : z->n) {
            if ((int)ptr.s.size() >= suffix_size) {
                if (ptr.s.substr(0, suffix_size) == suffix) {
                    max = std::max(max, ptr.index);
                }
            }
        }

        return max;
    }
};

TEST(prefix_and_suffix_search, t1) {
    std::vector<string> words{"apple"};
    WordFilter obj(words);
    int ret = obj.F("a", "e");
    EXPECT_EQ(ret, 0);
}

TEST(prefix_and_suffix_search, t2) {
    std::vector<string> words{
        "cabaabaaaa", "ccbcababac", "bacaabccba", "bcbbcbacaa", "abcaccbcaa",
        "accabaccaa", "cabcbbbcca", "ababccabcb", "caccbbcbab", "bccbacbcba"};
    // ["WordFilter","f","f","f","f","f","f","f","f","f","f"]
    WordFilter obj(words);

    int ret = obj.F("bccbacbcba", "a");
    EXPECT_EQ(ret, 9);

    ret = obj.F("ab", "abcaccbcaa");
    EXPECT_EQ(ret, 4);
    ret = obj.F("a", "aa");
    EXPECT_EQ(ret, 5);
    ret = obj.F("cabaaba", "abaaaa");
    EXPECT_EQ(ret, 0);
    ret = obj.F("cacc", "accbbcbab");
    EXPECT_EQ(ret, 8);
    ret = obj.F("ccbcab", "bac");
    EXPECT_EQ(ret, 1);
    ret = obj.F("bac", "cba");
    EXPECT_EQ(ret, 2);
    ret = obj.F("ac", "accabaccaa");
    EXPECT_EQ(ret, 5);
    ret = obj.F("bcbb", "aa");
    EXPECT_EQ(ret, 3);
    ret = obj.F("ccbca", "cbcababac");
    EXPECT_EQ(ret, 1);
}

}  // namespace
