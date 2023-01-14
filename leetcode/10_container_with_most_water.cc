#include <algorithm>
#include <vector>
class Solution {
   public:
    int MaxArea(std::vector<int>& height) {
        int ret = 0;
        int i = 0;
        int j = height.size() - 1;
        for (; j > i;) {
            int het = std::min(height[i], height[j]);
            ret = std::max(ret, het * (j - i));
            if (height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return ret;
    }

    int MaxAreaV2(std::vector<int>& height) {
        int l = 0;
        int h = height.size() - 1;
        int max_area = 0;
        while (l < h) {
            int lh = height[l];
            int hh = height[h];
            max_area = std::max(max_area, (h - l) * std::min(lh, hh));
            if (lh < hh) {
                l++;
            } else {
                h--;
            }
        }
        return max_area;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t1) {
    Solution s;
    std::vector<int> height{1, 1};
    int ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 1);
}

TEST(t1, t2) {
    Solution s;
    std::vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    int ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 49);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
