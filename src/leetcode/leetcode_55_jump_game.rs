// You are given an integer array nums.
// You are initially positioned at the array's first index,
// and each element in the array represents your maximum jump length at that
// position. Return true if you can reach the last index, or false otherwise

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn can_jump(nums: &[i32]) -> bool {
        fn can_jump_impl(nums: &[i32], start: usize, end: usize) -> bool {
            if start >= end || (start + nums[start] as usize >= end) {
                return true;
            }
            for i in ((start + 1)..=(start + nums[start] as usize)) {
                if can_jump_impl(nums, i, end) {
                    return true;
                }
            }
            false
        }
        let len = nums.len() - 1;
        can_jump_impl(nums, 0, len)
    }

    #[allow(unused)]
    pub fn can_jump_v2(nums: &[i32]) -> bool {
        nums.iter().enumerate().fold(0, |acc, (i, v)| {
            if acc < i as i32 {
                return -1;
            }
            acc.max(i as i32 + *v)
        }) >= (nums.len() - 1) as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let nums = [2, 3, 1, 1, 4];
        let output = true;
        // Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last
        // index.
        let ret = Solution::can_jump(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [3, 2, 1, 0, 4];
        let output = false;
        // You will always arrive at index 3 no matter what. Its maximum jump
        // length is 0, which makes it impossible to reach the last index.
        let ret = Solution::can_jump(&nums);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        let output = false;
        let nums = [3, 2, 1, 0, 4];
        b.iter(|| {
            // You will always arrive at index 3 no matter what. Its maximum
            // jump length is 0, which makes it impossible to reach the last
            // index.
            let ret = Solution::can_jump(&nums);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let nums = [2, 3, 1, 1, 4];
        let output = true;
        // Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last
        // index.
        let ret = Solution::can_jump_v2(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [3, 2, 1, 0, 4];
        let output = false;
        // You will always arrive at index 3 no matter what. Its maximum jump
        // length is 0, which makes it impossible to reach the last index.
        let ret = Solution::can_jump_v2(&nums);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_v2(b: &mut test::Bencher) {
        let nums = [3, 2, 1, 0, 4];
        let output = false;
        b.iter(|| {
            // You will always arrive at index 3 no matter what. Its maximum
            // jump length is 0, which makes it impossible to reach the last
            // index.
            let ret = Solution::can_jump_v2(&nums);
            assert_eq!(ret, output);
        });
    }
}
