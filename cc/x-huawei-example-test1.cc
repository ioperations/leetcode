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

/// FIXME: output the result to stdout
void Processing(std::vector<int> nums) {
    // find the max
    int max = std::numeric_limits<int>::min();
    for (auto& ret : nums) {
        max = std::max(max, ret);
    }
    int* dp = new int[max + 1];

    for (int i = 0; i <= max; ++i) {
        *(dp + i) = -1;
    }

    // establish dp array for the whole vector once
    std::function<int(int)> dp_fun = [&dp_fun, &dp](const int nums) -> int {
        if (nums == 0 || nums == 1) {
            return 0;
        }
        if (nums == 2) {
            // 借一瓶 得到三瓶 到时候还一瓶
            return 1;
        }

        if (*(dp + nums) != -1) {
            return *(dp + nums);
        }

        *(dp + nums) = nums / 3 + dp_fun(nums / 3 + nums % 3);
        return *(dp + nums);
    };

    // get value per nums
    for (auto& pingzi : nums) {
        std::cout << dp_fun(pingzi) << std::endl;
    }

    // dealloc the memory
    delete[] dp;
    return;
}

TEST(x_huawei_example_testv2, t2) {
  std::vector<int> const s{3, 10, 81};
  testing::internal::CaptureStdout();
  Processing(s);
  std::string const ret = testing::internal::GetCapturedStdout();

  EXPECT_EQ(ret, std::string("1\n5\n40\n"));
}
}  // namespace
