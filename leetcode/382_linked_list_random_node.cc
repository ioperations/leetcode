#include <cstdlib>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
    vector<int> vec;

   public:
    Solution(ListNode* head) {
        while (head != nullptr) {
            vec.push_back(head->val);
            head = head->next;
        }
    }

    int GetRandom() {
        int random_index = rand() / (RAND_MAX + 1.0) * vec.size();
        return vec[random_index];
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
    std::vector<int> rt{1, 2, 3};
    ListNode* head = ConstuctList(rt);
    Solution* s = new Solution(head);
    std::map<int, int> val_count;
    int count = 10000;
    for (int i = 0; i < count; i++) {
        val_count[s->GetRandom()]++;
    }
    std::set<int> set(rt.begin(), rt.end());
    for (auto& ptr : val_count) {
        EXPECT_NEAR(ptr.second, count / val_count.size(), 1000);
    }
    delete s;
    FreeList(head);
    // EXPECT_EQ(set.count(ret), 1);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
