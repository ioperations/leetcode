// There are n cities. Some of them are connected, while some are not. If city a
// is connected directly with city b, and city b is connected directly with city
// c, then city a is connected indirectly with city c.
//
// A province is a group of directly or indirectly connected cities and no other
// cities outside of the group.
//
// You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the
// ith city and the jth city are directly connected, and isConnected[i][j] = 0
// otherwise.
//
// Return the total number of provinces.
//
//
// 1 <= n <= 200
// n == isConnected.length
// n == isConnected[i].length
// isConnected[i][j] is 1 or 0.
// isConnected[i][i] == 1
// isConnected[i][j] == isConnected[j][i]

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_circle_num(is_connected: &[Vec<i32>]) -> i32 {
        let mut v = vec![];
        let len = is_connected.len();
        (0..len).for_each(|i| {
            v.push(i);
        });

        for i in 0..len {
            for j in (i + 1)..len {
                if is_connected[i][j] == 1 {
                    Self::update(&mut v, i, j);
                }
            }
        }

        v.iter().enumerate().fold(0, |acc, i| {
            if i.0 == *i.1 {
                return acc + 1;
            }
            acc
        })
    }

    #[allow(unused)]
    fn find(v: &mut Vec<usize>, x: usize) -> usize {
        if v[x] != x {
            v[x] = Self::find(v, v[x]);
        }
        v[x]
    }

    #[allow(unused)]
    fn update(v: &mut Vec<usize>, i: usize, j: usize) {
        let root_i = Self::find(v, i);
        let root_j = Self::find(v, j);
        if root_i != root_j {
            v[root_j] = root_i;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let is_connected = [[1, 1, 0], [1, 1, 0], [0, 0, 1]]
            .iter()
            .map(|v| v.into())
            .collect::<Vec<_>>();

        let output = 2;
        let ret = Solution::find_circle_num(&is_connected);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let is_connected = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
            .iter()
            .map(|v| v.into())
            .collect::<Vec<_>>();

        let output = 3;
        let ret = Solution::find_circle_num(&is_connected);
        assert_eq!(output, ret);
    }

    #[test]
    fn case3_test() {
        let is_connected =
            [[1, 0, 0, 1], [0, 1, 1, 0], [0, 1, 1, 1], [1, 0, 1, 1]]
                .iter()
                .map(|v| v.into())
                .collect::<Vec<_>>();
        // [1, 0, 0, 1],
        // [0, 1, 1, 0],
        // [0, 1, 1, 1],
        // [1, 0, 1, 1]

        let output = 1;
        let ret = Solution::find_circle_num(&is_connected);
        assert_eq!(output, ret);
    }
}
