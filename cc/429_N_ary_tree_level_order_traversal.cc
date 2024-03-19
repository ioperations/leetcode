// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an n-ary tree, return the level order traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal,
each group of children is separated by the null value (See examples).*/

#include <queue>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Node {
   public:
    int m_val;
    vector<Node *> m_children;

    Node() {}

    Node(int val) { m_val = val; }

    Node(int val, vector<Node *> children) {
        m_val = val;
        m_children = children;
    }
};

class Solution {
   public:
    vector<vector<int>> LevelOrder(Node *root) {
        vector<vector<int>> ret;

        if (root == nullptr) return ret;

        struct Status {
            Node *n;
            int level;
        };

        queue<Status> q;

        int cur_level = 1;
        q.push({root, 1});

        vector<int> tmp_vec;
        while (q.size()) {
            const Status tmp = q.front();
            if (tmp.level == cur_level) {
                tmp_vec.push_back(tmp.n->m_val);
            } else {
                ret.push_back(tmp_vec);
                tmp_vec.clear();
                tmp_vec.push_back(tmp.n->m_val);
                cur_level++;
            }
            for (auto &ptr : tmp.n->m_children) {
                q.push({ptr, cur_level + 1});
            }
            q.pop();
        }

        if (tmp_vec.size()) ret.push_back(tmp_vec);
        return ret;
    }
};

#include <optional>

Node *ConstructNode(vector<optional<int>> &elements) {
    Node *node = nullptr;
    const int size = elements.size();
    elements.resize(size * 3 + 31);
    if (size == 0) return nullptr;

    if (!elements[0].has_value()) return nullptr;
    queue<Node *> q;

    node = new Node(elements[0].value());
    q.push(node);

    int index = 2;
    while (index < size) {
        // todo

        Node *tmp = q.front();
        while (index < size && elements[index].has_value()) {
            Node *local_tmp = new Node(elements[index].value());
            tmp->m_children.push_back(local_tmp);
            q.push(local_tmp);
            index++;
        }
        index++;
        q.pop();
    }
    return node;
}

void FreeNode(Node *n) {
    if (n == nullptr) return;

    for (auto &ptr : n->m_children) {
        FreeNode(ptr);
    }

    delete n;
}

TEST(N_ary_tree_level_order_traversal, t1) {
#define null \
    optional<int> {}
    vector<optional<int>> root = {1, null, 3, 2, 4, null, 5, 6};
    const vector<vector<int>> output = {{1}, {3, 2, 4}, {5, 6}};

    Node *tree = ConstructNode(root);
    Solution sl;
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeNode(tree);
}

TEST(N_ary_tree_level_order_traversal, t2) {
#define null \
    optional<int> {}
    vector<optional<int>> root = {
        1, null, 2,    3,    4,  5,    null, null, 6,  7,    null, 8, null,
        9, 10,   null, null, 11, null, 12,   null, 13, null, null, 14};

    const vector<vector<int>> output = {
        {1}, {2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13}, {14}};

    Node *tree = ConstructNode(root);
    Solution sl;
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeNode(tree);
}

}  // namespace
