// You are given the root of a binary tree containing digits from 0 to 9 only.
// Each root-to-leaf path in the tree represents a number.
// For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
// Return the total sum of all root-to-leaf numbers. Test cases are generated so
// that the answer will fit in a 32-bit integer. A leaf node is a node with no
// children.

use super::leetcode_binary_tree::TreeNode;
use std::cell::RefCell;
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn sum_numbers(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        type Rn = Rc<RefCell<TreeNode<i32>>>;
        fn calculate(root: Option<&Rn>, pre: i32) -> (i32, bool) {
            if let Some(mut v) = root {
                let v = v.borrow();
                let (v1, last1) =
                    calculate(v.left.as_ref(), (pre + v.val) * 10);
                let (v2, last2) =
                    calculate(v.right.as_ref(), (pre + v.val) * 10);
                match (last1, last2) {
                    (true, true) => (v1 + v2, true),
                    (true, false) => (v1, true),
                    (false, true) => (v2, true),
                    (false, false) => (pre + v.val, true),
                }
            } else {
                (pre, false)
            }
        }
        calculate(root.as_ref(), 0).0
    }
}
#[cfg(test)]
mod test {
    use crate::leetcode::leetcode_binary_tree::build_binary_tree;

    use super::*;

    pub trait WrapSome<T> {
        fn wrap_some(self) -> Vec<Option<T>>;
    }

    impl<T> WrapSome<T> for Vec<T> {
        fn wrap_some(self) -> Vec<Option<T>> {
            self.into_iter().map(Some).collect()
        }
    }

    #[test]
    fn case0_test() {
        let root: Vec<_> = vec![1].wrap_some();
        let root = build_binary_tree(&root);
        let output = 1;
        let ret = Solution::sum_numbers(&root);
        assert_eq!(ret, output);
        // Explanation:
        // The root-to-leaf path 1->2 represents the number 12.
        // The root-to-leaf path 1->3 represents the number 13.
        // Therefore, sum = 12 + 13 = 25.
    }

    #[test]
    fn case1_test() {
        let root: Vec<_> = vec![1, 2, 3].wrap_some();
        let root = build_binary_tree(&root);
        let output = 25;
        let ret = Solution::sum_numbers(&root);
        assert_eq!(ret, output);
        // Explanation:
        // The root-to-leaf path 1->2 represents the number 12.
        // The root-to-leaf path 1->3 represents the number 13.
        // Therefore, sum = 12 + 13 = 25.
    }

    #[test]
    fn case2_test() {
        let root: Vec<_> = vec![4, 9, 0, 5, 1].wrap_some();
        let root = build_binary_tree(&root);
        let output = 1026;
        let ret = Solution::sum_numbers(&root);
        assert_eq!(ret, output);
        // Explanation:
        // The root-to-leaf path 4->9->5 represents the number 495.
        // The root-to-leaf path 4->9->1 represents the number 491.
        // The root-to-leaf path 4->0 represents the number 40.
        // Therefore, sum = 495 + 491 + 40 = 1026.
    }
}
