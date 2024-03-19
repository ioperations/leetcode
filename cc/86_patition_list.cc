// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given the head of a linked list and a value x, partition it such that all nodes
less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two
partitions.
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

//* Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode *Partition(ListNode *head, int x) {
        // pass
        ListNode less;
        ListNode more;

        ListNode *less_it = &less;
        ListNode *more_it = &more;

        while (head != nullptr) {
            if (head->val < x) {
                less_it->next = head;
                less_it = less_it->next;
            } else {
                more_it->next = head;
                more_it = more_it->next;
            }
            head = head->next;
        }
        if (less_it) {
            less_it->next = more.next;
            more_it->next = nullptr;
            return less.next;
        }
        return more.next;
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

TEST(patition_list, t1) {
    std::vector<int> vec = {1, 4, 3, 2, 5, 2};
    int x = 3;

    ListNode *head = List::ConstructList(vec);
    Solution s;
    head = s.Partition(head, x);

    ExpectEqList(head, std::vector<int>{1, 2, 2, 4, 3, 5});
    List::FreeList(head);
}

TEST(patition_list, t2) {
    std::vector<int> vec = {2, 1};
    int x = 2;

    ListNode *head = List::ConstructList(vec);
    Solution s;
    head = s.Partition(head, x);

    ExpectEqList(head, std::vector<int>{1, 2});
    List::FreeList(head);
}

TEST(patition_list, t3) {
    std::vector<int> vec = {2, 1};
    int x = 0;

    ListNode *head = List::ConstructList(vec);
    Solution s;
    head = s.Partition(head, x);

    ExpectEqList(head, std::vector<int>{2, 1});
    List::FreeList(head);
}

}  // namespace
