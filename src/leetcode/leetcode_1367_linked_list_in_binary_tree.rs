// Given a binary tree root and a linked list with head as the first node.
// Return True if all the elements in the linked list starting from the head
// correspond to some downward path connected in the binary tree otherwise return False.
// In this context downward path means a path that starts at some node and goes downwards.

use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
pub struct ListNode<T> {
    pub val: T,
    pub next: Option<Box<ListNode<T>>>,
}

impl<T> ListNode<T> {
    #[inline]
    #[allow(unused)]
    fn new(val: T) -> Self {
        ListNode { next: None, val }
    }
}

// Definition for a binary tree node.
#[allow(unused)]
pub struct TreeNode<T> {
    pub val: T,
    pub left: Option<Rc<RefCell<TreeNode<T>>>>,
    pub right: Option<Rc<RefCell<TreeNode<T>>>>,
}

impl<T> TreeNode<T> {
    #[inline]
    #[allow(unused)]
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
    pub fn is_sub_path(
        head: &Option<Box<ListNode<i32>>>,
        root: &Option<Rc<RefCell<TreeNode<i32>>>>,
    ) -> bool {
        Self::try_check_path(head.as_deref(), root.as_deref())
    }

    #[allow(unused)]
    fn try_check_path(head: Option<&ListNode<i32>>, root: Option<&RefCell<TreeNode<i32>>>) -> bool {
        Self::check_path(head, root)
            || root.map(std::cell::RefCell::borrow).map_or(false, |root| {
                Self::try_check_path(head, root.left.as_deref())
                    || Self::try_check_path(head, root.right.as_deref())
            })
    }

    #[allow(unused)]
    fn check_path(head: Option<&ListNode<i32>>, root: Option<&RefCell<TreeNode<i32>>>) -> bool {
        head.map_or(true, |head| {
            root.map(std::cell::RefCell::borrow).map_or(false, |root| {
                root.val == head.val
                    && (Self::check_path(head.next.as_deref(), root.left.as_deref())
                        || Self::check_path(head.next.as_deref(), root.right.as_deref()))
            })
        })
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

    #[allow(unused)]
    fn build_link_list<T>(node: &[T]) -> Option<Box<ListNode<T>>>
    where
        T: Copy,
    {
        if node.is_empty() {
            return None;
        }
        let mut node = node.iter().copied().rev().collect::<Vec<T>>();
        let mut ret: ListNode<T> = ListNode::new(node[0]);

        for i in node {
            let mut thisnode = Box::new(ListNode {
                val: i,
                next: ret.next.take(),
            });
            ret.next = Some(thisnode);
        }
        ret.next
    }

    #[test]
    fn case1_test() {
        let null = -10_000;
        let head = [4, 2, 8];
        let root = [
            1, 4, 4, null, 2, 2, null, 1, null, 6, 8, null, null, null, null, 1, 3,
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
        let head = build_link_list(&head);
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
            1, 4, 4, null, 2, 2, null, 1, null, 6, 8, null, null, null, null, 1, 3,
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
        let head = build_link_list(&head);
        let root = build_binary_tree(&root);
        let output = true;
        let ret = Solution::is_sub_path(&head, &root);
        assert_eq!(ret, output);
    }
}
