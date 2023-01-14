// Given the root of a binary tree, invert the tree, and return its root.

use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn invert_tree<T>(
        root: Option<Rc<RefCell<TreeNode<T>>>>,
    ) -> Option<Rc<RefCell<TreeNode<T>>>> {
        if let Some(v) = root {
            let left = Self::invert_tree(v.as_ref().borrow_mut().left.take());
            let right = Self::invert_tree(v.as_ref().borrow_mut().right.take());
            v.as_ref().borrow_mut().right = left;
            v.as_ref().borrow_mut().left = right;
            return Some(v);
        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::{build_binary_tree, flatten_binary_tree};
    use super::*;

    #[test]
    fn case1_test() {
        let root = [4, 2, 7, 1, 3, 6, 9].map(Some);
        let output = [4, 7, 2, 9, 6, 3, 1].map(Some);

        let r = build_binary_tree(&root);
        let r = Solution::invert_tree(r);
        let r = flatten_binary_tree(r);
        assert_eq!(r, output);
    }

    #[test]
    fn case2_test() {
        let root = [2, 1, 3].map(Some);
        let output = [2, 3, 1].map(Some);

        let r = build_binary_tree(&root);
        let r = Solution::invert_tree(r);
        let r = flatten_binary_tree(r);
        assert_eq!(r, output);
    }

    #[test]
    fn case3_test() {
        let root: Vec<Option<i32>> = vec![];
        let output: Vec<Option<i32>> = vec![];

        let r = build_binary_tree(&root);
        let r = Solution::invert_tree(r);
        let r = flatten_binary_tree(r);
        assert_eq!(r, output);
    }
}
