// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <string>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;

// Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace { 
class Solution {
    vector<int> vec;

   public:
    Solution(ListNode *head) {
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

TEST(t0, t1) {
    std::vector<int> rt{1, 2, 3};
    ListNode *head = List::ConstructList(rt);
    Solution *s = new Solution(head);
    std::map<int, int> val_count;
    int count = 10000;
    for (int i = 0; i < count; i++) {
        val_count[s->GetRandom()]++;
    }
    std::set<int> set(rt.begin(), rt.end());
    for (auto &ptr : val_count) {
        EXPECT_NEAR(ptr.second, count / val_count.size(), 1000);
    }
    delete s;
    List::FreeList(head);
    // EXPECT_EQ(set.count(ret), 1);
}

}
