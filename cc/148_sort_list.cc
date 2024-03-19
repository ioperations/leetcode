// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the head of a linked list, return the list after sorting it in ascending
order.
*/

#include <vector>

#include "benchmark/benchmark.h"
#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using ListNode = List::ListNode<int>;

namespace {
class SolutionV2 {
   public:
    ListNode *SortList(ListNode *head) {
        // If List Contain a Single or 0 Node
        if (head == nullptr || head->next == nullptr) return head;

        ListNode *temp = nullptr;
        ListNode *slow = head;
        ListNode *fast = head;

        // 2 pointer appraoach / turtle-hare Algorithm (Finding the middle
        // element)
        while (fast != nullptr && fast->next != nullptr) {
            temp = slow;
            slow = slow->next;        // slow increment by 1
            fast = fast->next->next;  // fast incremented by 2
        }
        temp->next = nullptr;  // end of first left half

        ListNode *l1 = SortList(head);  // left half recursive call
        ListNode *l2 = SortList(slow);  // right half recursive call

        return Mergelist(l1, l2);  // mergelist Function call
    }

    // MergeSort Function O(n*logn)
    ListNode *Mergelist(ListNode *l1, ListNode *l2) {
        ListNode z(0);
        ListNode *ptr = &z;
        ListNode *curr = ptr;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }

            curr = curr->next;
        }

        // for unqual length linked list

        if (l1 != nullptr) {
            curr->next = l1;
            l1 = l1->next;
        }

        if (l2 != nullptr) {
            curr->next = l2;
            l2 = l2->next;
        }

        return ptr->next;
    }
};

class Solution {
   public:
    ListNode *SortList(ListNode *head) { return SortList(head, nullptr); }

    ListNode *SortList(ListNode *head, ListNode *tail) {
        // pass

        if (head == nullptr) {
            return nullptr;
        }
        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }

        ListNode *fast = head;
        ListNode *slow = head;

        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) {
                fast = fast->next;
            }
        }
        ListNode *mid = slow;
        return Merge(SortList(head, mid), SortList(mid, tail));
    }

    ListNode *Merge(ListNode *head, ListNode *tail) {
        ListNode dummy_head;
        ListNode *temp = &dummy_head, *temp1 = head, *temp2 = tail;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;

            } else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        } else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummy_head.next;
    }
};

void ExpectEqList(ListNode *list, const std::vector<int> &elemets) {
    int count = 0;
    ListNode *ptr = list;
    while (ptr != nullptr) {
        EXPECT_EQ(ptr->val, elemets[count]);
        ptr = ptr->next;
        count++;
    }
}

TEST(sort_list, t1) {
    ListNode *n = List::ConstructList(std::vector<int>{4, 2, 1, 3});
    Solution s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{1, 2, 3, 4});
    List::FreeList(n);
}

TEST(sort_list_v2, t1) {
    ListNode *n = List::ConstructList(std::vector<int>{4, 2, 1, 3});
    SolutionV2 s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{1, 2, 3, 4});
    List::FreeList(n);
}

TEST(sort_list, t2) {
    ListNode *n = List::ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
    Solution s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
    List::FreeList(n);
}

TEST(sort_list_v2, t2) {
    ListNode *n = List::ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
    SolutionV2 s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
    List::FreeList(n);
}

TEST(sort_list, t3) {
    ListNode *n = List::ConstructList(std::vector<int>{});
    Solution s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{});
    List::FreeList(n);
}

TEST(sort_list_v2, t3) {
    ListNode *n = List::ConstructList(std::vector<int>{});
    SolutionV2 s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{});
    List::FreeList(n);
}

void BenchV2(benchmark::State &state) {
    for (auto _ : state) {
        ListNode *n = List::ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
        SolutionV2 s;
        n = s.SortList(n);
        ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
        List::FreeList(n);
    }
}
BENCHMARK(BenchV2);

void BenchV1(benchmark::State &state) {
    for (auto _ : state) {
        ListNode *n = List::ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
        Solution s;
        n = s.SortList(n);
        ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
        List::FreeList(n);
    }
}
BENCHMARK(BenchV1);

}  // namespace
