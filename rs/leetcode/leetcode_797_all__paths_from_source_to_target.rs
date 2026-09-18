// Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, find
// all possible paths from node 0 to node n - 1 and return them in any order.
//
// The graph is given as follows: graph[i] is a list of all nodes you can visit
// from node i (i.e., there is a directed edge from node i to node graph[i][j]).
//
// n == graph.length
// 2 <= n <= 15
// 0 <= graph[i][j] < n
// graph[i][j] != i (i.e., there will be no self-loops).
// All the elements of graph[i] are unique.
// The input graph is guaranteed to be a DAG.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn all_paths_source_target(graph: &[Vec<i32>]) -> Vec<Vec<i32>> {
        fn dfs(
            graph: &[Vec<i32>],
            node: i32,
            target: i32,
            path: &mut Vec<i32>,
            result: &mut Vec<Vec<i32>>,
        ) {
            path.push(node);
            if node == target {
                result.push(path.clone());
            } else {
                for &next in &graph[node as usize] {
                    dfs(graph, next, target, path, result);
                }
            }
            path.pop();
        }

        let target = (graph.len() - 1) as i32;

        let mut result = Vec::new();
        dfs(graph, 0, target, &mut Vec::new(), &mut result);
        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let graph = vec![vec![1, 2], vec![3], vec![3], vec![]];
        let ret = Solution::all_paths_source_target(&graph);
        let output = vec![vec![0, 1, 3], vec![0, 2, 3]];
        assert_eq!(output, ret);
        // There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
    }

    #[test]
    fn case2_test() {
        let graph =
            vec![vec![4, 3, 1], vec![3, 2, 4], vec![3], vec![4], vec![]];
        let ret = Solution::all_paths_source_target(&graph);
        let output = vec![
            vec![0, 4],
            vec![0, 3, 4],
            vec![0, 1, 3, 4],
            vec![0, 1, 2, 3, 4],
            vec![0, 1, 4],
        ];
        assert_eq!(output, ret);
    }
}
