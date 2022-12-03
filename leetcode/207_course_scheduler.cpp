/*
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/course-schedule
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中
prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

    例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。

请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。


输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。
学习课程 1 之前，你需要先完成课程 0 ；
并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。

*/

#include <vector>

class Solution {
   public:
    bool CanFinish(int num_courses,
                   std::vector<std::vector<int>>& prerequisites) {
        return true;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    Solution s;
    const int num_courses = 2;
    std::vector<std::vector<int>> input{{1, 0}};

    bool ret = s.CanFinish(num_courses, input);

    EXPECT_EQ(ret, true);
}

TEST(t0, t2) {
    Solution s;
    const int num_courses = 2;
    std::vector<std::vector<int>> input{{1, 0}, {0, 1}};

    bool ret = s.CanFinish(num_courses, input);

    EXPECT_EQ(ret, false);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
