
/*
Given the head of a linked list and an integer val, remove all the nodes of the
linked list that has Node.val == val, and return the new head.
*/

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

#include <memory>
#include <queue>
using namespace std;

class Solution {
   public:
    void AddToTail(ListNode*& tail, ListNode* node) {
        tail->next = node;
        tail = tail->next;
        tail->next = NULL;
    }

    ListNode* RemoveElementsV3(ListNode* head, int val) {
        ListNode* result = new ListNode();
        ListNode* rt = result;

        while (head) {
            ListNode* temp = head->next;
            if (head->val != val) AddToTail(rt, head);
            head = temp;
        }

        return result->next;
    }

    ListNode* RemoveElementsV2(ListNode* head, int val) {
        auto dummy = std::make_unique<ListNode>();
        dummy->next = head;
        auto* p = dummy.get();
        while (p->next) {
            if (p->next->val == val) {
                auto* removed = p->next;
                p->next = removed->next;
                delete removed;
            } else {
                p = p->next;
            }
        }

        return dummy->next;
    }
    ListNode* RemoveElements(ListNode* head, int val) {
        if (head == nullptr) {
            return nullptr;
        }
        // pass
        std::queue<ListNode*> q;

        PushNodes(head, q, val);
        ListNode z;
        ListNode* p = &z;

        while (q.size()) {
            p->next = q.front();
            p = p->next;
            q.pop();
        }
        return z.next;
    }

    void PushNodes(ListNode* head, std::queue<ListNode*>& q, int val) {
        ListNode* it = head;

        while (it != nullptr) {
            ListNode* tmp = it;
            it = it->next;
            if (tmp->val != val) {
                tmp->next = nullptr;
                q.push(tmp);
            } else {
                delete tmp;
            }
        }
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

TEST(t0, t1) {
    ListNode* head = ConstuctList(std::vector<int>{1, 2, 6, 3, 4, 5, 6});

    Solution s;
    head = s.RemoveElements(head, 6);
    ExpectEqList(head, std::vector<int>{1, 2, 3, 4, 5});
    FreeList(head);
}

TEST(t1, t1) {
    ListNode* head = ConstuctList(std::vector<int>{1, 2, 6, 3, 4, 5, 6});

    Solution s;
    head = s.RemoveElementsV2(head, 6);
    ExpectEqList(head, std::vector<int>{1, 2, 3, 4, 5});
    FreeList(head);
}

TEST(t2, t1) {
    ListNode* head = ConstuctList(std::vector<int>{1, 2, 6, 3, 4, 5, 6});

    Solution s;
    head = s.RemoveElementsV3(head, 6);
    ExpectEqList(head, std::vector<int>{1, 2, 3, 4, 5});
    FreeList(head);
}

TEST(t0, t2) {
    ListNode* head = ConstuctList(std::vector<int>{});

    Solution s;
    head = s.RemoveElements(head, 1);
    ExpectEqList(head, std::vector<int>{});
    FreeList(head);
}

TEST(t1, t2) {
    ListNode* head = ConstuctList(std::vector<int>{});

    Solution s;
    head = s.RemoveElementsV2(head, 1);
    ExpectEqList(head, std::vector<int>{});
    FreeList(head);
}

TEST(t2, t2) {
    ListNode* head = ConstuctList(std::vector<int>{});

    Solution s;
    head = s.RemoveElementsV3(head, 1);
    ExpectEqList(head, std::vector<int>{});
    FreeList(head);
}

TEST(t0, t3) {
    ListNode* head = ConstuctList(std::vector<int>{7, 7, 7, 7});

    Solution s;
    head = s.RemoveElements(head, 7);
    ExpectEqList(head, std::vector<int>{});
    FreeList(head);
}
TEST(t1, t3) {
    ListNode* head = ConstuctList(std::vector<int>{7, 7, 7, 7});

    Solution s;
    head = s.RemoveElementsV2(head, 7);
    ExpectEqList(head, std::vector<int>{});
    FreeList(head);
}

TEST(t2, t3) {
    ListNode* head = ConstuctList(std::vector<int>{7, 7, 7, 7});

    Solution s;
    head = s.RemoveElementsV3(head, 7);
    ExpectEqList(head, std::vector<int>{});
    FreeList(head);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

