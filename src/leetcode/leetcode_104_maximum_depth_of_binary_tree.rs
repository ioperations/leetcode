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
    fn max_depth<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> i32
    where
        T: Copy,
    {
        Self::get_max_depth(&root)
        // Self::max_depthv1(root, 0)
    }

    #[allow(unused)]
    fn get_max_depth<T>(node: &Option<Rc<RefCell<TreeNode<T>>>>) -> i32 {
        node.as_ref()
            .map(|node| node.borrow())
            .map(|node| 1 + Self::get_max_depth(&node.left).max(Self::get_max_depth(&node.right)))
            .unwrap_or(0)
    }

    #[allow(unused)]
    fn max_depthv1<T>(root: Option<Rc<RefCell<TreeNode<T>>>>, depth: i32) -> i32 {
        if root.is_none() {
            return depth;
        }
        let mut depth = depth;
        depth += 1;
        let root = root.unwrap();
        depth = Self::max_depthv1(root.as_ref().borrow_mut().left.take(), depth);
        depth = Self::max_depthv1(root.as_ref().borrow_mut().right.take(), depth);
        depth
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
            z1.as_ref().borrow_mut().right = None
        }
        i += 1;
    }
    Some(root)
}

/// expect binary tree equal to input
#[allow(unused)]
fn expect_binary_tree<T>(input: &[Option<T>], root: Option<Rc<RefCell<TreeNode<T>>>>)
where
    T: std::cmp::PartialEq + std::fmt::Debug + Copy,
{
    // pass
    let mut i = 0;
    let size = input.len();
    if i == size {
        return;
    }

    let mut q: VecDeque<Rc<RefCell<TreeNode<T>>>> = VecDeque::new();
    q.push_back(root.as_ref().unwrap().clone());
    while !q.is_empty() {
        let n1 = q.pop_front().unwrap();
        assert_eq!(Some(n1.as_ref().borrow().val), input[i]);
        i += 1;
        if let Some(v) = &n1.as_ref().borrow().left {
            q.push_back(v.clone());
        };
        if let Some(v) = &n1.as_ref().borrow().right {
            q.push_back(v.clone());
        };
    }

    assert_eq!(i, size);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let vec = vec![Some(3), Some(9), Some(20), None, None, Some(15), Some(7)];

        let tree = build_binary_tree(&vec[..]);
        let ret = Solution::max_depth(tree);
        assert_eq!(ret, 3);
    }

    #[test]
    fn case2_test() {
        let vec = vec![Some(1), None, Some(2)];

        let tree = build_binary_tree(&vec[..]);
        let ret = Solution::max_depth(tree);
        assert_eq!(ret, 2);
    }
}
