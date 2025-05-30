// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <string>

#include "gtest/gtest.h"

namespace {
std::string ReturnS(const char* s, int len) {
    if (len == 0) {
        return "";
    }

    return ReturnS(s + 1, len - 1) + *s;
}

TEST(x_niuke_hjv2, t2) {
    std::string const s = "1516000";
    std::string const rets = ReturnS(s.c_str(), s.size());
    EXPECT_EQ(rets, std::string("0006151"));
}
}  // namespace
