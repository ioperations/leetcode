// You are given nums, an array of positive integers of size 2 * n. You must
// perform n operations on this array.
//
// In the ith operation (1-indexed), you will:
//
// Choose two elements, x and y.
// Receive a score of i * gcd(x, y).
// Remove x and y from nums.
//
// Return the maximum score you can receive after performing n operations.
//
// The function gcd(x, y) is the greatest common divisor of x and y.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_score(nums: &[i32]) -> i32 {
        // 1 <= n <= 7
        // nums.length == 2 * n
        // 1 <= nums[i] <= 106

        // let n be nums.len() and k be n / 2, obviously, we have k * (2 * k -
        // 1) number of ways to select an i and a j such that 0 <= i < j < n.
        // Use this fact, we can recursively come up with the number of ways to
        // group 2 * k indexes into ordered k pairs ( cnt[k] = k * (2 * k - 1) *
        // cnt[k - 1] ).
        //
        // k => pair(s)
        // 1 => 1
        // 2 => 6
        // 3 => 90
        // 4 => 2520
        // 5 => 113400
        // 6 => 7484400
        // 7 => 681080400
        //
        // These numbers simply tell us that using brute force barely helps us
        // to handle the case when k <= 6.
        //
        // For a specific k, the ways of selecting k pairs might be unique,
        // HOWEVER, SOME OF THEM COULD BE COMBINED in calculating the final
        // solution. Let's say k is 7, four different indexes 0 <= i, j,
        // u, v < 14 have been selected for the 6th round & 7th round, does the
        // order these four indexes used in 6th round & 7th round have any
        // impact on selecting the pair from the remaining indexes for the 5th
        // round? The answer is NO! Therefore, we can use mask
        // (1<<i|1<<j|1<<u|1<<v) to indicate that i, j, u, v are unavailable in
        // the recursive call of selecting the 5th pair.
        let mut dp = vec![-1; 1 << nums.len()];
        Self::eval(nums, 0, &mut dp)
    }

    fn gcd(a: i32, b: i32) -> i32 {
        if a < b {
            return Self::gcd(b, a);
        }
        if a % b == 0 {
            return b;
        }
        Self::gcd(b, a % b)
    }

    fn eval(nums: &[i32], mask: usize, dp: &mut Vec<i32>) -> i32 {
        if dp[mask] != -1 {
            return dp[mask];
        }

        let mut k = nums.len();
        for i in 0..nums.len() {
            if mask & (1 << i) != 0 {
                k -= 1;
            }
        }
        k >>= 1;
        if k == 0 {
            return 0;
        }

        dp[mask] = 0;
        for i in 0..nums.len() {
            for j in i + 1..nums.len() {
                if mask & (1 << i) != 0 || mask & (1 << j) != 0 {
                    continue;
                }
                let mask_new = mask | (1 << i) | (1 << j);
                dp[mask] = dp[mask].max(
                    k as i32 * Self::gcd(nums[i], nums[j])
                        + Self::eval(nums, mask_new, dp),
                );
            }
        }

        dp[mask]
    }
}

#[cfg(test)]
mod test_gcd {

    use super::*;

    #[test]
    fn test_gcd() {
        // Simple greatest common divisor.
        assert_eq!(Solution::gcd(3, 5), 1);
        assert_eq!(Solution::gcd(14, 15), 1);

        // More complex greatest common divisor.
        assert_eq!(
            Solution::gcd(2 * 3 * 5 * 11 * 17, 3 * 7 * 11 * 13 * 19),
            3 * 11
        );
    }

    #[test]
    fn test_multiple_gcd() {
        // List of numbers.
        let numbers: [i32; 4] = [3, 9, 21, 81];
        // Compute divisor one after the other.
        // Method 1: Using for-loop.
        let mut divisor = numbers[0];
        for no in &numbers[1..] {
            divisor = Solution::gcd(divisor, *no);
        }
        assert_eq!(divisor, 3);

        // Method 2: Using iterator & fold.
        let divisor: i32 = numbers
            .iter()
            .fold(numbers[0], |acc, &x| Solution::gcd(acc, x));
        assert_eq!(divisor, 3);
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 2];
        let output = 1;
        let ret = Solution::max_score(&nums);
        assert_eq!(ret, output);
        // Explanation: The optimal choice of operations is:
        // (1 * gcd(1, 2)) = 1
    }

    #[test]
    fn case2_test() {
        let nums = [3, 4, 6, 8];
        let output = 11;
        let ret = Solution::max_score(&nums);
        assert_eq!(ret, output);
        // Explanation:
        //   The optimal choice of operations is:
        // (1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11
    }

    #[test]
    fn case3_test() {
        let nums = [1, 2, 3, 4, 5, 6];
        let output = 14;
        let ret = Solution::max_score(&nums);
        assert_eq!(ret, output);
        // Explanation:The optimal choice of operations is:
        // (1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14
    }
}
