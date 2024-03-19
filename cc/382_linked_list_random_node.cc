// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>

#include "catch2/catch_approx.hpp"
#include "datastruct_base.hh"

#define TEST(a, b) TEST_CASE(#a, #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

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

TEST(linked_list_random_node, t1) {
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
        REQUIRE(ptr.second == Catch::Approx(count / val_count.size()));
    }
    delete s;
    List::FreeList(head);
    // EXPECT_EQ(set.count(ret), 1);
}

}  // namespace
