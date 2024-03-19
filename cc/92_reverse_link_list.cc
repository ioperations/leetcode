// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

//* Definition for singly-linked list.
using ListNode = List::ListNode<int>;
/*
   ____       ____        ____       ____         ____
  |    |     |    |      |    |     |    |       |    |
  | 1  |---> | 2  | ---> | 3  |---> | 4  | --->  | 5  |
  |____|     |____|      |____|     |____|       |____|


   ____       ____        ____       ____         ____
  |    |     |    |      |    |     |    |       |    |
  | 1  |---> | 4  | ---> | 3  |---> | 2  | --->  | 5  |
  |____|     |____|      |____|     |____|       |____|


*/
namespace {
class Solution {
   public:
    /// 从 @left 到 @right反转链表
    ListNode *ReverseBetween(ListNode *head, int left, int right) {
        ListNode *this_head = head;
        ListNode this_tail_node;
        ListNode *this_tail = nullptr, *this_list = nullptr, *it = head;

        int i = 1;
        bool add = true;
        ListNode *this_head_pre = nullptr;
        while (it != nullptr) {
            if (i == left) {
                this_list = it;
                if (this_head_pre) {
                    this_head_pre->next = nullptr;
                }
                if (i == 1) {
                    add = false;
                }
                break;
            }
            this_head_pre = it;
            it = it->next;
            i++;
        }

        while (it != nullptr) {
            if (i == right) {
                this_tail = it->next;
                it->next = nullptr;
                break;
            }
            it = it->next;
            i++;
        }

        this_list = ReverseList(this_list);

        if (add) {
            // this_head->next = this_list;
            ListNode *this_head_it = this_head;
            while (this_head_it->next != nullptr) {
                this_head_it = this_head_it->next;
            }
            this_head_it->next = this_list;
        } else {
            this_head = this_list;
        }

        it = this_list;
        while (it->next != nullptr) {
            it = it->next;
        }

        it->next = this_tail;

        return this_head;
    }

    /// 反转整个链表
    ListNode *ReverseList(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode *this_head = head;
        ListNode *this_follow = head->next;
        this_head->next = nullptr;

        this_follow = ReverseList(this_follow);
        if (this_follow == nullptr) {
            return this_head;
        }

        ListNode *this_follow_it = this_follow;

        while (this_follow_it->next != nullptr) {
            this_follow_it = this_follow_it->next;
        }
        this_follow_it->next = this_head;
        return this_follow;
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

TEST(reverse_link_list_v2, t0) {
    // head = [1,2,3,4,5], left = 2, right = 4 Output: [1,4,3,2,5]

    ListNode *head = List::ConstructList(std::vector<int>{1, 2, 3, 4, 5});
    Solution s;
    head = s.ReverseList(head);
    ExpectEqList(head, {5, 4, 3, 2, 1});

    List::FreeList(head);
}

TEST(reverse_link_list_v2, t1) {
    // , 2, 4

    ListNode *head = List::ConstructList(std::vector<int>{1, 2, 3, 4, 5});
    Solution s;
    head = s.ReverseBetween(head, 2, 4);
    ExpectEqList(head, {1, 4, 3, 2, 5});

    List::FreeList(head);
}

TEST(reverse_link_list_v2, t2) {
    // , 2, 4

    ListNode *head = List::ConstructList(std::vector<int>{5});
    Solution s;
    head = s.ReverseBetween(head, 1, 1);
    ExpectEqList(head, {5});

    List::FreeList(head);
}

TEST(reverse_link_list_v2, t3) {
    // , 2, 4

    ListNode *head = List::ConstructList(std::vector<int>{3, 5});
    Solution s;
    head = s.ReverseBetween(head, 1, 2);
    ExpectEqList(head, {5, 3});

    List::FreeList(head);
}
TEST(reverse_link_list_v2, t4) {
    // , 2, 4

    ListNode *head = List::ConstructList(std::vector<int>{1, 2, 3});
    Solution s;
    head = s.ReverseBetween(head, 3, 3);

    ExpectEqList(head, {1, 2, 3});

    List::FreeList(head);
}

}  // namespace
