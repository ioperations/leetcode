/*
You are given an integer array nums of length n, and an integer array queries of length m.
Return an array answer of length m where answer[i] is the maximum size of a subsequence that you can take from nums such that the sum of its elements is less than or equal to queries[i].
A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
*/
#[allow(unused)]
struct Solution;
#[allow(unused)]
impl Solution {
    fn answer_queries(nums: Vec<i32>, queries: Vec<i32>) -> Vec<i32> {
        let nums_lens: usize = nums.len();
        let queue_lens: usize = queries.len();
        let nums: Vec<i32> = {
            let mut nums = nums;
            nums.sort_unstable();
            nums
        };
        let mut ans: Vec<i32> = vec![0; queue_lens];
        for (idx_q, query) in queries.into_iter().enumerate() {
            let mut sum = 0;
            for (idx_n, iterm) in nums.iter().enumerate().take(nums_lens) {
                sum += iterm;
                if sum > query {
                    ans[idx_q] = idx_n as i32;
                    break;
                }
                ans[idx_q] = idx_n as i32 + 1;
            }
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [4, 5, 2, 1];
        let queries = [3, 10, 21];
        let output = [2, 3, 4];
        /* Explanation: We answer the queries as follows:
        - The subsequence [2,1] has a sum less than or equal to 3. It can be proven that 2 is the maximum size of such a subsequence, so answer[0] = 2.
        - The subsequence [4,5,1] has a sum less than or equal to 10. It can be proven that 3 is the maximum size of such a subsequence, so answer[1] = 3.
        - The subsequence [4,5,2,1] has a sum less than or equal to 21. It can be proven that 4 is the maximum size of such a subsequence, so answer[2] = 4.
        */
        let ret = Solution::answer_queries(nums.into(), queries.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [2, 3, 4, 5];
        let queries = [1];
        let output = [0];
        /*
        The empty subsequence is the only subsequence that has a sum less than or equal to 1, so answer[0] = 0.
        */
        let ret = Solution::answer_queries(nums.into(), queries.into());
        assert_eq!(ret, output);
    }
}
