// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a n-ary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root
node down to the farthest leaf node.

Nary-Tree input serialization is represented in their level order traversal,
each group of children is separated by the null value (See examples).

*/

#include <algorithm>
#include <functional>
#include <optional>
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
    int MaxDepth(Node *root) {
        function<int(Node *)> fun = [&](Node *node) -> int {
            if (node == nullptr) return 0;
            int ret = 0;
            for (auto &ptr : node->m_children) {
                ret = max(ret, fun(ptr));
            }

            return ret + 1;
        };

        return fun(root);
    }
};

#define null \
    optional<int> {}

vector<Node *> ConstructTreeNode(Node *z1, vector<int> &z) {
    for (auto &ptr : z) {
        Node *ptrn = new Node(ptr);
        z1->m_children.push_back(ptrn);
    }
    return z1->m_children;
}

Node *ConstructTreeNode(vector<optional<int>> &elements) {
    const Node n;
    if (elements.size() == 0) {
        return nullptr;
    }
    Node *ptr = new Node(elements[0].value());
    queue<Node *> q;
    q.push(ptr);

    bool continue_loop = true;
    int i = 2;
    const int size = elements.size();
    while (continue_loop) {
        vector<int> z;
        while (i < size && elements[i].has_value()) {
            z.push_back(elements[i].value());
            i++;
        }
        Node *z1 = q.front();
        const vector<Node *> ret = ConstructTreeNode(z1, z);
        for (auto &ptr : ret) {
            q.push(ptr);
        }
        q.pop();
        i++;
        if (i >= (int)elements.size()) continue_loop = false;
    }

    return ptr;
}

void FreeNode(Node *n) {
    if (n == nullptr) {
        return;
    }
    for (auto &ptr : n->m_children) {
        FreeNode(ptr);
    }
    delete n;
}

TEST(memleak, t1) {
    vector<optional<int>> z{1, optional<int>{}, 3, 2, 4, optional<int>{}, 5, 6};
    Node *n = ConstructTreeNode(z);
    FreeNode(n);
}

TEST(maximum_depth_of_n_ary_tree, t1) {
    vector<optional<int>> z{1, optional<int>{}, 3, 2, 4, optional<int>{}, 5, 6};
    Node *n = ConstructTreeNode(z);
    const int output = 3;
    Solution sl;
    const int ret = sl.MaxDepth(n);
    EXPECT_EQ(ret, output);
    FreeNode(n);
}

TEST(maximum_depth_of_n_ary_tree, t2) {
    vector<optional<int>> z{1,    null, 2,    3,    4,    5,    null, null, 6,
                            7,    null, 8,    null, 9,    10,   null, null, 11,
                            null, 12,   null, 13,   null, null, 14};
    Node *n = ConstructTreeNode(z);
    Solution sl;
    const int output = 5;
    const int ret = sl.MaxDepth(n);
    EXPECT_EQ(ret, output);
    FreeNode(n);
}

}  // namespace
