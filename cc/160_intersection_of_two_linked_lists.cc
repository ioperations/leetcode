// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given the heads of two singly linked-lists headA and headB, return the node at
which the two lists intersect. If the two linked lists have no intersection at
all, return null.

For example, the following two linked lists begin to intersect at node c1:

     ___ ___
    | a1| a2| ___________
    |___|___|            |
                         |       ___ ___ ___
                         |----->| c1| c2| c3|
 ___ ___ ___             |      |___|___|___|
| b1| b2| b3| ___________|
|___|___|___|



The test cases are generated such that there are no cycles anywhere in the
entire linked structure.

Note that the linked lists must retain their original structure after the
function returns.

 */

#include <string>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

// Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace { 
class Solution {
   public:
    ListNode *GetIntersectionNode(ListNode *head_a, ListNode *head_b) {
        // pass
        if (head_a == nullptr || head_b == nullptr) {
            return nullptr;
        }
        ListNode *a = head_a;
        ListNode *b = head_b;

        while (a != b) {
            a = a == nullptr ? head_b : a->next;
            b = b == nullptr ? head_a : b->next;
        }

        return a;
    }
    ListNode *GetIntersectionNodeV2(ListNode *head_a, ListNode *head_b) {
        int size_a = 0;
        int size_b = 0;

        ListNode *temp = head_a;
        while (temp != nullptr) {
            size_a++;
            temp = temp->next;
        }
        temp = head_b;
        while (temp != nullptr) {
            size_b++;
            temp = temp->next;
        }
        int diff = size_a - size_b;
        if (diff > 0) {
            while (diff != 0) {
                head_a = head_a->next;
                diff--;
            }
        } else {
            diff = -1 * diff;
            while (diff != 0) {
                head_b = head_b->next;
                diff--;
            }
        }

        while (head_a != nullptr) {
            if (head_a == head_b) return head_a;
            head_b = head_b->next;
            head_a = head_a->next;
        }
        return nullptr;
    }
};


void ExpectEqList(ListNode *const head, const std::vector<int> &elements) {
    int i = 0;
    ListNode *m_head = head;

    while (m_head != nullptr) {
        EXPECT_EQ(m_head->val, elements[i]);
        m_head = m_head->next;
        i++;
    }
    EXPECT_EQ(i, elements.size());
}

TEST(intersection_of_two_linked_lists, t1) {
    // intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2,
    // skipB = 3
    // Output: Intersected at '8'
    // Explanation: The intersected node's value is 8 (note that this must not
    // be 0 if the two lists intersect). From the head of A, it reads as
    // [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2
    // nodes before the intersected node in A; There are 3 nodes before the
    // intersected node in B.

    /*
         ___ ___
        | 4 | 1 | ___________
        |___|___|            |       ___ ___ ___
                             |----->| 8 | 4 | 5 |
     ___ ___ ___             |      |___|___|___|
    | 5 | 6 | 1 | ___________|
    |___|___|___|

    */

    ListNode *first = List::ConstructList(std::vector<int>{4, 1, 8, 4, 5});
    ListNode *second = List::ConstructList(std::vector<int>{5, 6, 1});
    ListNode *first_it = first;
    for (int i = 0; i < 2; i++) {
        first_it = first_it->next;
    }

    ListNode *second_it = second;

    while (second_it->next != nullptr) {
        second_it = second_it->next;
    }

    second_it->next = first_it;

    Solution s;
    auto *ret = s.GetIntersectionNodeV2(first, second);
    EXPECT_EQ(ret->val, 8);
    second_it->next = nullptr;

    List::FreeList(first);
    List::FreeList(second);
}

TEST(intersection_of_two_linked_lists, t2) {
    // intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2,
    // skipB = 3
    // Output: Intersected at '8'
    // Explanation: The intersected node's value is 8 (note that this must not
    // be 0 if the two lists intersect). From the head of A, it reads as
    // [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2
    // nodes before the intersected node in A; There are 3 nodes before the
    // intersected node in B.

    /*
         ___ ___ ___
        | 1 | 9 | 1 | ___________
        |___|___|___|            |
                                 |       ___ ___
                                 |----->| 2 | 4 |
                 ___             |      |___|___|
                | 3 | ___________|
                |___|

    */

    ListNode *first = List::ConstructList(std::vector<int>{1, 9, 1, 2, 4});
    ListNode *second = List::ConstructList(std::vector<int>{3});
    ListNode *first_it = first;
    for (int i = 0; i < 3; i++) {
        first_it = first_it->next;
    }

    ListNode *second_it = second;

    while (second_it->next != nullptr) {
        second_it = second_it->next;
    }

    second_it->next = first_it;

    Solution s;
    auto *ret = s.GetIntersectionNodeV2(first, second);
    EXPECT_EQ(ret->val, 2);
    second_it->next = nullptr;

    List::FreeList(first);
    List::FreeList(second);
}

TEST(intersection_of_two_linked_lists, t3) {
    // intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2,
    // skipB = 3
    // Output: Intersected at '8'
    // Explanation: The intersected node's value is 8 (note that this must not
    // be 0 if the two lists intersect). From the head of A, it reads as
    // [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2
    // nodes before the intersected node in A; There are 3 nodes before the
    // intersected node in B.

    /*
         ___ ___ ___
        | 2 | 6 | 4 | __________
        |___|___|___|
             ___ ___
            | 1 | 5 | __________
            |___|___|
    */

    ListNode *first = List::ConstructList(std::vector<int>{2, 6, 4});
    ListNode *second = List::ConstructList(std::vector<int>{1, 5});

    Solution s;

    auto *ret = s.GetIntersectionNodeV2(first, second);
    EXPECT_EQ(ret, nullptr);

    List::FreeList(first);
    List::FreeList(second);
}

}
