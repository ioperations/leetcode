// Given the root of a binary tree, return the preorder traversal of its nodes' values.

use std::{cell::RefCell, collections::VecDeque, rc::Rc};

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
#[allow(unused)]
pub struct TreeNode<T> {
    pub val: T,
    pub left: Option<Rc<RefCell<TreeNode<T>>>>,
    pub right: Option<Rc<RefCell<TreeNode<T>>>>,
}

impl<T> TreeNode<T> {
    #[inline]
    #[allow(unused)]
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
    pub fn preorder_traversal(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> Vec<i32> {
        let mut vec = Vec::new();
        Self::preorder_traversal_recursive(root, &mut vec);
        vec
    }

    #[allow(unused)]
    fn preorder_traversal_recursive(root: &Option<Rc<RefCell<TreeNode<i32>>>>, vec: &mut Vec<i32>) {
        if let Some(root) = root {
            vec.push(root.borrow().val);
            Self::preorder_traversal_recursive(&root.borrow_mut().left, vec);
            Self::preorder_traversal_recursive(&root.borrow_mut().right, vec);
        }
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

#[cfg(test)]
mod tests {
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
        let output = [].to_vec();
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
