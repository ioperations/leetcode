// Definition for singly-linked list.
use super::leetcode_linklist::ListNode;
use std::mem;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn helper<T>(
        head: Option<Box<ListNode<T>>>,
        reversed: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>> {
        if let Some(mut node) = head {
            let new_head = mem::replace(&mut node.next, reversed);
            Self::helper(new_head, Some(node))
        } else {
            reversed
        }
    }

    #[allow(unused)]
    pub fn reverse_list<T>(
        head: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>> {
        Self::helper(head, None)
    }

    #[allow(unused)]
    pub fn reverse_list_v2<T>(
        head: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>> {
        let mut prev: Option<Box<ListNode<T>>> = None;
        let mut curr = head;

        while let Some(mut boxed_node) = curr {
            let mut next = boxed_node.next.take();
            boxed_node.next = prev.take();
            prev = Some(boxed_node);
            curr = next.take();
        }

        prev
    }
}

#[cfg(test)]
mod tests {
    use core::panic;

    use super::*;

    #[test]
    fn reverse_list_test() {
        let list = Box::new(ListNode::new(100));
        let ret = Solution::reverse_list(Some(list));
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
        let ret = Solution::reverse_list_v2(Some(list));
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
        let ret = Solution::reverse_list(Some(list));
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
        let ret = Solution::reverse_list::<i32>(Option::None);
        assert!(ret.is_none(), "not ok");
    }
}
