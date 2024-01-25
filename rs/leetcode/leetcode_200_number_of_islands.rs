#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn num_of_is_lands_v2(map: &[Vec<i32>]) -> i32 {
        let col = map.len();
        let row = map[0].len();
        let mut visited = vec![vec![0; row]; col];
        let mut count = 0;
        for i in (0..col) {
            for j in (0..row) {
                if (map[i][j] == 1 && visited[i][j] == 0) {
                    Solution::dfs(map, &mut visited, i as i32, j as i32);
                    count += 1;
                }
            }
        }

        count
    }

    #[allow(unused)]
    fn num_of_is_lands(map: &[Vec<i32>]) -> i32 {
        let col = map.len();
        let row = map[0].len();
        let mut visited = vec![vec![0; row]; col];
        let mut count = 0;
        for i in (0..col) {
            for j in (0..row) {
                if (map[i][j] == 1 && visited[i][j] == 0) {
                    Solution::dfs_using_stack(
                        map,
                        &mut visited,
                        i as i32,
                        j as i32,
                    );
                    count += 1;
                }
            }
        }

        count
    }

    #[allow(unused)]
    fn dfs(map: &[Vec<i32>], visit: &mut [Vec<i32>], i: i32, j: i32) {
        if i < 0
            || j < 0
            || i >= (map.len() as i32)
            || j >= (map[0].len() as i32)
            || map[i as usize][j as usize] == 0
            || visit[i as usize][j as usize] == 1
        {
            return;
        }
        visit[i as usize][j as usize] = 1;
        Solution::dfs(map, visit, i + 1, j);
        Solution::dfs(map, visit, i - 1, j);
        Solution::dfs(map, visit, i, j - 1);
        Solution::dfs(map, visit, i, j + 1);
    }

    #[allow(unused)]
    fn dfs_using_stack(
        map: &[Vec<i32>],
        visit: &mut [Vec<i32>],
        i: i32,
        j: i32,
    ) {
        use std::collections::VecDeque;
        let mut queue = VecDeque::new();
        queue.push_back((i, j));
        while !queue.is_empty() {
            let (col, row) = queue.pop_front().unwrap();
            if col < 0
                || row < 0
                || col >= (map.len() as i32)
                || row >= (map[0].len() as i32)
                || map[col as usize][row as usize] == 0
                || visit[col as usize][row as usize] == 1
            {
                continue;
            }
            visit[col as usize][row as usize] = 1;
            queue.push_back((col + 1, row));
            queue.push_back((col - 1, row));

            queue.push_back((col, row - 1));
            queue.push_back((col, row + 1));
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;
    #[test]
    fn t1() {
        let map = vec![
            vec![1, 1, 0, 0, 0],
            vec![1, 1, 0, 0, 0],
            vec![0, 0, 1, 0, 0],
            vec![0, 0, 0, 1, 1],
        ];
        let ret = Solution::num_of_is_lands(&map);
        assert_eq!(3, ret);
    }

    #[test]
    fn t2() {
        let map = vec![
            vec![1, 0, 1, 0, 1],
            vec![1, 1, 0, 1, 0],
            vec![0, 1, 0, 0, 1],
            vec![0, 0, 0, 1, 0],
        ];
        let ret = Solution::num_of_is_lands(&map);
        assert_eq!(6, ret);
    }

    #[test]
    fn t3() {
        let map = vec![
            vec![1, 0, 1, 0, 1],
            vec![0, 1, 0, 1, 0],
            vec![1, 0, 1, 0, 1],
            vec![0, 1, 0, 1, 0],
        ];
        let ret = Solution::num_of_is_lands(&map);
        assert_eq!(10, ret);
    }
}

#[cfg(test)]
mod testdfs {
    use super::*;
    #[test]
    fn t1() {
        let map = vec![
            vec![1, 1, 0, 0, 0],
            vec![1, 1, 0, 0, 0],
            vec![0, 0, 1, 0, 0],
            vec![0, 0, 0, 1, 1],
        ];
        let ret = Solution::num_of_is_lands_v2(&map);
        assert_eq!(3, ret);
    }

    #[test]
    fn t2() {
        let map = vec![
            vec![1, 0, 1, 0, 1],
            vec![1, 1, 0, 1, 0],
            vec![0, 1, 0, 0, 1],
            vec![0, 0, 0, 1, 0],
        ];
        let ret = Solution::num_of_is_lands_v2(&map);
        assert_eq!(6, ret);
    }

    #[test]
    fn t3() {
        let map = vec![
            vec![1, 0, 1, 0, 1],
            vec![0, 1, 0, 1, 0],
            vec![1, 0, 1, 0, 1],
            vec![0, 1, 0, 1, 0],
        ];
        let ret = Solution::num_of_is_lands_v2(&map);
        assert_eq!(10, ret);
    }
}
