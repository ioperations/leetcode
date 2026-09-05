use super::leetcode_linklist::ListNode;

// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
//
// impl ListNode {
//   #[inline]
//   fn new(val: i32) -> Self {
//     ListNode {
//       next: None,
//       val
//     }
//   }
// }
#[allow(unused)]
struct Solution;

use std::collections::VecDeque;

impl Solution {
    #[allow(unused)]
    pub fn partition(
        head: Option<Box<ListNode<i32>>>,
        x: i32,
    ) -> Option<Box<ListNode<i32>>> {
        let mut less_dummy = Box::new(ListNode::new(0));
        let mut less_tail = &mut *less_dummy;
        let mut more_dummy = Box::new(ListNode::new(0));
        let mut more_tail = &mut *more_dummy;
        let mut current = head;

        while let Some(mut node) = current.take() {
            current = node.next.take();
            if node.val < x {
                less_tail.next = Some(node);
                less_tail = less_tail.next.as_mut().unwrap();
            } else {
                more_tail.next = Some(node);
                more_tail = more_tail.next.as_mut().unwrap();
            }
        }
        less_tail.next = more_dummy.next;
        less_dummy.next
    }
}

#[cfg(test)]
mod test {
    use super::super::leetcode_linklist::build_list_from_vec;
    use super::super::leetcode_linklist::list_into_vec;
    use super::*;

    #[test]
    fn case1_test() {
        let head = [1, 4, 3, 2, 5, 2];
        let x = 3;
        let root = build_list_from_vec(&head);
        let ret = Solution::partition(root, x);
        let ret = list_into_vec(&ret);
        let output: Vec<i32> = [1, 2, 2, 4, 3, 5].into();
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let head = [2, 1];
        let x = 2;
        let root = build_list_from_vec(&head);
        let ret = Solution::partition(root, x);
        let ret = list_into_vec(&ret);
        let output: Vec<i32> = [1, 2].into();
        assert_eq!(output, ret);
    }
}
