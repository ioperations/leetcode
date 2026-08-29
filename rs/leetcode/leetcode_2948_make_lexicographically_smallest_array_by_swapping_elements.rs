// You are given a 0-indexed array of positive integers nums and a positive
// integer limit.
//
// In one operation, you can choose any two indices i and j and swap nums[i] and
// nums[j] if |nums[i] - nums[j]| <= limit.
//
// Return the lexicographically smallest array that can be obtained by
// performing the operation any number of times.
//
// An array a is lexicographically smaller than an array b if in the first
// position where a and b differ, array a has an element that is less than the
// corresponding element in b. For example, the array [2,10,3] is
// lexicographically smaller than the array [10,2,3] because they differ at
// index 0 and 2 < 10.
//
// 1 <= nums.length <= 105
// 1 <= nums[i] <= 109
// 1 <= limit <= 109

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn lexicographically_smallest_array(
        nums: Vec<i32>,
        limit: i32,
    ) -> Vec<i32> {
        // Construct a virtual graph where all elements in nums are nodes and
        // the pairs satisfying the condition have an edge between them.
        //
        // Instead of constructing all edges, we only care about the connected
        // components.
        //
        // Can we use DSU?
        //
        // Sort nums. Now we just need to consider if the consecutive elements
        // have an edge to check if they belong to the same connected component.
        // Hence, all connected components become a list of position-consecutive
        // elements after sorting.
        //
        //
        // For each index of nums from 0 to nums.length - 1 we can change it to
        // the current minimum value we have in its connected component and
        // remove that value from the connected component.

        let mut nums_indices: Box<_> =
            nums.iter().copied().enumerate().collect();
        nums_indices.sort_unstable_by_key(|&(_, num)| num);
        let mut groups = vec![0_usize; nums.len()];
        let mut chunks: Box<_> = nums_indices
            .chunk_by(|&(_, a), &(_, b)| b - a <= limit)
            .collect();
        for (i, &chunk) in chunks.iter().enumerate() {
            for &(j, _) in chunk {
                groups[j] = i;
            }
        }

        let mut nums = nums;
        for (num, group) in nums.iter_mut().zip(groups) {
            let (&(_, swap_num), new_chunk) =
                chunks[group].split_first().unwrap();
            chunks[group] = new_chunk;
            *num = swap_num;
        }

        nums
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![1, 5, 3, 9, 8];
        let limit = 2;
        let output = vec![1, 3, 5, 8, 9];
        let ret =
            Solution::lexicographically_smallest_array(nums.into(), limit);
        assert_eq!(output, ret);
        // Apply the operation 2 times:
        // - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
        // - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
        // We cannot obtain a lexicographically smaller array by applying any
        // more operations. Note that it may be possible to get the same
        // result by doing different operations.
    }

    #[test]
    fn case2_test() {
        let nums = vec![1, 7, 6, 18, 2, 1];
        let limit = 2;
        let output = vec![1, 6, 7, 18, 1, 2];
        let ret =
            Solution::lexicographically_smallest_array(nums.into(), limit);
        assert_eq!(output, ret);
        // Apply the operation 3 times:
        // - Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
        // - Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
        // - Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
        // We cannot obtain a lexicographically smaller array by applying any
        // more operations.
    }

    #[test]
    fn case3_test() {
        let nums = vec![1, 7, 28, 19, 10];
        let limit = 3;
        let output = vec![1, 7, 28, 19, 10];
        let ret =
            Solution::lexicographically_smallest_array(nums.into(), limit);
        assert_eq!(output, ret);
        // [1,7,28,19,10] is the lexicographically smallest array we can obtain
        // because we cannot apply the operation on any two indices.
    }
}
