// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <functional>
#include <iostream>
#include <string>
#include <string_view>

#include "gtest/gtest.h"

namespace {

void ReverseOutPutAllWords(std::string_view const s) {
    std::function<std::string(std::string_view)> recursive =
        [&recursive](std::string_view const str) -> std::string {
        if (str.empty()) {
            return {""};
        }

        size_t i = 0;
        for (; i < str.size() &&
               !((('a' <= str.at(i)) && (str.at(i) <= 'z')) ||
                 (('A' <= str.at(i)) && (str.at(i) <= 'Z')));) {
            i += 1;
        }

        if (i >= str.size()) {
            return {""};
        }

        size_t const begin = i;
        for (; i < str.size() &&
               (('a' <= str.at(i) && str.at(i) <= 'z') ||
                ('A' <= str.at(i) && str.at(i) <= 'Z'));) {
            ++i;
        }
        std::string const back(str.substr(begin, i - begin).data(), i - begin);
        return recursive(str.substr(i)) + " " + back;
    };

    std::string ret = recursive(s);

    std::string const ret2(ret.begin() + 1, ret.end());

    std::cout << ret2 << '\n';
}

TEST(XNiukeHjv2, t2) {
    testing::internal::CaptureStdout();
    std::string const s("i am a student");

    ReverseOutPutAllWords(s);
    std::string const out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, std::string("student a am i\n"));
}

TEST(XNiukeHjv3, t2) {
    testing::internal::CaptureStdout();
    std::string const s("$bo*y gi!r#l");

    ReverseOutPutAllWords(s);
    std::string const out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, std::string("l r gi y bo\n"));
}
}  // namespace