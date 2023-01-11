/*Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
After doing so, return the head of the final linked list.  You may return any such answer.


(Note that in the examples below, all sequences are serializations of ListNode objects.)*/

// Definition for singly-linked list.
#[allow(unused)]
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[allow(unused)]
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

#[allow(unused)]
pub fn from_vec(v: &[i32]) -> Option<Box<ListNode>> {
    let mut head = None;
    let n = v.len();
    for i in (0..n).rev() {
        let x = v[i];
        head = Some(Box::new(ListNode { val: x, next: head }));
    }
    head
}

#[allow(unused)]
pub fn to_vec(head: &Option<Box<ListNode>>) -> Vec<i32> {
    let mut ans = vec![];
    let mut p = head;
    while let Some(node) = p {
        ans.push(node.val);
        p = &node.next;
    }
    ans
}

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn remove_zero_sum_sublists(head: &Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        use std::collections::HashMap;

        let mut v = to_vec(head);
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
                let mut lo = std::i32::MIN;
                let mut hi = std::i32::MAX;
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
                //                println!("sum = {}, lo = {}, hi = {}", key, lo, hi);
                if lo > std::i32::MIN && hi < std::i32::MAX && hi > lo {
                    for j in lo + 1..=hi {
                        partial_sum[j as usize] = std::i32::MAX;
                    }
                }
            }
        }
        //        println!("{:?}", partial_sum);
        let mut ans = vec![];
        for i in 1..partial_sum.len() {
            if partial_sum[i] != std::i32::MAX {
                ans.push(v[i - 1]);
            }
        }
        from_vec(&ans)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// 将自定义链表转换成数组
    #[allow(unused)]
    fn convert_list_to_vec_iter(lists: Option<Box<ListNode>>) -> Vec<i32> {
        let mut lists = lists;
        let mut ret = vec![];
        while let Some(node) = lists {
            ret.push(node.val);
            lists = node.next;
        }
        ret
    }

    #[allow(unused)]
    fn build_list_iter(node: &[i32]) -> Option<Box<ListNode>> {
        if node.is_empty() {
            return None;
        }
        let mut node = node.iter().copied().rev().collect::<Vec<i32>>();
        let mut ret: ListNode = ListNode::new(0);

        for i in node {
            let mut thisnode = Box::new(ListNode::new(i));
            thisnode.next = ret.next.take();
            ret.next = Some(thisnode);
        }
        ret.next
    }

    #[test]
    fn case1_test() {
        let head = [1, 2, -3, 3, 1];
        let output1 = vec![3, 1];
        let output2 = vec![1, 2, 1];
        let head = build_list_iter(&head);
        let ret = Solution::remove_zero_sum_sublists(&head);
        let ret = convert_list_to_vec_iter(ret);
        assert!(ret == output1 || ret == output2);
        // let Note: The answer [1,2,1] would also be accepted.;
    }

    #[test]
    fn case2_test() {
        let head = [1, 2, 3, -3, 4];
        let output1 = vec![1, 2, 4];
        let head = build_list_iter(&head);
        let ret = Solution::remove_zero_sum_sublists(&head);
        let ret = convert_list_to_vec_iter(ret);
        assert!(ret == output1);
        // let Note: The answer [1,2,1] would also be accepted.;
    }

    #[test]
    fn case3_test() {
        let head = [1, 2, 3, -3, -2];
        let output1 = vec![1];
        let head = build_list_iter(&head);
        let ret = Solution::remove_zero_sum_sublists(&head);
        let ret = convert_list_to_vec_iter(ret);
        assert!(ret == output1);
        // let Note: The answer [1,2,1] would also be accepted.;
    }
}
