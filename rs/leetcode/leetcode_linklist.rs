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
pub fn list_into_vec_iter<T>(head: Option<&Box<ListNode<T>>>) -> Vec<T>
where
    T: Copy,
{
    let mut v = vec![];
    let mut h = head;
    while let Some(value) = h {
        v.push(value.val);
        h = value.next.as_ref();
    }
    v
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
#[tracing::instrument(level = "debug", skip_all)]
pub fn build_list_from_vec<T>(node: &[T]) -> Option<Box<ListNode<T>>>
where
    T: Default + Copy,
{
    // debug!("build list from vec called!");
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let vec = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0];
        let link_list = build_list_from_vec(&vec);
        let ret = list_into_vec(&link_list);
        assert_eq!(ret, vec);
    }

    #[test]
    fn case2_test() {
        let vec: Vec<i32> = vec![];
        let link_list = build_list_from_vec(&vec);
        let ret = list_into_vec(&link_list);
        assert_eq!(ret, vec);
    }

    #[test]
    fn case3_test() {
        let vec = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0];
        let link_list = build_list_from_vec(&vec);
        let ret = list_into_vec(&link_list);
        assert_eq!(ret, vec);
    }

    #[test]
    fn case3_iter_test() {
        let vec = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0];
        let link_list = build_list_from_vec(&vec);
        let ret = list_into_vec_iter(link_list.as_ref());
        assert_eq!(ret, vec);
    }

    #[test]
    fn case4_test() {
        let vec = [0];
        let link_list = build_list_from_vec(&vec);
        let ret = list_into_vec(&link_list);
        assert_eq!(ret, vec);
    }
}
