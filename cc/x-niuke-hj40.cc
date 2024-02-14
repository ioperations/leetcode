// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <iostream>
#include <string>

#include "gtest/gtest.h"

namespace {

enum type {
    ENGLISH_CHAR = 0,
    SPACE,
    NUMBER,
    OTHERS,
    LENGTH,
};

void Func(const char *s, int len) {
    int classfy[type::LENGTH] = {0};

    for (int i = 0; i < len; ++i) {
        if (('a' <= *(s + i) && *(s + i) <= 'z') ||
            ('A' <= *(s + i) && *(s + i) <= 'Z')) {
            classfy[type::ENGLISH_CHAR]++;
        } else if ('0' <= *(s + i) && *(s + i) <= '9') {
            classfy[type::NUMBER]++;
        } else if (' ' == *(s + i)) {
            classfy[type::SPACE]++;
        } else {
            classfy[type::OTHERS]++;
        }
    }

    for (int i = 0; i < type::LENGTH; ++i) {
        std::cout << classfy[i] << std::endl;
    }
}

TEST(t1, t2) {
    std::string s = "1qazxsw23 edcvfr45tgbn hy67uj m,ki89ol.\\\\/;p0-=\\\\][";
    testing::internal::CaptureStdout();
    Func(s.c_str(), s.size());
    std::string result = testing::internal::GetCapturedStdout();
    std::string expected("26\n3\n10\n12\n");
    EXPECT_EQ(result, expected);
}
}  // namespace
