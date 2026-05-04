// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace {

void Processing(std::vector<int> const & nums) {
    int max = std::numeric_limits<int>::min();
    for (const auto& ret : nums) {
        max = std::max(max, ret);
    }

    std::vector<int> dp(max + 1, -1);

    std::function<int(int)> dp_fun = [&dp_fun, &dp](const int nums) -> int {
        if (nums == 0 || nums == 1) {
            return 0;
        }
        if (nums == 2) {
            return 1;
        }

        if (dp.at(nums) != -1) {
            return dp.at(nums);
        }

        dp.at(nums) = nums / 3 + dp_fun(nums / 3 + nums % 3);
        return dp.at(nums);
    };

    for (const auto& pingzi : nums) {
        std::cout << dp_fun(pingzi) << '\n';
    }
}

TEST(XHuaweiExampleTestv2, t2) {
    std::vector<int> const s{3, 10, 81};
    testing::internal::CaptureStdout();
    Processing(s);
    std::string const ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("1\n5\n40\n"));
}
}  // namespace
