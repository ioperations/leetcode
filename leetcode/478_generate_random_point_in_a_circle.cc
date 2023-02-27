/*
Given the radius and the position of the center of a circle, implement the
function randPoint which generates a uniform random point inside the circle.

Implement the Solution class:

Solution(double radius, double x_center, double y_center) initializes the object
with the radius of the circle radius and the position of the center (x_center,
y_center). randPoint() returns a random point inside the circle. A point on the
circumference of the circle is considered to be in the circle. The answer is
returned as an array [x, y].
*/

#include <climits>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution {
    double x_center;
    double y_center;
    double radius;

   public:
    Solution(double rad, double cx_center, double cy_center) {
        radius = rad;
        x_center = cx_center;
        y_center = cy_center;
    }

    double Random() { return 1.0 * rand() / RAND_MAX; }

    vector<double> RandPoint() {
        double length = sqrt(Random()) * radius;
        double angle = Random() * 2 * M_PI;
        double x_rand = x_center + length * cos(angle),
               y_rand = y_center + length * sin(angle);
        return {x_rand, y_rand};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    Solution sl(1.0, 0.0, 0.0);
    vector<double> t1;
    t1 = sl.RandPoint();  // return [-0.02493, -0.38077]
    t1 = sl.RandPoint();  // return [0.82314, 0.38945]
    t1 = sl.RandPoint();  // return [0.36572, 0.17248]
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
