// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/* * Definition for singly-linked list. */

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode *AddTwoNumbers(ListNode *l1, ListNode *l2) {
        for (int i = 0; l1 || l2 || carrier; i++) {
            int va = 0;
            if (l1 && l2) {
                va = l1->val + carrier + l2->val;
            } else if (l1) {
                va = l1->val + carrier;
            } else if (l2) {
                va = l2->val + carrier;
            } else if (carrier) {
                va = carrier;
            }
            carrier = va >= 10 ? 1 : 0;
            va = va % 10;
            ListNode *n = new ListNode(va);
            // 保存 head
            if (i == 0) {
                head = n;
            }

            // 链接节点
            if (i != 0) {
                pre->next = n;
            }

            // 前一个节点
            pre = n;

            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }

        return head;
    }

   private:
    mutable int carrier = 0;
    ListNode *head = nullptr;
    ListNode *pre = nullptr;
    /*

      n -> n1 -> n2 -> n3

        * first free list n1 ; then free n
            * first free list n2 ; then free n1
                * first free list n3 ; then free n2

    */
};

void PrintNode(ListNode *n) {
    std::cout << std::endl;

    for (; n;) {
        std::cout << n->val << " -> ";
        n = n->next;
    }
    std::cout << std::endl;
}

TEST(add_two_number, t1) {
    auto *l1 = List::ConstructList(std::vector<int>{1, 2, 3});
    auto *l2 = List::ConstructList(std::vector<int>{4, 5, 6});

    Solution sl;
    auto *ret = sl.AddTwoNumbers(l1, l2);
    List::FreeList(ret);
    List::FreeList(l1);
    List::FreeList(l2);
}

}  // namespace
