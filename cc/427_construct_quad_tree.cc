// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a n * n matrix grid of 0's and 1's only. We want to represent the grid
with a Quad-Tree. Return the root of the Quad-Tree representing the grid. Notice
that you can assign the value of a node to True or False when isLeaf is False,
and both are accepted in the answer. A Quad-Tree is a tree data structure in
which each internal node has exactly four children. Besides, each node has two
attributes: val: True if the node represents a grid of 1's or False if the node
represents a grid of 0's. isLeaf: True if the node is leaf node on the tree or
namespace {
False if the node has the four children. class Node { public boolean val; public
boolean isLeaf; public Node topLeft; public Node topRight; public Node
bottomLeft; public Node bottomRight;
}
We can construct a Quad-Tree from a two-dimensional area using the following
steps:

If the current grid has the same value (i.e all 1's or all 0's) set isLeaf True
and set val to the value of the grid and set the four children to Null and stop.
If the current grid has different values, set isLeaf to False and set val to any
value and divide the current grid into four sub-grids as shown in the photo.
Recurse for each of the children with the proper sub-grid.


Quad-Tree format:

The output represents the serialized format of a Quad-Tree using level order
traversal, where null signifies a path terminator where no node exists below.

It is very similar to the serialization of the binary tree. The only difference
is that the node is represented as a list [isLeaf, val].

If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf,
val] and if the value of isLeaf or val is False we represent it as 0.

*/

#include <functional>
#include <optional>
#include <queue>

#include "gtest/gtest.h"

namespace {
class Node {
   public:
    bool m_val;
    bool m_is_leaf;
    Node* m_top_left;
    Node* m_top_right;
    Node* m_bottom_left;
    Node* m_bottom_right;

    Node()
        : m_val(false),
          m_is_leaf(false),
          m_top_left(nullptr),
          m_top_right(nullptr),
          m_bottom_left(nullptr),
          m_bottom_right(nullptr) {}

    Node(bool n_val, bool n_is_leaf)
        : m_val(n_val),
          m_is_leaf(n_is_leaf),
          m_top_left(nullptr),
          m_top_right(nullptr),
          m_bottom_left(nullptr),
          m_bottom_right(nullptr) {}

    Node(bool n_val, bool n_is_leaf, Node* n_top_left, Node* n_top_rightt,
         Node* n_bottom_left, Node* n_bottom_rightt)
        : m_val(n_val),
          m_is_leaf(n_is_leaf),
          m_top_left(n_top_left),
          m_top_right(n_top_rightt),
          m_bottom_left(n_bottom_left),
          m_bottom_right(n_bottom_rightt) {}
};
#include <vector>

using namespace std;

class Solution {
   public:
    Node* Construct(vector<vector<int>>& grid) {
        std::function<Node*(int i, int j, int len)> fun =
            [&](int i, int j, int len) -> Node* {
            if (len == 1) {
                return new Node(grid[i][j], true);
            }
            int const size = len / 2;
            auto* top_left = fun(i, j, size);
            auto* top_right = fun(i, j + size, size);
            auto* bottom_left = fun(i + size, j, size);
            auto* bottom_right = fun(i + size, j + size, size);
            if (top_left->m_is_leaf && top_right->m_is_leaf &&
                bottom_left->m_is_leaf && bottom_right->m_is_leaf) {
              if ((top_left->m_val == top_right->m_val) &&
                  (top_left->m_val == bottom_left->m_val) &&
                  (bottom_right->m_val == top_left->m_val)) {
                int const val = top_left->m_val;
                delete top_left;
                delete top_right;
                delete bottom_right;
                delete bottom_left;
                return new Node(val, true);
              }
            }
            return new Node(true, false, top_left, top_right, bottom_left,
                            bottom_right);
        };

        return fun(0, 0, grid.size());
    }
};

#define null optional<vector<int>>()

vector<optional<vector<int>>> FlattenQuadTree(Node* n) {
    // pass
    std::queue<Node*> q;
    q.push(n);
    vector<optional<vector<int>>> ret;
    while (q.size()) {
        auto* n = q.front();
        if (n == nullptr) {
            ret.push_back(null);
            ret.push_back(null);
            ret.push_back(null);
            ret.push_back(null);
        } else {
          if (n->m_is_leaf) {
            ret.emplace_back(vector<int>{n->m_is_leaf, n->m_val});
          } else {
            ret.emplace_back(vector<int>{n->m_is_leaf, n->m_val});
            q.push(n->m_top_left);
            q.push(n->m_top_right);
            q.push(n->m_bottom_left);
            q.push(n->m_bottom_right);
          }
            delete n;
        }
        q.pop();
    }
    return ret;
}

TEST(construct_quad_tree, t1) {
    vector<vector<int>> grid =
        vector<vector<int>>{vector<int>{0, 1}, vector<int>{1, 0}};
    vector<optional<vector<int>>> const output = vector<optional<vector<int>>>{
        // clang-format off
        vector<int>{0, 1},
        vector<int>{1, 0},
        vector<int>{1, 1},
        vector<int>{1, 1},
        vector<int>{1, 0}  // clang-format on
    };
    // Explanation
    // : The explanation of this example is shown below
    // : Notice that 0 represnts False and
    // 1 represents True in the photo representing the Quad - Tree.

    Solution sl;
    auto* ret = sl.Construct(grid);
    auto flattern = FlattenQuadTree(ret);
    EXPECT_EQ(flattern, output);
}

TEST(construct_quad_tree, t2) {
    vector<vector<int>> grid = vector<vector<int>>{
        // clang-format off
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0},
        // clang-format on
    };
    vector<optional<vector<int>>> const output = vector<optional<vector<int>>>{
        // clang-format off
        vector<int>{0, 1},
        vector<int>{1, 1},
        vector<int>{0, 1},
        vector<int>{1, 1},
        vector<int>{1, 0},
       //  null,
       //  null,
       //  null,
       //  null,
        vector<int>{1, 0},
        vector<int>{1, 0},
        vector<int>{1, 1},
        vector<int>{1, 1},
        // clang-format on
    };
    // Explanation:
    // All values in the grid are not the same. We divide the grid into four
    // sub-grids. The topLeft, bottomLeft and bottomRight each has the same
    // value. The topRight have different values so we divide it into 4
    // sub-grids where each has the same value

    Solution sl;
    auto* ret = sl.Construct(grid);
    auto flattern = FlattenQuadTree(ret);
    EXPECT_EQ(flattern, output);
}

}  // namespace
