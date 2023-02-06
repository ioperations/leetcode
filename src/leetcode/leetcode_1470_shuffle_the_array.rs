// Given the array nums consisting of 2n elements in the form
// [x1,x2,...,xn,y1,y2,...,yn].
//
// Return the array in the form [x1,y1,x2,y2,...,xn,yn].

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn shuffle(nums: &[i32], n: i32) -> Vec<i32> {
        let n: usize = n as usize;
        let first = &nums[0..n];
        let second = &nums[n..];

        let mut ret = Vec::with_capacity(nums.len());
        for (&i, &j) in first.iter().zip(second.iter()) {
            ret.push(i);
            ret.push(j);
        }

        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [2, 5, 1, 3, 4, 7];
        let n = 3;
        let output = vec![2, 3, 5, 4, 1, 7];
        // Explanation: Since x1=2, x2=5, x3=1, y1=3, y2=4, y3=7 then the answer
        // is [2,3,5,4,1,7].
        let ret = Solution::shuffle(&nums, n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [1, 2, 3, 4, 4, 3, 2, 1];
        let n = 4;
        let output = vec![1, 4, 2, 3, 3, 2, 4, 1];
        // Explanation: Since x1=2, x2=5, x3=1, y1=3, y2=4, y3=7 then the answer
        // is [2,3,5,4,1,7].
        let ret = Solution::shuffle(&nums, n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = [1, 1, 2, 2];
        let n = 2;
        let output = vec![1, 2, 1, 2];
        // Explanation: Since x1=2, x2=5, x3=1, y1=3, y2=4, y3=7 then the answer
        // is [2,3,5,4,1,7].
        let ret = Solution::shuffle(&nums, n);
        assert_eq!(ret, output);
    }
}
