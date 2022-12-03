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

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode() {}
};

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

class Codec {
   public:
    // Encodes a tree to a single string.
    string Serialize(TreeNode* root) {
        if (root == nullptr) return "";
        std::queue<TreeNode*> q;

        std::string ret;
        q.push(root);
        while (q.size()) {
            TreeNode* n = q.front();

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
    TreeNode* Deserialize(string data) {
        if (data.size() == 0) return nullptr;
        replace(data.begin(), data.end(), ',', ' ');
        std::stringstream ss(data);

        std::string tmp;
        TreeNode* n = nullptr;
        std::queue<TreeNode*> q;

        bool first = true;
        while (ss >> tmp) {
            if (first) {
                n = new TreeNode(atoi(tmp.c_str()));
                q.push(n);
                first = false;
            } else {
                TreeNode* n = q.front();
                if (tmp == "#") {
                    n->left = nullptr;
                } else {
                    TreeNode* t = new TreeNode(atoi(tmp.c_str()));
                    n->left = t;
                    q.push(t);
                }

                if (ss >> tmp) {
                    if (tmp == "#") {
                        n->right = nullptr;
                    } else {
                        TreeNode* t = new TreeNode(atoi(tmp.c_str()));
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

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

// Decodes your encoded data to tree.
TreeNode* ConstructBinaryTree(std::vector<std::optional<int>>& data) {
    data.resize(data.size() * 2);
    if (data.size() == 0) return nullptr;

    if (!data[0].has_value()) return nullptr;
    TreeNode* root = new TreeNode(data[0].value());
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;

    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        if (!data[i].has_value()) {
            cur->left = NULL;
        } else {
            TreeNode* left_n = new TreeNode(data[i].value());
            cur->left = left_n;
            q.push(left_n);
        }
        i++;

        if (!data[i].has_value()) {
            cur->right = NULL;
        } else {
            TreeNode* right_n = new TreeNode(data[i].value());
            cur->right = right_n;
            q.push(right_n);
        }
        i++;
    }
    return root;
}

// Function to print tree nodes in
// InOrder fashion
void InOrder(TreeNode* root, std::vector<string>& vec) {
    if (root != nullptr) {
        InOrder(root->left, vec);
        vec.push_back(std::to_string(root->val));

        InOrder(root->right, vec);
    }
}

void BfsSearch(TreeNode* root, std::vector<int>& vec) {
    queue<TreeNode*> q;
    q.push(root);

    while (q.size()) {
        TreeNode* tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        }
    }
}

void FreeTreeNode(TreeNode* root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

void PrintBt(const std::string& prefix, const TreeNode* node, bool is_left) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (is_left ? "├──" : "└──");

        // print the value of the node
        std::cout << node->val << std::endl;

        // enter the next tree level - left and right branch
        PrintBt(prefix + (is_left ? "│   " : "    "), node->left, true);
        PrintBt(prefix + (is_left ? "│   " : "    "), node->right, false);
    }
}

void PrintBt(const TreeNode* node) { PrintBt("", node, false); }

TEST(construtTest, t1) {
    std::vector<std::optional<int>> input{
        1, 2, 3, optional<int>(), optional<int>(), 4, 5};

    std::vector<int> output = {1, 2, 3, 4, 5};
    TreeNode* ret = ConstructBinaryTree(input);

    PrintBt(ret);
    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);
    FreeTreeNode(ret);
}

TEST(memleak, t0) {
    std::vector<optional<int>> input{};
    std::vector<int> output = {};

    TreeNode* head = ConstructBinaryTree(input);

    FreeTreeNode(head);
}

TEST(t0, t1) {
#define null optional<int>()
    std::vector<optional<int>> input{1, 2, 3, null, null, 4, 5};
    std::vector<int> output = {1, 2, 3, 4, 5};

    TreeNode* head = ConstructBinaryTree(input);

    PrintBt(head);

    Codec cl;
    std::string data = cl.Serialize(head);

    EXPECT_EQ(data, "1,2,3,#,#,4,5,#,#,#,#,");
    TreeNode* ret = cl.Deserialize(data);

    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);
    FreeTreeNode(head);

    FreeTreeNode(ret);
}

TEST(t0, t2) {
    std::vector<optional<int>> input(10, optional<int>());
    std::vector<int> output = {};

    TreeNode* head = ConstructBinaryTree(input);

    Codec cl;
    string data = cl.Serialize(head);
    EXPECT_EQ(data, "");
    TreeNode* ret = cl.Deserialize(data);

    std::vector<int> vec;
    BfsSearch(ret, vec);

    EXPECT_EQ(vec, output);

    FreeTreeNode(head);

    FreeTreeNode(ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
