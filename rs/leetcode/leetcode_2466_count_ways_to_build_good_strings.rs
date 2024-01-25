// Given the integers zero, one, low, and high, we can construct a string by
// starting with an empty string, and then at each step perform either of the
// following:
//
// Append the character '0' zero times.
// Append the character '1' one times.
//
// This can be performed any number of times.
//
// A good string is a string constructed by the above process having a length
// between low and high (inclusive).
//
//
// Return the number of different good strings that can be constructed
// satisfying these properties. Since the answer can be large, return it modulo
// 109 + 7.

#[allow(unused)]
struct Solution;

const MOD: i32 = 10i32.pow(9) + 7;

impl Solution {
    #[allow(unused)]
    pub fn count_good_strings(low: i32, high: i32, zero: i32, one: i32) -> i32 {
        // 1 <= low <= high <= 105
        // 1 <= zero, one <= low
        assert!(low > 0);
        assert!(high > 0);
        assert!(high >= low);
        assert!(zero > 0 && zero <= low);
        assert!(one > 0 && one <= low);

        let mut cache = vec![-1; high as usize + 1];
        Self::dfs(&mut cache, low, high, zero, one, 0)
    }

    #[allow(unused)]
    pub fn count_good_strings_v2(
        low: i32,
        high: i32,
        zero: i32,
        one: i32,
    ) -> i32 {
        // 1 <= low <= high <= 105
        // 1 <= zero, one <= low
        assert!(low > 0);
        assert!(high > 0);
        assert!(high >= low);
        assert!(zero > 0 && zero <= low);
        assert!(one > 0 && one <= low);

        // 进阶版的青蛙趴楼梯
        //
        // 令m = zero, n = one
        //
        // 青蛙趴楼梯时可以跳1步或者两步，扩展一些，就是可以跳m步和n步，
        // 总体思路不变：
        //
        // 1. 当前的状态i，可以由状态i - m通过跳一次m步的方式到达
        // 2. 当前的状态i，也可以由状态i - n通过跳一次n步的方式到达
        //
        // 转移方程：
        // dp[i] = dp[i-m] + dp[i-n];
        //
        // 初始化dp[0] = 1，
        //
        // dp[high] 记录的时从0到high有多少种组成方式！！！
        //
        // 所以说当前状态i >= low的时候，我们可以再用一个变量累加结果。
        //
        let mut cache = vec![0; high as usize + 1];
        cache[0] = 1;
        let mut res = 0;
        for i in (1..=high) {
            if i >= one {
                cache[i as usize] = cache[(i - one) as usize];
            }
            if i >= zero {
                cache[i as usize] =
                    (cache[i as usize] + cache[(i - zero) as usize]) % MOD;
            }

            if i >= low {
                res = (res + cache[i as usize]) % MOD;
            }
        }
        res
    }
    fn dfs(
        cache: &mut [i32],
        low: i32,
        high: i32,
        zero: i32,
        one: i32,
        len: i32,
    ) -> i32 {
        const MOD: i32 = 10i32.pow(9) + 7;
        if len > high {
            return 0;
        }
        let len_idx = len as usize;
        if cache[len_idx] >= 0 {
            return cache[len_idx];
        }

        let initial = (len >= low) as i32;
        let if_zero = Self::dfs(cache, low, high, zero, one, len + zero);
        let if_one = Self::dfs(cache, low, high, zero, one, len + one);

        cache[len_idx] = (initial + if_zero + if_one) % MOD;
        cache[len_idx]
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let low = 3;
        let high = 3;
        let zero = 1;
        let one = 1;
        let output = 8;
        let ret = Solution::count_good_strings(low, high, zero, one);
        assert_eq!(ret, output);
        // Explanation:
        // One possible valid good string is "011".
        // It can be constructed as follows: "" -> "0" -> "01" -> "011".
        // All binary strings from "000" to "111" are good strings in this
        // example.
    }

    #[test]
    fn case2_test() {
        let low = 2;
        let high = 3;
        let zero = 1;
        let one = 2;
        let output = 5;
        let ret = Solution::count_good_strings(low, high, zero, one);
        assert_eq!(ret, output);
        // Explanation:
        // The good strings are "00", "11", "000", "110", and "011".
    }
}

#[cfg(test)]
mod test_v2 {
    use super::*;

    #[test]
    fn case1_test() {
        let low = 3;
        let high = 3;
        let zero = 1;
        let one = 1;
        let output = 8;
        let ret = Solution::count_good_strings_v2(low, high, zero, one);
        assert_eq!(ret, output);
        // Explanation:
        // One possible valid good string is "011".
        // It can be constructed as follows: "" -> "0" -> "01" -> "011".
        // All binary strings from "000" to "111" are good strings in this
        // example.
    }

    #[test]
    fn case2_test() {
        let low = 2;
        let high = 3;
        let zero = 1;
        let one = 2;
        let output = 5;
        let ret = Solution::count_good_strings_v2(low, high, zero, one);
        assert_eq!(ret, output);
        // Explanation:
        // The good strings are "00", "11", "000", "110", and "011".
    }
}
