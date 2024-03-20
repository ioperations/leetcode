// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {

class Solution {
   public:
    std::size_t MaxArea(std::vector<std::size_t > &height) {
        std::size_t ret = 0;
        std::size_t i = 0;
        std::size_t j = height.size() - 1;
        for (; j > i;) {
            std::size_t het = std::min(height[i], height[j]);
            ret = std::max(ret, het * (j - i));
            if (height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return ret;
    }

    std::size_t MaxAreaV2(std::vector<std::size_t> &height) {
        std::size_t l = 0;
        std::size_t h = height.size() - 1;
        std::size_t max_area = 0;
        while (l < h) {
            auto lh = height[l];
            auto hh = height[h];
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
    std::vector<std::size_t> height{1, 1};
    const std::size_t ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 1);
}

TEST(container_with_most_water, t2) {
    Solution s;
    std::vector<std::size_t> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    const std::size_t ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 49);
}

TEST(container_with_most_water_v2, t1) {
    Solution s;
    std::vector<std::size_t> height{1, 1};
    const auto ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 1);
}

TEST(container_with_most_water_v2, t2) {
    Solution s;
    std::vector<std::size_t> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    const auto ret = s.MaxAreaV2(height);
    EXPECT_EQ(ret, 49);
}

}  // namespace
