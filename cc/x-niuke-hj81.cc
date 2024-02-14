// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <iterator>
#include <string>

#include "gtest/gtest.h"

namespace {

void Func(std::string &less, std::string &more) {
    bool t = true;
    std::map<int, char> less_set{};
    for (size_t i = 0; i < less.size(); ++i) {
        less_set.emplace(i, less[i]);
    }

    for (size_t i = 0; i < less_set.size(); ++i) {
        auto z = std::find_if(
            more.begin(), more.end(),
            [&less_set, &i](const char &c) { return c == less_set[i]; });
        if (z == std::end(more)) {
            t = false;
            break;
        }
    }

    std::cout << (t ? "true" : "false") << std::endl;
}

TEST(t1, t2) {
    testing::internal::CaptureStdout();
    std::string le("bc");
    std::string more("abc");
    Func(le, more);
    std::string out = testing::internal::GetCapturedStdout();
    std::string expected = "true\n";
    EXPECT_EQ(out, expected);
}

TEST(t1, t3) {
    testing::internal::CaptureStdout();
    std::string le("bd");
    std::string more("abc");
    Func(le, more);
    std::string out = testing::internal::GetCapturedStdout();
    std::string expected = "false\n";
    EXPECT_EQ(out, expected);
}

}  // namespace
