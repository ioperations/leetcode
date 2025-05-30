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

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {

class Trie {
   private:
    class TrieNode {
       public:
        vector<TrieNode*> m_child;
        bool m_is_end{false};
        TrieNode() { m_child.resize(26, nullptr); }
        ~TrieNode() { m_child.clear(); }
    };
    TrieNode* m_root;

    void DeleteTrieNode(TrieNode* root) {
        if (root != nullptr) {
            for (auto& ptr : root->m_child) {
                DeleteTrieNode(ptr);
            }
            delete root;
        }
    }

   public:
    Trie() : m_root(new TrieNode()) {}
    ~Trie() { DeleteTrieNode(m_root); }

    void Insert(string word) {
        TrieNode* c = m_root;
        for (auto x : word) {
            if (c->m_child[x - 'a'] == nullptr) {
                c->m_child[x - 'a'] = new TrieNode();
            }
            c = c->m_child[x - 'a'];
        }
        c->m_is_end = true;
    }

    bool Search(string word) {
        TrieNode* c = m_root;
        for (auto x : word) {
            if (c->m_child[x - 'a'] == nullptr) {
                return false;
            }
            c = c->m_child[x - 'a'];
        }
        return c->m_is_end;
    }

    bool StartsWith(string prefix) {
        TrieNode* c = m_root;
        for (auto x : prefix) {
            if (c->m_child[x - 'a'] == nullptr) {
                return false;
            }
            c = c->m_child[x - 'a'];
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
        std::map<char, Tree> m_map;
        bool m_end{};
        ~Tree() { m_map.clear(); }
    };

    Tree m_root;

   public:
    TrieV1() = default;

    void Insert(string word) {
        // pass
        Tree* z = &m_root;
        for (char const i : word) {
            auto& t = z->m_map[i];
            z = &t;
        }
        z->m_end = true;
    }

    bool Search(string word) {
        Tree* z = &m_root;
        for (char const i : word) {
            auto t = z->m_map.find(i);
            if (t != z->m_map.end()) {
                auto& t = z->m_map[i];
                z = &t;
            } else {
                return false;
            }
        }
        return z->m_end;
    }

    bool StartsWith(string prefix) {
        Tree* z = &m_root;
        for (char const i : prefix) {
            auto t = z->m_map.find(i);
            if (t != z->m_map.end()) {
                auto& t = z->m_map[i];
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

TEST(implement_trie, t1) {
    //    ["Trie", "insert", "search", "search", "startsWith", "insert",
    //    "search"]
    //    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    //    Output [null, null, true, false, true, null, true]

    bool ret = false;
    Trie* trie = new Trie();
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

TEST(implement_trie_v2, t1) {
    //    ["Trie", "insert", "search", "search", "startsWith", "insert",
    //    "search"]
    //    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    //    Output [null, null, true, false, true, null, true]

    bool ret = false;
    auto* trie = new TrieV1();
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

void BenchMarkOther(benchmark::State& state) {
    for (auto _ : state) {
        bool ret = false;
        Trie* trie = new Trie();
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

void BenchMarkMyImpl(benchmark::State& state) {
    for (auto _ : state) {
        bool ret = false;
        auto* trie = new TrieV1();
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
