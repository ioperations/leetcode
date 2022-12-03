/*There are n different online courses numbered from 1 to n. You are given an
array courses where courses[i] = [durationi, lastDayi] indicate that the ith
course should be taken continuously for durationi days and must be finished
before or on lastDayi.

You will start on the 1st day and you cannot take two or more courses
simultaneously.

Return the maximum number of courses that you can take.*/
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

class Solution {
    bool static Comp(vector<int>& course1, vector<int>& course2) {
        return (course1[1] != course2[1]) ? (course1[1] < course2[1])
                                          : (course1[0] < course2[0]);
    }

   public:
    int ScheduleCourse(vector<vector<int>>& courses) {
        // sort it by last day, but if last day is same then sort it by duration
        sort(courses.begin(), courses.end(), Comp);

        // building Max Heap
        priority_queue<int> pq;
        int total_time = 0;

        for (auto course : courses) {
            // checking if we can can take the current course if, course
            // duration is less than course last day
            if (course[0] <= course[1]) {
                // checking current course can be complete withing the last day
                // or not
                if (total_time + course[0] <= course[1]) {
                    pq.push(course[0]);
                    total_time += course[0];
                } else {
                    // checking if we can remove the max time taken course
                    if (pq.top() > course[0]) {
                        total_time -= pq.top();
                        pq.pop();
                        total_time += course[0];
                        pq.push(course[0]);
                    }
                }
            }
        }
        return pq.size();
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<vector<int>> courses = {
        {100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
    int output = 3;
    Solution sl;
    int ret = sl.ScheduleCourse(courses);
    EXPECT_EQ(ret, output);
    // There are totally 4 courses, but you can take 3 courses at most:
    // First, take the 1st course, it costs 100 days so you will finish it on
    // the 100th day, and ready to take the next course on the 101st day.
    // Second, take the 3rd course, it costs 1000 days so you will finish it on
    // the 1100th day, and ready to take the next course on the 1101st day.
    // Third, take the 2nd course, it costs 200 days so you will finish it on
    // the 1300th day. The 4th course cannot be taken now, since you will finish
    // it on the 3300th day, which exceeds the closed date.
}

TEST(t0, t2) {
    std::vector<vector<int>> courses = {{1, 2}};
    int output = 1;
    Solution sl;
    int ret = sl.ScheduleCourse(courses);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    std::vector<vector<int>> courses = {{3, 2}, {4, 3}};
    int output = 0;
    Solution sl;
    int ret = sl.ScheduleCourse(courses);
    EXPECT_EQ(ret, output);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
