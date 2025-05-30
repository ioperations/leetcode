// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <cstdlib>
#include <map>
#include <set>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;

// Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
    vector<int> m_vec;

   public:
    Solution(ListNode* head) {
        while (head != nullptr) {
            m_vec.push_back(head->val);
            head = head->next;
        }
    }

    int GetRandom() {
        int const random_index = rand() / (RAND_MAX + 1.0) * m_vec.size();
        return m_vec[random_index];
    }
};

TEST(linked_list_random_node, t1) {
    std::vector<int> rt{1, 2, 3};
    ListNode* head = List::ConstructList(rt);
    auto* s = new Solution(head);
    std::map<int, int> val_count;
    int const count = 10000;
    for (int i = 0; i < count; i++) {
        val_count[s->GetRandom()]++;
    }
    std::set<int> const set(rt.begin(), rt.end());
    for (auto& ptr : val_count) {
        EXPECT_NEAR(ptr.second, count / val_count.size(), 1000);
    }
    delete s;
    List::FreeList(head);
    // EXPECT_EQ(set.count(ret), 1);
}

}  // namespace
