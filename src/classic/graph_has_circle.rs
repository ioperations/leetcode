#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn can_finish(num_courses: i32, prerequisites: &[Vec<i32>]) -> bool {
        use std::collections::VecDeque;
        let num_courses = num_courses as usize;

        // 记录顶点入度
        let mut indegress = vec![0; num_courses];
        // 邻接表
        let mut adjacency_list: Vec<Vec<i32>> = vec![vec![]; num_courses];
        let len = prerequisites.len();

        for item in prerequisites.iter().take(len) {
            let cur_course = item[0];
            let pre_course = item[1];
            // 计算入度
            indegress[pre_course as usize] += 1;
            // 构造邻接表
            adjacency_list[cur_course as usize].push(pre_course);
        }

        let mut que = VecDeque::new();

        // 将所有入度为0的顶点入队列
        for (i, &indegress_is_zero) in
            indegress.iter().enumerate().take(num_courses)
        {
            if indegress_is_zero == 0 {
                que.push_back(i);
            }
        }

        // 记录访问过的顶点数
        let mut count = 0;
        // 拓扑排序遍历顶点
        while !que.is_empty() {
            let point = que.pop_front().unwrap();
            count += 1;

            // 从邻接表里面访问，把从该顶点出发所能到达人顶点的入度减一
            for i in (0..adjacency_list[point].len()) {
                let pre_course = adjacency_list[point][i] as usize;
                indegress[pre_course] -= 1;
                // 入度为0则加入队列
                if indegress[pre_course] == 0 {
                    que.push_back(pre_course);
                }
            }
        }
        // 如果遍历完还有顶点没有访问到，说明该有向图有环
        count == num_courses
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let v = [vec![1, 0], vec![0, 1]];
        let ret = Solution::can_finish(2, &v);
        assert!(!ret);
    }

    #[test]
    fn case2_test() {
        let v = [vec![1, 0]];
        let ret = Solution::can_finish(2, &v);
        assert!(ret);
    }
}
