// Definition for singly-linked list.
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
fn list_into_vec(head: &Option<Box<ListNode>>) -> Vec<i32> {
    if let Some(h) = head {
        let mut v = list_into_vec(&h.next);
        v.insert(0, h.val);
        return v;
    }

    vec![]
}

#[allow(unused)]
fn build_list_from_vec(node: &[i32]) -> Option<Box<ListNode>> {
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
        let z = build_list_from_vec(&[1, 2, 3, 4]);
        let ret = swap_pairs(z);
        let v = list_into_vec(&ret);
        assert_eq!(v, vec![2, 1, 4, 3]);
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;

    #[test]
    fn swap_pairs_test() {
        // head = [1,2,3,4]
        let z = build_list_from_vec(&[1, 2, 3, 4]);
        let ret = swap_pairs_v2(z);
        let v = list_into_vec(&ret);
        assert_eq!(v, vec![2, 1, 4, 3]);
    }
}
