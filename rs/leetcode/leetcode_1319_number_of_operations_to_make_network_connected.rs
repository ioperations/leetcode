// There are n computers numbered from 0 to n - 1 connected by ethernet cables
// connections forming a network where connections[i] = [ai, bi] represents a
// connection between computers ai and bi. Any computer can reach any other
// computer directly or indirectly through the network.
//
// You are given an initial computer network connections. You can extract
// certain cables between two directly connected computers, and place them
// between any pair of disconnected computers to make them directly connected.
//
// Return the minimum number of times you need to do this in order to make all
// the computers connected. If it is not possible, return -1.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn make_connected(n: i32, connections: Vec<Vec<i32>>) -> i32 {
        let n = n as usize;

        if connections.len() < n - 1 {
            return -1;
        }

        let mut uf: Vec<_> = (0..n).collect();

        for con in connections {
            Self::join(con[0] as usize, con[1] as usize, &mut uf);
        }

        let mut count = 0;
        for i in 0..n {
            if Self::find(i, &mut uf) == i {
                count += 1;
            }
        }
        count - 1
    }

    #[allow(unused)]
    fn join(i: usize, j: usize, uf: &mut [usize]) {
        let i = Self::find(i, uf);
        let j = Self::find(j, uf);
        if i < j {
            uf[j] = i;
        } else {
            uf[i] = j;
        }
    }

    #[allow(unused)]
    fn find(i: usize, uf: &mut [usize]) -> usize {
        if uf[i] != i {
            uf[i] = Self::find(uf[i], uf);
        }
        uf[i]
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 4;
        let connections = [vec![0, 1], vec![0, 2], vec![1, 2]];
        let output = 1;
        let ret = Solution::make_connected(n, connections.into());
        assert_eq!(ret, output);
        // Explanation: Remove cable between computer 1 and 2 and place between
        // computers 1 and 3.
    }

    #[test]
    fn case2_test() {
        let n = 6;
        let connections =
            [vec![0, 1], vec![0, 2], vec![0, 3], vec![1, 2], vec![1, 3]];
        let output = 2;
        let ret = Solution::make_connected(n, connections.into());
        assert_eq!(ret, output);
        // Explanation: Remove cable between computer 1 and 2 and place between
        // computers 1 and 3.
    }

    #[test]
    fn case3_test() {
        let n = 6;
        let connections = [vec![0, 1], vec![0, 2], vec![0, 3], vec![1, 2]];
        let output = -1;
        let ret = Solution::make_connected(n, connections.into());
        assert_eq!(ret, output);
        // There are not enough cables.
    }
}
