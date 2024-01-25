// Given an array nums of positive integers, return the longest possible length
// of an array prefix of nums, such that it is possible to remove exactly one
// element from this prefix so that every number that has appeared in it will
// have the same number of occurrences.
//
// If after removing one element there are no remaining elements, it's still
// considered that every appeared number has the same number of ocurrences (0).

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_equal_freq(nums: &[i32]) -> i32 {
        let mut count = vec![0i32; 100_001];
        let mut freq = vec![0i32; 100_001];
        let n = nums.len();
        let mut ans = 0;
        for i in 1..=n {
            let a = nums[i - 1];
            let mut c = count[a as usize];
            freq[c as usize] -= 1;
            c += 1;
            count[a as usize] = c;
            freq[c as usize] += 1;
            if freq[c as usize] * c == i as i32 && i < n {
                ans = i as i32 + 1;
            }
            let d = i as i32 - freq[c as usize] * c;
            if (d == c + 1 || d == 1) && freq[d as usize] == 1 {
                ans = i as i32;
            }
        }
        ans
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [2, 2, 1, 1, 5, 3, 3, 5];
        let output = 7;
        let ret = Solution::max_equal_freq(&nums);
        assert_eq!(ret, output);
        // Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we
        // remove nums[4] = 5, we will get [2,2,1,1,3,3], so that each number
        // will appear exactly twice.
    }

    #[test]
    fn case2_test() {
        let nums = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5];
        let output = 13;
        let ret = Solution::max_equal_freq(&nums);
        assert_eq!(ret, output);
    }
}
