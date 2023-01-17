use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn distribute_coins(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        let mut steps = 0;
        Self::helper(root, &mut steps);
        steps
    }

    #[allow(unused)]
    fn helper(
        node: &Option<Rc<RefCell<TreeNode<i32>>>>,
        steps: &mut i32,
    ) -> i32 {
        if let Some(node) = node {
            let left = Self::helper(&node.as_ref().borrow().left, steps);
            let right = Self::helper(&node.as_ref().borrow().right, steps);
            *steps += left.abs() + right.abs();

            return left + right - 1 + node.as_ref().borrow().val;
        }
        0
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

    #[test]
    fn case1_test() {
        let v = vec![Some(3), Some(0), Some(0)];
        let tree = build_binary_tree(&v);
        let ret = Solution::distribute_coins(&tree);
        assert_eq!(ret, 2);
    }

    #[test]
    fn case2_test() {
        let v = vec![Some(0), Some(3), Some(0)];
        let tree = build_binary_tree(&v);
        let ret = Solution::distribute_coins(&tree);
        assert_eq!(ret, 3);
    }
}
