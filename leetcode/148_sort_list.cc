// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the head of a linked list, return the list after sorting it in ascending
order.
*/
#include <vector>

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

/**
 * @brief 更加简单的方式从一个数组当中来创建一个list
 * @param @elemenets 要创建的list的数组
 * @return 链表的头，用户需要free掉
 */
ListNode *ConstructList(const std::vector<int> &elemenets) {
    ListNode head;
    ListNode *tail = &head;

    for (auto &ptr : elemenets) {
        tail->next = new ListNode(ptr);
        tail = tail->next;
    }

    return head.next;
}

/**
 * @brief 释放掉链表的内存
 * @param @list 链表的头
 * @return nil
 */
void FreeListList(ListNode *list) {
    if (list == nullptr) {
        return;
    }
    FreeListList(list->next);
    if (list != nullptr) {
        delete list;
        list = nullptr;
    }
}

#include <gtest/gtest.h>

#include <iostream>

void ExpectEqList(ListNode *list, const std::vector<int> &elemets) {
    int count = 0;
    ListNode *ptr = list;
    while (ptr != nullptr) {
        EXPECT_EQ(ptr->val, elemets[count]);
        ptr = ptr->next;
        count++;
    }
}

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    ListNode *n = ConstructList(std::vector<int>{4, 2, 1, 3});
    Solution s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{1, 2, 3, 4});
    FreeListList(n);
}

TEST(t1, t1) {
    ListNode *n = ConstructList(std::vector<int>{4, 2, 1, 3});
    SolutionV2 s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{1, 2, 3, 4});
    FreeListList(n);
}

TEST(t0, t2) {
    ListNode *n = ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
    Solution s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
    FreeListList(n);
}

TEST(t1, t2) {
    ListNode *n = ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
    SolutionV2 s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
    FreeListList(n);
}

TEST(t0, t3) {
    ListNode *n = ConstructList(std::vector<int>{});
    Solution s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{});
    FreeListList(n);
}

TEST(t1, t3) {
    ListNode *n = ConstructList(std::vector<int>{});
    SolutionV2 s;
    n = s.SortList(n);
    ExpectEqList(n, std::vector<int>{});
    FreeListList(n);
}

#include <benchmark/benchmark.h>

#include <algorithm>
#include <vector>

void BenchV2(benchmark::State &state) {
    for (auto _ : state) {
        ListNode *n = ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
        SolutionV2 s;
        n = s.SortList(n);
        ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
        FreeListList(n);
    }
}
BENCHMARK(BenchV2);

void BenchV1(benchmark::State &state) {
    for (auto _ : state) {
        ListNode *n = ConstructList(std::vector<int>{-4, 5, 3, 4, 0});
        Solution s;
        n = s.SortList(n);
        ExpectEqList(n, std::vector<int>{-4, 0, 3, 4, 5});
        FreeListList(n);
    }
}
BENCHMARK(BenchV1);

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    const int ret = RUN_ALL_TESTS();
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return ret;
}
