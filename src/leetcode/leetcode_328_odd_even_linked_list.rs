// Given the head of a singly linked list,
// group all the nodes with odd indices together followed by the nodes with even
// indices, and return the reordered list.
// The first node is considered odd, and the second node is even, and so on.
// Note that the relative order inside both the even and odd groups should
// remain as it was in the input. You must solve the problem in O(1) extra space
// complexity and O(n) time complexity.

use super::leetcode_linklist::ListNode;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn odd_even_list_dummy<T>(
        head: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>>
    where
        T: Default,
    {
        let mut head = head;
        let mut odd_dummy_head = ListNode::new(Default::default());
        let mut even_dummy_head = ListNode::new(Default::default());
        let mut odd_cur = &mut odd_dummy_head;
        let mut even_cur = &mut even_dummy_head;

        let mut is_even = false;
        while let Some(mut node) = head {
            head = std::mem::replace(&mut node.next, None);
            if is_even {
                even_cur.next = Some(node);
                even_cur = even_cur.next.as_mut().unwrap();
            } else {
                odd_cur.next = Some(node);
                odd_cur = odd_cur.next.as_mut().unwrap();
            }
            is_even = !is_even;
        }

        odd_cur.next = even_dummy_head.next;
        odd_dummy_head.next
    }

    #[allow(unused)]
    pub fn odd_even_list<T>(
        head: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>> {
        // establish Even and Odd lists
        let mut odd_head = head?;
        let mut odd_tail = &mut odd_head.next;
        let Some(mut even_head)  = odd_tail.take() else {
            return Some(odd_head);
        };
        let mut even_tail = &mut even_head.next;

        // iterate over remaining nodes and alternate appends to Even and Odd
        let mut rest = even_tail.take();
        let mut even = false;
        while let Some(mut node) = rest {
            rest = node.next.take();
            if even {
                *even_tail = Some(node);
                even_tail =
                    even_tail.as_mut().map(|node| &mut node.next).unwrap();
            } else {
                *odd_tail = Some(node);
                odd_tail =
                    odd_tail.as_mut().map(|node| &mut node.next).unwrap();
            }
            even = !even;
        }
        // Place Even at the end of Odd
        *odd_tail = Some(even_head);

        Some(odd_head)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    extern crate test;
    use super::super::leetcode_linklist::{build_list_from_vec, list_into_vec};

    #[test]
    fn case1_test() {
        let head = [1, 2, 3, 4, 5];
        let output = [1, 3, 5, 2, 4];
        let list = build_list_from_vec(&head);
        let ret = Solution::odd_even_list(list);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output.to_vec());
    }

    #[test]
    fn case2_test() {
        let head = [2, 1, 3, 5, 6, 4, 7];
        let output = [2, 3, 6, 7, 1, 5, 4];
        let list = build_list_from_vec(&head);
        let ret = Solution::odd_even_list(list);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output.to_vec());
    }

    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        let head = [2, 1, 3, 5, 6, 4, 7];
        let output = [2, 3, 6, 7, 1, 5, 4];
        b.iter(|| {
            let list = build_list_from_vec(&head);
            let ret = Solution::odd_even_list(list);
            let ret = list_into_vec(&ret);
            assert_eq!(ret, output.to_vec());
        });
    }
}

#[cfg(test)]
mod tests_dummy {
    use super::*;
    extern crate test;
    use super::super::leetcode_linklist::{build_list_from_vec, list_into_vec};

    #[test]
    fn case1_test() {
        let head = [1, 2, 3, 4, 5];
        let output = [1, 3, 5, 2, 4];
        let list = build_list_from_vec(&head);
        let ret = Solution::odd_even_list_dummy(list);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output.to_vec());
    }

    #[test]
    fn case2_test() {
        let head = [2, 1, 3, 5, 6, 4, 7];
        let output = [2, 3, 6, 7, 1, 5, 4];
        let list = build_list_from_vec(&head);
        let ret = Solution::odd_even_list_dummy(list);
        let ret = list_into_vec(&ret);
        assert_eq!(ret, output.to_vec());
    }

    #[bench]
    fn bench_dummy(b: &mut test::Bencher) {
        let head = [2, 1, 3, 5, 6, 4, 7];
        let output = [2, 3, 6, 7, 1, 5, 4];
        b.iter(|| {
            let list = build_list_from_vec(&head);
            let ret = Solution::odd_even_list_dummy(list);
            let ret = list_into_vec(&ret);
            assert_eq!(ret, output.to_vec());
        });
    }
}
