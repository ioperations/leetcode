// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Write a function to delete a node in a singly-linked list. You will not be given
access to the head of the list, instead you will be given access to the node to
be deleted directly.

It is guaranteed that the node to be deleted is not a tail node in the list.
 */
#include <utility>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

// Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    void DeleteNode(ListNode* node) {
        while (node != nullptr) {
            if (node->next != nullptr) {
                std::swap(node->val, node->next->val);
                if (node->next->next == nullptr) {
                    // node->next = nullptr;
                    // break;
                }
                node = node->next;
            } else {
                break;
            }
        }
    }
};

#include <vector>

using namespace std;

void ExpectEqList(ListNode* const head, const std::vector<int>& elements) {
    ListNode* m_head = head;

    for (int const element : elements) {
        EXPECT_EQ(m_head->val, element);
        m_head = m_head->next;
    }
}

ListNode* FindNode(ListNode* const head, int v) {
    ListNode* local = head;
    while (local != nullptr) {
        if (local->val == v) {
            return local;
        }
        local = local->next;
    }
    return head;
}

TEST(delete_node_in_a_linked_list, t1) {
    std::vector<int> const v{4, 5, 1, 9};
    int const node = 5;
    std::vector<int> const final{4, 1, 9};
    Solution sl;
    ListNode* head = List::ConstructList(v);
    ListNode* input = FindNode(head, node);
    sl.DeleteNode(input);

    ExpectEqList(head, final);

    List::FreeList(head);
}

TEST(delete_node_in_a_linked_list, t2) {
    std::vector<int> const v{4, 5, 1, 9};
    int const node = 1;
    std::vector<int> const final{4, 5, 9};
    Solution sl;
    ListNode* head = List::ConstructList(v);
    ListNode* input = FindNode(head, node);
    sl.DeleteNode(input);

    ExpectEqList(head, final);

    List::FreeList(head);
}
}  // namespace
