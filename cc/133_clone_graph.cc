// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a reference of a node in a connected undirected graph.
Return a deep copy (clone) of the graph.
Each node in the graph contains a value (int) and a list (List[Node]) of its
neighbors.
class Node {
    public int val;
    public List<Node> neighbors;
}
Test case format:
For simplicity, each node's value is the same as the node's index (1-indexed).
For example, the first node with val == 1, the second node with val == 2, and so
on. The graph is represented in the test case using an adjacency list.
An adjacency list is a collection of unordered lists used to represent a finite
graph. Each list describes the set of neighbors of a node in the graph.
The given node will always be the first node with val = 1. You must return the
copy of the given node as a reference to the cloned graph.
*/

#include <map>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

// Definition for a Node.
#include <stddef.h>

namespace {
class Node {
   public:
    int val;
    vector<Node *> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int my_val) {
        val = my_val;
        neighbors = vector<Node *>();
    }
    Node(int my_val, vector<Node *> my_neighbors) {
        val = my_val;
        neighbors = my_neighbors;
    }
};

class Solution {
   public:
    unordered_map<int, Node *> track;

    Node *CloneGraph(Node *node) {
        // node is NULL then graph is empty
        if (node == NULL) return NULL;

        // return node object from track if already created
        if (track.count(node->val)) return track[node->val];

        // create new node from node value
        Node *n_node = new Node(node->val);

        // store new node object in track
        track[node->val] = n_node;

        // add neighbor node objects of current node in to new node's neighbor
        // from DFS call
        for (int i = 0; i < node->neighbors.size(); i++) {
            n_node->neighbors.push_back(CloneGraph(node->neighbors[i]));
        }

        // return new node object
        return n_node;
    }

    unordered_map<Node *, shared_ptr<Node>> visited;

    Node *CloneGraphV2(Node *node) {
        if (node == nullptr) {
            return nullptr;
        }

        visited.clear();
        queue<Node *> q;
        q.push(node);
        visited[node] = make_shared<Node>(node->val);

        while (!q.empty()) {
            auto *current = q.front();
            q.pop();

            for (auto *v : current->neighbors) {
                if (visited.find(v) == visited.end()) {
                    visited[v] = make_shared<Node>(v->val);
                    q.push(v);
                }
                visited[current]->neighbors.push_back(visited[v].get());
            }
        }

        return visited[node].get();
    }
};

Node *GetOrInsert(std::map<int, Node *> &map, int v) {
    if (map.find(v) == map.end()) {
        Node *n = new Node(v);
        map[v] = n;
    }
    return map[v];
}

Node *BuildNode(vector<std::vector<int>> &adj_list) {
    std::map<int, Node *> node;
    int count = 1;
    for (auto &ptr : adj_list) {
        for (auto &z : ptr) {
            Node *to_insert = GetOrInsert(node, z);
            Node *to_be_insert = GetOrInsert(node, count);
            to_be_insert->neighbors.push_back(to_insert);
        }
        count++;
    }
    if (node.size()) {
        return node[1];
    }
    return nullptr;
}

auto FreeGraph(Node *node) -> void {
    if (node == nullptr) {
        return;
    }

    std::function<void(Node *, std::map<int, Node *> &)> impl =
        [&](Node *node, std::map<int, Node *> &waiting) {
            if (waiting.find(node->val) != waiting.end()) {
                return;
            }
            waiting[node->val] = node;

            for (auto &ptr : node->neighbors) {
                impl(ptr, waiting);
            }
        };

    std::map<int, Node *> map;
    impl(node, map);

    for (auto &ptr : map) {
        delete ptr.second;
    }
}

void CheckEqual(Node *node, std::vector<std::vector<int>> &adj_list) {
    // TODO:: to implemen
}

TEST(clone_graph, t1) {
    std::vector<std::vector<int>> adj_list = {
        std::vector<int>{2, 4}, std::vector<int>{1, 3}, std::vector<int>{2, 4},
        std::vector<int>{1, 3}};
    Node *node = BuildNode(adj_list);
    Solution sl;
    auto *ret = sl.CloneGraph(node);
    FreeGraph(node);
    FreeGraph(ret);
    CheckEqual(ret, adj_list);
    // Explanation: There are 4 nodes in the graph.
    // 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val =
    // 4). 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node
    // (val = 3). 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th
    // node (val = 4). 4th node (val = 4)'s neighbors are 1st node (val = 1) and
    // 3rd node (val = 3).
}

TEST(clone_graph, t2) {
    std::vector<std::vector<int>> adj_list = {std::vector<int>{}};
    Node *node = BuildNode(adj_list);
    Solution sl;
    auto *ret = sl.CloneGraph(node);
    FreeGraph(node);
    FreeGraph(ret);
    CheckEqual(ret, adj_list);
    /*Note that the input contains one empty list. The graph consists of only
     * one node with val = 1 and it does not have any neighbors*/
}

TEST(clone_graph, t3) {
    std::vector<std::vector<int>> adj_list = {};
    Node *node = BuildNode(adj_list);
    Solution sl;
    auto *ret = sl.CloneGraph(node);
    FreeGraph(node);
    FreeGraph(ret);
    CheckEqual(ret, adj_list);
    /*This an empty graph, it does not have any nodes.*/
}

TEST(clone_graph_v2, t1) {
    std::vector<std::vector<int>> adj_list = {
        std::vector<int>{2, 4}, std::vector<int>{1, 3}, std::vector<int>{2, 4},
        std::vector<int>{1, 3}};
    Node *node = BuildNode(adj_list);
    Solution sl;
    auto *ret = sl.CloneGraphV2(node);
    FreeGraph(node);
    CheckEqual(ret, adj_list);
    // Explanation: There are 4 nodes in the graph.
    // 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val =
    // 4). 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node
    // (val = 3). 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th
    // node (val = 4). 4th node (val = 4)'s neighbors are 1st node (val = 1) and
    // 3rd node (val = 3).
}

TEST(clone_graph_v2, t2) {
    std::vector<std::vector<int>> adj_list = {std::vector<int>{}};
    Node *node = BuildNode(adj_list);
    Solution sl;
    auto *ret = sl.CloneGraphV2(node);
    FreeGraph(node);
    CheckEqual(ret, adj_list);
    /*Note that the input contains one empty list. The graph consists of only
     * one node with val = 1 and it does not have any neighbors*/
}

TEST(clone_graph_v2, t3) {
    std::vector<std::vector<int>> adj_list = {};
    Node *node = BuildNode(adj_list);
    Solution sl;
    auto *ret = sl.CloneGraphV2(node);
    FreeGraph(node);
    CheckEqual(ret, adj_list);
    /*This an empty graph, it does not have any nodes.*/
}

}  // namespace
