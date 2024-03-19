// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {

class Solution {
   public:
    int MaxArea(std::vector<int> &height) {
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

    int MaxAreaV2(std::vector<int> &height) {
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

TEST(container_with_most_water, t1) {
    Solution s;
    std::vector<int> height{1, 1};
    int ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 1);
}

TEST(container_with_most_water, t2) {
    Solution s;
    std::vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    const int ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 49);
}

TEST(container_with_most_water_v2, t1) {
    Solution s;
    std::vector<int> height{1, 1};
    const int ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 1);
}

TEST(container_with_most_water_v2, t2) {
    Solution s;
    std::vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    const int ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 49);
}

}  // namespace
