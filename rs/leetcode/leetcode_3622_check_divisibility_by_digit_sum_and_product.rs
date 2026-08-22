// You are given a positive integer n. Determine whether n is divisible by the
// sum of the following two values:
//
// The digit sum of n (the sum of its digits).
//
// The digit product of n (the product of its digits).
//
// Return true if n is divisible by this sum; otherwise, return false.
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn check_divisibility(n: i32) -> bool {
        fn sum(mut n: i32) -> i32 {
            let mut digitsum = 0;
            while n > 0 {
                digitsum += n % 10;
                n /= 10;
            }

            digitsum
        }

        fn product(mut n: i32) -> i32 {
            let mut digitsum = 1;
            while n > 0 {
                digitsum *= n % 10;
                n /= 10;
            }

            digitsum
        }

        let sum = sum(n);
        let product = product(n);
        if n % (sum + product) != 0 {
            return false;
        }

        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 99;
        let output = true;
        let ret = Solution::check_divisibility(n);
        assert_eq!(output, ret);
        // Since 99 is divisible by the sum (9 + 9 = 18) plus product (9 * 9 =
        // 81) of its digits total 99)(, the output is true.
        //
        // )
    }

    #[test]
    fn case2_test() {
        let n = 23;
        let output = false;
        let ret = Solution::check_divisibility(n);
        assert_eq!(output, ret);
        // Since 23 is not divisible by the sum (2 + 3 = 5 plus product )2 * 3 =
        // 6)( of its digits (total 11), the output is false.)
    }
}
