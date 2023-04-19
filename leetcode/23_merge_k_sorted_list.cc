// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <climits>
#include <cmath>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
class ListNodeTemplate {
   public:
    T val;
    ListNodeTemplate<T> *next;
    ListNodeTemplate() : val(), next(nullptr) {}
    ListNodeTemplate(T x) : val(x), next(nullptr) {}
    ListNodeTemplate(T x, ListNodeTemplate<T> *next) : val(x), next(next) {}
};

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#define inf 0x7fffffff
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
        int nums_size = nums.size();
        if (nums_size == 0) return;
        int power_num = ceil(log2(nums_size));
        int leaves_num = 1 << power_num;
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
        int lwinner_idx = Build(node_idx << 1);
        int rwinner_idx = Build(node_idx << 1 | 1);
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
        int ans = (*this->base)[ls[0]];
        // modify_fa_idx为ls的下标
        int leaves_idx = this->leaves_ls_st + ls[0];
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
            int min = lstree->GetMin();
            ans.push_back(min);
        }
        delete (lstree);
        return ans;
    }

    ListNode *MergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *a_ptr = a, *b_ptr = b;
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

    ListNode *MergeKListsv1(vector<ListNode *> &lists) {
        ListNode *ans = nullptr;
        for (size_t i = 0; i < lists.size(); ++i) {
            ans = MergeTwoLists(ans, lists[i]);
        }
        return ans;
    }

    struct Status {
        int val;
        ListNode *ptr;
        bool operator<(const Status &rhs) const { return val > rhs.val; }
    };

    std::priority_queue<Status> q;

    //  最小堆实现k路归并排序
    ListNode *MergeKListsPriorityQueue(std::vector<ListNode *> &lists) {
        for (auto *node : lists) {
            if (node) q.push({node->val, node});
        }
        ListNode head, *tail = &head;
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
    ListNode *MergeKLists(vector<ListNode *> &lists) {
        // 我们记录这一路 走到了什么位置
        std::vector<ListNode *> cursors;

        cursors = lists;

        // 对于每一路我们拿出值最小的那个值(这个node !=
        // nullptr)，并将这一路的游标向右移动一格

        ListNode *head = nullptr;
        ListNode *pre;

        int first = true;

        while (true) {
            ListNode *candidate =
                nullptr;  // 所以现在的问题是怎样确定这个candidate
            int val = std::numeric_limits<int>::max();
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

ListNode *ConstructList(std::vector<int> &elemenets) {
    ListNode *head = nullptr;
    ListNode *pre;
    ListNode *now;

    bool first = true;

    for (auto &ptr : elemenets) {
        now = new ListNode(ptr);
        if (first) {
            head = now;
            pre = head;
            first = false;
        } else {
            pre->next = now;
            pre = pre->next;
        }
    }

    return head;
}

/**
 * @brief 更加简单的方式从一个数组当中来创建一个list
 * @param @elemenets 要创建的list的数组
 * @return 链表的头，用户需要free掉
 */
ListNode *ConstructListV2(std::vector<int> &elemenets) {
    ListNode head;
    ListNode *tail = &head;

    for (auto &ptr : elemenets) {
        tail->next = new ListNode(ptr);
        tail = tail->next;
    }

    return head.next;
}

/**
 * @brief 更加简单的方式从一个数组当中来创建一个list 模版化
 * @param @elements 要创建的list的数组
 * @return  链表的头，用户需要free掉
 */
template <typename T>
ListNodeTemplate<T> *ConstructListV3(std::vector<T> &elements) {
    ListNodeTemplate<T> head;
    ListNodeTemplate<T> *tail = &head;

    for (auto &ptr : elements) {
        tail->next = new ListNodeTemplate<T>(ptr);
        tail = tail->next;
    }

    return head.next;
}

/**
 * @brief 释放掉链表的内存
 * @param @list 链表的头
 * @return nil
 */
template <typename T>
void FreeListListTemplate(ListNodeTemplate<T> *list) {
    if (list == nullptr) {
        return;
    }
    FreeListListTemplate(list->next);
    if (list != nullptr) {
        delete list;
        list = nullptr;
    }
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

TEST(memleak, t1) {
    ListNode *n1 = new ListNode(1);
    ListNode *n2 = new ListNode(3);
    ListNode *n3 = new ListNode(4);
    n1->next = n2;
    n2->next = n3;

    FreeListList(n1);
}

TEST(memleak, t2) {
    std::vector<int> list1{1, 4, 5};

    ListNode *n1 = ConstructListV2(list1);
    FreeListList(n1);
}

TEST(memleak, t3) {
    std::vector<int> list1{1, 4, 5};

    ListNodeTemplate<int> *n1 = ConstructListV3<int>(list1);
    FreeListListTemplate(n1);
}

TEST(t1, t1_1) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]
    std::vector<int> list1{1, 4, 5};
    std::vector<int> list2{1, 3, 4};
    std::vector<int> list3{2, 6};

    ListNode *n1 = ConstructList(list1);
    ListNode *n2 = ConstructList(list2);
    ListNode *n3 = ConstructList(list3);

    std::vector<ListNode *> merge_list{n1, n2, n3};

    Solution s;
    // 1->1->2->3->4->4->5->6
    auto *ret = s.MergeKListsv1(merge_list);

    FreeListList(ret);
}

void ExpectEqList(ListNode *list, const std::vector<int> &elemets) {
    int count = 0;
    ListNode *ptr = list;
    while (ptr != nullptr) {
        EXPECT_EQ(ptr->val, elemets[count]);
        ptr = ptr->next;
        count++;
    }
}

TEST(t1, priority_queue) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]
    std::vector<int> list1{1, 4, 5};
    std::vector<int> list2{1, 3, 4};
    std::vector<int> list3{2, 6};

    ListNode *n1 = ConstructList(list1);
    ListNode *n2 = ConstructList(list2);
    ListNode *n3 = ConstructList(list3);

    std::vector<ListNode *> merge_list{n1, n2, n3};

    Solution s;
    // 1->1->2->3->4->4->5->6
    auto *ret = s.MergeKListsPriorityQueue(merge_list);

    std::vector<int> expected{1, 1, 2, 3, 4, 4, 5, 6};
    ExpectEqList(ret, expected);
    FreeListList(ret);
}

TEST(t1, null) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]

    std::vector<ListNode *> merge_list{};

    Solution s;
    auto *ret = s.MergeKLists(merge_list);

    EXPECT_EQ(ret, nullptr);
    // FreeListList(ret);
}

TEST(t1, null2) {
    /// Input: lists = [[1,4,5],[1,3,4],[2,6]]
    /// Output: [1,1,2,3,4,4,5,6]
    std::vector<int> list1{};

    ListNode *n1 = ConstructList(list1);
    std::vector<ListNode *> merge_list{n1};

    Solution s;
    auto *ret = s.MergeKLists(merge_list);

    EXPECT_EQ(ret, nullptr);

    FreeListList(n1);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
