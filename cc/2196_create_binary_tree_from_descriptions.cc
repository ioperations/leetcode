/*
 * You are given a 2D integer array descriptions where descriptions[i] =
 * [parenti, childi, isLefti] indicates that parenti is the parent of childi in
 * a binary tree of unique values. Furthermore,
 *
 * If isLefti == 1, then childi is the left child of parenti.
 * If isLefti == 0, then childi is the right child of parenti.
 * Construct the binary tree described by descriptions and return its root.
 *
 * The test cases will be generated such that the binary tree is valid.
 *
 * 1 <= descriptions.length <= 104
 * descriptions[i].length == 3
 * 1 <= parenti, childi <= 105
 * 0 <= isLefti <= 1
 * The binary tree described by descriptions is valid.
 *
 */

#include <cassert>
#include <optional>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

#include "datastruct_base.hh"
using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    TreeNode* CreateBinaryTree(vector<vector<int>>& descriptions) {
        assert(descriptions.size() > 0);
        for (auto& desc : descriptions) {
            assert(desc.size() == 3);
            auto parent = desc[0];
            auto child = desc[1];
            auto isleft = desc[2] == 1;
            auto it = m_id2Node.find(parent);
            if (it == m_id2Node.end()) {
                auto* n = new TreeNode(parent);
                m_id2Node[parent] = n;
            }

            it = m_id2Node.find(child);
            if (it == m_id2Node.end()) {
                auto* n = new TreeNode(child);
                m_id2Node[child] = n;
            }
            auto*& p_parent = m_id2Node[parent];
            auto*& p_child = m_id2Node[child];

            if (isleft) {
                p_parent->left = p_child;
            } else {
                p_parent->right = p_child;
            }
            UpdateFather(child, parent);
        }
        auto z = GetRootParent(m_id2Node.cbegin()->first);
        return m_id2Node[z];
    }

   private:
    void UpdateFather(int child, int parent) {
        int tmp = child;
        if (m_child2Father.find(tmp) != m_child2Father.end()) {
            int z = GetRootParent(parent);
            m_child2Father[child] = z;
        } else {
            m_child2Father[tmp] = parent;
        }
    }

    int GetRootParent(int parent) {
        if (m_child2Father.find(parent) == m_child2Father.end()) {
            m_child2Father[parent] = parent;
            return parent;
        }

        int z = GetRootParent((m_child2Father[parent]));
        m_child2Father[parent] = z;
        return z;
    }
    std::unordered_map<int, int> m_child2Father;
    std::unordered_map<int, TreeNode*> m_id2Node;
};
struct Node {
    int level;
    int seq;
    TreeNode* n;
    bool operator<(const Node& rhs) const {
        if (level > rhs.level) {
            return true;
        }
        return seq > rhs.seq;
    }
    Node(int level, int seq, TreeNode* n) : level(level), seq(seq), n(n) {}
};
void LevelTranverse(TreeNode* n, std::vector<optional<int>>& ret) {
    priority_queue<Node> pq;
    int seq = 0;
    pq.emplace(0, seq, n);
    seq++;
    while (!pq.empty()) {
        auto z = pq.top();
        pq.pop();
        if (z.n != nullptr) {
            ret.emplace_back(z.n->val);
            pq.emplace(z.level + 1, seq, z.n->left);
            seq++;
            pq.emplace(z.level + 1, seq, z.n->right);
            seq++;
        } else {
            ret.emplace_back(std::nullopt);
        }
    }
}
}  // namespace

#include <gtest/gtest.h>

#define null std::nullopt
TEST(createBinaryTree, t1) {
    vector<std::vector<int>> descriptions = {
        {20, 15, 1}, {20, 17, 0}, {50, 20, 1}, {50, 80, 0}, {80, 19, 1}};
    std::vector<std::optional<int>> output = {50, 20, 80, 15, 17, 19};
    Solution sl;
    auto* ret = sl.CreateBinaryTree(descriptions);
    std::vector<std::optional<int>> ret_flattern;
    LevelTranverse(ret, ret_flattern);
    ret_flattern.resize(output.size());
    EXPECT_EQ(output, ret_flattern);

    Tree::FreeTreeNode(ret);
    /*
     * Explanation: The root node is the node with value 50 since it has no
     * parent. The resulting binary tree is shown in the diagram.
     *
     *      50
     *     /  \
     *   20    80
     *   / \   /
     *  15 17 19
     */
}

TEST(createBinaryTree, t2) {
    vector<std::vector<int>> descriptions = {{1, 2, 1}, {2, 3, 0}, {3, 4, 1}};
    std::vector<std::optional<int>> output = {1, 2, null, null, 3, 4};

    Solution sl;
    auto* ret = sl.CreateBinaryTree(descriptions);
    std::vector<std::optional<int>> ret_flattern;
    LevelTranverse(ret, ret_flattern);
    ret_flattern.resize(output.size());
    EXPECT_EQ(output, ret_flattern);
    Tree::FreeTreeNode(ret);
    /*
     * Explanation: The root node is the node with value 50 since it has no
     * parent. The resulting binary tree is shown in the diagram.
     *       1
     *      /
     *     2
     *      \
     *       3
     *      /
     *     4
     */
}

TEST(createBinaryTree, t3) {
    vector<std::vector<int>> descriptions = {{85, 82, 1}, {74, 85, 1},
                                             {39, 70, 0}, {82, 38, 1},
                                             {74, 39, 0}, {39, 13, 1}};
    std::vector<std::optional<int>> output = {74, 85, 39, 82, null, 13, 70, 38};

    Solution sl;
    auto* ret = sl.CreateBinaryTree(descriptions);
    std::vector<std::optional<int>> ret_flattern;
    LevelTranverse(ret, ret_flattern);
    ret_flattern.resize(output.size());
    EXPECT_EQ(output, ret_flattern);
    Tree::FreeTreeNode(ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
