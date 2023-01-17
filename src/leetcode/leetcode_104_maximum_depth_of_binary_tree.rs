use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn max_depth<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>) -> i32
    where
        T: Copy,
    {
        Self::get_max_depth(root)
        // Self::max_depthv1(root, 0)
    }

    #[allow(unused)]
    fn get_max_depth<T>(node: &Option<Rc<RefCell<TreeNode<T>>>>) -> i32 {
        node.as_ref().map(|node| node.borrow()).map_or(0, |node| {
            1 + Self::get_max_depth(&node.left)
                .max(Self::get_max_depth(&node.right))
        })
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

    #[test]
    fn case1_test() {
        let vec =
            vec![Some(3), Some(9), Some(20), None, None, Some(15), Some(7)];

        let tree = build_binary_tree(&vec);
        let ret = Solution::max_depth(&tree);
        assert_eq!(ret, 3);
    }

    #[test]
    fn case2_test() {
        let vec = vec![Some(1), None, Some(2)];

        let tree = build_binary_tree(&vec);
        let ret = Solution::max_depth(&tree);
        assert_eq!(ret, 2);
    }
}
