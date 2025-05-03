// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given the head of a linked list, reverse the nodes of the list k at a time, and
return the modified list.

k is a positive integer and is less than or equal to the length of the linked
list. If the number of nodes is not a multiple of k then left-out nodes, in the
end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be
changed.

*/

//* Definition for singly-linked list.
#include "datastruct_base.hh"
#include "gtest/gtest.h"

using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode* ReverseKGroup(ListNode* head, int k) {
        // pass

        if (head == nullptr) {
            return nullptr;
        }
        ListNode* this_tail = head;
        ListNode* this_head_it = head;
        ListNode* this_head_back = head;
        bool reverse = true;
        for (int i = 1; i < k; i++) {
            if (this_head_it->next) {
                this_head_it = this_head_it->next;
            } else {
                // 不需要反转了
                reverse = false;
            }
        }

        if (reverse) {
            ListNode* this_follow = ReverseKGroup(this_head_it->next, k);
            this_head_it->next = nullptr;

            this_head_back = ReverseList(this_head_back);
            this_tail->next = this_follow;
        }

        return this_head_back;
    }
    /// 反转整个链表
    ListNode* ReverseList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* this_head = head;
        ListNode* this_follow = head->next;
        this_head->next = nullptr;

        this_follow = ReverseList(this_follow);
        if (this_follow == nullptr) {
            return this_head;
        }

        ListNode* this_follow_it = this_follow;

        while (this_follow_it->next != nullptr) {
            this_follow_it = this_follow_it->next;
        }
        this_follow_it->next = this_head;
        return this_follow;
    }
};

#include <vector>

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

TEST(memleak, t0) {
  std::vector<int> const head = {1, 2, 3, 4, 5};
  ListNode* root = List::ConstructList(head);

  std::vector<int> const expect = {1, 2, 3, 4, 5};

  ExpectEqList(root, expect);
  List::FreeList(root);
}

TEST(reverse_nodes_in_k_group, t0) {
  std::vector<int> const head = {1, 2, 3, 4, 5};
  int const k = 2;
  ListNode* root = List::ConstructList(head);

  Solution s;
  root = s.ReverseKGroup(root, k);

  std::vector<int> const expect = {2, 1, 4, 3, 5};

  ExpectEqList(root, expect);
  List::FreeList(root);
}

TEST(reverse_nodes_in_k_group, t1) {
  std::vector<int> const head = {1, 2, 3, 4, 5};
  int const k = 3;
  std::vector<int> const expect = {3, 2, 1, 4, 5};
  ListNode* root = List::ConstructList(head);

  Solution s;
  root = s.ReverseKGroup(root, k);

  ExpectEqList(root, expect);

  // Output: [2,1,4,3,5]
  List::FreeList(root);
}

TEST(reverse_nodes_in_k_group, t2) {
  std::vector<int> const head = {1, 2, 3, 4, 5};
  int const k = 1;
  std::vector<int> const expect = {1, 2, 3, 4, 5};
  ListNode* root = List::ConstructList(head);

  Solution s;
  root = s.ReverseKGroup(root, k);

  ExpectEqList(root, expect);

  // Output: [2,1,4,3,5]
  List::FreeList(root);
}
}  // namespace
