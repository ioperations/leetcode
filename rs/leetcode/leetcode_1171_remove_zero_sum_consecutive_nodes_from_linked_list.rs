// Given the head of a linked list, we repeatedly delete consecutive sequences
// of nodes that sum to 0 until there are no such sequences. After doing so,
// return the head of the final linked list.  You may return any such answer.
//
// (Note that in the examples below, all sequences are serializations of
// ListNode objects.)

use super::leetcode_linklist::{build_list_from_vec, list_into_vec, ListNode};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn remove_zero_sum_sublists(
        head: &Option<Box<ListNode<i32>>>,
    ) -> Option<Box<ListNode<i32>>> {
        use std::collections::HashMap;

        let mut v = list_into_vec(head);
        let mut partial_sum = vec![0; v.len() + 1];

        let mut map = HashMap::<i32, i32>::new();
        let mut sum = 0;
        map.insert(0, 1);
        for i in 0..v.len() {
            sum += v[i];
            partial_sum[i + 1] = sum;
            *map.entry(sum).or_default() += 1;
        }

        for (&key, &val) in &map {
            if val > 1 {
                let mut lo = i32::MIN;
                let mut hi = i32::MAX;
                for (i, &v) in partial_sum.iter().enumerate() {
                    if v == key {
                        lo = i as i32;
                        break;
                    }
                }
                for i in (0..partial_sum.len()).rev() {
                    if partial_sum[i] == key {
                        hi = i as i32;
                        break;
                    }
                }
                // println!("sum = {}, lo = {}, hi = {}", key, lo, hi);
                if lo > i32::MIN && hi < i32::MAX && hi > lo {
                    for j in lo + 1..=hi {
                        partial_sum[j as usize] = i32::MAX;
                    }
                }
            }
        }
        //        println!("{:?}", partial_sum);
        let mut ans = vec![];
        for i in 1..partial_sum.len() {
            if partial_sum[i] != i32::MAX {
                ans.push(v[i - 1]);
            }
        }
        build_list_from_vec(&ans)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use super::{build_list_from_vec, list_into_vec};

    #[test]
    fn case1_test() {
        let head = [1, 2, -3, 3, 1];
        let output1 = vec![3, 1];
        let output2 = vec![1, 2, 1];
        let head = build_list_from_vec(&head);
        let ret = Solution::remove_zero_sum_sublists(&head);
        let ret = list_into_vec(&ret);
        assert!(ret == output1 || ret == output2);
        // let Note: The answer [1,2,1] would also be accepted.;
    }

    #[test]
    fn case2_test() {
        let head = [1, 2, 3, -3, 4];
        let output1 = vec![1, 2, 4];
        let head = build_list_from_vec(&head);
        let ret = Solution::remove_zero_sum_sublists(&head);
        let ret = list_into_vec(&ret);
        assert!(ret == output1);
        // let Note: The answer [1,2,1] would also be accepted.;
    }

    #[test]
    fn case3_test() {
        let head = [1, 2, 3, -3, -2];
        let output1 = vec![1];
        let head = build_list_from_vec(&head);
        let ret = Solution::remove_zero_sum_sublists(&head);
        let ret = list_into_vec(&ret);
        assert!(ret == output1);
        // let Note: The answer [1,2,1] would also be accepted.;
    }
}
