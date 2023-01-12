// You are given a tree (i.e. a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. The root of the tree is the node 0, and each node of the tree has a label which is a lower-case character given in the string labels (i.e. The node with the number i has the label labels[i]).
// The edges array is given on the form edges[i] = [ai, bi], which means there is an edge between nodes ai and bi in the tree.
// Return an array of size n where ans[i] is the number of nodes in the subtree of the ith node which have the same label as node i.
// A subtree of a tree T is the tree consisting of a node in T and all of its descendant nodes.

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn count_sub_trees(n: i32, edges: &[Vec<i32>], labels: &str) -> Vec<i32> {
        /*
         * 1 <= n <= 105
         * edges.length == n - 1
         * edges[i].length == 2
         * 0 <= ai, bi < n
         * ai != bi
         * labels.length == n
         * labels is consisting of only of lowercase English letters.
         */
        use std::collections::{HashMap, HashSet};

        fn dfs(
            map: &mut HashMap<usize, Vec<usize>>,
            labels: &str,
            x: usize,
            visited: &mut HashSet<usize>,
            ans: &mut Vec<i32>,
        ) -> [i32; 26] {
            let mut vec = [0; 26];
            if visited.insert(x) {
                for e in map.entry(x).or_default().clone() {
                    let v = dfs(map, labels, e, visited, ans);
                    for i in 0..26 {
                        vec[i] += v[i];
                    }
                }
                let ch = labels.as_bytes()[x];
                vec[(ch - b'a') as usize] += 1;
                ans[x] = vec[(ch - b'a') as usize];
            }
            vec
        }

        let mut map = HashMap::<usize, Vec<usize>>::new();
        for e in edges {
            map.entry(e[0] as usize).or_default().push(e[1] as usize);
            map.entry(e[1] as usize).or_default().push(e[0] as usize);
        }
        let mut visited = HashSet::<usize>::new();
        let mut ans = vec![0; n as usize];
        dfs(&mut map, labels, 0, &mut visited, &mut ans);
        ans
        // Self::count_sub_trees_clippy(n, &edges, &labels)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 7;
        let edges = [
            vec![0, 1],
            vec![0, 2],
            vec![1, 4],
            vec![1, 5],
            vec![2, 3],
            vec![2, 6],
        ];
        let labels = "abaedcd";
        let output = [2, 1, 1, 1, 1, 1, 1].to_vec();
        /*Explanation: Node 0 has label 'a' and its sub-tree has node 2 with label 'a' as well, thus the answer is 2. Notice that any node is part of its sub-tree.
        Node 1 has a label 'b'. The sub-tree of node 1 contains nodes 1,4 and 5, as nodes 4 and 5 have different labels than node 1, the answer is just 1 (the node itself).
        */
        let ret = Solution::count_sub_trees(n, &edges, labels);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let n = 4;
        let edges = [vec![0, 1], vec![1, 2], vec![0, 3]];
        let labels = "bbbb";
        let output = [4, 2, 1, 1].to_vec();
        /*
        The sub-tree of node 2 contains only node 2, so the answer is 1.
        The sub-tree of node 3 contains only node 3, so the answer is 1.
        The sub-tree of node 1 contains nodes 1 and 2, both have label 'b', thus the answer is 2.
        The sub-tree of node 0 contains nodes 0, 1, 2 and 3, all with label 'b', thus the answer is 4.
        */
        let ret = Solution::count_sub_trees(n, &edges, labels);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let n = 5;
        let edges = [vec![0, 1], vec![0, 2], vec![1, 3], vec![0, 4]];
        let labels = "aabab";
        let output = [3, 2, 1, 1, 1].to_vec();
        let ret = Solution::count_sub_trees(n, &edges, labels);
        assert_eq!(ret, output);
    }
}
