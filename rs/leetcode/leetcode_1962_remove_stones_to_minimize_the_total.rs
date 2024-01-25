// You are given a 0-indexed integer array piles, where piles[i] represents the
// number of stones in the ith pile, and an integer k. You should apply the
// following operation exactly k times: Choose any piles[i] and remove
// floor(piles[i] / 2) stones from it. Notice that you can apply the operation
// on the same pile more than once. Return the minimum possible total number of
// stones remaining after applying the k operations. floor(x) is the greatest
// integer that is smaller than or equal to x (i.e., rounds x down).

use std::collections::BinaryHeap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn min_stone_sum(piles: Vec<i32>, k: i32) -> i32 {
        let mut piles = piles.into_iter().collect::<BinaryHeap<i32>>();

        for _ in 0..k {
            if let Some(v) = piles.pop() {
                let v = v - (v / 2);
                piles.push(v);
            }
        }

        piles.iter().sum::<i32>()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let piles = [5, 4, 9];
        let k = 2;
        let output = 12;
        let ret = Solution::min_stone_sum(piles.into(), k);
        assert_eq!(ret, output);
        // Explanation: Steps of a possible scenario are:
        // - Apply the operation on pile 2. The resulting piles are [5,4,5].
        // - Apply the operation on pile 0. The resulting piles are [3,4,5].
        // The total number of stones in [3,4,5] is 12.
    }

    #[test]
    fn case2_test() {
        let piles = [4, 3, 6, 7];
        let k = 3;
        let output = 12;
        let ret = Solution::min_stone_sum(piles.into(), k);
        assert_eq!(ret, output);
        // Explanation: Steps of a possible scenario are:
        // - Apply the operation on pile 2. The resulting piles are [4,3,3,7].
        // - Apply the operation on pile 3. The resulting piles are [4,3,3,4].
        // - Apply the operation on pile 0. The resulting piles are [2,3,3,4].
        // The total number of stones in [2,3,3,4] is 12.
    }
}
