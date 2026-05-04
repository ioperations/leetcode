// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A linked list of length n is given such that each node contains an additional
random pointer, which could point to any node in the list, or null.↳

Construct a deep copy of the list. The deep copy should consist of exactly n
brand new nodes, where each new node has its value set to the value of its
corresponding original node. Both the next and random pointer of the new nodes
should point to new nodes in the copied list such that the pointers in the
original list and copied list represent the same list state. None of the
pointers in the new list should point to nodes in the original list. For
example, if there are two nodes X and Y in the original list, where X.random -->
Y, then for the corresponding two nodes x and y in the copied list, x.random -->
y. Return the head of the copied linked list. The linked list is represented in
the input/output as a list of n nodes. Each node is represented as a pair of
[val, random_index] where: val: an integer representing Node.val random_index:
the index of the node (range from 0 to n-1) that the random pointer points to,
or null if it does not point to any node. Your code will only be given the head
of the original linked list.*/

#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace {
class Node {
   public:
    int m_val;
    Node* m_next{nullptr};
    Node* m_random{nullptr};

    Node(int my_val) : m_val(my_val) {}
};

class Solution {
   public:
    Node* CopyRandomList(Node* head) {
        Node dummy_new(0);
        Node dummy_old(1);
        dummy_old.m_next = head;
        Node* ite_new = &dummy_new;
        Node* ite_old = dummy_old.m_next;
        std::unordered_map<Node*, int> map;
        std::vector<Node*> new_nodes;
        int i = 0;
        while (ite_old != nullptr) {
            ite_new->m_next = new Node(ite_old->m_val);
            map.emplace(ite_old, i);
            ite_old = ite_old->m_next;
            ite_new = ite_new->m_next;
            new_nodes.push_back(ite_new);

            i++;
        }

        ite_new = &dummy_new;
        Node* ite_old_dup = dummy_old.m_next;
        i = 0;
        while (ite_new->m_next != nullptr) {
            if (ite_old_dup->m_random != nullptr) {
                ite_new->m_next->m_random = new_nodes.at(map.at(ite_old_dup->m_random));
            }
            ite_new = ite_new->m_next;
            ite_old_dup = ite_old_dup->m_next;
            i++;
        }

        return dummy_new.m_next;
    }
};

#include <optional>

#define null std::nullopt

/// 从vec当中构造链表
Node* ConstructNode(std::vector<std::vector<std::optional<int>>>& vec) {
    Node dummy(0);
    Node* ite = &dummy;
    std::vector<Node*> cache;
    cache.reserve(vec.size());
    for (auto& ptr : vec) {
        ite->m_next = new Node(ptr.at(0).value());
        ite = ite->m_next;
        cache.push_back(ite);
    }
    ite = &dummy;

    int const len = static_cast<int>(vec.size());
    int i = 0;
    while (ite->m_next != nullptr && i < len) {
        if (vec.at(i).at(1).has_value()) {
            ite->m_next->m_random = cache.at(vec.at(i).at(1).value());
        }
        i++;
        ite = ite->m_next;
    }
    return dummy.m_next;
}

/// 从链表当中恢复到vec
std::vector<std::vector<std::optional<int>>> RestoreNode(Node* node) {
    std::vector<std::vector<std::optional<int>>> ret;
    std::unordered_map<Node*, int> map;

    Node* ite = node;
    int i = 0;
    while (ite != nullptr) {
        map[ite] = i;
        std::vector<std::optional<int>> myret(2, std::optional<int>());
        myret.at(0) = ite->m_val;
        ite = ite->m_next;
        ret.push_back(myret);
        i++;
    }
    ite = node;
    i = 0;
    while (ite != nullptr) {
        if (ite->m_random != nullptr) {
            ret.at(i).at(1) = map[ite->m_random];
        }
        i++;
        ite = ite->m_next;
    }

    ite = node;
    while (ite != nullptr) {
        Node* const now = ite;
        ite = now->m_next;
        delete now;
    }

    return ret;
}

TEST(Base, t1) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    std::vector<std::vector<std::optional<int>>> const output =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    Node* node = ConstructNode(head);
    auto vec = RestoreNode(node);
    EXPECT_EQ(output, vec);
}

TEST(CopyListWithRandomPointer, t1) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    std::vector<std::vector<std::optional<int>>> const output =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    Node* node = ConstructNode(head);
    Solution sl;
    Node* ret = sl.CopyRandomList(node);
    auto vec = RestoreNode(ret);
    RestoreNode(node);  // do the free things
    EXPECT_EQ(output, vec);
}

TEST(CopyListWithRandomPointer, t2) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{{1, 1}, {2, 1}};
    std::vector<std::vector<std::optional<int>>> const output =
        std::vector<std::vector<std::optional<int>>>{{1, 1}, {2, 1}};
    Node* node = ConstructNode(head);
    Solution sl;
    Node* ret = sl.CopyRandomList(node);
    auto vec = RestoreNode(ret);
    RestoreNode(node);  // do the free things
    EXPECT_EQ(output, vec);
}

TEST(CopyListWithRandomPointer, t3) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{
            {3, null}, {3, 0}, {3, null}};
    std::vector<std::vector<std::optional<int>>> const output =
        std::vector<std::vector<std::optional<int>>>{
            {3, null}, {3, 0}, {3, null}};
    Node* node = ConstructNode(head);
    Solution sl;
    Node* ret = sl.CopyRandomList(node);
    auto vec = RestoreNode(ret);
    RestoreNode(node);  // do the free things
    EXPECT_EQ(output, vec);
}

}  // namespace
