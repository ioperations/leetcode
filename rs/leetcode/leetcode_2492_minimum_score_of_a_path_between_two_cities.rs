// You are given a positive integer n representing n cities numbered from 1 to
// n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei]
// indicates that there is a bidirectional road between cities ai and bi with a
// distance equal to distancei. The cities graph is not necessarily connected.
//
// The score of a path between two cities is defined as the minimum distance of
// a road in this path.
//
// Return the minimum possible score of a path between cities 1 and n.
//
// Note:
//
// A path is a sequence of roads between two cities.
// It is allowed for a path to contain the same road multiple times, and you can
// visit cities 1 and n multiple times along the path. The test cases are
// generated such that there is at least one path between 1 and n.

use std::collections::{HashSet, VecDeque};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn min_score(n: i32, roads: Vec<Vec<i32>>) -> i32 {
        // 2 <= n <= 105
        // 1 <= roads.length <= 105
        // roads[i].length == 3
        // 1 <= ai, bi <= n
        // ai != bi
        // 1 <= distancei <= 104
        // There are no repeated edges.
        // There is at least one path between 1 and n.

        let n = n as usize;
        // 1. 转换为临接矩阵
        let mut matrix = vec![vec![]; n + 1];

        for i in roads {
            let (from, to, value) = (i[0] as usize, i[1] as usize, i[2]);
            matrix[from].push((to, value));
            matrix[to].push((from, value));
        }

        let mut this = VecDeque::new();
        let mut seen = HashSet::new();
        this.push_back(1);

        let mut ret = std::i32::MAX;
        while !this.is_empty() {
            let cur = this.pop_front().unwrap();
            for &(i, value) in &matrix[cur] {
                if value < ret {
                    ret = value;
                }
                if !seen.contains(&i) {
                    this.push_back(i);
                    seen.insert(i);
                }
            }
        }
        ret
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 4;
        let roads =
            [vec![1, 2, 9], vec![2, 3, 6], vec![2, 4, 5], vec![1, 4, 7]];
        let output = 5;
        let ret = Solution::min_score(n, roads.into());
        assert_eq!(ret, output);
        // Explanation: The path from city 1 to 4 with the minimum score is: 1
        // -> 2 -> 4. The score of this path is min(9,5) = 5.
        // It can be shown that no other path has less score.
    }

    #[test]
    fn case2_test() {
        let n = 4;
        let roads = [vec![1, 2, 2], vec![1, 3, 4], vec![3, 4, 7]];
        let output = 2;
        let ret = Solution::min_score(n, roads.into());
        assert_eq!(ret, output);
        // The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3
        // -> 4. The score of this path is min(2,2,4,7) = 2.
    }

    #[test]
    fn case3_test() {
        let n = 4;
        let roads =
            [vec![1, 2, 9], vec![2, 3, 2], vec![2, 4, 5], vec![1, 4, 7]];
        let output = 2;
        let ret = Solution::min_score(n, roads.into());
        assert_eq!(ret, output);
        // The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3
        // -> 4. The score of this path is min(2,2,4,7) = 2.
    }

    #[test]
    fn case4_test() {
        let n = 3;
        let roads = [vec![3, 2, 1], vec![1, 3, 3]];
        let output = 1;
        let ret = Solution::min_score(n, roads.into());
        assert_eq!(ret, output);
        // The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3
        // -> 4. The score of this path is min(2,2,4,7) = 2.
    }
}
