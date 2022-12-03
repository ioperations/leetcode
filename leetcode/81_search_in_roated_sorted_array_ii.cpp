/*
 num[] roated in k index  , given a target , return true if it in array or false
*/

#include <vector>
class Solution {
   public:
    bool Search(std::vector<int>& v, int target) {
        // pass
        return true;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> nums = {2, 5, 6, 0, 0, 1, 2};
    int target = 0;
    Solution s;
    bool ret = s.Search(nums, target);
    EXPECT_EQ(ret, true);
}

TEST(t0, t2) {
    std::vector<int> nums = {2, 5, 6, 0, 0, 1, 2};
    int target = 3;
    Solution s;
    bool ret = s.Search(nums, target);
    EXPECT_EQ(ret, false);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

