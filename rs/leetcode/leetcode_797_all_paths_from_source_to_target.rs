// Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1,
// find all possible paths from node 0 to node n - 1 and return them in any
// order.↳ The graph is given as follows: graph[i] is a list of all nodes
// you can visit from node i (i.e., there is a directed edge from node i to node
// graph[i][j]).

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    fn dfs(
        graph: &[Vec<i32>],
        node: i32,
        n: i32,
        path: &mut Vec<i32>,
        mut paths: Vec<Vec<i32>>,
    ) -> Vec<Vec<i32>> {
        path.push(node);

        if node == n {
            // We have reached the target. Append path to output
            paths.push(path.clone());
        } else {
            // Branch out to all children
            for child in &graph[node as usize] {
                paths = Self::dfs(graph, *child, n, path, paths);
            }
        }

        // backtrack
        path.pop();
        paths
    }

    #[allow(unused)]
    pub fn all_paths_source_target(graph: &[Vec<i32>]) -> Vec<Vec<i32>> {
        Self::dfs(graph, 0, (graph.len() - 1) as i32, &mut vec![], vec![])
    }
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use super::*;

    #[test]
    fn case1_test() {
        let graph = vec![vec![1, 2], vec![3], vec![3], vec![]];
        let output = vec![vec![0, 1, 3], vec![0, 2, 3]]
            .into_iter()
            .collect::<HashSet<Vec<i32>>>();
        // Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
        let ret: HashSet<Vec<i32>> = Solution::all_paths_source_target(&graph)
            .into_iter()
            .collect();
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let graph =
            vec![vec![4, 3, 1], vec![3, 2, 4], vec![3], vec![4], vec![]];
        let output = vec![
            vec![0, 4],
            vec![0, 3, 4],
            vec![0, 1, 3, 4],
            vec![0, 1, 2, 3, 4],
            vec![0, 1, 4],
        ]
        .into_iter()
        .collect::<HashSet<Vec<i32>>>();
        // Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
        let ret: HashSet<Vec<i32>> = Solution::all_paths_source_target(&graph)
            .into_iter()
            .collect();

        assert_eq!(ret, output);
    }
}
