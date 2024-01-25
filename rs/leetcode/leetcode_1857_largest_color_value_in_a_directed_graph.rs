// There is a directed graph of n colored nodes and m edges. The nodes are
// numbered from 0 to n - 1.
//
// You are given a string colors where colors[i] is a lowercase English letter
// representing the color of the ith node in this graph (0-indexed). You are
// also given a 2D array edges where edges[j] = [aj, bj] indicates that there is
// a directed edge from node aj to node bj.
//
// A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk
// such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The
// color value of the path is the number of nodes that are colored the most
// frequently occurring color along that path.
//
// Return the largest color value of any valid path in the given graph, or -1 if
// the graph contains a cycle.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn largest_path_value(colors: &str, edges: &[Vec<i32>]) -> i32 {
        // n == colors.length
        // m == edges.length
        // 1 <= n <= 105
        // 0 <= m <= 105
        // colors consists of lowercase English letters.
        // 0 <= aj, bj < n
        use std::collections::VecDeque;
        let mut degree = vec![0; colors.len()];

        let mut adj = vec![Vec::new(); colors.len()];

        for v in edges {
            adj[v[0] as usize].push(v[1] as usize);

            degree[v[1] as usize] += 1;
        }

        let mut queue = VecDeque::new();

        (0..adj.len()).for_each(|i| {
            if degree[i] == 0 {
                queue.push_back(i);
            }
        });

        let mut dp = vec![[0; 26]; adj.len()];

        let mut ans = 1;

        while let Some(i) = queue.pop_front() {
            let c = (colors.as_bytes()[i] - b'a') as usize;

            dp[i][c] += 1;

            ans = ans.max(*dp[i].iter().max().unwrap());

            for &j in &adj[i] {
                degree[j] -= 1;

                for c in 0..26 {
                    dp[j][c] = dp[j][c].max(dp[i][c]);
                }

                if degree[j] == 0 {
                    queue.push_back(j);
                }
            }
        }

        if degree.iter().any(|&d| d > 0) {
            return -1;
        }

        ans
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let colors = "abaca";
        let edges: Vec<Vec<i32>> = [[0, 1], [0, 2], [2, 3], [3, 4]]
            .iter()
            .map(|v| v.to_vec())
            .collect();
        let output = 3;
        let ret = Solution::largest_path_value(colors, &edges);
        assert_eq!(ret, output);
        // Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are
        // colored "a" (red in the above image).
    }

    #[test]
    fn case2_test() {
        let colors = "a";
        let edges: Vec<Vec<i32>> =
            [[0, 0]].iter().map(|v| v.to_vec()).collect();
        let output = -1;
        let ret = Solution::largest_path_value(colors, &edges);
        assert_eq!(ret, output);
        // There is a cycle from 0 to 0.
    }
}
