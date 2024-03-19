// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given the head of a linked list, rotate the list to the right by k places.
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
    ListNode *RotateRight(ListNode *head, int k) {
        int ret = Solve(head);
        if (ret != 0) {
            int left = k % ret - 1;
            if (k % ret == 0) {
                for (int i = 0; i < (k - 1); i++) {
                    Solve(head);
                }
            }
            for (int i = 0; i < left; i++) {
                Solve(head);
            }
        } else {
            for (int i = 0; i < (k - 1); i++) {
                Solve(head);
            }
        }
        return head;
    }
    ListNode *RotateRightV1(ListNode *head, int k) {
        if (head == nullptr) return nullptr;

        ListNode *fast = head;
        ListNode *slow = head;
        ListNode *prev = head;
        int len = 1;

        while (fast->next != nullptr) {
            fast = fast->next;
            len++;
        }
        fast = head;

        for (int i = 0; i < k % len; i++) {
            fast = fast->next;
        }

        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
            prev = prev->next;
        }

        if (slow->next == nullptr) return head;
        slow = slow->next;
        fast->next = head;
        prev->next = nullptr;

        return slow;
    }

    int Solve(ListNode *&head) {
        int size = 0;
        if (head == nullptr) {
            return 0;
        }
        ListNode *local_head = head;

        if (local_head->next != nullptr) {
            while (local_head->next != nullptr) {
                if (local_head->next->next == nullptr) {
                    ListNode *last = local_head->next;
                    local_head->next = nullptr;
                    last->next = head;
                    head = last;
                    size += 2;
                    break;
                }
                local_head = local_head->next;
                size++;
            }
        } else {
            return 1;
        }

        return size;
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

TEST(rotate_list, t1) {
    std::vector<int> v{1, 2, 3, 4, 5};
    int k = 2;
    std::vector<int> output{4, 5, 1, 2, 3};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
};

TEST(rotate_list, t2) {
    std::vector<int> v{0, 1, 2};
    int k = 4;
    std::vector<int> output{2, 0, 1};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
};

TEST(rotate_list, t3) {
    std::vector<int> v{1, 2};
    int k = 1;
    std::vector<int> output{2, 1};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
};

TEST(rotate_list, t4) {
    std::vector<int> v{1, 2};
    int k = 1;
    std::vector<int> output{2, 1};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRightV1(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
};

TEST(rotate_list, t5) {
    std::vector<int> v{};
    int k = 1;
    std::vector<int> output{};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
};

TEST(rotate_list, t6) {
    std::vector<int> v{1, 2, 3};
    int k = 2000000000;
    std::vector<int> output{2, 3, 1};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
};

TEST(rotate_list, t7) {
    std::vector<int> v{1, 2};
    int k = 2;
    std::vector<int> output{1, 2};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
};

TEST(rotate_list, t8) {
    std::vector<int> v{1, 2, 3};
    int k = 3;
    std::vector<int> output{1, 2, 3};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
}

TEST(rotate_list, t9) {
    std::vector<int> v{1, 2, 3, 4, 5};
    int k = 10;
    std::vector<int> output{1, 2, 3, 4, 5};
    ListNode *head = List::ConstructList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    List::FreeList(head);
}

}  // namespace
