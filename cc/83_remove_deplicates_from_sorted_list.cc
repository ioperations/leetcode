// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given the head of a sorted linked list, delete all duplicates such that each
element appears only once. Return the linked list sorted as well.
*/

#include "datastruct_base.hh"
#include "gtest/gtest.h"

//* Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode* DeleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *slow = head, *fast = head->next;

        while (fast != nullptr) {
            if (fast->val == slow->val) {
                // remove current fast
                ListNode* tmp = fast;
                fast = fast->next;
                slow->next = fast;
                delete tmp;
            } else {
                // advance
                fast = fast->next;
                slow = slow->next;
            }
        }

        return head;
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

TEST(remove_deplicates_from_sorted_list, t1) {
    std::vector<int> const head{1, 1, 2};
    std::vector<int> const output{1, 2};

    ListNode* root = List::ConstructList(head);

    Solution sl;
    auto* ret = sl.DeleteDuplicates(root);
    ExpectEqList(ret, output);
    List::FreeList(root);
}
TEST(remove_deplicates_from_sorted_list, t2) {
    std::vector<int> const head{1, 1, 2, 3, 3};
    std::vector<int> const output{1, 2, 3};

    ListNode* root = List::ConstructList(head);

    Solution sl;
    auto* ret = sl.DeleteDuplicates(root);
    ExpectEqList(ret, output);
    List::FreeList(root);
}

}  // namespace
