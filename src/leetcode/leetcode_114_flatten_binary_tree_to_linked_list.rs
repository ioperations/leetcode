// Given the root of a binary tree, flatten the tree into a "linked list":
//
// The "linked list" should use the same TreeNode class where the right child
// pointer points to the next node in the list and the left child pointer is
// always null. The "linked list" should be in the same order as a pre-order
// traversal of the binary tree

use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn flatten<T>(root: &mut Option<Rc<RefCell<TreeNode<T>>>>)
    where
        T: Copy,
    {
        let mut vals: Vec<T> = Vec::new();
        Self::read(root, &mut vals);
        Self::build(root, &vals);
    }

    #[allow(unused)]
    pub fn build<T>(root: &mut Option<Rc<RefCell<TreeNode<T>>>>, vals: &[T])
    where
        T: Clone + Copy,
    {
        if vals.is_empty() {
            return;
        }

        if root.is_none() {
            *root = Some(Rc::new(RefCell::new(TreeNode::new(vals[0]))));
        } else {
            root.as_mut().unwrap().borrow_mut().val = vals[0];
        }
        root.as_mut().unwrap().borrow_mut().left = None;
        Self::build(&mut root.as_mut().unwrap().borrow_mut().right, &vals[1..]);
    }

    #[allow(unused)]
    pub fn read<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>, vals: &mut Vec<T>)
    where
        T: Copy,
    {
        if let Some(root) = root {
            vals.push(root.as_ref().borrow().val);
            Self::read(&root.as_ref().borrow().left, vals);
            Self::read(&root.as_ref().borrow().right, vals);
        }
    }

    #[allow(unused)]
    pub fn pre_order<T>(
        root: &Option<Rc<RefCell<TreeNode<T>>>>,
    ) -> Vec<Option<T>>
    where
        T: Copy,
    {
        let mut v: Vec<Option<T>> = vec![];
        Self::pre_order_v1(root, &mut v);
        v
    }

    #[allow(unused)]
    pub fn pre_order_v1<T>(
        root: &Option<Rc<RefCell<TreeNode<T>>>>,
        v: &mut Vec<Option<T>>,
    ) where
        T: Copy,
    {
        if let Some(root) = root {
            v.push(Some(root.as_ref().borrow().val));

            Self::pre_order_v1(&root.as_ref().borrow().left, v);
            Self::pre_order_v1(&root.as_ref().borrow().right, v);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::{build_binary_tree, right_expect};
    use super::*;

    #[test]
    fn case1_test() {
        let t = vec![Some(1), Some(2), Some(5), Some(3), Some(4), Some(6)];
        let mut tr = build_binary_tree(&t);
        let tr1 = build_binary_tree(&t);
        let expected: Vec<Option<i32>> = Solution::pre_order(&tr1);

        Solution::flatten(&mut tr);
        right_expect(&tr, &expected);
    }

    #[test]
    fn case2_test() {
        let t: Vec<Option<i32>> = vec![];
        let mut tr = build_binary_tree(&t);
        let tr1 = build_binary_tree(&t);
        let expected: Vec<Option<i32>> = Solution::pre_order(&tr1);

        Solution::flatten(&mut tr);
        right_expect(&tr, &expected);
    }

    #[test]
    fn case3_test() {
        let t = vec![Some(0)];
        let mut tr = build_binary_tree(&t);
        let tr1 = build_binary_tree(&t);
        let expected: Vec<Option<i32>> = Solution::pre_order(&tr1);

        Solution::flatten(&mut tr);
        right_expect(&tr, &expected);
    }
}
