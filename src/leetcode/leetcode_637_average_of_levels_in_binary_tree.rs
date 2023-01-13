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
    fn average_of_levels(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> Vec<f64> {
        let mut v = vec![];

        if let Some(r) = root {
            let mut qu = VecDeque::new();

            let mut cur_level = 1;
            let mut cur_count = 0;
            let mut cur_sum: f64 = 0.0;
            qu.push_back((r, cur_level));
            while !qu.is_empty() {
                let z = qu.pop_front().unwrap();
                if z.1 == cur_level {
                    cur_sum += z.0.as_ref().borrow().val as f64;
                    cur_count += 1;
                } else {
                    v.push(cur_sum / cur_count as f64);
                    cur_level += 1;
                    cur_sum = f64::from(z.0.as_ref().borrow().val);
                    cur_count = 1;
                }
                if let Some(n) = z.0.as_ref().borrow_mut().left.take() {
                    qu.push_back((n, cur_level + 1));
                };
                if let Some(n) = z.0.as_ref().borrow_mut().right.take() {
                    qu.push_back((n, cur_level + 1));
                };
            }
            if cur_count != 0 {
                v.push(cur_sum / f64::from(cur_count));
            }
        }
        v
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
    use std::usize;

    use super::*;

    #[test]
    fn case1_test() {
        let r1 = vec![Some(3), Some(9), Some(20), None, None, Some(15), Some(7)];
        let t1 = build_binary_tree(&r1);
        let output = vec![3.00000, 14.50000, 11.00000];
        let ret = Solution::average_of_levels(t1);
        let mut i = 0;
        for j in ret {
            assert!((j - output[i as usize]).abs() < std::f64::EPSILON);
            i += 1;
        }

        assert_eq!(i, output.len() as i32);
    }

    #[test]
    fn case2_test() {
        let r1 = vec![Some(3), Some(9), Some(20), Some(15), Some(7)];
        let t1 = build_binary_tree(&r1);
        let output = vec![3.00000, 14.50000, 11.00000];
        let ret = Solution::average_of_levels(t1);
        let mut i = 0;
        for j in ret {
            assert!((j - output[i as usize]).abs() < std::f64::EPSILON);
            i += 1;
        }

        assert_eq!(i, output.len() as i32);
    }

    #[test]
    fn case3_test() {
        let r1 = vec![Some(3), Some(9), Some(20), None, None, Some(15), Some(7)];
        let t1 = build_binary_tree(&r1);
        let output = vec![3.00000, 14.50000, 11.00000];
        let ret = Solution::average_of_levels(t1);
        let mut i = 0;
        for j in ret {
            assert!((j - output[i as usize]).abs() < std::f64::EPSILON);
            i += 1;
        }

        assert_eq!(i, output.len() as i32);
    }
}
