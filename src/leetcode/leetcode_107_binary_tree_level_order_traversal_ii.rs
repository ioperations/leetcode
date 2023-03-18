// Given the root of a binary tree, return the bottom-up level order traversal
// of its nodes' values. (i.e., from left to right, level by level from leaf to
// root).

use super::leetcode_binary_tree::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn level_order_bottom<T>(
        root: Option<Rc<RefCell<TreeNode<T>>>>,
    ) -> Vec<Vec<T>>
    where
        T: std::default::Default + Copy,
    {
        use std::collections::VecDeque;
        type Rn<T> = Rc<RefCell<TreeNode<T>>>;

        struct Node<T> {
            node: Rn<T>,
            level: i32,
        }

        let mut que = VecDeque::new();
        if let Some(v) = root {
            que.push_front(Node { node: v, level: 1 });
        }

        let mut current_expected = 1;
        let mut ret = vec![];
        let mut current_level = vec![];
        while !que.is_empty() {
            let Node { node, level } = que.pop_front().unwrap();
            let mut node = node.borrow_mut();
            if level != current_expected {
                ret.insert(0, current_level);
                current_expected += 1;
                current_level = vec![];
            }
            current_level.push(std::mem::take(&mut node.val));
            if let Some(left) = node.left.take() {
                que.push_back(Node {
                    node: left,
                    level: level + 1,
                });
            }
            if let Some(right) = node.right.take() {
                que.push_back(Node {
                    node: right,
                    level: level + 1,
                });
            }
        }

        if !current_level.is_empty() {
            ret.insert(0, current_level);
        }

        ret
    }
}

#[cfg(test)]
mod test {
    use crate::leetcode::leetcode_binary_tree::build_binary_tree;

    use super::*;

    #[test]
    fn case1_test() {
        let null = -1;
        let root = [3, 9, 20, null, null, 15, 7].map(|i| {
            if i == null {
                None
            } else {
                Some(i)
            }
        });
        let output = [vec![15, 7], vec![9, 20], vec![3]];
        let root = build_binary_tree(&root);
        let ret = Solution::level_order_bottom(root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let null = -1;
        let root = [1].map(|i| if i == null { None } else { Some(i) });
        let output = [vec![1]];
        let root = build_binary_tree(&root);
        let ret = Solution::level_order_bottom(root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let null = -1;
        let root = [].map(|i: i32| if i == null { None } else { Some(i) });
        let output: Vec<Vec<i32>> = [].to_vec();
        let root = build_binary_tree(&root);
        let ret = Solution::level_order_bottom(root);
        assert_eq!(ret, output);
    }
}
