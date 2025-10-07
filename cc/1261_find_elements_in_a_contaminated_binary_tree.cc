/**
 *
 * Given a binary tree with the following rules:
 * root.val == 0
 * For any treeNode:
 * If treeNode.val has a value x and treeNode.left != null, then
 treeNode.left.val
 * == 2 * x + 1 If treeNode.val has a value x and treeNode.right != null, then
 * treeNode.right.val == 2 * x + 2 Now the binary tree is contaminated, which
 means
 * all treeNode.val have been changed to -1.
 *
 * Implement the FindElements class:
 *
 * FindElements(TreeNode* root) Initializes the object with a contaminated
 binary
 * tree and recovers it. bool find(int target) Returns true if the target value
 * exists in the recovered binary tree.
*/

#include <optional>
#include <set>
#include <vector>

#include "datastruct_base.hh"

using TreeNode = Tree::TreeNode<int>;

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
class FindElements {
   public:
    FindElements(TreeNode* root) { Gen(root, 0); }

    bool Find(int target) { return m_s.count(target) > 0; }

   private:
    void Gen(TreeNode* root, int v) {
        m_s.emplace(v);

        if (root->left) {
            Gen(root->left, 2 * v + 1);
        }
        if (root->right) {
            Gen(root->right, 2 * v + 2);
        }
    }
    std::set<int> m_s;
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */

#include <gtest/gtest.h>

#define null std::nullopt

TEST(t0, t1) {
    //     ["FindElements","find","find"]
    // [[[-1,null,-1]],[1],[2]]
    // Output
    // [null,false,true]
    // Explanation
    auto* root = Tree::ConstructBinaryTree(
        std::vector<std::optional<int>>{-1, null, -1});
    FindElements find_elements(root);
    auto ret = find_elements.Find(1);  // return False
    EXPECT_FALSE(ret);
    ret = find_elements.Find(2);  // return True
    EXPECT_TRUE(ret);
    Tree::FreeTreeNode(root);
}

TEST(t0, t2) {
    //     ["FindElements","find","find"]
    // [[[-1,null,-1]],[1],[2]]
    // Output
    // [null,false,true]
    // Explanation
    auto* root = Tree::ConstructBinaryTree(
        std::vector<std::optional<int>>{-1, -1, -1, -1, -1});
    FindElements find_elements(root);
    auto ret = find_elements.Find(1);  // return False
    EXPECT_TRUE(ret);
    ret = find_elements.Find(3);  // return True
    EXPECT_TRUE(ret);
    ret = find_elements.Find(5);  // return True
    EXPECT_FALSE(ret);
    Tree::FreeTreeNode(root);
}

TEST(t0, t3) {
    //     ["FindElements","find","find"]
    // [[[-1,null,-1]],[1],[2]]
    // Output
    // [null,false,true]
    // Explanation
    auto* root = Tree::ConstructBinaryTree(
        std::vector<std::optional<int>>{-1, null, -1});
    {
        auto* root2 =
            Tree::ConstructBinaryTree(std::vector<std::optional<int>>{-1, -1});
        root->right->left = root2;
    }
    FindElements find_elements(root);
    auto ret = find_elements.Find(2);  // return False
    EXPECT_TRUE(ret);
    ret = find_elements.Find(3);  // return True
    EXPECT_FALSE(ret);
    ret = find_elements.Find(4);  // return True
    EXPECT_FALSE(ret);
    ret = find_elements.Find(5);  // return True
    EXPECT_TRUE(ret);
    Tree::FreeTreeNode(root);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
