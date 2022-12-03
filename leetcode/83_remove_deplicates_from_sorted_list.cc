
/*
Given the head of a sorted linked list, delete all duplicates such that each
element appears only once. Return the linked list sorted as well.
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
    ListNode* DeleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *slow = head, *fast = head->next;

        while (fast != nullptr) {
            if (fast->val == slow->val) {
                // remove current fast
                ListNode* tmp = fast;
                fast = fast->next;
                slow->next = fast;
                delete tmp;
            } else {
                // advance
                fast = fast->next;
                slow = slow->next;
            }
        }

        return head;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
ListNode* ConstructList(const std::vector<int>& elemets) {
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

TEST(t0, t1) {
    std::vector<int> head{1, 1, 2};
    std::vector<int> output{1, 2};

    ListNode* root = ConstructList(head);

    Solution sl;
    auto* ret = sl.DeleteDuplicates(root);
    ExpectEqList(ret, output);
    FreeList(root);
}
TEST(t0, t2) {
    std::vector<int> head{1, 1, 2, 3, 3};
    std::vector<int> output{1, 2, 3};

    ListNode* root = ConstructList(head);

    Solution sl;
    auto* ret = sl.DeleteDuplicates(root);
    ExpectEqList(ret, output);
    FreeList(root);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
