/*Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same
 * tree, construct and return the binary tree.*/

//* Definition for a binary tree node.
#include <unordered_map>

#include "datastruct_base.hh"

using namespace std;
class Solution {
   public:
    template <typename T>
    TreeNode<T> *Build(vector<T> &preorder, int p_start, int p_end,
                       unordered_map<int, int> &inorder_map, int i_start,
                       int i_end) {
        if (p_start > p_end || i_start > i_end) return nullptr;

        auto *root = new TreeNode(preorder[p_start]);
        int i_root = inorder_map[root->val];
        int nums_left = i_root - i_start;

        root->left = Build(preorder, p_start + 1, p_start + nums_left,
                           inorder_map, i_start, i_root - 1);
        root->right = Build(preorder, p_start + 1 + nums_left, p_end,
                            inorder_map, i_root + 1, i_end);

        return root;
    }
    template <typename T>
    TreeNode<T> *BuildTree(vector<T> &preorder, vector<T> &inorder) {
        unordered_map<int, int> inorder_map;
        for (int i = 0; i < (int)inorder.size(); i++)
            inorder_map[inorder[i]] = i;

        return Build(preorder, 0, preorder.size() - 1, inorder_map, 0,
                     inorder.size() - 1);
    }
};

#include <gtest/gtest.h>

using namespace std;

TEST(t0, t1) {
    vector<int> preorder = {3, 9, 20, 15, 7}, inorder = {9, 3, 15, 20, 7};
    Solution sl;
    auto *node = sl.BuildTree(preorder, inorder);
    std::vector<int> ret;
    BfsSearch(node, ret);

    FreeTreeNode(node);
    vector<int> output = {3, 9, 20, 15, 7};
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> preorder = {-1}, inorder = {-1};
    Solution sl;
    auto *node = sl.BuildTree(preorder, inorder);
    std::vector<int> ret;
    BfsSearch(node, ret);

    FreeTreeNode(node);
    vector<int> output = {-1};
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
