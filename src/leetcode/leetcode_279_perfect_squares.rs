#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn num_squares(n: i32) -> i32 {
        let mut dp = vec![];
        dp.resize((n + 1) as usize, std::i32::MAX);
        dp[0] = 0;
        let mut count = 1;
        while count * count <= n {
            let sq = count * count;
            for i in sq..=n {
                dp[i as usize] = (dp[(i - sq) as usize] + 1).min(dp[i as usize]);
            }
            count += 1;
        }
        dp[n as usize]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 12;
        let output = 3;
        // Explanation: 12 = 4 + 4 + 4.
        let ret = Solution::num_squares(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let n = 13;
        let output = 2;
        // Explanation: 12 = 4 + 9

        let ret = Solution::num_squares(n);
        assert_eq!(ret, output);
    }
}
