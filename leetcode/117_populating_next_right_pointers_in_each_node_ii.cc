// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a binary tree

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node. If there is no next
right node, the next pointer should be set to nullptr.

Initially, all next pointers are set to nullptr.*/

// Definition for a Node.
class Node {
   public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int val) : val(val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int val, Node *left, Node *right, Node *next)
        : val(val), left(left), right(right), next(next) {}
};

class Solution {
   public:
    Node *Connect(Node *root) {
        Node n;
        Node *start = &n;
        Node *node_child = start;
        Node *node = root;

        while (node != nullptr) {
            while (node != nullptr) {  // Connect node child
                if (node->left != nullptr) {
                    node_child->next = node->left;
                    node_child = node_child->next;
                }
                if (node->right != nullptr) {
                    node_child->next = node->right;
                    node_child = node_child->next;
                }
                node = node->next;
            }
            node = start->next;
            start->next = nullptr;
            node_child = start;
        }
        return root;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
