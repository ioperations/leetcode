// You are given an integer n. There is an undirected graph with n nodes,
// numbered from 0 to n - 1. You are given a 2D integer array edges where
// edges[i] = [ai, bi] denotes that there exists an undirected edge connecting
// nodes ai and bi.
//
// Return the number of pairs of different nodes that are unreachable from each
// other.
#[allow(unused)]
struct UnionFind {
    p: Vec<i32>,
}

impl UnionFind {
    #[allow(unused)]
    fn new(n: i32) -> UnionFind {
        let mut parent = vec![0; n as _];

        for i in 0..n {
            parent[i as usize] = i;
        }

        UnionFind { p: parent }
    }

    #[allow(unused)]
    fn find(&mut self, x: i32) -> i32 {
        let i = x as usize;
        if self.p[i] != x {
            self.p[i] = self.find(self.p[i]);
        }
        self.p[i]
    }

    #[allow(unused)]
    fn union(&mut self, a: i32, b: i32) {
        let au = self.find(a);
        let bu = self.find(b);
        self.p[au as usize] = bu;
    }
}

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn count_pairs_v1(n: i32, edges: &[Vec<i32>]) -> i64 {
        // 1 <= n <= 105
        // 0 <= edges.length <= 2 * 105
        // edges[i].length == 2
        // 0 <= ai, bi < n
        // ai != bi
        // There are no repeated edges.
        let n = n as usize;
        let mut matrix = vec![vec![]; n];

        for i in edges {
            let (from, to) = (i[0] as usize, i[1] as usize);
            if from > to {
                matrix[to].push(from);
            } else {
                matrix[from].push(to);
            }
        }
        let mut ret = 0;

        for (k, v) in edges.iter().enumerate() {
            ret += (n - k) as i64 - v.len() as i64;
        }
        ret
    }

    #[allow(unused)]
    pub fn count_pairs(n: i32, edges: Vec<Vec<i32>>) -> i64 {
        // 1 <= n <= 105
        // 0 <= edges.length <= 2 * 105
        // edges[i].length == 2
        // 0 <= ai, bi < n
        // ai != bi
        // There are no repeated edges.
        let mut uf = UnionFind::new(n);

        for e in edges {
            let (u, v) = (e[0], e[1]);
            uf.union(u, v);
        }

        let mut counts = vec![0; n as _];
        for v in 0..n {
            let i = uf.find(v) as usize;
            counts[i] += 1;
        }

        let mut res = 0;

        for v in counts {
            let (a, b) = (v as i64, n as i64);
            res += (a * (b - a));
        }

        res / 2
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 3;
        let edges = [vec![0, 1], vec![0, 2], vec![1, 2]];
        let output = 0;
        let ret = Solution::count_pairs(n, edges.into());
        assert_eq!(ret, output);
        // Explanation: There are no pairs of nodes that are unreachable from
        // each other. Therefore, we return 0.
    }

    #[test]
    fn case2_test() {
        let n = 7;
        let edges =
            [vec![0, 2], vec![0, 5], vec![2, 4], vec![1, 6], vec![5, 4]];
        let output = 14;
        let ret = Solution::count_pairs(n, edges.into());
        assert_eq!(ret, output);
        // There are 14 pairs of nodes that are unreachable from each other:
        // [[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],
        // [3,6],[4,6],[5,6]]. Therefore, we return 14.
    }
}

#[cfg(test)]
mod test_v1 {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 3;
        let edges = [vec![0, 1], vec![0, 2], vec![1, 2]];
        let output = 0;
        let ret = Solution::count_pairs_v1(n, &edges);
        assert_eq!(ret, output);
        // Explanation: There are no pairs of nodes that are unreachable from
        // each other. Therefore, we return 0.
    }

    #[test]
    fn case2_test() {
        let n = 7;
        let edges =
            [vec![0, 2], vec![0, 5], vec![2, 4], vec![1, 6], vec![5, 4]];
        let output = 15;
        let ret = Solution::count_pairs_v1(n, &edges);
        assert_eq!(ret, output);
        // There are 14 pairs of nodes that are unreachable from each other:
        // [[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],
        // [3,6],[4,6],[5,6]]. Therefore, we return 14.
    }
}
