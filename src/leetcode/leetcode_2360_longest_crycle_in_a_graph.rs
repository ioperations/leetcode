// You are given a directed graph of n nodes numbered from 0 to n - 1, where
// each node has at most one outgoing edge.
//
// The graph is represented with a given 0-indexed array edges of size n,
// indicating that there is a directed edge from node i to node edges[i]. If
// there is no outgoing edge from node i, then edges[i] == -1.
//
// Return the length of the longest cycle in the graph. If no cycle exists,
// return -1.
//
// A cycle is a path that starts and ends at the same node.

#[allow(unused)]
struct Solution;

impl Solution {
    const NOT_VISITED: u8 = 0;
    const VISITING: u8 = 1;
    const VISITED: u8 = 2;
    const NOT_CYCLIC: i32 = -1;

    #[allow(unused)]
    pub fn longest_cycle(edges: &[i32]) -> i32 {
        let len_vs: usize = edges.len();
        let mut visited: Vec<u8> = vec![Self::NOT_VISITED; len_vs];
        let mut path: Vec<usize> = vec![0; len_vs];
        let mut longest: i32 = Self::NOT_CYCLIC;
        for vertex in 0..len_vs {
            if visited[vertex] == Self::NOT_VISITED {
                let len = Self::dfs(vertex, &mut visited, &mut path, edges);
                longest = std::cmp::max(longest, len);
            }
        }
        longest
    }

    #[allow(unused)]
    fn dfs(
        cur: usize,
        visited: &mut Vec<u8>,
        path: &mut Vec<usize>,
        edges: &[i32],
    ) -> i32 {
        if visited[cur] == Self::VISITING {
            // to construct the cycle
            let mut len: i32 = 1;
            let mut c = cur;
            while path[c] != cur {
                c = path[c];
                len += 1;
            }
            return len;
        }
        if visited[cur] == Self::VISITED {
            return Self::NOT_CYCLIC;
        }
        visited[cur] = Self::VISITING;
        if edges[cur] == -1 {
            visited[cur] = Self::VISITED;
            return Self::NOT_CYCLIC;
        }
        let nxt: usize = edges[cur] as usize;
        path[nxt] = cur;
        let len = Self::dfs(nxt, visited, path, edges);
        visited[cur] = Self::VISITED;
        path[nxt] = 0;
        len
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let edges = [3, 3, 4, 2, 3];
        let output = 3;

        let ret = Solution::longest_cycle(&edges);
        assert_eq!(ret, output);
        // Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3
        // -> 2. The length of this cycle is 3, so 3 is returned.
    }

    #[test]
    fn case2_test() {
        let edges = [2, -1, 3, 1];
        let output = -1;

        let ret = Solution::longest_cycle(&edges);
        assert_eq!(ret, output);
        // There are no cycles in this graph.
    }
}
