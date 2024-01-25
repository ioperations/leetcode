use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    // Given a binary tree root, a node X in the tree is named good if in the
    // path from root to X there are no nodes with a value greater than X.
    // Return the number of good nodes in the binary tree.
    #[allow(unused)]
    fn good_nodes(r: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        if let Some(n) = r {
            let mut count = 0;
            let val = n.as_ref().borrow().val;
            Self::fun(Some(n), val, &mut count);
            return count;
        };
        0
    }

    fn fun(
        node: Option<&Rc<RefCell<TreeNode<i32>>>>,
        val: i32,
        count: &mut i32,
    ) {
        if node.is_none() {
            return;
        }
        let node = node.unwrap();
        if node.as_ref().borrow().val >= val {
            *count += 1;
        }
        let z = node.as_ref().borrow().val.max(val);
        Self::fun(node.borrow().left.as_ref(), z, count);
        Self::fun(node.borrow().right.as_ref(), z, count);
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

    #[test]
    fn case1_test() {
        let root =
            vec![Some(3), Some(1), Some(4), Some(3), None, Some(1), Some(5)];
        let tree = build_binary_tree(&root);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 4);
    }

    #[test]
    fn case2_test() {
        let root = vec![Some(3), Some(3), None, Some(4), Some(2)];
        let tree = build_binary_tree(&root);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 3);
    }

    #[test]
    fn case3_test() {
        let root = vec![Some(1)];
        let tree = build_binary_tree(&root);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 1);
    }

    #[test]
    fn case4_test() {
        let root = vec![Some(9), None, Some(3), Some(6)];
        let tree = build_binary_tree(&root);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 1);
    }
}
