// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <map>
#include <random>
#include <set>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;

// Definition for singly-linked list.
using ListNode = List::ListNode<int>;

namespace {
class Solution {
    std::mt19937 m_gen;
    std::vector<int> m_vec;

   public:
    Solution(ListNode* head) : m_gen(std::random_device{}()) {
        while (head != nullptr) {
            m_vec.push_back(head->val);
            head = head->next;
        }
    }

    int GetRandom() {
        std::uniform_int_distribution<> dis(0, static_cast<int>(m_vec.size()) - 1);
        int const random_index = dis(m_gen);
        return m_vec.at(random_index);
    }
};

TEST(LinkedListRandomNode, t1) {
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
