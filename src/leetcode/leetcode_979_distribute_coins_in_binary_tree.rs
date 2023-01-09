use std::cell::RefCell;
use std::rc::Rc;

/// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode<T> {
    pub val: T,
    pub left: Option<Rc<RefCell<TreeNode<T>>>>,
    pub right: Option<Rc<RefCell<TreeNode<T>>>>,
}

impl<T> TreeNode<T> {
    #[inline]
    pub fn new(val: T) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn distribute_coins(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        let mut steps = 0;
        Self::helper(&root, &mut steps);
        steps
    }

    #[allow(unused)]
    fn helper(node: &Option<Rc<RefCell<TreeNode<i32>>>>, steps: &mut i32) -> i32 {
        if let Some(node) = node {
            let left = Self::helper(&node.as_ref().borrow_mut().left, steps);
            let right = Self::helper(&node.as_ref().borrow_mut().right, steps);
            *steps += left.abs() + right.abs();

            return left + right - 1 + node.as_ref().borrow().val;
        }
        0
    }
}

use std::collections::VecDeque;

/// build binary tree from &[i32]
#[allow(unused)]
fn build_binary_tree<T>(input: &[Option<T>]) -> Option<Rc<RefCell<TreeNode<T>>>>
where
    T: Copy,
{
    let size = input.len();
    if size == 0 {
        return None;
    }

    let mut queue: VecDeque<Rc<RefCell<TreeNode<T>>>> = VecDeque::new();
    let root = Rc::new(RefCell::new(TreeNode::<T>::new(input[0].unwrap())));
    queue.push_back(root.clone());
    let mut i = 1;

    while i < size {
        let z1 = queue.pop_front().unwrap();
        if input[i].is_some() {
            z1.as_ref().borrow_mut().left =
                Some(Rc::new(RefCell::new(TreeNode::<T>::new(input[i].unwrap()))));
            queue.push_back(z1.borrow().left.as_ref().unwrap().clone());
        } else {
            z1.as_ref().borrow_mut().left = None;
        }

        i += 1;
        if i >= size {
            break;
        }
        if input[i].is_some() {
            z1.as_ref().borrow_mut().right =
                Some(Rc::new(RefCell::new(TreeNode::<T>::new(input[i].unwrap()))));
            queue.push_back(z1.borrow().right.as_ref().unwrap().clone());
        } else {
            z1.as_ref().borrow_mut().right = None;
        }
        i += 1;
    }
    Some(root)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let v = vec![Some(3), Some(0), Some(0)];
        let tree = build_binary_tree(&v[..]);
        let ret = Solution::distribute_coins(tree);
        assert_eq!(ret, 2);
    }

    #[test]
    fn case2_test() {
        let v = vec![Some(0), Some(3), Some(0)];
        let tree = build_binary_tree(&v[..]);
        let ret = Solution::distribute_coins(tree);
        assert_eq!(ret, 3);
    }
}
