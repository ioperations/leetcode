// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <limits>
#include <queue>
#include <utility>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace List;
using namespace std;

using MyListNode = List::ListNode<int>;

#define inf 0x7fffffff

namespace {
class LoserTree {
   private:
    // 以下存ls的下标
    int leaves_ls_st;
    //  int leaves_ls_ed;
    // 败者树根节点为ls[1]
    vector<int> ls;

    vector<int> *base;  // 数组副本(叶节点数据)
   public:
    LoserTree(vector<int> &nums) {
        const int nums_size = nums.size();
        if (nums_size == 0) return;
        const int power_num = ceil(log2(nums_size));
        const int leaves_num = 1 << power_num;
        this->base = &nums;
        this->leaves_ls_st = leaves_num;
        this->ls.resize(leaves_num << 1, -1);
        (*this->base).resize(leaves_num, inf);
        // 左闭右开
        for (int i = 0; i < leaves_num; i++) {
            this->ls[this->leaves_ls_st + i] = i;
        }
        this->ls[0] = this->Build(1);
    }

    // node_idx为ls中的下标
    //  返回:winner_id为base中的下标
    int Build(int node_idx) {
        if (node_idx >= this->leaves_ls_st) {
            return this->ls[node_idx];
        }
        const int lwinner_idx = Build(node_idx << 1);
        const int rwinner_idx = Build(node_idx << 1 | 1);
        int winner_idx = -1;
        // 父节点存loser
        if ((*this->base)[lwinner_idx] < (*this->base)[rwinner_idx]) {
            this->ls[node_idx] = rwinner_idx;
            winner_idx = lwinner_idx;
        } else {
            this->ls[node_idx] = lwinner_idx;
            winner_idx = rwinner_idx;
        }
        return winner_idx;
    }

    int GetMin() {
        const int ans = (*this->base)[ls[0]];
        // modify_fa_idx为ls的下标
        const int leaves_idx = this->leaves_ls_st + ls[0];
        (*this->base)[this->ls[leaves_idx]] = inf;
        this->Sort(leaves_idx >> 1, this->ls[0]);
        return ans;
    }

    // node_idx:ls的index
    // winner_idx:base的下标
    // 自底上更新败者树
    void Sort(int node_idx, int winner_idx) {
        while (node_idx) {
            if ((*this->base)[winner_idx] > (*this->base)[this->ls[node_idx]]) {
                swap(this->ls[node_idx], winner_idx);
            }
            node_idx >>= 1;
        }
        this->ls[0] = winner_idx;
    }
};

class Solution {
   public:
    std::vector<int> GetLeastNumbers(std::vector<int> &arr, int k) {
        std::vector<int> ans;
        LoserTree *lstree = new LoserTree(arr);
        for (int i = 0; i < k; i++) {
            const int min = lstree->GetMin();
            ans.push_back(min);
        }
        delete (lstree);
        return ans;
    }

    MyListNode *MergeTwoLists(MyListNode *a, MyListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        MyListNode head, *tail = &head, *a_ptr = a, *b_ptr = b;
        while (a_ptr && b_ptr) {
            if (a_ptr->val < b_ptr->val) {
                tail->next = a_ptr;
                a_ptr = a_ptr->next;
            } else {
                tail->next = b_ptr;
                b_ptr = b_ptr->next;
            }
            tail = tail->next;
        }
        tail->next = (a_ptr ? a_ptr : b_ptr);
        return head.next;
    }

    MyListNode *MergeKListsv1(vector<MyListNode *> &lists) {
        MyListNode *ans = nullptr;
        for (size_t i = 0; i < lists.size(); ++i) {
            ans = MergeTwoLists(ans, lists[i]);
        }
        return ans;
    }

    struct Status {
        int val;
        MyListNode *ptr;
        bool operator<(const Status &rhs) const { return val > rhs.val; }
    };

    std::priority_queue<Status> q;

    //  最小堆实现k路归并排序
    MyListNode *MergeKListsPriorityQueue(std::vector<MyListNode *> &lists) {
        for (auto *node : lists) {
            if (node) q.push({node->val, node});
        }
        MyListNode head, *tail = &head;
        while (!q.empty()) {
            auto f = q.top();
            q.pop();
            tail->next = f.ptr;
            tail = tail->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }

    ///* k路归并排序 升序
    ///* 听说用最小堆,还可以用败者树
    MyListNode *MergeKLists(vector<MyListNode *> &lists) {
        // 我们记录这一路 走到了什么位置
        std::vector<MyListNode *> cursors;

        cursors = lists;

        // 对于每一路我们拿出值最小的那个值(这个node !=
        // nullptr)，并将这一路的游标向右移动一格

        MyListNode *head = nullptr;
        MyListNode *pre;

        int first = true;

        while (true) {
            MyListNode *candidate =
                nullptr;  // 所以现在的问题是怎样确定这个candidate
            const int val = std::numeric_limits<int>::max();
            for (auto &cur_cursor : cursors) {
                if (cur_cursor == nullptr) {
                    continue;
                }
                if (cur_cursor->val < val) {
                    candidate = cur_cursor;
                }
            }

            if (candidate == nullptr) {
                break;
            }

            if (first) {
                head = candidate;
                pre = head;
                first = false;
            } else {
                pre->next = candidate;
                pre = pre->next;
            }

            // 现在当前的candidate的node需要向下一格
            candidate = candidate->next;
        }

        return head;
    }
};

TEST(memleak, merge_k_sorted_list_23) {
    MyListNode *n1 = new MyListNode(1);
    MyListNode *n2 = new MyListNode(3);
    MyListNode *n3 = new MyListNode(4);
    n1->next = n2;
    n2->next = n3;

    FreeList(n1);
}

TEST(memleak, t2) {
    std::vector<int> list1{1, 4, 5};

    MyListNode *n1 = ConstructList(list1);
    FreeList(n1);
}

TEST(memleak, t3) {
    std::vector<int> list1{1, 4, 5};

    MyListNode *n1 = ConstructList<int>(list1);
    FreeList(n1);
}

TEST(merge_k_sorted_list_v2, t1_1) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]
    std::vector<int> list1{1, 4, 5};
    std::vector<int> list2{1, 3, 4};
    std::vector<int> list3{2, 6};

    MyListNode *n1 = ConstructList(list1);
    MyListNode *n2 = ConstructList(list2);
    MyListNode *n3 = ConstructList(list3);

    std::vector<MyListNode *> merge_list{n1, n2, n3};

    Solution s;
    // 1->1->2->3->4->4->5->6
    auto *ret = s.MergeKListsv1(merge_list);

    FreeList(ret);
}

void ExpectEqList(MyListNode *list, const std::vector<int> &elemets) {
    int count = 0;
    MyListNode *ptr = list;
    while (ptr != nullptr) {
        EXPECT_EQ(ptr->val, elemets[count]);
        ptr = ptr->next;
        count++;
    }
}

TEST(merge_k_sorted_list_v2, priority_queue) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]
    std::vector<int> list1{1, 4, 5};
    std::vector<int> list2{1, 3, 4};
    std::vector<int> list3{2, 6};

    MyListNode *n1 = ConstructList(list1);
    MyListNode *n2 = ConstructList(list2);
    MyListNode *n3 = ConstructList(list3);

    std::vector<MyListNode *> merge_list{n1, n2, n3};

    Solution s;
    // 1->1->2->3->4->4->5->6
    auto *ret = s.MergeKListsPriorityQueue(merge_list);

    std::vector<int> expected{1, 1, 2, 3, 4, 4, 5, 6};
    ExpectEqList(ret, expected);
    FreeList(ret);
}

TEST(merge_k_sorted_list_v2, null) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]

    std::vector<MyListNode *> merge_list{};

    Solution s;
    auto *ret = s.MergeKLists(merge_list);

    EXPECT_EQ(ret, nullptr);
    // FreeListList(ret);
}

TEST(merge_k_sorted_list_v2, null2) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]
    std::vector<int> list1{};

    MyListNode *n1 = ConstructList(list1);
    std::vector<MyListNode *> merge_list{n1};

    Solution s;
    auto *ret = s.MergeKLists(merge_list);

    EXPECT_EQ(ret, nullptr);

    FreeList(n1);
}

}  // namespace
