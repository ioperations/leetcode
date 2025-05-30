// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <functional>
#include <iostream>
#include <string>

#include "gtest/gtest.h"

namespace {

void ReverseOutPutAllWords(const char* s, int len) {
    std::function<std::string(const char*, int)> recursive =
        [&recursive](const char* str, int str_len) -> std::string {
        // base case

        if (str_len == 0) {
            return {""};
        }

        int i = 0;
        /// 向前找到第一个word的开头
        for (; !((('a' <= *(str + i)) && (*(str + i) <= 'z')) ||
                 (('A' <= *(str + i)) && (*(str + i) <= 'Z')));) {
            i += 1;
        }

        const char* begin = str + i;

        if (i >= str_len) {
            return {""};
        }
        for (; ('a' <= *(str + i) && *(str + i) <= 'z') ||
               ('A' <= *(str + i) && *(str + i) <= 'Z');
             ++i) {
        }
        std::string const back(begin, str + i);
        return recursive(str + i, str_len - i) + " " + back;
    };

    std::string ret = recursive(s, len);

    /// remove the first " " in front of ret
    std::string const ret2(ret.begin() + 1, ret.end());

    std::cout << ret2 << std::endl;
}

TEST(x_niuke_hjv2, t2) {
    testing::internal::CaptureStdout();
    std::string const s("i am a student");

    ReverseOutPutAllWords(s.c_str(), s.size());
    std::string const out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, std::string("student a am i\n"));
}

TEST(x_niuke_hjv3, t2) {
    testing::internal::CaptureStdout();
    std::string const s("$bo*y gi!r#l");

    ReverseOutPutAllWords(s.c_str(), s.size());
    std::string const out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, std::string("l r gi y bo\n"));
}
}  // namespace
