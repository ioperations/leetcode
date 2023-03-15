// Given the root of a binary tree, determine if it is a complete binary tree.
// In a complete binary tree, every level, except possibly the last, is
// completely filled, and all nodes in the last level are as far left as

// possible. It can have between 1 and 2h nodes inclusive at the last level h.
use super::leetcode_binary_tree::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn is_complete_tree<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> bool {
        type Rn<T> = Rc<RefCell<TreeNode<T>>>;
        fn my_impl<T>(root: Option<Rn<T>>) -> bool {
            use std::collections::VecDeque;
            struct Node<T> {
                val: i32,
                node: Rn<T>,
            }
            let mut queue = VecDeque::new();
            if let Some(v) = root {
                queue.push_back(Node { val: 1, node: v });
            }
            let mut expected = 1;
            while !queue.is_empty() {
                let Node { val, node } = queue.pop_front().unwrap();
                if val == expected {
                    if let Some(left) = node.borrow_mut().left.take() {
                        queue.push_back(Node {
                            val: val * 2,
                            node: left,
                        });
                    }
                    if let Some(right) = node.borrow_mut().right.take() {
                        queue.push_back(Node {
                            val: val * 2 + 1,
                            node: right,
                        });
                    }
                } else {
                    return false;
                }
                expected += 1;
            }
            true
        }
        my_impl(root)
    }
}

#[cfg(test)]
mod test {
    use super::super::leetcode_binary_tree::build_binary_tree;

    use super::*;

    #[test]
    fn case1_test() {
        let root: Vec<_> = [1, 2, 3, 4, 5, 6].into_iter().map(Some).collect();
        let root = build_binary_tree(&root);
        let output = true;
        let ret = Solution::is_complete_tree(root);
        assert_eq!(ret, output);
        // Explanation: Every level before the last is full (ie. levels with
        // node-values {1} and {2, 3}), and all nodes in the last level ({4, 5,
        // 6}) are as far left as possible.
    }

    #[test]
    fn case2_test() {
        let null = -1;
        let root: Vec<_> = [1, 2, 3, 4, 5, null, 7]
            .into_iter()
            .map(|i| if i == null { None } else { Some(i) })
            .collect();
        let root = build_binary_tree(&root);
        let output = false;
        let ret = Solution::is_complete_tree(root);
        assert_eq!(ret, output);
        // The node with value 7 isn't as far left as possible.
    }
}
