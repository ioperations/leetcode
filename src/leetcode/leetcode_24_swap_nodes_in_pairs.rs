// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
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
pub fn swap_pairs(mut head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    let mut list = ListNode::new(0);
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
pub fn swap_pairs_v2(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    swap_pairs_helper(head)
}

pub fn swap_pairs_helper(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    let mut head = head;
    if let Some(mut first) = head.take() {
        if let Some(mut second) = first.next.take() {
            if let Some(next) = second.next.take() {
                first.next = swap_pairs_helper(Some(next));
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn swap_pairs_test() {
        // head = [1,2,3,4]
        let z = Some(Box::new(ListNode {
            val: 1,
            next: Some(Box::new(ListNode {
                val: 2,
                next: Some(Box::new(ListNode {
                    val: 3,
                    next: Some(Box::new(ListNode { val: 4, next: None })),
                })),
            })),
        }));
        let ret = swap_pairs(z);
        if let Some(v) = ret {
            assert_eq!(v.val, 2);
            if let Some(v2) = v.next {
                assert_eq!(v2.val, 1);
                if let Some(v3) = v2.next {
                    assert_eq!(v3.val, 4);
                    if let Some(v4) = v3.next {
                        assert_eq!(v4.val, 3);
                        return;
                    }
                }
            }
        }

        panic!("unreachable");
    }
}
