// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <stddef.h>
#include <queue>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

// leetcode-cn.com/problems/course-schedule/solution/c-you-xiang-tu-cheng-huan-jian-ce-by-hank-31/
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    bool CanFinish(int num_courses, vector<vector<int>> &prerequisites) {
        // 记录顶点入度
        vector<int> indegree(num_courses, 0);
        // 邻接表
        vector<vector<int>> adjacency_list(num_courses, vector<int>());
        int len = prerequisites.size();
        // 计算所有的顶点的入度值
        for (int i = 0; i < len; i++) {
            vector<int> &item = prerequisites[i];
            int cur_course = item[0];
            int pre_course = item[1];
            // 计算入度
            indegree[pre_course]++;
            // 构造邻接表
            adjacency_list[cur_course].push_back(pre_course);
        }

        // 将所有入度为0的顶点入队列
        queue<int> course_queue;
        for (int i = 0; i < num_courses; i++) {
            if (indegree[i] == 0) {
                course_queue.push(i);
            }
        }

        int count = 0;  // 记录访问过的顶点数
        // 拓扑排序遍历顶点
        while (!course_queue.empty()) {
            int point = course_queue.front();
            course_queue.pop();
            count++;
            // 从邻接表里面访问，把从该顶点出发所能到达人顶点的入度减一
            for (size_t i = 0; i < adjacency_list[point].size(); i++) {
                int pre_course = adjacency_list[point][i];
                indegree[pre_course]--;
                // 入度为0则加入队列
                if (indegree[pre_course] == 0) {
                    course_queue.push(pre_course);
                }
            }
        }

        // 如果遍历完还有顶点没有访问到，说明该有向图有环
        return count == num_courses;
    }
};



TEST(t0, t1) {
    // numCourses = 2, prerequisites = [[1,0],[0,1]]
    // 输出：false
    // 解释：总共有 2 门课程。学习课程 1
    // 之前，你需要先完成课程 0 ；并且学习课程 0
    // 之前，你还应先完成课程 1 。这是不可能的。

    std::vector<std::vector<int>> v{{1, 0}, {0, 1}};

    Solution s;
    bool ret = s.CanFinish(2, v);
    EXPECT_EQ(ret, false);
}

TEST(t0, t2) {
    // numCourses = 2, prerequisites = [[1,0]]
    // 输出：true
    // 解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
    std::vector<std::vector<int>> v{{1, 0}};

    Solution s;
    bool ret = s.CanFinish(2, v);
    EXPECT_EQ(ret, true);
}

}
