// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the head of a linked list, remove the nth node from the end of the list
and return its head.
*/

#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"
//* Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode* RemoveNthFromEnd(ListNode* head, int n) {
        return RemoveNthFromEndV2(head, n);
    }

    ListNode* RemoveNthFromEndV2(ListNode* head, int n) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        for (int i = 0; fast && i < n + 1; ++i) {
            fast = fast->next;
        }

        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* tmp = nullptr;
        if (slow->next) {
            tmp = slow->next;
            slow->next = slow->next->next;
            delete tmp;
        } else {
            delete slow;
            return nullptr;
        }

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

TEST(remove_Nth_node_from_end_of_list, t1) {
    const std::vector<int> v{1, 2, 3, 4, 5};
    const int n = 2;

    ListNode* head = List::ConstructList(v);
    Solution sl;
    head = sl.RemoveNthFromEnd(head, n);
    ExpectEqList(head, std::vector<int>{1, 2, 3, 5});
    List::FreeList(head);
}

TEST(remove_Nth_node_from_end_of_list, t2) {
    const std::vector<int> v{1};
    const int n = 1;

    ListNode* head = List::ConstructList(v);
    Solution sl;
    head = sl.RemoveNthFromEnd(head, n);
    ExpectEqList(head, std::vector<int>{});
    List::FreeList(head);
}

TEST(remove_Nth_node_from_end_of_list, t3) {
    const std::vector<int> v{1, 2};
    const int n = 1;

    ListNode* head = List::ConstructList(v);
    Solution sl;
    head = sl.RemoveNthFromEnd(head, n);
    ExpectEqList(head, std::vector<int>{1});
    List::FreeList(head);
}
}  // namespace
