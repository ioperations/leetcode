// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the head of a singly linked list, group all the nodes with odd indices
together followed by the nodes with even indices, and return the reordered list.

The first node is considered odd, and the second node is even, and so on.

Note that the relative order inside both the even and odd groups should remain
as it was in the input.

You must solve the problem in O(1) extra space complexity and O(n) time
complexity.
*/

#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

// Definition for singly-linked lis
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode *OddEvenListV1(ListNode *head) {
        // The number of nodes in the linked list is in the range [0, 104].
        // -106 <= Node.val <= 106
        if (head == nullptr) {
            return nullptr;
        }

        ListNode node;
        ListNode *first = &node;
        ListNode node2;
        ListNode *second = &node2;
        ;
        ListNode *my_head = head;

        bool odd_first = head->val % 2 == 0;

        while (my_head != nullptr) {
            if (odd_first ^
                (my_head->val % 2 ==
                 0)) {  // odd_first 和head->val不都为奇或者不都为偶数
                second->next = my_head;
                second = second->next;
            } else {
                first->next = my_head;
                first = first->next;
            }

            my_head = my_head->next;
        }
        second->next = nullptr;

        first->next = node2.next;

        return node.next;
    }

    ListNode *OddEvenList(ListNode *head) {
        // The number of nodes in the linked list is in the range [0, 104].
        // -106 <= Node.val <= 106
        if (head == nullptr) {
            return nullptr;
        }

        ListNode node;
        ListNode *first = &node;
        ListNode node2;
        ListNode *second = &node2;
        ;
        ListNode *my_head = head;

        bool odd_first = true;

        int i = 0;
        while (my_head != nullptr) {
            if (odd_first ^
                (i % 2 == 0)) {  // odd_first 和head->val不都为奇或者不都为偶数
                second->next = my_head;
                second = second->next;
            } else {
                first->next = my_head;
                first = first->next;
            }

            my_head = my_head->next;
            i++;
        }
        second->next = nullptr;

        first->next = node2.next;

        return node.next;
    }
};
#include <vector>

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

TEST(odd_even_linked_list, t1) {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> ex{1, 3, 5, 2, 4};

    /*
         ___      ___       ___        ___       ___
        | 1 |    | 2 |     | 3 |      | 4 |     | 5 |
        |___|    |___|     |___|      |___|     |___|


         ___      ___       ___        ___       ___
        | 1 |    | 3 |     | 5 |      | 2 |     | 4 |
        |___|    |___|     |___|      |___|     |___|

    */
    ListNode *head = List::ConstructList(v);

    Solution sl;
    head = sl.OddEvenListV1(head);

    ExpectEqList(head, ex);
    List::FreeList(head);
}

TEST(odd_even_linked_list, t2) {
    std::vector<int> v{2, 1, 3, 5, 6, 4, 7};
    std::vector<int> ex{2, 6, 4, 1, 3, 5, 7};
    /*
         ___      ___       ___        ___       ___        ___       ___
        | 2 |    | 1 |     | 3 |      | 5 |     | 6 |      | 4 |     | 7 |
        |___|    |___|     |___|      |___|     |___|      |___|     |___|


         ___      ___       ___        ___       ___        ___       ___
        | 2 |    | 6 |     | 4 |      | 1 |     | 3 |      | 5 |     | 7 |
        |___|    |___|     |___|      |___|     |___|      |___|     |___|
    */

    ListNode *head = List::ConstructList(v);

    Solution sl;
    head = sl.OddEvenListV1(head);

    ExpectEqList(head, ex);
    List::FreeList(head);
}

TEST(odd_even_linked_list_v2, t1) {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> ex{1, 3, 5, 2, 4};

    /*
         ___      ___       ___        ___       ___
        | 1 |    | 2 |     | 3 |      | 4 |     | 5 |
        |___|    |___|     |___|      |___|     |___|


         ___      ___       ___        ___       ___
        | 1 |    | 3 |     | 5 |      | 2 |     | 4 |
        |___|    |___|     |___|      |___|     |___|

    */
    ListNode *head = List::ConstructList(v);

    Solution sl;
    head = sl.OddEvenList(head);

    ExpectEqList(head, ex);
    List::FreeList(head);
}

TEST(odd_even_linked_list_v2, t2) {
    std::vector<int> v{2, 1, 3, 5, 6, 4, 7};
    std::vector<int> ex{2, 3, 6, 7, 1, 5, 4};
    /*
         ___      ___       ___        ___       ___        ___       ___
        | 2 |    | 1 |     | 3 |      | 5 |     | 6 |      | 4 |     | 7 |
        |___|    |___|     |___|      |___|     |___|      |___|     |___|


         ___      ___       ___        ___       ___        ___       ___
        | 2 |    | 3 |     | 6 |      | 7 |     | 1 |      | 5 |     | 4 |
        |___|    |___|     |___|      |___|     |___|      |___|     |___|
    */

    ListNode *head = List::ConstructList(v);

    Solution sl;
    head = sl.OddEvenList(head);

    ExpectEqList(head, ex);
    List::FreeList(head);
}
}  // namespace
