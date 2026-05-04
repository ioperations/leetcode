// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <cstddef>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

#include "gtest/gtest.h"

namespace {

void Func(const std::string& less, const std::string& more) {
    bool t = true;
    std::map<int, char> less_set{};
    for (size_t i = 0; i < less.size(); ++i) {
        less_set.emplace(static_cast<int>(i), less.at(i));
    }

    int const less_set_size = static_cast<int>(less_set.size());
    for (int i = 0; i < less_set_size; ++i) {
        auto z = std::find_if(
            more.begin(), more.end(),
            [target = less_set.at(i)](const char& c) { return c == target; });
        if (z == std::end(more)) {
            t = false;
            break;
        }
    }

    std::cout << (t ? "true" : "false") << '\n';
}

TEST(XNiukeHjv2, t2) {
    testing::internal::CaptureStdout();
    std::string le("bc");
    std::string more("abc");
    Func(le, more);
    std::string const out = testing::internal::GetCapturedStdout();
    std::string const expected = "true\n";
    EXPECT_EQ(out, expected);
}

TEST(XNiukeHjv2, t3) {
    testing::internal::CaptureStdout();
    std::string le("bd");
    std::string more("abc");
    Func(le, more);
    std::string const out = testing::internal::GetCapturedStdout();
    std::string const expected = "false\n";
    EXPECT_EQ(out, expected);
}

}  // namespace
