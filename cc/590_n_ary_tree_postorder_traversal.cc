// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the root of an n-ary tree, return the postorder traversal of its nodes'
values.

Nary-Tree input serialization is represented in their level order traversal.
Each group of children is separated by the null value (See examples)


*/

#include <optional>
#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Node {
   public:
    int m_val{};
    vector<Node*> m_children;

    Node() = default;

    Node(int i_val) : m_val(i_val) {}

    Node(int i_val, vector<Node*> i_children)
        : m_val(i_val), m_children(std::move(i_children)) {}
};

class Solution {
   public:
    vector<int> Postorder(Node* root) {
        vector<int> ret;
        Postorder(root, ret);
        return ret;
    }

    void Postorder(Node* root, std::vector<int>& ret) {
        if (root == nullptr) return;
        for (auto& ptr : root->m_children) {
            Postorder(ptr, ret);
        }
        ret.push_back(root->m_val);
    }
};

vector<Node*> ConstructTreeNode(Node* z1, vector<int>& z) {
    for (auto& ptr : z) {
        Node* ptrn = new Node(ptr);
        z1->m_children.push_back(ptrn);
    }
    return z1->m_children;
}

Node* ConstructTreeNode(vector<optional<int>>& elements) {
    const Node n;
    if (elements.size() == 0) {
        return nullptr;
    }
    Node* ptr = new Node(elements[0].value());
    queue<Node*> q;
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
        Node* z1 = q.front();
        const vector<Node*> ret = ConstructTreeNode(z1, z);
        for (auto& ptr : ret) {
            q.push(ptr);
        }
        q.pop();
        i++;
        if (i >= (int)elements.size()) continue_loop = false;
    }

    return ptr;
}

void FreeNode(Node* n) {
    if (n == nullptr) {
        return;
    }
    for (auto& ptr : n->m_children) {
        FreeNode(ptr);
    }
    delete n;
}
TEST(n_ary_tree_postorder_traversal, t1) {
#define null optional<int>()

    vector<optional<int>> root = {1, null, 3, 2, 4, null, 5, 6};
    const vector<int> output = {5, 6, 3, 2, 4, 1};
    Solution sl;
    auto* tree = ConstructTreeNode(root);
    auto ret = sl.Postorder(tree);
    EXPECT_EQ(ret, output);
    FreeNode(tree);
}

TEST(n_ary_tree_postorder_traversal, t2) {
#define null optional<int>()

    vector<optional<int>> root = {
        1, null, 2,    3,    4,  5,    null, null, 6,  7,    null, 8, null,
        9, 10,   null, null, 11, null, 12,   null, 13, null, null, 14};

    const vector<int> output = {2, 6, 14, 11, 7, 3, 12, 8, 4, 13, 9, 10, 5, 1};
    Solution sl;
    auto* tree = ConstructTreeNode(root);
    auto ret = sl.Postorder(tree);
    EXPECT_EQ(ret, output);
    FreeNode(tree);
}

}  // namespace
