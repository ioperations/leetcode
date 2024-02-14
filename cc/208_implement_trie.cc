// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A trie (pronounced as "try") or prefix tree is a tree data structure used to
efficiently store and retrieve keys in a dataset of strings. There are various
applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie
(i.e., was inserted before), and false otherwise. boolean startsWith(String
prefix) Returns true if there is a previously inserted string word that has the
prefix prefix, and false otherwise.*/

#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

namespace {

class Trie {
   private:
    class TrieNode {
       public:
        vector<TrieNode *> child;
        bool is_end;
        TrieNode() {
            child.resize(26, NULL);
            is_end = false;
        }
        ~TrieNode() { child.clear(); }
    };
    TrieNode *root;

    void DeleteTrieNode(TrieNode *root) {
        if (root != nullptr) {
            for (auto &ptr : root->child) {
                DeleteTrieNode(ptr);
            }
            delete root;
        }
    }

   public:
    Trie() { root = new TrieNode(); }
    ~Trie() { DeleteTrieNode(root); }

    void Insert(string word) {
        TrieNode *c = root;
        for (auto x : word) {
            if (c->child[x - 'a'] == NULL) {
                c->child[x - 'a'] = new TrieNode();
            }
            c = c->child[x - 'a'];
        }
        c->is_end = true;
    }

    bool Search(string word) {
        TrieNode *c = root;
        for (auto x : word) {
            if (c->child[x - 'a'] == NULL) {
                return false;
            }
            c = c->child[x - 'a'];
        }
        return c->is_end;
    }

    bool StartsWith(string prefix) {
        TrieNode *c = root;
        for (auto x : prefix) {
            if (c->child[x - 'a'] == NULL) {
                return false;
            }
            c = c->child[x - 'a'];
        }

        return true;
    }
};

class TrieV1 {
    // 1 <= word.length, prefix.length <= 2000
    // word and prefix consist only of lowercase English letters.
    // At most 3 * 104 calls in total will be made to insert, search, and
    // startsWith.

    struct Tree {
        std::map<char, Tree> map;
        bool end;
        ~Tree() { map.clear(); }
    };

    Tree root;

   public:
    TrieV1() {}

    void Insert(string word) {
        // pass
        Tree *z = &root;
        for (int i = 0; i < (int)word.size(); i++) {
            auto &t = z->map[word[i]];
            z = &t;
        }
        z->end = true;
    }

    bool Search(string word) {
        Tree *z = &root;
        for (int i = 0; i < (int)word.size(); i++) {
            auto t = z->map.find(word[i]);
            if (t != z->map.end()) {
                auto &t = z->map[word[i]];
                z = &t;
            } else {
                return false;
            }
        }
        return z->end;
    }

    bool StartsWith(string prefix) {
        Tree *z = &root;
        for (int i = 0; i < (int)prefix.size(); i++) {
            auto t = z->map.find(prefix[i]);
            if (t != z->map.end()) {
                auto &t = z->map[prefix[i]];
                z = &t;
            } else {
                return false;
            }
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    //    ["Trie", "insert", "search", "search", "startsWith", "insert",
    //    "search"]
    //    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    //    Output [null, null, true, false, true, null, true]

    bool ret;
    Trie *trie = new Trie();
    trie->Insert("apple");
    ret = trie->Search("apple");  // return True
    EXPECT_EQ(ret, true);
    ret = trie->Search("app");  // return False
    EXPECT_EQ(ret, false);
    ret = trie->StartsWith("app");  // return True
    EXPECT_EQ(ret, true);
    trie->Insert("app");
    ret = trie->Search("app");  // return True
    EXPECT_EQ(ret, true);
    delete trie;
}

TEST(t1, t1) {
    //    ["Trie", "insert", "search", "search", "startsWith", "insert",
    //    "search"]
    //    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    //    Output [null, null, true, false, true, null, true]

    bool ret;
    TrieV1 *trie = new TrieV1();
    trie->Insert("apple");
    ret = trie->Search("apple");  // return True

    EXPECT_EQ(ret, true);
    ret = trie->StartsWith("purp");
    EXPECT_EQ(ret, false);
    trie->Insert("purple");

    ret = trie->Search("app");  // return False
    EXPECT_EQ(ret, false);
    ret = trie->StartsWith("app");  // return True
    EXPECT_EQ(ret, true);
    trie->Insert("app");
    ret = trie->Search("app");  // return True
    EXPECT_EQ(ret, true);
    delete trie;
}

void BenchMarkOther(benchmark::State &state) {
    for (auto _ : state) {
        bool ret;
        Trie *trie = new Trie();
        trie->Insert("apple");
        ret = trie->Search("apple");  // return True
        EXPECT_EQ(ret, true);
        ret = trie->Search("app");  // return False
        EXPECT_EQ(ret, false);
        ret = trie->StartsWith("app");  // return True
        EXPECT_EQ(ret, true);
        trie->Insert("app");
        ret = trie->Search("app");  // return True
        EXPECT_EQ(ret, true);
        delete trie;
    }
}
BENCHMARK(BenchMarkOther);

void BenchMarkMyImpl(benchmark::State &state) {
    for (auto _ : state) {
        bool ret;
        TrieV1 *trie = new TrieV1();
        trie->Insert("apple");
        ret = trie->Search("apple");  // return True
        EXPECT_EQ(ret, true);
        ret = trie->Search("app");  // return False
        EXPECT_EQ(ret, false);
        ret = trie->StartsWith("app");  // return True
        EXPECT_EQ(ret, true);
        trie->Insert("app");
        ret = trie->Search("app");  // return True
        EXPECT_EQ(ret, true);
        delete trie;
    }
}
BENCHMARK(BenchMarkMyImpl);

}  // namespace
