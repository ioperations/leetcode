#pragma once
#include <iostream>
#include <optional>
#include <queue>

namespace Tree {

template <typename T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(T()), left(nullptr), right(nullptr) {}
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(T x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
    virtual ~TreeNode() = default;
};

template <typename T>
TreeNode<T>* AddToRoot(TreeNode<T>* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val < root->val) {
        if (root->left) {
            TreeNode<T>* head = AddToRoot(root->left, val);
            root->left = head;
            return root;
        }
        root->left = new TreeNode<T>(val);

    } else {
        if (root->right) {
            TreeNode<T>* head = AddToRoot(root->right, val);
            root->right = head;
            return root;
        }
        root->right = new TreeNode<T>(val);
    }
    return root;
}

template <typename T>
TreeNode<T>* AddToRoot(TreeNode<T>* root, const std::vector<T>& elements) {
    for (auto& ptr : elements) {
        root = AddToRoot(root, ptr);
    }
    return root;
}

template <typename T>
TreeNode<T>* ConstructTree(const std::vector<T>& elements) {
    if (!elements.size()) {
        return nullptr;
    }

    TreeNode<T>* root = new TreeNode<T>(elements[0]);

    for (int i = 1; i < (int)elements.size(); i++) {
        root = AddToRoot(root, elements[i]);
    }

    return root;
}

template <typename T>
TreeNode<T>* ConstructBinaryTree(const std::vector<std::optional<T>>& data) {
    if (data.empty()) return nullptr;
    if (!data[0]) return nullptr;

    TreeNode<T>* root = new TreeNode(*data[0]);
    std::queue<TreeNode<T>*> q;
    q.push(root);

    int i = 1;
    const int datasize = (int)data.size();

    while (!q.empty() && i < datasize) {
        TreeNode<T>* cur = q.front();
        q.pop();
        if (!data[i]) {
            cur->left = nullptr;
        } else {
            TreeNode<T>* left_n = new TreeNode(data[i].value());
            cur->left = left_n;
            q.push(left_n);
        }
        i++;

        if (i >= datasize) break;
        if (!data[i]) {
            cur->right = nullptr;
        } else {
            TreeNode<T>* right_n = new TreeNode(data[i].value());
            cur->right = right_n;
            q.push(right_n);
        }
        i++;
    }
    return root;
}

template <typename T>
inline void FreeTreeNode(TreeNode<T>* root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
    root = nullptr;
}

template <typename T>
void BfsSearch(TreeNode<T>* root, std::vector<T>& vec) {
    std::queue<TreeNode<T>*> queue;
    queue.push(root);

    while (queue.size()) {
        TreeNode<T>* tmp = queue.front();

        queue.pop();

        if (tmp != nullptr) {
            queue.push(tmp->left);
            queue.push(tmp->right);
            vec.push_back(tmp->val);
        }
    }
}

template <typename T>
void BfsSearchV1(TreeNode<T>* root, std::vector<std::optional<int>>& vec) {
    std::queue<TreeNode<T>*> q;
    q.push(root);

    while (q.size()) {
        auto* tmp = q.front();

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
void PrintBt(const std::string& prefix, const TreeNode<T>* node, bool is_left) {
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
void PrintBt(const TreeNode<T>* node) {
    PrintBt("", node, false);
}

template <typename T>
TreeNode<T>* FindInTree(TreeNode<T>* n, int v) {
    if (n == nullptr) return nullptr;

    if (n->val == v) return n;

    auto* le = FindInTree(n->left, v);
    if (le == nullptr) return FindInTree(n->right, v);
    return le;
}

template <typename T>
TreeNode<T>* ConstructRight(const std::vector<T>& arr) {
    TreeNode node(0);
    auto* z = &node;

    for (auto& ptr : arr) {
        z->right = new TreeNode(ptr);
        z = z->right;
    }

    return node.right;
}
}  // namespace Tree

namespace List {

template <typename T>
struct ListNode {
    T val;
    ListNode* next;
    ListNode() : val(T()), next(nullptr) {}
    ListNode(T x) : val(x), next(nullptr) {}
    ListNode(T x, ListNode* next) : val(x), next(next) {}
};

/**
 * @brief 更加简单的方式从一个数组当中来创建一个list 模版化
 * @param @elements 要创建的list的数组
 * @return  链表的头，用户需要free掉
 */
template <typename T>
ListNode<T>* ConstructList(const std::vector<T>& elements) {
    ListNode<T> head;
    ListNode<T>* tail = &head;

    for (auto& ptr : elements) {
        tail->next = new ListNode<T>(ptr);
        tail = tail->next;
    }

    return head.next;
}

/**
 * @brief 释放掉链表的内存
 * @param @list 链表的头
 * @return nil
 */
template <typename T>
void FreeList(ListNode<T>* list) {
    if (list == nullptr) {
        return;
    }
    FreeList(list->next);
    delete list;
    list = nullptr;
}

}  // namespace List

template <typename Func>
class ScopeGuard {
   public:
    ScopeGuard(Func f) : f(f) {}
    ~ScopeGuard() { f(); }

   private:
    Func f;
};
