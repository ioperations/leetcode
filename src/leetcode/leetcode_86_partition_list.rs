use super::leetcode_linklist::*;

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
        let mut queue_less = VecDeque::new();
        let mut queue_more = VecDeque::new();
        let mut head = head;

        while let Some(mut v) = head.take() {
            head = v.next.take();
            if v.val < x {
                queue_less.push_back(v);
            } else {
                queue_more.push_back(v);
            }
        }
        let mut dummy = Box::new(ListNode::new(0));
        let mut p = &mut dummy;
        while let Some(v) = queue_less.pop_front() {
            p.next = Some(v);
            p = p.next.as_mut().unwrap();
        }
        while let Some(v) = queue_more.pop_front() {
            p.next = Some(v);
            p = p.next.as_mut().unwrap();
        }
        dummy.next
    }
}

#[cfg(test)]
mod test {
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
