// You are given an array of k linked-lists lists, each linked-list is sorted in
// ascending order. Merge all the linked-lists into one sorted linked-list and
// return it.
//

use super::leetcode_linklist::ListNode;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn merge_k_lists<T>(
        lists: Vec<Option<Box<ListNode<T>>>>,
    ) -> Option<Box<ListNode<T>>>
    where
        T: Ord + std::fmt::Debug + Default + PartialOrd + Copy,
    {
        use std::cmp::Reverse;
        use std::collections::BinaryHeap;

        use std::fmt::Debug;

        struct Node<T> {
            val: T,
            next: Box<ListNode<T>>,
        };
        impl<T> PartialEq for Node<T>
        where
            T: PartialEq,
        {
            fn eq(&self, other: &Self) -> bool {
                self.val == other.val
            }
        }
        impl<T> Eq for Node<T> where T: Eq {}

        impl<T> Ord for Node<T>
        where
            T: PartialOrd + Eq,
        {
            fn cmp(&self, other: &Self) -> std::cmp::Ordering {
                todo!()
            }
        }

        impl<T> PartialOrd for Node<T>
        where
            T: PartialEq + PartialOrd,
        {
            fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
                match std::cmp::Reverse(&self.val)
                    .partial_cmp(&std::cmp::Reverse(&other.val))
                {
                    Some(core::cmp::Ordering::Equal) => {
                        Some(core::cmp::Ordering::Equal)
                    }
                    ord => ord,
                }
            }
        }

        impl<T> Debug for Node<T>
        where
            T: Debug,
        {
            fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
                f.debug_struct("Node").field("val", &self.val).finish()
            }
        }

        let mut binary_heap = BinaryHeap::new();
        #[allow(clippy::manual_flatten)]
        for mut i in lists {
            if let Some(mut v) = i {
                binary_heap.push(Node {
                    val: v.val,
                    next: v,
                });
            }
        }
        let mut dummy = Box::new(ListNode::new(Default::default()));
        let mut pointer = &mut dummy;
        while !binary_heap.is_empty() {
            let mut v = binary_heap.pop().unwrap();
            if let Some(val) = v.next.next.take() {
                binary_heap.push(Node {
                    val: val.val,
                    next: val,
                });
            }
            pointer.next = Some(v.next);

            pointer = pointer.next.as_mut().unwrap();
        }
        // println!("{binary_heap:?}");

        dummy.next
    }

    #[allow(unused)]
    pub fn merge_two_lists<T>(
        list1: &mut Option<Box<ListNode<T>>>,
        list2: &mut Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>>
    where
        T: Default + PartialOrd,
    {
        let mut dummy: Box<ListNode<T>> =
            Box::new(ListNode::new(Default::default()));
        let mut pointer = &mut dummy;

        for _ in (0..) {
            match (list1.take(), list2.take()) {
                (Some(mut v1), Some(mut v2)) => {
                    if v1.val < v2.val {
                        *list1 = v1.next.take();
                        pointer.next = Some(v1);
                        *list2 = Some(v2);
                    } else {
                        *list2 = v2.next.take();
                        pointer.next = Some(v2);
                        *list1 = Some(v1);
                    }
                }
                (Some(mut v1), None) => {
                    *list1 = v1.next.take();
                    pointer.next = Some(v1);
                }
                (None, Some(mut v2)) => {
                    *list2 = v2.next.take();
                    pointer.next = Some(v2);
                }
                (None, None) => break,
            }
            pointer = pointer.next.as_mut().unwrap();
        }

        dummy.next
    }
}

#[cfg(test)]
mod test {
    use super::super::leetcode_linklist::{build_list_from_vec, list_into_vec};

    use super::*;

    #[test]
    fn case0_test() {
        let mut list1: Option<Box<ListNode<_>>> =
            build_list_from_vec(&[1, 4, 5]);
        let mut list2: Option<Box<ListNode<_>>> =
            build_list_from_vec(&[1, 3, 4]);

        let output = [1, 1, 3, 4, 4, 5];

        let ret = Solution::merge_two_lists(&mut list1, &mut list2);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output);

        // Explanation: The linked-lists are:
        // [
        //   1->4->5,
        //   1->3->4,
        // ]
        // merging them into one sorted list:
        // 1->1->2->3->4->4->5->6
    }

    #[test]
    fn case1_test() {
        let lists: Vec<_> = [vec![1, 4, 5], vec![1, 3, 4], vec![2, 6]]
            .iter()
            .map(|v| build_list_from_vec(v))
            .collect();

        let output = [1, 1, 2, 3, 4, 4, 5, 6];

        let ret = Solution::merge_k_lists(lists);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output);

        // Explanation: The linked-lists are:
        // [
        //   1->4->5,
        //   1->3->4,
        //   2->6
        // ]
        // merging them into one sorted list:
        // 1->1->2->3->4->4->5->6
    }
}
