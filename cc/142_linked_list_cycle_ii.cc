// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given head, the head of a linked list, determine if the linked list has a cycle
in it.

There is a cycle in a linked list if there is some node in the list that can be
reached again by continuously following the next pointer. Internally, pos is
used to denote the index of the node that tail's next pointer is connected to.
Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false
*/
#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

//* Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode *DetectCycle(ListNode *head) {
        bool cycle_present = false;
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast != nullptr and fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                cycle_present = true;
                break;
            }
        }
        if (cycle_present == false) {
            return nullptr;
        }
        ListNode *k = head;
        while (k != slow) {
            k = k->next;
            slow = slow->next;
        }
        return k;
    }
};

TEST(memleak, linked_list_cycle_ii_2) {
    ListNode *head = List::ConstructList(std::vector<int>{3, 2, 0, -4});

    FreeList(head);
}

TEST(linked_list_cycle_ii, t1) {
    /*
             ___       ___         ___       ___
            | 3 |---->| 2 |------>| 0 |---->|-4 |------|
            |___|     |___|       |___|     |___|      |
                       /\                              |
                       ||                              |
                       |-------------------------------|
             ___       ___         ___       ___        ___
            | 3 |---->| 2 |------>| 0 |---->|-4 |------| 4 |------|
            |___|     |___|       |___|     |___|      |___|      |
                                    /\                            |
                                    ||                            |
                                    |-----------------------------|

    */

    ListNode *head = List::ConstructList(std::vector<int>{3, 2, 0, -4});

    ListNode *it = head;
    ListNode *it2 = head;

    it = it->next;

    while (it2->next != nullptr) {
        it2 = it2->next;
    }

    it2->next = it;

    Solution s;
    ListNode *ret = s.DetectCycle(head);
    EXPECT_EQ(ret->val, 2);

    it2->next = nullptr;

    FreeList(head);
}

TEST(linked_list_cycle_ii, t2) {
    /*
         ___       ___
        | 1 |---->| 2 |------|
        |___|     |___|      |
         /\                  |
         ||                  |
         |-------------------|
    */

    ListNode *head = List::ConstructList(std::vector<int>{1, 2});

    ListNode *it = head;
    ListNode *it2 = head;

    while (it2->next != nullptr) {
        it2 = it2->next;
    }

    it2->next = it;

    Solution s;
    ListNode *ret = s.DetectCycle(head);
    EXPECT_EQ(ret->val, 1);

    it2->next = nullptr;

    FreeList(head);
}

TEST(linked_list_cycle_ii, t3) {
    /*
         ___
        | 1 |
        |___|

    */
    ListNode *head = List::ConstructList(std::vector<int>{1});

    Solution s;
    ListNode *ret = s.DetectCycle(head);
    EXPECT_EQ(ret, nullptr);

    FreeList(head);
}

TEST(linked_list_cycle_ii, t4) {
    ListNode *head = List::ConstructList(std::vector<int>{});

    Solution s;
    ListNode *ret = s.DetectCycle(head);
    EXPECT_EQ(ret, nullptr);

    FreeList(head);
}

}  // namespace
