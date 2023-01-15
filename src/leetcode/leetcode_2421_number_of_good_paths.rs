// There is a tree (i.e. a connected, undirected graph with no cycles)
// consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
// You are given a 0-indexed integer array vals of length n where vals[i]
// denotes the value of the ith node. You are also given a 2D integer array edges
// where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A good path is a simple path that satisfies the following conditions:
// The starting node and the ending node have the same value.
// All nodes between the starting node and the ending node have values less than or
// equal to the starting node (i.e. the starting node's value should be the maximum value along the path).
// Return the number of distinct good paths.
// Note that a path and its reverse are counted as the same path. For example,
// 0 -> 1 is considered to be the same as 1 -> 0. A single node is also considered as a valid path.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn number_of_good_paths(vals: Vec<i32>, edges: Vec<Vec<i32>>) -> i32 {
        /*
         * n == vals.length
         * 1 <= n <= 3 * 104
         * 0 <= vals[i] <= 105
         * edges.length == n - 1
         * edges[i].length == 2
         * 0 <= ai, bi < n
         * ai != bi
         * edges represents a valid tree.
         */
        // dfs + how to dertermine if a path is valid
        use std::collections::{BTreeMap, HashMap};
        fn uf_find(uf: &mut [usize], a: usize) -> usize {
            let mut b = a;
            while uf[b] != b {
                b = uf[b];
            }
            uf[a] = b;
            b
        }
        fn uf_union(uf: &mut [usize], mut a: usize, mut b: usize) {
            a = uf_find(uf, a);
            b = uf_find(uf, b);
            uf[a] = b;
        }

        let n = vals.len();

        // only build connection from big val -> small val
        let mut adj = vec![vec![]; n];
        for edge in edges {
            if vals[edge[0] as usize] >= vals[edge[1] as usize] {
                adj[edge[0] as usize].push(edge[1] as usize);
            } else {
                adj[edge[1] as usize].push(edge[0] as usize);
            }
        }

        // a sorted map for all node binding with same value
        let mut val_to_idx: BTreeMap<i32, Vec<usize>> = BTreeMap::new();
        for (i, val) in vals.into_iter().enumerate() {
            val_to_idx.entry(val).or_insert(vec![]).push(i);
        }

        // union find stuff
        let mut uf: Vec<_> = (0..n).collect();
        let mut ret = n;
        for (val, idx_arr) in val_to_idx {
            // add new nodes into union
            for &idx in &idx_arr {
                for &node in &adj[idx] {
                    uf_union(&mut uf, idx, node);
                }
            }

            // count path in each group
            let mut group: HashMap<usize, usize> = HashMap::new();
            for idx in idx_arr {
                group
                    .entry(uf_find(&mut uf, idx))
                    .and_modify(|count| *count += 1)
                    .or_insert(1);
            }
            for (_, count) in group {
                ret += count * (count - 1) / 2;
            }
        }
        ret as _
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let vals = [1, 3, 2, 1, 3];
        let edges = [vec![0, 1], vec![0, 2], vec![2, 3], vec![2, 4]];
        let output = 6;
        /*
         * Explanation: There are 5 good paths consisting of a single node.
         * There is 1 additional good path: 1 -> 0 -> 2 -> 4.
         * (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
         * Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
         */
        let ret = Solution::number_of_good_paths(vals.into(), edges.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let vals = [1, 1, 2, 2, 3];
        let edges = [vec![0, 1], vec![1, 2], vec![2, 3], vec![2, 4]];
        let output = 7;
        /*
         * There are 5 good paths consisting of a single node.
         * There are 2 additional good paths: 0 -> 1 and 2 -> 3.
         */
        let ret = Solution::number_of_good_paths(vals.into(), edges.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let vals = [1];
        let edges = [];
        let output = 1;
        /*
         * The tree consists of only one node, so there is one good path.
         */
        let ret = Solution::number_of_good_paths(vals.into(), edges.into());
        assert_eq!(ret, output);
    }
}
