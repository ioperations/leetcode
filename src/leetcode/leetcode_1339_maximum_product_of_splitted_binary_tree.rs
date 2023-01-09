/*Given the root of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.

Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.

Note that you need to maximize the answer before taking the mod and not after taking it.

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
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_product(root: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        /*
         * The number of nodes in the tree is in the range [2, 5 * 104].
         * 1 <= Node.val <= 104
         */
        let mod_math = 1_000_000_000 + 7;
        let sum = Self::get_sum(root);
        let mut max_product: i64 = 0;
        Self::get_max_product(root, &mut max_product, sum);
        (max_product % mod_math) as i32
    }
    fn get_max_product(
        node: &Option<Rc<RefCell<TreeNode<i32>>>>,
        max_product: &mut i64,
        sum: i64,
    ) -> i64 {
        if let Some(n) = node {
            let left = Self::get_max_product(&n.borrow().left, max_product, sum);
            let right = Self::get_max_product(&n.borrow().right, max_product, sum);
            let cur_sum = left + right + n.borrow().val as i64;
            let product = cur_sum * (sum - cur_sum);
            if product > *max_product {
                *max_product = product;
            }
            cur_sum
        } else {
            0
        }
    }
    fn get_sum(node: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i64 {
        if let Some(n) = node {
            let left = Self::get_sum(&n.borrow().left);
            let right = Self::get_sum(&n.borrow().right);
            left + right + n.borrow().val as i64
        } else {
            0
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
mod tests {

    use super::*;

    #[test]
    fn case1_test() {
        let root = [1, 2, 3, 4, 5, 6].map(Some);
        let root = build_binary_tree(&root);
        let output = 110;
        let ret = Solution::max_product(&root);
        assert_eq!(ret, output);
        // Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
    }

    #[test]
    fn case2_test() {
        let null = -1;
        let root = [1, null, 2, 3, 4, null, null, 5, 6].map(|i| {
            if i == -1 {
                return None;
            }
            Some(i)
        });
        let root = build_binary_tree(&root);
        let output = 90;
        let ret = Solution::max_product(&root);
        assert_eq!(ret, output);
        // Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)
    }

    #[allow(unused)]
    #[derive(Debug)]
    struct Testfiled {
        pub val: i32,
    }

    impl Testfiled {
        #[allow(unused)]
        fn new(i: i32) -> Self {
            Self { val: i }
        }
    }

    #[test]
    fn casessss3_test() {
        let z = (0..)
            .map(|i| Rc::new(RefCell::new(Box::new(Testfiled::new(i)))))
            .take(20)
            .collect::<Vec<_>>();

        println!(
            "{:#?}",
            z.iter()
                .zip(z.iter().skip(2))
                .map(|(i, j)| {
                    if j.borrow().val == 4 {
                        j.borrow_mut().val = 5;
                    }
                    (i, j)
                })
                .take(4)
                .collect::<Vec<_>>()
        );
    }
}
