/*You are given the head of a linked list with n nodes.↳

For each node in the list, find the value of the next greater node. That is, for each node, find the value of the first node that is next to it and has a strictly larger value than it.
Return an integer array answer where answer[i] is the value of the next greater node of the ith node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.*/

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
#[allow(unused)]
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

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn next_larger_nodes(head: Option<Box<ListNode>>) -> Vec<i32> {
        let mut stack = Vec::with_capacity(16);
        let mut result = Vec::with_capacity(256); // allocate large enough initial buffer in order to reduce reallocations

        let mut head = head;
        let mut idx = 0; // used to track the position in the solution array
        while let Some(mut node) = head.take() {
            head = node.next.take();

            while let Some(&(top, pos)) = stack.last() {
                // the classical monotonic stack algorithm, with the addition that we propagate both the value and the index
                if top >= node.val {
                    break;
                }

                stack.pop();
                result[pos] = node.val; //use the propagated position to update the solutions aarray
            }

            stack.push((node.val, idx)); // push both the value and the position at the solution array, otherwise we won't know which element to update
            result.push(0); // expand the solution array with one element on every new node
            idx += 1; // do not forget to update the index ;)
        }

        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[allow(unused)]
    fn build_list_from_vec(node: &[i32]) -> Option<Box<ListNode>> {
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
        let head = [2, 1, 5];
        let output: Vec<i32> = [5, 5, 0].into();
        let head = build_list_from_vec(&head);
        let ret = Solution::next_larger_nodes(head);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let head = [2, 7, 4, 3, 5];
        let output: Vec<i32> = [7, 0, 5, 5, 0].into();
        let head = build_list_from_vec(&head);
        let ret = Solution::next_larger_nodes(head);
        assert_eq!(ret, output);
    }
}
