
/*
Given the head of a linked list, rotate the list to the right by k places.
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
    ListNode* RotateRight(ListNode* head, int k) {
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
    ListNode* RotateRightV1(ListNode* head, int k) {
        if (head == nullptr) return nullptr;

        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* prev = head;
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

    int Solve(ListNode*& head) {
        int size = 0;
        if (head == nullptr) {
            return 0;
        }
        ListNode* local_head = head;

        if (local_head->next != nullptr) {
            while (local_head->next != nullptr) {
                if (local_head->next->next == nullptr) {
                    ListNode* last = local_head->next;
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

TEST(t0, t1) {
    std::vector<int> v{1, 2, 3, 4, 5};
    int k = 2;
    std::vector<int> output{4, 5, 1, 2, 3};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
};

TEST(t0, t2) {
    std::vector<int> v{0, 1, 2};
    int k = 4;
    std::vector<int> output{2, 0, 1};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
};

TEST(t0, t3) {
    std::vector<int> v{1, 2};
    int k = 1;
    std::vector<int> output{2, 1};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
};

TEST(t0, t4) {
    std::vector<int> v{1, 2};
    int k = 1;
    std::vector<int> output{2, 1};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRightV1(head, k);
    ExpectEqList(head, output);
    FreeList(head);
};

TEST(t0, t5) {
    std::vector<int> v{};
    int k = 1;
    std::vector<int> output{};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
};

TEST(t0, t6) {
    std::vector<int> v{1, 2, 3};
    int k = 2000000000;
    std::vector<int> output{2, 3, 1};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
};

TEST(t0, t7) {
    std::vector<int> v{1, 2};
    int k = 2;
    std::vector<int> output{1, 2};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
};

TEST(t0, t8) {
    std::vector<int> v{1, 2, 3};
    int k = 3;
    std::vector<int> output{1, 2, 3};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
}

TEST(t0, t9) {
    std::vector<int> v{1, 2, 3, 4, 5};
    int k = 10;
    std::vector<int> output{1, 2, 3, 4, 5};
    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.RotateRight(head, k);
    ExpectEqList(head, output);
    FreeList(head);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
