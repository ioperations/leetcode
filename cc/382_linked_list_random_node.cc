// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <catch2/catch_test_macros.hpp>
#include <map>
#include <set>
#include <vector>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
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

}  // namespace
