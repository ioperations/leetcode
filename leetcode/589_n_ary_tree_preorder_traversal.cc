// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of an n-ary tree, return the preorder traversal of its nodes'
values.

Nary-Tree input serialization is represented in their level order traversal.
Each group of children is separated by the null value (See examples)*/

// Definition for a Node.
#include <vector>

using namespace std;
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
#include <stack>
#include <unordered_set>

class Solution {
   public:
    vector<int> Preorder(Node *root) {
        vector<int> v;
        if (!root) return v;
        stack<Node *> st;
        st.push(root);
        while (!st.empty()) {
            Node *node = st.top();
            st.pop();
            v.push_back(node->m_val);
            for (int i = (node->m_children.size()) - 1; i >= 0; i--) {
                st.push(node->m_children[i]);
            }
        }
        return v;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>

Node *ConstructNode(vector<optional<int>> &elements) {
    Node *node = nullptr;
    int size = elements.size();
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

TEST(t0, t1) {
#define null \
    optional<int> {}
    vector<optional<int>> root = {1, null, 3, 2, 4, null, 5, 6};

    Node *tree = ConstructNode(root);
    std::vector<int> output{1, 3, 5, 6, 2, 4};
    Solution sl;
    auto ret = sl.Preorder(tree);
    EXPECT_EQ(ret, output);

    FreeNode(tree);
}

TEST(t0, t2) {
#define null \
    optional<int> {}
    vector<optional<int>> root = {
        1, null, 2,    3,    4,  5,    null, null, 6,  7,    null, 8, null,
        9, 10,   null, null, 11, null, 12,   null, 13, null, null, 14};

    Node *tree = ConstructNode(root);
    std::vector<int> output{1, 2, 3, 6, 7, 11, 14, 4, 8, 12, 5, 9, 13, 10};
    Solution sl;
    auto ret = sl.Preorder(tree);
    EXPECT_EQ(ret, output);

    FreeNode(tree);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
