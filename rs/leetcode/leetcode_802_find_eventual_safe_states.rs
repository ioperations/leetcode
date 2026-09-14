// There is a directed graph of n nodes with each node labeled from 0 to n - 1.
// The graph is represented by a 0-indexed 2D integer array graph where graph[i]
// is an integer array of nodes adjacent to node i, meaning there is an edge
// from node i to each node in graph[i].
//
// A node is a terminal node if there are no outgoing edges. A node is a safe
// node if every possible path starting from that node leads to a terminal node
// (or another safe node).
//
// Return an array containing all the safe nodes of the graph. The answer should
// be sorted in ascending order.

// n == graph.length
// 1 <= n <= 104
// 0 <= graph[i].length <= n
// 0 <= graph[i][j] <= n - 1
// graph[i] is sorted in a strictly increasing order.
// The graph may contain self-loops.
// The number of edges in the graph will be in the range [1, 4 * 104].

use std::collections::HashMap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn eventual_safe_nodes(graph: &[Vec<i32>]) -> Vec<i32> {
        fn is_safe(
            hm: &mut HashMap<i32, bool>,
            graph: &[Vec<i32>],
            i: i32,
        ) -> bool {
            if let Some(&v) = hm.get(&i) {
                return v;
            }

            hm.insert(i, false);

            for &v in &graph[i as usize] {
                if !is_safe(&mut *hm, graph, v) {
                    return false;
                }
            }

            hm.insert(i, true);
            true
        }

        let len = graph.len();
        let mut hm: HashMap<i32, bool> = HashMap::new();
        let mut ret = Vec::new();

        for i in 0..len {
            if is_safe(&mut hm, graph, i as i32) {
                ret.push(i as i32);
            }
        }

        ret.sort_unstable();
        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let graph = vec![
            vec![1, 2],
            vec![2, 3],
            vec![5],
            vec![0],
            vec![5],
            vec![],
            vec![],
        ];
        let output = vec![2, 4, 5, 6];
        let ret = Solution::eventual_safe_nodes(&graph);
        assert_eq!(output, ret);
        //  The given graph is shown above.
        // Nodes 5 and 6 are terminal nodes as there are no outgoing edges from
        // either of them. Every path starting at nodes 2, 4, 5, and 6
        // all lead to either node 5 or 6.
    }

    #[test]
    fn case2_test() {
        let graph =
            vec![vec![1, 2, 3, 4], vec![1, 2], vec![3, 4], vec![0, 4], vec![]];
        let output = vec![4];
        let ret = Solution::eventual_safe_nodes(&graph);
        assert_eq!(output, ret);
        // Only node 4 is a terminal node, and every path starting at node 4
        // leads to node 4.
    }
}
