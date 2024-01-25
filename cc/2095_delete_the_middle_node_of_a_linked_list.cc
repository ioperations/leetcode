// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given the head of a linked list. Delete the middle node, and return
the head of the modified linked list.

The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start
using 0-based indexing, where ⌊x⌋ denotes the largest integer less than or equal
to x.

For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2,
respectively.*/

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
    ListNode *MiddlePrev(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *prev = nullptr;
        while (fast != nullptr && fast->next != nullptr) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        return prev;
    }

   public:
    ListNode *DeleteMiddle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        ListNode *curr = MiddlePrev(head);
        /* NOTE: mem */ ListNode *de = curr->next;
        curr->next = curr->next->next;
        /* NOTE: mem */ delete de;
        return head;
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

#include <gtest/gtest.h>

#include <iostream>
using namespace std;

TEST(t0, t1) {
    vector<int> head = {1, 3, 4, 7, 1, 2, 6};
    vector<int> output = {1, 3, 4, 1, 2, 6};
    /*
    Explanation:
    The above figure represents the given linked list. The indices of the nodes
    are written below. Since n = 7, node 3 with value 7 is the middle node,
    which is marked in red. We return the new list after removing this node.
    */
    auto *list = ConstuctList(head);

    Solution sl;
    list = sl.DeleteMiddle(list);
    ExpectEqList(list, output);
    FreeList(list);
}

TEST(t0, t2) {
    vector<int> head = {1, 2, 3, 4};
    vector<int> output = {1, 2, 4};
    /*
    Explanation:
    The above figure represents the given linked list.
    For n = 4, node 2 with value 3 is the middle node, which is marked in red.
    */
    auto *list = ConstuctList(head);

    Solution sl;
    list = sl.DeleteMiddle(list);
    ExpectEqList(list, output);
    FreeList(list);
}

TEST(t0, t3) {
    vector<int> head = {2, 1};
    vector<int> output = {2};
    /*
    The above figure represents the given linked list.
For n = 2, node 1 with value 1 is the middle node, which is marked in red.
Node 0 with value 2 is the only node remaining after removing node 1.
    */
    auto *list = ConstuctList(head);

    Solution sl;
    list = sl.DeleteMiddle(list);
    ExpectEqList(list, output);
    FreeList(list);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
