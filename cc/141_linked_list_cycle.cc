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
//* Definition for singly-linked list.
#include <vector>

#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using ListNode = List::ListNode<int>;
using List::ConstructList;
using List::FreeList;

namespace {
class Solution {
   public:
    bool HasCycle(ListNode *head) {
        // pass
        if (head == nullptr) {
            return false;
        }

        ListNode *fast = head;
        ListNode *slow = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow) {
                return true;
            }
        }
        return false;
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
TEST(memleak, t1) {
    ListNode *head = ConstructList(std::vector<int>{3, 2, 0, -4});

    FreeList(head);
}

TEST(linked_list_cycle, t1) {
    /*
             ___       ___         ___       ___
            | 3 |---->| 2 |------>| 0 |---->|-4 |------|
            |___|     |___|       |___|     |___|      |
                       /\                              |
                       ||                              |
                       |-------------------------------|
    */

    ListNode *head = ConstructList(std::vector<int>{3, 2, 0, -4});

    ListNode *it = head;
    ListNode *it2 = head;

    it = it->next;

    while (it2->next != nullptr) {
        it2 = it2->next;
    }

    it2->next = it;

    Solution s;
    bool ret = s.HasCycle(head);
    EXPECT_EQ(ret, true);

    it2->next = nullptr;

    FreeList(head);
}

TEST(linked_list_cycle, t2) {
    /*
         ___       ___
        | 1 |---->| 2 |------|
        |___|     |___|      |
         /\                  |
         ||                  |
         |-------------------|
    */

    ListNode *head = ConstructList(std::vector<int>{1, 2});

    ListNode *it = head;
    ListNode *it2 = head;

    while (it2->next != nullptr) {
        it2 = it2->next;
    }

    it2->next = it;

    Solution s;
    bool ret = s.HasCycle(head);
    EXPECT_EQ(ret, true);

    it2->next = nullptr;

    FreeList(head);
}

TEST(linked_list_cycle, t3) {
    /*
         ___
        | 1 |
        |___|

    */

    ListNode *head = ConstructList(std::vector<int>{1});

    Solution s;
    bool ret = s.HasCycle(head);
    EXPECT_EQ(ret, false);

    FreeList(head);
}

TEST(linked_list_cycle, t4) {
    ListNode *head = ConstructList(std::vector<int>{});

    Solution s;
    bool ret = s.HasCycle(head);
    EXPECT_EQ(ret, false);

    FreeList(head);
}

}  // namespace
