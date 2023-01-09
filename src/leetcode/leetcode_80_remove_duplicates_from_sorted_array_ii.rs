/*
Given an integer array nums sorted in non-decreasing order,
remove some duplicates in-place such that each unique element appears at most twice.
The relative order of the elements should be kept the same.
Since it is impossible to change the length of the array in some languages,
you must instead have the result be placed in the first part of the array nums.
More formally, if there are k elements after removing the duplicates,
then the first k elements of nums should hold the final result.
It does not matter what you leave beyond the first k elements.
Return k after placing the final result in the first k slots of nums.
Do not allocate extra space for another array.
You must do this by modifying the input array in-place with O(1) extra memory.
*/

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused, clippy::mut_range_bound)]
    pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
        match nums.len() {
            0 | 1 => nums.len() as i32,
            _ => {
                let mut ptr = 2;
                for i in ptr..nums.len() {
                    if nums[ptr - 2] != nums[i] {
                        nums[ptr] = nums[i];
                        ptr += 1;
                    }
                }
                ptr as i32
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let mut nums = vec![1, 1, 1, 2, 2, 3];
        let output = 5;
        /*
        Explanation: Your function should return k = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
        It does not matter what you leave beyond the returned k (hence they are underscores).
        */
        let ret = Solution::remove_duplicates(&mut nums);
        let nums_expeced = [1, 1, 2, 2, 3];
        assert_eq!(ret, output);
        for (i, val) in nums_expeced.iter().enumerate() {
            assert_eq!(*val, nums[i], "{nums:?}");
        }
        // assert_eq!(nums);
    }

    #[test]
    fn case2_test() {
        let mut nums = vec![0, 0, 1, 1, 1, 1, 2, 3, 3];
        let output = 7;
        /*
        Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
        It does not matter what you leave beyond the returned k (hence they are underscores).
        */
        let ret = Solution::remove_duplicates(&mut nums);
        let nums_expeced = [0, 0, 1, 1, 2, 3, 3];
        assert_eq!(ret, output);
        for (i, val) in nums_expeced.iter().enumerate() {
            assert_eq!(*val, nums[i], "{nums:?}");
        }
    }
}
