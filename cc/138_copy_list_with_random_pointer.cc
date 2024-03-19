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

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Node {
   public:
    int val;
    Node *next;
    Node *random;

    Node(int my_val) {
        val = my_val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
   public:
    Node *CopyRandomList(Node *head) {
        Node dummy_new(0);
        Node dummy_old(1);
        dummy_old.next = head;
        Node *ite_new = &dummy_new;
        Node *ite_old = dummy_old.next;
        std::unordered_map<Node *, int> map;
        std::vector<Node *> new_nodes;
        int i = 0;
        while (ite_old != nullptr) {
            ite_new->next = new Node(ite_old->val);
            map[ite_old] = i;
            ite_old = ite_old->next;
            ite_new = ite_new->next;
            new_nodes.push_back(ite_new);

            i++;
        }

        ite_new = &dummy_new;
        ite_old = dummy_old.next;
        i = 0;
        while (ite_new->next != nullptr) {
            if (ite_old->random != nullptr) {
                ite_new->next->random = new_nodes[map[ite_old->random]];
            }
            ite_new = ite_new->next;
            ite_old = ite_old->next;
            i++;
        }

        return dummy_new.next;
    }
};

#include <optional>

#define null std::optional<int>()

/// 从vec当中构造链表
Node *ConstructNode(std::vector<std::vector<std::optional<int>>> &vec) {
    Node dummy(0);
    Node *ite = &dummy;
    std::vector<Node *> cache;
    cache.reserve(vec.size());
    for (auto &ptr : vec) {
        ite->next = new Node(ptr[0].value());
        ite = ite->next;
        cache.push_back(ite);
    }
    ite = &dummy;

    int i = 0;
    const int len = vec.size();
    while (ite->next != nullptr && i < len) {
        if (vec[i][1].has_value()) {
            ite->next->random = cache[vec[i][1].value()];
        }
        i++;
        ite = ite->next;
    }
    return dummy.next;
}

/// 从链表当中恢复到vec
std::vector<std::vector<std::optional<int>>> RestoreNode(Node *node) {
    std::vector<std::vector<std::optional<int>>> ret;
    std::unordered_map<Node *, int> map;

    Node *ite = node;
    int i = 0;
    while (ite != nullptr) {
        map[ite] = i;
        std::vector<std::optional<int>> myret(2, std::optional<int>());
        myret[0] = ite->val;
        ite = ite->next;
        ret.push_back(myret);
        i++;
    }
    ite = node;
    i = 0;
    while (ite != nullptr) {
        if (ite->random != nullptr) {
            ret[i][1] = map[ite->random];
        }
        i++;
        ite = ite->next;
    }

    ite = node;
    while (ite != nullptr) {
        Node *now = ite;
        ite = now->next;
        delete now;
    }
    delete ite;

    return ret;
}

TEST(base, t1) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    std::vector<std::vector<std::optional<int>>> output =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    Node *node = ConstructNode(head);
    auto vec = RestoreNode(node);
    EXPECT_EQ(output, vec);
}

TEST(copy_list_with_random_pointer, t1) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    std::vector<std::vector<std::optional<int>>> output =
        std::vector<std::vector<std::optional<int>>>{
            {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    Node *node = ConstructNode(head);
    Solution sl;
    Node *ret = sl.CopyRandomList(node);
    auto vec = RestoreNode(ret);
    RestoreNode(node);  // do the free things
    EXPECT_EQ(output, vec);
}

TEST(copy_list_with_random_pointer, t2) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{{1, 1}, {2, 1}};
    std::vector<std::vector<std::optional<int>>> output =
        std::vector<std::vector<std::optional<int>>>{{1, 1}, {2, 1}};
    Node *node = ConstructNode(head);
    Solution sl;
    Node *ret = sl.CopyRandomList(node);
    auto vec = RestoreNode(ret);
    RestoreNode(node);  // do the free things
    EXPECT_EQ(output, vec);
}

TEST(copy_list_with_random_pointer, t3) {
    std::vector<std::vector<std::optional<int>>> head =
        std::vector<std::vector<std::optional<int>>>{
            {3, null}, {3, 0}, {3, null}};
    std::vector<std::vector<std::optional<int>>> output =
        std::vector<std::vector<std::optional<int>>>{
            {3, null}, {3, 0}, {3, null}};
    Node *node = ConstructNode(head);
    Solution sl;
    Node *ret = sl.CopyRandomList(node);
    auto vec = RestoreNode(ret);
    RestoreNode(node);  // do the free things
    EXPECT_EQ(output, vec);
}

}  // namespace
