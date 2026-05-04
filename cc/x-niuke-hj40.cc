// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <array>
#include <cstddef>
#include <iostream>
#include <string>

#include "gtest/gtest.h"

namespace {

enum class type {
    english_char = 0,
    space,
    number,
    others,
    length,
};

void Func(const char* s, int len) {
    std::array<int, static_cast<size_t>(type::length)> classfy{};
    classfy.fill(0);

    for (int i = 0; i < len; ++i) {
        char const c = s[static_cast<size_t>(i)];
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            classfy.at(static_cast<size_t>(type::english_char))++;
        } else if ('0' <= c && c <= '9') {
            classfy.at(static_cast<size_t>(type::number))++;
        } else if (' ' == c) {
            classfy.at(static_cast<size_t>(type::space))++;
        } else {
            classfy.at(static_cast<size_t>(type::others))++;
        }
    }

    for (const int i : classfy) {
        std::cout << i << '\n';
    }
}

TEST(XNiukeHjv2, t2) {
    std::string const s =
        R"(1qazxsw23 edcvfr45tgbn hy67uj m,ki89ol.\\/;p0-=\\][)";
    testing::internal::CaptureStdout();
    Func(s.c_str(), static_cast<int>(s.size()));
    std::string const result = testing::internal::GetCapturedStdout();
    std::string const expected("26\n3\n10\n12\n");
    EXPECT_EQ(result, expected);
}
}  // namespace
