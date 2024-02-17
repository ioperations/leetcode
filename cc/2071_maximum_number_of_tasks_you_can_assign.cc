// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You have n tasks and m workers. Each task has a strength requirement stored
    in a 0-indexed integer array tasks, with the ith task requiring tasks[i]
    strength to complete. The strength of each worker is stored in a 0-indexed
    integer array workers, with the jth worker having workers[j] strength. Each
    worker can only be assigned to a single task and must have a strength
   greater than or equal to the task's strength requirement (i.e., workers[j] >=
   tasks[i]).

    Additionally, you have pills magical pills that will increase a worker's
    strength by strength. You can decide which workers receive the magical
   pills, however, you may only give each worker at most one magical pill.

    Given the 0-indexed integer arrays tasks and workers and the integers pills
   and strength, return the maximum number of tasks that can be completed.

*/

#include <algorithm>
#include <queue>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace { 
class Solution {
   public:
    int MaxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills,
                      int strength) {
        /*
            n == tasks.length
            m == workers.length
            1 <= n, m <= 5 * 104
            0 <= pills <= m
            0 <= tasks[i], workers[j], strength <= 109
        */
        // Sort in descending order, could sort in ascending. Would just need to
        // change loop iteration direction
        sort(tasks.begin(), tasks.end(),
             [](int lhs, int rhs) { return lhs > rhs; });
        sort(workers.begin(), workers.end(),
             [](int lhs, int rhs) { return lhs > rhs; });

        int t = 0;   // Current task we are assessing
        int w = 0;   // Current worker we are checking
        int wp = 0;  // Weakest worker than can complete task with a pill

        int completed_tasks = 0;  // Final output
        bool b_search_down =
            true;  // When false, we've  hit the point that all workers can
                   // complete remaining tasks with a pill?

        priority_queue<int> workers_q;  // Workers than have a task assigned to
                                        // them, but can only complete with a
                                        // pill. Needs to be in descending order

        while (t < (int)tasks.size()) {
            while (w < (int)workers.size() && workers[w] == -1)
                w++;  // Find next worker that has not already been processed

            if (w >= (int)workers
                         .size())  // If we've run out of workers, look to see
                                   // if any in the queue can solve the task.
            {
                if (!workers_q.empty() && workers_q.top() > tasks[t]) {
                    workers_q.pop();
                    completed_tasks++;
                }
            } else if (workers[w] >=
                       tasks[t])  // If the current worker can solve the task
                                  // without a pill, use her.
            {
                workers[w] = -1;
                w++;
                completed_tasks++;
            } else {
                if (b_search_down)  // Find the lowest strength worker that can
                                    // solve the task with a pill
                {
                    // Find first worker that can't do task with pill
                    while (wp < (int)workers.size() &&
                           (workers[wp] == -1 ||
                            workers[wp] + strength >= tasks[t])) {
                        wp++;
                    }

                    // All tasks can now be completed by all workers with pill
                    if (wp == (int)workers.size()) {
                        b_search_down = false;
                        wp = workers.size() - 1;
                    }
                }

                // Iterate up till we find a worker that has not been processed
                // and can complete the task. Should be the next valid worker.
                while (wp >= (int)workers.size() ||
                       (wp > w && (workers[wp] == -1 ||
                                   workers[wp] + strength < tasks[t]))) {
                    wp--;
                }

                // If we have equal or more workers assigned to the queue than
                // pills, see if we can pull one out to finish this task
                if ((int)workers_q.size() >= pills && !workers_q.empty() &&
                    workers_q.top() >= tasks[t]) {
                    completed_tasks++;
                    workers_q.pop();
                }
                // Can wp worker finish the task?
                else if (workers[wp] + strength >= tasks[t]) {
                    workers_q.push(workers[wp]);
                    workers[wp] = -1;
                    wp += b_search_down ? -1 : 1;
                }
                // Even if we haven't filled queue, check to see if a worker can
                // finish a task without a pill (task would be wasted otherwise)
                else if (!workers_q.empty() && workers_q.top() >= tasks[t]) {
                    completed_tasks++;
                    workers_q.pop();
                }
            }

            t++;  // Processed one task
            wp =
                max(wp, w);  // If ever WP becomes greater than w, clamp it to w
        }

        return completed_tasks +
               min((int)workers_q.size(),
                   pills);  // Return number of completed tasks + number of
                            // workers in queue (i.e. number of workers than can
                            // complete a task with a pill.)
        return 0;
    }
};



TEST(t0, t1) {
    std::vector<int> tasks = {3, 2, 1}, workers = {0, 3, 3};
    int pills = 1, strength = 1;
    int output = 3;
    Solution sl;
    int ret = sl.MaxTaskAssign(tasks, workers, pills, strength);
    EXPECT_EQ(ret, output);
    // Explanation:
    // We can assign the magical pill and tasks as follows:
    // - Give the magical pill to worker 0.
    // - Assign worker 0 to task 2 (0 + 1 >= 1)
    // - Assign worker 1 to task 1 (3 >= 2)
    // - Assign worker 2 to task 0 (3 >= 3)
}

TEST(t0, t2) {
    std::vector<int> tasks = {5, 4}, workers = {0, 0, 0};
    int pills = 1, strength = 5;
    int output = 1;
    Solution sl;
    int ret = sl.MaxTaskAssign(tasks, workers, pills, strength);
    EXPECT_EQ(ret, output);
    /*
        We can assign the magical pill and tasks as follows:
        - Give the magical pill to worker 0.
        - Assign worker 0 to task 0 (0 + 5 >= 5)
    */
}

TEST(t0, t3) {
    std::vector<int> tasks = {10, 15, 30}, workers = {0, 10, 10, 10, 10};
    int pills = 3, strength = 10;
    int output = 2;
    Solution sl;
    int ret = sl.MaxTaskAssign(tasks, workers, pills, strength);
    EXPECT_EQ(ret, output);
    /*
        We can assign the magical pills and tasks as follows:
        - Give the magical pill to worker 0 and worker 1.
        - Assign worker 0 to task 0 (0 + 10 >= 10)
        - Assign worker 1 to task 1 (10 + 10 >= 15)
        The last pill is not given because it will not make any worker strong
       enough for the last task.
    */
}

}
