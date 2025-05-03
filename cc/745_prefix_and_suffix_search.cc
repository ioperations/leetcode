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

#include <cstddef>

namespace {
class Trie {
   public:
    struct Node {
       public:
        Node* child[27];
        int m_end_idx;

       public:
        bool Contains(char& ch) { return (child[ch - 'a'] != nullptr); }

        void PutNode(char& ch, Node* new_node) { child[ch - 'a'] = new_node; }

        Node* GetNext(char& ch) { return child[ch - 'a']; }

        void SetIdx(int& i) { m_end_idx = i; }

        int GetIdx() { return m_end_idx; }
    };

    Node* root;
    void DeleteNode(Node* n) {
        if (n == nullptr) return;
        for (auto& i : n->child) {
            DeleteNode(i);
        }
        delete n;
    }

   public:
    Trie() : root(new Node()) {}

    ~Trie() { DeleteNode(root); }

    void Insert(string& word, int& idx) {
        Node* temp = root;

        for (auto& ch : word) {
            if (!temp->Contains(ch)) {
                temp->PutNode(ch, new Node());
            }

            temp = temp->GetNext(ch);
            temp->SetIdx(idx);
        }
    }

    int StartsWith(string& word) {
        Node* temp = root;

        for (auto& ch : word) {
            if (!temp->Contains(ch)) {
                return -1;
            }

            temp = temp->GetNext(ch);
        }

        return temp->GetIdx();
    }
};

class WordFilter {
    Trie m_trie;

   public:
    WordFilter(vector<string>& words) {
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
        int const len = words.size();
        for (int i = 0; i < len; i++) {
            string const str = words[i];
            int const n = str.size();

            for (int j = 0; j <= n; j++) {
                string cur = str.substr(j) + '{' + str;

                m_trie.Insert(cur, i);
            }
        }
    }

    int F(string prefix, string suffix) {
        string cur = suffix + '{' + prefix;

        // just use startswith function and pass suffix + '{' + prefix to find
        // index

        return m_trie.StartsWith(cur);
    }
};

class WordFilterMy {
    struct Pp {
        string m_s;
        int m_index;
    };

    class PrefixTree {
       public:
        std::vector<Pp> m_n;
        std::map<char, PrefixTree> m_node;
        PrefixTree() = default;
        ~PrefixTree() {
            m_node.clear();
            m_n.clear();
        }
    };

    PrefixTree m_root;

   public:
    WordFilterMy(vector<string>& words) {
        // 应该是先有一个前缀树
        // 指向一个新的前缀树，前缀树中的节点是一个链表,
        // 在真正构建的时候可以覆盖，后面的index覆盖前面的index，
        // 第一个前缀树当中还需要保留链表，
        int const size = words.size();
        for (int i = 0; i < size; i++) {
            PrefixTree* z = &m_root;
            string const tmp = words[i];
            reverse(words[i].begin(), words[i].end());

            for (auto& ptr : tmp) {
                z = &z->m_node[ptr];
                z->m_n.push_back(Pp{words[i], i});
            }
        }
    }

    int F(string prefix, string suffix) {
        // pass
        PrefixTree* z = &m_root;
        for (auto& ptr : prefix) {
            if (z->m_node.find(ptr) != z->m_node.end()) {
                z = &z->m_node[ptr];
            } else {
                return -1;
            }
        }
        int max = -1;

        int const suffix_size = suffix.size();
        reverse(suffix.begin(), suffix.end());
        for (auto& ptr : z->m_n) {
            if ((int)ptr.m_s.size() >= suffix_size) {
                if (ptr.m_s.substr(0, suffix_size) == suffix) {
                    max = std::max(max, ptr.m_index);
                }
            }
        }

        return max;
    }
};

TEST(prefix_and_suffix_search, t1) {
    std::vector<string> words{"apple"};
    WordFilter obj(words);
    int const ret = obj.F("a", "e");
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
