/// Definition for a binary tree node.
use super::leetcode_binary_tree::TreeNode;

use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn count_nodes(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        match root {
            None => 0,
            Some(n) => {
                let n = n.as_ref().borrow();
                1 + Self::count_nodes(&n.left) + Self::count_nodes(&n.right)
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::{build_binary_tree, expect_binary_tree};
    use super::*;

    #[test]
    fn test_v1_test() {
        let v: Vec<Option<i32>> = vec![Some(1), Some(2), Some(3), Some(4), Some(5), Some(6)];
        let root = build_binary_tree::<i32>(&v);
        expect_binary_tree(&v, &root);

        let ret = Solution::count_nodes(&root);
        assert_eq!(ret, 6);
    }

    #[test]
    fn test_v2_test() {
        let v: Vec<Option<i32>> = vec![Some(1)];
        let root = build_binary_tree::<i32>(&v);
        expect_binary_tree(&v, &root);

        let ret = Solution::count_nodes(&root);
        assert_eq!(ret, 1);
    }

    #[test]
    fn test_v3_test() {
        let v: Vec<Option<i32>> = vec![];
        let root = build_binary_tree(&v);
        expect_binary_tree(&v, &root);

        let ret = Solution::count_nodes(&root);
        assert_eq!(ret, 0);
    }
}
