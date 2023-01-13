// Given the root of a binary tree, flatten the tree into a "linked list":
//
// The "linked list" should use the same TreeNode class where the right child
// pointer points to the next node in the list and the left child pointer is always
// null. The "linked list" should be in the same order as a pre-order traversal of
// the binary tree

use std::{cell::RefCell, collections::VecDeque, rc::Rc};

/// Definition for a binary tree node.
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
    pub fn pre_order<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>) -> Vec<Option<T>>
    where
        T: Copy,
    {
        let mut v: Vec<Option<T>> = vec![];
        Self::pre_order_v1(root, &mut v);
        v
    }

    #[allow(unused)]
    pub fn pre_order_v1<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>, v: &mut Vec<Option<T>>)
    where
        T: Copy,
    {
        if let Some(root) = root {
            v.push(Some(root.as_ref().borrow().val));

            Self::pre_order_v1(&root.as_ref().borrow().left, v);
            Self::pre_order_v1(&root.as_ref().borrow().right, v);
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
        } else {
            z1.as_ref().borrow_mut().left = None;
        }

        queue.push_back(z1.borrow().left.as_ref().unwrap().clone());
        i += 1;
        if i >= size {
            break;
        }
        if input[i].is_some() {
            z1.as_ref().borrow_mut().right =
                Some(Rc::new(RefCell::new(TreeNode::<T>::new(input[i].unwrap()))));
        } else {
            z1.as_ref().borrow_mut().right = None;
        }
        queue.push_back(z1.borrow().right.as_ref().unwrap().clone());
        i += 1;
    }
    Some(root)
}

#[allow(unused)]
fn right_expect<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>, vec: &[Option<T>])
where
    T: std::fmt::Debug + std::cmp::PartialEq + Copy,
{
    if vec.is_empty() && root.is_none() {
        return;
    }

    assert!(root.is_some());

    if let Some(n) = &root {
        assert!(vec[0].is_some());
        assert_eq!(n.as_ref().borrow().val, vec[0].unwrap());
        assert!(n.as_ref().borrow_mut().left.is_none());
        right_expect(&n.as_ref().borrow_mut().right, &vec[1..]);
    }
}

#[cfg(test)]
mod tests {
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
