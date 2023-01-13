use std::{cell::RefCell, collections::VecDeque, rc::Rc};

/// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode<T> {
    pub val: T,
    pub left: Option<Rc<RefCell<TreeNode<T>>>>,
    pub right: Option<Rc<RefCell<TreeNode<T>>>>,
}

impl<T> TreeNode<T> {
    #[allow(unused)]
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
    fn sorted_array_to_bst<T>(nums: &[T]) -> Option<Rc<RefCell<TreeNode<T>>>>
    where
        T: Copy,
    {
        // pass
        Self::helper(nums, 0, (nums.len() - 1) as i32)
    }

    #[allow(unused)]
    fn helper<T>(nums: &[T], start: i32, end: i32) -> Option<Rc<RefCell<TreeNode<T>>>>
    where
        T: Copy,
    {
        if start > end {
            return None;
        }
        let mid = start + (end - start) / 2;
        // println!("start is {}, end is {}, mid is {}", start, end, mid);

        let root = Rc::new(RefCell::new(TreeNode::new(nums[mid as usize])));
        root.as_ref().borrow_mut().left = Self::helper(nums, start, mid - 1);
        root.as_ref().borrow_mut().right = Self::helper(nums, mid + 1, end);

        Some(root)
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

    let mut it = ret.iter().rev().skip_while(|x| x.is_none());

    let mut ret = vec![];
    for v in it {
        ret.push(*v);
    }
    ret.into_iter().rev().collect()
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use super::*;

    #[test]
    fn case0_test() {
        let tree = [Some(1), Some(2), Some(3), Some(4)];
        let v = build_binary_tree(&tree);
        let ret = flatten_binary_tree(v);
        assert_eq!(ret, tree);
    }

    #[test]
    fn case1_test() {
        let tree = [Some(-10), Some(-3), Some(0), Some(5), Some(9)];
        let v = build_binary_tree(&tree);
        let ret = flatten_binary_tree(v);
        assert_eq!(ret, tree);
    }

    #[test]
    fn case2_test() {
        let v = vec![-10, -3, 0, 5, 9];
        let ret = Solution::sorted_array_to_bst(&v);
        let ret = flatten_binary_tree(ret);
        println!("ret =>  {ret:?}");
        let mut hashset = HashSet::new();
        hashset.insert([Some(0), Some(-3), Some(9), Some(10), None, Some(9)].to_vec());
        hashset.insert([Some(0), Some(-10), Some(5), None, Some(-3), None, Some(9)].to_vec());

        assert!(hashset.contains(&ret));
    }
}
