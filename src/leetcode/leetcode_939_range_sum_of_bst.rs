// Given the root node of a binary search tree and two integers low and high,
// return the sum of values of all nodes with a value in the inclusive range [low, high].

// Definition for a binary tree node.
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
use std::rc::Rc;
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn range_sum_bst(root: Option<Rc<RefCell<TreeNode<i32>>>>, low: i32, high: i32) -> i32 {
        match root {
            None => 0,
            Some(node) => {
                let node = node.borrow();
                if high < node.val {
                    Self::range_sum_bst(node.left.clone(), low, high)
                } else if node.val < low {
                    Self::range_sum_bst(node.right.clone(), low, high)
                } else {
                    Self::range_sum_bst(node.left.clone(), low, high)
                        + node.val
                        + Self::range_sum_bst(node.right.clone(), low, high)
                }
            }
        }
    }
    #[allow(unused)]
    pub fn range_sum_bst_v2(root: Option<Rc<RefCell<TreeNode<i32>>>>, low: i32, high: i32) -> i32 {
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
    pub fn range_sum_bst_v1(root: Option<Rc<RefCell<TreeNode<i32>>>>, low: i32, high: i32) -> i32 {
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
                        + Self::range_sum_bst_v1(head.borrow_mut().right.take(), low, high);
                } else if head_value >= high {
                    return extra
                        + Self::range_sum_bst_v1(head.borrow_mut().left.take(), low, high);
                }
                let left = Self::range_sum_bst_v1(head.borrow_mut().left.take(), low, high);
                let right = Self::range_sum_bst_v1(head.borrow_mut().right.take(), low, high);
                left + right + head_value
            }
            None => 0,
        }
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
mod tests_rec {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let root = [10, 5, 15, 3, 7, -1, 18];
        let low = 7;
        let high = 15;
        let output = 32;
        // Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
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
        let ret = Solution::range_sum_bst(root, low, high);
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
        let ret = Solution::range_sum_bst(root, low, high);
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
            let ret = Solution::range_sum_bst(root, low, high);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_v1 {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let root = [10, 5, 15, 3, 7, -1, 18];
        let low = 7;
        let high = 15;
        let output = 32;
        // Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
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
        let ret = Solution::range_sum_bst_v1(root, low, high);
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
        let ret = Solution::range_sum_bst_v1(root, low, high);
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
            let ret = Solution::range_sum_bst_v1(root, low, high);
            assert_eq!(ret, output);
        });
    }
}
#[cfg(test)]
mod tests_ite {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let root = [10, 5, 15, 3, 7, -1, 18];
        let low = 7;
        let high = 15;
        let output = 32;
        // Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
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
