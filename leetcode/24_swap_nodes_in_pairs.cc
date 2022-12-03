
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* SwapPairs(ListNode* head) {
        /*
Given a linked list, swap every two adjacent nodes and return its head. You must
solve the problem without modifying the values in the list's nodes (i.e., only
nodes themselves may be changed.)
        */
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* m_head = head;
        ListNode* m_next = m_head->next;
        if (m_next == nullptr) {
            // m_head->next = nullptr;
            return m_head;
        }
        ListNode* m_follow = SwapPairs(m_next->next);

        m_head->next = m_follow;
        m_next->next = m_head;
        return m_next;
    }
};

#include <gtest/gtest.h>

#include <iostream>
ListNode* ConstuctList(const std::vector<int>& elemets) {
    ListNode head;
    ListNode* tail = &head;
    for (auto& pt : elemets) {
        tail->next = new ListNode(pt);
        tail = tail->next;
    }
    return head.next;
}

void FreeList(ListNode* head) {
    if (head == nullptr) {
        return;
    }
    FreeList(head->next);
    delete head;
}

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

TEST(t0, t0) {
    // Input: head = [1,2,3,4]
    // Output: [2,1,4,3]

    auto* ret = ConstuctList(std::vector<int>{1, 2, 3, 4});
    ExpectEqList(ret, std::vector<int>{1, 2, 3, 4});
    FreeList(ret);
}

TEST(t0, t1) {
    // Input: head = [1,2,3,4]
    // Output: [2,1,4,3]

    auto* ret = ConstuctList(std::vector<int>{1, 2, 3, 4});
    Solution s;
    ret = s.SwapPairs(ret);
    ExpectEqList(ret, std::vector<int>{2, 1, 4, 3});
    FreeList(ret);
}

TEST(t0, t2) {
    // Input: head = []
    // Output: []

    auto* ret = ConstuctList(std::vector<int>{});
    Solution s;
    ret = s.SwapPairs(ret);
    ExpectEqList(ret, std::vector<int>{});
    FreeList(ret);
}

TEST(t0, t3) {
    // Input: head = [1]
    // Output: [1]

    auto* ret = ConstuctList(std::vector<int>{1});
    Solution s;
    ret = s.SwapPairs(ret);
    ExpectEqList(ret, std::vector<int>{1});
    FreeList(ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
