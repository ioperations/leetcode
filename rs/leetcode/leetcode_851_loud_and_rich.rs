// There is a group of n people labeled from 0 to n - 1 where each person has a
// different amount of money and a different level of quietness.
//
// You are given an array richer where richer[i] = [ai, bi] indicates that ai
// has more money than bi and an integer array quiet where quiet[i] is the
// quietness of the ith person. All the given data in richer are logically
// correct (i.e., the data will not lead you to a situation where x is richer
// than y and y is richer than x at the same time).
//
// Return an integer array answer where answer[x] = y if y is the least quiet
// person (that is, the person y with the smallest value of quiet[y]) among all
// people who definitely have equal to or more money than the person x.
//

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn loud_and_rich(richer: &[Vec<i32>], quiet: &[i32]) -> Vec<i32> {
        // n == quiet.length
        // 1 <= n <= 500
        // 0 <= quiet[i] < n
        // All the values of quiet are unique.
        // 0 <= richer.length <= n * (n - 1) / 2
        // 0 <= ai, bi < n
        // ai != bi
        // All the pairs of richer are unique.
        // The observations in richer are all logically consistent.
        use std::collections::HashMap;

        fn dfs(
            richer2: &HashMap<i32, Vec<i32>>,
            quiet: &[i32],
            i: i32,
            ans: &mut Vec<i32>,
        ) -> i32 {
            if ans[i as usize] >= 0 {
                return ans[i as usize];
            }
            ans[i as usize] = i;
            for &j in richer2.get(&i).unwrap() {
                if quiet[ans[i as usize] as usize]
                    > quiet[dfs(richer2, quiet, j, ans) as usize]
                {
                    ans[i as usize] = ans[j as usize];
                }
            }
            ans[i as usize]
        }

        let n = quiet.len();
        let mut ans = vec![-1; n];
        let mut richer2 = HashMap::<i32, Vec<i32>>::new();
        for i in 0..n {
            richer2.insert(i as i32, Vec::<i32>::new());
        }
        for v in richer {
            richer2.entry(v[1]).or_default().push(v[0]);
        }
        for i in 0..n {
            dfs(&richer2, quiet, i as i32, &mut ans);
        }
        ans
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let richer = [
            vec![1, 0],
            vec![2, 1],
            vec![3, 1],
            vec![3, 7],
            vec![4, 3],
            vec![5, 3],
            vec![6, 3],
        ];
        let quiet = [3, 2, 5, 4, 6, 1, 7, 0];
        let output = [5, 5, 2, 5, 4, 5, 6, 7];
        let ret = Solution::loud_and_rich(&richer, &quiet);
        // answer[0] = 5.
        // Person 5 has more money than 3, which has more money than 1, which
        // has more money than 0. The only person who is quieter (has
        // lower quiet[x]) is person 7, but it is not clear if they have more
        // money than person 0. answer[7] = 7.
        // Among all people that definitely have equal to or more money than
        // person 7 (which could be persons 3, 4, 5, 6, or 7), the person who is
        // the quietest (has lower quiet[x]) is person 7.
        // The other answers can be filled out with similar reasoning.
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let richer = [];
        let quiet = [0];
        let output = [0];
        let ret = Solution::loud_and_rich(&richer, &quiet);
        assert_eq!(ret, output);
    }
}
