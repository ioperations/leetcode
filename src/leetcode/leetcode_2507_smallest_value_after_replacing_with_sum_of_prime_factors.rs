// Smallest Value After Replacing With Sum of Prime Factors
// You are given a positive integer n.
// Continuously replace n with the sum of its prime factors.
// Note that if a prime factor divides n multiple times, it should be included
// in the sum as many times as it divides n. Return the smallest value n will
// take on.

use std::collections::HashMap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn smallest_value(n: i32) -> i32 {
        // 2 <= n <= 105
        fn find_all_sub_expr(
            num: i32,
            cache: &mut HashMap<i32, Vec<i32>>,
        ) -> Vec<i32> {
            for i in (2..) {
                if i * i > num {
                    break;
                }
                if num % i == 0 {
                    let mut ret = find_all_sub_expr(num / i, cache);
                    ret.push(i);
                    cache.entry(num).or_insert(ret.clone());
                    return ret;
                }
            }
            let ret = vec![num];
            cache.entry(num).or_insert(ret.clone());
            ret
        };

        fn caclculate(
            num: i32,
            cache: &mut HashMap<i32, Vec<i32>>,
            cache_res: &mut HashMap<i32, i32>,
        ) -> i32 {
            if let Some(&v) = cache_res.get(&num) {
                return v;
            }
            for i in (2..) {
                if i * i > num {
                    break;
                }
                if num % i == 0 {
                    let ret = find_all_sub_expr(num / i, cache);
                    let ret: i32 = ret.into_iter().sum();
                    if (i + ret) == num {
                        cache_res.entry(num).or_insert(num);
                        return num;
                    }
                    let ret = caclculate(ret + i, cache, cache_res);
                    cache_res.entry(num).or_insert(ret);
                    return ret;
                }
            }
            cache_res.entry(num).or_insert(num);

            num
        };

        let mut cache = HashMap::new();
        let mut cache_res = HashMap::new();
        caclculate(n, &mut cache, &mut cache_res)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 15;
        let output = 5;
        // Explanation: Initially, n = 15.
        // 15 = 3 * 5, so replace n with 3 + 5 = 8.
        // 8 = 2 * 2 * 2, so replace n with 2 + 2 + 2 = 6.
        // 6 = 2 * 3, so replace n with 2 + 3 = 5.
        // 5 is the smallest value n will take on.
        let ret = Solution::smallest_value(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let n = 3;
        let output = 3;
        // Explanation: Initially, n = 15.
        // Initially, n = 3.
        // 3 is the smallest value n will take on.
        let ret = Solution::smallest_value(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let n = 100_000;
        let output = 7;
        // Explanation: Initially, n = 15.
        // Initially, n = 3.
        // 3 is the smallest value n will take on.
        let ret = Solution::smallest_value(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let n = 4;
        let output = 4;
        // Explanation: Initially, n = 15.
        // Initially, n = 3.
        // 3 is the smallest value n will take on.
        let ret = Solution::smallest_value(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case5_test() {
        let n = 27;
        let output = 5;
        // Explanation: Initially, n = 27
        // 3 is the smallest value n will take on.

        // 27 = 3 * 3 * 3 , so replace n with 3 + 3 + 3  = 9.
        // 9 =  3 * 3, so replace n with 3 + 3 = 6.
        // 6 = 2 * 3, so replace n with 2 + 3 = 5.
        // 5 is the smallest value n will take on.
        let ret = Solution::smallest_value(n);
        assert_eq!(ret, output);
    }
}
