// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    #[allow(unused)]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

use std::mem;

fn helper(head: Option<Box<ListNode>>, reversed: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    if let Some(mut node) = head {
        let new_head = mem::replace(&mut node.next, reversed);
        helper(new_head, Some(node))
    } else {
        reversed
    }
}

#[allow(unused)]
pub fn reverse_list(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    helper(head, None)
}

#[allow(unused)]
pub fn reverse_list_v2(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    let mut prev: Option<Box<ListNode>> = None;
    let mut curr = head;

    while let Some(mut boxed_node) = curr {
        let mut next = boxed_node.next.take();
        boxed_node.next = prev.take();
        prev = Some(boxed_node);
        curr = next.take();
    }

    prev
}
#[cfg(test)]
mod tests {
    use core::panic;

    use super::*;

    #[test]
    fn reverse_list_test() {
        let list = Box::new(ListNode::new(100));
        let ret = reverse_list(Some(list));
        match ret {
            Some(v) => {
                assert_eq!(v.val, 100);
            }
            None => panic!("not ok"),
        }
    }

    #[test]
    fn reverse_list_v2_test() {
        let list = Box::new(ListNode::new(100));
        let ret = reverse_list_v2(Some(list));
        match ret {
            Some(v) => {
                assert!(v.val == 100);
            }
            None => panic!("not ok"),
        }
    }

    #[test]
    fn reverse_list1_test() {
        let list = Box::new(ListNode {
            val: 100,
            next: Some(Box::new(ListNode::new(200))),
        });
        let ret = reverse_list(Some(list));
        match ret {
            Some(v) => {
                assert!(v.val == 200);
                assert!(v.next.unwrap().val == 100);
            }
            None => panic!("not ok"),
        }
    }

    #[test]
    fn reverse_list2_test() {
        let ret = reverse_list(Option::None);
        assert!(ret.is_none(), "not ok");
    }
}
