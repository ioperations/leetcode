// A path in a binary tree is a sequence of nodes where each pair of adjacent nodes
// in the sequence has an edge connecting them.
// A node can only appear in the sequence at most once.
// Note that the path does not need to pass through the root.
//
// The path sum of a path is the sum of the node's values in the path.
// Given the root of a binary tree, return the maximum path sum of any non-empty path.

use std::{cell::RefCell, collections::VecDeque, rc::Rc};

// Definition for a binary tree node.
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
    pub fn max_path_sum(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        fn helper(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> (Option<i32>, Option<i32>) {
            if let Some(v) = root {
                let left = helper(&v.borrow_mut().left);
                let right = helper(&v.borrow_mut().right);
                let z = v.borrow().val;
                return match (left, right) {
                    ((Some(l), Some(v)), (Some(r), Some(v2))) => {
                        return (
                            Some(z.max(l + z).max(r + z)),
                            Some(
                                v.max(v2)
                                    .max(l + r + z)
                                    .max(z)
                                    .max(l)
                                    .max(r)
                                    .max(l + z)
                                    .max(r + z),
                            ),
                        );
                    }
                    ((Some(l), Some(v)), (None, None)) | ((None, None), (Some(l), Some(v))) => {
                        return (Some(z.max(l + z)), Some(v.max(l + z).max(z)));
                    }
                    ((None, None), ((None, None))) => {
                        return (Some(z), Some(z));
                    }
                    (_, _) => todo!(),
                };
            }
            (None, None)
        }
        let (a, b) = helper(root);
        a.unwrap().max(b.unwrap())
    }

    #[allow(unused)]
    pub fn max_path_sum_v2(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        fn helper(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> (i32, i32) {
            // how many can we get when root is
            // how many can
            if let Some(v) = root {
                let (left, h) = helper(v.borrow_mut().left.take());
                let (right, r) = helper(v.borrow_mut().right.take());
                let z = left + right + v.borrow().val;
                return (left.max(right).max(z), h.max(r));
            }
            (0, 0)
        }
        let (as_routine, v) = helper(root);
        as_routine.max(v)
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
        let root = [1, 2, 3].map(Some);
        let output = 6;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
        // Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
    }

    #[test]
    fn case2_test() {
        let null = -1;
        let root = [-10, 9, 20, null, null, 15, 7].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = 42;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
        // The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
    }

    #[test]
    fn case3_test() {
        let null = -1;
        let root = [-3].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = -3;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let null = -2;
        let root = [2, -1].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = 2;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case5_test() {
        let null = -100_000;
        let root = [-1, -2, 10, -6, null, -3, -6].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = 10;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case6_test() {
        let null = -100_000;
        let root = [-6, null, 3, 2].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = 5;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case7_test() {
        let null = -100_000;
        let root = [-1, 5, null, 4, null, null, 2, -4].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = 11;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case8_test() {
        let null = -100_000;
        let root = [-1, null, 6, null, -4].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = 6;
        let root = build_binary_tree(&root);
        let ret = Solution::max_path_sum(&root);
        assert_eq!(ret, output);
    }
}
