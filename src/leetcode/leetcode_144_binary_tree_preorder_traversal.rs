// Given the root of a binary tree, return the preorder traversal of its nodes'
// values.

use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn preorder_traversal(
        root: &Option<Rc<RefCell<TreeNode<i32>>>>,
    ) -> Vec<i32> {
        let mut vec = Vec::new();
        Self::preorder_traversal_recursive(root, &mut vec);
        vec
    }

    #[allow(unused)]
    fn preorder_traversal_recursive(
        root: &Option<Rc<RefCell<TreeNode<i32>>>>,
        vec: &mut Vec<i32>,
    ) {
        if let Some(root) = root {
            vec.push(root.borrow().val);
            Self::preorder_traversal_recursive(&root.borrow().left, vec);
            Self::preorder_traversal_recursive(&root.borrow().right, vec);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

    #[test]
    fn case1_test() {
        let null = 1000;
        let root = [1, null, 2, 3].map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        });
        let output = [1, 2, 3].to_vec();
        let tree = build_binary_tree(&root);
        let ret = Solution::preorder_traversal(&tree);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let null = 1000;
        let root = [].map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        });
        let output: Vec<i32> = [].to_vec();
        let tree = build_binary_tree(&root);
        let ret = Solution::preorder_traversal(&tree);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let null = 1000;
        let root = [1].map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        });
        let output = [1].to_vec();
        let tree = build_binary_tree(&root);
        let ret = Solution::preorder_traversal(&tree);
        assert_eq!(ret, output);
    }
}
