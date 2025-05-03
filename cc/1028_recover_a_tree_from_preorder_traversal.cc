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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
   public:
    TreeNode* recoverFromPreorder(string traversal) {
        // The number of nodes in the original tree is in the range [1, 1000].
        // 1 <= Node.val <= 109
        tranverse(traversal);
        return Build();
    }

    TreeNode* Build(int currentIndex = 0) {
        if (index >= stringInfo.size()) {
            return nullptr;
        }

        const auto& now = stringInfo[index];
        if (currentIndex != now.depth) {
            return nullptr;
        }

        TreeNode* n = new TreeNode(now.value);

        index++;
        auto* z = Build(currentIndex + 1);
        n->left = z;
        auto* q = Build(currentIndex + 1);
        n->right = q;

        return n;
    }

   private:
    void tranverse(const std::string& value) {
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

            stringInfo.emplace_back(dash, atoi(v.c_str()));
            dash = 0;
        }
    }

    struct info {
        int depth;
        int value;
        info(int d, int v) : depth(d), value(v) {}
    };
    vector<info> stringInfo;
    int index = 0;
};

#include <gtest/gtest.h>

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

#define null std::optional<int>()

TEST(t0, t0) {
    auto root = Tree::ConstructBinaryTree(
        std::vector<std::optional<int>>{1, 2, 5, 3, 4, 6, 7});

    string out;
    PreOrder(root, out);
    string output = "1-2--3--4-5--6--7";
    EXPECT_EQ(out, output);

    Solution sl;
    auto r2 = sl.recoverFromPreorder(output);
    PreOrder(r2, out);
    EXPECT_EQ(out, output);
    Tree::FreeTreeNode(r2);

    Tree::FreeTreeNode(root);
}

TEST(t1, t1) {
    auto root = new TreeNode(1);
    {
        auto left = Tree::ConstructBinaryTree(
            std::vector<std::optional<int>>{2, 3, null, 4});
        root->left = left;

        auto right = Tree::ConstructBinaryTree(
            std::vector<std::optional<int>>{5, 6, null, 7});
        root->right = right;
    }

    string out;
    PreOrder(root, out);
    string output = "1-2--3---4-5--6---7";
    EXPECT_EQ(out, output);

    Solution sl;
    auto r2 = sl.recoverFromPreorder(output);
    PreOrder(r2, out);
    EXPECT_EQ(out, output);
    Tree::FreeTreeNode(r2);

    Tree::FreeTreeNode(root);
}

TEST(t2, t2) {
    auto root = new TreeNode(1);
    {
        auto sub = Tree::ConstructBinaryTree(
            std::vector<std::optional<int>>{401, 349, 88, 90});
        root->left = sub;
    }

    string out;
    PreOrder(root, out);
    string output = "1-401--349---90--88";
    EXPECT_EQ(out, output);

    Solution sl;
    auto r2 = sl.recoverFromPreorder(output);
    PreOrder(r2, out);
    EXPECT_EQ(out, output);
    Tree::FreeTreeNode(r2);

    Tree::FreeTreeNode(root);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
