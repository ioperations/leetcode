// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <iostream>
#include <string>

#include "gtest/gtest.h"

namespace {

/// FIXME: output the result to stdout
void Processing(std::string s) {
    // emit the first 0x
    std::string s2(s.begin() + 2, s.end());

    int ret = 0;

    for (auto &c : s2) {
        int cur = 0;
        if ('A' <= c && c <= 'F') {
            cur = 10 + c - 'A';
        } else if ('a' <= c && c <= 'f') {
            cur = 10 + c - 'a';
        } else if ('0' <= c && c <= '9') {
            cur = c - '0';
        }

        ret = ret * 16 + cur;
    }

    std::cout << ret << std::endl;
}

TEST(x_huawei_example_testv2, t2) {
    std::string s = "0xA";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("10\n"));
}

TEST(x_huawei_example_testv3, t2) {
    std::string s = "0xF";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("15\n"));
}

TEST(x_huawei_example_testv4, t1) {
    std::string s = "0xFF";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("255\n"));
}

TEST(x_huawei_example_test3, t2) {
    std::string s = "0xAA";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("170\n"));
}
}  // namespace
