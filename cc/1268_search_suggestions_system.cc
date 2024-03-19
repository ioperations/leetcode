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
    class Trie {
       public:
        std::map<char, Trie> ndoe;
        vector<int> index_array;
        ~Trie() {
            ndoe.clear();
            index_array.clear();
        }
    };
    Trie root;
    vector<string> m_product;

   public:
    vector<vector<string>> SuggestedProducts(const vector<string> &products,
                                             string search_word) {
        m_product = products;
        sort(m_product.begin(), m_product.end());
        Build();
        vector<vector<string>> ret;
        for (int i = 0; i < (int)search_word.size(); i++) {
            vector<string> tmp = Search(search_word.substr(0, i + 1));
            ret.push_back(tmp);
        }
        return ret;
    }

    vector<string> Search(const string &pattern) {
        Trie *z = &root;
        for (auto &ptr : pattern) {
            if (z->ndoe.find(ptr) != z->ndoe.end()) {
                z = &z->ndoe[ptr];
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
            Trie *t = &root;
            for (auto &ptr : m_product[i]) {
                t = &t->ndoe[ptr];
                t->index_array.push_back(i);
            }
        }
    }
};

class SolutionV2 {
    class TrieNode {
       public:
        TrieNode *links[26];
        vector<int> idx;
    };

    class Trie {
        TrieNode *root;

       private:
        void DeleteNode(TrieNode *root) {
            if (root == nullptr) return;
            for (int i = 0; i < 26; i++) {
                DeleteNode(root->links[i]);
            }
            delete root;
        }

       public:
        Trie() { root = new TrieNode(); }
        ~Trie() { DeleteNode(root); }

        void Insert(const string &s, int id) {
            TrieNode *node = root;
            for (auto &ch : s) {
                if (!node->links[ch - 'a'])
                    node->links[ch - 'a'] = new TrieNode();

                node = node->links[ch - 'a'];
                node->idx.push_back(id);
            }
        }

        vector<int> Search(const string &s) {
            TrieNode *node = root;
            for (int i = 0; i < (int)s.length(); i++) {
                if (!node->links[s[i] - 'a']) return {};
                node = node->links[s[i] - 'a'];
            }
            return node->idx;
        }
    };

   public:
    vector<vector<string>> SuggestedProducts(vector<string> &products,
                                             const string &search_word) {
        Trie trie;
        sort(products.begin(), products.end());
        for (int i = 0; i < (int)products.size(); i++) {
            trie.Insert(products[i], i);
        }

        string s;
        int len = search_word.length();
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
    vector<string> products = {"mobile", "mouse", "moneypot", "monitor",
                               "mousepad"};
    string search_word = "mouse";

    Solution sl;
    vector<vector<string>> out{{"mobile", "moneypot", "monitor"},
                               {"mobile", "moneypot", "monitor"},
                               {"mouse", "mousepad"},
                               {"mouse", "mousepad"},
                               {"mouse", "mousepad"}};
    vector<vector<string>> ret = sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system, t2) {
    vector<string> products = {"havana"};
    string search_word = "havana";

    Solution sl;
    vector<vector<string>> out{
        {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"},
    };
    vector<vector<string>> ret = sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system, t3) {
    vector<string> products = {"bags", "baggage", "banner", "box", "cloths"};
    string search_word = "bags";

    Solution sl;
    vector<vector<string>> out{{"baggage", "bags", "banner"},
                               {"baggage", "bags", "banner"},
                               {"baggage", "bags"},
                               {"bags"}};
    vector<vector<string>> ret = sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system_v2, t1) {
    vector<string> products = {"mobile", "mouse", "moneypot", "monitor",
                               "mousepad"};
    string search_word = "mouse";

    SolutionV2 sl;
    vector<vector<string>> out{{"mobile", "moneypot", "monitor"},
                               {"mobile", "moneypot", "monitor"},
                               {"mouse", "mousepad"},
                               {"mouse", "mousepad"},
                               {"mouse", "mousepad"}};
    vector<vector<string>> ret = sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system_v2, t2) {
    vector<string> products = {"havana"};
    string search_word = "havana";

    SolutionV2 sl;
    vector<vector<string>> out{
        {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"},
    };
    vector<vector<string>> ret = sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}

TEST(search_suggestions_system_v2, t3) {
    vector<string> products = {"bags", "baggage", "banner", "box", "cloths"};
    string search_word = "bags";

    SolutionV2 sl;
    vector<vector<string>> out{{"baggage", "bags", "banner"},
                               {"baggage", "bags", "banner"},
                               {"baggage", "bags"},
                               {"bags"}};
    vector<vector<string>> ret = sl.SuggestedProducts(products, search_word);
    EXPECT_EQ(ret, out);
}
}  // namespace
