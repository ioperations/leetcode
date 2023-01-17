use std::collections::HashSet;

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn intersection(nums1: &[i32], nums2: &[i32]) -> Vec<i32> {
        let mut ret_set: HashSet<i32> = HashSet::new();
        for i in nums1 {
            for j in nums2 {
                if i == j {
                    ret_set.insert(*i);
                }
            }
        }
        ret_set.into_iter().collect::<Vec<i32>>()
    }

    #[allow(unused)]
    pub fn intersection_v2(nums1: &[i32], nums2: &[i32]) -> Vec<i32> {
        let mut h: std::collections::HashSet<i32> =
            std::collections::HashSet::new();
        let mut v: Vec<i32> = vec![];
        for &i in nums1.iter() {
            if nums2.iter().any(|x| *x == i) {
                h.insert(i);
            }
        }
        for i in h {
            v.push(i);
        }
        v
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn cast1_test() {
        let nums1 = vec![1, 2, 2, 1];
        let nums2 = vec![2, 2];

        let ret = Solution::intersection(&nums1, &nums2);
        assert_eq!(ret, vec![2]);
    }

    #[test]
    fn cast2_test() {
        let nums1 = vec![4, 9, 5];
        let nums2 = vec![9, 4, 9, 8, 4];

        let ret = Solution::intersection(&nums1, &nums2);
        assert!((ret == vec![9, 4]) || (ret == vec![4, 9]), "ret is {ret:?}");
    }
    #[test]
    fn cast1_v2_test() {
        let nums1 = vec![1, 2, 2, 1];
        let nums2 = vec![2, 2];

        let ret = Solution::intersection_v2(&nums1, &nums2);
        assert_eq!(ret, vec![2]);
    }

    #[test]
    fn cast2_v2_test() {
        let nums1 = vec![4, 9, 5];
        let nums2 = vec![9, 4, 9, 8, 4];

        let ret = Solution::intersection_v2(&nums1, &nums2);
        assert!((ret == vec![9, 4]) || (ret == vec![4, 9]), "ret is {ret:?}");
    }
}
