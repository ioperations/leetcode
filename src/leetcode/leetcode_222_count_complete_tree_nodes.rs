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

use std::cell::RefCell;
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn count_nodes(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        match root {
            None => 0,
            Some(n) => {
                let mut n = n.as_ref().borrow_mut();
                1 + Self::count_nodes(n.left.take()) + Self::count_nodes(n.right.take())
            }
        }
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
        } else {
            z1.as_ref().borrow_mut().left = None;
        }

        queue.push_back(z1.borrow().left.as_ref().unwrap().clone());
        i += 1;
        if i >= size {
            break;
        }
        if input[i].is_some() {
            z1.borrow_mut().right =
                Some(Rc::new(RefCell::new(TreeNode::<T>::new(input[i].unwrap()))));
        } else {
            z1.borrow_mut().right = None;
        }
        queue.push_back(z1.borrow().right.as_ref().unwrap().clone());
        i += 1;
    }
    Some(root)
}

/// expect binary tree equal to input
#[allow(unused)]
fn expect_binary_tree<T: std::cmp::PartialEq + std::fmt::Debug + Copy>(
    input: &[Option<T>],
    root: Option<Rc<RefCell<TreeNode<T>>>>,
) -> () {
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

#[test]
fn test_v1_test() {
    let v: Vec<Option<i32>> = vec![Some(1), Some(2), Some(3), Some(4), Some(5), Some(6)];
    let root = build_binary_tree::<i32>(&v[..]);
    expect_binary_tree(&v[..], root.clone());

    let ret = Solution::count_nodes(root);
    assert_eq!(ret, 6);
}

#[test]
fn test_v2_test() {
    let v: Vec<Option<i32>> = vec![Some(1)];
    let root = build_binary_tree::<i32>(&v[..]);
    expect_binary_tree(&v[..], root.clone());

    let ret = Solution::count_nodes(root);
    assert_eq!(ret, 1);
}

#[test]
fn test_v3_test() {
    let v: Vec<Option<i32>> = vec![];
    let root = build_binary_tree(&v[..]);
    expect_binary_tree(&v[..], root.clone());

    let ret = Solution::count_nodes(root);
    assert_eq!(ret, 0);
}
