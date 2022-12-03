use std::collections::BinaryHeap;

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn vec_to_min_heap<T: std::cmp::Ord>(vec: Vec<T>) -> BinaryHeap<T> {
        BinaryHeap::from(vec)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn vec_to_min_heap_test() {
        let ret = Solution::vec_to_min_heap(vec![1, 2, 3, 4, 5]);
        assert_eq!(ret.into_sorted_vec(), vec![1, 2, 3, 4, 5]);
    }
}
