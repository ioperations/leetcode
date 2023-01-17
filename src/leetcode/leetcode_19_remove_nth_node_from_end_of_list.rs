// Given the head of a linked list, remove the nth node from the end of the list and return its head.

use super::leetcode_linklist::ListNode;
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    #[allow(clippy::borrow_as_ptr)]
    pub fn remove_nth_from_end<T>(
        head: Option<Box<ListNode<T>>>,
        n: i32,
    ) -> Option<Box<ListNode<T>>>
    where
        T: Copy + Default,
    {
        let mut dummy = Box::new(ListNode::<T> {
            val: Default::default(),
            next: head,
        });

        unsafe {
            let mut slow = &mut dummy as *mut Box<ListNode<T>>;

            // miri 报错 error: Undefined Behavior
            // let mut fast = &mut dummy as *mut Box<ListNode>;
            let mut fast = &dummy as *const Box<ListNode<T>>;

            for _ in 0..n {
                // fast = (*fast).next.as_mut().unwrap();
                fast = (*fast).next.as_ref().unwrap();
            }

            while (*fast).next.is_some() {
                // fast = (*fast).next.as_mut().unwrap();
                fast = (*fast).next.as_ref().unwrap();

                slow = (*slow).next.as_mut().unwrap();
            }
            (*slow).next = (*slow).next.take().unwrap().next;
        }
        dummy.next
    }

    #[allow(unused)]
    #[allow(clippy::borrow_as_ptr)]
    pub fn remove_middle_node<T>(head: Option<Box<ListNode<T>>>) -> Option<Box<ListNode<T>>>
    where
        T: Copy + Default,
    {
        let mut dummy = Box::new(ListNode::<T> {
            val: Default::default(),
            next: head,
        });

        unsafe {
            let mut slow = &mut dummy as *mut Box<ListNode<T>>;
            let mut fast = &dummy as *const Box<ListNode<T>>;

            while (*fast).next.is_some() {
                fast = (*fast).next.as_ref().unwrap();
                if (*fast).next.is_some() {
                    fast = (*fast).next.as_ref().unwrap();
                } else {
                    break;
                }
                slow = (*slow).next.as_mut().unwrap();
            }
            (*slow).next = (*slow).next.take().unwrap().next;
        }
        dummy.next
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_linklist::{build_list_from_vec, list_into_vec};
    use super::*;

    #[test]
    fn case1_test() {
        let head = [1, 2, 3, 4, 5];
        let n = 2;
        let output = [1, 2, 3, 5];
        let root = build_list_from_vec(&head);
        let root = Solution::remove_nth_from_end(root, n);
        let ret = list_into_vec(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let head = [1];
        let n = 1;
        let output = [];
        let root = build_list_from_vec(&head);
        let root = Solution::remove_nth_from_end(root, n);
        let ret = list_into_vec(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let head = [1, 2];
        let n = 1;
        let output = [1];
        let root = build_list_from_vec(&head);
        let root = Solution::remove_nth_from_end(root, n);
        let ret = list_into_vec(&root);
        assert_eq!(ret, output);
    }
}

#[cfg(test)]
mod tests_middle_node {
    use super::super::leetcode_linklist::{build_list_from_vec, list_into_vec};
    use super::*;

    #[test]
    fn case1_test() {
        let head = [1, 2, 3, 4, 5];
        let output = [1, 2, 4, 5];
        let root = build_list_from_vec(&head);
        let root = Solution::remove_middle_node(root);
        let ret = list_into_vec(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let head = [1];
        let output = [];
        let root = build_list_from_vec(&head);
        let root = Solution::remove_middle_node(root);
        let ret = list_into_vec(&root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let head = [1, 2];
        let output = [1];
        let root = build_list_from_vec(&head);
        let root = Solution::remove_middle_node(root);
        let ret = list_into_vec(&root);
        assert_eq!(ret, output);
    }
}
