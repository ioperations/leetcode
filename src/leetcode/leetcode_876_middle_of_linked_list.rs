// Given the head of a singly linked list, return the middle node of the linked list.
// If there are two middle nodes, return the second middle node.

// Definition for singly-linked list.

#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn middle_node(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let (mut iter, mut iter_slow) = (head.clone(), head);
        let mut count = 0;
        while let Some(node) = iter {
            iter = node.next;

            if count == 1 {
                if let Some(slow_node) = iter_slow {
                    iter_slow = slow_node.next;
                    count = 0;
                }
            } else {
                count += 1;
            }
        }
        iter_slow
    }

    #[allow(unused)]
    pub fn middle_node_v2(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        head.as_ref()?;
        let head = head.unwrap();
        let mut fast_p = &head;
        let mut slow_p = &head;
        let mut jump = 0;
        loop {
            match fast_p.next {
                None => break,
                Some(ref next_node) => {
                    jump += 1;
                    if jump % 2 == 0 {
                        slow_p = slow_p.next.as_ref().unwrap();
                    }
                    fast_p = next_node;
                }
            }
        }
        if jump % 2 == 1 {
            slow_p = slow_p.next.as_ref().unwrap();
        }

        // because the method's signature is intended 'move' the original list in and 'move'
        // the middle of it out, which is not possible by Rust (because the ownership rules don't
        // allow it), so we have to create a new list.
        let mut new_head = ListNode::new(slow_p.val);
        Solution::copy_values(&mut new_head, slow_p);
        Some(Box::new(new_head))
    }

    #[allow(unused)]
    fn copy_values(new_head: &mut ListNode, old_head: &ListNode) {
        let mut old_head = old_head;
        let mut new_tail = new_head;
        loop {
            match old_head.next {
                None => break,
                Some(ref next_node) => {
                    let mut new_node = ListNode::new(next_node.val);
                    new_tail.next = Some(Box::new(new_node));

                    // the '{}' around 'new_tail' is used to move (but not borrow) it into a temporary
                    // variable, so we are free to set new value to the original variable, without causing
                    // an "already borrowed" error.
                    // see: https://stackoverflow.com/questions/37986640/cannot-obtain-a-mutable-reference-when-iterating-a-recursive-structure-cannot-b
                    new_tail = { new_tail }.next.as_mut().unwrap();

                    old_head = next_node;
                }
            }
        }
    }
}
#[allow(unused)]
fn list_into_vec(head: &Option<Box<ListNode>>) -> Vec<i32> {
    if let Some(h) = head {
        let mut v = list_into_vec(&h.next);
        v.insert(0, h.val);
        return v;
    }

    vec![]
}

#[allow(unused)]
fn build_list_from_vec(node: &[i32]) -> Option<Box<ListNode>> {
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
    extern crate test;

    #[test]
    fn case1_test() {
        let head = vec![1, 2, 3, 4, 5];
        let output = vec![3, 4, 5];
        let head = build_list_from_vec(&head);
        let ret = Solution::middle_node(head);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output);
        // Explanation: The middle node of the list is node 3.
    }

    #[test]
    fn case2_test() {
        let head = vec![1, 2, 3, 4, 5, 6];
        let output = vec![4, 5, 6];
        let head = build_list_from_vec(&head);
        let ret = Solution::middle_node(head);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output);
        // Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
    }

    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        let head = vec![1, 2, 3, 4, 5, 6];
        b.iter(|| {
            let head = build_list_from_vec(&head);
            Solution::middle_node(head);
        });
    }
}

#[cfg(test)]
mod testsv2 {
    use super::{build_list_from_vec, list_into_vec, Solution};
    extern crate test;

    #[test]
    fn case1_test() {
        let head = vec![1, 2, 3, 4, 5];
        let output = vec![3, 4, 5];
        let head = build_list_from_vec(&head);
        let ret = Solution::middle_node_v2(head);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output);
        // Explanation: The middle node of the list is node 3.
    }

    #[test]
    fn case2_test() {
        let head = vec![1, 2, 3, 4, 5, 6];
        let output = vec![4, 5, 6];
        let head = build_list_from_vec(&head);
        let ret = Solution::middle_node_v2(head);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output);
        // Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
    }

    #[bench]
    fn bench_v2(b: &mut test::Bencher) {
        let head = vec![1, 2, 3, 4, 5, 6];
        b.iter(|| {
            let head = build_list_from_vec(&head);
            Solution::middle_node_v2(head);
        });
    }
}
