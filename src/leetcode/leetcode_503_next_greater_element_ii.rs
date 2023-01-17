// Given a circular integer array nums (i.e., the next element of
// nums[nums.length - 1] is nums[0]), return the next greater number for every
// element in nums.
//
// The next greater number of a number x is the first greater number to its
// traversing-order next in the array, which means you could search circularly
// to find its next greater number. If it doesn't exist, return -1 for this
// number.

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn next_greater_elements(nums: Vec<i32>) -> Vec<i32> {
        let size = nums.len();
        let mut numsz = vec![nums.clone(), nums];
        let nums: Vec<i32> = numsz.into_iter().flatten().collect();
        let mut ret: Vec<i32> = vec![(-1); size];

        for i in 0..size {
            for j in 1..size {
                if nums[i + j] > nums[i] {
                    ret[i] = nums[i + j];
                    break;
                }
            }
        }

        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let vec = vec![1, 2, 1];
        let out = vec![2, -1, 2];
        let ret = Solution::next_greater_elements(vec);
        //  Explanation: The first 1's next greater number is 2;
        //  The number 2 can't find next greater number.
        //  The second 1's next greater number needs to search circularly, which
        // is also 2.
        assert_eq!(ret, out);
    }

    #[test]
    fn case2_test() {
        let vec = vec![1, 2, 3, 4, 3];
        let out = vec![2, 3, 4, -1, 4];
        let ret = Solution::next_greater_elements(vec);
        assert_eq!(ret, out);
    }
}
