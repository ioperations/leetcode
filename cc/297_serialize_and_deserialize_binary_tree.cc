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

#include <stddef.h>

#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <sstream>
#include <string>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
using namespace Tree;

namespace {
class Codec {
   public:
    // Encodes a tree to a single string.
    template <typename T>
    string Serialize(TreeNode<T> *root) {
        if (!root) return "";
        string s = "";
        queue<TreeNode<T> *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode<T> *cur = q.front();
            q.pop();
            if (cur == NULL)
                s.append("#,");
            else {
                s.append(to_string(cur->val) + ',');
            }

            if (cur != NULL) {
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        // cout << s;
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode<int> *Deserialize(string data) {
        if (data.size() == 0) return NULL;

        stringstream s(data);
        string str;
        getline(s, str, ',');
        int x = stoi(str);
        auto *root = new TreeNode(x);
        queue<TreeNode<int> *> q;
        q.push(root);

        while (!q.empty()) {
            auto *cur = q.front();
            q.pop();

            getline(s, str, ',');
            if (str == "#") {
                cur->left = NULL;
            } else {
                x = stoi(str);
                auto *left_n = new TreeNode(x);
                cur->left = left_n;
                q.push(left_n);
            }

            getline(s, str, ',');
            if (str == "#") {
                cur->right = NULL;
            } else {
                x = stoi(str);
                auto *right_n = new TreeNode(x);
                cur->right = right_n;
                q.push(right_n);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

#include <optional>
#include <vector>

using namespace std;

TEST(construtTest, serialize_and_deserialize_binary_tree_297) {
    std::vector<std::optional<int>> input{
        1, 2, 3, optional<int>(), optional<int>(), 4, 5};

    std::vector<int> output = {1, 2, 3, 4, 5};
    auto *ret = ConstructBinaryTree(input);

    PrintBt(ret);
    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);
    FreeTreeNode(ret);
}

TEST(memleak, t0) {
    std::vector<optional<int>> input{};
    std::vector<int> output = {};

    auto *head = ConstructBinaryTree(input);

    FreeTreeNode(head);
}

TEST(serialize_and_deserialize_binary_tree, t1) {
#define null optional<int>()
    std::vector<optional<int>> input{1, 2, 3, null, null, 4, 5};
    std::vector<int> output = {1, 2, 3, 4, 5};

    auto *head = ConstructBinaryTree(input);

    PrintBt(head);

    Codec cl;
    std::string data = cl.Serialize(head);

    EXPECT_EQ(data, "1,2,3,#,#,4,5,#,#,#,#,");
    auto *ret = cl.Deserialize(data);

    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);
    FreeTreeNode(head);

    FreeTreeNode(ret);
}

TEST(serialize_and_deserialize_binary_tree, t2) {
    std::vector<optional<int>> input(10, optional<int>());
    std::vector<int> output = {};

    auto *head = ConstructBinaryTree(input);

    Codec cl;
    string data = cl.Serialize(head);
    EXPECT_EQ(data, "");
    auto *ret = cl.Deserialize(data);

    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);

    FreeTreeNode(head);

    FreeTreeNode(ret);
}

}  // namespace
