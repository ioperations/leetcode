template<typename T>
struct TreeNode {
    T val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(T()), left(nullptr), right(nullptr) {}
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(T x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <vector>

template <typename T>
TreeNode<T> *AddToRoot(TreeNode<T> *root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val < root->val) {
        if (root->left) {
            TreeNode<T> *head = AddToRoot(root->left, val);
            root->left = head;
            return root;
        }
        root->left = new TreeNode<T>(val);

    } else {
        if (root->right) {
            TreeNode<T> *head = AddToRoot(root->right, val);
            root->right = head;
            return root;
        }
        root->right = new TreeNode<T>(val);
    }
    return root;
}

template <typename T>
TreeNode<T> *AddToRoot(TreeNode<T> *root, const std::vector<T> &elements) {
    for (auto &ptr : elements) {
        root = AddToRoot(root, ptr);
    }
    return root;
}

template <typename T>
TreeNode<T> *ConstructTree(const std::vector<T> &elements) {
    if (!elements.size()) {
        return nullptr;
    }

    TreeNode<T> *root = new TreeNode<T>(elements[0]);

    for (int i = 1; i < (int)elements.size(); i++) {
        root = AddToRoot(root, elements[i]);
    }

    return root;
}

template <typename T>
TreeNode<T> *ConstructBinaryTree(std::vector<std::optional<T>> &data) {
    data.resize(data.size() * 2 + 31);
    if (data.size() == 0) return nullptr;

    if (!data[0].has_value()) return nullptr;
    TreeNode<T> *root = new TreeNode(data[0].value());
    std::queue<TreeNode<T> *> q;
    q.push(root);

    int i = 1;

    while (!q.empty()) {
        TreeNode<T> *cur = q.front();
        q.pop();

        if (!data[i].has_value()) {
            cur->left = NULL;
        } else {
            TreeNode<T> *left_n = new TreeNode(data[i].value());
            cur->left = left_n;
            q.push(left_n);
        }
        i++;

        if (!data[i].has_value()) {
            cur->right = NULL;
        } else {
            TreeNode<T> *right_n = new TreeNode(data[i].value());
            cur->right = right_n;
            q.push(right_n);
        }
        i++;
    }
    return root;
}

template <typename T>
void FreeRoot(TreeNode<T> *root) {
    if (root == nullptr) {
        return;
    }

    FreeRoot(root->left);
    FreeRoot(root->right);
    delete root;
}

template <typename T>
void FreeTreeNode(TreeNode<T> *root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

template <typename T>
void BfsSearch(TreeNode<T> *root, std::vector<T> &vec) {
    std::queue<TreeNode<T> *> q;
    q.push(root);

    while (q.size()) {
        TreeNode<T> *tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        }
    }
}

template <typename T>
void BfsSearchV1(TreeNode<T> *root, std::vector<std::optional<int>> &vec) {
    std::queue<TreeNode<T> *> q;
    q.push(root);

    while (q.size()) {
        auto *tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        } else {
            vec.emplace_back(std::optional<int>());
        }
    }

    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        if (!it->has_value()) {
            vec.pop_back();
            continue;
        }
        break;
    }
}

template <typename T>
void PrintBt(const std::string &prefix, const TreeNode<T> *node, bool is_left) {
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

template <typename T>
void PrintBt(const TreeNode<T> *node) {
    PrintBt("", node, false);
}

template <typename T>
TreeNode<T> *FindInTree(TreeNode<T> *n, int v) {
    if (n == nullptr) return nullptr;

    if (n->val == v) return n;

    auto *le = FindInTree(n->left, v);
    if (le == nullptr) return FindInTree(n->right, v);
    return le;
}

template <typename T>
TreeNode<T> *ConstructRight(const std::vector<T> &arr) {
    TreeNode node(0);
    auto *z = &node;

    for (auto &ptr : arr) {
        z->right = new TreeNode(ptr);
        z = z->right;
    }

    return node.right;
}
