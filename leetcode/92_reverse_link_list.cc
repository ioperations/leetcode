//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
ListNode *ConstuctList(const std::vector<int> &elemets) {
    ListNode head;
    ListNode *tail = &head;
    for (auto &pt : elemets) {
        tail->next = new ListNode(pt);
        tail = tail->next;
    }
    return head.next;
}

void FreeList(ListNode *head) {
    if (head == nullptr) {
        return;
    }
    FreeList(head->next);
    delete head;
}

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

TEST(t1, t0) {
    // head = [1,2,3,4,5], left = 2, right = 4 Output: [1,4,3,2,5]

    ListNode *head = ConstuctList(std::vector<int>{1, 2, 3, 4, 5});
    Solution s;
    head = s.ReverseList(head);
    ExpectEqList(head, {5, 4, 3, 2, 1});

    FreeList(head);
}

TEST(t1, t1) {
    // , 2, 4

    ListNode *head = ConstuctList(std::vector<int>{1, 2, 3, 4, 5});
    Solution s;
    head = s.ReverseBetween(head, 2, 4);
    ExpectEqList(head, {1, 4, 3, 2, 5});

    FreeList(head);
}

TEST(t1, t2) {
    // , 2, 4

    ListNode *head = ConstuctList(std::vector<int>{5});
    Solution s;
    head = s.ReverseBetween(head, 1, 1);
    ExpectEqList(head, {5});

    FreeList(head);
}

TEST(t1, t3) {
    // , 2, 4

    ListNode *head = ConstuctList(std::vector<int>{3, 5});
    Solution s;
    head = s.ReverseBetween(head, 1, 2);
    ExpectEqList(head, {5, 3});

    FreeList(head);
}
TEST(t1, t4) {
    // , 2, 4

    ListNode *head = ConstuctList(std::vector<int>{1, 2, 3});
    Solution s;
    head = s.ReverseBetween(head, 3, 3);

    ExpectEqList(head, {1, 2, 3});

    FreeList(head);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
