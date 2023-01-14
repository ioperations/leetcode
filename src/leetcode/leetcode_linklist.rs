// Definition for singly-linked list.
#[allow(unused)]
#[derive(Clone)]
pub struct ListNode<T> {
    pub val: T,
    pub next: Option<Box<ListNode<T>>>,
}

impl<T> ListNode<T> {
    #[allow(unused)]
    #[inline]
    pub fn new(val: T) -> Self {
        ListNode { next: None, val }
    }
}

#[allow(unused)]
pub fn list_into_vec<T>(head: &Option<Box<ListNode<T>>>) -> Vec<T>
where
    T: Copy,
{
    if let Some(h) = head {
        let mut v = list_into_vec(&h.next);
        v.insert(0, h.val);
        return v;
    }

    vec![]
}

#[allow(unused)]
pub fn build_list_from_vec<T>(node: &[T]) -> Option<Box<ListNode<T>>>
where
    T: Default + Copy,
{
    if node.is_empty() {
        return None;
    }
    let mut ret: ListNode<T> = ListNode::new(Default::default());

    for i in node.iter().rev() {
        let thisnode = Box::new(ListNode {
            val: *i,
            next: ret.next.take(),
        });
        ret.next = Some(thisnode);
    }
    ret.next
}
