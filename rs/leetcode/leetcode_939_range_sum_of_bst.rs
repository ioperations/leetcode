// Given the root node of a binary search tree and two integers low and high,
// return the sum of values of all nodes with a value in the inclusive range
// [low, high].

use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn range_sum_bst(
        root: Option<&Rc<RefCell<TreeNode<i32>>>>,
        low: i32,
        high: i32,
    ) -> i32 {
        match root {
            None => 0,
            Some(node) => {
                let node = node.borrow();
                if high < node.val {
                    Self::range_sum_bst(node.left.as_ref(), low, high)
                } else if node.val < low {
                    Self::range_sum_bst(node.right.as_ref(), low, high)
                } else {
                    Self::range_sum_bst(node.left.as_ref(), low, high)
                        + node.val
                        + Self::range_sum_bst(node.right.as_ref(), low, high)
                }
            }
        }
    }

    #[allow(unused)]
    pub fn range_sum_bst_v2(
        root: Option<Rc<RefCell<TreeNode<i32>>>>,
        low: i32,
        high: i32,
    ) -> i32 {
        let mut stack = vec![root];
        let mut sum = 0;

        while let Some(node) = stack.pop() {
            if let Some(node) = node {
                let node = node.borrow();
                if node.val >= low && node.val <= high {
                    sum += node.val;
                }
                if node.val > low {
                    stack.push(node.left.clone());
                }
                if node.val < high {
                    stack.push(node.right.clone());
                }
            }
        }

        sum
    }

    #[allow(unused)]
    pub fn range_sum_bst_v1(
        root: Option<&Rc<RefCell<TreeNode<i32>>>>,
        low: i32,
        high: i32,
    ) -> i32 {
        match root {
            Some(head) => {
                let head_value: i32 = head.borrow().val;
                let extra = if head_value == high || head_value == low {
                    head_value
                } else {
                    0
                };

                if head_value <= low {
                    return extra
                        + Self::range_sum_bst_v1(
                            head.borrow().right.as_ref(),
                            low,
                            high,
                        );
                } else if head_value >= high {
                    return extra
                        + Self::range_sum_bst_v1(
                            head.borrow().left.as_ref(),
                            low,
                            high,
                        );
                }
                let left = Self::range_sum_bst_v1(
                    head.borrow().left.as_ref(),
                    low,
                    high,
                );
                let right = Self::range_sum_bst_v1(
                    head.borrow().right.as_ref(),
                    low,
                    high,
                );
                left + right + head_value
            }
            None => 0,
        }
    }
}

#[cfg(test)]
mod tests_rec {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let root = [10, 5, 15, 3, 7, -1, 18];
        let low = 7;
        let high = 15;
        let output = 32;
        // Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 +
        // 15 = 32.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::range_sum_bst(root.as_ref(), low, high);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let root = [10, 5, 15, 3, 7, 13, 18, 1, -1, 6];
        let low = 6;
        let high = 10;
        let output = 23;
        // Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::range_sum_bst(root.as_ref(), low, high);
        assert_eq!(ret, output);
    }
    #[bench]
    fn bench_rec(b: &mut test::Bencher) {
        let root = [10, 5, 15, 3, 7, 13, 18, 1, -1, 6];
        let low = 6;
        let high = 10;
        let output = 23;
        // Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        b.iter(|| {
            let root = build_binary_tree(&root);
            let ret = Solution::range_sum_bst(root.as_ref(), low, high);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_v1 {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let root = [10, 5, 15, 3, 7, -1, 18];
        let low = 7;
        let high = 15;
        let output = 32;
        // Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 +
        // 15 = 32.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::range_sum_bst_v1(root.as_ref(), low, high);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let root = [10, 5, 15, 3, 7, 13, 18, 1, -1, 6];
        let low = 6;
        let high = 10;
        let output = 23;
        // Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::range_sum_bst_v1(root.as_ref(), low, high);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        let root = [10, 5, 15, 3, 7, 13, 18, 1, -1, 6];
        let low = 6;
        let high = 10;
        let output = 23;
        // Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        b.iter(|| {
            let root = build_binary_tree(&root);
            let ret = Solution::range_sum_bst_v1(root.as_ref(), low, high);
            assert_eq!(ret, output);
        });
    }
}
#[cfg(test)]
mod tests_ite {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let root = [10, 5, 15, 3, 7, -1, 18];
        let low = 7;
        let high = 15;
        let output = 32;
        // Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 +
        // 15 = 32.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::range_sum_bst_v2(root, low, high);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let root = [10, 5, 15, 3, 7, 13, 18, 1, -1, 6];
        let low = 6;
        let high = 10;
        let output = 23;
        // Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::range_sum_bst_v2(root, low, high);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_ite(b: &mut test::Bencher) {
        let root = [10, 5, 15, 3, 7, 13, 18, 1, -1, 6];
        let low = 6;
        let high = 10;
        let output = 23;
        // Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        b.iter(|| {
            let root = build_binary_tree(&root);
            let ret = Solution::range_sum_bst_v2(root, low, high);
            assert_eq!(ret, output);
        });
    }
}
