// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*There is a special square room with mirrors on each of the four walls. Except
for the southwest corner, there are receptors on each of the remaining corners,
numbered 0, 1, and 2.

The square room has walls of length p and a laser ray from the southwest corner
first meets the east wall at a distance q from the 0th receptor.

Given the two integers p and q, return the number of the receptor that the ray
meets first.

The test cases are guaranteed so that the ray will meet a receptor eventually.*/
#include <vector>

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    int MirrorReflection(int p, int q) {
        // Divide p,q by 2 until at least one odd.
        while ((p % 2 == 0) && (q % 2 == 0)) {
            p /= 2;
            q /= 2;
        }
        // both p qnd q can't be even
        if ((p % 2) == 0 && (q % 2) != 0) {
            return 2;  // when p is even and q is odd
        }
        if ((p % 2) != 0 && (q % 2) != 0) {
            return 1;  // when p is odd and q is odd
        }
        return 0;  // when p is odd and q is even
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int p = 2, q = 1;
    int output = 2;
    // Explanation: The ray meets receptor 2 the first time it gets reflected
    // back to the left wall
    Solution sl;

    int ret = sl.MirrorReflection(p, q);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int p = 3, q = 1;
    int output = 1;
    Solution sl;

    int ret = sl.MirrorReflection(p, q);
    EXPECT_EQ(ret, output);
}

}
