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
#include "gtest/gtest.h"

namespace {
class Node {
   public:
    int m_val;
    Node* m_left;
    Node* m_right;
    Node* m_next;

    Node() : m_val(0), m_left(nullptr), m_right(nullptr), m_next(nullptr) {}

    Node(int val)
        : m_val(val), m_left(nullptr), m_right(nullptr), m_next(nullptr) {}

    Node(int val, Node* left, Node* right, Node* next)
        : m_val(val), m_left(left), m_right(right), m_next(next) {}
};

class Solution {
   public:
    Node* Connect(Node* root) {
        Node n;
        Node* start = &n;
        Node* node_child = start;
        Node* node = root;

        while (node != nullptr) {
            while (node != nullptr) {  // Connect node child
              if (node->m_left != nullptr) {
                node_child->m_next = node->m_left;
                node_child = node_child->m_next;
              }
              if (node->m_right != nullptr) {
                node_child->m_next = node->m_right;
                node_child = node_child->m_next;
              }
              node = node->m_next;
            }
            node = start->m_next;
            start->m_next = nullptr;
            node_child = start;
        }
        return root;
    }
};

TEST(populating_next_right_pointers_in_each_node_ii, t1) {}

}  // namespace
