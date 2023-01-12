/*
You are given the head of a linked list containing unique integer values and an integer array nums that is a subset of the linked list values.
Return the number of connected components in nums where two values are connected if they appear consecutively in the linked list.*/

use std::collections::HashSet;
// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode<T> {
    pub val: T,
    pub next: Option<Box<ListNode<T>>>,
}

impl<T> ListNode<T> {
    #[inline]
    fn new(val: T) -> Self {
        ListNode { next: None, val }
    }
}

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn num_components(head: &Option<Box<ListNode<i32>>>, nums: &[i32]) -> i32 {
        let nums: HashSet<_> = nums.iter().collect();
        (0..)
            .scan(head, |node, _| {
                node.as_deref().map(|ListNode { val, next }| {
                    *node = next;
                    nums.contains(val)
                })
            })
            .take(1000)
            .fuse()
            .fold((0, false), |(cnt, pre), b| (i32::from(b && !pre) + cnt, b))
            .0
    }
}

#[allow(unused)]
fn build_list_from_vec(node: &[i32]) -> Option<Box<ListNode<i32>>> {
    if node.is_empty() {
        return None;
    }
    let mut ret = ListNode::new(0);

    for i in node.iter().rev() {
        let mut thisnode = Box::new(ListNode {
            val: *i,
            next: ret.next.take(),
        });
        ret.next = Some(thisnode);
    }
    ret.next
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let head = [0, 1, 2, 3];
        let nums = [0, 1, 3];
        let output = 2;
        // Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
        let link_list = build_list_from_vec(&head);
        let ret = Solution::num_components(&link_list, &nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let head = [0, 1, 2, 3, 4];
        let nums = [0, 3, 1, 4];
        let output = 2;
        // 0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
        let link_list = build_list_from_vec(&head);

        let ret = Solution::num_components(&link_list, &nums);
        assert_eq!(ret, output);
    }
}
