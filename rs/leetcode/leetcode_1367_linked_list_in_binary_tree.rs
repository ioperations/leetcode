// Given a binary tree root and a linked list with head as the first node.
// Return True if all the elements in the linked list starting from the head
// correspond to some downward path connected in the binary tree otherwise
// return False. In this context downward path means a path that starts at some
// node and goes downwards.

use super::leetcode_binary_tree::TreeNode;
use super::leetcode_linklist::ListNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn is_sub_path(
        head: &Option<Box<ListNode<i32>>>,
        root: &Option<Rc<RefCell<TreeNode<i32>>>>,
    ) -> bool {
        Self::try_check_path(head.as_deref(), root.as_deref())
    }

    #[allow(unused)]
    fn try_check_path(
        head: Option<&ListNode<i32>>,
        root: Option<&RefCell<TreeNode<i32>>>,
    ) -> bool {
        Self::check_path(head, root)
            || root.map(std::cell::RefCell::borrow).map_or(false, |root| {
                Self::try_check_path(head, root.left.as_deref())
                    || Self::try_check_path(head, root.right.as_deref())
            })
    }

    #[allow(unused)]
    fn check_path(
        head: Option<&ListNode<i32>>,
        root: Option<&RefCell<TreeNode<i32>>>,
    ) -> bool {
        head.map_or(true, |head| {
            root.map(std::cell::RefCell::borrow).map_or(false, |root| {
                root.val == head.val
                    && (Self::check_path(
                        head.next.as_deref(),
                        root.left.as_deref(),
                    ) || Self::check_path(
                        head.next.as_deref(),
                        root.right.as_deref(),
                    ))
            })
        })
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::super::leetcode_linklist::build_list_from_vec;
    use super::*;

    #[test]
    fn case1_test() {
        let null = -10_000;
        let head = [4, 2, 8];
        let root = [
            1, 4, 4, null, 2, 2, null, 1, null, 6, 8, null, null, null, null,
            1, 3,
        ]
        .iter()
        .copied()
        .map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        })
        .collect::<Vec<Option<i32>>>();
        let head = build_list_from_vec(&head);
        let root = build_binary_tree(&root);
        let output = true;
        // Explanation: Nodes in blue form a subpath in the binary Tree.
        let ret = Solution::is_sub_path(&head, &root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let null = -10_000;
        let head = [1, 4, 2, 6];
        let root = [
            1, 4, 4, null, 2, 2, null, 1, null, 6, 8, null, null, null, null,
            1, 3,
        ]
        .iter()
        .copied()
        .map(|i| {
            if i == null {
                return None;
            }
            Some(i)
        })
        .collect::<Vec<Option<i32>>>();
        let head = build_list_from_vec(&head);
        let root = build_binary_tree(&root);
        let output = true;
        let ret = Solution::is_sub_path(&head, &root);
        assert_eq!(ret, output);
    }
}
