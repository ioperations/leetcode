// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an array of strings products and a string searchWord.

Design a system that suggests at most three product names from products after
each character of searchWord is typed. Suggested products should have common
prefix with searchWord. If there are more than three products with a common
prefix return the three lexicographically minimums products.

Return a list of lists of the suggested products after each character of
searchWord is typed.*/

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
    class Trie {
       public:
        std::map<char, Trie> m_ndoe;
        vector<int> index_array;
        ~Trie() {
            m_ndoe.clear();
            index_array.clear();
        }
    };
    Trie m_root;
    vector<string> m_product;

   public:
    vector<vector<string>> SuggestedProducts(const vector<string>& products,
                                             string search_word) {
        m_product = products;
        sort(m_product.begin(), m_product.end());
        Build();
        vector<vector<string>> ret;
        for (int i = 0; i < (int)search_word.size(); i++) {
            vector<string> const tmp = Search(search_word.substr(0, i + 1));
            ret.push_back(tmp);
        }
        return ret;
    }

    vector<string> Search(const string& pattern) {
        Trie* z = &m_root;
        for (auto& ptr : pattern) {
            if (z->m_ndoe.find(ptr) != z->m_ndoe.end()) {
                z = &z->m_ndoe[ptr];
            }
        }
#define b z->index_array
        if (z->index_array.size() >= 3) {
            return vector<string>{m_product[b[0]], m_product[b[1]],
                                  m_product[b[2]]};
        }
        if (z->index_array.size() == 2) {
            return vector<string>{m_product[b[0]], m_product[b[1]]};
        }

        if (z->index_array.size() == 1) {
            return vector<string>{m_product[b[0]]};
        }
#undef b
        return vector<string>{};
    }

    void Build() {
        for (int i = 0; i < (int)m_product.size(); i++) {
            Trie* t = &m_root;
            for (auto& ptr : m_product[i]) {
                t = &t->m_ndoe[ptr];
                t->index_array.push_back(i);
            }
        }
    }
};

class SolutionV2 {
    class TrieNode {
       public:
        TrieNode* m_links[26]{};
        vector<int> m_idx;
    };

    class Trie {
      TrieNode* m_root;

     private:
      void DeleteNode(TrieNode* root) {
        if (root == nullptr) return;
        for (auto& link : root->m_links) {
          DeleteNode(link);
        }
        delete root;
      }

       public:
        Trie() : m_root(new TrieNode()) {}
        ~Trie() { DeleteNode(m_root); }

        void Insert(const string& s, int id) {
          TrieNode* node = m_root;
          for (auto& ch : s) {
            if (!node->m_links[ch - 'a'])
              node->m_links[ch - 'a'] = new TrieNode();

            node = node->m_links[ch - 'a'];
            node->m_idx.push_back(id);
          }
        }

        vector<int> Search(const string& s) {
          TrieNode* node = m_root;
          for (int i = 0; i < (int)s.length(); i++) {
            if (!node->m_links[s[i] - 'a']) return {};
            node = node->m_links[s[i] - 'a'];
          }
            return node->m_idx;
        }
    };

   public:
    vector<vector<string>> SuggestedProducts(vector<string>& products,
                                             const string& search_word) {
        Trie trie;
        sort(products.begin(), products.end());
        for (int i = 0; i < (int)products.size(); i++) {
            trie.Insert(products[i], i);
        }

        string s;
        int const len = search_word.length();
        vector<vector<string>> res(len);

        for (int i = 0; i < (int)search_word.length(); i++) {
            s += search_word[i];
            vector<int> t = trie.Search(s);
            for (int j = 0; j < min(3, (int)t.size()); j++) {
                res[i].push_back(products[t[j]]);
            }
        }

        return res;
    }
};

TEST(search_suggestions_system, t1) {
    vector<string> const products = {"mobile", "mouse", "moneypot", "monitor",
                                     "mousepad"};
    string const search_word = "mouse";

    Solution sl;
    vector<vector<string>> const out{{"mobile", "moneypot", "monitor"},
                                     {"mobile", "moneypot", "monitor"},
                                     {"mouse", "mousepad"},
                                     {"mouse", "mousepad"},
                                     {"mouse", "mousepad"}};
    vector<vector<string>> const ret =
        sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system, t2) {
    vector<string> const products = {"havana"};
    string const search_word = "havana";

    Solution sl;
    vector<vector<string>> const out{
        {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"},
    };
    vector<vector<string>> const ret =
        sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system, t3) {
    vector<string> const products = {"bags", "baggage", "banner", "box",
                                     "cloths"};
    string const search_word = "bags";

    Solution sl;
    vector<vector<string>> const out{{"baggage", "bags", "banner"},
                                     {"baggage", "bags", "banner"},
                                     {"baggage", "bags"},
                                     {"bags"}};
    vector<vector<string>> const ret =
        sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system_v2, t1) {
    vector<string> products = {"mobile", "mouse", "moneypot", "monitor",
                               "mousepad"};
    string const search_word = "mouse";

    SolutionV2 sl;
    vector<vector<string>> const out{{"mobile", "moneypot", "monitor"},
                                     {"mobile", "moneypot", "monitor"},
                                     {"mouse", "mousepad"},
                                     {"mouse", "mousepad"},
                                     {"mouse", "mousepad"}};
    vector<vector<string>> const ret =
        sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system_v2, t2) {
    vector<string> products = {"havana"};
    string const search_word = "havana";

    SolutionV2 sl;
    vector<vector<string>> const out{
        {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"},
    };
    vector<vector<string>> const ret =
        sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system_v2, t3) {
    vector<string> products = {"bags", "baggage", "banner", "box", "cloths"};
    string const search_word = "bags";

    SolutionV2 sl;
    vector<vector<string>> const out{{"baggage", "bags", "banner"},
                                     {"baggage", "bags", "banner"},
                                     {"baggage", "bags"},
                                     {"bags"}};
    vector<vector<string>> const ret =
        sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}
}  // namespace
