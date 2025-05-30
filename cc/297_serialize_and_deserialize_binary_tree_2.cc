// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Serialization is the process of converting a data structure or object into a
sequence of bits so that it can be stored in a file or memory buffer, or
transmitted across a network connection link to be reconstructed later in the
same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no
restriction on how your serialization/deserialization algorithm should work. You
just need to ensure that a binary tree can be serialized to a string and this
string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a
binary tree. You do not necessarily need to follow this format, so please be
creative and come up with different approaches yourself.*/

#include <cstdlib>
//* Definition for a binary tree node.
#include <algorithm>
#include <queue>
#include <sstream>
#include <string>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Tree;

namespace {
class Codec {
   public:
    // Encodes a tree to a single string.
    template <typename T>
    string Serialize(TreeNode<T>* root) {
        if (root == nullptr) return "";
        std::queue<TreeNode<T>*> q;

        std::string ret;
        q.push(root);
        while (q.size()) {
            TreeNode<T>* n = q.front();

            if (n == nullptr) {
                ret += "#,";
                q.pop();
                continue;
            }
            ret += (std::to_string(n->val) + ",");

            q.push(n->left);
            q.push(n->right);
            q.pop();
        }
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode<int>* Deserialize(string data) {
        if (data.size() == 0) return nullptr;
        replace(data.begin(), data.end(), ',', ' ');
        std::stringstream ss(data);

        std::string tmp;
        TreeNode<int>* n = nullptr;
        std::queue<TreeNode<int>*> q;

        bool first = true;
        while (ss >> tmp) {
            if (first) {
                n = new TreeNode(atoi(tmp.c_str()));
                q.push(n);
                first = false;
            } else {
                TreeNode<int>* n = q.front();
                if (tmp == "#") {
                    n->left = nullptr;
                } else {
                    auto* t = new TreeNode(atoi(tmp.c_str()));
                    n->left = t;
                    q.push(t);
                }

                if (ss >> tmp) {
                    if (tmp == "#") {
                        n->right = nullptr;
                    } else {
                        auto* t = new TreeNode(atoi(tmp.c_str()));
                        n->right = t;
                        q.push(t);
                    }
                }
                q.pop();
            }
        }
        return n;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

#include <optional>
#include <vector>

using namespace std;

TEST(construtTest, t1) {
    std::vector<std::optional<int>> const input{
        1, 2, 3, optional<int>(), optional<int>(), 4, 5};

    std::vector<int> const output = {1, 2, 3, 4, 5};
    TreeNode<int>* ret = ConstructBinaryTree(input);

    PrintBt(ret);
    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);
    FreeTreeNode(ret);
}

TEST(memleak, t0) {
    std::vector<optional<int>> const input{};
    std::vector<int> const output = {};

    TreeNode<int>* head = ConstructBinaryTree(input);

    FreeTreeNode(head);
}

TEST(serialize_and_deserialize_binary_tree_2, t1) {
#define null optional<int>()
    std::vector<optional<int>> const input{1, 2, 3, null, null, 4, 5};
    std::vector<int> const output = {1, 2, 3, 4, 5};

    TreeNode<int>* head = ConstructBinaryTree(input);

    PrintBt(head);

    Codec cl;
    std::string const data = cl.Serialize(head);

    EXPECT_EQ(data, "1,2,3,#,#,4,5,#,#,#,#,");
    TreeNode<int>* ret = cl.Deserialize(data);

    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);
    FreeTreeNode(head);

    FreeTreeNode(ret);
}

TEST(serialize_and_deserialize_binary_tree_2, t2) {
    std::vector<optional<int>> const input(10, optional<int>());
    std::vector<int> const output = {};

    TreeNode<int>* head = ConstructBinaryTree(input);

    Codec cl;
    string const data = cl.Serialize(head);
    EXPECT_EQ(data, "");
    TreeNode<int>* ret = cl.Deserialize(data);

    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);

    FreeTreeNode(head);

    FreeTreeNode(ret);
}

}  // namespace
