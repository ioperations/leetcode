/*
Write a function to delete a node in a singly-linked list. You will not be given
access to the head of the list, instead you will be given access to the node to
be deleted directly.

It is guaranteed that the node to be deleted is not a tail node in the list.
 */
#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
   public:
    void DeleteNode(ListNode* node) {
        while (node != nullptr) {
            if (node->next != nullptr) {
                std::swap(node->val, node->next->val);
                if (node->next->next == nullptr) {
                    // node->next = nullptr;
                    // break;
                }
                node = node->next;
            } else {
                break;
            }
        }
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
using namespace std;

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
    ListNode* m_head = head;

    for (int i = 0; i < (int)elements.size(); i++) {
        EXPECT_EQ(m_head->val, elements[i]);
        m_head = m_head->next;
    }
}

ListNode* FindNode(ListNode* const head, int v) {
    ListNode* local = head;
    while (local != nullptr) {
        if (local->val == v) {
            return local;
        }
        local = local->next;
    }
    return head;
}

TEST(t0, t1) {
    std::vector<int> v{4, 5, 1, 9};
    int node = 5;
    std::vector<int> final{4, 1, 9};
    Solution sl;
    ListNode* head = ConstuctList(v);
    ListNode* input = FindNode(head, node);
    sl.DeleteNode(input);

    ExpectEqList(head, final);

    FreeList(head);
}

TEST(t0, t2) {
    std::vector<int> v{4, 5, 1, 9};
    int node = 1;
    std::vector<int> final{4, 5, 9};
    Solution sl;
    ListNode* head = ConstuctList(v);
    ListNode* input = FindNode(head, node);
    sl.DeleteNode(input);

    ExpectEqList(head, final);

    FreeList(head);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
