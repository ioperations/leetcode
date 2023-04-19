// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given the head of a singly linked list, return true if it is a palindrome.
*/

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#include <vector>

class Solution2 {
   public:
    bool IsPalindrome(ListNode *head) {
        auto *right = head;
        auto *left = head;

        // Left makes one step when right makes two
        while (right->next) {
            right = right->next;
            if (right->next) {
                right = right->next;
                left = left->next;
            }
        }

        // Now 'right' points to the last element, 'left' - to the middle,
        // or to the left half last element if number of elements is even.
        // Reversing right half, 'right' now points to the head of reversed
        // right half
        Reverse(left->next);
        left = head;

        // left half is longer if number is odd, so checking the right pointer
        while (right) {
            if (left->val != right->val) return false;
            left = left->next;
            right = right->next;
        }
        return true;
    }

    // common reverse algorithm
    static void Reverse(ListNode *from) noexcept {
        ListNode *prev = nullptr;
        ListNode *cur = from;
        ListNode *tmp = nullptr;
        while (cur) {
            tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
    }
};

class Solution {
   public:
    bool IsPalindrome(ListNode *head) {
        std::vector<ListNode *> vec;
        ListNode *z = head;
        while (z != nullptr) {
            vec.push_back(z);
            z = z->next;
        }

        return IsPalindrome(vec);
    }

    bool IsPalindrome(std::vector<ListNode *> &vec) {
        std::size_t size = vec.size();
        if (vec.size() == 1 || vec.size() == 0) {
            return true;
        }

        int left = 0;
        int right = 0;
        if (size % 2 == 0) {
            left = size / 2 - 1;
            right = size / 2;
        } else {
            left = size / 2 - 1;
            right = size / 2 + 1;
        }

        while (left >= 0) {
            if (vec[left]->val == vec[right]->val) {
                left--;
                right++;
            } else {
                return false;
            }
        }

        return true;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
ListNode *ConstuctList(const std::vector<int> &elemets) {
    ListNode head;
    ListNode *tail = &head;
    for (auto &pt : elemets) {
        tail->next = new ListNode(pt);
        tail = tail->next;
    }
    return head.next;
}

void FreeList(ListNode *head) {
    if (head == nullptr) {
        return;
    }
    FreeList(head->next);
    delete head;
}

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    ListNode *head = ConstuctList(std::vector<int>{1, 2, 2, 1});

    Solution s;
    bool ret = s.IsPalindrome(head);
    EXPECT_EQ(ret, true);

    FreeList(head);
}

TEST(t1, t1) {
    ListNode head(1);
    ListNode head2(2);
    ListNode head3(2);
    ListNode head4(1);
    head.next = &head2;
    head2.next = &head3;
    head3.next = &head4;

    Solution2 s;
    bool ret = s.IsPalindrome(&head);
    EXPECT_EQ(ret, true);
}

TEST(t0, t2) {
    ListNode *head = ConstuctList(std::vector<int>{1, 2});

    Solution s;
    bool ret = s.IsPalindrome(head);
    EXPECT_EQ(ret, false);

    FreeList(head);
}

TEST(t1, t2) {
    ListNode head(1);
    ListNode head2(2);
    head.next = &head2;

    Solution2 s;
    bool ret = s.IsPalindrome(&head);
    EXPECT_EQ(ret, false);
}

#include <benchmark/benchmark.h>

#include <algorithm>
#include <vector>

static void BenchFastSlow(benchmark::State &state) {
    Solution2 s;
    for (auto _ : state) {
        ListNode head(1);
        ListNode head2(2);
        ListNode head3(3);
        ListNode head4(4);
        ListNode head5(5);
        ListNode head6(6);
        ListNode head7(5);
        ListNode head8(4);
        ListNode head9(3);
        ListNode head10(2);
        ListNode head11(1);

        head.next = &head2;
        head2.next = &head3;
        head3.next = &head4;
        head4.next = &head5;
        head5.next = &head6;
        head6.next = &head7;
        head7.next = &head8;
        head8.next = &head9;
        head9.next = &head10;
        head10.next = &head11;

        bool ret = s.IsPalindrome(&head);
        EXPECT_EQ(ret, true);
    }
}
BENCHMARK(BenchFastSlow);
static void BenchMyVec(benchmark::State &state) {
    Solution s;
    for (auto _ : state) {
        ListNode head(1);
        ListNode head2(2);
        ListNode head3(3);
        ListNode head4(4);
        ListNode head5(5);
        ListNode head6(6);
        ListNode head7(5);
        ListNode head8(4);
        ListNode head9(3);
        ListNode head10(2);
        ListNode head11(1);

        head.next = &head2;
        head2.next = &head3;
        head3.next = &head4;
        head4.next = &head5;
        head5.next = &head6;
        head6.next = &head7;
        head7.next = &head8;
        head8.next = &head9;
        head9.next = &head10;
        head10.next = &head11;

        bool ret = s.IsPalindrome(&head);
        EXPECT_EQ(ret, true);
    }
}
BENCHMARK(BenchMyVec);

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return ret;
}
