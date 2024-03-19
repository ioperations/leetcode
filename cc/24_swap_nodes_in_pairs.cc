// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <vector>

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

// Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode *SwapPairs(ListNode *head) {
        /*
Given a linked list, swap every two adjacent nodes and return its head. You must
solve the problem without modifying the values in the list's nodes (i.e., only
nodes themselves may be changed.)
        */
        if (head == nullptr) {
            return nullptr;
        }
        ListNode *m_head = head;
        ListNode *m_next = m_head->next;
        if (m_next == nullptr) {
            // m_head->next = nullptr;
            return m_head;
        }
        ListNode *m_follow = SwapPairs(m_next->next);

        m_head->next = m_follow;
        m_next->next = m_head;
        return m_next;
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

TEST(swap_nodes_in_pairs, t0) {
    // Input: head = [1,2,3,4]
    // Output: [2,1,4,3]

    auto *ret = List::ConstructList(std::vector<int>{1, 2, 3, 4});
    ExpectEqList(ret, std::vector<int>{1, 2, 3, 4});
    List::FreeList(ret);
}

TEST(swap_nodes_in_pairs, t1) {
    // Input: head = [1,2,3,4]
    // Output: [2,1,4,3]

    auto *ret = List::ConstructList(std::vector<int>{1, 2, 3, 4});
    Solution s;
    ret = s.SwapPairs(ret);
    ExpectEqList(ret, std::vector<int>{2, 1, 4, 3});
    List::FreeList(ret);
}

TEST(swap_nodes_in_pairs, t2) {
    // Input: head = []
    // Output: []

    auto *ret = List::ConstructList(std::vector<int>{});
    Solution s;
    ret = s.SwapPairs(ret);
    ExpectEqList(ret, std::vector<int>{});
    List::FreeList(ret);
}

TEST(swap_nodes_in_pairs, t3) {
    // Input: head = [1]
    // Output: [1]

    auto *ret = List::ConstructList(std::vector<int>{1});
    Solution s;
    ret = s.SwapPairs(ret);
    ExpectEqList(ret, std::vector<int>{1});
    List::FreeList(ret);
}

} // namespace
