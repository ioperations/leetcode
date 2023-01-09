/*
    Given the root of a binary tree, find the maximum value
    v for which there exist different nodes a and b where
    v = |a.val - b.val| and a is an ancestor of b.
    A node a is an ancestor of b if either:
    any child of a is equal to b or any child of a is an ancestor of b.
*/

// Definition for a binary tree node.
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
use std::cmp;
use std::collections::VecDeque;
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_ancestor_diff_v2(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        fn helper(root: Rc<RefCell<TreeNode<i32>>>) -> ((i32, i32), i32) {
            ((0, 0), 0)
        }
        if let Some(v) = root {
            let val = v.borrow().val;
            let ret = helper(v);
            return val
                .abs_diff(ret.0 .0)
                .max(val.abs_diff(ret.0 .1))
                .max(ret.1 as u32) as i32;
        }

        0
    }
}

#[allow(unused)]
struct MinMax {
    min: i32,
    max: i32,
    answer: i32,
}

impl Solution {
    #[allow(unused)]
    fn min_max(node_ref: Rc<RefCell<TreeNode<i32>>>) -> MinMax {
        let node = node_ref.borrow();
        let mut a = MinMax {
            min: node.val,
            max: node.val,
            answer: 0,
        };
        if node.left.is_none() && node.right.is_none() {
            a
        } else {
            let children = vec![&node.left, &node.right];
            for child_option in children.iter().copied().flatten() {
                let c = Self::min_max(Rc::clone(child_option));
                a.answer = cmp::max(a.answer, c.answer);
                a.answer = cmp::max(a.answer, (node.val - c.min).abs());
                a.answer = cmp::max(a.answer, (node.val - c.max).abs());
                a.min = cmp::min(a.min, c.min);
                a.max = cmp::max(a.max, c.max);
            }
            a
        }
    }
    #[allow(unused)]
    pub fn max_ancestor_diff(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        if let Some(node_ref) = root {
            Self::min_max(Rc::clone(&node_ref)).answer
        } else {
            panic!("bad_input");
        }
    }
}

/// build binary tree from &\[T\]
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let null = -1;
        let root = [8, 3, 10, 1, 6, null, 14, null, null, 4, 7, 13].map(|i| {
            if i == -1 {
                return None;
            }
            Some(i)
        });
        let output = 7;
        /*
         * Explanation: We have various ancestor-node differences, some of which are given below :
         * |8 - 3| = 5
         * |3 - 7| = 4
         * |8 - 1| = 7
         * |10 - 13| = 3
         * Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
         */
        let ret = Solution::max_ancestor_diff(build_binary_tree(&root));
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let null = -1;
        let root = [1, null, 2, null, 0, 3].map(|i| {
            if i == -1 {
                return None;
            }
            Some(i)
        });
        let output = 3;
        let ret = Solution::max_ancestor_diff(build_binary_tree(&root));
        assert_eq!(ret, output);
    }
}
