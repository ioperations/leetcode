// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node
from the beginning and the kth node from the end (the list is 1-indexed).
*/

#include <utility>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

//* Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode* SwapNodes(ListNode* head, int k) {
        // pass
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* node1 = nullptr;
        ListNode* my_head = head;
        for (int i = 1; i < k && my_head != nullptr; i++) {
            my_head = my_head->next;
        }
        node1 = my_head;

        ListNode* node2 = head;

        my_head = my_head->next;
        while (my_head != nullptr) {
            my_head = my_head->next;
            node2 = node2->next;
        }
        std::swap(node1->val, node2->val);
        return head;
    }
};

void ExpectEqList(ListNode* const head, const std::vector<int>& elements) {
    int i = 0;
    ListNode* m_head = head;

    while (m_head != nullptr) {
        EXPECT_EQ(m_head->val, elements[i]);
        m_head = m_head->next;
        i++;
    }
    EXPECT_EQ(i, elements.size());
}
TEST(memleak, t1) {
    ListNode* head = List::ConstructList(std::vector<int>{3, 2, 0, -4});

    List::FreeList(head);
}

TEST(swapping_nodes_in_a_linked_list, t1) {
    std::vector<int> const v{1, 2, 3, 4, 5};
    int const k = 2;

    ListNode* head = List::ConstructList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{1, 4, 3, 2, 5});
    List::FreeList(head);
}

TEST(swapping_nodes_in_a_linked_list, t2) {
    std::vector<int> const v{7, 9, 6, 6, 7, 8, 3, 0, 9, 5};
    int const k = 5;

    ListNode* head = List::ConstructList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{7, 9, 6, 6, 8, 7, 3, 0, 9, 5});
    List::FreeList(head);
}

TEST(swapping_nodes_in_a_linked_list, t3) {
    std::vector<int> const v{1, 2};
    int const k = 1;

    ListNode* head = List::ConstructList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{2, 1});
    List::FreeList(head);
}

TEST(swapping_nodes_in_a_linked_list, t4) {
    std::vector<int> const v{1, 2};
    int const k = 2;

    ListNode* head = List::ConstructList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{2, 1});
    List::FreeList(head);
}

}  // namespace
