
#include <gtest/gtest.h>

#include <vector>

#include "for_each.hh"

TEST(for_each, basic_test) {
    std::vector<std::vector<std::vector<int>>> v{{{1}, {2, 3}}, {{4, 5, 6}}};

    DfsForEach(v, [&](int& v) { v += 100; });

    std::vector<int> flattern;
    DfsForEach(v, [&](int v) { flattern.push_back(v); });

    const std::vector<int> expected{101, 102, 103, 104, 105, 106};
    EXPECT_EQ(flattern, expected);
}
