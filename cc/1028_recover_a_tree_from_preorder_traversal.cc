/*
 * We run a preorder depth-first search (DFS) on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this
node), then we output the value of this node.  If the depth of a node is D, the
depth of its immediate child is D + 1.  The depth of the root node is 0.

If a node has only one child, that child is guaranteed to be the left child.

Given the output traversal of this traversal, recover the tree and return its
root.

*/
#include <cstdlib>
#include <optional>
#include <string>
#include <vector>

#include "datastruct_base.hh"

using TreeNode = Tree::TreeNode<int>;
using namespace std;

class Solution {
   public:
    TreeNode* RecoverFromPreorder(string traversal) {
        // The number of nodes in the original tree is in the range [1, 1000].
        // 1 <= Node.val <= 109
        Tranverse(traversal);
        return Build();
    }

    TreeNode* Build(int current_index = 0) {
        if (m_index >= m_string_info.size()) {
            return nullptr;
        }

        const auto& now = m_string_info[m_index];
        if (current_index != now.m_depth) {
            return nullptr;
        }

        m_index++;
        auto* left = Build(current_index + 1);
        auto* right = Build(current_index + 1);
        return new TreeNode(now.m_value, left, right);
    }

   private:
    void Tranverse(const std::string& value) {
        int dash = 0;
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == '-') {
                dash++;
                continue;
            }

            string v;
            int k = 0;
            for (int j = i; j < value.size() && value[j] != '-'; j++) {
                v += value[j];
                k++;
            }
            i = i + k - 1;

            m_string_info.emplace_back(dash, atoi(v.c_str()));
            dash = 0;
        }
    }

    struct Info {
        int m_depth;
        int m_value;
        Info(int d, int v) : m_depth(d), m_value(v) {}
    };
    vector<Info> m_string_info;
    int m_index = 0;
};

#include <gtest/gtest.h>

namespace {
void PreOrder(TreeNode* node, string& out, int depth = 0) {
    if (depth == 0) {
        out.clear();
    }
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        out += '-';
    }
    out += to_string(node->val);
    PreOrder(node->left, out, depth + 1);
    PreOrder(node->right, out, depth + 1);
}
}  // namespace

#define null std::nullopt

TEST(t0, t0) {
    auto* root = Tree::ConstructBinaryTree(
        std::vector<std::optional<int>>{1, 2, 5, 3, 4, 6, 7});

    string out;
    PreOrder(root, out);
    string const output = "1-2--3--4-5--6--7";
    EXPECT_EQ(out, output);

    Solution sl;
    auto* r2 = sl.RecoverFromPreorder(output);
    PreOrder(r2, out);
    EXPECT_EQ(out, output);
    Tree::FreeTreeNode(r2);

    Tree::FreeTreeNode(root);
}

TEST(t1, t1) {
    auto* root = new TreeNode(1);
    {
        auto* left = Tree::ConstructBinaryTree(
            std::vector<std::optional<int>>{2, 3, null, 4});
        root->left = left;

        auto* right = Tree::ConstructBinaryTree(
            std::vector<std::optional<int>>{5, 6, null, 7});
        root->right = right;
    }

    string out;
    PreOrder(root, out);
    string const output = "1-2--3---4-5--6---7";
    EXPECT_EQ(out, output);

    Solution sl;
    auto* r2 = sl.RecoverFromPreorder(output);
    PreOrder(r2, out);
    EXPECT_EQ(out, output);
    Tree::FreeTreeNode(r2);

    Tree::FreeTreeNode(root);
}

TEST(t2, t2) {
    auto* root = new TreeNode(1);
    {
        auto* sub = Tree::ConstructBinaryTree(
            std::vector<std::optional<int>>{401, 349, 88, 90});
        root->left = sub;
    }

    string out;
    PreOrder(root, out);
    string const output = "1-401--349---90--88";
    EXPECT_EQ(out, output);

    Solution sl;
    auto* r2 = sl.RecoverFromPreorder(output);
    PreOrder(r2, out);
    EXPECT_EQ(out, output);
    Tree::FreeTreeNode(r2);

    Tree::FreeTreeNode(root);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
