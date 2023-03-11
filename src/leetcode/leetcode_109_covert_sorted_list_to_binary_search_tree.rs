// Given the head of a singly linked list where elements are sorted in ascending
// order, convert it to a height-balanced
// binary search tree.

// Height-Balanced
// A height-balanced binary tree is a binary tree in which the depth of the two
// subtrees of every node never differs by more than one.

use super::leetcode_binary_tree::TreeNode;
use super::leetcode_linklist::ListNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn sorted_list_to_bst<T>(
        head: Option<Box<ListNode<T>>>,
    ) -> Option<Rc<RefCell<TreeNode<T>>>>
    where
        T: Copy,
    {
        // The number of nodes in head is in the range [0, 2 * 104].
        // -105 <= Node.val <= 105

        fn build<const T: bool, F>(v: &[F]) -> Option<Rc<RefCell<TreeNode<F>>>>
        where
            F: Copy,
        {
            let len = v.len();
            if len == 0 {
                return None;
            }
            if T {
                // left tree
                let mut ret = Rc::new(RefCell::new(TreeNode::new(v[0])));

                for &i in v.iter().take(len).skip(1) {
                    let sub = Rc::new(RefCell::new(TreeNode::new(i)));
                    sub.borrow_mut().left = Some(ret);
                    ret = sub;
                }
                Some(ret)
            } else {
                let mut ret = Rc::new(RefCell::new(TreeNode::new(v[0])));
                let sub = build::<false, F>(&v[1..]);
                ret.borrow_mut().right = sub;
                Some(ret)
            }
        };

        let mut head = head;
        let mut vec = Vec::new();
        while let Some(v) = head.take() {
            vec.push(v.val);
            head = v.next;
        }
        let len = vec.len();
        if len == 0 {
            return None;
        }

        let i = len / 2;
        let left = build::<true, T>(&vec[0..i]);
        let right = build::<false, T>(&vec[i + 1..]);
        let head = Rc::new(RefCell::new(TreeNode::new(vec[i])));
        head.borrow_mut().left = left;
        head.borrow_mut().right = right;
        Some(head)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let null = -100;
        let head = [-10, -3, 0, 5, 9];
        let output = [0, -3, 5, -10, null, null, 9].map(|i| {
            if i == null {
                None
            } else {
                Some(i)
            }
        });
        let node = build_list_from_vec(&head);
        let ret = Solution::sorted_list_to_bst(node);
        let output2 = [0, -3, 5, -10, 9].map(Some);
        expect_binary_tree(&output2, &ret);
        let ret = flatten_binary_tree(ret);
        assert_eq!(ret, output);
        // Explanation: One possible answer is [0,-3,9,-10,null,5], which
        // represents the shown height balanced BST.
    }

    #[test]
    fn case2_test() {
        let null = -100;
        let head = [];
        let output: [Option<i32>; 0] =
            [].map(|i| if i == null { None } else { Some(i) });
        let node = build_list_from_vec(&head);
        let ret = Solution::sorted_list_to_bst(node);
        expect_binary_tree(&output, &ret);
    }
}
