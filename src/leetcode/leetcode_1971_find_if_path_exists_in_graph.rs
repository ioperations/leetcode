/*There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
You want to determine if there is a valid path that exists from vertex source to vertex destination.
Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.
*/
#[allow(unused)]
struct Solution;

use std::collections::{HashSet, VecDeque};
impl Solution {
    #[allow(unused)]
    pub fn valid_path(n: i32, edges: &[Vec<i32>], start: i32, end: i32) -> bool {
        let graph: Vec<HashSet<usize>> = {
            let mut tmp: Vec<HashSet<usize>> = vec![HashSet::new(); n as usize];
            for edge in edges {
                let u = edge[0] as usize;
                let v = edge[1] as usize;

                tmp[u].insert(v);
                tmp[v].insert(u);
            }
            tmp
        };
        let mut queue: VecDeque<usize> = VecDeque::with_capacity(n as usize);
        queue.push_back(start as usize);
        let mut seen: HashSet<usize> = HashSet::new();
        seen.insert(start as usize);

        while !queue.is_empty() {
            let size = queue.len();

            for _ in 0..size {
                if let Some(cur) = queue.pop_front() {
                    if cur == end as usize {
                        return true;
                    }

                    for &next in &graph[cur] {
                        if seen.insert(next) {
                            queue.push_back(next);
                        }
                    }
                }
            }
        }

        false
    }
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 3;
        let edges = vec![vec![0, 1], vec![1, 2], vec![2, 0]];
        let source = 0;
        let destination = 2;
        let output = true;
        let ret = Solution::valid_path(n, &edges, source, destination);
        /*
         * There are two paths from vertex 0 to vertex 2:
         * - 0 → 1 → 2
         * - 0 → 2
         */
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let n = 6;
        let edges = vec![vec![0, 1], vec![0, 2], vec![3, 5], vec![5, 4], vec![4, 3]];
        let source = 0;
        let destination = 5;
        let output = false;
        let ret = Solution::valid_path(n, &edges, source, destination);
        // There is no path from vertex 0 to vertex 5.
        assert_eq!(ret, output);
    }
}
