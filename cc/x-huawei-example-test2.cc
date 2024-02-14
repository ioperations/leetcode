// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include <string>

#include "gtest/gtest.h"

namespace {

/// FIXME: output the result to stdout
void Processing(std::vector<int> &nums) {
    std::set<int> s(nums.begin(), nums.end());
    std::vector<int> ss(s.begin(), s.end());

    std::sort(ss.begin(), ss.end(), std::less<int>());

    for (auto &s : ss) {
        std::cout << s << std::endl;
    }
}

TEST(t1, t2) {
    std::vector<int> t{1, 2, 4, 5, 5, 6, 6, 7, 7, 7, 3};
    testing::internal::CaptureStdout();
    Processing(t);
    std::string s = testing::internal::GetCapturedStdout();

    EXPECT_EQ(s, std::string("1\n2\n3\n4\n5\n6\n7\n"));
}
}  // namespace
