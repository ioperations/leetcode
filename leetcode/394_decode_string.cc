// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the
square brackets is being repeated exactly k times. Note that k is guaranteed to
be a positive integer.

You may assume that the input string is always valid; there are no extra white
spaces, square brackets are well-formed, etc. Furthermore, you may assume that
the original data does not contain any digits and that digits are only for those
repeat numbers, k. For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed
105.*/

#include <iterator>
#include <stack>
#include <string>
using namespace std;
namespace { 
class Solution {
   public:
    string DecodeString(string encoded_string) {
        stack<string> st;
        string curr = "";
        string num = "";
        for (int i = 0; i < (int)encoded_string.size(); i++) {
            if (isalpha(encoded_string[i])) curr += encoded_string[i];
            if (isdigit(encoded_string[i])) num += encoded_string[i];
            if (encoded_string[i] == '[') {
                st.push(curr);
                st.push(num);
                num = "";
                curr = "";
            }
            if (encoded_string[i] == ']') {
                int to_repeat = stoi(st.top());
                st.pop();
                string left_part_plus_repeat = st.top();
                st.pop();
                for (int i = 0; i < to_repeat; i++)
                    left_part_plus_repeat += curr;
                curr = left_part_plus_repeat;
            }
        }
        return curr;
    }
};
} 

#include <gtest/gtest.h>

template <typename T>
struct TreeNode {
    T val;
    struct TreeNode<T> *left;
    struct TreeNode<T> *right;
    TreeNode() : val(T()), left(nullptr), right(nullptr) {}
    TreeNode(T val) : val(val), left(nullptr), right(nullptr) {}
};

#include <algorithm>
#include <optional>
#include <queue>
/// construct a tree
template <typename T>
TreeNode<T> *ConstructTree(const std::vector<std::optional<T>> &elements,
                           bool dummy) {
    std::queue<TreeNode<T> *> q;
    if (!elements[0].has_value()) return nullptr;

    TreeNode<T> *node = new TreeNode<T>(elements[0].value());
    q.push(node);

    int size = elements.size();
    for (int i = 1; i < size; i++) {
        TreeNode<T> *tmp = q.front();
        if (elements[i].has_value()) {
            tmp->left = new TreeNode<T>(elements[i].value());
            q.push(tmp->left);
        } else {
            tmp->left = nullptr;
        }
        i++;
        if (elements[i].has_value()) {
            tmp->right = new TreeNode<T>(elements[i].value());
            q.push(tmp->right);
        } else {
            tmp->right = nullptr;
        }
        q.pop();
    }

    return node;
}

template <typename T>
void FreeTreeNode(TreeNode<T> *root, bool dummy) {
    if (root == nullptr) {
        return;
    }
    FreeTreeNode(root->left, dummy);
    FreeTreeNode(root->right, dummy);
    delete root;
}

namespace { 
TEST(t0, t1) {
    string s = "3[a]2[bc]";
    string out = "aaabcbc";
    Solution sl;
    auto ret = sl.DecodeString(s);
    EXPECT_EQ(ret, out);
}

TEST(t0, t2) {
    string s = "3[a2[c]]";
    string out = "accaccacc";
    Solution sl;
    auto ret = sl.DecodeString(s);
    EXPECT_EQ(ret, out);
}

TEST(t0, t3) {
    string s = "2[abc]3[cd]ef";
    string out = "abcabccdcdcdef";
    Solution sl;
    auto ret = sl.DecodeString(s);
    EXPECT_EQ(ret, out);
}

TEST(t0, t4) {
#define null std::optional<int>()
    std::vector<std::optional<int>> values{1, 2, 3, 4, 5, 6, 7, null, null};
    TreeNode<int> *n = ConstructTree<int>(values, true);
    FreeTreeNode<int>(n, true);
}

}
