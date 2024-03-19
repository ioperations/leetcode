// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the head of a sorted linked list, delete all nodes that have duplicate
numbers, leaving only distinct numbers from the original list. Return the linked
list sorted as well.
*/

#include <vector>

#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using ListNode = List::ListNode<int>;

namespace {
class Solution {
   public:
    ListNode *DeleteDuplicates(ListNode *head) {
        std::vector<int> vec;
        head = DeleteDuplicatesV1(head, vec);

        for (auto &ptr : vec) {
            head = RemoveNodeByValue(head, ptr);
        }

        return head;
    }

    ListNode *RemoveNodeByValue(ListNode *head, int v) {
        if (head == nullptr) {
            return head;
        }

        ListNode *ret = head;
        if (head->val == v) {
            ListNode *tmp = head;
            ret = head->next;
            delete tmp;
        } else {
            ListNode *now_ret = RemoveNodeByValue(head->next, v);
            ret->next = now_ret;
        }
        return ret;
    }

    ListNode *DeleteDuplicatesV1(ListNode *head, std::vector<int> &val) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *slow = head, *fast = head->next;

        while (fast != nullptr) {
            if (fast->val == slow->val) {
                // remove current fast
                ListNode *tmp = fast;
                fast = fast->next;
                slow->next = fast;
                val.push_back(tmp->val);
                delete tmp;
            } else {
                // advance
                fast = fast->next;
                slow = slow->next;
            }
        }

        return head;
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

TEST(test, t1) {
    std::vector<int> head{1, 2, 3, 4, 5};
    std::vector<int> output{2, 3, 4, 5};
    ListNode *root = List::ConstructList(head);

    Solution sl;
    root = sl.RemoveNodeByValue(root, 1);

    ExpectEqList(root, output);
    List::FreeList(root);
}

TEST(remove_duplicates_from_sorted_list_ii, t1) {
    std::vector<int> head{1, 2, 3, 3, 4, 4, 5};

    /*
     ___     ___     ___     ___     ___     ___     ___
    | 1 |-->| 2 |-->| 3 |-->| 3 |-->| 4 |-->| 4 |-->| 5 |
    |___|   |___|   |___|   |___|   |___|   |___|   |___|

              ___     ___     ___
             | 1 |-->| 2 |-->| 5 |
             |___|   |___|   |___|
    */
    std::vector<int> output{1, 2, 5};
    ListNode *root = List::ConstructList(head);

    Solution sl;
    root = sl.DeleteDuplicates(root);

    ExpectEqList(root, output);
    List::FreeList(root);
}

TEST(remove_duplicates_from_sorted_list_ii, t2) {
    std::vector<int> head{1, 1, 1, 2, 3};

    /*
     ___     ___     ___     ___     ___
    | 1 |-->| 1 |-->| 1 |-->| 2 |-->| 3 |
    |___|   |___|   |___|   |___|   |___|

              ___     ___
             | 2 |-->| 3 |
             |___|   |___|
    */

    std::vector<int> output{2, 3};
    ListNode *root = List::ConstructList(head);

    Solution sl;
    root = sl.DeleteDuplicates(root);

    ExpectEqList(root, output);
    List::FreeList(root);
}

}  // namespace
