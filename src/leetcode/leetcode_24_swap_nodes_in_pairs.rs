// Definition for singly-linked list.
use super::leetcode_linklist::ListNode;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn swap_pairs<T>(
        mut head: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>>
    where
        T: Default,
    {
        let mut list = ListNode::new(Default::default());
        let mut tail = &mut list.next;

        let mut temp = None;
        while let Some(mut node) = head.take() {
            head = node.next.take();

            match temp.take() {
                None => temp = Some(node),
                Some(temp) => {
                    node.next = Some(temp);
                    *tail = Some(node);
                    tail = &mut tail
                        .as_mut()
                        .unwrap()
                        .next // i.e. node's next
                        .as_mut()
                        .unwrap()
                        .next; // i.e. temp's next
                }
            }
        }

        *tail = temp; // in case there is a leftover
        list.next.take()
    }

    #[allow(unused)]
    pub fn swap_pairs_v2<T>(
        head: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>> {
        Self::swap_pairs_helper(head)
    }

    pub fn swap_pairs_helper<T>(
        head: Option<Box<ListNode<T>>>,
    ) -> Option<Box<ListNode<T>>> {
        let mut head = head;
        if let Some(mut first) = head.take() {
            if let Some(mut second) = first.next.take() {
                if let Some(next) = second.next.take() {
                    first.next = Self::swap_pairs_helper(Some(next));
                } else {
                    first.next = None;
                }
                second.next = Some(first);
                return Some(second);
            }
            return Some(first);
        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_linklist::{build_list_from_vec, list_into_vec};
    use super::*;

    #[test]
    fn swap_pairs_test() {
        // head = [1,2,3,4]
        let z = build_list_from_vec(&[1, 2, 3, 4]);
        let ret = Solution::swap_pairs(z);
        let v = list_into_vec(&ret);
        assert_eq!(v, vec![2, 1, 4, 3]);
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::super::leetcode_linklist::{build_list_from_vec, list_into_vec};
    use super::*;

    #[test]
    fn swap_pairs_test() {
        // head = [1,2,3,4]
        let z = build_list_from_vec(&[1, 2, 3, 4]);
        let ret = Solution::swap_pairs_v2(z);
        let v = list_into_vec(&ret);
        assert_eq!(v, vec![2, 1, 4, 3]);
    }
}
