// Given the root of a binary tree, invert the tree, and return its root.
use std::{cell::RefCell, collections::VecDeque, rc::Rc};

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

/// expect binary tree equal to input
#[allow(unused)]
fn flatten_binary_tree<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> Vec<Option<T>>
where
    T: std::cmp::PartialEq + std::fmt::Debug + Copy,
{
    let mut q: VecDeque<Option<Rc<RefCell<TreeNode<T>>>>> = VecDeque::new();
    let mut ret: Vec<Option<T>> = vec![];
    q.push_back(root);
    while !q.is_empty() {
        let n1 = q.pop_front().unwrap();
        if let Some(n) = &n1 {
            ret.push(Some(n.as_ref().borrow().val));
            q.push_back(n.as_ref().borrow_mut().left.take());
            q.push_back(n.as_ref().borrow_mut().right.take());
        } else {
            ret.push(None);
        }
    }

    ret.into_iter()
        .rev()
        .skip_while(std::option::Option::is_none)
        .collect::<Vec<Option<T>>>()
        .into_iter()
        .rev()
        .collect::<Vec<Option<T>>>()
}

#[cfg(test)]
mod tests {
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
