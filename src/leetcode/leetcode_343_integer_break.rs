// Given an integer n, break it into the sum of k positive integers, where k >=
// 2, and impthe product of those integers. Return the maximum product you
// can get.

use std::collections::HashMap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn integer_break(n: i32) -> i32 {
        let mut cache = HashMap::new();
        Self::impls(n, &mut cache)
    }

    #[allow(unused)]
    pub fn impls(n: i32, cache: &mut HashMap<i32, i32>) -> i32 {
        // 2 <= n <= 58
        if (n == 1) {
            return 1;
        }

        if let Some(&v) = cache.get(&n) {
            return v;
        }

        let mut ret = 1;
        for i in (1..=(n / 2)) {
            ret = (Self::impls(i, cache) * (n - i)).max(ret);
            ret = (Self::impls(n - i, cache) * i).max(ret);
            ret = ((n - i) * i).max(ret);
            ret = (Self::impls(i, cache) * Self::impls(n - i, cache)).max(ret);
        }
        cache.entry(n).or_insert(ret);
        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 2;
        let output = 1;
        // Explanation: 2 = 1 + 1, 1 × 1 = 1.
        let ret = Solution::integer_break(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let n = 10;
        let output = 36;
        // Explanation:   10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
        let ret = Solution::integer_break(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let n = 58;
        let output = 1549681956;
        let ret = Solution::integer_break(n);
        assert_eq!(ret, output);
    }
}
