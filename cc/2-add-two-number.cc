// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/* * Definition for singly-linked list. */

#include <iostream>

#include "datastruct_base.hh"

using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode* AddTwoNumbers(ListNode* l1, ListNode* l2) {
        for (int i = 0; l1 || l2 || m_carrier; i++) {
            int va = 0;
            if (l1 && l2) {
                va = l1->val + m_carrier + l2->val;
            } else if (l1) {
                va = l1->val + m_carrier;
            } else if (l2) {
                va = l2->val + m_carrier;
            } else if (m_carrier) {
                va = m_carrier;
            }
            m_carrier = va >= 10 ? 1 : 0;
            va = va % 10;
            auto* n = new ListNode(va);
            // 保存 head
            if (i == 0) {
                m_head = n;
            }

            // 链接节点
            if (i != 0) {
                m_pre->next = n;
            }

            // 前一个节点
            m_pre = n;

            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }

        return m_head;
    }

   private:
    mutable int m_carrier = 0;
    ListNode* m_head = nullptr;
    ListNode* m_pre = nullptr;
    /*

      n -> n1 -> n2 -> n3

        * first free list n1 ; then free n
            * first free list n2 ; then free n1
                * first free list n3 ; then free n2

    */
   public:
    void FreeListNode(ListNode* n) {
        if (!n) {
            return;
        }

        FreeListNode(n->next);
        std::cout << " free: " << n->val;
        delete n;
    }
};

}  // namespace
