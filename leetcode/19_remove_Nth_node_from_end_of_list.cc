/*
Given the head of a linked list, remove the nth node from the end of the list
and return its head.
*/

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* RemoveNthFromEnd(ListNode* head, int n) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* slow = head;
        ListNode* fast = head;

        int i = 0;
        while (fast != nullptr && i < n) {
            fast = fast->next;
            if (fast == nullptr) {
                if (i == n - 1) {
                    ListNode* tmp = head;
                    ListNode* ret = tmp->next;

                    delete tmp;
                    return ret;
                }
                return head;
            }
            i++;
        }

        if (fast) {
            fast = fast->next;

            while (fast != nullptr) {
                fast = fast->next;
                slow = slow->next;
            }

            {
                ListNode* tmp = slow->next;
                slow->next = slow->next->next;

                delete tmp;
            }
            return head;
        }
        if (slow == head) {
            delete slow;
            return nullptr;
        }

        return nullptr;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> v{1, 2, 3, 4, 5};
    int n = 2;

    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RemoveNthFromEnd(head, n);
    ExpectEqList(head, std::vector<int>{1, 2, 3, 5});
    FreeList(head);
}
TEST(t0, t2) {
    std::vector<int> v{1};
    int n = 1;

    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RemoveNthFromEnd(head, n);
    ExpectEqList(head, std::vector<int>{});
    FreeList(head);
}

TEST(t0, t3) {
    std::vector<int> v{1, 2};
    int n = 1;

    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RemoveNthFromEnd(head, n);
    ExpectEqList(head, std::vector<int>{1});
    FreeList(head);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
