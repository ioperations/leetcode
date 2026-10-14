// You are given two positive integers num and sum.
//
// A positive integer n is good if it satisfies both of the following:
//
// The number of digits in n is exactly num.
// The sum of digits in n is exactly sum.
// The score of a good integer n is the sum of the squares of digits in n.
//
// Return a string denoting the good integer n that achieves the maximum score.
// If there are multiple possible integers, return the maximum one. If no such
// integer exists, return an empty string.
//
// 1 <= num <= 2 * 105
// 1 <= sum <= 2 * 106

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_sum_of_squares(num: i32, sum: i32) -> String {
        let mut num = num;
        let mut sum = sum;
        let mut ret = String::new();

        while num > 0 {
            let p = 9.min(sum);
            sum -= p;
            num -= 1;
            let c = char::from_digit(p as u32, 10).unwrap();
            ret.push(c);
        }

        if sum == 0 {
            return ret;
        }
        String::new()
    }
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn case1_test() {
        let num = 2;
        let sum = 3;
        let output = "30".to_string();

        let ret = Solution::max_sum_of_squares(num, sum);
        assert_eq!(output, ret);
        // There are 3 good integers: 12, 21, and 30.
        //
        // The score of 12 is 12 + 22 = 5.
        // The score of 21 is 22 + 12 = 5.
        // The score of 30 is 32 + 02 = 9.
        // The maximum score is 9, which is achieved by the good integer 30.
        // Therefore, the answer is "30".
    }

    #[test]
    fn case2_test() {
        let num = 2;
        let sum = 17;
        let output = "98".to_string();

        let ret = Solution::max_sum_of_squares(num, sum);
        assert_eq!(output, ret);
        // There are 2 good integers: 89 and 98.
        //
        // The score of 89 is 82 + 92 = 145.
        // The score of 98 is 92 + 82 = 145.
        // The maximum score is 145. The maximum good integer that achieves this
        // score is 98. Therefore, the answer is "98".
    }

    #[test]
    fn case3_test() {
        let num = 1;
        let sum = 10;
        let output = "".to_string();

        let ret = Solution::max_sum_of_squares(num, sum);
        assert_eq!(output, ret);
        // There are no integers that have exactly 1 digit and whose digits sum
        // to 10. Therefore, the answer is "".
    }
}
