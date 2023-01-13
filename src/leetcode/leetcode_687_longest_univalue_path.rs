// Given the root of a binary tree, return the length of the longest path,
// where each node in the path has the same value. This path may or may not pass through the root.
// The length of the path between two nodes is represented by the number of edges between them.

use std::{cell::RefCell, rc::Rc};

#[derive(PartialEq)]
#[allow(unused)]
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
    pub fn longest_univalue_path<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>) -> i32
    where
        T: PartialEq + Copy,
    {
        fn helper<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>) -> (Option<(T, i32)>, Option<i32>)
        where
            T: PartialEq + Copy,
        {
            // 第一个元素返回 (某个数字, 数字出现的次数) , 还能参与上层路径的建设
            // 第二个元素返回 本root下面能提供的最长长度的路径的值，不准备参与上层路径的建设了
            if let Some(n) = root {
                let n = n.as_ref().borrow();
                let root_val = n.val;

                let (continue_construction_left, stop_construction_left) = helper(&n.left);
                let (continue_construction_right, stop_construction_right) = helper(&n.right);

                let continue_number = {
                    match (continue_construction_left, continue_construction_right) {
                        (Some((left_val, left_number)), Some((right_val, right_number))) => {
                            if left_val == root_val && left_val == right_val {
                                left_number.max(right_number) + 1
                            } else if left_val == root_val {
                                1 + left_number
                            } else if right_val == root_val {
                                1 + right_number
                            } else {
                                1
                            }
                        }
                        (None, Some((val, number))) | (Some((val, number)), None) => {
                            if val == root_val {
                                number + 1
                            } else {
                                1
                            }
                        }
                        (None, None) => 1,
                    }
                };
                let stop_number = {
                    match (continue_construction_left, continue_construction_right) {
                        (Some((left_val, left_number)), Some((right_val, right_number))) => {
                            if left_val == root_val && left_val == right_val {
                                left_number + right_number + 1
                            } else if left_val == root_val {
                                1 + left_number
                            } else if right_val == root_val {
                                1 + right_number
                            } else {
                                1
                            }
                        }
                        (None, Some((val, number))) | (Some((val, number)), None) => {
                            if val == root_val {
                                number + 1
                            } else {
                                1
                            }
                        }
                        (None, None) => 1,
                    }
                    .max(
                        match (stop_construction_left, stop_construction_right) {
                            (Some(left), Some(right)) => left.max(right),
                            (Some(l), None) | (None, Some(l)) => l,
                            (None, None) => 0,
                        },
                    )
                };

                (Some((root_val, continue_number)), Some(stop_number))
            } else {
                (None, None)
            }
        }

        if let (Some((v, v1)), Some(v2)) = helper(root) {
            v1.max(v2) - 1
        } else {
            0
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
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

    #[test]
    fn case1_test() {
        let null = 100;
        let root = [5, 4, 5, 1, 1, null, 5].map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        });
        let output = 2;
        let root = build_binary_tree(&root);
        let ret = Solution::longest_univalue_path(&root);
        assert_eq!(ret, output);
        // Explanation: The shown image shows that the longest path of the same value (i.e. 5).
    }

    #[test]
    fn case2_test() {
        let null = 100;
        let root = [1, 4, 5, 4, 4, null, 5].map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        });
        let output = 2;
        let root = build_binary_tree(&root);
        let ret = Solution::longest_univalue_path(&root);
        assert_eq!(ret, output);
        // The shown image shows that the longest path of the same value (i.e. 4).
    }

    #[test]
    fn case3_test() {
        let null = 100;
        let root = [1, 2, 2, 2, 2].map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        });
        let output = 2;
        let root = build_binary_tree(&root);
        let ret = Solution::longest_univalue_path(&root);
        assert_eq!(ret, output);
        // The shown image shows that the longest path of the same value (i.e. 4).
    }
}
