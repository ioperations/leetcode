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
struct Solution;
use std::collections::HashMap;
impl Solution {
    #[allow(unused)]
    pub fn remove_zero_sum_sublists(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut head = head;
        let mut data = vec![];
        let (mut index, mut sum) = (0, 0);
        let mut from_index: HashMap<i32, i32> = HashMap::new();
        let mut to_index = HashMap::new();

        to_index.insert(0, -1);
        while let Some(mut node) = head {
            head = node.next.take();
            sum += node.val;
            node.next = None;
            data.push(node);

            if let Some(i) = to_index.get(&sum) {
                data.pop();
                let (start, end) = (*i as usize + 1, index as usize);
                for k in start..end {
                    if let Some(a) = from_index.get(&(k as i32)) {
                        to_index.remove(a);
                        from_index.remove(&(k as i32));
                        data.pop();
                    }
                }
                continue;
            }

            to_index.insert(sum, index);
            from_index.insert(index, sum);
            index += 1;
        }

        let mut ret = None;
        let mut tail = &mut ret;
        for p in data {
            tail = &mut tail.insert(p).next;
        }

        ret
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
    fn build_list_iter(node: Vec<i32>) -> Option<Box<ListNode>> {
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
        let head = build_list_iter(head.into());
        let ret = Solution::remove_zero_sum_sublists(head);
        let ret = convert_list_to_vec_iter(ret);
        assert!(ret == output1 || ret == output2);
        // let Note: The answer [1,2,1] would also be accepted.;
    }

    #[test]
    fn case2_test() {
        let head = [1, 2, 3, -3, 4];
        let output1 = vec![1, 2, 4];
        let head = build_list_iter(head.into());
        let ret = Solution::remove_zero_sum_sublists(head);
        let ret = convert_list_to_vec_iter(ret);
        assert!(ret == output1);
        // let Note: The answer [1,2,1] would also be accepted.;
    }

    #[test]
    fn case3_test() {
        let head = [1, 2, 3, -3, -2];
        let output1 = vec![1];
        let head = build_list_iter(head.into());
        let ret = Solution::remove_zero_sum_sublists(head);
        let ret = convert_list_to_vec_iter(ret);
        assert!(ret == output1);
        // let Note: The answer [1,2,1] would also be accepted.;
    }
}
