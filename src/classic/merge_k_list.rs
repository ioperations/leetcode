// Definition for singly-linked list.

#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}
use std::cmp::Ordering;

impl Ord for ListNode {
    fn cmp(&self, other: &Self) -> Ordering {
        other.val.cmp(&self.val)
    }
}
impl PartialOrd for ListNode {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}
#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn merge_k_lists(lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        type BH<T> = std::collections::BinaryHeap<T>;
        let mut pq: BH<Box<ListNode>> = std::collections::BinaryHeap::new();
        for list in lists.into_iter().flatten() {
            pq.push(list);
        }

        let mut dummy = Box::new(ListNode::new(0));
        let mut z = &mut dummy;
        while (!pq.is_empty()) {
            if let Some(a) = z.next.take() {
                pq.push(a);
            }
            if let Some(a) = pq.pop() {
                z.next = Some(a);
                z = z.next.as_mut().unwrap();
            }
        }

        dummy.next
    }
}
#[cfg(test)]
mod tests {
    use super::*;
    extern crate test;

    #[allow(unused)]
    fn build_list_iter(node: &[i32]) -> Option<Box<ListNode>> {
        if node.is_empty() {
            return None;
        }
        let mut ret: ListNode = ListNode::new(0);

        for i in node.iter().rev() {
            let mut thisnode = Box::new(ListNode {
                val: *i,
                next: ret.next.take(),
            });
            ret.next = Some(thisnode);
        }
        ret.next
    }

    #[bench]
    fn bench_build_list_iter(b: &mut test::Bencher) {
        let vec = vec![10; 100];
        b.iter(|| {
            let _ = build_list_iter(&vec);
        });
    }

    /// 将数组转换成自定义链表
    fn convert_vec_to_list(nodes: Vec<Vec<i32>>) -> Vec<Option<Box<ListNode>>> {
        let mut ret: Vec<Option<Box<ListNode>>> = Vec::with_capacity(nodes.len());
        for i in nodes {
            let list = build_list_iter(&i);
            ret.push(list);
        }
        ret
    }

    /// 将数组转换成自定义链表
    fn convert_vec_to_list_iter(nodes: Vec<Vec<i32>>) -> Vec<Option<Box<ListNode>>> {
        let mut ret: Vec<Option<Box<ListNode>>> = Vec::with_capacity(nodes.len());
        for i in nodes {
            let list = build_list_iter(&i);
            ret.push(list);
        }
        ret
    }

    /// 将自定义链表转换成数组
    fn convert_list_to_vec(lists: Option<Box<ListNode>>) -> Vec<i32> {
        convert_list_to_vec_iter(lists)
    }

    /// 将自定义链表转换成数组
    fn convert_list_to_vec_iter(lists: Option<Box<ListNode>>) -> Vec<i32> {
        let mut lists = lists;
        let mut ret = vec![];
        while let Some(node) = lists {
            ret.push(node.val);
            lists = node.next;
        }
        ret
    }

    #[test]
    fn basic_test() {
        let lists = Some(Box::new(ListNode::new(1)));
        let vec = convert_list_to_vec(lists);
        assert_eq!(vec, vec![1]);
        let lists = Some(Box::new(ListNode {
            val: 1,
            next: Some(Box::new(ListNode {
                val: 2,
                next: Some(Box::new(ListNode::new(3))),
            })),
        }));
        let vec = convert_list_to_vec(lists);
        assert_eq!(vec, vec![1, 2, 3]);
    }

    #[test]
    fn basic_2_test() {
        let vec = vec![vec![1, 2, 3], vec![2]];
        let list_expected = vec![
            Some(Box::new(ListNode {
                val: 1,
                next: Some(Box::new(ListNode {
                    val: 2,
                    next: Some(Box::new(ListNode::new(3))),
                })),
            })),
            Some(Box::new(ListNode::new(2))),
        ];

        let list = convert_vec_to_list(vec);
        assert_eq!(list_expected, list);
    }

    #[test]
    fn basic_22_test() {
        let vec = vec![vec![1, 2, 3], vec![2]];
        let list_expected = vec![
            Some(Box::new(ListNode {
                val: 1,
                next: Some(Box::new(ListNode {
                    val: 2,
                    next: Some(Box::new(ListNode::new(3))),
                })),
            })),
            Some(Box::new(ListNode::new(2))),
        ];

        let list = convert_vec_to_list_iter(vec);
        assert_eq!(list_expected, list);
    }

    #[test]
    fn basic_3_test() {
        let mut vec: Vec<Vec<i32>> = vec![vec![]];
        vec.resize(10, vec![]);
        for k in &mut vec {
            for j in 0..1000 {
                k.push(j);
            }
        }
        let z = vec.clone();
        let list = convert_vec_to_list(vec);
        for (i, k) in list.into_iter().enumerate() {
            let v = convert_list_to_vec(k);
            assert_eq!(z[i], v);
        }
    }

    #[test]
    fn basic_33_test() {
        let mut vec: Vec<Vec<i32>> = vec![vec![]];
        vec.resize(10, vec![]);
        for k in &mut vec {
            for j in 0..1000 {
                k.push(j);
            }
        }
        let z = vec.clone();
        let list = convert_vec_to_list_iter(vec);
        for (i, k) in list.into_iter().enumerate() {
            let v = convert_list_to_vec_iter(k);
            assert_eq!(z[i], v);
        }
    }
    #[test]
    fn case1_test() {
        let input = vec![vec![1, 4, 5], vec![1, 3, 4], vec![2, 6]];
        let out = vec![1, 1, 2, 3, 4, 4, 5, 6];
        let lists = convert_vec_to_list(input);
        let ret = Solution::merge_k_lists(lists);
        let ret_vec = convert_list_to_vec(ret);
        assert_eq!(ret_vec, out);
    }

    #[test]
    fn case2_test() {
        let input = vec![];
        let out = vec![];
        let lists = convert_vec_to_list(input);
        let ret = Solution::merge_k_lists(lists);
        let ret_vec = convert_list_to_vec(ret);
        assert_eq!(ret_vec, out);
    }

    #[test]
    fn case3_test() {
        let input = vec![vec![]];
        let out = vec![];
        let lists = convert_vec_to_list(input);
        let ret = Solution::merge_k_lists(lists);
        let ret_vec = convert_list_to_vec(ret);
        assert_eq!(ret_vec, out);
    }
}
