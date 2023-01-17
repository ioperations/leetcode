// Given the root of a binary tree, find the maximum value
//     v for which there exist different nodes a and b where
//     v = |a.val - b.val| and a is an ancestor of b.
//     A node a is an ancestor of b if either:
//     any child of a is equal to b or any child of a is an ancestor of b.

use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, cmp, rc::Rc};

#[allow(unused)]
struct Solution;

#[allow(unused)]
struct MinMax {
    min: i32,
    max: i32,
    answer: i32,
}

impl Solution {
    #[allow(unused)]
    fn min_max(node_ref: &Rc<RefCell<TreeNode<i32>>>) -> MinMax {
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
                let c = Self::min_max(&Rc::clone(child_option));
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
    pub fn max_ancestor_diff(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        if let Some(node_ref) = root {
            Self::min_max(&Rc::clone(node_ref)).answer
        } else {
            panic!("bad_input");
        }
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
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
        // Explanation: We have various ancestor-node differences, some of which
        // are given below : |8 - 3| = 5
        // |3 - 7| = 4
        // |8 - 1| = 7
        // |10 - 13| = 3
        // Among all possible differences, the maximum value of 7 is obtained by
        // |8 - 1| = 7.
        let root = build_binary_tree(&root);
        let ret = Solution::max_ancestor_diff(&root);
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
        let root = build_binary_tree(&root);
        let ret = Solution::max_ancestor_diff(&root);
        assert_eq!(ret, output);
    }
}
