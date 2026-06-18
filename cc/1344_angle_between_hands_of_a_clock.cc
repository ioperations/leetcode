/**
 * Given two numbers, hour and minutes, return the smaller angle (in degrees)
 * formed between the hour and the minute hand.
 * Answers within 10-5 of the actual value will be accepted as correct.
 * 1 <= hour <= 12
 * 0 <= minutes <= 59
 */

#include <cstdlib>

namespace {

class Solution {
   public:
    double AngleClock(int hour, int minutes) {
        double angle = minutes * 1.0 / 60 * 360;
        double hour_angle = hour / 12.0 * 360 + minutes * 1.0 / 60 * (360 / 12);
        double t = std::abs(angle - hour_angle);
        if (t >= 180) {
            return 360 - t;
        }
        return t;
    }
};
}  // namespace
//
#include <gtest/gtest.h>

TEST(angleClock, t1) {
    int hour = 12, minutes = 30;
    double output = 165;
    Solution sl;
    double ret = sl.AngleClock(hour, minutes);
    EXPECT_NEAR(output, ret, 0.01);
}

TEST(angleClock, t2) {
    int hour = 3, minutes = 30;
    double output = 75;
    Solution sl;
    double ret = sl.AngleClock(hour, minutes);
    EXPECT_NEAR(output, ret, 0.01);
}

TEST(angleClock, t3) {
    int hour = 3, minutes = 15;
    double output = 7.5;
    Solution sl;
    double ret = sl.AngleClock(hour, minutes);
    EXPECT_NEAR(output, ret, 0.01);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
